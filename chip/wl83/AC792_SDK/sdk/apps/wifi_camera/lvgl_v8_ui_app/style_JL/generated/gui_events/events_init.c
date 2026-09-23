#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
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



extern char video_rec_car_num[64];
static uint8_t del = 0;
extern uint8_t no_select;
extern uint8_t lock_all_flag;
void scr_loaded_handler(lv_event_t *e)
{
    lv_obj_t *src = lv_event_get_target(e);
    gui_msg_init_ui();
    gui_msg_init_events();
}

void events_init(lv_ui *ui)
{
}

static void usb_slave_imgbtn_videorec_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_usb_slave *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_REC);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void usb_slave_imgbtn_masstorage_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_usb_slave *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_add_flag(ui_scr->usb_slave_view_btnlist, LV_OBJ_FLAG_HIDDEN);
        //custom code usb_slave_view_btnlist
        {
            lv_ui_usb_slave *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
            lv_obj_t *dest = ui_scr->usb_slave_view_btnlist;
#if !LV_USE_GUIBUILDER_SIMULATOR
            usb_start(TCFG_USB_DEBUG_ID, MASSSTORAGE_CLASS);
#endif
        }
        lv_obj_clear_flag(ui_scr->usb_slave_img_icon_masstorage, LV_OBJ_FLAG_HIDDEN);
    }
    break;
    default:
        break;
    }
}

static void usb_slave_imgbtn_pccam_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_usb_slave *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_add_flag(ui_scr->usb_slave_view_btnlist, LV_OBJ_FLAG_HIDDEN);
        //custom code usb_slave_view_btnlist
        {
            lv_ui_usb_slave *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
            lv_obj_t *dest = ui_scr->usb_slave_view_btnlist;
#if !LV_USE_GUIBUILDER_SIMULATOR
            usb_start(TCFG_USB_DEBUG_ID, MASSSTORAGE_CLASS | UVC_CLASS | CDC_CLASS);
#endif
        }
        lv_obj_clear_flag(ui_scr->usb_slave_img_icon_pccam, LV_OBJ_FLAG_HIDDEN);
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
    lv_obj_add_event_cb(ui_scr->usb_slave_imgbtn_videorec, usb_slave_imgbtn_videorec_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->usb_slave_imgbtn_masstorage, usb_slave_imgbtn_masstorage_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->usb_slave_imgbtn_pccam, usb_slave_imgbtn_pccam_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->usb_slave, usb_slave_screen_event_handler, LV_EVENT_ALL, ui);
}

