#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "./events_init.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "lvgl.h"
#include "./callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../gui_group/gui_group.h"




#include "../../custom/custom.h"
extern void carnum_utf8_to_gb2312(const uint8_t *utf_8, uint8_t *gb2312_data, int selected_index);
#if !LV_USE_GUIBUILDER_SIMULATOR
extern void exit_sys_setting_menu(void);
#endif
extern bool update_date;
#if LV_USE_GUIBUILDER_SIMULATOR
int cur_mode = 0;
#endif
static uint8_t del = 0;
extern uint8_t no_select;
extern uint8_t lock_all_flag;
extern void delete_file(uint8_t data);
extern void lock_flie(uint8_t file_num, uint8_t lock);
extern void exit_dec_setting_menu(void);
#if !LV_USE_GUIBUILDER_SIMULATOR
//#include "fs/fs.h"
extern int map_jpeg_disp_one_frame(u16 width, u16 height, u8 *buf, int len);
extern int map_jpeg_disp_frame_init(void);
extern void lv_example_lyrics_text_input(char *new_text);
extern int logo_show(char *logo_path, char *audio_path, int time_out, void (*func)());
static int init_flag = 1;
char *lyrics_test = "lyrics one lyrics two";
#endif

static lv_obj_t *page_map_simple_navi_view = NULL;
static int page_map_img_2_init_flag = 1;
int in_ui_navi_flag = 0; //只有ui在导航界面允许更新导航信息

int get_in_ui_navi_flag(void)
{
    return in_ui_navi_flag;
}

void set_in_ui_navi_flag(int val)
{
    in_ui_navi_flag = val;
}
#if !LV_USE_GUIBUILDER_SIMULATOR
extern int map_jpeg_disp_frame_uninit(void);
#endif
void scr_loaded_handler(lv_event_t *e)
{
    lv_obj_t *src = lv_event_get_target(e);
    gui_msg_init_ui();
    gui_msg_init_events();
}

void events_init(lv_ui *ui)
{
}

static void usb_slave_btn_usb_msd_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_add_flag(guider_ui.usb_slave->usb_slave_view_btnlist, LV_OBJ_FLAG_HIDDEN);
        //custom code usb_slave_view_btnlist
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_usb_slave *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
            lv_obj_t *dest = ui_scr->usb_slave_view_btnlist;
#if !LV_USE_GUIBUILDER_SIMULATOR
            usb_start(TCFG_USB_DEBUG_ID, MASSSTORAGE_CLASS);
#endif
        }
        lv_obj_clear_flag(guider_ui.usb_slave->usb_slave_img_icon_masstorage, LV_OBJ_FLAG_HIDDEN);
    }
    break;
    default:
        break;
    }
}

static void usb_slave_btn_pc_cam_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_add_flag(guider_ui.usb_slave->usb_slave_view_btnlist, LV_OBJ_FLAG_HIDDEN);
        //custom code usb_slave_view_btnlist
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_usb_slave *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
            lv_obj_t *dest = ui_scr->usb_slave_view_btnlist;
#if !LV_USE_GUIBUILDER_SIMULATOR
            usb_start(TCFG_USB_DEBUG_ID, UVC_CLASS | MASSSTORAGE_CLASS | CDC_CLASS);
#endif
        }
        lv_obj_clear_flag(guider_ui.usb_slave->usb_slave_img_icon_pccam, LV_OBJ_FLAG_HIDDEN);
    }
    break;
    default:
        break;
    }
}

static void usb_slave_btn_video_rec_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_REC);
        if (screen != NULL) {
            ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 3, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void usb_slave_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_PAGE_MAP);
        if (screen != NULL) {
            ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}
static void usb_slave_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_USB_SLAVE, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_USB_SLAVE, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_usb_slave(lv_ui *ui)
{
    lv_ui_usb_slave *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
    lv_obj_add_event_cb(ui_scr->usb_slave, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->usb_slave_btn_usb_msd, usb_slave_btn_usb_msd_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->usb_slave_btn_pc_cam, usb_slave_btn_pc_cam_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->usb_slave_btn_video_rec, usb_slave_btn_video_rec_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->usb_slave_btn_1, usb_slave_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->usb_slave, usb_slave_screen_event_handler, LV_EVENT_ALL, ui);
}

