#include "custom.h"
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "ui.h"
#include "fs/fs.h"
#include "avctp_user.h"
#include "video/logo_show.h"


static u32 toltal_time = 0;
static void img_cleanup_cb(lv_event_t *e);

//UI 按钮事件
void res_event_next_song(lv_event_t *e)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    app_send_message(APP_MSG_BT_MUSIC_NEXT, 0);
#endif
}
void res_event_prev_song(lv_event_t *e)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    app_send_message(APP_MSG_BT_MUSIC_PREV, 0);
#endif
}
void res_event_pause_or_play(lv_event_t *e)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    app_send_message(APP_MSG_BT_MUSIC_PP, 0);
    if (bt_get_total_connect_dev() == 0) {
        ui_music_pause_handler(); //没有设备连接，重置UI按钮
    }
#endif
}
void res_event_music_volume_change(lv_event_t *e)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    lv_obj_t *slider = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(slider); // 从该对象获取当前值
    app_send_message(APP_MSG_BT_VOL_SET, 1, value);
#endif
}
void res_event_music_process_change(lv_event_t *e)
{
#if !LV_USE_GUIBUILDER_SIMULATOR

#endif
}

//歌词、专辑图片视图转换
void res_event_lyrics_album_view_change(lv_event_t *e)
{
    lv_ui_music_player *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_MUSIC_PLAYER);
    if (!ui_scr || ui_scr->music_player_del) {
        return;
    }
    gui_msg_data_t *name_data = gui_msg_get(GUI_SONGS_MSG_ID_MUSIC_NAME);
    gui_msg_data_t *artist_data = gui_msg_get(GUI_SONGS_MSG_ID_MUSIC_ARTIST);

    lv_obj_t *view_pic = ui_scr->music_player_view_1;
    lv_obj_t *view_lyrics = ui_scr->music_player_view_lyrics;
    if (lv_obj_has_flag(view_lyrics, LV_OBJ_FLAG_HIDDEN)) {
        //显示歌词
        user_spectrum_advance_set_bypass(1);
        lvgl_module_msg_send_value(GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW, 0, 0);
        lvgl_module_msg_send_value(GUI_SONGS_MSG_ID_LYRICS_SHOW, 1, 0);
    } else if (lv_obj_has_flag(view_pic, LV_OBJ_FLAG_HIDDEN)) {
        //显示专辑、频谱
        user_spectrum_advance_set_bypass(0);
        lvgl_module_msg_send_value(GUI_SONGS_MSG_ID_LYRICS_SHOW, 0, 0);
        lvgl_module_msg_send_value(GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW, 1, 0);
    }
}

// UI处理SDK消息回调
void ui_music_pause_handler(void)
{
    lvgl_module_msg_send_value(GUI_SONGS_MSG_ID_MUSIC_STATE, LV_STATE_DEFAULT, 0);
}

void ui_music_on_handler(void)
{
    lvgl_module_msg_send_value(GUI_SONGS_MSG_ID_MUSIC_STATE, LV_STATE_CHECKED, 0);
}

void ui_music_tol_time_handler(u32 tol_time)
{
    uint8_t min = tol_time / 1000 / 60;
    uint8_t sec = tol_time / 1000 - (min * 60);
    toltal_time = tol_time;
    char *tol_time_ptr =  lvgl_module_msg_get_ptr(GUI_SONGS_MSG_ID_TOL_TIME, 8);
    sprintf(tol_time_ptr, "%02u:%02u", min, sec);
    lvgl_module_msg_send_ptr(tol_time_ptr, 0); //发送成功后内部会释放指针，无需再释放
}

void ui_music_cur_time_handler(u32 cur_time)
{
    uint8_t min = cur_time / 1000 / 60;
    uint8_t sec = cur_time / 1000 - (min * 60);
    char *cur_time_ptr =  lvgl_module_msg_get_ptr(GUI_SONGS_MSG_ID_CUR_TIME, 8);
    sprintf(cur_time_ptr, "%02u:%02u", min, sec);
    lvgl_module_msg_send_ptr(cur_time_ptr, 0); //发送成功后内部会释放指针，无需再释放
    lvgl_rpc_post_func(ui_music_process_handler, 1, cur_time);
}