static void video_rec_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED: {
        //custom code
        {
            lv_obj_t *dest = src;
            printf("[chili] %s %d   \n",  __func__, __LINE__);
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_RECORD_TIME, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
            //lv_timer_pause(guider_ui.video_rec_timer_1);
        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_DOWN) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
            if (screen != NULL) {
                ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            rec_control_ontouch();
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_video_set_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code video_rec_view_video_set
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_video_set;
            bool is_hidden = lv_obj_has_flag(dest, LV_OBJ_FLAG_HIDDEN);
            //printf("[chili] %s is_hidden %d   \n",  __func__, is_hidden);
            if (!is_hidden) {
                lv_obj_add_flag(dest, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(dest, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_15_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_PHOTO);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
        //custom code video_photo
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo;

#if !LV_USE_GUIBUILDER_SIMULATOR
            extern unsigned char rec_running;
            if (rec_running) {
                rec_control_ontouch();
            }
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_home_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
        //custom code home_page
        {
            lv_ui_home_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
            lv_obj_t *dest = ui_scr->home_page;
            extern unsigned char rec_running;
            if (rec_running) {
                rec_control_ontouch();
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_imgbtn_lock_set_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code video_rec_img_lock_icon
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_img_lock_icon;


            bool is_hidden = lv_obj_has_flag(dest, LV_OBJ_FLAG_HIDDEN);

            printf("[chili] %s is_hidden %d   \n",  __func__, is_hidden);

            rec_set_lock_ontouch();

            if (!is_hidden) {//解锁
                lv_obj_add_flag(dest, LV_OBJ_FLAG_HIDDEN);

            } else {
                lv_obj_clear_flag(dest, LV_OBJ_FLAG_HIDDEN);

            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_imgbtn_sw_window_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            rec_switch_win_ontouch();
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_video_set_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_add_flag(ui_scr->video_rec_view_video_set, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_video_set
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_video_set;

            //更新菜单子页面内容
            rec_subpage_data.funkey1 = 0;//(void*)_("nodealy");
            rec_subpage_data.funkey2 = 0;//(void*)_("dealy2s");
            rec_subpage_data.funkey3 = 0;//(void*)_("dealy5s");
            rec_subpage_data.funkey4 = 0;//(void*)_("dealy10s");
            rec_subpage_data.roller_opt = 0;//"VGA,1M,2M,3M,5M,8M,10M,64M";
            rec_subpage_data.btn_focus_id = 0;

            switch (rec_subpage_data.now_subpage) {

            case SUBPAGE_RESOLUTION:
                rec_subpage_data.icon_res_id = (void *)RES_RESOLUTION_RATIO;
                rec_subpage_data.title = (void *)_("resolution");
                rec_subpage_data.roller_opt = 0;////(void*)"VGA\n1M\n2M\n3M\n5M\n8M\n10M\n64M";
                rec_subpage_data.funkey2 = (void *)"720P";
                rec_subpage_data.funkey3 = (void *)"480P";
                switch (db_select("res")) { //处理高亮样式
                case VIDEO_RES_720P:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                }
                break;
                break;
            case SUBPAGE_DOUBLE_REC:
                rec_subpage_data.icon_res_id = (void *)RES_DOUBLE_VIDEO;
                rec_subpage_data.title = (void *)_("doublerec");
                rec_subpage_data.funkey2 = (void *)_("close");
                rec_subpage_data.funkey3 = (void *)_("open");
                switch (db_select("two")) { //处理高亮样式
                case 1:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;
            case SUBPAGE_HDR:
                rec_subpage_data.icon_res_id = (void *)RES_HDR;
                rec_subpage_data.title = (void *)"HDR";
                rec_subpage_data.funkey2 = (void *)_("close");
                rec_subpage_data.funkey3 = (void *)_("ope");
                switch (db_select("hdr")) { //处理高亮样式
                case 1:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY3;
                    break;
                default:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                }
                break;
            case SUBPAGE_MOTION:
                rec_subpage_data.icon_res_id = (void *)RES_CHECK_SPORT;
                rec_subpage_data.title = (void *)_("motion");
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
                break;

            case SUBPAGE_RECORD:
                rec_subpage_data.icon_res_id = (void *)GUI_RES_SOUND_PNG;
                rec_subpage_data.title = (void *)_("record");
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
            case SUBPAGE_GUARD:
                rec_subpage_data.icon_res_id = (void *)GUI_RES_STOPPING_MONITOR_1_PNG;
                rec_subpage_data.title = (void *)_("guard");
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
                rec_subpage_data.icon_res_id = (void *)GUI_RES_CAR_NUM_PNG;
                rec_subpage_data.title = (void *)_("carnum");
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

            case SUBPAGE_CYC_REC:
                rec_subpage_data.icon_res_id = (void *)RES_CYCLIC_VIDEO;
                rec_subpage_data.title = (void *)_("cycrec");
                rec_subpage_data.funkey1 = (void *)_("close");
                rec_subpage_data.funkey2 = (void *)"1min";
                rec_subpage_data.funkey3 = (void *)"3min";
                rec_subpage_data.funkey4 = (void *)"10min";
                switch (db_select("cyc")) { //处理高亮样式
                case 1:
                    rec_subpage_data.btn_focus_id = SUBPAGE_FUNKEY2;
                    break;
                case 3:
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
                rec_subpage_data.icon_res_id = (void *)RES_INTERVAL_VIDEO;
                rec_subpage_data.title = (void *)_("gaprec");
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
            case SUBPAGE_GSENSOR:
                rec_subpage_data.icon_res_id = (void *)RES_GRAVITY_SENSOR;
                rec_subpage_data.title = (void *)_("gsensor");
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
            case SUBPAGE_EXPOSURE:
                rec_subpage_data.icon_res_id = (void *)RES_EXPOSURE;
                rec_subpage_data.title = (void *)_("exposure");
                rec_subpage_data.roller_opt = (void *)"-3\n-2\n-1\n0\n1\n2\n3";
                rec_subpage_data.funkey2 = (void *)_("YES");
                rec_subpage_data.funkey3 = (void *)_("CANCEL");
                rec_subpage_data.roller = ui_scr->video_rec_roller_mutifunc;
                switch (db_select("exp")) {
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
                    rec_subpage_data.roller_sel = 0;//auto
                    break;

                }
                break;
            case SUBPAGE_DATE:
                rec_subpage_data.icon_res_id = (void *)RES_DATE;
                rec_subpage_data.title = (void *)_("date");
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

            default:
                printf("[chili] %s %d   no match subpage!\n",  __func__, __LINE__);
                break;
            }

            subpage_show(&rec_subpage_data);


        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_resolution_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_subpage
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_subpage;
            rec_subpage_data.now_subpage = SUBPAGE_RESOLUTION;
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_19_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_subpage
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_subpage;
            rec_subpage_data.now_subpage = SUBPAGE_DOUBLE_REC;
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_20_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_subpage
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_subpage;
            rec_subpage_data.now_subpage = SUBPAGE_CYC_REC;
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_21_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_subpage
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_subpage;
            rec_subpage_data.now_subpage = SUBPAGE_GAP;
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_subpage
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_subpage;
            rec_subpage_data.now_subpage = SUBPAGE_HDR;
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_10_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_subpage
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_subpage;
            rec_subpage_data.now_subpage = SUBPAGE_EXPOSURE;
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_17_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_subpage
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_subpage;
            rec_subpage_data.now_subpage = SUBPAGE_MOTION;
            rec_ask_app_open_menu();
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_18_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_subpage
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_subpage;
            rec_subpage_data.now_subpage = SUBPAGE_DATE;
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_subpage
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_subpage;
            rec_subpage_data.now_subpage = SUBPAGE_GSENSOR;
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_22_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_subpage
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_subpage;
            rec_subpage_data.now_subpage = SUBPAGE_RECORD;
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_23_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_subpage
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_subpage;
            rec_subpage_data.now_subpage = SUBPAGE_GUARD;
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_img_24_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_subpage
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_subpage;
            rec_subpage_data.now_subpage = SUBPAGE_CARNUM;
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_view_subpage_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_rec_view_video_set, LV_OBJ_FLAG_HIDDEN);
        //custom code video_rec_view_video_set
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec_view_video_set;

            //根据当前子页面下用户所按按钮设置菜单项
            switch (rec_subpage_data.now_subpage) {
            case SUBPAGE_RESOLUTION:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("res", VIDEO_RES_720P);//单位P
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("res", VIDEO_RES_VGA);//单位P
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }

                break;
            case SUBPAGE_DOUBLE_REC:
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
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("cyc", 1);
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("cyc", 3);
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
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2://确认
                    lv_roller_get_selected_str(ui_scr->video_rec_roller_mutifunc, user_roller_str, 16);
                    printf("[chili] %s %d  %s YES \n",  __func__, __LINE__, user_roller_str);
                    switch (lv_roller_get_selected(ui_scr->video_rec_roller_mutifunc)) {
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
                        db_update("exp", -3);
                        break;
                    }
                    break;
                case SUBPAGE_FUNKEY3://取消
                    printf("[chili] %s %d  CANCEL \n",  __func__, __LINE__);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                break;
            case SUBPAGE_MOTION:
                switch (subpage_cur_btn) {
                case SUBPAGE_FUNKEY2:
                    db_update("mot", 0);
                    rec_tell_app_exit_menu();
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("mot", 1);
                    rec_tell_app_exit_menu();
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
                    lv_obj_add_flag(ui_scr->video_rec_digitclock_2, LV_OBJ_FLAG_HIDDEN);
                    break;
                case SUBPAGE_FUNKEY3:
                    lv_obj_clear_flag(ui_scr->video_rec_digitclock_2, LV_OBJ_FLAG_HIDDEN);
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
                    lv_obj_add_flag(ui_scr->video_rec_lbl_4, LV_OBJ_FLAG_HIDDEN);//未开启车牌号码功能，隐藏
                    break;
                case SUBPAGE_FUNKEY3:
                    db_update("num", 1);
                    lv_obj_clear_flag(ui_scr->video_rec_lbl_4, LV_OBJ_FLAG_HIDDEN);//开启车牌号码功能，取消隐藏
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                video_rec_config_init();
                break;

            default:
                printf("[chili] %s %d   no match subpage!\n",  __func__, __LINE__);
                break;
            }

            video_rec_icon_reshow(rec_subpage_data.now_subpage);//更新预览界面图标







        }
        lv_obj_add_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
    }
    break;
    default:
        break;
    }
}

static void video_rec_lbl_funkey1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            subpage_cur_btn = SUBPAGE_FUNKEY1;//记录下被按下的keyfun键值
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_lbl_funkey2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            subpage_cur_btn = SUBPAGE_FUNKEY2;//记录下被按下的keyfun键值
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_lbl_funkey3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            subpage_cur_btn = SUBPAGE_FUNKEY3;//记录下被按下的keyfun键值
        }
    }
    break;
    default:
        break;
    }
}

static void video_rec_lbl_funkey4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            subpage_cur_btn = SUBPAGE_FUNKEY4;//记录下被按下的keyfun键值
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
    lv_obj_add_event_cb(ui_scr->video_rec_imgbtn_1, video_rec_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_video_set, video_rec_img_video_set_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_15, video_rec_img_15_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_home, video_rec_img_home_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_imgbtn_lock_set, video_rec_imgbtn_lock_set_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_imgbtn_sw_window, video_rec_imgbtn_sw_window_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_video_set, video_rec_view_video_set_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_resolution, video_rec_img_resolution_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_19, video_rec_img_19_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_20, video_rec_img_20_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_21, video_rec_img_21_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_1, video_rec_img_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_10, video_rec_img_10_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_17, video_rec_img_17_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_18, video_rec_img_18_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_3, video_rec_img_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_22, video_rec_img_22_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_23, video_rec_img_23_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_img_24, video_rec_img_24_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_view_subpage, video_rec_view_subpage_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_lbl_funkey1, video_rec_lbl_funkey1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_lbl_funkey2, video_rec_lbl_funkey2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_lbl_funkey3, video_rec_lbl_funkey3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec_lbl_funkey4, video_rec_lbl_funkey4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_rec, video_rec_screen_event_handler, LV_EVENT_ALL, ui);
}

static void home_page_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_home_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_REC);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void home_page_imgbtn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_home_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_DIR);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void home_page_imgbtn_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_home_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_SYS_SETTING);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 50, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}
static void home_page_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_HOME_PAGE, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_HOME_PAGE, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_home_page(lv_ui *ui)
{
    lv_ui_home_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
    lv_obj_add_event_cb(ui_scr->home_page, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->home_page_imgbtn_1, home_page_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->home_page_imgbtn_2, home_page_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->home_page_imgbtn_3, home_page_imgbtn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->home_page, home_page_screen_event_handler, LV_EVENT_ALL, ui);
}