static void video_rec_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            printf("[chili] %s %d   \n",  __func__, __LINE__);

        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_scan_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_HOME || *key == LV_KEY_LEFT) {
            lv_obj_add_flag(guider_ui.video_rec->video_rec_view_scan, LV_OBJ_FLAG_HIDDEN);
        }
        if (*key == LV_KEY_HOME || *key == LV_KEY_LEFT) {
            //custom code video_rec_view_scan
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
                lv_obj_t *dest = ui_scr->video_rec_view_scan;
                printf(">>>>enter rec setting menu\n");
                lv_obj_clear_flag(ui_scr->video_rec_view_menu_b, LV_OBJ_FLAG_HIDDEN);  //显示录像设置菜单
                lv_group_focus_obj(ui_scr->video_rec_view_reso);  //进入设置菜单时直接聚焦到第一个设置项

#ifndef LV_USE_GUIBUILDER_SIMULATOR
                set_menu_status(1);
#endif
            }
        }
        if (*key == LV_KEY_RIGHT) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_PHOTO);
            if (screen != NULL) {
                ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_menu_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);

            //更新菜单子页面内容
            rec_subpage_data.funkey1 = 0;
            rec_subpage_data.funkey2 = 0;
            rec_subpage_data.funkey3 = 0;
            rec_subpage_data.funkey4 = 0;
            rec_subpage_data.btn_focus_id = 0;
            rec_subpage_data.roller = 0;
            rec_subpage_data.roller_opt = 0;
            rec_subpage_data.roller_sel = 0;
            rec_subpage_data.car_num_view = 0;

            switch (rec_subpage_data.now_subpage) {
            case SUBPAGE_RESOLUTION:
                rec_subpage_data.funkey2 = (void *)"720P";
                rec_subpage_data.funkey3 = (void *)"480P";
                printf(">>>res: %d\n", db_select("res"));
                switch (db_select("res")) { //处理高亮样式
                case VIDEO_RES_720P:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                }
                break;
            case SUBPAGE_DOUBLE_REC:
                rec_subpage_data.funkey2 = (void *)_("close");
                rec_subpage_data.funkey3 = (void *)_("open");
                printf(">>>two rec: %d\n", db_select("two"));
                switch (db_select("two")) { //处理高亮样式
                case 1:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;
            case SUBPAGE_CYC_REC:
                rec_subpage_data.funkey1 = (void *)_("close");
                rec_subpage_data.funkey2 = (void *)"3min";
                rec_subpage_data.funkey3 = (void *)"5min";
                rec_subpage_data.funkey4 = (void *)"10min";
                printf(">>>cyc: %d\n", db_select("cyc"));
                switch (db_select("cyc")) { //处理高亮样式
                case 3:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                case 5:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                case 10:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY4;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY1;
                    break;
                }
                break;
            case SUBPAGE_GAP:
                rec_subpage_data.funkey1 = (void *)_("close");
                rec_subpage_data.funkey2 = (void *)"100ms";
                rec_subpage_data.funkey3 = (void *)"200ms";
                rec_subpage_data.funkey4 = (void *)"500ms";
                switch (db_select("gap")) { //处理高亮样式
                case 100:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                case 200:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                case 500:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY4;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY1;
                    break;
                }
                break;
            case SUBPAGE_HDR:
                rec_subpage_data.funkey2 = (void *)_("close");
                rec_subpage_data.funkey3 = (void *)_("open");
                switch (db_select("hdr")) { //处理高亮样式
                case 1:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;
            case SUBPAGE_EXPOSURE:
                rec_subpage_data.roller_opt = (void *)"-3\n-2\n-1\n0\n1\n2\n3";
                rec_subpage_data.roller = ui_scr->video_rec_roller_mutifunc;
                switch (db_select("exp")) {
                case 0xfffffffd://-3
                    rec_subpage_data.roller_sel = 0;
                    break;
                case 0xfffffffe://-2:
                    rec_subpage_data.roller_sel = 1;
                    break;
                case 0xffffffff://-1
                    rec_subpage_data.roller_sel = 2;//
                    break;
                case 0:
                    rec_subpage_data.roller_sel = 3;
                    break;
                case 1:
                    rec_subpage_data.roller_sel = 4;
                    break;
                case 2:
                    rec_subpage_data.roller_sel = 5;//
                    break;
                case 3:
                    rec_subpage_data.roller_sel = 6;//
                    break;
                default://-3
                    rec_subpage_data.roller_sel = 3;//auto
                    break;
                }
                break;
            case SUBPAGE_MOTION:
                rec_subpage_data.funkey2 = (void *)_("close");
                rec_subpage_data.funkey3 = (void *)_("open");
                switch (db_select("mot")) { //处理高亮样式
                case 1:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                rec_ask_app_open_menu();
                break;
            case SUBPAGE_RECORD:
                rec_subpage_data.funkey2 = (void *)_("close");
                rec_subpage_data.funkey3 = (void *)_("open");
                switch (db_select("mic")) { //处理高亮样式
                case 1:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;
            case SUBPAGE_DATE:
                rec_subpage_data.funkey2 = (void *)_("close");
                rec_subpage_data.funkey3 = (void *)_("open");
                switch (db_select("dat")) { //处理高亮样式
                case 1:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;
            case SUBPAGE_GSENSOR:
                rec_subpage_data.funkey1 = (void *)_("close");
                rec_subpage_data.funkey2 = (void *)_("Lsensitive");
                rec_subpage_data.funkey3 = (void *)_("Msensitive");
                rec_subpage_data.funkey4 = (void *)_("Hsensitive");
                switch (db_select("gra")) { //处理高亮样式
                case 1:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                case 2:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                case 3:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY4;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY1;
                    break;
                }
                break;
            case SUBPAGE_GUARD:
                rec_subpage_data.funkey2 = (void *)_("close");
                rec_subpage_data.funkey3 = (void *)_("open");
                switch (db_select("par")) { //处理高亮样式
                case 1:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;
            case SUBPAGE_CARNUM:
                rec_subpage_data.funkey2 = (void *)_("close");
                rec_subpage_data.funkey3 = (void *)_("open");
                switch (db_select("num")) { //处理高亮样式
                case 1:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;
            case SUBPAGE_HAEDLAMP:
                rec_subpage_data.funkey2 = (void *)_("close");
                rec_subpage_data.funkey3 = (void *)_("open");
                switch (db_select("hlw")) { //处理高亮样式
                case 1:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;

            default:
                printf("[chili] %s %d   no match subpage!\n",  __func__, __LINE__);
                break;
            }

            subpage_show(&rec_subpage_data);

            /* 将菜单中的选项从组中移除，在按键操作子菜单时不会被聚焦 */
            lv_obj_t *menu_obj = NULL;
            uint32_t menu_cnt = lv_obj_get_child_cnt(ui_scr->video_rec_view_menu);
            printf("rec menu num: %d\n", menu_cnt);
            for (int i = 0; i < menu_cnt; i++) {
                menu_obj = lv_obj_get_child(ui_scr->video_rec_view_menu, i);
                if (menu_obj) {
                    lv_group_remove_obj(menu_obj);
                }
                menu_obj = NULL;
            }




        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_HOME || *key == LV_KEY_LEFT) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_SYS_SETTING);
            if (screen != NULL) {
                ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
            }
        }
        if (*key == LV_KEY_HOME || *key == LV_KEY_LEFT) {
            //custom code sys_setting
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
#if LV_USE_GUIBUILDER_SIMULATOR
                cur_mode = 0; //video_rec
#endif
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_reso_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_submenu;
            rec_subpage_data.now_subpage = SUBPAGE_RESOLUTION;
            rec_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_two_rec_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_submenu;
            rec_subpage_data.now_subpage = SUBPAGE_DOUBLE_REC;
            rec_subpage_data.menu_index = lv_obj_get_index(src);

        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_cyc_rec_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_submenu;
            rec_subpage_data.now_subpage = SUBPAGE_CYC_REC;
            rec_subpage_data.menu_index = lv_obj_get_index(src);

        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_gap_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_submenu;
            rec_subpage_data.now_subpage = SUBPAGE_GAP;
            rec_subpage_data.menu_index = lv_obj_get_index(src);

        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_hdr_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_submenu;
            rec_subpage_data.now_subpage = SUBPAGE_HDR;
            rec_subpage_data.menu_index = lv_obj_get_index(src);

        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_exp_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_submenu;
            rec_subpage_data.now_subpage = SUBPAGE_EXPOSURE;
            rec_subpage_data.menu_index = lv_obj_get_index(src);

        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_motd_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_submenu;
            rec_subpage_data.now_subpage = SUBPAGE_MOTION;
            rec_subpage_data.menu_index = lv_obj_get_index(src);

        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_mic_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_submenu;
            rec_subpage_data.now_subpage = SUBPAGE_RECORD;
            rec_subpage_data.menu_index = lv_obj_get_index(src);

        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_date_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_submenu;
            rec_subpage_data.now_subpage = SUBPAGE_DATE;
            rec_subpage_data.menu_index = lv_obj_get_index(src);

        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_gra_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_submenu;
            rec_subpage_data.now_subpage = SUBPAGE_GSENSOR;
            rec_subpage_data.menu_index = lv_obj_get_index(src);

        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_par_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_submenu;
            rec_subpage_data.now_subpage = SUBPAGE_GUARD;
            rec_subpage_data.menu_index = lv_obj_get_index(src);

        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_num_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_submenu;
            rec_subpage_data.now_subpage = SUBPAGE_CARNUM;
            rec_subpage_data.menu_index = lv_obj_get_index(src);

        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_hlw_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_submenu;
            rec_subpage_data.now_subpage = SUBPAGE_HAEDLAMP;
            rec_subpage_data.menu_index = lv_obj_get_index(src);

        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_submenu_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_add_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_submenu;
            printf(">>>>return rec menu\n");
            int flag = 0;
            unsigned char *carnumber_cn =  lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER, 16);//车牌

            //更新菜单设置项
            switch (rec_subpage_data.now_subpage) {
            case SUBPAGE_RESOLUTION:
                printf(">>> reso cur_btn: %d\n", subpage_cur_btn);
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("res", 1);//单位P
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("res", 2);//单位P
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                break;
            case SUBPAGE_DOUBLE_REC:
                printf(">>> two rec cur_btn: %d\n", subpage_cur_btn);
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("two", 0);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("two", 1);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                break;
            case SUBPAGE_CYC_REC:
                printf(">>> cyc rec cur_btn: %d\n", subpage_cur_btn);
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("cyc", 3);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("cyc", 5);
                    break;
                case SUBPAGE_FUNKEY4:
                    db_update("cyc", 10);
                    break;
                default:
                    db_update("cyc", 0);
                    break;
                }
                break;
            case SUBPAGE_GAP:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("gap", 100);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("gap", 200);
                    break;
                case SUBPAGE_FUNKEY4:
                    db_update("gap", 500);
                    break;
                default:
                    db_update("gap", 0);
                    break;
                }
                break;
            case SUBPAGE_HDR:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("hdr", 0);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("hdr", 1);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                break;
            case SUBPAGE_EXPOSURE:
                lv_roller_get_selected_str(ui_scr->video_rec_roller_mutifunc, user_roller_str, 16);
                printf("[chili] %s %d YES \n",  __func__, __LINE__);
                switch (lv_roller_get_selected(ui_scr->video_rec_roller_mutifunc)) {
                case 0:
                    db_update("exp", -3);
                    break;
                case 1:
                    db_update("exp", -2);
                    break;
                case 2:
                    db_update("exp", -1);
                    break;
                case 3:
                    db_update("exp", 0);
                    break;
                case 4:
                    db_update("exp", 1);
                    break;
                case 5:
                    db_update("exp", 2);
                    break;
                case 6:
                    db_update("exp", 3);
                    break;
                default:
                    db_update("exp", 0);
                    break;
                }
                break;
            case SUBPAGE_MOTION:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("mot", 0);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("mot", 1);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                break;
            case SUBPAGE_RECORD:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("mic", 0);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("mic", 1);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                break;
            case SUBPAGE_DATE:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("dat", 0);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("dat", 1);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                video_rec_config_init();
                break;
            case SUBPAGE_GSENSOR:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY1:
                    db_update("gra", 0);
                    break;
                case SUBPAGE_FUNKEY2:
                    db_update("gra", 1);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("gra", 2);
                    break;
                case SUBPAGE_FUNKEY4:
                    db_update("gra", 3);
                    break;
                default:
                    db_update("gra", 2);
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                video_rec_config_init();
                break;
            case SUBPAGE_GUARD:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("par", 0);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("par", 1);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                break;
            case SUBPAGE_CARNUM:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("num", 0);
                    break;
                case SUBPAGE_FUNKEY3: {
                    printf("enter SUBPAGE_CARNUM SUBPAGE_FUNKEY3\n");
                    flag = 1;
                    db_update("num", 1);
                    rec_subpage_data.funkey1 = 0;
                    rec_subpage_data.funkey2 = 0;
                    rec_subpage_data.funkey3 = 0;
                    rec_subpage_data.btn_focus_id = 0;
                    rec_subpage_data.roller_opt = 0;
                    rec_subpage_data.roller = 0;
                    rec_subpage_data.roller_sel = 0;
                    rec_subpage_data.funkey4 = (void *)_("YES");
                    rec_subpage_data.car_num_view = (void *)"carnum";
                    lv_obj_clear_flag(ui_scr->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
                    subpage_show(&rec_subpage_data);
                }
                break;
                case SUBPAGE_FUNKEY4: {
                    printf("enter SUBPAGE_CARNUM SUBPAGE_FUNKEY4\n");
                    lv_dropdown_get_selected_str(ui_scr->video_rec_ddlist_1, carnumber_cn, 4);
                    lv_dropdown_get_selected_str(ui_scr->video_rec_ddlist_2, &carnumber_cn[3], 2);
                    lv_dropdown_get_selected_str(ui_scr->video_rec_ddlist_3, &carnumber_cn[4], 2);
                    lv_dropdown_get_selected_str(ui_scr->video_rec_ddlist_4, &carnumber_cn[5], 2);
                    lv_dropdown_get_selected_str(ui_scr->video_rec_ddlist_5, &carnumber_cn[6], 2);
                    lv_dropdown_get_selected_str(ui_scr->video_rec_ddlist_6, &carnumber_cn[7], 2);
                    lv_dropdown_get_selected_str(ui_scr->video_rec_ddlist_7, &carnumber_cn[8], 2);
                    printf("[chili] %s carnumber_cn:%s   \n", __func__, carnumber_cn);
                    int  selected_idx = lv_dropdown_get_selected(ui_scr->video_rec_ddlist_1);
                    db_update("proc", selected_idx);
                    unsigned char gb2312Data[16] = {0};
                    carnum_utf8_to_gb2312((uint8_t *)carnumber_cn, (uint8_t *)gb2312Data, selected_idx);
                    uint32_t *carnum_p = gb2312Data;
                    db_update("cna", carnum_p[0]);
                    db_update("cnb", carnum_p[1]);
                    lvgl_module_msg_send_ptr(carnumber_cn, 0);
                    // printf("p0: %x, p1: %x, p2: %x\n", );
                }
                break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                video_rec_config_init();
                break;
            case SUBPAGE_HAEDLAMP:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("hlw", 0);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("hlw", 1);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                break;

            default:
                printf("[chili] %s %d   no match subpage!\n",  __func__, __LINE__);
                break;
            }

            if (flag) {
                return;
            }


            //更新状态图标
            video_rec_icon_reshow(rec_subpage_data.now_subpage);//更新预览界面图标


            //添加菜单设置项到组内，因为在进入子菜单时从组内移出了
            lv_obj_t *menu_obj = NULL;
            uint32_t menu_cnt = lv_obj_get_child_cnt(ui_scr->video_rec_view_menu);
            for (int i = 0; i < menu_cnt; i++) {
                menu_obj = lv_obj_get_child(ui_scr->video_rec_view_menu, i);
                if (menu_obj) {
                    lv_group_add_obj(lv_group_get_default(), menu_obj);
                }
                menu_obj = NULL;
            }



            /* 返回一级菜单时聚焦回原来进入二级菜单时的选项 */
            menu_obj = lv_obj_get_child(ui_scr->video_rec_view_menu, rec_subpage_data.menu_index);
            if (menu_obj) {
                lv_group_focus_obj(menu_obj);
            }
            rec_subpage_data.menu_index = 0;


        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_LEFT || *key == LV_KEY_HOME) {
            lv_obj_add_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        }
        if (*key == LV_KEY_LEFT || *key == LV_KEY_HOME) {
            //custom code video_rec_view_submenu
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
                lv_obj_t *dest = ui_scr->video_rec_view_submenu;
                //添加菜单设置项到组内，因为在进入子菜单时从组内移出了
                lv_obj_t *menu_obj = NULL;
                uint32_t menu_cnt = lv_obj_get_child_cnt(ui_scr->video_rec_view_menu);
                for (int i = 0; i < menu_cnt; i++) {
                    menu_obj = lv_obj_get_child(ui_scr->video_rec_view_menu, i);
                    if (menu_obj) {
                        lv_group_add_obj(lv_group_get_default(), menu_obj);
                    }
                    menu_obj = NULL;
                }

                /* 返回一级菜单时聚焦回原来进入二级菜单时的选项 */
                menu_obj = lv_obj_get_child(ui_scr->video_rec_view_menu, rec_subpage_data.menu_index);
                if (menu_obj) {
                    lv_group_focus_obj(menu_obj);
                }
                rec_subpage_data.menu_index = 0;
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_rec_submenu_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            printf("enter rec submenu btn1\n");
            subpage_cur_btn = SUBPAGE_FUNKEY1;//记录下被按下的keyfun键值
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_rec_submenu_btn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            printf("enter rec submenu btn2\n");
            subpage_cur_btn = SUBPAGE_FUNKEY2;//记录下被按下的keyfun键值
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_rec_submenu_btn_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            printf("enter rec submenu btn3\n");
            subpage_cur_btn = SUBPAGE_FUNKEY3;//记录下被按下的keyfun键值
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_rec_submenu_btn_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            printf("enter rec submenu btn4\n");
            subpage_cur_btn = SUBPAGE_FUNKEY4;//记录下被按下的keyfun键值
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_carnum_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_group_focus_next(lv_group_get_default());
        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_HOME || *key == LV_KEY_LEFT || *key == LV_KEY_RIGHT) {
            lv_obj_add_flag(guider_ui.video_rec->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
        }
        if (*key == LV_KEY_HOME || *key == LV_KEY_LEFT || *key == LV_KEY_RIGHT) {
            //custom code video_rec_view_submenu
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
                lv_obj_t *dest = ui_scr->video_rec_view_submenu;
                //添加菜单设置项到组内，因为在进入子菜单时从组内移出了
                lv_obj_t *menu_obj = NULL;
                uint32_t menu_cnt = lv_obj_get_child_cnt(ui_scr->video_rec_view_menu);
                for (int i = 0; i < menu_cnt; i++) {
                    menu_obj = lv_obj_get_child(ui_scr->video_rec_view_menu, i);
                    if (menu_obj) {
                        lv_group_add_obj(lv_group_get_default(), menu_obj);
                    }
                    menu_obj = NULL;
                }

                /* 返回一级菜单时聚焦回原来进入二级菜单时的选项 */
                menu_obj = lv_obj_get_child(ui_scr->video_rec_view_menu, rec_subpage_data.menu_index);
                if (menu_obj) {
                    lv_group_focus_obj(menu_obj);
                }
                rec_subpage_data.menu_index = 0;
            }
        }
    }
    break;
    default:
        break;
    }
}
static void video_rec_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_REC, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_REC, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_video_rec(lv_ui *ui)
{
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_add_event_cb(ui_scr->video_rec, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->video_rec, video_rec_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_scan, video_rec_view_scan_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_menu, video_rec_view_menu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_reso, video_rec_view_reso_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_two_rec, video_rec_view_two_rec_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_cyc_rec, video_rec_view_cyc_rec_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_gap, video_rec_view_gap_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_hdr, video_rec_view_hdr_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_exp, video_rec_view_exp_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_motd, video_rec_view_motd_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_mic, video_rec_view_mic_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_date, video_rec_view_date_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_gra, video_rec_view_gra_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_par, video_rec_view_par_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_num, video_rec_view_num_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_hlw, video_rec_view_hlw_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_submenu, video_rec_view_submenu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_rec_submenu_btn_1, video_rec_rec_submenu_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_rec_submenu_btn_2, video_rec_rec_submenu_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_rec_submenu_btn_3, video_rec_rec_submenu_btn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_rec_submenu_btn_4, video_rec_rec_submenu_btn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_carnum, video_rec_view_carnum_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec, video_rec_screen_event_handler, LV_EVENT_ALL, ui);
}

