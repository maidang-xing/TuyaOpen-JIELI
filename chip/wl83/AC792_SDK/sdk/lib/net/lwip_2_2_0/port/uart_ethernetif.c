/* Includes ------------------------------------------------------------------*/
#include "typedef.h"
#include "lwip/err.h"
#include "etharp.h"
#include "ethip6.h"
#include "lwip/dhcp6.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip.h"
#include "lwip/sys.h"
#include "uart.h"

/* Define those to better describe your network interface. */
#define IFNAME0 'w'
#define IFNAME1 'l'

static void *uart_hdl = NULL;               //串口句柄
static u8 *uart_cbuf = NULL;                //用于串口接收缓存数据的循环buf
static u32 uart_cbuf_len = 20 * 1024;        //循环buf大小
static u8 *uart_recv_buf = NULL;            //用于lwip串口接收数据的buf
static u32 uart_recv_buf_len = 2 * 1024;   //buf大小
static u8 *uart_send_buf = NULL;             //用于lwip串口发送数据的buf
static u32 uart_send_buf_len = 2 * 1024;   //buf大小
static int lwip_uart_recv_pid = 0;          //线程pid
static u8 lwip_uart_mac_addr[6];            //mac地址

static struct uart_platform_data g_uart_parm = {
    .baudrate              = 4000000,
    .tx_pin                = IO_PORTB_05,
    .rx_pin                = IO_PORTB_04,
    .max_continue_recv_cnt = 0,       /* 后面再覆盖 */
    .idle_sys_clk_cnt      = 0,
    .parity                = UART_PARITY_DISABLE,
    .irq                   = IRQ_UART1_IDX,
};
static char g_uart_dev_name[16] = "uart1";

void uart_ethernetif_set_dev_name(const char *name)
{
    if (!name) {
        return;
    }

    strncpy(g_uart_dev_name, name, sizeof(g_uart_dev_name) - 1);
    g_uart_dev_name[sizeof(g_uart_dev_name) - 1] = '\0';
}

void uart_ethernetif_set_platform_data(const struct uart_platform_data *parm)
{
    if (!parm) {
        return;
    }
    memcpy(&g_uart_parm, parm, sizeof(g_uart_parm));
}

void lwip_uart_set_mac_addr(u8 *mac_addr)
{
    memcpy(lwip_uart_mac_addr, mac_addr, sizeof(lwip_uart_mac_addr));
}

void lwip_uart_get_mac_addr(u8 *mac_addr)
{
    memcpy(mac_addr, lwip_uart_mac_addr, sizeof(lwip_uart_mac_addr));
}

/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
static void low_level_init(struct netif *netif)
{
    /* set MAC hardware address length */
    netif->hwaddr_len = ETHARP_HWADDR_LEN;

    memcpy(netif->hwaddr, lwip_uart_mac_addr, sizeof(lwip_uart_mac_addr));

    /* maximum transfer unit */
    netif->mtu = NETIF_MTU;

    /* device capabilities */
    /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP | NETIF_FLAG_IGMP;

#if LWIP_IPV6
    netif->flags |= NETIF_FLAG_MLD6;
    netif->output_ip6 = ethip6_output;

#if LWIP_IPV6_DHCP6
    static struct dhcp6 dhcp6;
    dhcp6_set_struct(netif, &dhcp6);
#endif
#endif

    /* Do whatever else is needed to initialize interface. */

    /* Initialise the EMAC.  This routine contains code that polls status bits.
       If the Ethernet cable is not plugged in then this can take a considerable
       time.  To prevent this starving lower priority tasks of processing time we
       lower our priority prior to the call, then raise it back again once the
       initialisation is complete. */
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */
static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
#if ETH_PAD_SIZE
    pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

    if (!uart_hdl) {
        return ERR_IF_BUSY;
    }

    u8 *pos = uart_send_buf;
    for (struct pbuf *q = p; q != NULL; q = q->next) {
        memcpy(pos, q->payload, q->len);
        pos += q->len;
    }
    dev_write(uart_hdl, uart_send_buf, p->tot_len);

#if ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

    LINK_STATS_INC(link.xmit);

    return ERR_OK;
}

/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *low_level_input(void *rx_pkt, int len)
{
    struct pbuf *q, *p;
    u16 i;

    /* Obtain the size of the packet and put it into the "len" variable. */

    if (len == 0) {
        return 0;
    }

#if ETH_PAD_SIZE
    len += ETH_PAD_SIZE; /* allow room for Ethernet padding */
#endif

    /* We allocate a pbuf chain of pbufs from the pool. */
    p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);

    if (p != NULL) {
#if ETH_PAD_SIZE
        pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

        /* We iterate over the pbuf chain until we have read the entire packet into the pbuf. */
        for (i = 0, q = p; q != NULL; q = q->next) {
            /* Read enough bytes to fill this pbuf in the chain. The
             * available data in the pbuf is given by the q->len
             * variable.
             * This does not necessarily have to be a memcpy, you can also preallocate
             * pbufs for a DMA-enabled MAC and after receiving truncate it to the
             * actually received size. In this case, ensure the tot_len member of the
             * pbuf is the sum of the chained pbuf len members.
             */
            memcpy((u8_t *)q->payload, (u8_t *)rx_pkt + i, q->len);
            i += q->len;
        }

#if ETH_PAD_SIZE
        pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

        LINK_STATS_INC(link.recv);

    } else {
        /* puts("pbuf_alloc fail!\n"); */

        LINK_STATS_INC(link.memerr);
        LINK_STATS_INC(link.drop);
    }

    return p;
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
static void ethernetif_input(void *param, void *data, int len)
{
    struct pbuf *p;
    struct netif *netif = (struct netif *)param;

    /* move received packet into a new pbuf */
    p = low_level_input(data, len);
    /* no packet could be read, silently ignore this */
    if (p == NULL) {
        printf("no packet could be read\n");
        return;
    }

    if (netif->input(p, netif) != ERR_OK) {
        pbuf_free(p);
    }
}