void ui_music_process_handler(u32 cur_time)
{
    if (toltal_time == 0) {
        return;
    }
    uint32_t progress_percent = 0;
    if (cur_time <= toltal_time) {
        progress_percent = (cur_time * 100) / toltal_time;
    } else {
        progress_percent = 100;
    }
    lv_ui_music_player *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_MUSIC_PLAYER);
    if (!ui_scr) {
        return;
    }
    if (!lv_obj_is_valid(ui_scr->music_player_slider_1)) {
        return;
    }
    lv_bar_set_value(ui_scr->music_player_slider_1, progress_percent, LV_ANIM_OFF);
}

void ui_music_album_pic_handler(void)
{
    printf("--->%s()----->%d\n", __func__, __LINE__);

    uint32_t rgb_buf_len;
    uint8_t *rgb565_buf = NULL;
    uint16_t width = 0, height = 0;

    rgb_color_t avg_color = {0x80, 0x80, 0x80}; // 默认灰色
    int err = ui_action_jpeg_decoder(&rgb565_buf, &rgb_buf_len, &avg_color, &width, &height);
    if (err != 0 || !rgb565_buf) {
        printf("JPEG decode failed\n");
        return;
    }

    ui_music_spectrum_set_bg_avg_color(avg_color.r, avg_color.g, avg_color.b);

    //printf("Image loaded 0x%x, size: %d bytes\n", rgb565_buf, rgb_buf_len);
    printf("Image loaded size: %d bytes\n", rgb_buf_len);

    // 获取当前活跃页面ID
    gui_scr_t *current_screen = gui_scr_get_act();
    if (!current_screen) {
        printf("No active screen found\n");
        lv_mem_free(rgb565_buf);
        return;
    }

    int32_t current_screen_id = gui_scr_get_id(current_screen);
    printf("Current screen ID: %d\n", current_screen_id);

    lv_obj_t *img_dst = NULL;
    lv_obj_t *img_view = NULL;
    lv_obj_t **img_ptr_to_update = NULL; // 用于更新页面结构体中的指针
    bool is_sys_menu_page = false;



    // 根据当前活跃页面ID决定更新哪个控件
    if (current_screen_id == GUI_SCREEN_MUSIC_PLAYER) {
        lv_ui_music_player *ui_scr_player = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_MUSIC_PLAYER);
        if (ui_scr_player && !ui_scr_player->music_player_del) {
            printf("Updating music player page\n");
            img_dst = ui_scr_player->music_player_img_1;
            img_view = ui_scr_player->music_player_view_1;
            img_ptr_to_update = &ui_scr_player->music_player_img_1;

#ifndef UI_MUSIC_DYNAMIC_BACKGROUND //未启用动态背景时，根据平均rgb更新背景颜色
            // 获取背景对象
            lv_obj_t *bg_obj = ui_scr_player->music_player;
            // 用于保存遮罩层对象指针，以便后续使用
            static lv_obj_t *mask_layer = NULL;

            // 如果存在旧的遮罩层，先删除它
            if (mask_layer && lv_obj_is_valid(mask_layer)) {
                lv_obj_del(mask_layer);
                mask_layer = NULL;
            }

            // 在设置背景时添加智能判断
            if (bg_obj && lv_obj_is_valid(bg_obj)) {
                // 直接使用平均颜色作为背景色，不再进行亮度计算和调整
                lv_color_t bg_color = lv_color_make(avg_color.r, avg_color.g, avg_color.b);

                // 设置背景颜色
                lv_obj_set_style_bg_color(bg_obj, bg_color, 0);

#if 0
                // 创建更暗的渐变颜色
                lv_color_t grad_color = lv_color_make(
                                            avg_color.r > 20 ? avg_color.r - 20 : 0,
                                            avg_color.g > 20 ? avg_color.g - 20 : 0,
                                            avg_color.b > 20 ? avg_color.b - 20 : 0
                                        );
                // 设置渐变
                lv_grad_dsc_t grad;
                grad.dither = 0;
                grad.dir = LV_GRAD_DIR_HOR;
                grad.stops_count = 2;
                grad.stops[0].color = bg_color;
                grad.stops[0].frac = 0;
                grad.stops[1].color = grad_color;
                grad.stops[1].frac = 255;

                lv_obj_set_style_bg_grad(bg_obj, &grad, 0);

                lv_obj_set_style_bg_opa(bg_obj, LV_OPA_100, 0);
#endif

                // 添加灰色遮罩层
                mask_layer = lv_obj_create(bg_obj);
                if (mask_layer) {
                    // 设置遮罩层覆盖整个背景
                    lv_obj_set_size(mask_layer, lv_obj_get_width(bg_obj), lv_obj_get_height(bg_obj));
                    lv_obj_set_pos(mask_layer, 0, 0);

                    // 设置遮罩层样式
                    // 使用深灰色遮罩，可以根据需要调整颜色
                    lv_obj_set_style_bg_color(mask_layer, lv_color_make(0x30, 0x30, 0x30), 0);

                    // 设置透明度，40%的透明度，可以根据需要调整 (0-255)
                    lv_obj_set_style_bg_opa(mask_layer, LV_OPA_40, 0);

                    lv_obj_set_style_border_width(mask_layer, 0, 0);
                    lv_obj_set_style_pad_all(mask_layer, 0, 0);
                    lv_obj_set_style_radius(mask_layer, 0, 0);
                    lv_obj_clear_flag(mask_layer, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_move_background(mask_layer);
                    printf("Created gray mask layer\n");
                }

            }
#endif
        } else {
            printf("Music player screen is not valid or deleted\n");
            lv_mem_free(rgb565_buf);
            return;
        }
    } else if (current_screen_id == GUI_SCREEN_SYS_MENU) {
        lv_ui_sys_menu *ui_scr_sys_menu = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_MENU);
        if (ui_scr_sys_menu && !ui_scr_sys_menu->sys_menu_del) {
            printf("Updating sys menu page\n");
            img_dst = ui_scr_sys_menu->sys_menu_img_8;
            img_view = ui_scr_sys_menu->sys_menu_view_6;
            img_ptr_to_update = &ui_scr_sys_menu->sys_menu_img_8;
            is_sys_menu_page = true;
        } else {
            printf("Sys menu screen is not valid or deleted\n");
            lv_mem_free(rgb565_buf);
            return;
        }
    } else {
        printf("Current page ID %d is neither music player nor sys menu\n", current_screen_id);
        lv_mem_free(rgb565_buf);
        return;
    }

    if (!img_view || !lv_obj_is_valid(img_view)) {
        printf("Invalid view container\n");
        lv_mem_free(rgb565_buf);
        return;
    }

    printf("Target view found, creating image...\n");

    // 动态分配并初始化图像描述符
    lv_img_dsc_t *image_dsc = (lv_img_dsc_t *)lv_mem_alloc(sizeof(lv_img_dsc_t));
    if (!image_dsc) {
        printf("Failed to allocate image descriptor\n");
        lv_mem_free(rgb565_buf);
        return;
    }

    memset(image_dsc, 0, sizeof(lv_img_dsc_t));
    image_dsc->header.always_zero = 0;
    image_dsc->header.w = width;
    image_dsc->header.h = height;
    image_dsc->header.cf = LV_IMG_CF_TRUE_COLOR;
    image_dsc->data = rgb565_buf;
    image_dsc->data_size = rgb_buf_len;

    // 创建图片对象
    lv_obj_t *img = lv_img_create(img_view);
    if (!img) {
        printf("Failed to create image object\n");
        lv_mem_free(image_dsc);
        lv_mem_free(rgb565_buf);
        return;
    }

    lv_img_set_src(img, image_dsc);
    printf("Image object created\n");

    // 基本样式设置
    ui_style_set(img, GUI_CTRL_IMG);

    // 如果是sys_menu页面，设置缩放100
    if (is_sys_menu_page) {
        printf("Setting zoom to 100%% for sys menu\n");
        lv_obj_align(img, LV_ALIGN_LEFT_MID, -35, 5);
        lv_img_set_zoom(img, 120);
    } else {
        lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    }

    // 圆形裁剪样式
    lv_obj_set_style_radius(img, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(img, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(img, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 为图片对象添加标志，标记需要清理
    lv_obj_add_flag(img, LV_OBJ_FLAG_USER_1);

    // 设置用户数据指向 image_dsc
    lv_obj_set_user_data(img, image_dsc);

    // 添加删除事件回调
    lv_obj_add_event_cb(img, img_cleanup_cb, LV_EVENT_DELETE, NULL);

    // 如果之前有专辑图片，先删除它
    if (img_dst && lv_obj_is_valid(img_dst)) {
        printf("Deleting old image\n");
        lv_obj_del(img_dst);
    }

    // 更新页面结构体中的图片指针
    if (img_ptr_to_update) {
        *img_ptr_to_update = img;
        printf("Updated page image pointer\n");
    }

    printf("Image update completed\n");
}

static void img_cleanup_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_DELETE) {
        lv_obj_t *img = lv_event_get_target(e);
        // 检查是否需要清理
        if (lv_obj_has_flag(img, LV_OBJ_FLAG_USER_1)) {
            lv_img_dsc_t *image_dsc = (lv_img_dsc_t *)lv_obj_get_user_data(img);
            if (image_dsc) {
                // 释放图像数据
                if (image_dsc->data) {
                    lv_mem_free((void *)image_dsc->data);
                }
                // 释放描述符结构体
                lv_mem_free(image_dsc);
                // 清除用户数据
                lv_obj_set_user_data(img, NULL);
            }
        }
    }
}