static void sys_prompt_img_warn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code sys_prompt
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_PROMPT);
            lv_obj_t *dest = ui_scr->sys_prompt;
            extern lv_timer_t *prompt_timer;
            if (prompt_timer) {
                lv_timer_del(prompt_timer);
                prompt_timer = NULL;
            }
            if (ui_scr->sys_prompt_del == false && lv_obj_is_valid(ui_scr->sys_prompt)) {
                lv_obj_add_flag(ui_scr->sys_prompt, LV_OBJ_FLAG_HIDDEN);
                unload_scr_sys_prompt(&guider_ui);
            }

        }
    }
    break;
    default:
        break;
    }
}

void events_init_sys_prompt(lv_ui *ui)
{
    lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_PROMPT);
    lv_obj_add_event_cb(ui_scr->sys_prompt, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->sys_prompt_img_warn, sys_prompt_img_warn_event_handler, LV_EVENT_ALL, ui);
}

static void sys_setting_view_menu_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            //更新菜单子页面内容
            my_sysmenu_subpage.funkey1 = 0;
            my_sysmenu_subpage.funkey2 = 0;
            my_sysmenu_subpage.funkey3 = 0;
            my_sysmenu_subpage.funkey4 = 0;
            my_sysmenu_subpage.btn_focus_id = 0;
            my_sysmenu_subpage.time_num_view = 0;
            my_sysmenu_subpage.warning = 0;
            my_sysmenu_subpage.roller_opt = 0;
            my_sysmenu_subpage.roller = 0;
            my_sysmenu_subpage.roller_sel = 0;

            switch (my_sysmenu_subpage.now_subpage) {
            case SUBPAGE_SAVER:
                my_sysmenu_subpage.funkey1 = (void *)_("close");
                my_sysmenu_subpage.funkey2 = (void *)"30s";
                my_sysmenu_subpage.funkey3 = (void *)"60s";
                my_sysmenu_subpage.funkey4 = (void *)"120s";
                printf(">>>sys pro value: %d\n", db_select("pro"));
                switch (db_select("pro")) {
                case 30:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                case 60:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                case 120:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY4;
                    break;
                default:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY1;
                    break;
                }
                break;
            case SUBPAGE_POWEROFF:
                my_sysmenu_subpage.funkey1 = (void *)_("close");
                my_sysmenu_subpage.funkey2 = (void *)"3min";
                my_sysmenu_subpage.funkey3 = (void *)"5min";
                my_sysmenu_subpage.funkey4 = (void *)"10min";
                printf(">>>sys aff value: %d\n", db_select("aff"));
                switch (db_select("aff")) {
                case 3:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                case 5:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                case 10:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY4;
                    break;
                default:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY1;
                    break;
                }
                break;
            case SUBPAGE_FREQ:
                my_sysmenu_subpage.funkey2 = (void *)"50Hz";
                my_sysmenu_subpage.funkey3 = (void *)"60Hz";
                printf(">>>sys fre value: %d\n", db_select("fre"));
                switch (db_select("fre")) {
                case 50:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                case 60:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;
            case SUBPAGE_VOLUME:
                my_sysmenu_subpage.funkey2 = (void *)_("close");
                my_sysmenu_subpage.funkey3 = (void *)_("open");
                printf(">>>sys kvo value: %d\n", db_select("kvo"));
                switch (db_select("kvo")) {
                case 1:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;
            case SUBPAGE_LANGUAGE: {
                char buf[128];
                sprintf(buf, "%s\n%s", _("chinese_simplified"), "English");
                my_sysmenu_subpage.roller_opt = (void *)buf;
                my_sysmenu_subpage.roller = ui_scr->sys_setting_roller_mutifunc;
                printf(">>>sys lag value: %d\n", db_select("lag"));
                switch (db_select("lag")) {
                case LANG_ENGLISH:
                    my_sysmenu_subpage.roller_sel = 1;
                    break;
                default:
                    my_sysmenu_subpage.roller_sel = 0;
                    break;
                }
            }
            break;
            case SUBPAGE_DATA:
                my_sysmenu_subpage.time_num_view = (void *)"time";
                my_sysmenu_subpage.funkey4 = (void *)_("YES");
                break;
            case SUBPAGE_TVSYSTEM:
                my_sysmenu_subpage.funkey2 = (void *)"PAL";
                my_sysmenu_subpage.funkey3 = (void *)"NTSC";
                printf(">>>sys tvm value: %d\n", db_select("tvm"));
                switch (db_select("tvm")) {
                case 1:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;
            case SUBPAGE_FORMATTING:
                my_sysmenu_subpage.warning = (void *)_("format_warning");
                my_sysmenu_subpage.funkey3 = (void *)_("CANCEL");
                my_sysmenu_subpage.funkey4 = (void *)_("YES");
                my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY3;
                break;
            case SUBPAGE_RESET:
                my_sysmenu_subpage.warning = (void *)_("reset_warning");
                my_sysmenu_subpage.funkey3 = (void *)_("CANCEL");
                my_sysmenu_subpage.funkey4 = (void *)_("YES");
                my_sysmenu_subpage.btn_focus_id = SUBPAGE_FUNKEY3;
                break;
            case SUBPAGE_VERSION:
                my_sysmenu_subpage.warning = (void *)"\n\nVersion: JL V1.0.0";
                break;


            default:
                printf("[chili] %s %d   no match subpage!\n",  __func__, __LINE__);
                break;
            }

            sysmenu_subpage_show(&my_sysmenu_subpage);


            //将菜单中的选项从组中移除，在按键操作子菜单时不会被聚焦
            lv_obj_t *menu_obj = NULL;
            uint32_t menu_cnt = lv_obj_get_child_cnt(ui_scr->sys_setting_view_menu);
            printf("setting menu num: %d\n", menu_cnt);
            for (int i = 0; i < menu_cnt; i++) {
                menu_obj = lv_obj_get_child(ui_scr->sys_setting_view_menu, i);
                if (menu_obj) {
                    lv_group_remove_obj(menu_obj);
                }
                menu_obj = NULL;
            }




        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_HOME || *key == LV_KEY_LEFT) {
            //custom code
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
                printf(">>>exit sysmenu\n");
#ifndef LV_USE_GUIBUILDER_SIMULATOR
                exit_sys_setting_menu();
                set_menu_status(0);
#else

                if (cur_mode == 0) {
                    gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_REC);
                    if (screen == NULL) {
                        screen = gui_scr_create(GUI_SCREEN_VIDEO_REC, "video_rec", guider_ui.video_rec, (gui_scr_setup_cb_t)setup_scr_video_rec, (gui_scr_unload_cb_t)unload_scr_video_rec);
                    }
                    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
                } else if (cur_mode == 1) {
                    gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_PHOTO);
                    if (screen == NULL) {
                        screen = gui_scr_create(GUI_SCREEN_VIDEO_PHOTO, "video_photo", guider_ui.video_photo, (gui_scr_setup_cb_t)setup_scr_video_photo, (gui_scr_unload_cb_t)unload_scr_video_photo);
                    }
                    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
                }

#endif
            }
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_view_pro_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.sys_setting->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code sys_setting_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_view_submenu;
            my_sysmenu_subpage.now_subpage = SUBPAGE_SAVER;
            my_sysmenu_subpage.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_view_autof_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.sys_setting->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code sys_setting_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_view_submenu;
            my_sysmenu_subpage.now_subpage = SUBPAGE_POWEROFF;
            my_sysmenu_subpage.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_view_hz_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.sys_setting->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code sys_setting_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_view_submenu;
            my_sysmenu_subpage.now_subpage = SUBPAGE_FREQ;
            my_sysmenu_subpage.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_view_kvo_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.sys_setting->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code sys_setting_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_view_submenu;
            my_sysmenu_subpage.now_subpage = SUBPAGE_VOLUME;
            my_sysmenu_subpage.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_view_lag_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.sys_setting->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code sys_setting_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_view_submenu;
            my_sysmenu_subpage.now_subpage = SUBPAGE_LANGUAGE;
            my_sysmenu_subpage.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_view_time_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.sys_setting->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code sys_setting_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_view_submenu;
            my_sysmenu_subpage.now_subpage = SUBPAGE_DATA;
            my_sysmenu_subpage.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_view_tv_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.sys_setting->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code sys_setting_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_view_submenu;
            my_sysmenu_subpage.now_subpage = SUBPAGE_TVSYSTEM;
            my_sysmenu_subpage.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_view_format_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.sys_setting->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code sys_setting_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_view_submenu;
            my_sysmenu_subpage.now_subpage = SUBPAGE_FORMATTING;
            my_sysmenu_subpage.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_view_reset_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.sys_setting->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code sys_setting_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_view_submenu;
            my_sysmenu_subpage.now_subpage = SUBPAGE_RESET;
            my_sysmenu_subpage.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_view_ver_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.sys_setting->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code sys_setting_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_view_submenu;
            my_sysmenu_subpage.now_subpage = SUBPAGE_VERSION;
            my_sysmenu_subpage.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_view_submenu_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_add_flag(guider_ui.sys_setting->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code sys_setting_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_view_submenu;

            int format_err;
            char time_buf[8] = {0};

            //更新菜单设置项
            switch (my_sysmenu_subpage.now_subpage) {
            case SUBPAGE_SAVER:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("pro", 30);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("pro", 60);
                    break;
                case SUBPAGE_FUNKEY4:
                    db_update("pro", 120);
                    break;
                default:
                    db_update("pro", 0);
                    break;
                }
                ui_lcd_light_time_set(db_select("pro"));
                break;
            case SUBPAGE_POWEROFF:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("aff", 3);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("aff", 5);
                    break;
                case SUBPAGE_FUNKEY4:
                    db_update("aff", 10);
                    break;
                default:
                    db_update("aff", 0);
                    break;
                }
                aff_set_function(db_select("aff"));
                break;
            case SUBPAGE_FREQ:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY3:
                    db_update("fre", 60);
                    break;
                default:
                    db_update("fre", 50);
                    break;
                }
                break;
            case SUBPAGE_VOLUME:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY3:
                    db_update("kvo", 1);
                    break;
                default:
                    db_update("kvo", 0);
                    break;
                }
                break;
            case SUBPAGE_LANGUAGE:
                lv_roller_get_selected_str(ui_scr->sys_setting_roller_mutifunc, user_roller_str, 16);
                switch (lv_roller_get_selected(ui_scr->sys_setting_roller_mutifunc)) {
                case 0:
                    db_update("lag", LANG_CHINESE_SIMP);
                    lv_i18n_set_locale("zh_cn");
                    break;
                case 1:
                    db_update("lag", LANG_ENGLISH);
                    lv_i18n_set_locale("en");
                    break;
                default:
                    db_update("lag", LANG_CHINESE_SIMP);
                    lv_i18n_set_locale("zh_cn");
                    break;
                }
                i18n_refresh_all_texts();
                break;
            case SUBPAGE_DATA:
                printf(">>>set rtc time\n");
                lv_dropdown_get_selected_str(ui_scr->sys_setting_ddlist_year, &time_buf, 5);
                printf("year: %s\n", time_buf);
                db_update("datey", atoi(time_buf));
                memset(time_buf, 0, sizeof(time_buf));
                lv_dropdown_get_selected_str(ui_scr->sys_setting_ddlist_month, &time_buf, 3);
                printf("month: %s\n", time_buf);
                db_update("datem", atoi(time_buf));
                memset(time_buf, 0, sizeof(time_buf));
                lv_dropdown_get_selected_str(ui_scr->sys_setting_ddlist_day, &time_buf, 3);
                printf("day: %s\n", time_buf);
                db_update("dated", atoi(time_buf));
                memset(time_buf, 0, sizeof(time_buf));
                lv_dropdown_get_selected_str(ui_scr->sys_setting_ddlist_hour, &time_buf, 3);
                printf("hour: %s\n", time_buf);
                db_update("dateh", atoi(time_buf));
                memset(time_buf, 0, sizeof(time_buf));
                lv_dropdown_get_selected_str(ui_scr->sys_setting_ddlist_min, &time_buf, 3);
                printf("min: %s\n", time_buf);
                db_update("datemi", atoi(time_buf));
                memset(time_buf, 0, sizeof(time_buf));
                lv_dropdown_get_selected_str(ui_scr->sys_setting_ddlist_sec, &time_buf, 3);
                printf("sec: %s\n", time_buf);
                db_update("dates", atoi(time_buf));

                update_date = true;
                break;
            case SUBPAGE_TVSYSTEM:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY3:
                    db_update("tvm", 1);
                    break;
                default:
                    db_update("tvm", 0);
                    break;
                }
                break;
            case SUBPAGE_FORMATTING:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY4:
                    printf("format sdcard...\n");
                    format_sdcard();
                    break;
                default:
                    break;
                }
                break;
            case SUBPAGE_RESET:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY4:
                    printf("restore default...\n");
                    setting_reset();
                    break;
                default:
                    break;
                }
                break;
            case SUBPAGE_VERSION:

                break;


            default:
                printf("[chili] %s %d   no match subpage!\n",  __func__, __LINE__);
                break;
            }


            //更新状态图标


            //添加菜单设置项到组内，因为在进入子菜单时从组内移出了
            lv_obj_t *menu_obj = NULL;
            uint32_t menu_cnt = lv_obj_get_child_cnt(ui_scr->sys_setting_view_menu);
            printf("rec menu num: %d\n", menu_cnt);
            for (int i = 0; i < menu_cnt; i++) {
                menu_obj = lv_obj_get_child(ui_scr->sys_setting_view_menu, i);
                if (menu_obj) {
                    lv_group_add_obj(lv_group_get_default(), menu_obj);
                }
                menu_obj = NULL;
            }

            /* 返回一级菜单时聚焦回原来进入二级菜单时的选项 */
            menu_obj = lv_obj_get_child(ui_scr->sys_setting_view_menu, my_sysmenu_subpage.menu_index);
            if (menu_obj) {
                lv_group_focus_obj(menu_obj);
            }
            my_sysmenu_subpage.menu_index = 0;



        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_LEFT || *key == LV_KEY_HOME) {
            lv_obj_add_flag(guider_ui.sys_setting->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
        }
        if (*key == LV_KEY_LEFT || *key == LV_KEY_HOME) {
            //custom code sys_setting_view_submenu
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
                lv_obj_t *dest = ui_scr->sys_setting_view_submenu;
                //添加菜单设置项到组内，因为在进入子菜单时从组内移出了
                lv_obj_t *menu_obj = NULL;
                uint32_t menu_cnt = lv_obj_get_child_cnt(ui_scr->sys_setting_view_menu);
                printf("rec menu num: %d\n", menu_cnt);
                for (int i = 0; i < menu_cnt; i++) {
                    menu_obj = lv_obj_get_child(ui_scr->sys_setting_view_menu, i);
                    if (menu_obj) {
                        lv_group_add_obj(lv_group_get_default(), menu_obj);
                    }
                    menu_obj = NULL;
                }

                /* 返回一级菜单时聚焦回原来进入二级菜单时的选项 */
                menu_obj = lv_obj_get_child(ui_scr->sys_setting_view_menu, my_sysmenu_subpage.menu_index);
                if (menu_obj) {
                    lv_group_focus_obj(menu_obj);
                }
                my_sysmenu_subpage.menu_index = 0;

            }
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_submenu_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            subpage_cur_btn = SUBPAGE_FUNKEY1;//记录下被按下的keyfun键值
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_submenu_btn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            subpage_cur_btn = SUBPAGE_FUNKEY2;
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_submenu_btn_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            subpage_cur_btn = SUBPAGE_FUNKEY3;
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_submenu_btn_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            subpage_cur_btn = SUBPAGE_FUNKEY4;
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_view_time_mun_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_group_focus_next(lv_group_get_default());
        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_LEFT || *key == LV_KEY_HOME || *key == LV_KEY_RIGHT) {
            lv_obj_add_flag(guider_ui.sys_setting->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
        }
        if (*key == LV_KEY_LEFT || *key == LV_KEY_HOME || *key == LV_KEY_RIGHT) {
            //custom code sys_setting_view_submenu
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
                lv_obj_t *dest = ui_scr->sys_setting_view_submenu;
                //添加菜单设置项到组内，因为在进入子菜单时从组内移出了
                lv_obj_t *menu_obj = NULL;
                uint32_t menu_cnt = lv_obj_get_child_cnt(ui_scr->sys_setting_view_menu);
                printf("rec menu num: %d\n", menu_cnt);
                for (int i = 0; i < menu_cnt; i++) {
                    menu_obj = lv_obj_get_child(ui_scr->sys_setting_view_menu, i);
                    if (menu_obj) {
                        lv_group_add_obj(lv_group_get_default(), menu_obj);
                    }
                    menu_obj = NULL;
                }

                /* 返回一级菜单时聚焦回原来进入二级菜单时的选项 */
                menu_obj = lv_obj_get_child(ui_scr->sys_setting_view_menu, my_sysmenu_subpage.menu_index);
                if (menu_obj) {
                    lv_group_focus_obj(menu_obj);
                }
                my_sysmenu_subpage.menu_index = 0;
            }
        }
    }
    break;
    default:
        break;
    }
}
static void sys_setting_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_SYS_SETTING, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_SYS_SETTING, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_sys_setting(lv_ui *ui)
{
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_add_event_cb(ui_scr->sys_setting, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_menu, sys_setting_view_menu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_pro, sys_setting_view_pro_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_autof, sys_setting_view_autof_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_hz, sys_setting_view_hz_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_kvo, sys_setting_view_kvo_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_lag, sys_setting_view_lag_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_time, sys_setting_view_time_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_tv, sys_setting_view_tv_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_format, sys_setting_view_format_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_reset, sys_setting_view_reset_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_ver, sys_setting_view_ver_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_submenu, sys_setting_view_submenu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_submenu_btn_1, sys_setting_submenu_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_submenu_btn_2, sys_setting_submenu_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_submenu_btn_3, sys_setting_submenu_btn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_submenu_btn_4, sys_setting_submenu_btn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_time_mun, sys_setting_view_time_mun_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting, sys_setting_screen_event_handler, LV_EVENT_ALL, ui);
}

