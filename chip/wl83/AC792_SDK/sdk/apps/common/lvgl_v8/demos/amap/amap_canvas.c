#include "app_config.h"
//*********MY INCLUDE*********//
#include "amap_canvas.h"
#if LV_USE_DEMO_AMAP
#if AMAP_USE_CANVAS
#include "list.h"
#include "awk.h"
#include "stdio.h"
#include "awk_map.h"
#include "awk_defines.h"
#include "awk_map_defines.h"
#include "string.h"
#include "lv_gpu_jl_dma2d.h"
#if AMAP_OPEN_INFO
#define OPEN_INFO 1
#define INFO_PRINTF(...)    printf(__VA_ARGS__)
#else
#define OPEN_INFO 0
#define INFO_PRINTF(...)
#endif
#if LV_DISP_UI_FB_NUM == 2
#define BUF_DMA2D_COPY lv_draw_jl_dma2d_buffer_copy
#define JL_DMA2D_FILL lv_draw_jl_dma2d_blend_fill
#define BUF_MEMSET memset
#elif LV_DISP_UI_FB_NUM == 1
#define BUF_DMA2D_COPY
#define JL_DMA2D_FILL
#define BUF_MEMSET
#endif // LV_DISP_UI_FB_NUM
//****************************//
#ifdef CONFIG_UI_ENABLE

#ifdef CONFIG_UI_STYLE_LY_ENABLE
#include "lvgl_v8_ui_app/style_LY/generated/gui_guider.h"
#else
#include "lvgl_v8_ui_app/style_JL/generated/gui_guider.h"
#endif
/**
 * @brief 文件扫描信息
 */