void ui_music_artist_handler(char *song_info)
{

    if (!song_info) {
        return;
    }

    char *artist_and_name = lvgl_module_msg_get_ptr(GUI_SONGS_MSG_ID_MUSIC_ARTIST_AND_NAME, strlen(song_info) + 1);
    if (!artist_and_name) {
        return;
    }
    strncpy(artist_and_name, song_info, strlen(song_info));
    artist_and_name[strlen(song_info)] = '\0';
    char *copy_str = strdup(artist_and_name);
    if (!copy_str) {
        free(artist_and_name);
        return;
    }

    char *artist = NULL;
    char *title = NULL;

    // 查找最后一个 '/' 的位置
    char *last_slash = strrchr(copy_str, '/');

    if (last_slash) {
        *last_slash = '\0';
        artist = strdup(copy_str);
        title = strdup(last_slash + 1);
        *last_slash = '/';
    } else {
        title = strdup(copy_str);
        artist = strdup("");
    }

    free(copy_str);

    if (artist && title) {
        printf("Artist: %s, Title: %s\n", artist, title);

        char *song_name = (char *)malloc(strlen(title) + 1);
        strncpy(song_name, title, strlen(title));
        song_name[strlen(title)] = '\0';
        char *song_artist = (char *)malloc(strlen(artist) + 1);
        strncpy(song_artist, artist, strlen(artist));
        song_artist[strlen(artist)] = '\0';

        free(artist);
        free(title);

        // 使用 lyrics 方式显示歌名和歌手
        int ret = lvgl_rpc_post_func(music_player_song_info_update, 2, song_name, song_artist); //title, artist);
        if (ret != 0) {
            free(song_name);
            free(song_artist);
            return;
        }
    } else {
        if (artist) {
            free(artist);
        }
        if (title) {
            free(title);
        }
        printf("Failed to parse song info\n");
    }
    lvgl_module_msg_send_ptr(artist_and_name, 0); //最后再发送字符串，发送成功后内部会释放指针，无需再释放
    return;
}