static void video_photo_view_scan_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_RIGHT) {
            //custom code
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
#if !LV_USE_GUIBUILDER_SIMULATOR
                extern void gui_switch_video_dec_page(void);
                gui_switch_video_dec_page();
#endif /* LV_USE_GUIBUILDER_SIMULATOR */

            }
        }
        if (*key == LV_KEY_HOME || *key == LV_KEY_LEFT) {
            lv_obj_add_flag(guider_ui.video_photo->video_photo_view_scan, LV_OBJ_FLAG_HIDDEN);
        }
        if (*key == LV_KEY_HOME || *key == LV_KEY_LEFT) {
            //custom code video_photo_view_scan
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
                lv_obj_t *dest = ui_scr->video_photo_view_scan;
                lv_obj_clear_flag(ui_scr->video_photo_view_menu_b, LV_OBJ_FLAG_HIDDEN);  //显示录像设置菜单
                lv_group_focus_obj(ui_scr->video_photo_view_phm);  //进入设置菜单时直接聚焦到第一个设置项

#ifndef LV_USE_GUIBUILDER_SIMULATOR
                set_menu_status(1);
#endif
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_menu_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            photo_subpage_data.funkey1 = 0;
            photo_subpage_data.funkey2 = 0;
            photo_subpage_data.funkey3 = 0;
            photo_subpage_data.funkey4 = 0;
            photo_subpage_data.roller_opt = 0;
            photo_subpage_data.roller = 0;
            photo_subpage_data.roller_sel = 0;
            photo_subpage_data.btn_focus_id = 0;
            memset(user_roller_str, 0, sizeof(user_roller_str));

            switch (photo_subpage_data.now_subpage) {
            case SUBPAGE_SHOOT:
                photo_subpage_data.funkey1 = (void *)_("nodealy");
                photo_subpage_data.funkey2 = (void *)_("dealy2s");
                photo_subpage_data.funkey3 = (void *)_("dealy5s");
                photo_subpage_data.funkey4 = (void *)_("dealy10s");
                switch (db_select("phm")) {
                case 2:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                case 5:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                case 10:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY4;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY1;
                    break;
                }
                break;
            case SUBPAGE_RESOLUTION:
                photo_subpage_data.roller_opt = (void *)"VGA\n1M\n2M\n3M\n5M\n8M\n10M";
                photo_subpage_data.roller = ui_scr->video_photo_roller_mutifunc;
                switch (db_select("pres")) {
                case PHOTO_RES_1M:
                    photo_subpage_data.roller_sel = 1;
                    break;
                case PHOTO_RES_2M:
                    photo_subpage_data.roller_sel = 2;
                    break;
                case PHOTO_RES_3M:
                    photo_subpage_data.roller_sel = 3;
                    break;
                case PHOTO_RES_5M:
                    photo_subpage_data.roller_sel = 4;
                    break;
                case PHOTO_RES_8M:
                    photo_subpage_data.roller_sel = 5;
                    break;
                case PHOTO_RES_10M:
                    photo_subpage_data.roller_sel = 6;
                    break;
                default:
                    photo_subpage_data.roller_sel = 0;//vga
                    break;
                }
                break;
            case SUBPAGE_SHOTS:
                photo_subpage_data.funkey2 = (void *)_("close");
                photo_subpage_data.funkey3 = (void *)_("open");
                switch (db_select("cyt")) {
                case 1:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;
            case SUBPAGE_QUALITY:
                photo_subpage_data.funkey1 = (void *)_("pool");
                photo_subpage_data.funkey2 = (void *)_("standard");
                photo_subpage_data.funkey3 = (void *)_("high");
                switch (db_select("qua")) {
                case 0:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY1;
                    break;
                case 1:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                case 2:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                }
                break;
            case SUBPAGE_SHARPNESS:
                photo_subpage_data.funkey1 = (void *)_("strong");
                photo_subpage_data.funkey2 = (void *)_("standard");
                photo_subpage_data.funkey3 = (void *)_("soft");
                switch (db_select("acu")) {
                case 0:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                case 1:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                case 2:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY1;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;
            case SUBPAGE_AWB:
                sprintf(user_roller_str, "%s\n%s\n%s\n%s\n%s", _("auto"), _("sunshine"), _("cloudy"), _("tung"), _("fluolamp"));
                photo_subpage_data.roller_opt = (void *)user_roller_str;
                photo_subpage_data.roller = ui_scr->video_photo_roller_mutifunc;
                photo_subpage_data.roller_sel = db_select("wbl");
                break;
            case SUBPAGE_COLOR:
                photo_subpage_data.funkey1 = (void *)_("normal");
                photo_subpage_data.funkey2 = (void *)_("mono");
                photo_subpage_data.funkey3 = (void *)_("Nostalgia");
                switch (db_select("col")) {
                case 0:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY1;
                    break;
                case 1:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                case 2:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY1;
                    break;
                }
                break;
            case SUBPAGE_ISO:
                sprintf(user_roller_str, "%s\n%s\n%s\n%s", _("auto"), "100", "200", "400");
                photo_subpage_data.roller_opt = (void *)user_roller_str;
                photo_subpage_data.roller = ui_scr->video_photo_roller_mutifunc;
                switch (db_select("iso")) {
                case 100:
                    photo_subpage_data.roller_sel = 1;
                    break;
                case 200:
                    photo_subpage_data.roller_sel = 2;
                    break;
                case 400:
                    photo_subpage_data.roller_sel = 3;
                    break;
                default:
                    photo_subpage_data.roller_sel = 0; //auto
                    break;
                }
                break;
            case SUBPAGE_EXPOSURE:
                photo_subpage_data.roller_opt = (void *)"-3\n-2\n-1\n0\n1\n2\n3";
                photo_subpage_data.roller = ui_scr->video_photo_roller_mutifunc;
                switch (db_select("pexp")) {
                case 0xfffffffd://-3
                    photo_subpage_data.roller_sel = 0;
                    break;
                case 0xfffffffe://-2:
                    photo_subpage_data.roller_sel = 1;
                    break;
                case 0xffffffff://-1
                    photo_subpage_data.roller_sel = 2;
                    break;
                case 0:
                    photo_subpage_data.roller_sel = 3;
                    break;
                case 1:
                    photo_subpage_data.roller_sel = 4;
                    break;
                case 2:
                    photo_subpage_data.roller_sel = 5;
                    break;
                case 3:
                    photo_subpage_data.roller_sel = 6;
                    break;
                default://0
                    photo_subpage_data.roller_sel = 3;
                    break;
                }
                break;
            case SUBPAGE_HANDSHAKE:
                photo_subpage_data.funkey2 = (void *)_("close");
                photo_subpage_data.funkey3 = (void *)_("open");
                switch (db_select("sok")) {
                case 1:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;
            case SUBPAGE_PREVIEW:
                photo_subpage_data.funkey1 = (void *)_("close");
                photo_subpage_data.funkey2 = (void *)"2s";
                photo_subpage_data.funkey3 = (void *)"5s";
                switch (db_select("sca")) {
                case 2:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                case 5:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY1;
                    break;
                }
                break;
            case SUBPAGE_DATE:
                photo_subpage_data.funkey2 = (void *)_("close");
                photo_subpage_data.funkey3 = (void *)_("open");
                switch (db_select("pdat")) {
                case 1:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;

            default:
                break;
            }

            photo_submenu_update(&photo_subpage_data);

            lv_obj_t *menu_obj = NULL;
            uint32_t menu_cnt = lv_obj_get_child_cnt(ui_scr->video_photo_view_menu);
            for (int i = 0; i < menu_cnt; i++) {
                menu_obj = lv_obj_get_child(ui_scr->video_photo_view_menu, i);
                if (menu_obj) {
                    lv_group_remove_obj(menu_obj);
                }
                menu_obj = NULL;
            }
        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_HOME || *key == LV_KEY_LEFT) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_SYS_SETTING);
            if (screen != NULL) {
                ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
            }
        }
        if (*key == LV_KEY_HOME || *key == LV_KEY_LEFT) {
            //custom code sys_setting
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
#if LV_USE_GUIBUILDER_SIMULATOR
                cur_mode = 1; //video_photo
#endif
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_phm_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_photo->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_submenu;
            photo_subpage_data.now_subpage = SUBPAGE_SHOOT;
            photo_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_reso_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_photo->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_submenu;
            photo_subpage_data.now_subpage = SUBPAGE_RESOLUTION;
            photo_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_cyt_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_photo->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_submenu;
            photo_subpage_data.now_subpage = SUBPAGE_SHOTS;
            photo_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_qua_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_photo->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_submenu;
            photo_subpage_data.now_subpage = SUBPAGE_QUALITY;
            photo_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_acu_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_photo->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_submenu;
            photo_subpage_data.now_subpage = SUBPAGE_SHARPNESS;
            photo_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_wbl_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_photo->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_submenu;
            photo_subpage_data.now_subpage = SUBPAGE_AWB;
            photo_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_col_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_photo->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_submenu;
            photo_subpage_data.now_subpage = SUBPAGE_COLOR;
            photo_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_iso_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_photo->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_submenu;
            photo_subpage_data.now_subpage = SUBPAGE_ISO;
            photo_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_pexp_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_photo->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_submenu;
            photo_subpage_data.now_subpage = SUBPAGE_EXPOSURE;
            photo_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_sok_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_photo->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_submenu;
            photo_subpage_data.now_subpage = SUBPAGE_HANDSHAKE;
            photo_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_sca_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_photo->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_submenu;
            photo_subpage_data.now_subpage = SUBPAGE_PREVIEW;
            photo_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_pdat_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_photo->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_submenu;
            photo_subpage_data.now_subpage = SUBPAGE_DATE;
            photo_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_submenu_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_add_flag(guider_ui.video_photo->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_submenu;
            switch (photo_subpage_data.now_subpage) {
            case SUBPAGE_SHOOT:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY1:  //单拍
                    db_update("phm", 0);
                    break;
                case SUBPAGE_FUNKEY2:  //定时2s
                    db_update("phm", 2);
                    break;
                case SUBPAGE_FUNKEY3:  //定时5s
                    db_update("phm", 5);
                    break;
                case SUBPAGE_FUNKEY4:  //定时10s
                    db_update("phm", 10);
                    break;
                default:
                    db_update("phm", 0);
                    break;
                }
                break;
            case SUBPAGE_RESOLUTION:
                switch (lv_roller_get_selected(ui_scr->video_photo_roller_mutifunc)) {
                case 1:
                    db_update("pres", PHOTO_RES_1M);//M
                    break;
                case 2:
                    db_update("pres", PHOTO_RES_2M);;//M
                    break;
                case 3:
                    db_update("pres", PHOTO_RES_3M);//M
                    break;
                case 4:
                    db_update("pres", PHOTO_RES_5M);//M
                    break;
                case 5:
                    db_update("pres", PHOTO_RES_8M);//M
                    break;
                case 6:
                    db_update("pres", PHOTO_RES_10M);//M
                    break;
                default:
                    db_update("pres", PHOTO_RES_VGA);//vga
                    break;
                }
                break;
            case SUBPAGE_SHOTS:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("cyt", 0);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("cyt", 1);
                    break;
                default:
                    db_update("cyt", 0);
                    break;
                }
                break;
            case SUBPAGE_QUALITY:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY1:
                    db_update("qua", PHOTO_QUA_LO);
                    break;
                case SUBPAGE_FUNKEY2:
                    db_update("qua", PHOTO_QUA_MD);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("qua", PHOTO_QUA_HI);
                    break;
                default:
                    db_update("qua", PHOTO_QUA_HI);
                    break;
                }
                break;
            case SUBPAGE_SHARPNESS:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY1:
                    db_update("acu", PHOTO_ACU_HI);
                    break;
                case SUBPAGE_FUNKEY2:
                    db_update("acu", PHOTO_ACU_MD);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("acu", PHOTO_ACU_LO);
                    break;
                default:
                    db_update("acu", PHOTO_ACU_MD);
                    break;
                }
                break;
            case SUBPAGE_AWB:
                db_update("wbl", lv_roller_get_selected(ui_scr->video_photo_roller_mutifunc));
                break;
            case SUBPAGE_COLOR:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY1:
                    db_update("col", PHOTO_COLOR_NORMAL);
                    break;
                case SUBPAGE_FUNKEY2:
                    db_update("col", PHOTO_COLOR_WB);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("col", PHOTO_COLOR_OLD);
                    break;
                default:
                    db_update("col", PHOTO_COLOR_NORMAL);
                    break;
                }
                break;
            case SUBPAGE_ISO:
                switch (lv_roller_get_selected(ui_scr->video_photo_roller_mutifunc)) {
                case 1:
                    db_update("iso", 100);
                    break;
                case 2:
                    db_update("iso", 200);
                    break;
                case 3:
                    db_update("iso", 400);
                    break;
                default:
                    db_update("iso", 0);
                    break;
                }
                break;
            case SUBPAGE_EXPOSURE:
                switch (lv_roller_get_selected(ui_scr->video_photo_roller_mutifunc)) {
                case 0:
                    db_update("pexp", -3);
                    break;
                case 1:
                    db_update("pexp", -2);
                    break;
                case 2:
                    db_update("pexp", -1);
                    break;
                case 3:
                    db_update("pexp", 0);
                    break;
                case 4:
                    db_update("pexp", 1);
                    break;
                case 5:
                    db_update("pexp", 2);
                    break;
                case 6:
                    db_update("pexp", 3);
                    break;
                default:
                    db_update("pexp", 0);
                    break;
                }
                break;
            case SUBPAGE_HANDSHAKE:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY3:
                    db_update("sok", 1);
                    break;
                case SUBPAGE_FUNKEY2:
                    db_update("sok", 0);
                    break;
                default:
                    db_update("sok", 0);
                    break;
                }
                break;
            case SUBPAGE_PREVIEW:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("sca", 2);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("sca", 5);
                    break;
                default:
                    db_update("sca", 0);
                    break;
                }
                break;
            case SUBPAGE_DATE:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY3:
                    db_update("pdat", 1);
                    break;
                case SUBPAGE_FUNKEY2:
                    db_update("pdat", 0);
                    break;
                default:
                    db_update("pdat", 0);
                    break;
                }
                break;

            default:
                break;
            }

            //更新预览中的设置图标
            video_photo_icon_reshow(photo_subpage_data.now_subpage);

            lv_obj_t *menu_obj = NULL;
            uint32_t menu_cnt = lv_obj_get_child_cnt(ui_scr->video_photo_view_menu);
            for (int i = 0; i < menu_cnt; i++) {
                menu_obj = lv_obj_get_child(ui_scr->video_photo_view_menu, i);
                if (menu_obj) {
                    lv_group_add_obj(lv_group_get_default(), menu_obj);
                }
                menu_obj = NULL;
            }

            menu_obj = lv_obj_get_child(ui_scr->video_photo_view_menu, photo_subpage_data.menu_index);
            if (menu_obj) {
                lv_group_focus_obj(menu_obj);
            }
            photo_subpage_data.menu_index = 0;
        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_LEFT || *key == LV_KEY_HOME) {
            lv_obj_add_flag(guider_ui.video_photo->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
        }
        if (*key == LV_KEY_LEFT || *key == LV_KEY_HOME) {
            //custom code video_photo_view_submenu
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
                lv_obj_t *dest = ui_scr->video_photo_view_submenu;
                lv_obj_t *menu_obj = NULL;
                uint32_t menu_cnt = lv_obj_get_child_cnt(ui_scr->video_photo_view_menu);
                for (int i = 0; i < menu_cnt; i++) {
                    menu_obj = lv_obj_get_child(ui_scr->video_photo_view_menu, i);
                    if (menu_obj) {
                        lv_group_add_obj(lv_group_get_default(), menu_obj);
                    }
                    menu_obj = NULL;
                }

                menu_obj = lv_obj_get_child(ui_scr->video_photo_view_menu, photo_subpage_data.menu_index);
                if (menu_obj) {
                    lv_group_focus_obj(menu_obj);
                }
                photo_subpage_data.menu_index = 0;
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_submenu_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            subpage_cur_btn = SUBPAGE_FUNKEY1;
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_submenu_btn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            subpage_cur_btn = SUBPAGE_FUNKEY2;
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_submenu_btn_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            subpage_cur_btn = SUBPAGE_FUNKEY3;
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_submenu_btn_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            subpage_cur_btn = SUBPAGE_FUNKEY4;
        }
    }
    break;
    default:
        break;
    }
}
static void video_photo_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_PHOTO, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_PHOTO, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_video_photo(lv_ui *ui)
{
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_add_event_cb(ui_scr->video_photo, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_scan, video_photo_view_scan_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_menu, video_photo_view_menu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_phm, video_photo_view_phm_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_reso, video_photo_view_reso_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_cyt, video_photo_view_cyt_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_qua, video_photo_view_qua_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_acu, video_photo_view_acu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_wbl, video_photo_view_wbl_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_col, video_photo_view_col_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_iso, video_photo_view_iso_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_pexp, video_photo_view_pexp_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_sok, video_photo_view_sok_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_sca, video_photo_view_sca_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_pdat, video_photo_view_pdat_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_submenu, video_photo_view_submenu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_submenu_btn_1, video_photo_submenu_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_submenu_btn_2, video_photo_submenu_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_submenu_btn_3, video_photo_submenu_btn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_submenu_btn_4, video_photo_submenu_btn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo, video_photo_screen_event_handler, LV_EVENT_ALL, ui);
}