static void sys_prompt_img_warn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_PROMPT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code sys_prompt
        {
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
                /*lv_obj_clean(ui_scr->sys_prompt);*/
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

static void sys_setting_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED: {
        //custom code sys_setting_img_saver
        {
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_img_saver;
            printf("[chili] %s %d   \n",  __func__, __LINE__);
            // 执行点击事件
            my_sysmenu_subpage.now_subpage = SUBPAGE_SAVER;
            reinit_sys_setting_model(); //每次重新初始化模型
        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_HOME) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
            if (screen != NULL) {
                ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
            }
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_view_menupage_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            //隐藏弹性布局放置18语 label列表
            hide_flex_language_list();
            //更新菜单子页面内容
            my_sysmenu_subpage.funkey1 = 0;
            my_sysmenu_subpage.funkey2 = 0;
            my_sysmenu_subpage.funkey3 = 0;
            my_sysmenu_subpage.funkey4 = 0;
            my_sysmenu_subpage.funkey5 = 0;
            my_sysmenu_subpage.funkey6 = 0;
            my_sysmenu_subpage.funkey7 = 0;
            my_sysmenu_subpage.funkey8 = 0;
            my_sysmenu_subpage.carnum_view = 0;
            my_sysmenu_subpage.date_view = 0;
            my_sysmenu_subpage.warning = 0;
            //清除disable样式
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey4, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey5, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey6, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey7, LV_STATE_DISABLED);
            switch (my_sysmenu_subpage.now_subpage) {

            case SUBPAGE_SAVER:
                my_sysmenu_subpage.icon_res_id = (void *)RES_LCD_OFF;
                my_sysmenu_subpage.title = (void *)_("lcdprotect");
                my_sysmenu_subpage.funkey4 = (void *)_("close");
                my_sysmenu_subpage.funkey5 = (void *)"30s";
                my_sysmenu_subpage.funkey6 = (void *)"60s";
                my_sysmenu_subpage.funkey7 = (void *)"120s";
                switch (db_select("pro")) { //处理高亮样式
                case 30:
                    my_sysmenu_subpage.list_focus_id = 1;
                    break;
                case 60:
                    my_sysmenu_subpage.list_focus_id = 2;
                    break;
                case 120:
                    my_sysmenu_subpage.list_focus_id = 3;
                    break;
                default:
                    my_sysmenu_subpage.list_focus_id = 0;
                    break;
                }
                //lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey4);
                break;
            case  SUBPAGE_POWEROFF:
                my_sysmenu_subpage.icon_res_id = (void *)RES_AUTO_OFF;
                my_sysmenu_subpage.title = (void *)_("poweroff");
                my_sysmenu_subpage.funkey4 = (void *)_("close");
                my_sysmenu_subpage.funkey5 = (void *)"3min";
                my_sysmenu_subpage.funkey6 = (void *)"5min";
                my_sysmenu_subpage.funkey7 = (void *)"10min";
                switch (db_select("aff")) { //处理高亮样式
                case 3:
                    my_sysmenu_subpage.list_focus_id = 1;
                    break;
                case 5:
                    my_sysmenu_subpage.list_focus_id = 2;
                    break;
                case 10:
                    my_sysmenu_subpage.list_focus_id = 3;
                    break;
                default:
                    my_sysmenu_subpage.list_focus_id = 0;
                    break;
                }
                //lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey4);
                break;

            case  SUBPAGE_FREQ:
                my_sysmenu_subpage.icon_res_id = (void *)RES_FREQUENCY;
                my_sysmenu_subpage.title = (void *)_("frequency");
                my_sysmenu_subpage.funkey4 = (void *)"50Hz";
                my_sysmenu_subpage.funkey5 = (void *)"60Hz";
                switch (db_select("fre")) { //处理高亮样式
                case 60:
                    my_sysmenu_subpage.list_focus_id = 1;
                    break;
                default:
                    my_sysmenu_subpage.list_focus_id = 0;
                    break;
                }
                //lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey4);
                break;

            case  SUBPAGE_VOLUME:
                my_sysmenu_subpage.icon_res_id = (void *)RES_VOICE;
                my_sysmenu_subpage.title = (void *)_("speaker");
                my_sysmenu_subpage.funkey4 = (void *)_("close");
                my_sysmenu_subpage.funkey5 = (void *)_("open");
                switch (db_select("kvo")) { //处理高亮样式
                case 1:
                    my_sysmenu_subpage.list_focus_id = 1;
                    break;
                default:
                    my_sysmenu_subpage.list_focus_id = 0;
                    break;
                }
                //lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey4);
                break;

            case  SUBPAGE_LANGUAGE:
                my_sysmenu_subpage.icon_res_id = (void *)RES_LANGUAGES;
                my_sysmenu_subpage.title = (void *)_("language");
                flex_language_list();
                break;

            case  SUBPAGE_VERSION:
                my_sysmenu_subpage.icon_res_id = (void *)RES_SOFTWARE;
                my_sysmenu_subpage.title = (void *)_("software");
                my_sysmenu_subpage.warning = (void *)_("subpagewarning3");
                break;

            case  SUBPAGE_DATA:
                my_sysmenu_subpage.icon_res_id = (void *)RES_DATE_1;
                my_sysmenu_subpage.title = (void *)_("date");
                my_sysmenu_subpage.funkey8 = (void *)_("YES");
                my_sysmenu_subpage.date_view = "for test";
                lv_group_focus_obj(ui_scr->sys_setting_roller_hour);
                break;

            case  SUBPAGE_CARNUM:
                my_sysmenu_subpage.icon_res_id = (void *)RES_CAR_NUM_1;
                my_sysmenu_subpage.title = (void *)_("carnum");
                my_sysmenu_subpage.funkey8 = (void *)_("YES");
                my_sysmenu_subpage.carnum_view = "for test";
                lv_group_focus_obj(ui_scr->sys_setting_ddlist_1);
                break;

            case  SUBPAGE_LINEDRIFT:
                my_sysmenu_subpage.icon_res_id = (void *)RES_LANE;
                my_sysmenu_subpage.title = (void *)_("roadline");
                my_sysmenu_subpage.funkey4 = (void *)_("close");
                my_sysmenu_subpage.funkey5 = (void *)_("open");
                switch (db_select("lan")) { //处理高亮样式
                case 1:
                    my_sysmenu_subpage.list_focus_id = 1;
                    break;
                default:
                    my_sysmenu_subpage.list_focus_id = 0;
                    break;
                }
                //lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey4);
                break;

            case  SUBPAGE_HAEDLAMP:
                my_sysmenu_subpage.icon_res_id = (void *)RES_FLIG;
                my_sysmenu_subpage.title = (void *)_("lamp");
                my_sysmenu_subpage.funkey4 = (void *)_("close");
                my_sysmenu_subpage.funkey5 = (void *)_("open");
                switch (db_select("hlw")) { //处理高亮样式
                case 1:
                    my_sysmenu_subpage.list_focus_id = 1;
                    break;
                default:
                    my_sysmenu_subpage.list_focus_id = 0;
                    break;
                }
                //lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey4);
                break;

            case  SUBPAGE_FORMATTING:
                my_sysmenu_subpage.icon_res_id = (void *)RES_FORMAT;
                my_sysmenu_subpage.title = (void *)_("formatting");
                my_sysmenu_subpage.warning = (void *)_("subpagewarning0");
                my_sysmenu_subpage.funkey8 = (void *)_("YES");
                lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey2);
                break;

            case  SUBPAGE_RESET:
                my_sysmenu_subpage.icon_res_id = (void *)RES_RESET;
                my_sysmenu_subpage.title = (void *)_("reset");
                my_sysmenu_subpage.warning = (void *)_("subpagewarning2");
                my_sysmenu_subpage.funkey8 = (void *)_("YES");
                lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey2);
                break;

            default:
                printf("[chili] %s %d   no match subpage!\n",  __func__, __LINE__);
                break;
            }
            sysmenu_subpage_show(&my_sysmenu_subpage);


        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_saver_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code sys_setting_view_list
        {
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_view_list;
            //更新菜单子页面内容
            //注意：这是按下“屏保”按钮的按键事件，首次显示菜单子界面放在了SYS_SETTING页面的页面事件中。
            printf("[chili] %s %d   \n",  __func__, __LINE__);

            my_sysmenu_subpage.now_subpage = SUBPAGE_SAVER;

        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            //更新菜单子页面内容
            printf("[chili] %s %d   \n",  __func__, __LINE__);

            my_sysmenu_subpage.now_subpage = SUBPAGE_POWEROFF;



        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            //更新菜单子页面内容
            printf("[chili] %s %d   \n",  __func__, __LINE__);

            my_sysmenu_subpage.now_subpage = SUBPAGE_FREQ;



        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            //更新菜单子页面内容
            printf("[chili] %s %d   \n",  __func__, __LINE__);

            my_sysmenu_subpage.now_subpage = SUBPAGE_VOLUME;


        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            //更新菜单子页面内容
            printf("[chili] %s %d   \n",  __func__, __LINE__);

            my_sysmenu_subpage.now_subpage = SUBPAGE_LANGUAGE;




        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_7_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            //更新菜单子页面内容
            printf("[chili] %s %d   \n",  __func__, __LINE__);

            my_sysmenu_subpage.now_subpage = SUBPAGE_VERSION;






        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_9_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            my_sysmenu_subpage.now_subpage = SUBPAGE_CARNUM;
#if !LV_USE_GUIBUILDER_SIMULATOR
            set_car_num_part_a(db_select("cna"));
            set_car_num_part_b(db_select("cnb"));
            lv_dropdown_set_selected(ui_scr->sys_setting_ddlist_1, db_select("proc"));
            lv_dropdown_set_selected(ui_scr->sys_setting_ddlist_2, (video_rec_car_num[3] - 'A'));
            lv_dropdown_set_selected(ui_scr->sys_setting_ddlist_3, (video_rec_car_num[4] - '0'));
            lv_dropdown_set_selected(ui_scr->sys_setting_ddlist_4, (video_rec_car_num[5] - '0'));
            lv_dropdown_set_selected(ui_scr->sys_setting_ddlist_5, (video_rec_car_num[6] - '0'));
            lv_dropdown_set_selected(ui_scr->sys_setting_ddlist_6, (video_rec_car_num[7] - '0'));
            lv_dropdown_set_selected(ui_scr->sys_setting_ddlist_7, (video_rec_car_num[8] - '0'));
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_8_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            //更新菜单子页面内容
            printf("[chili] %s %d   \n",  __func__, __LINE__);

            my_sysmenu_subpage.now_subpage = SUBPAGE_LINEDRIFT;


        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_6_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            //更新菜单子页面内容
            printf("[chili] %s %d   \n",  __func__, __LINE__);

            my_sysmenu_subpage.now_subpage = SUBPAGE_HAEDLAMP;


        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_10_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code sys_setting_lbl_subpage_warning
        {
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_lbl_subpage_warning;
            my_sysmenu_subpage.now_subpage = SUBPAGE_FORMATTING;

        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_11_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code sys_setting_lbl_subpage_warning
        {
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_lbl_subpage_warning;
            my_sysmenu_subpage.now_subpage = SUBPAGE_RESET;


        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_12_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code sys_setting_view_date
        {
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_view_date;
            my_sysmenu_subpage.now_subpage = SUBPAGE_DATA;
#if !LV_USE_GUIBUILDER_SIMULATOR
            char buf[16];
            struct sys_time usr_time;
            get_sys_time(&usr_time);
            lv_snprintf(buf, sizeof(buf), "%d/%02d/%02d", usr_time.year, usr_time.month, usr_time.day);
            lv_label_set_text(ui_scr->sys_setting_datetext_subpage, buf);
            lv_roller_set_selected(ui_scr->sys_setting_roller_hour, usr_time.hour, LV_ANIM_OFF);
            lv_roller_set_selected(ui_scr->sys_setting_roller_min, usr_time.min, LV_ANIM_OFF);
#endif

        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_15_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_REC);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
        //custom code video_rec
        {
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
            lv_obj_t *dest = ui_scr->video_rec;
            /*
            *   隐藏弹性布局放置18语 label列表
            *
            */
            hide_flex_language_list();
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_14_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_DIR);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
        //custom code video_dir
        {
            lv_ui_video_dir *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR);
            lv_obj_t *dest = ui_scr->video_dir;
            /*
            *   隐藏弹性布局放置18语 label列表
            *
            */
            hide_flex_language_list();
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_img_16_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
        //custom code home_page
        {
            lv_ui_home_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
            lv_obj_t *dest = ui_scr->home_page;
            /*
            *   隐藏弹性布局放置18语 label列表
            *
            */
            hide_flex_language_list();
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_view_list_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            sysmenu_subpage_btnlist_keyevent_cb(ui);//高亮处理&按键处理
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_lbl_funkey4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_add_state(ui_scr->sys_setting_lbl_funkey4, LV_STATE_FOCUS_KEY);
        //custom code sys_setting_lbl_funkey4
        {
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_lbl_funkey4;
            subpage_cur_btn = SUBPAGE_FUNKEY4;//记录下被按下的keyfun键值
            //清除disable样式
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey4, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey5, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey6, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey7, LV_STATE_DISABLED);
            //清除高亮样式
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey4, LV_STATE_FOCUS_KEY);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey5, LV_STATE_FOCUS_KEY);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey6, LV_STATE_FOCUS_KEY);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey7, LV_STATE_FOCUS_KEY);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_lbl_funkey5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_add_state(ui_scr->sys_setting_lbl_funkey5, LV_STATE_FOCUS_KEY);
        //custom code sys_setting_lbl_funkey5
        {
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_lbl_funkey5;
            subpage_cur_btn = SUBPAGE_FUNKEY5;//记录下被按下的keyfun键值
            //清除disable样式
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey4, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey5, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey6, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey7, LV_STATE_DISABLED);

            //清除高亮样式
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey4, LV_STATE_FOCUS_KEY);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey5, LV_STATE_FOCUS_KEY);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey6, LV_STATE_FOCUS_KEY);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey7, LV_STATE_FOCUS_KEY);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_lbl_funkey6_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_add_state(ui_scr->sys_setting_lbl_funkey6, LV_STATE_FOCUS_KEY);
        //custom code sys_setting_lbl_funkey6
        {
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_lbl_funkey6;
            subpage_cur_btn = SUBPAGE_FUNKEY6;//记录下被按下的keyfun键值
            //清除disable样式
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey4, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey5, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey6, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey7, LV_STATE_DISABLED);
            //清除高亮样式
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey4, LV_STATE_FOCUS_KEY);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey5, LV_STATE_FOCUS_KEY);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey6, LV_STATE_FOCUS_KEY);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey7, LV_STATE_FOCUS_KEY);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_lbl_funkey7_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_add_state(ui_scr->sys_setting_lbl_funkey7, LV_STATE_FOCUS_KEY);
        //custom code sys_setting_lbl_funkey7
        {
            lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
            lv_obj_t *dest = ui_scr->sys_setting_lbl_funkey7;
            subpage_cur_btn = SUBPAGE_FUNKEY7;//记录下被按下的keyfun键值
            //清除disable样式
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey4, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey5, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey6, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey7, LV_STATE_DISABLED);
            //清除高亮样式
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey4, LV_STATE_FOCUS_KEY);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey5, LV_STATE_FOCUS_KEY);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey6, LV_STATE_FOCUS_KEY);
            lv_obj_clear_state(ui_scr->sys_setting_lbl_funkey7, LV_STATE_FOCUS_KEY);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_setting_lbl_funkey2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_SETTING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            subpage_cur_btn = SUBPAGE_FUNKEY2;//记录下被按下的keyfun键值
            sysmenu_subpage_btnlist_keyevent_cb(ui);
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
    lv_obj_add_event_cb(ui_scr->sys_setting, sys_setting_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_menupage, sys_setting_view_menupage_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_saver, sys_setting_img_saver_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_2, sys_setting_img_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_3, sys_setting_img_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_4, sys_setting_img_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_5, sys_setting_img_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_7, sys_setting_img_7_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_9, sys_setting_img_9_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_8, sys_setting_img_8_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_6, sys_setting_img_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_10, sys_setting_img_10_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_11, sys_setting_img_11_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_12, sys_setting_img_12_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_15, sys_setting_img_15_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_14, sys_setting_img_14_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_img_16, sys_setting_img_16_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_view_list, sys_setting_view_list_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_lbl_funkey4, sys_setting_lbl_funkey4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_lbl_funkey5, sys_setting_lbl_funkey5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_lbl_funkey6, sys_setting_lbl_funkey6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_lbl_funkey7, sys_setting_lbl_funkey7_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting_lbl_funkey2, sys_setting_lbl_funkey2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_setting, sys_setting_screen_event_handler, LV_EVENT_ALL, ui);
}