void ui_music_lyrics_handler(char *song_lyrics)
{
    if (!song_lyrics) {
        return;
    }
    gui_scr_t *current_screen = gui_scr_get_act();
    if (!current_screen) {
        printf("No active screen found\n");
        return;
    }
    int32_t current_screen_id = gui_scr_get_id(current_screen);
    if (current_screen_id == GUI_SCREEN_MUSIC_PLAYER) {
        char *lyrics = (char *)malloc(strlen(song_lyrics) + 1);
        strncpy(lyrics, song_lyrics, strlen(song_lyrics));
        lyrics[strlen(song_lyrics)] = '\0';
        extern void lv_example_lyrics_text_input(char *new_text);
        int ret = lvgl_rpc_post_func(lv_example_lyrics_text_input, 1, lyrics);
        if (ret != 0) {
            free(lyrics);
        }
    } else {
        //非播放页面采用模型更新的方式
        char *lyrics = lvgl_module_msg_get_ptr(GUI_SONGS_MSG_ID_MUSIC_LYRICS, strlen(song_lyrics) + 1);
        strncpy(lyrics, song_lyrics, strlen(song_lyrics));
        lyrics[strlen(song_lyrics)] = '\0';
        lvgl_module_msg_send_ptr(lyrics, 0);
    }
}