static void video_play_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
            lv_group_focus_obj(ui_scr->video_play_imgbtn_pause);
        }
    }
    break;
    default:
        break;
    }
}

static void video_play_imgbtn_pause_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code video_play_imgbtn_pause
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
            lv_obj_t *dest = ui_scr->video_play_imgbtn_pause;
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            printf("------>%s()----->%d\n", __func__, __LINE__);
            cfun_dec_ok();
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void video_play_img_prev_file_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code video_play_lbl_msg
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
            lv_obj_t *dest = ui_scr->video_play_lbl_msg;
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            static int32_t prev_file = RES_SKIP_PREVIOUS;
            lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_PREV_FILE, prev_file, 0);
            lvgl_module_msg_send_global_ptr(GUI_MODEL_MSG_ID_FILE_NAME, NULL, 0, 0);
            lvgl_module_msg_send_global_ptr(GUI_MODEL_MSG_ID_TOTAL_TIME, NULL, 0, 0);
            dec_video_prev_next(3);
#endif
            // 显示标签
            lv_obj_clear_flag(dest, LV_OBJ_FLAG_HIDDEN);

            uint32_t HIDE_DELAY_MS = 1500; // 例如，隐藏前延迟1.5秒
            lv_timer_t *timer = lv_timer_create(hide_label_timer_cb, HIDE_DELAY_MS, dest);
        }
    }
    break;
    default:
        break;
    }
}