static void video_photo_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED: {
        //custom code
        {
            lv_obj_t *dest = src;

            printf("[chili] %s %d   \n",  __func__, __LINE__);
            //更新预览界面图标---非模型注册方式（主动set）
#if LV_USE_GUIBUILDER_SIMULATOR
            memset(user_roller_str, 0, 16);
            sprintf(user_roller_str, "%dM", db_select("pres"));
            video_photo_icon_reshow(SUBPAGE_RESOLUTION);

            memset(user_roller_str, 0, 16);
            if (db_select("iso")) {
                sprintf(user_roller_str, "%d", db_select("iso"));
            } else {
                strcpy(user_roller_str, "AUTO");
            }
            video_photo_icon_reshow(SUBPAGE_ISO);

            video_photo_icon_reshow(SUBPAGE_SHOOT);
            video_photo_icon_reshow(SUBPAGE_SHOTS);
            video_photo_icon_reshow(SUBPAGE_QUALITY);
            video_photo_icon_reshow(SUBPAGE_HANDSHAKE);
            video_photo_icon_reshow(SUBPAGE_AWB);
#else//模型回调GET方式（注册模型回调被动GET）
            //extern void get_video_photo_cfg(void);//获取设备当前拍照设置参数
#endif
        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_HOME) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
            if (screen != NULL) {
                ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_imgbtn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;

            extern int gui_take_photo(void);
            gui_take_photo();

        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            extern int gui_switch_camera(void);
            gui_switch_camera();

        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_video_set_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code video_photo_view_video_set
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_video_set;
            bool is_hidden = lv_obj_has_flag(dest, LV_OBJ_FLAG_HIDDEN);
            printf("[chili] %s is_hidden %d   \n",  __func__, is_hidden);
            if (!is_hidden) {
                lv_obj_add_flag(dest, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(dest, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_15_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_REC);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_home_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_video_set_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_add_flag(ui_scr->video_photo_view_video_set, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_video_set
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_video_set;
            //更新菜单子页面内容
            photo_subpage_data.funkey1 = 0;//(void*)_("nodealy");
            photo_subpage_data.funkey2 = 0;//(void*)_("dealy2s");
            photo_subpage_data.funkey3 = 0;//(void*)_("dealy5s");
            photo_subpage_data.funkey4 = 0;//(void*)_("dealy10s");
            photo_subpage_data.roller_opt = 0;//"VGA,1M,2M,3M,5M,8M,10M";
            photo_subpage_data.btn_focus_id = 0;

            switch (photo_subpage_data.now_subpage) {

            case SUBPAGE_RESOLUTION:
                photo_subpage_data.icon_res_id = (void *)RES_RESOLUTION_RATIO;
                photo_subpage_data.title = (void *)_("resolution");
                photo_subpage_data.roller_opt = (void *)"VGA\n1M\n2M\n3M\n5M\n8M\n10M";
                photo_subpage_data.funkey2 = (void *)_("YES");
                photo_subpage_data.funkey3 = (void *)_("CANCEL");
                photo_subpage_data.roller = ui_scr->video_photo_roller_mutifunc;
                switch (db_select("pres")) { //单位M
                case 1:
                    photo_subpage_data.roller_sel = 1;
                    break;
                case 2:
                    photo_subpage_data.roller_sel = 2;//
                    break;
                case 3:
                    photo_subpage_data.roller_sel = 3;
                    break;
                case 5:
                    photo_subpage_data.roller_sel = 4;//
                    break;
                case 8:
                    photo_subpage_data.roller_sel = 5;
                    break;
                case 10:
                    photo_subpage_data.roller_sel = 6;//
                    break;
                default:
                    photo_subpage_data.roller_sel = 0;//vga
                    break;

                }

                break;
            case SUBPAGE_SHOOT:
                photo_subpage_data.icon_res_id = (void *)GUI_RES_TIMING_PHOTO_PNG;
                photo_subpage_data.title = (void *)_("shoot");
                photo_subpage_data.funkey1 = (void *)_("nodealy");
                photo_subpage_data.funkey2 = (void *)_("dealy2s");
                photo_subpage_data.funkey3 = (void *)_("dealy5s");
                photo_subpage_data.funkey4 = (void *)_("dealy10s");
                switch (db_select("phm")) { //处理高亮样式
                case 2:
                    photo_subpage_data.btn_focus_id = 2;
                    break;
                case 5:
                    photo_subpage_data.btn_focus_id = 3;
                    break;
                case 10:
                    photo_subpage_data.btn_focus_id = 4;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = 1;
                    break;
                }
                break;
            case SUBPAGE_SHOTS:
                photo_subpage_data.icon_res_id = (void *)GUI_RES_CONTINUOUS_PHOTO_PNG;
                photo_subpage_data.title = (void *)_("shots");
                photo_subpage_data.funkey2 = (void *)_("close");
                photo_subpage_data.funkey3 = (void *)_("open");
                switch (db_select("cyt")) { //处理高亮样式
                case 1:
                    photo_subpage_data.btn_focus_id = 3;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = 2;
                    break;
                }
                break;
            case SUBPAGE_QUALITY:
                photo_subpage_data.icon_res_id = (void *)GUI_RES_PHOTO_QUALITY_PNG;
                photo_subpage_data.title = (void *)_("quality");
                photo_subpage_data.funkey1 = (void *)_("pool");
                photo_subpage_data.funkey2 = (void *)_("standard");
                photo_subpage_data.funkey3 = (void *)_("high");
                switch (db_select("qua")) { //处理高亮样式
                case 1:
                    photo_subpage_data.btn_focus_id = 2;
                    break;
                case 2:
                    photo_subpage_data.btn_focus_id = 3;
                    break;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = 1;
                    break;
                }
                break;
            case SUBPAGE_SHARPNESS:
                photo_subpage_data.icon_res_id = (void *)GUI_RES_ACUITY_PNG;
                photo_subpage_data.title = (void *)_("sharpness");
                photo_subpage_data.funkey1 = (void *)_("strong");
                photo_subpage_data.funkey2 = (void *)_("standard");
                photo_subpage_data.funkey3 = (void *)_("soft");
                switch (db_select("acu")) { //处理高亮样式
                case 2:
                    photo_subpage_data.btn_focus_id = 1;
                    break;
                case 1:
                    photo_subpage_data.btn_focus_id = 2;
                    break;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = 3;
                    break;
                }
                break;
            case SUBPAGE_AWB:
                photo_subpage_data.icon_res_id = (void *)GUI_RES_AWB_PNG;
                photo_subpage_data.title = (void *)_("awb");
                sprintf(user_roller_str, "%s\n%s\n%s\n%s\n%s", _("default"), _("sunshine"), _("cloudy"), _("tung"), _("fluolamp"));
                photo_subpage_data.roller_opt = (void *)user_roller_str;
                photo_subpage_data.funkey2 = (void *)_("YES");
                photo_subpage_data.funkey3 = (void *)_("CANCEL");
                photo_subpage_data.roller = ui_scr->video_photo_roller_mutifunc;
                photo_subpage_data.roller_sel = db_select("wbl");
                break;
            case SUBPAGE_COLOR:
                photo_subpage_data.icon_res_id = (void *)GUI_RES_COLOR_PNG;
                photo_subpage_data.title = (void *)_("color");
                photo_subpage_data.funkey1 = (void *)_("default");
                photo_subpage_data.funkey2 = (void *)_("mono");
                photo_subpage_data.funkey3 = (void *)_("Nostalgia");
                switch (db_select("col")) { //处理高亮样式
                case 1:
                    photo_subpage_data.btn_focus_id = 2;
                    break;
                case 2:
                    photo_subpage_data.btn_focus_id = 3;
                    break;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = 1;
                    break;
                }
                break;
            case SUBPAGE_ISO:
                photo_subpage_data.icon_res_id = (void *)GUI_RES_ISO_PNG;
                photo_subpage_data.title = (void *)"ISO";
                photo_subpage_data.roller_opt = "AUTO\n100\n200\n400";
                photo_subpage_data.funkey2 = (void *)_("YES");
                photo_subpage_data.funkey3 = (void *)_("CANCEL");
                photo_subpage_data.roller = ui_scr->video_photo_roller_mutifunc;
                switch (db_select("iso")) {
                case 100:
                    photo_subpage_data.roller_sel = 1;
                    break;
                case 200:
                    photo_subpage_data.roller_sel = 2;//
                    break;
                case 400:
                    photo_subpage_data.roller_sel = 3;
                    break;
                    break;
                default:
                    photo_subpage_data.roller_sel = 0;//auto
                    break;

                }
                break;
            case SUBPAGE_EXPOSURE:
                photo_subpage_data.icon_res_id = (void *)GUI_RES_EXPOSURE_PNG;
                photo_subpage_data.title = (void *)_("exposure");
                photo_subpage_data.roller_opt = (void *)"-3\n-2\n-1\n0\n1\n2\n3";
                photo_subpage_data.funkey2 = (void *)_("YES");
                photo_subpage_data.funkey3 = (void *)_("CANCEL");
                photo_subpage_data.roller = ui_scr->video_photo_roller_mutifunc;
                switch (db_select("pexp")) {
                case 0xfffffffe://-2:
                    photo_subpage_data.roller_sel = 1;
                    break;
                case 0xffffffff://-1
                    photo_subpage_data.roller_sel = 2;//
                    break;
                case 0:
                    photo_subpage_data.roller_sel = 3;
                    break;
                case 1:
                    photo_subpage_data.roller_sel = 4;
                    break;
                case 2:
                    photo_subpage_data.roller_sel = 5;//
                    break;
                case 3:
                    photo_subpage_data.roller_sel = 6;//
                    break;
                default://-3
                    photo_subpage_data.roller_sel = 0;//auto
                    break;

                }

                break;
            case SUBPAGE_HANDSHAKE:
                photo_subpage_data.icon_res_id = (void *)GUI_RES_HAND_SHAKE_1_PNG;
                photo_subpage_data.title = (void *)_("handshake");
                photo_subpage_data.funkey2 = (void *)_("close");
                photo_subpage_data.funkey3 = (void *)_("open");
                switch (db_select("sok")) { //处理高亮样式
                case 1:
                    photo_subpage_data.btn_focus_id = 3;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = 2;
                    break;
                }
                break;
            case SUBPAGE_PREVIEW:
                photo_subpage_data.icon_res_id = (void *)GUI_RES_QUICK_SCAN_PNG;
                photo_subpage_data.title = (void *)_("preview");
                photo_subpage_data.funkey1 = (void *)_("close");
                photo_subpage_data.funkey2 = (void *)"2s";
                photo_subpage_data.funkey3 = (void *)"5s";
                //printf("[chili] %s sub user_photo_preview %d   \n",  __func__, user_photo_preview);
                switch (db_select("sca")) { //处理高亮样式
                case 2:
                    photo_subpage_data.btn_focus_id = 2;
                    break;
                case 5:
                    photo_subpage_data.btn_focus_id = 3;
                    break;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = 1;
                    break;
                }
                break;
            case SUBPAGE_DATE:
                photo_subpage_data.icon_res_id = (void *)RES_DATE;
                photo_subpage_data.title = (void *)_("date_p");
                photo_subpage_data.funkey2 = (void *)_("close");
                photo_subpage_data.funkey3 = (void *)_("open");
                switch (db_select("pdat")) { //处理高亮样式
                case 1:
                    photo_subpage_data.btn_focus_id = 3;
                    break;
                default:
                    photo_subpage_data.btn_focus_id = 2;
                    break;
                }
                break;

            default:
                printf("[chili] %s %d   no match subpage!\n",  __func__, __LINE__);
                break;
            }

            subpage_show(&photo_subpage_data);


        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_resolution_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_subpage
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_subpage;
            photo_subpage_data.now_subpage = SUBPAGE_RESOLUTION;


        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_19_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_subpage
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_subpage;
            photo_subpage_data.now_subpage = SUBPAGE_SHOOT;






        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_20_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_subpage
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_subpage;

            photo_subpage_data.now_subpage = SUBPAGE_SHOTS;








        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_21_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_subpage
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_subpage;

            photo_subpage_data.now_subpage = SUBPAGE_QUALITY;






        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_subpage
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_subpage;

            photo_subpage_data.now_subpage = SUBPAGE_SHARPNESS;







        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_10_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_subpage
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_subpage;

            photo_subpage_data.now_subpage = SUBPAGE_AWB;








        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_17_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_subpage
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_subpage;

            photo_subpage_data.now_subpage = SUBPAGE_COLOR;





        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_18_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_subpage
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_subpage;

            photo_subpage_data.now_subpage = SUBPAGE_ISO;


        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_subpage
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_subpage;

            photo_subpage_data.now_subpage = SUBPAGE_EXPOSURE;


        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_22_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_subpage
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_subpage;

            photo_subpage_data.now_subpage = SUBPAGE_HANDSHAKE;

        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_23_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_subpage
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_subpage;

            photo_subpage_data.now_subpage = SUBPAGE_PREVIEW;


        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_img_24_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_subpage
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_subpage;

            photo_subpage_data.now_subpage = SUBPAGE_DATE;


        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_view_subpage_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_obj_clear_flag(ui_scr->video_photo_view_video_set, LV_OBJ_FLAG_HIDDEN);
        //custom code video_photo_view_video_set
        {
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
            lv_obj_t *dest = ui_scr->video_photo_view_video_set;
            //根据当前子页面下用户所按按钮设置菜单项
            switch (photo_subpage_data.now_subpage) {
            case SUBPAGE_RESOLUTION:
                //拍摄分辨率设定
                switch (subpage_cur_btn) {
                case 2://确认
                    lv_roller_get_selected_str(ui_scr->video_photo_roller_mutifunc, user_roller_str, 16);
                    printf("[chili] %s %d  %s YES \n",  __func__, __LINE__, user_roller_str);
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
                    case 7:
                        db_update("pres", PHOTO_RES_64M);//M
                        break;
                    default:
                        db_update("pres", PHOTO_RES_VGA);//M vga
                        break;
                    }

                    break;
                case 3://取消
                    printf("[chili] %s %d  CANCEL \n",  __func__, __LINE__);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }

                break;
            case SUBPAGE_EXPOSURE:
                switch (subpage_cur_btn) {
                case 2://确认
                    lv_roller_get_selected_str(ui_scr->video_photo_roller_mutifunc, user_roller_str, 16);
                    printf("[chili] %s %d  %s YES \n",  __func__, __LINE__, user_roller_str);
                    switch (lv_roller_get_selected(ui_scr->video_photo_roller_mutifunc)) {
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
                        db_update("pexp", -3);
                        break;
                    }
                    break;
                case 3://取消
                    printf("[chili] %s %d  CANCEL \n",  __func__, __LINE__);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                break;
            case SUBPAGE_ISO:
                //iso
                switch (subpage_cur_btn) {
                case 2://确认
                    lv_roller_get_selected_str(ui_scr->video_photo_roller_mutifunc, user_roller_str, 16);
                    printf("[chili] %s %d  %s YES \n",  __func__, __LINE__, user_roller_str);
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
                case 3://取消
                    printf("[chili] %s %d  CANCEL \n",  __func__, __LINE__);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                break;
            case SUBPAGE_SHOOT:
                //拍摄方式设定
                switch (subpage_cur_btn) {
                case 1://单拍
                    printf("[chili] %s %d  timing 0s \n",  __func__, __LINE__);
                    db_update("phm", 0);
                    break;
                case 2://定时2s
                    printf("[chili] %s %d  timing 2s \n",  __func__, __LINE__);
                    db_update("phm", 2);
                    break;
                case 3://定时5s
                    printf("[chili] %s %d  timing 5s \n",  __func__, __LINE__);
                    db_update("phm", 5);
                    break;
                case 4://定时10s
                    printf("[chili] %s %d  timing 10s \n",  __func__, __LINE__);
                    db_update("phm", 10);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    db_update("phm", 0);
                    break;
                }
                break;
            case SUBPAGE_SHOTS:
                switch (subpage_cur_btn) {
                case 3://确认
                    db_update("cyt", 1);
                    break;
                case 2://关闭
                    db_update("cyt", 0);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                break;
            case SUBPAGE_QUALITY:
                //图像质量设定
                switch (subpage_cur_btn) {
                case 1://
                    db_update("qua", PHOTO_QUA_LO);
                    break;
                case 2://
                    db_update("qua", PHOTO_QUA_MD);
                    break;
                default:
                    db_update("qua", PHOTO_QUA_HI);
                    break;
                }
                break;
            case SUBPAGE_SHARPNESS:
                //锐度设定
                switch (subpage_cur_btn) {
                case 1://强烈
                    printf("[chili] %s %d  strong \n",  __func__, __LINE__);
                    db_update("acu", PHOTO_ACU_HI);
                    break;
                case 2://标准
                    printf("[chili] %s %d  standard \n",  __func__, __LINE__);
                    db_update("acu", PHOTO_ACU_MD);
                    break;
                case 3://柔和
                    printf("[chili] %s %d  soft \n",  __func__, __LINE__);
                    db_update("acu", PHOTO_ACU_LO);
                    break;
                default:
                    db_update("acu", PHOTO_ACU_MD);
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                break;
            case SUBPAGE_AWB:
                //awb设定
                switch (subpage_cur_btn) {
                case 2://确认
                    lv_roller_get_selected_str(ui_scr->video_photo_roller_mutifunc, user_roller_str, 16);
                    db_update("wbl", lv_roller_get_selected(ui_scr->video_photo_roller_mutifunc));
                    break;
                case 3://取消
                    printf("[chili] %s %d  CANCEL \n",  __func__, __LINE__);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }

                break;
            case SUBPAGE_COLOR:
                switch (subpage_cur_btn) {
                case 3:
                    db_update("col", PHOTO_COLOR_OLD);
                    break;
                case 2:
                    db_update("col", PHOTO_COLOR_WB);
                    break;
                default:
                    db_update("col", PHOTO_COLOR_NORMAL);
                    break;
                }
                break;

            case SUBPAGE_HANDSHAKE:
                switch (subpage_cur_btn) {
                case 3://确认
                    db_update("sok", 1);
                    break;
                case 2://关闭
                    db_update("sok", 0);
                    break;
                default:
                    printf("[chili] %s %d  no key clicked. \n",  __func__, __LINE__);
                    break;
                }
                break;
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
                //printf("[chili] %s user_photo_preview %d   \n",  __func__, user_photo_preview);
                break;
            case SUBPAGE_DATE:
                switch (subpage_cur_btn) {
                case 3://确认
                    db_update("pdat", 1);
                    break;
                case 2://关闭
                    db_update("pdat", 0);
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

            video_photo_icon_reshow(photo_subpage_data.now_subpage);//更新预览界面图标







        }
        lv_obj_add_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
    }
    break;
    default:
        break;
    }
}

static void video_photo_lbl_funkey1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            subpage_cur_btn = SUBPAGE_FUNKEY1;//记录下被按下的keyfun键值
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_lbl_funkey2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            subpage_cur_btn = SUBPAGE_FUNKEY2;//记录下被按下的keyfun键值
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_lbl_funkey3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            subpage_cur_btn = SUBPAGE_FUNKEY3;//记录下被按下的keyfun键值
        }
    }
    break;
    default:
        break;
    }
}

static void video_photo_lbl_funkey4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            subpage_cur_btn = SUBPAGE_FUNKEY4;//记录下被按下的keyfun键值
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
    lv_obj_add_event_cb(ui_scr->video_photo, video_photo_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_imgbtn_2, video_photo_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_imgbtn_1, video_photo_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_video_set, video_photo_img_video_set_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_15, video_photo_img_15_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_home, video_photo_img_home_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_video_set, video_photo_view_video_set_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_resolution, video_photo_img_resolution_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_19, video_photo_img_19_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_20, video_photo_img_20_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_21, video_photo_img_21_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_1, video_photo_img_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_10, video_photo_img_10_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_17, video_photo_img_17_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_18, video_photo_img_18_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_3, video_photo_img_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_22, video_photo_img_22_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_23, video_photo_img_23_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_img_24, video_photo_img_24_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_view_subpage, video_photo_view_subpage_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_lbl_funkey1, video_photo_lbl_funkey1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_lbl_funkey2, video_photo_lbl_funkey2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_lbl_funkey3, video_photo_lbl_funkey3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo_lbl_funkey4, video_photo_lbl_funkey4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_photo, video_photo_screen_event_handler, LV_EVENT_ALL, ui);
}

static void video_play_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            if (lv_obj_is_valid(ui_scr->video_play_view_1)) {
                lv_obj_clear_flag(ui_scr->video_play_view_1, LV_OBJ_FLAG_HIDDEN);
            }

            if (ui_scr->video_play_hide_bar) {
                lv_timer_del(ui_scr->video_play_hide_bar);
                ui_scr->video_play_hide_bar = NULL;
            }

            ui_scr->video_play_hide_bar = lv_timer_create(hide_label_timer_cb, 3000, ui_scr->video_play_view_1);
        }
    }
    break;
    case LV_EVENT_SCREEN_LOADED: {
        //custom code
        {
            lv_obj_t *dest = src;
            lv_group_focus_obj(ui_scr->video_play_imgbtn_pause);
        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_HOME) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
            if (screen != NULL) {
                ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
            }
        }
        if (*key == LV_KEY_HOME) {
            //custom code home_page
            {
                lv_ui_home_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
                lv_obj_t *dest = ui_scr->home_page;
#if !LV_USE_GUIBUILDER_SIMULATOR
                cfun_dec_ok();
                cfun_dec_return();
#endif
            }
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
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code video_play_imgbtn_pause
        {
            lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
            lv_obj_t *dest = ui_scr->video_play_imgbtn_pause;
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            cfun_dec_ok();
#endif
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
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
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
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        //custom code video_play_ddlist_multi_spped
        {
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
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
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

static void video_play_imgbtn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_FILE);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
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
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code video_play_lbl_msg
        {
            lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
            lv_obj_t *dest = ui_scr->video_play_lbl_msg;
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            dec_video_prev_next(3);
#endif
            // 显示标签
            lv_obj_clear_flag(dest, LV_OBJ_FLAG_HIDDEN);

            uint32_t HIDE_DELAY_MS = 1500; // 例如，隐藏前延迟1.5秒
            if (ui_scr->video_play_hide_label) {
                lv_timer_del(ui_scr->video_play_hide_label);
                ui_scr->video_play_hide_label = NULL;
            }
            if (ui_scr->video_play_hide_bar) {
                lv_timer_del(ui_scr->video_play_hide_bar);
                ui_scr->video_play_hide_bar = NULL;
            }

            ui_scr->video_play_hide_label = lv_timer_create(hide_label_timer_cb, HIDE_DELAY_MS, dest);
            ui_scr->video_play_hide_bar = lv_timer_create(hide_label_timer_cb, 3000, ui_scr->video_play_view_1);
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
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code video_play_lbl_msg
        {
            lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
            lv_obj_t *dest = ui_scr->video_play_lbl_msg;
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            dec_video_prev_next(2);
#endif
            // 显示标签
            lv_obj_clear_flag(dest, LV_OBJ_FLAG_HIDDEN);

            uint32_t HIDE_DELAY_MS = 1500; // 例如，隐藏前延迟1.5秒

            if (ui_scr->video_play_hide_label) {
                lv_timer_del(ui_scr->video_play_hide_label);
                ui_scr->video_play_hide_label = NULL;
            }
            if (ui_scr->video_play_hide_bar) {
                lv_timer_del(ui_scr->video_play_hide_bar);
                ui_scr->video_play_hide_bar = NULL;
            }

            ui_scr->video_play_hide_label = lv_timer_create(hide_label_timer_cb, HIDE_DELAY_MS, dest);
            ui_scr->video_play_hide_bar = lv_timer_create(hide_label_timer_cb, 3000, ui_scr->video_play_view_1);

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
    lv_obj_add_event_cb(ui_scr->video_play_imgbtn_loud, video_play_imgbtn_loud_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play_ddlist_multi_spped, video_play_ddlist_multi_spped_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play_imgbtn_1, video_play_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play_imgbtn_2, video_play_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play_img_prev_file, video_play_img_prev_file_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play_img_next_file, video_play_img_next_file_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play, video_play_screen_event_handler, LV_EVENT_ALL, ui);
}

static void video_file_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            extern void video_file_screen_load(void);
            video_file_screen_load();
#endif
        }
    }
    break;
    case LV_EVENT_SCREEN_UNLOADED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            extern void video_file_screen_unload(void);
            video_file_screen_unload();
#endif
        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_HOME) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
            if (screen != NULL) {
                ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_file_imgbtn_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_DIR);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
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
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
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
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
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