// 全局变量保存 mapId
static uint32_t mapId = 0;
static awk_context_t context;
static int i2590 = 1;
static int malloccount = 0;
static int nodecount = 0;
static int maxmalloc = 0;
static bool first = 1;
static int disp_hor = 800;
static int disp_ver = 480;
static int map_hor = 386;
static int map_ver = 320;
//统计内存消耗节点
struct malloc_node {
    int size;
    void *ptr;
    struct list_head list;
};
LIST_HEAD(my_list);  // 初始化链表头
void add_malloc(void *ptr, int size)
{
#if OPEN_INFO
    // ✅ 使用 malloc 分配节点内存
    struct malloc_node *temp = (struct malloc_node *)malloc(sizeof(struct malloc_node));
    if (!temp) {
        printf("❌ 内存节点的内存分配失败\n");
        return;
    }
    temp->size = size;
    temp->ptr = ptr;
    INIT_LIST_HEAD(&temp->list);
    list_add_tail(&temp->list, &my_list);  // 插入到尾部
    printf("开辟内存的指针 %p，大小 %d 字节\n", ptr, size);
    //----------------------统计总大小,更新最大值----------------------
    struct malloc_node *pos, *n;
    list_for_each_entry_safe(pos, n, &my_list, list) {
        malloccount += pos->size + sizeof(struct malloc_node);
        nodecount ++;
    }
    if (malloccount > maxmalloc) {
        maxmalloc = malloccount;
    }
    malloccount = 0;
    nodecount = 0;
#endif
    return;
}
void delete_malloc(void *ptr)
{
#if OPEN_INFO
    struct malloc_node *pos, *n;
    int found = 0;
    // 遍历链表找到匹配的指针
    list_for_each_entry_safe(pos, n, &my_list, list) {
        if (pos->ptr == ptr) {
            list_del(&pos->list);  // 从链表中删除节点
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("警告：未找到对应指针 %p 的内存记录\n", ptr);
    } else {
        printf("释放内存指针 %p，大小 %d 字节\n", ptr, pos->size);
        free(pos);             // 释放节点本身占用的内存
    }
#endif
    return;
}
struct vfscan {
    u8 scan_file;					/*!< 是否扫描文件 */
    u8 subpath;						/*!< 子目录，设置是否只扫描一层 */
    u8 scan_dir;					/*!< 是否扫描目录 */
    u8 attr;						/*!< 文件属性 */
    u8 cycle_mode;					/*!< 扫描的循环模式 */
    char sort;						/*!< 扫描的文件排序 't' 'n' */
    char ftype[22 * 3 + 1];			/*!< 扫描的文件扩展类型 */
    u16 file_number;				/*!< 扫描出来的文件总数 */
    u16 file_counter;				/*!< 当前文件序号 */

    u16 dir_totalnumber;			/*!< 文件夹总数 */
    u16 musicdir_counter;			/*!< 播放文件所在文件夹序号 */
    u16 fileTotalInDir;				/*!< 文件夹下的文件数目 */

    void *priv;						/*!< 私有指针 */
    struct vfs_devinfo *dev;		/*!< 设备信息 */
    struct vfs_partition *part;		/*!< 分区信息 */
    char filt_dir[12];				/*!< 设置文件夹过滤 */
    char fasten_num[8];
    char *fasten_buf;
    char *d_save;
};
/*下载回调函数（离线地图未用到）
static void on_download_started(awk_map_download_callback_t *callback) {
    printf("📥 地图开始下载...\n");
}
static void on_download_progress(awk_map_download_callback_t *callback, float progress) {
    printf("📊 下载进度: %.2f%%\n", progress * 100);
}
static void on_download_finish(awk_map_download_callback_t *callback) {
    printf("✅ 地图下载完成，初始化地图...\n");

    // 步骤1：创建地图窗口
    awk_map_view_param_t awkParam;
    awkParam.port.width = disp_hor;
    awkParam.port.height = disp_ver;
    mapId = awk_map_create_view(awkParam); // 创建地图
    printf("📍 地图创建成功，mapId = %u\n", mapId);

    // 步骤2：开始绘制
    printf("开始绘制地图\n");
    sys_timer_add(NULL, (void (*)(void *))awk_map_do_render, 33);

    // 步骤3：设置缩放等级和中心点
    awk_map_set_level(mapId, 14);
    awk_map_coord2d_t map_center;
    map_center.lat = 39.9219;  // 北京朝阳区的GCJ02大概坐标
    map_center.lon = 116.4435;
    awk_map_set_center(mapId, map_center);
    // 第一个参数是创建地图时返回的地图id，第二个参数即窗口宽高
}
static void on_download_stop(awk_map_download_callback_t *callback) {
    printf("⏹️ 下载被中止\n");
}
static void on_download_error(awk_map_download_callback_t *callback, int32_t error_code, const char *msg) {
    printf("❌ 下载失败，code = %d，msg = %s\n", error_code, msg);
}
void my_activate_callback(bool result, int code, const char* msg) {
    printf("进入激活回调函数\n");
    if (result) {
        printf("✅ 设备激活成功\n");
        // 构造回调结构体
        static awk_map_download_callback_t cb = {
            .on_started = on_download_started,
            .on_progress = on_download_progress,
            .on_finish = on_download_finish,
            .on_stop = on_download_stop,
            .on_error = on_download_error,
        };
        int mapret = awk_map_start_download_offline_data("110105", 16, &cb);
        if (mapret == 0) printf("download map suss!\n");
        else if (mapret == -1) printf("no init!\n");
        else if (mapret == -3) printf("init thread  and this thread different!\n");
    } else {
        printf("❌ 激活失败，code = %d，msg = %s\n", code, msg);
    }
}*/
static void awk_mem_free_adapter(void *ptr)
{
#if OPEN_INFO
    printf("free start\n");
    delete_malloc(ptr);
#endif
    free(ptr);
    ptr = NULL;
}
static void *awk_mem_malloc_adapter(size_t size)
{
    INFO_PRINTF("malloc start\n");
    void *ptr = malloc(size);
#if OPEN_INFO
    if (ptr) {
        add_malloc((void *)ptr, (int)size);
    }
#endif
    return ptr;
}
static void *awk_mem_calloc_adapter(size_t count, size_t size)
{
    INFO_PRINTF("calloc start\n");
    void *ptr = calloc(count, size);
#if OPEN_INFO
    if (ptr) {
        add_malloc(ptr, (int)(count * size));  // 加入到链表中
    }
#endif
    return ptr;
}
static void *awk_mem_realloc_adapter(void *ptr, size_t size)
{
    INFO_PRINTF("realloc start\n");
    void *r_ptr = realloc(ptr, size);
#if OPEN_INFO
    int found = 0;
    if (!r_ptr) {
        // realloc失败，原指针不变，直接返回NULL
        printf("realloc失败，ptr=%p，size=%zu\n", ptr, size);
        return NULL;
    }
    if (ptr == NULL) {
        // 原指针为空，等同于malloc，添加新节点
        add_malloc(r_ptr, (int)size);
    } else {
        // 原指针非空，更新链表中对应节点的 ptr 和 size
        struct malloc_node *pos, *n;
        list_for_each_entry_safe(pos, n, &my_list, list) {
            if (pos->ptr == ptr) {
                pos->ptr = r_ptr;
                pos->size = (int)size;
                printf("realloc更新节点 ptr %p -> %p，大小 %d\n", ptr, r_ptr, (int)size);
                found = 1;
                break;
            }
        }
        if (!found) {
            // 找不到对应节点，可能之前没加，直接加一个新节点
            printf("警告：realloc时未找到原指针 %p，新增节点\n", ptr);
            add_malloc(r_ptr, (int)size);
        }
    }
#endif
    return r_ptr;
}
static void *awk_file_open_adapter(const char *filename, const char *mode)
{
    FILE *file = fopen(filename, mode);
#if OPEN_INFO
    printf("openfile %s start\n", filename);
    if (file == NULL) {
        printf("openfile fail!\n");
    } else {
        printf("openfile suss!\n");
    }
#endif
    return (void *)file;
}
static int awk_file_close_adapter(void *handler)
{
    FILE *file = (FILE *)handler;
    INFO_PRINTF("closefile start\n");
    return fclose(file);
}
static int awk_file_seek_adapter(void *handler, long offset, int where)
{
    INFO_PRINTF("seek start\n");
    FILE *file = (FILE *)handler;
    return fseek(file, offset, where);
}
static int awk_file_flush_adapter(void *handler)
{
    INFO_PRINTF("flush start\n");
    FILE *file = (FILE *)handler;
    return fflush(file);
}
static size_t awk_file_read_adapter(void *ptr, size_t size, void *handler)
{
#if OPEN_INFO
    char *name = (char *)malloc(256);
    add_malloc((void *)name, 256);
    fget_name((FILE *)handler, name, 256);
    printf("read file %s start\n", name);
    delete_malloc((void *)name);
    free(name);
    name = NULL;
#endif
    return fread(ptr, sizeof(char), size, (FILE *)handler);
}
static size_t awk_file_write_adapter(void *ptr, size_t size, void *handler)
{
#if OPEN_INFO
    char *name = (char *)malloc(256);
    add_malloc((void *)name, 256);
    fget_name((FILE *)handler, name, 256);
    printf("write file %s start\n", name);
    delete_malloc((void *)name);
    free(name);
    name = NULL;
#endif
    return fwrite(ptr, sizeof(char), size, (FILE *)handler);
}
static bool awk_file_exists_adapter(const char *path)
{
    // 使用 vfs 的文件打开函数尝试打开文件
    INFO_PRINTF("ask file is exists start\n");
    FILE *file = fopen(path, "r");
    if (file) {
        fclose(file);  // 能打开说明文件存在，记得关闭
        return true;
    }
    return false;  // 打不开说明文件不存在
}
static bool awk_file_dir_exists_adapter(const char *path)
{
    char *pathtemp = (char *)malloc(strlen(path) + 5);
#if OPEN_INFO
    add_malloc((void *)pathtemp, (int)(strlen(path) + 5));
#endif
    strcpy(pathtemp, path);
    if (pathtemp[strlen(pathtemp) - 1] != '/') {
        strcat(pathtemp, "/");
    }
    INFO_PRINTF("are %s exists start\n", pathtemp);
    bool temp = fdir_exist(pathtemp);
#if OPEN_INFO
    if (temp) {
        printf("%s exists\n", pathtemp);
    } else {
        printf("%s not exists\n", pathtemp);
    }
    delete_malloc((void *)pathtemp);
#endif
    free(pathtemp);
    pathtemp = NULL;
    return temp;
}
static int awk_file_remove_adapter(const char *path)
{
    INFO_PRINTF("rmfile start\n");
    return fdelete_by_name(path);
}
static int awk_file_mkdir_adapter(const char *path, uint16_t model)
{
    char *pathtemp = (char *)malloc(strlen(path) + 5);
#if OPEN_INFO
    add_malloc((void *)pathtemp, (int)(strlen(path) + 5));
#endif
    strcpy(pathtemp, path);
    if (pathtemp[strlen(pathtemp) - 1] != '/') {
        strcat(pathtemp, "/");
    }
    FILE *ret = fopen(pathtemp, "w+");
#if OPEN_INFO
    if (ret != NULL) {
        printf("mkdir %s suss!\n", pathtemp);
    } else {
        printf("mkdir %s fail!", pathtemp);
    }
    delete_malloc((void *)pathtemp);
#endif
    free(pathtemp);
    pathtemp = NULL;
    fclose(ret);
}
static int awk_file_rmdir_adapter(const char *path)
{
    char *pathtemp = (char *)malloc(strlen(path) + 5);
#if OPEN_INFO
    add_malloc((void *)pathtemp, (int)(strlen(path) + 5));
#endif
    strcpy(pathtemp, path);
    if (pathtemp[strlen(pathtemp) - 1] != '/') {
        strcat(pathtemp, "/");
    }
    int ret = fdelete_dir(pathtemp);
#if OPEN_INFO
    if (ret == 0) {
        printf("rmdir %s suss!\n", pathtemp);
    } else {
        printf("rmdir %s fail!\n", pathtemp);
    }
    delete_malloc((void *)pathtemp);
#endif
    free(pathtemp);
    pathtemp = NULL;
    return ret;
}
static void *awk_file_opendir_adapter(const char *path)
{
    if (!path) {
        return NULL;  // 路径为空
    }
    INFO_PRINTF("opendir start\n");
    char *pathtemp = (char *)malloc(strlen(path) + 5);
#if OPEN_INFO
    add_malloc((void *)pathtemp, (int)(strlen(path) + 5));
#endif
    strcpy(pathtemp, path);
    // 使用 vfscan 打开目录
    if (pathtemp[strlen(pathtemp) - 1] != '/') {
        strcat(pathtemp, "/");
    }
    struct vfscan *scan = fscan(pathtemp, "-d -tALL -sn", 100); // 100 是最大目录+文件项数，可根据需要调整
    if (!scan) {
        INFO_PRINTF("fscan failed for path: %s\n", pathtemp);
        return NULL;
    }
#if OPEN_INFO
    printf("fscan suss for path: %s\n", pathtemp);
    delete_malloc((void *)pathtemp);
#endif
    free(pathtemp);
    pathtemp = NULL;
    return (void *)scan;  // 返回结构体句柄，供 closedir 和 readdir 使用
}
static int awk_file_closedir_adapter(void *dir)
{
    if (!dir) {
        return -1;  // 参数错误或目录已经关闭
    }

    fscan_release((struct vfscan *)dir);  // 释放目录扫描结构体资源
    INFO_PRINTF("closedir start\n");
    return 0;  // 成功关闭目录
}
static bool awk_file_readdir_adapter(void *dir, awk_readdir_result *result)
{
    if (!dir || !result) {//如果dir和result为空直接返回
#if OPEN_INFO
        printf("Invalid input to readdir_adapter\n");
#endif
        return 0;
    }
    struct vfscan *scan = (struct vfscan *)dir;
    int count = scan->file_number;//文件总数

    result->nodes = (awk_file_node *)calloc(count, sizeof(awk_file_node));
#if OPEN_INFO
    add_malloc(result->nodes, (int)(count * sizeof(awk_file_node)));
#endif
    if (!result->nodes) {
        INFO_PRINTF("Failed to allocate memory for readdir result\n");
        result->size = 0;
        return 0;
    }
    result->size = count;
    INFO_PRINTF("有%d个文件\n", count);
    FILE *file = fselect(scan, 0, 0);
    for (int i = 0; i < count && file; i++) {
        // 获取文件名
        fget_name(file, result->nodes[i].file_name, sizeof(result->nodes[i].file_name));
        INFO_PRINTF("文件%d：%s\n", i + 1, result->nodes[i].file_name);
        INFO_PRINTF("文件大小：%d\n", flen(file));
        // 获取文件大小（可选，如果你不需要可以不写）
        result->nodes[i].file_size = flen(file);
        // 关闭当前项
        fclose(file);
        // 选择下一个
        file = fselect(scan, 2, 0);
    }
    return 1;
}
static size_t awk_file_get_size_adapter(const char *path)
{
    INFO_PRINTF("getsize start\n");
    FILE *fp = fopen(path, "r"); // 或 "rb"，根据你的需求
    if (!fp) {
        return 0; // 打开失败
    }

    size_t size = flen(fp); // 使用 vfs_operations 提供的 flen
    fclose(fp);
    return size;
}
static long awk_file_get_last_access_adapter(const char *path)
{
    INFO_PRINTF("last_access start\n");//待实现
    return 0;
}
static int awk_file_rename_adapter(const char *old_name, const char *new_name)
{
    INFO_PRINTF("rename start\n");
    FILE *temp = fopen(old_name, "w+");
    frename(temp, new_name);
    fclose(temp);
}
static bool awk_file_unzip_adapter(const char *zip_file, const char *out_dir)
{
    INFO_PRINTF("unzip start\n");//待实现
}
lv_obj_t *canvas = NULL;
void *canvas_buf = NULL;
static void awk_render_begin_drawing_adapter(uint32_t map_id, awk_render_context_t status)
{
    if (first) {
        canvas_buf = malloc(LV_CANVAS_BUF_SIZE_TRUE_COLOR(map_hor, map_ver));
#if OPEN_INFO
        add_malloc(canvas_buf, map_hor * map_ver * 2);
#endif
        if (!canvas_buf) {
            // 申请失败，打印错误或返回
            return;
        }
        // 创建canvas对象，父对象为当前屏幕
        canvas = lv_canvas_create(lv_scr_act());
        lv_canvas_set_buffer(canvas, canvas_buf, map_hor, map_ver, LV_IMG_CF_TRUE_COLOR);
        lv_obj_set_pos(canvas, 0, 0);
    } else {
        return;
    }
    INFO_PRINTF("render begin drawing start\n");
    return;//2590
}
static void awk_render_commit_drawing_adapter(uint32_t map_id)
{
    INFO_PRINTF("render commit drawing start\n");
    lv_disp_t *disp = lv_disp_get_default();
    if (disp == NULL) {
        INFO_PRINTF("no default display\n");
        return;
    }
    lv_refr_now(disp);
}
static void awk_render_point_adapter(uint32_t map_id, awk_point_t *point, uint32_t point_size, const awk_paint_style_t *style)
{
    //因为还未用到，所以还未实现改功能，要实现详情请见polyline
    INFO_PRINTF("render point start\n");
    // 1. 检查输入参数是否有效
    if (!point || !style) {
        return;
    }

    // 2. 地图坐标转LVGL屏幕坐标（示例：假设point->x/y已为屏幕像素坐标，实际需根据地图缩放/偏移调整）
    lv_coord_t x = (lv_coord_t)point->x;  // 点的X坐标（像素）
    lv_coord_t y = (lv_coord_t)point->y;  // 点的Y坐标（像素）

    // 3. 定义点的绘制区域（1x1像素对应点，point_size可扩展为点的大小）
    lv_area_t point_area;
    point_area.x1 = x;                      // 左上角X
    point_area.y1 = y;                      // 左上角Y
    point_area.x2 = x + point_size - 1;     // 右下角X（根据point_size扩展点大小）
    point_area.y2 = y + point_size - 1;     // 右下角Y

    // 4. 配置点的样式（颜色、透明度等）
    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);               // 初始化绘制描述符
    rect_dsc.bg_color = lv_color_hex(style->color);  // 从高德样式获取颜色（假设style->color是0xRRGGBB格式）
    rect_dsc.bg_opa = LV_OPA_COVER;                 // 不透明（可根据style调整透明度）
    rect_dsc.radius = point_size / 2;               // 圆角（让点看起来更圆润）

    // 5. 调用LVGL的lv_draw_rect绘制点（本质是绘制小矩形）
    lv_draw_rect(&point_area, NULL, &rect_dsc);
}
bool first_polyline = 1;
int linenum = 0;
static void awk_render_polyline_adapter(uint32_t map_id, awk_point_t *points, uint32_t point_size, const awk_paint_style_t *style)
{
    if (!first_polyline) {
        return;
    }
    linenum++;
    INFO_PRINTF("linenum = %d\n", linenum);
    if (!canvas || !style || point_size < 2) {
        return;
    }
    // 输出颜色信息
    uint32_t argb = style->color;
    uint8_t a = (argb >> 24) & 0xFF;
    uint8_t r = (argb >> 16) & 0xFF;
    uint8_t g = (argb >> 8) & 0xFF;
    uint8_t b = argb & 0xFF;

    INFO_PRINTF("🎨 color = 0x%08X → (A=%d, R=%d, G=%d, B=%d), width = %d\n", argb, a, r, g, b, style->width);
    // 设置线条样式
    lv_draw_line_dsc_t line_dsc;
    lv_draw_line_dsc_init(&line_dsc);
    line_dsc.color = lv_color_make(r, g, b);
    line_dsc.opa = a;
    line_dsc.width = style->width;
    line_dsc.round_start = 1;
    line_dsc.round_end = 1;
    lv_canvas_draw_line(canvas, points, point_size, &line_dsc);
    INFO_PRINTF("✅ polyline drawn on canvas\n");
}
static void awk_render_polygon_adapter(uint32_t map_id, awk_point_t *points, uint32_t point_size, const awk_paint_style_t *style)
{
    //目前没用到，所以此处还未写功能，要完善详情请见polyline
    INFO_PRINTF("render polygon start\n");
    if (!points || point_size < 3 || !style) {
        return;    // 多边形至少3点
    }

    lv_draw_line_dsc_t line_dsc;
    lv_draw_line_dsc_init(&line_dsc);

    uint32_t argb = style->color;
    uint8_t a = (argb >> 24) & 0xFF;
    uint8_t r = (argb >> 16) & 0xFF;
    uint8_t g = (argb >> 8) & 0xFF;
    uint8_t b = argb & 0xFF;

    line_dsc.color = lv_color_make(r, g, b);
    line_dsc.opa = a;
    line_dsc.width = style->width;

    // 依次连线
    for (uint32_t i = 0; i < point_size - 1; i++) {
        lv_point_t p1 = { points[i].x, points[i].y };
        lv_point_t p2 = { points[i + 1].x, points[i + 1].y };
        lv_draw_line(lv_disp_get_default(), &line_dsc, &p1, &p2);
    }
    // 闭合多边形，连接最后一点和第一点
    lv_point_t p_last = { points[point_size - 1].x, points[point_size - 1].y };
    lv_point_t p_first = { points[0].x, points[0].y };
    lv_draw_line(lv_disp_get_default(), &line_dsc, &p_last, &p_first);
}
int mapi = 0;
lv_obj_t *img_obj[20] = {0};
lv_img_dsc_t *img_dsc[20] = {0};
uint8_t *temp_buffer[20] = {0};
static void awk_render_bitmap_adapter(uint32_t map_id, awk_rect_area_t area, awk_bitmap_t bitmap, const awk_paint_style_t *style)
{
#if OPEN_INFO
    int a, b;
    a = get_system_ms();
#endif
    if (first_polyline) {
        linenum = 0;
        first_polyline = 0;
    }
    if (mapi == 0) {
        for (int i = 0; i < 20; i++) {
            if (temp_buffer[i] != NULL) {
                free(temp_buffer[i]);
#if OPEN_INFO
                delete_malloc((void *)temp_buffer[i]);
#endif
                temp_buffer[i] = NULL;
            }
            if (img_dsc[i] != NULL) {
                free(img_dsc[i]);
#if OPEN_INFO
                delete_malloc((void *)img_dsc[i]);
#endif
                img_dsc[i] = NULL;
            }
            if (img_obj[i] != NULL) {
                lv_obj_del(img_obj[i]);
                img_obj[i] = NULL;
            }
        }
    }
    INFO_PRINTF("mapi：%d\n", mapi);
    INFO_PRINTF("🖼️ [Bitmap Render Start] map_id=%u\n", map_id);
    INFO_PRINTF("📐 Render Area: x=%d, y=%d, width=%d, height=%d\n", area.x, area.y, area.width, area.height);
    INFO_PRINTF("🧱 Bitmap Info: width=%u, height=%u, buffer_size=%u, stride=%u, pixel_mode=%d, pre_multiplied=%s\n",
                bitmap.width, bitmap.height, bitmap.buffer_size, bitmap.stride,
                bitmap.pixel_mode, bitmap.pre_multiplied ? "true" : "false");

    /*下载图片
    char *temp = (char *)malloc(150);
    char str2590[20];
    sprintf(str2590,"%d",i2590);
    strcpy(temp,"storage/sd0/C/tempdata/");
    strcat(temp,str2590);
    strcat(temp,".bin");
    FILE* fp = fopen(temp,"w+");
    if (fp) {
        size_t written = fwrite(bitmap.buffer, 1, bitmap.buffer_size, fp);
        fclose(fp);
        printf("💾 已保存原始图像数据 %d 字节 到 %s\n", written, temp);
    } else {
        printf("❌ 打开文件失败：%s\n", temp);
    }
    i2590++;*/
    temp_buffer[mapi] = malloc(bitmap.buffer_size);
#if OPEN_INFO
    add_malloc((void *)temp_buffer[mapi], bitmap.buffer_size);
#endif
    memcpy(temp_buffer[mapi], bitmap.buffer, bitmap.buffer_size);
    img_dsc[mapi] = malloc(sizeof(lv_img_dsc_t));
#if OPEN_INFO
    add_malloc((void *)img_dsc[mapi], sizeof(lv_img_dsc_t));
#endif
    img_dsc[mapi]->header.always_zero = 0;
    img_dsc[mapi]->header.w = bitmap.width;
    img_dsc[mapi]->header.h = bitmap.height;
    img_dsc[mapi]->header.cf = LV_IMG_CF_TRUE_COLOR;
    img_dsc[mapi]->data_size = bitmap.buffer_size;
    img_dsc[mapi]->data = temp_buffer[mapi];
    img_obj[mapi] = lv_img_create(lv_scr_act());
    lv_img_set_src(img_obj[mapi], img_dsc[mapi]);
    lv_obj_set_pos(img_obj[mapi], area.x, area.y);
    lv_obj_set_size(img_obj[mapi], area.width, area.height);

    lv_img_set_angle(img_obj[mapi], style->angle * 10);
    INFO_PRINTF("刷新完成\n");
    mapi++;
#if OPEN_INFO
    b = get_system_ms();
    printf("bitmap绘制时间：%dms\n", b - a);
#endif
}
static void awk_render_color_adapter(uint32_t map_id, awk_rect_area_t area, const awk_paint_style_t *style)
{
    if (first) {
        first = 0;
    } else {
        return;
    }
    if (!style) {
        return;
    }
    INFO_PRINTF("🖌️ render color start\n");

    // 提取颜色（ARGB）
    uint32_t argb = style->color;
    uint8_t a = (argb >> 24) & 0xFF;
    uint8_t r = (argb >> 16) & 0xFF;
    uint8_t g = (argb >> 8) & 0xFF;
    uint8_t b = argb & 0xFF;

    // 生成 lv_color_t（假设使用 RGB565 显存）
    lv_color_t lv_color = lv_color_make(r, g, b);
    lv_canvas_fill_bg(canvas, lv_color, LV_OPA_COVER);
    INFO_PRINTF("✅ blend_fill done: color R=%d G=%d B=%d\n", r, g, b);
}
static uint64_t awk_get_system_time_adapter(void)
{
    INFO_PRINTF("get system time start\n");
    uint32_t tick = get_system_ms();
    // 如果1 tick = 1ms，直接返回tick即可
    // 如果1 tick = x ms，需要乘以x

    return (uint64_t)tick; // 单位：毫秒
}
static int awk_printf_adapter(const char *__fmt, ...)
{
#if OPEN_INFO
    INFO_PRINTF("printf start\n");
    va_list args;
    va_start(args, __fmt);
    int ret = vprintf(__fmt, args);
    va_end(args);
    return ret;
#endif
}
static uint64_t awk_aos_network_adapter_send_adapter(awk_http_request_t *request, awk_http_response_callback_t *callback)
{
    INFO_PRINTF("network send start\n");
    return 0;
}
static void awk_aos_network_adapter_cancel_adapter(uint64_t request_id)
{
    INFO_PRINTF("network cancel start\n");
    return;
}
void *your_thread_create_function(void (*func)(void *), void *arg)
{
    INFO_PRINTF("thread create start\n");
    // 如果无多线程，直接调用func，返回NULL
    func(arg);
    return NULL;
}
static uint64_t my_get_thread_id(void)
{
    return get_cur_thread_pid();
}
void show_malloc_size()
{
#if OPEN_INFO
    struct malloc_node *pos, *n;
    list_for_each_entry_safe(pos, n, &my_list, list) {
        malloccount += pos->size + sizeof(struct malloc_node);
        nodecount ++;
    }
    printf("内存块数量：%d,内存占用情况：%d字节\n,最大内存占用情况：%d字节", nodecount, malloccount, maxmalloc);
    malloccount = 0;
    nodecount = 0;
#endif
    return;
}
static void touch_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    lv_point_t point;
    lv_indev_get_point(lv_indev_get_act(), &point);
    mapi = 0;
    switch (code) {
    case LV_EVENT_PRESSED:
        awk_map_touch_begin(mapId, point.x, point.y);
        INFO_PRINTF("awk_map_touch_begin\n");
        break;
    case LV_EVENT_PRESSING:
        awk_map_touch_update(mapId, point.x, point.y);
        INFO_PRINTF("awk_map_touch_update\n");
        break;
    case LV_EVENT_RELEASED:
    case LV_EVENT_PRESS_LOST:
        awk_map_touch_end(mapId, point.x, point.y);
        INFO_PRINTF("awk_map_touch_end\n");
        break;
    }