void ui_music_volume_handler(int volume)
{
    lvgl_module_msg_send_value(GUI_SONGS_MSG_ID_PLAYER_VOLUME, volume, 0);
}

//注册页面加载卸载回调
static int gui_src_action_music_player(int action)
{
    printf("--->%s()----->%d, action: %d\n", __func__, __LINE__, action);

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        // UI主动获取当前音乐播放状态
        if (bt_get_total_connect_dev() > 0) {
            bt_cmd_prepare(USER_CTRL_AVCTP_OPID_GET_PLAY_TIME, 0, NULL); //获取音乐播放等信息
            bt_cmd_prepare(USER_CTRL_BIP_GET_IMAGE, 0, NULL);//获取专辑照片
        }
#ifdef UI_MUSIC_DYNAMIC_BACKGROUND
        //启用动态背景，从SD卡中加载背景视频
        if (storage_device_ready()) {
            logo_show(CONFIG_BACKGROUND_AVI_PATH, NULL, 0xffff,  NULL);
        }

#endif
        break;
    case GUI_SCREEN_ACTION_UNLOAD:
#ifdef UI_MUSIC_DYNAMIC_BACKGROUND
        //停止动态背景播放
        if (storage_device_ready()) {
            logo_stop(NULL);
        }
#endif
#if LV_USE_LYRICS
        lyrics_example_clean();
        music_player_song_info_lyrics_clean();
#endif
        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_MUSIC_PLAYER)
.onchange = gui_src_action_music_player,
};

static int gui_src_action_sys_menu(int action)
{
    printf("--->%s()----->%d, action: %d\n", __func__, __LINE__, action);

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        // UI主动获取当前音乐播放状态
        if (bt_get_total_connect_dev() > 0) {
            bt_cmd_prepare(USER_CTRL_AVCTP_OPID_GET_PLAY_TIME, 0, NULL); //获取音乐播放等信息更新状态栏
            bt_cmd_prepare(USER_CTRL_BIP_GET_IMAGE, 0, NULL);//获取专辑照片更新状态栏

            gui_msg_data_t *song_data = gui_msg_get(GUI_SONGS_MSG_ID_MUSIC_ARTIST_AND_NAME);
            if (song_data) { //name_data->value_string != NULL)
                if (song_data->value_string != NULL) {
                    char *song_info = (char *)malloc(strlen(song_data->value_string) + 1);
                    strncpy(song_info, song_data->value_string, strlen(song_data->value_string));
                    song_info[strlen(song_data->value_string)] = '\0';
                    sys_menu_song_info_update(song_info);
                }
            }
        }
        break;
    case GUI_SCREEN_ACTION_UNLOAD:
#if LV_USE_LYRICS
        sys_menu_song_info_lyrics_clean();
#endif

        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_SYS_MENU)
.onchange = gui_src_action_sys_menu,
};

#endif