static void video_file_imgbtn_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code video_file
        {
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
            lv_obj_t *dest = ui_scr->video_file;
            if (lv_obj_has_flag(ui_scr->video_file_imgbtn_2, LV_OBJ_FLAG_HIDDEN)) {
                lv_obj_clear_flag(ui_scr->video_file_imgbtn_2, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_scr->video_file_imgbtn_5, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(ui_scr->video_file_imgbtn_5, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_scr->video_file_imgbtn_2, LV_OBJ_FLAG_HIDDEN);
            }
            edit_lock_file(dest, 0);
        }
    }
    break;
    default:
        break;
    }
}

static void video_file_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_ui_sys_popwin *_ui_sys_popwin = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
        if (_ui_sys_popwin && _ui_sys_popwin->sys_popwin_del == false && lv_obj_is_valid(_ui_sys_popwin->sys_popwin)) {
            lv_obj_clear_flag(_ui_sys_popwin->sys_popwin, LV_OBJ_FLAG_HIDDEN);
        } else {
            setup_scr_sys_popwin(&guider_ui);
            gui_msg_init_ui();
            gui_msg_init_events();
            gui_timelines_delete();
        }
        //custom code sys_popwin
        {
            lv_ui_sys_popwin *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
            lv_obj_t *dest = ui_scr->sys_popwin;
            if (no_select) {
                if (lock_all_flag) {
                    lvgl_module_msg_send_string(GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, _("lock_all"), 0);
                } else {
                    lvgl_module_msg_send_string(GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, _("unlock_all"), 0);
                }
            } else {
                lvgl_module_msg_send_string(GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, _("lock_file"), 0);
            }
            del = 0;


        }
    }
    break;
    default:
        break;
    }
}