#if OPEN_INFO
    int a, b;
    a = get_system_ms();
#endif
    awk_map_do_render();
#if OPEN_INFO
    b = get_system_ms();
    printf("运行时间：%dms\n", b - a);
#endif
}
/*空函数，用来查看链接前的资源消耗时打开
int32_t awk_init(awk_context_t *context){}
int32_t awk_map_create_view(awk_map_view_param_t param){}
int awk_map_set_level(uint32_t a,float b){}
int32_t awk_map_set_center(uint32_t map_id, awk_map_coord2d_t coord2d){}
int32_t awk_map_do_render(void){};*/
void AMAP_USE_TILE_DEMO(void)
{
    printf("LCD Width: %d, Height: %d\n", LCD_W, LCD_H);
    extern int storage_device_ready(void);
    while (storage_device_ready() != true) {
        os_time_dly(3);    //example
    }
    lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_TRANSP, LV_PART_MAIN);
    memset(&context, 0, sizeof(awk_context_t)); //务必先memset
    context.tile_pixel_mode = AWK_PIXEL_MODE_RGB_565;
    context.device_id = "259066";
    context.key = "259066";
    context.root_dir = "storage/sd0/C/GDPfile";            //SDK内部文件夹根路径
    context.offline_map_dir = "storage/sd0/C/offline"; // 离线文件路径
    context.tile_mem_cache_max_size = 0;     //栅格图内存缓存限值，单位：MB
    context.tile_disk_cache_max_size = 200;  //栅格图磁盘缓存限值，单位：MB
    context.tile_load_mode = AWK_MAP_TILE_LOAD_OFFLINE;    //离线模式
    //内存相关适配
    context.memory_adapter.mem_malloc = awk_mem_malloc_adapter;
    context.memory_adapter.mem_free = awk_mem_free_adapter;
    context.memory_adapter.mem_calloc = awk_mem_calloc_adapter;
    context.memory_adapter.mem_realloc = awk_mem_realloc_adapter;

    //文件相关适配
    context.file_adapter.file_open = awk_file_open_adapter;
    context.file_adapter.file_close = awk_file_close_adapter;
    context.file_adapter.file_read = awk_file_read_adapter;
    context.file_adapter.file_write = awk_file_write_adapter;
    context.file_adapter.file_mkdir = awk_file_mkdir_adapter;
    context.file_adapter.file_exists = awk_file_exists_adapter;
    context.file_adapter.file_remove = awk_file_remove_adapter;
    context.file_adapter.file_opendir = awk_file_opendir_adapter;
    context.file_adapter.file_closedir = awk_file_closedir_adapter;
    context.file_adapter.file_readdir = awk_file_readdir_adapter;
    context.file_adapter.file_seek = awk_file_seek_adapter;
    context.file_adapter.file_flush = awk_file_flush_adapter;
    context.file_adapter.file_rmdir = awk_file_rmdir_adapter;
    context.file_adapter.file_dir_exists = awk_file_dir_exists_adapter;
    context.file_adapter.file_get_size = awk_file_get_size_adapter;
    context.file_adapter.file_get_last_access = awk_file_get_last_access_adapter;
    context.file_adapter.file_rename = awk_file_rename_adapter;
    context.file_adapter.file_unzip = awk_file_unzip_adapter;

    //网络相关适配
    context.network_adapter.send = awk_aos_network_adapter_send_adapter;
    context.network_adapter.cancel = awk_aos_network_adapter_cancel_adapter;

    //渲染绘制相关适配
    context.render_adapter.begin_drawing = awk_render_begin_drawing_adapter;
    context.render_adapter.commit_drawing = awk_render_commit_drawing_adapter;
    context.render_adapter.draw_point = awk_render_point_adapter;
    context.render_adapter.draw_polyline = awk_render_polyline_adapter;
    context.render_adapter.draw_polygon = awk_render_polygon_adapter;
    context.render_adapter.draw_bitmap = awk_render_bitmap_adapter;
    context.render_adapter.draw_color = awk_render_color_adapter;

    //其他系统相关适配
    context.system_adapter.get_system_time = awk_get_system_time_adapter;
    context.system_adapter.log_printf = awk_printf_adapter;
    //线程
    context.thread_adapter.get_thread_id = my_get_thread_id;
    int isOK = awk_init(&context);
    printf("2590_awk_init : %d\n", isOK);
    // 步骤1：创建地图窗口
    awk_map_view_param_t awkParam;
    awkParam.port.width = map_hor;
    awkParam.port.height = map_ver;
    mapId = awk_map_create_view(awkParam); // 创建地图
    printf("📍 地图创建成功，mapId = %u\n", mapId);
    // 步骤2：设置缩放等级和中心点
    awk_map_set_level(mapId, 16);
    awk_map_coord2d_t map_center;
    map_center.lat = 39.995273;  // 北京朝阳区的GCJ02大概坐标
    map_center.lon = 116.473362;
    awk_map_set_center(mapId, map_center);
    //挪动事件设置
    lv_obj_add_event_cb(lv_scr_act(), touch_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(lv_scr_act(), touch_cb, LV_EVENT_PRESSING, NULL);
    lv_obj_add_event_cb(lv_scr_act(), touch_cb, LV_EVENT_RELEASED, NULL);
    lv_obj_add_event_cb(lv_scr_act(), touch_cb, LV_EVENT_PRESS_LOST, NULL);
    /*离线下载的（展开)
    // 步骤3：下载离线地图
    if (isOK == 0) {
        printf("✅ awk_init 成功，正在激活设备\n");
        //awk_activate_device(NULL);
        printf("✅ 设备激活成功\n");
        // 构造回调结构体
        awk_map_download_callback_t *cb = (awk_map_download_callback_t *)malloc(sizeof(awk_map_download_callback_t));
        cb->on_started = on_download_started;
        cb->on_started = on_download_started;
        cb->on_progress = on_download_progress;
        cb->on_finish = on_download_finish;
        cb->on_stop = on_download_stop;
        cb->on_error = on_download_error;
        int mapret = awk_map_start_download_offline_data("110105", 16, cb);
        if (mapret == 0) printf("download map suss!\n");
        else if (mapret == -1) printf("no init!\n");
        else if (mapret == -3) printf("init thread  and this thread different!\n");
    } else {
        printf("❌ awk_init 失败，无法继续激活设备\n");
    }
    // 查询通过adcode下载的
    awk_map_offline_gdb_query_result_t result;
    memset(&result, 0, sizeof(awk_map_offline_gdb_query_result_t));
    awk_map_list_download_offline_regions("110105", 16, &result);
    for (int i = 0;i < result.size; i++) {
        printf("list adcode: %s %d %s\n", result.infos[i].adcode_info.adcode, result.infos[i].level, result.infos[i].file_name);
    }
    if (result.size == 0) printf("not found download map!\n");
    if (result.infos) {
        awk_mem_free_adapter(result.infos);
        result.infos = NULL;
        result.size = 0;
    }*/
    // 步骤4：开始绘制
    printf("开始绘制地图\n");
#if OPEN_INFO
    lv_timer_create(show_malloc_size, 2000, NULL);
#endif
    lv_timer_t *t1 = lv_timer_create(awk_map_do_render, 500, NULL);
    lv_timer_set_repeat_count(t1, 1);  // 只执行1次
}
#endif //CONFIG_UI_ENABLE
#endif //AMAP_USE_CANVAS
#endif //LV_USE_DEMO_AMAP

