#include "system/includes.h"
#include "app_config.h"
#include "device/uart.h"
#include "lwip.h"
#include "lwip/inet.h"
#include "syscfg/syscfg_id.h"
#include "wifi/wifi_connect.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"


static char ssid[33];
static char pwd[65];
static char P2P_Device_Name[30];
static u8   mac_addr[6];
void wifi_sta_connect(char *ssid, char *pwd, char save);


void cmd_do(char *buf)
{
    char *cmd = buf;
    if (buf == NULL) {
        return;
    }

    printf("cmd rec:%s\n", cmd);

    if (0 == memcmp(buf, "sta", strlen("sta"))) {  //串口输入 sta <ssid> <pwd> 进入STA模式。uart1 Rx为PA1
        if (sscanf(buf, "sta %s %s", ssid, pwd) == 2) {
            printf("Enter sta mode, ssid : %s, pwd: %s\n", ssid, pwd);
            wifi_sta_connect(ssid, pwd, 1);
        } else if (sscanf(buf, "sta %s", ssid) == 1) {
            wifi_sta_connect(ssid, "", 1);
        }
    } else if (0 == memcmp(buf, "ap", strlen("ap"))) {	//ap <ssid> <pwd> 进入AP模式
        if (sscanf(buf, "ap  %s %s", ssid, pwd) == 2) {
            printf("Enter ap mode, ssid : %s, pwd: %s\n", ssid, pwd);
            wifi_enter_ap_mode(ssid, pwd);
        } else if (sscanf(buf, "ap %s", ssid) == 1) {
            wifi_enter_ap_mode(ssid, "");
        }
    } else if (0 == memcmp(buf, "go", strlen("go"))) {	//go <name>  进入GO模式
        if (sscanf(buf, "go %s", P2P_Device_Name) == 1) {
            printf("Enter GO Mode, Device name: %s\n", P2P_Device_Name);
            wifi_enter_p2p_mode(P2P_GO_MODE, P2P_Device_Name);
        } else {
            printf("Enter GO Mode, Default device name");
            wifi_enter_p2p_mode(P2P_GO_MODE, "JL_GO_TEST");
        }
    } else if (0 == memcmp(buf, "gc", strlen("gc"))) {	//gc <name>  进入GC模式
        if (sscanf(buf, "gc %s", P2P_Device_Name) == 1) {
            printf("Enter GC Mode, Device name: %s\n", P2P_Device_Name);
            wifi_enter_p2p_mode(P2P_GC_MODE, P2P_Device_Name);
        } else {
            printf("Enter GC Mode, Default device name");
            wifi_enter_p2p_mode(P2P_GC_MODE, "JL_GC_TEST");
        }
    } else if (0 == memcmp(buf, "scan", strlen("scan"))) {	//scan
        void wifi_get_list_example(void);
        wifi_get_list_example();
    } else if (0 == memcmp(buf, "get_mac", strlen("get_mac"))) {	//get_mac 获取mac地址
        wifi_get_mac(mac_addr);
        printf("Mac addr: %02X:%02X:%02X:%02X:%02X:%02X", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    } else if (0 == memcmp(buf, "smp_cfg", strlen("smp_cfg"))) {	//smp_cfg 进入smp_cfg模式
        wifi_enter_smp_cfg_mode();
    } else if (0 == memcmp(buf, "ssid_store_test", strlen("ssid_store_test"))) {	//ssid_store_test 测试ssid存储
        u8 ssid_stored_cnt;
        struct wifi_stored_sta_info wifi_stored_sta_info[32];

        os_time_dly(5 * 100); //假设等待已经连接上路由器
        wifi_store_mode_info(STA_MODE, "GJ12", "123456789");
        wifi_store_mode_info(STA_MODE, "WL83", "12345678");
        wifi_store_mode_info(STA_MODE, "WIFI_PS_TEST", "12345678");

        ssid_stored_cnt = wifi_get_stored_sta_info(wifi_stored_sta_info);
        for (int i = 0; i < ssid_stored_cnt; i++) {
            printf("1:wifi_get_stored_sta_info[%d]= %s \r\n", i, wifi_stored_sta_info[i].ssid);
        }

        wifi_del_stored_sta_info("WIFI_PS_TEST"); //中途删除掉其中一个存储过的SSID

        ssid_stored_cnt = wifi_get_stored_sta_info(wifi_stored_sta_info);
        for (int i = 0; i < ssid_stored_cnt; i++) {
            printf("2:wifi_get_stored_sta_info[%d]= %s \r\n", i, wifi_stored_sta_info[i].ssid);
        }
    }
}


static u8 buf[1 * 1024] __attribute__((aligned(32))); //用于串口接收缓存数据的循环buf
static void uart_test_main(void *priv)
{
    char recv_buf[256];
    int len;
    int cnt = 0;
    void *hdl = dev_open("uart1", NULL);
    if (!hdl) {
        printf("open uart err !!!\n");
        return ;
    }
    /* 1 . 设置串口接收缓存数据的循环buf地址 */
    dev_ioctl(hdl, IOCTL_UART_SET_CIRCULAR_BUFF_ADDR, (int)buf);

    /* 1 . 设置串口接收缓存数据的循环buf长度 */
    dev_ioctl(hdl, IOCTL_UART_SET_CIRCULAR_BUFF_LENTH, sizeof(buf));

    /* 3 . 设置接收数据为阻塞方式,需要非阻塞可以去掉,建议加上超时设置 */
    dev_ioctl(hdl, IOCTL_UART_SET_RECV_BLOCK, 1);

    /* u32 parm = 1000; */
    /* dev_ioctl(hdl, IOCTL_UART_SET_RECV_TIMEOUT, (u32)parm); //超时设置 */

    /* 4 . 使能特殊串口,启动收发数据 */
    dev_ioctl(hdl, IOCTL_UART_START, 0);

    printf("uart_test_task running");

    while (1) {
        /* 5 . 接收数据 */
        len = dev_read(hdl, recv_buf, sizeof(recv_buf));
        if (len <= 0) {
            printf("\n  uart recv err len = %d\n", len);
            if (len == UART_CIRCULAR_BUFFER_WRITE_OVERLAY) {
                printf("\n UART_CIRCULAR_BUFFER_WRITE_OVERLAY err\n");
                dev_ioctl(hdl, IOCTL_UART_FLUSH, 0); //如果由于用户长期不取走接收的数据导致循环buf接收回卷覆盖,因此直接冲掉循环buf所有数据重新接收
            } else if (len == UART_RECV_TIMEOUT) {
                puts("UART_RECV_TIMEOUT...\r\n");
            }
            continue;
        }
        recv_buf[len] = '\0';
        cmd_do(recv_buf);
    }
    dev_close(hdl);
}

static int c_main(void)
{
    os_task_create(uart_test_main, NULL, 10, 4 * 1024, 0, "uart_test_main");
    return 0;
}

late_initcall(c_main);