static void lwip_uart_recv_task(void *priv)
{
    int ret = 0;
    struct netif *netif = (struct netif *)priv;

    while (1) {
        ret = dev_read(uart_hdl, uart_recv_buf, uart_recv_buf_len);
        if (ret <= 0) {
            printf("uart read fail ret:%d \n", ret);
            continue;
        }
        /* stats_display(); */
        ethernetif_input(netif, uart_recv_buf, ret);
    }
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t uart_ethernetif_init(struct netif *netif)
{
    int ret = 0;
#if LWIP_NETIF_HOSTNAME
    /* Initialize interface hostname */
    netif->hostname = LWIP_LOCAL_HOSTNAME;
#endif /* LWIP_NETIF_HOSTNAME */

    /*
     * Initialize the snmp variables and counters inside the struct netif.
     * The last argument should be replaced with your link speed, in units
     * of bits per second.
     */
#define LINK_SPEED_OF_YOUR_NETIF_IN_BPS (100*1000000)
    NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, LINK_SPEED_OF_YOUR_NETIF_IN_BPS);

    //netif->state = ethernetif;
    netif->name[0] = IFNAME0;
    netif->name[1] = IFNAME1;
    /* We directly use etharp_output() here to save a function call.
     * You can instead declare your own function an call etharp_output()
     * from it if you have to do some checks before sending (e.g. if link
     * is available...) */
    netif->output = etharp_output;
    netif->linkoutput = low_level_output;

    ret = lwip_uart_dev_init();
    if (ret) {
        printf("lwip_uart_dev_init err:%d", ret);
        return ret;
    }

    /* initialize the hardware */
    low_level_init(netif);

    thread_fork("lwip_uart_recv_task", 25, 2048, 2048
                , &lwip_uart_recv_pid, lwip_uart_recv_task, netif);

    //ethernetif->ethaddr = (struct eth_addr *)&(netif->hwaddr[0]);


    return ERR_OK;
}

static void lwip_uart_irq_cb(uart_irq_event_t event)
{
}

static int lwip_uart_dev_init(void)
{
    int ret = 0;

    struct uart_platform_data *uart_parm = &g_uart_parm;

    if (uart_parm->max_continue_recv_cnt == 0) {
        uart_parm->max_continue_recv_cnt = uart_recv_buf_len;
    }
    if (uart_parm->idle_sys_clk_cnt == 0) {
        uart_parm->idle_sys_clk_cnt = (3 * 10000000 / uart_parm->baudrate) * 24;
    }

    uart_hdl = dev_open("uart1", (void *)uart_parm);
    if (!uart_hdl) {
        printf("lwip uart dev open err \n");
        return ERR_IF_BUSY;
    }

    uart_cbuf = malloc(uart_cbuf_len);
    if (!uart_cbuf) {
        printf("lwip uart cbuf malloc err \n");
        ret = ERR_MEM;
        goto fail;
    }

    uart_send_buf = malloc(uart_send_buf_len);
    if (!uart_send_buf) {
        printf("lwip uart send buf  malloc err \n");
        ret = ERR_MEM;
        goto fail;
    }

    uart_recv_buf = malloc(uart_recv_buf_len);
    if (!uart_recv_buf) {
        printf("lwip uart recv buf  malloc err \n");
        ret = ERR_MEM;
        goto fail;
    }

    dev_ioctl(uart_hdl, IOCTL_UART_SET_CIRCULAR_BUFF_ADDR, (u32)uart_cbuf);
    dev_ioctl(uart_hdl, IOCTL_UART_SET_CIRCULAR_BUFF_LENTH, uart_cbuf_len);
    dev_ioctl(uart_hdl, IOCTL_UART_SET_SEND_BLOCK, 1);
    dev_ioctl(uart_hdl, IOCTL_UART_SET_RECV_BLOCK, 1);
    /* dev_ioctl(uart_hdl, IOCTL_UART_SET_IRQ_EVENT_CB, (u32)&lwip_uart_irq_cb); */
    dev_ioctl(uart_hdl, IOCTL_UART_START, 0);

    return 0;


fail:
    if (uart_hdl) {
        dev_close(uart_hdl);
        uart_hdl = NULL;
    }
    if (uart_cbuf) {
        free(uart_cbuf);
        uart_cbuf = NULL;
    }
    if (uart_send_buf) {
        free(uart_send_buf);
        uart_send_buf = NULL;
    }
    if (uart_recv_buf) {
        free(uart_recv_buf);
        uart_recv_buf = NULL;
    }
    return ret;
}