static void video_file_imgbtn_5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void video_file_imgbtn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_ui_sys_popwin *_ui_sys_popwin = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
        if (_ui_sys_popwin && _ui_sys_popwin->sys_popwin_del == false && lv_obj_is_valid(_ui_sys_popwin->sys_popwin)) {
            lv_obj_clear_flag(_ui_sys_popwin->sys_popwin, LV_OBJ_FLAG_HIDDEN);
        } else {
            setup_scr_sys_popwin(&guider_ui);
            gui_msg_init_ui();
            gui_msg_init_events();
            gui_timelines_delete();
        }
        //custom code sys_popwin
        {
            lv_ui_sys_popwin *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
            lv_obj_t *dest = ui_scr->sys_popwin;
            del = 1;
            if (no_select) {
                lvgl_module_msg_send_string(GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, _("del_all"), 0);
            } else {
                lvgl_module_msg_send_string(GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, _("del_file"), 0);
            }

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
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_SCROLL: {
        //custom code video_file_view_3
        {
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
static void video_file_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_FILE, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_FILE, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_video_file(lv_ui *ui)
{
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
    lv_obj_add_event_cb(ui_scr->video_file, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->video_file, video_file_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_imgbtn_4, video_file_imgbtn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_img_1, video_file_img_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_img_2, video_file_img_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_imgbtn_3, video_file_imgbtn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_imgbtn_1, video_file_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_imgbtn_5, video_file_imgbtn_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_imgbtn_2, video_file_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file_view_3, video_file_view_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_file, video_file_screen_event_handler, LV_EVENT_ALL, ui);
}

static void video_dir_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_dir *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED: {
        //custom code video_dir
        {
            lv_ui_video_dir *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR);
            lv_obj_t *dest = ui_scr->video_dir;
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            lvgl_module_msg_send_string(GUI_MODEL_MSG_ID_FILE_PATH, CONFIG_DEC_ROOT_PATH, 0);
            extern void video_dir_screen_load(void);
            video_dir_screen_load();
#endif
        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_HOME) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
            if (screen != NULL) {
                ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
            }
        }
    }
    break;
    default:
        break;
    }
}