static void video_play_img_next_file_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code video_play_lbl_msg
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
            lv_obj_t *dest = ui_scr->video_play_lbl_msg;
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            static int32_t next_file = RES_SKIP_NEXT;
            lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_NEXT_FILE, next_file, 0);
            lvgl_module_msg_send_global_ptr(GUI_MODEL_MSG_ID_FILE_NAME, NULL, 0, 0);
            lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_NEXT_FILE, next_file, 0);
            lvgl_module_msg_send_global_ptr(GUI_MODEL_MSG_ID_TOTAL_TIME, NULL, 0, 0);
            dec_video_prev_next(2);
#endif
            // 显示标签
            lv_obj_clear_flag(dest, LV_OBJ_FLAG_HIDDEN);

            uint32_t HIDE_DELAY_MS = 1500; // 例如，隐藏前延迟1.5秒
            lv_timer_t *timer = lv_timer_create(hide_label_timer_cb, HIDE_DELAY_MS, dest);
        }
    }
    break;
    default:
        break;
    }
}

static void video_play_imgbtn_loud_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
#if !LV_USE_GUIBUILDER_SIMULATOR
            gui_set_video_volume();
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void video_play_ddlist_multi_spped_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
            lv_group_focus_obj(ui_scr->video_play_imgbtn_pause);
        }
    }
    break;
    case LV_EVENT_VALUE_CHANGED: {
        //custom code video_play_ddlist_multi_spped
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
            lv_obj_t *dest = ui_scr->video_play_ddlist_multi_spped;
            int selected_index = lv_dropdown_get_selected(dest);
            printf("Selected (Index: %d)\n", selected_index);
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            void speed_change(int index);
            speed_change(selected_index);
#endif



        }
    }
    break;
    default:
        break;
    }
}

static void video_play_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
#if !LV_USE_GUIBUILDER_SIMULATOR
            gui_get_video_frame();
#endif
        }
    }
    break;
    default:
        break;
    }
}
static void video_play_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_PLAY, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_PLAY, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_video_play(lv_ui *ui)
{
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    lv_obj_add_event_cb(ui_scr->video_play, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->video_play, video_play_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play_imgbtn_pause, video_play_imgbtn_pause_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play_img_prev_file, video_play_img_prev_file_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play_img_next_file, video_play_img_next_file_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play_imgbtn_loud, video_play_imgbtn_loud_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play_ddlist_multi_spped, video_play_ddlist_multi_spped_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play_imgbtn_1, video_play_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play, video_play_screen_event_handler, LV_EVENT_ALL, ui);
}

static void video_file_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            printf("------>%s()----->%d\n", __func__, __LINE__);
            extern void video_file_screen_load(void);
            video_file_screen_load();
#endif
        }
    }
    break;
    case LV_EVENT_SCREEN_UNLOADED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            extern void video_file_screen_unload(void);
            video_file_screen_unload();
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void video_file_img_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            file_list_up();
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void video_file_img_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            file_list_down();
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void video_file_view_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCROLL: {
        //custom code video_file_view_3
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
            lv_obj_t *dest = ui_scr->video_file_view_3;
            int scroll_value = lv_obj_get_scroll_top(src);
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            scroll_update_position(scroll_value);
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void video_file_view_menu_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
            dec_subpage_data.funkey1 = 0;
            dec_subpage_data.funkey2 = 0;
            dec_subpage_data.funkey3 = 0;
            dec_subpage_data.funkey4 = 0;
            dec_subpage_data.warning = 0;
            dec_subpage_data.btn_focus_id = 0;
            switch (dec_subpage_data.now_subpage) {
            case SUBPAGE_DELETE:
                dec_subpage_data.funkey2 = (void *)_("delete_current");
                dec_subpage_data.funkey3 = (void *)_("delete_all");
                dec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                break;
            case SUBPAGE_PROTECTION:
                dec_subpage_data.funkey1 = (void *)_("lock_one");
                dec_subpage_data.funkey2 = (void *)_("ulock_one");
                dec_subpage_data.funkey3 = (void *)_("all_lock");
                dec_subpage_data.funkey4 = (void *)_("all_ulock");
                dec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY1;
                break;
            default:
                printf("[chili] %s %d   no match subpage!\n",  __func__, __LINE__);
                break;
            }

            decmenu_subpage_show(&dec_subpage_data);
#if !LV_USE_GUIBUILDER_SIMULATOR
            set_dec_submenu_flag(1);
#endif

            lv_obj_t *menu_obj = NULL;
            uint32_t menu_cnt = lv_obj_get_child_cnt(ui_scr->video_file_view_menu);
            printf("rec menu num: %d\n", menu_cnt);
            for (int i = 0; i < menu_cnt; i++) {
                menu_obj = lv_obj_get_child(ui_scr->video_file_view_menu, i);
                if (menu_obj) {
                    lv_group_remove_obj(menu_obj);
                }
                menu_obj = NULL;
            }



        }
    }
    break;
    default:
        break;
    }
}

static void video_file_view_del_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_file->video_file_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_file_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
            lv_obj_t *dest = ui_scr->video_file_view_submenu;
            dec_subpage_data.now_subpage = SUBPAGE_DELETE;
            dec_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_file_view_pro_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(guider_ui.video_file->video_file_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_file_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
            lv_obj_t *dest = ui_scr->video_file_view_submenu;
            dec_subpage_data.now_subpage = SUBPAGE_PROTECTION;
            dec_subpage_data.menu_index = lv_obj_get_index(src);
        }
    }
    break;
    default:
        break;
    }
}

static void video_file_view_submenu_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_add_flag(guider_ui.video_file->video_file_view_submenu, LV_OBJ_FLAG_HIDDEN);
        //custom code video_file_view_submenu
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
            lv_obj_t *dest = ui_scr->video_file_view_submenu;
            uint8_t back_dec = 0;
            static uint8_t war_flag = 0;
            static uint8_t del_type = 0;
            switch (dec_subpage_data.now_subpage) {
            case SUBPAGE_DELETE:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2: {
                    printf("delete current file\n");

                    war_flag = 1;
                    del_type = 0;
                    dec_subpage_data.funkey1 = 0;
                    dec_subpage_data.funkey2 = 0;
                    dec_subpage_data.funkey3 = (void *)_("CANCEL");
                    dec_subpage_data.funkey4 = (void *)_("YES");
                    dec_subpage_data.warning = (void *)_("del_cur_file");
                    dec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    lv_obj_clear_flag(ui_scr->video_file_view_submenu, LV_OBJ_FLAG_HIDDEN);
                    decmenu_subpage_show(&dec_subpage_data);

                }
                break;
                case SUBPAGE_FUNKEY3: {
                    printf("delete all file\n");

                    if (!war_flag) {
                        war_flag = 1;
                        del_type = 1;
                        dec_subpage_data.funkey1 = 0;
                        dec_subpage_data.funkey2 = 0;
                        dec_subpage_data.funkey3 = (void *)_("CANCEL");
                        dec_subpage_data.funkey4 = (void *)_("YES");
                        dec_subpage_data.warning = (void *)_("del_all_file");
                        dec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                        lv_obj_clear_flag(ui_scr->video_file_view_submenu, LV_OBJ_FLAG_HIDDEN);
                        decmenu_subpage_show(&dec_subpage_data);
                    } else {
                        war_flag = 0;
                        del_type = 0;
                        printf("cancel delete file\n");
                    }

                }
                break;
                case SUBPAGE_FUNKEY4: {
                    if (!del_type) {
                        printf("delete current file ok\n");
#if !LV_USE_GUIBUILDER_SIMULATOR
                        delete_file(0);
#endif
                    } else {
                        printf("delete all file ok\n");
#if !LV_USE_GUIBUILDER_SIMULATOR
                        delete_file(1);
#endif
                    }
                    war_flag = 0;
                    del_type = 0;

                    //从子菜单直接返回九宫页面，要先将子菜单的选项添加回默认组
                    lv_group_add_obj(lv_group_get_default(), ui_scr->video_file_view_del);
                    lv_group_add_obj(lv_group_get_default(), ui_scr->video_file_view_pro);
#if !LV_USE_GUIBUILDER_SIMULATOR
                    exit_dec_setting_menu();
                    set_dec_submenu_flag(0);
#endif
                    back_dec = 1;
                }
                break;
                default:
                    break;
                }
                break;
            case SUBPAGE_PROTECTION:
#if !LV_USE_GUIBUILDER_SIMULATOR
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY1:
                    lock_flie(0, 1);
                    break;
                case SUBPAGE_FUNKEY2:
                    lock_flie(0, 0);
                    break;
                case SUBPAGE_FUNKEY3:
                    lock_flie(1, 1);
                    break;
                case SUBPAGE_FUNKEY4:
                    lock_flie(1, 0);
                    break;
                default:
                    break;
                }
#endif

                //从子菜单直接返回九宫页面，要先将子菜单的选项添加回默认组
                lv_group_add_obj(lv_group_get_default(), ui_scr->video_file_view_del);
                lv_group_add_obj(lv_group_get_default(), ui_scr->video_file_view_pro);
#if !LV_USE_GUIBUILDER_SIMULATOR
                exit_dec_setting_menu();
                set_dec_submenu_flag(0);
#endif
                back_dec = 1;
                break;
            default:
                printf("[chili] %s %d   no match subpage!\n",  __func__, __LINE__);
                break;
            }

            if (war_flag || back_dec) {
                return;
            }
            printf("----->%s()----->%d\n", __func__, __LINE__);

            lv_obj_t *menu_obj = NULL;
            uint32_t menu_cnt = lv_obj_get_child_cnt(ui_scr->video_file_view_menu);
            for (int i = 0; i < menu_cnt; i++) {
                menu_obj = lv_obj_get_child(ui_scr->video_file_view_menu, i);
                if (menu_obj) {
                    lv_group_add_obj(lv_group_get_default(), menu_obj);
                }
                menu_obj = NULL;
            }

#if !LV_USE_GUIBUILDER_SIMULATOR
            set_dec_submenu_flag(0);
#endif

            menu_obj = lv_obj_get_child(ui_scr->video_file_view_menu, dec_subpage_data.menu_index);
            if (menu_obj) {
                lv_group_focus_obj(menu_obj);
            }
            dec_subpage_data.menu_index = 0;

        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_HOME) {
            lv_obj_add_flag(guider_ui.video_file->video_file_view_submenu, LV_OBJ_FLAG_HIDDEN);
        }
        if (*key == LV_KEY_HOME) {
            //custom code video_file_view_submenu
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
                lv_obj_t *dest = ui_scr->video_file_view_submenu;

                printf("menu key return\n");
                lv_group_add_obj(lv_group_get_default(), ui_scr->video_file_view_del);
                lv_group_add_obj(lv_group_get_default(), ui_scr->video_file_view_pro);

                switch (dec_subpage_data.now_subpage) {
                case SUBPAGE_DELETE:
                    lv_group_focus_obj(ui_scr->video_file_view_del);
                    break;
                case SUBPAGE_PROTECTION:
                    lv_group_focus_obj(ui_scr->video_file_view_pro);
                    break;
                default:
                    break;
                }
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_file_submenu_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
            subpage_cur_btn = SUBPAGE_FUNKEY1;
        }
    }
    break;
    default:
        break;
    }
}

static void video_file_submenu_btn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
            subpage_cur_btn = SUBPAGE_FUNKEY2;
        }
    }
    break;
    default:
        break;
    }
}

static void video_file_submenu_btn_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
            subpage_cur_btn = SUBPAGE_FUNKEY3;
        }
    }
    break;
    default:
        break;
    }
}

static void video_file_submenu_btn_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
            subpage_cur_btn = SUBPAGE_FUNKEY4;
        }
    }
    break;
    default:
        break;
    }
}
static void video_file_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_FILE, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    }
}

void events_init_video_file(lv_ui *ui)
{
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
    lv_obj_add_event_cb(ui_scr->video_file, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->video_file, video_file_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_img_1, video_file_img_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_img_2, video_file_img_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_view_3, video_file_view_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_view_menu, video_file_view_menu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_view_del, video_file_view_del_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_view_pro, video_file_view_pro_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_view_submenu, video_file_view_submenu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_submenu_btn_1, video_file_submenu_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_submenu_btn_2, video_file_submenu_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_submenu_btn_3, video_file_submenu_btn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_submenu_btn_4, video_file_submenu_btn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file, video_file_screen_event_handler, LV_EVENT_ALL, ui);
}

static void video_dir_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED: {
        //custom code video_dir
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_dir *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR);
            lv_obj_t *dest = ui_scr->video_dir;
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            printf("------>%s()----->%d\n", __func__, __LINE__);
            lvgl_module_msg_send_string(GUI_MODEL_MSG_ID_FILE_PATH, CONFIG_DEC_ROOT_PATH, 0);
            extern void video_dir_screen_load(void);
            video_dir_screen_load();
#endif
        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_RIGHT) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_REC);
            if (screen != NULL) {
                ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
            }
        }
    }
    break;
    default:
        break;
    }
}
static void video_dir_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_DIR, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    }
}

void events_init_video_dir(lv_ui *ui)
{
    lv_ui_video_dir *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR);
    lv_obj_add_event_cb(ui_scr->video_dir, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->video_dir, video_dir_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_dir, video_dir_screen_event_handler, LV_EVENT_ALL, ui);
}

static void line_drift_btn_horizon_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING: {
        //custom code line_drift_btn_horizon
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_line_drift *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LINE_DRIFT);
            lv_obj_t *dest = ui_scr->line_drift_btn_horizon;

            lv_point_t p;

            lv_indev_get_point(lv_indev_get_act(), &p);

            if (dest) {
                if (p.y >= 0 && (p.y < lv_obj_get_y(ui_scr->line_drift_btn_carhead) - lv_obj_get_height(ui_scr->line_drift_btn_horizon))) { //不超过车头线
                    // && (p.y + lv_obj_get_height(dest) <= lv_obj_get_height(lv_obj_get_parent(dest))) ){//限定在父级之内滑动
                    lv_obj_set_y(dest, p.y);
                }

            }

        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_DOWN) {
            //custom code line_drift_btn_horizon
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_line_drift *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LINE_DRIFT);
                lv_obj_t *dest = ui_scr->line_drift_btn_horizon;

                if (dest) {
                    int dest_y = lv_obj_get_y(dest) + 10;

                    if (dest_y >= 0 && (dest_y < lv_obj_get_y(ui_scr->line_drift_btn_carhead) - lv_obj_get_height(ui_scr->line_drift_btn_horizon))) { //不超过车头线
                        //&& (dest_y + lv_obj_get_height(dest) <= lv_obj_get_height(lv_obj_get_parent(dest))) ){//限定在父级之内滑动
                        lv_obj_set_y(dest, dest_y);
                    }

                }


            }
        }
        if (*key == LV_KEY_UP) {
            //custom code line_drift_btn_horizon
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_line_drift *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LINE_DRIFT);
                lv_obj_t *dest = ui_scr->line_drift_btn_horizon;

                if (dest) {
                    int dest_y = lv_obj_get_y(dest) - 10;

                    if (dest_y >= 0) {
                        lv_obj_set_y(dest, dest_y);
                    }

                }


            }
        }
    }
    break;
    default:
        break;
    }
}