static void video_dir_imgbtn_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_dir *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void video_dir_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_dir *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code video_dir
        {
            lv_ui_video_dir *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR);
            lv_obj_t *dest = ui_scr->video_dir;
            edit_lock_file(dest, 1);
        }
    }
    break;
    default:
        break;
    }
}

static void video_dir_imgbtn_5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_dir *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
    }
    break;
    default:
        break;
    }
}

static void video_dir_imgbtn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_dir *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
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
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_DIR, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_video_dir(lv_ui *ui)
{
    lv_ui_video_dir *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR);
    lv_obj_add_event_cb(ui_scr->video_dir, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->video_dir, video_dir_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_dir_imgbtn_4, video_dir_imgbtn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_dir_imgbtn_1, video_dir_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_dir_imgbtn_5, video_dir_imgbtn_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_dir_imgbtn_2, video_dir_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_dir, video_dir_screen_event_handler, LV_EVENT_ALL, ui);
}

static void car_parking_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_car_parking *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_CAR_PARKING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED: {
        //custom code usb_slave
        {
            lv_ui_usb_slave *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
            lv_obj_t *dest = ui_scr->usb_slave;
            /*测试使用*/
        }
    }
    break;
    default:
        break;
    }
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
    lv_obj_add_event_cb(ui_scr->car_parking, car_parking_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->car_parking, car_parking_screen_event_handler, LV_EVENT_ALL, ui);
}