static void line_drift_btn_carhead_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING: {
        //custom code line_drift_btn_carhead
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_line_drift *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LINE_DRIFT);
            lv_obj_t *dest = ui_scr->line_drift_btn_carhead;

            lv_point_t p;
            lv_area_t coords;

            lv_indev_get_point(lv_indev_get_act(), &p);
            lv_obj_get_coords(ui_scr->line_drift_btn_horizon, &coords);

            if (dest) {
                if (p.y >= 0 && p.y > coords.y2 //不超过地平线
                    && (p.y + lv_obj_get_height(dest) <= lv_obj_get_height(lv_obj_get_parent(dest)))) {//限定在父级之内滑动
                    lv_obj_set_y(dest, p.y);
                }

            }

        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_DOWN) {
            //custom code line_drift_btn_carhead
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_line_drift *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LINE_DRIFT);
                lv_obj_t *dest = ui_scr->line_drift_btn_carhead;

                if (dest) {

                    int dest_y = lv_obj_get_y(dest) + 10;

                    if (dest_y >= 0 && (dest_y + lv_obj_get_height(dest) <= lv_obj_get_height(lv_obj_get_parent(dest)))) { //限定在父级之内滑动

                        lv_obj_set_y(dest, dest_y);
                    }

                }
            }
        }
        if (*key == LV_KEY_UP) {
            //custom code line_drift_btn_carhead
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_line_drift *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LINE_DRIFT);
                lv_obj_t *dest = ui_scr->line_drift_btn_carhead;



                lv_area_t coords;


                lv_obj_get_coords(ui_scr->line_drift_btn_horizon, &coords);

                if (dest) {
                    int dest_y = lv_obj_get_y(dest) - 10;
                    if (dest_y >= 0 && dest_y > coords.y2) { //不超过地平线
                        lv_obj_set_y(dest, dest_y);
                    }

                }

            }
        }
    }
    break;
    default:
        break;
    }
}

static void line_drift_lbl_7_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_line_drift *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LINE_DRIFT);

            db_update("lan", lv_obj_get_y(ui_scr->line_drift_btn_horizon) || (lv_obj_get_y(ui_scr->line_drift_btn_carhead) << 16));
            printf("[chili]: %s line_drift_btn_horizon %d %d\n", __func__, lv_obj_get_y(ui_scr->line_drift_btn_horizon), lv_obj_get_y(ui_scr->line_drift_btn_carhead));

            line_drift_page_hide(0);
        }
    }
    break;
    default:
        break;
    }
}

static void line_drift_lbl_6_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_line_drift *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LINE_DRIFT);
            line_drift_page_hide(0);
        }
    }
    break;
    default:
        break;
    }
}
static void line_drift_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_LINE_DRIFT, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_LINE_DRIFT, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_line_drift(lv_ui *ui)
{
    lv_ui_line_drift *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LINE_DRIFT);
    lv_obj_add_event_cb(ui_scr->line_drift, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->line_drift_btn_horizon, line_drift_btn_horizon_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->line_drift_btn_carhead, line_drift_btn_carhead_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->line_drift_lbl_7, line_drift_lbl_7_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->line_drift_lbl_6, line_drift_lbl_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->line_drift, line_drift_screen_event_handler, LV_EVENT_ALL, ui);
}

static void sys_popwin_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code sys_popwin
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_popwin *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
            lv_obj_t *dest = ui_scr->sys_popwin;
            if (ui_scr->sys_popwin_del == false && lv_obj_is_valid(ui_scr->sys_popwin)) {
                lv_obj_add_flag(ui_scr->sys_popwin, LV_OBJ_FLAG_HIDDEN);
                /*unload_scr_sys_popwin(&guider_ui);*/
                /*lv_obj_del(ui_scr->sys_popwin);*/
                gui_msg_init_ui();
                gui_msg_init_events();
                delete_gui_timelines();
            }
        }
    }
    break;
    default:
        break;
    }
}

static void sys_popwin_btn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code sys_popwin
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_sys_popwin *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
            lv_obj_t *dest = ui_scr->sys_popwin;
            video_dec_edit_files(del);
            if (ui_scr->sys_popwin_del == false && lv_obj_is_valid(ui_scr->sys_popwin)) {
                lv_obj_add_flag(ui_scr->sys_popwin, LV_OBJ_FLAG_HIDDEN);
                /*unload_scr_sys_popwin(&guider_ui);*/
                /*lv_obj_del(ui_scr->sys_popwin);*/
                gui_msg_init_ui();
                gui_msg_init_events();
                delete_gui_timelines();
            }
        }
    }
    break;
    default:
        break;
    }
}

void events_init_sys_popwin(lv_ui *ui)
{
    lv_ui_sys_popwin *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
    lv_obj_add_event_cb(ui_scr->sys_popwin, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->sys_popwin_btn_1, sys_popwin_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_popwin_btn_2, sys_popwin_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void video_dec_view_scan_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_RIGHT) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_REC);
            if (screen != NULL) {
                ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
            }
        }
        if (*key == LV_KEY_LEFT || *key == LV_KEY_HOME) {
            lv_obj_add_flag(guider_ui.video_dec->video_dec_view_scan, LV_OBJ_FLAG_HIDDEN);
        }
        if (*key == LV_KEY_LEFT || *key == LV_KEY_HOME) {
            //custom code video_dec_view_scan
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_video_dec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DEC);
                lv_obj_t *dest = ui_scr->video_dec_view_scan;
                printf(">>>>enter dec setting menu\n");
                lv_obj_clear_flag(ui_scr->video_dec_view_5, LV_OBJ_FLAG_HIDDEN);  //显示设置菜单
                lv_group_focus_obj(ui_scr->video_dec_view_2);  //进入设置菜单时直接聚焦到第一个设置项

#if !LV_USE_GUIBUILDER_SIMULATOR
                extern void gui_video_dec_set_menu_show(void);
                gui_video_dec_set_menu_show();
#endif
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_dec_view_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_LEFT || *key == LV_KEY_HOME) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_SYS_SETTING);
            if (screen != NULL) {
                ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
            }
        }
        if (*key == LV_KEY_LEFT || *key == LV_KEY_HOME) {
            //custom code sys_setting
            {
                lv_obj_t *src = lv_event_get_target(e);
                lv_ui *ui = lv_event_get_user_data(e);
                lv_ui_video_dec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DEC);
#if !LV_USE_GUIBUILDER_SIMULATOR
                extern void gui_video_dec_set_menu_hide(void);
                gui_video_dec_set_menu_hide();
#endif
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_dec_view_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_dec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DEC);
#if !LV_USE_GUIBUILDER_SIMULATOR
            extern void gui_video_dec_del_file(void);
            gui_video_dec_del_file();
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void video_dec_view_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_dec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DEC);
#if !LV_USE_GUIBUILDER_SIMULATOR
            extern void gui_video_dec_prot_file(void);
            gui_video_dec_prot_file();
#endif
        }
    }
    break;
    default:
        break;
    }
}
static void video_dec_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_DEC, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_DEC, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_video_dec(lv_ui *ui)
{
    lv_ui_video_dec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DEC);
    lv_obj_add_event_cb(ui_scr->video_dec, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->video_dec_view_scan, video_dec_view_scan_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_dec_view_4, video_dec_view_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_dec_view_2, video_dec_view_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_dec_view_3, video_dec_view_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_dec, video_dec_screen_event_handler, LV_EVENT_ALL, ui);
}

static void video_dec_options_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code video_dec_options
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_dec_options *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DEC_OPTIONS);
            lv_obj_t *dest = ui_scr->video_dec_options;
#if !LV_USE_GUIBUILDER_SIMULATOR
            extern void gui_video_dec_cancel_btn(void);
            gui_video_dec_cancel_btn();
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void video_dec_options_btn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code video_dec_options
        {
            lv_obj_t *src = lv_event_get_target(e);
            lv_ui *ui = lv_event_get_user_data(e);
            lv_ui_video_dec_options *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DEC_OPTIONS);
            lv_obj_t *dest = ui_scr->video_dec_options;
#if !LV_USE_GUIBUILDER_SIMULATOR
            extern void gui_video_dec_confirm_btn(void);
            gui_video_dec_confirm_btn();
#endif
        }
    }
    break;
    default:
        break;
    }
}

void events_init_video_dec_options(lv_ui *ui)
{
    lv_ui_video_dec_options *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DEC_OPTIONS);
    lv_obj_add_event_cb(ui_scr->video_dec_options, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->video_dec_options_btn_1, video_dec_options_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_dec_options_btn_2, video_dec_options_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void page_map_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED: {
        //custom code
        {
            set_in_ui_navi_flag(1);
            if (page_map_img_2_init_flag) {
                lv_ui_page_map *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
                lv_obj_clear_flag(ui_scr->page_map_img_2, LV_OBJ_FLAG_HIDDEN);
                page_map_img_2_init_flag = 0;
            }

#if !LV_USE_GUIBUILDER_SIMULATOR

            if (init_flag) {
                lv_example_lyrics_text_input(lyrics_test);
                init_flag = 0;
            }

            page_map_simple_navi_view = get_page_map_view_3_in_map();
            if (page_map_simple_navi_view) {
                lv_obj_clear_flag(page_map_simple_navi_view, LV_OBJ_FLAG_HIDDEN);
            }

#endif
        }
    }
    break;
    case LV_EVENT_SCREEN_UNLOADED: {
        //custom code
        {
#if !LV_USE_GUIBUILDER_SIMULATOR
            page_map_simple_navi_view = get_page_map_view_3_in_map();
            if (page_map_simple_navi_view) {
                lv_obj_add_flag(page_map_simple_navi_view, LV_OBJ_FLAG_HIDDEN);
            }
#endif
        }
    }
    break;
    case LV_EVENT_GESTURE: {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if (dir & LV_DIR_RIGHT) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_USB_SLAVE);
            if (screen != NULL) {
                ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
            }
        }
        if (dir & LV_DIR_RIGHT) {
            //custom code usb_slave
            {
#if !LV_USE_GUIBUILDER_SIMULATOR
                set_in_ui_navi_flag(0);
#endif
            }
        }
    }
    break;
    default:
        break;
    }
}

static void page_map_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_USB_SLAVE);
        if (screen != NULL) {
            ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, true, false);
        }
        //custom code usb_slave
        {
            set_in_ui_navi_flag(0);
        }
    }
    break;
    default:
        break;
    }
}
static void page_map_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_PAGE_MAP, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_PAGE_MAP, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_page_map(lv_ui *ui)
{
    lv_ui_page_map *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAGE_MAP);
    lv_obj_add_event_cb(ui_scr->page_map, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->page_map, page_map_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->page_map_btn_1, page_map_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->page_map, page_map_screen_event_handler, LV_EVENT_ALL, ui);
}

static void power_on_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_timeline_start(&gui_timeline_timeline);
    }
    break;
    default:
        break;
    }
}

void events_init_power_on(lv_ui *ui)
{
    lv_ui_power_on *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_POWER_ON);
    lv_obj_add_event_cb(ui_scr->power_on, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->power_on, power_on_event_handler, LV_EVENT_ALL, ui);
}
static void car_parking_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_CAR_PARKING, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_CAR_PARKING, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_car_parking(lv_ui *ui)
{
    lv_ui_car_parking *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_CAR_PARKING);
    lv_obj_add_event_cb(ui_scr->car_parking, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->car_parking, car_parking_screen_event_handler, LV_EVENT_ALL, ui);
}

void events_init_page_music(lv_ui *ui)
{
    lv_ui_page_music *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAGE_MUSIC);
    lv_obj_add_event_cb(ui_scr->page_music, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
}
static void page_meter_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_PAGE_METER, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_PAGE_METER, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_page_meter(lv_ui *ui)
{
    lv_ui_page_meter *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAGE_METER);
    lv_obj_add_event_cb(ui_scr->page_meter, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->page_meter, page_meter_screen_event_handler, LV_EVENT_ALL, ui);
}

#endif