static void line_drift_btn_horizon_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_line_drift *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LINE_DRIFT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_PRESSING: {
        //custom code line_drift_btn_horizon
        {
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
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_line_drift *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LINE_DRIFT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_PRESSING: {
        //custom code line_drift_btn_carhead
        {
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
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_line_drift *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LINE_DRIFT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;

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
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_line_drift *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LINE_DRIFT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
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
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_popwin *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code sys_popwin
        {
            lv_ui_sys_popwin *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
            lv_obj_t *dest = ui_scr->sys_popwin;
            if (ui_scr->sys_popwin_del == false && lv_obj_is_valid(ui_scr->sys_popwin)) {
                lv_obj_add_flag(ui_scr->sys_popwin, LV_OBJ_FLAG_HIDDEN);
                unload_scr_sys_popwin(&guider_ui);
                lv_obj_clean(ui_scr->sys_popwin);
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
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_popwin *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code sys_popwin
        {
            lv_ui_sys_popwin *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
            lv_obj_t *dest = ui_scr->sys_popwin;
            video_dec_edit_files(del);
            if (ui_scr->sys_popwin_del == false && lv_obj_is_valid(ui_scr->sys_popwin)) {
                lv_obj_add_flag(ui_scr->sys_popwin, LV_OBJ_FLAG_HIDDEN);
                unload_scr_sys_popwin(&guider_ui);
                lv_obj_clean(ui_scr->sys_popwin);
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

#endif
