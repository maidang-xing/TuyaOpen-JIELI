#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_events/i18n_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"

static const char *page_map_imgList_gear_mode_imgs[3] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\SPORT.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\TTFAR.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\FREE.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000075.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000076.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000077.zip"
#endif
};
static const char *page_map_imgList_bluetooth_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_25.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_26.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000079.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00007a.zip"
#endif
};
static const char *page_map_imgList_phone_bl_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_23.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_24.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00007b.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00007c.zip"
#endif
};
static const char *page_map_imgList_gps_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_29.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_30.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00007d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00007e.zip"
#endif
};
static const char *page_map_imgList_networksignal_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_27.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_28.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00007f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000080.zip"
#endif
};
static const char *page_map_imgList_soc_beam_imgs[3] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_20.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_21.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_22.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000083.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000084.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000085.zip"
#endif
};
static const char *page_map_imglist_bat_imgs[100] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_001.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_002.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_003.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_004.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_005.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_006.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_007.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_008.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_009.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_010.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_011.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_012.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_013.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_014.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_015.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_016.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_017.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_018.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_019.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_020.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_021.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_022.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_023.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_024.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_025.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_026.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_027.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_028.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_029.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_030.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_031.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_032.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_033.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_034.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_035.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_036.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_037.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_038.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_039.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_040.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_041.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_042.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_043.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_044.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_045.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_046.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_047.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_048.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_049.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_050.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_051.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_052.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_053.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_054.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_055.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_056.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_057.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_058.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_059.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_060.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_061.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_062.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_063.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_064.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_065.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_066.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_067.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_068.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_069.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_070.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_071.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_072.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_073.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_074.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_075.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_076.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_077.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_078.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_079.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_080.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_081.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_082.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_083.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_084.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_085.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_086.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_087.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_088.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_089.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_090.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_091.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_092.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_093.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_094.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_095.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_096.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_097.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_098.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_099.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_100.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000086.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000087.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000088.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000089.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00008a.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00008b.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00008c.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00008d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00008e.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00008f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000090.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000091.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000092.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000093.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000094.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000095.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000096.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000097.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000098.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000099.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00009a.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00009b.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00009c.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00009d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00009e.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00009f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000a0.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000a1.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000a2.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000a3.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000a4.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000a5.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000a6.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000a7.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000a8.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000a9.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000aa.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ab.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ac.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ad.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ae.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000af.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000b0.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000b1.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000b2.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000b3.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000b4.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000b5.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000b6.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000b7.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000b8.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000b9.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ba.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000bb.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000bc.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000bd.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000be.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000bf.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000c0.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000c1.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000c2.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000c3.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000c4.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000c5.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000c6.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000c7.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000c8.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000c9.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ca.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000cb.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000cc.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000cd.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ce.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000cf.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000d0.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000d1.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000d2.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000d3.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000d4.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000d5.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000d6.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000d7.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000d8.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000d9.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000da.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000db.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000dc.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000dd.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000de.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000df.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000e0.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000e1.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000e2.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000e3.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000e4.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000e5.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000e6.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000e7.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000e8.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000e9.zip"
#endif
};

lv_obj_t *setup_scr_page_map(lv_ui *ui)
{
    lv_ui_page_map *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAGE_MAP);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_page_map));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_page_map));
        ui->page_map = ui_scr;
    }

    //Write codes page_map
    ui_scr->page_map = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(ui_scr->page_map, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map, GUI_CTRL_SCR);

    //Set style for page_map. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_border_color(ui_scr->page_map, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->page_map, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_view_1
    ui_scr->page_map_view_1 = lv_obj_create(ui_scr->page_map);
    lv_obj_set_pos(ui_scr->page_map_view_1, 0, 0);
    lv_obj_set_size(ui_scr->page_map_view_1, 800, 70);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_view_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_view_1, GUI_CTRL_CONT);

    //Set style for page_map_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_view_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->page_map_view_1, 51, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for page_map_view_1
    lv_obj_remove_style(ui_scr->page_map_view_1, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes page_map_imgList_gear_mode
    ui_scr->page_map_imgList_gear_mode = lv_imglist_create(ui_scr->page_map_view_1);
    lv_obj_set_pos(ui_scr->page_map_imgList_gear_mode, 158, 19);
    lv_obj_set_size(ui_scr->page_map_imgList_gear_mode, 84, 32);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_imgList_gear_mode, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_imgList_gear_mode, GUI_CTRL_IMGLIST);

    //Set style for page_map_imgList_gear_mode. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_imgList_gear_mode, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_imglist_set_src(ui_scr->page_map_imgList_gear_mode, (const void **) page_map_imgList_gear_mode_imgs, 3);
    lv_imglist_set_act(ui_scr->page_map_imgList_gear_mode, 0);

    //Write codes page_map_lbl_time
    ui_scr->page_map_lbl_time = lv_label_create(ui_scr->page_map_view_1);
    lv_label_set_text(ui_scr->page_map_lbl_time, "10:30");
    lv_label_set_long_mode(ui_scr->page_map_lbl_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_time, 314, 10);
    lv_obj_set_size(ui_scr->page_map_lbl_time, 96, 50);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_time, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_time, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_time. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_time, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_scr->page_map_lbl_time, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->page_map_lbl_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->page_map_lbl_time, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->page_map_lbl_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_time, &lv_font_montserratMedium_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_time, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_img_weather
    ui_scr->page_map_img_weather = lv_img_create(ui_scr->page_map_view_1);
    lv_img_set_src(ui_scr->page_map_img_weather, gui_get_res_path(GUI_RES_TEM_01_PNG));
    lv_img_set_pivot(ui_scr->page_map_img_weather, 0, 0);
    lv_img_set_angle(ui_scr->page_map_img_weather, 0);
    lv_img_set_zoom(ui_scr->page_map_img_weather, 256);
    lv_obj_set_pos(ui_scr->page_map_img_weather, 448, 12);
    lv_obj_set_size(ui_scr->page_map_img_weather, 42, 40);
    lv_obj_add_flag(ui_scr->page_map_img_weather, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_map_img_weather, GUI_CTRL_IMG);

    //Set style for page_map_img_weather. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_img_weather, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_lbl_temp
    ui_scr->page_map_lbl_temp = lv_label_create(ui_scr->page_map_view_1);
    lv_label_set_text(ui_scr->page_map_lbl_temp, "25°C");
    lv_label_set_long_mode(ui_scr->page_map_lbl_temp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_temp, 499, 10);
    lv_obj_set_size(ui_scr->page_map_lbl_temp, 86, 50);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_temp, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_temp, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_temp. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_temp, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_scr->page_map_lbl_temp, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->page_map_lbl_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->page_map_lbl_temp, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->page_map_lbl_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_temp, &lv_font_montserratMedium_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_temp, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_imgList_bluetooth
    ui_scr->page_map_imgList_bluetooth = lv_imglist_create(ui_scr->page_map_view_1);
    lv_obj_set_pos(ui_scr->page_map_imgList_bluetooth, 619, 15);
    lv_obj_set_size(ui_scr->page_map_imgList_bluetooth, 40, 40);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_imgList_bluetooth, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_imgList_bluetooth, GUI_CTRL_IMGLIST);
    lv_imglist_set_src(ui_scr->page_map_imgList_bluetooth, (const void **) page_map_imgList_bluetooth_imgs, 2);
    lv_imglist_set_act(ui_scr->page_map_imgList_bluetooth, 0);

    //Write codes page_map_imgList_phone_bl
    ui_scr->page_map_imgList_phone_bl = lv_imglist_create(ui_scr->page_map_view_1);
    lv_obj_set_pos(ui_scr->page_map_imgList_phone_bl, 663, 15);
    lv_obj_set_size(ui_scr->page_map_imgList_phone_bl, 40, 40);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_imgList_phone_bl, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_imgList_phone_bl, GUI_CTRL_IMGLIST);

    //Set style for page_map_imgList_phone_bl. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_imgList_phone_bl, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_imglist_set_src(ui_scr->page_map_imgList_phone_bl, (const void **) page_map_imgList_phone_bl_imgs, 2);
    lv_imglist_set_act(ui_scr->page_map_imgList_phone_bl, 0);

    //Write codes page_map_imgList_gps
    ui_scr->page_map_imgList_gps = lv_imglist_create(ui_scr->page_map_view_1);
    lv_obj_set_pos(ui_scr->page_map_imgList_gps, 703, 15);
    lv_obj_set_size(ui_scr->page_map_imgList_gps, 40, 40);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_imgList_gps, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_imgList_gps, GUI_CTRL_IMGLIST);
    lv_imglist_set_src(ui_scr->page_map_imgList_gps, (const void **) page_map_imgList_gps_imgs, 2);
    lv_imglist_set_act(ui_scr->page_map_imgList_gps, 0);

    //Write codes page_map_imgList_networksignal
    ui_scr->page_map_imgList_networksignal = lv_imglist_create(ui_scr->page_map_view_1);
    lv_obj_set_pos(ui_scr->page_map_imgList_networksignal, 747, 15);
    lv_obj_set_size(ui_scr->page_map_imgList_networksignal, 40, 40);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_imgList_networksignal, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_imgList_networksignal, GUI_CTRL_IMGLIST);
    lv_imglist_set_src(ui_scr->page_map_imgList_networksignal, (const void **) page_map_imgList_networksignal_imgs, 2);
    lv_imglist_set_act(ui_scr->page_map_imgList_networksignal, 0);

    //Write codes page_map_img_ready
    ui_scr->page_map_img_ready = lv_img_create(ui_scr->page_map_view_1);
    lv_img_set_src(ui_scr->page_map_img_ready, gui_get_res_path(GUI_RES_READY_PNG));
    lv_img_set_pivot(ui_scr->page_map_img_ready, 0, 0);
    lv_img_set_angle(ui_scr->page_map_img_ready, 0);
    lv_img_set_zoom(ui_scr->page_map_img_ready, 256);
    lv_obj_set_pos(ui_scr->page_map_img_ready, 26, 24);
    lv_obj_set_size(ui_scr->page_map_img_ready, 108, 24);
    lv_obj_add_flag(ui_scr->page_map_img_ready, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_map_img_ready, GUI_CTRL_IMG);

    //Set style for page_map_img_ready. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_img_ready, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_view_2
    ui_scr->page_map_view_2 = lv_obj_create(ui_scr->page_map);
    lv_obj_set_pos(ui_scr->page_map_view_2, 0, 419);
    lv_obj_set_size(ui_scr->page_map_view_2, 800, 60);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_view_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_view_2, GUI_CTRL_CONT);

    //Set style for page_map_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_view_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->page_map_view_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for page_map_view_2
    lv_obj_remove_style(ui_scr->page_map_view_2, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes page_map_lbl_endurance
    ui_scr->page_map_lbl_endurance = lv_label_create(ui_scr->page_map_view_2);
    lv_label_set_text(ui_scr->page_map_lbl_endurance, "100km");
    lv_label_set_long_mode(ui_scr->page_map_lbl_endurance, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_endurance, 74, 0);
    lv_obj_set_size(ui_scr->page_map_lbl_endurance, 127, 42);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_endurance, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_endurance, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_endurance. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_endurance, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_scr->page_map_lbl_endurance, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->page_map_lbl_endurance, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->page_map_lbl_endurance, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->page_map_lbl_endurance, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_endurance, &lv_font_montserratMedium_28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_endurance, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_img_charge
    ui_scr->page_map_img_charge = lv_img_create(ui_scr->page_map_view_2);
    lv_img_set_src(ui_scr->page_map_img_charge, gui_get_res_path(GUI_RES_LAMP_19_PNG));
    lv_img_set_pivot(ui_scr->page_map_img_charge, 0, 0);
    lv_img_set_angle(ui_scr->page_map_img_charge, 0);
    lv_img_set_zoom(ui_scr->page_map_img_charge, 256);
    lv_obj_set_pos(ui_scr->page_map_img_charge, 20, 11);
    lv_obj_set_size(ui_scr->page_map_img_charge, 40, 40);
    lv_obj_add_flag(ui_scr->page_map_img_charge, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_map_img_charge, GUI_CTRL_IMG);

    //Set style for page_map_img_charge. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_img_charge, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_imgList_soc_beam
    ui_scr->page_map_imgList_soc_beam = lv_imglist_create(ui_scr->page_map_view_2);
    lv_obj_set_pos(ui_scr->page_map_imgList_soc_beam, 309, 10);
    lv_obj_set_size(ui_scr->page_map_imgList_soc_beam, 40, 40);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_imgList_soc_beam, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_imgList_soc_beam, GUI_CTRL_IMGLIST);

    //Set style for page_map_imgList_soc_beam. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_imgList_soc_beam, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_imglist_set_src(ui_scr->page_map_imgList_soc_beam, (const void **) page_map_imgList_soc_beam_imgs, 3);
    lv_imglist_set_act(ui_scr->page_map_imgList_soc_beam, 1);

    //Write codes page_map_lbl_bat
    ui_scr->page_map_lbl_bat = lv_label_create(ui_scr->page_map_view_2);
    lv_label_set_text(ui_scr->page_map_lbl_bat, "100%");
    lv_label_set_long_mode(ui_scr->page_map_lbl_bat, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_bat, 365, 0);
    lv_obj_set_size(ui_scr->page_map_lbl_bat, 85, 42);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_bat, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_bat, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_bat. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_bat, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_scr->page_map_lbl_bat, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->page_map_lbl_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->page_map_lbl_bat, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->page_map_lbl_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_bat, &lv_font_montserratMedium_28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_bat, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_imglist_bat
    ui_scr->page_map_imglist_bat = lv_imglist_create(ui_scr->page_map_view_2);
    lv_obj_set_pos(ui_scr->page_map_imglist_bat, 462, 24);
    lv_obj_set_size(ui_scr->page_map_imglist_bat, 160, 12);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_imglist_bat, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_imglist_bat, GUI_CTRL_IMGLIST);
    lv_imglist_set_src(ui_scr->page_map_imglist_bat, (const void **) page_map_imglist_bat_imgs, 100);
    lv_imglist_set_act(ui_scr->page_map_imglist_bat, 99);

    //Write codes page_map_lbl_odo_num
    ui_scr->page_map_lbl_odo_num = lv_label_create(ui_scr->page_map_view_2);
    lv_label_set_text(ui_scr->page_map_lbl_odo_num, "10260km");
    lv_label_set_long_mode(ui_scr->page_map_lbl_odo_num, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_odo_num, 634, 5);
    lv_obj_set_size(ui_scr->page_map_lbl_odo_num, 159, 50);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_odo_num, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_odo_num, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_odo_num. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_odo_num, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_scr->page_map_lbl_odo_num, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->page_map_lbl_odo_num, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->page_map_lbl_odo_num, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->page_map_lbl_odo_num, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_odo_num, &lv_font_montserratMedium_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->page_map_lbl_odo_num, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_odo_num, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write Timer page_map_timer_1
    if (ui_scr->page_map_timer_1 != NULL) {
        lv_timer_del(ui_scr->page_map_timer_1);
    }
    ui_scr->page_map_timer_1 = lv_timer_create(page_map_timer_1_timer_cb, 50, "");
    lv_timer_set_repeat_count(ui_scr->page_map_timer_1, -1);

    //Write codes page_map_view_3
    ui_scr->page_map_view_3 = lv_obj_create(ui_scr->page_map);
    lv_obj_set_pos(ui_scr->page_map_view_3, 27, 125);
    lv_obj_set_size(ui_scr->page_map_view_3, 207, 117);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_view_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_view_3, GUI_CTRL_CONT);

    //Set style for page_map_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->page_map_view_3, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->page_map_view_3, lv_color_make(0x08, 0x17, 0x27), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->page_map_view_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for page_map_view_3
    lv_obj_remove_style(ui_scr->page_map_view_3, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes page_map_lbl_1
    ui_scr->page_map_lbl_1 = lv_label_create(ui_scr->page_map_view_3);
    lv_label_set_text(ui_scr->page_map_lbl_1, "328");
    lv_label_set_long_mode(ui_scr->page_map_lbl_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_1, 81, 17);
    lv_obj_set_size(ui_scr->page_map_lbl_1, 72, 38);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_1, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_1, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_1, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->page_map_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_lbl_2
    ui_scr->page_map_lbl_2 = lv_label_create(ui_scr->page_map_view_3);
    lv_label_set_text(ui_scr->page_map_lbl_2, "22");
    lv_label_set_long_mode(ui_scr->page_map_lbl_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_2, 4, 65);
    lv_obj_set_size(ui_scr->page_map_lbl_2, 72, 38);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_2, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_2, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_2, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->page_map_lbl_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_2, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_lbl_3
    ui_scr->page_map_lbl_3 = lv_label_create(ui_scr->page_map_view_3);
    lv_label_set_text(ui_scr->page_map_lbl_3, "45");
    lv_label_set_long_mode(ui_scr->page_map_lbl_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_3, 59, 65);
    lv_obj_set_size(ui_scr->page_map_lbl_3, 72, 38);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_3, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_3, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_3, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->page_map_lbl_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_3, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_lbl_4
    ui_scr->page_map_lbl_4 = lv_label_create(ui_scr->page_map_view_3);
    lv_label_set_text(ui_scr->page_map_lbl_4, "12:20");
    lv_label_set_long_mode(ui_scr->page_map_lbl_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_4, 124, 65);
    lv_obj_set_size(ui_scr->page_map_lbl_4, 72, 38);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_4, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_4, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_4, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_4, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->page_map_lbl_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_4, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_img_1
    ui_scr->page_map_img_1 = lv_img_create(ui_scr->page_map_view_3);
    lv_img_set_src(ui_scr->page_map_img_1, gui_get_res_path(GUI_RES_LAMP_01_PNG));
    lv_img_set_pivot(ui_scr->page_map_img_1, 0, 0);
    lv_img_set_angle(ui_scr->page_map_img_1, 0);
    lv_img_set_zoom(ui_scr->page_map_img_1, 256);
    lv_obj_set_pos(ui_scr->page_map_img_1, 18, 15);
    lv_obj_set_size(ui_scr->page_map_img_1, 40, 40);
    lv_obj_add_flag(ui_scr->page_map_img_1, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_map_img_1, GUI_CTRL_IMG);

    // Write Timer page_map_timer_2
    if (ui_scr->page_map_timer_2 != NULL) {
        lv_timer_del(ui_scr->page_map_timer_2);
    }
    ui_scr->page_map_timer_2 = lv_timer_create(page_map_timer_2_timer_cb, 5000, "");
    lv_timer_set_repeat_count(ui_scr->page_map_timer_2, -1);

    //Write codes page_map_btn_1
    ui_scr->page_map_btn_1 = lv_btn_create(ui_scr->page_map);
    lv_obj_set_pos(ui_scr->page_map_btn_1, 340, 80);
    lv_obj_set_size(ui_scr->page_map_btn_1, 58, 36);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_btn_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_btn_1, GUI_CTRL_BUTTON);

    //Set style for page_map_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_btn_1, lv_color_make(0x40, 0xEC, 0xC2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_btn_1, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for page_map_btn_1
    lv_obj_remove_style(ui_scr->page_map_btn_1, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    ui_scr->page_map_btn_1_label = lv_label_create(ui_scr->page_map_btn_1);
    lv_label_set_text(ui_scr->page_map_btn_1_label, "back");
    lv_obj_set_style_pad_all(ui_scr->page_map_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->page_map_btn_1_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes page_map_btn_2
    ui_scr->page_map_btn_2 = lv_btn_create(ui_scr->page_map);
    lv_obj_set_pos(ui_scr->page_map_btn_2, 404, 80);
    lv_obj_set_size(ui_scr->page_map_btn_2, 58, 36);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_btn_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_btn_2, GUI_CTRL_BUTTON);

    //Set style for page_map_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_btn_2, lv_color_make(0x40, 0xEC, 0xC2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for page_map_btn_2
    lv_obj_remove_style(ui_scr->page_map_btn_2, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    ui_scr->page_map_btn_2_label = lv_label_create(ui_scr->page_map_btn_2);
    lv_label_set_text(ui_scr->page_map_btn_2_label, "next");
    lv_obj_set_style_pad_all(ui_scr->page_map_btn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->page_map_btn_2_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes page_map_view_4
    ui_scr->page_map_view_4 = lv_obj_create(ui_scr->page_map);
    lv_obj_set_pos(ui_scr->page_map_view_4, 540, 74);
    lv_obj_set_size(ui_scr->page_map_view_4, 245, 168);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_view_4, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_view_4, GUI_CTRL_CONT);

    //Set style for page_map_view_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->page_map_view_4, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->page_map_view_4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->page_map_view_4, 128, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for page_map_view_4
    lv_obj_remove_style(ui_scr->page_map_view_4, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes page_map_lbl_5
    ui_scr->page_map_lbl_5 = lv_label_create(ui_scr->page_map_view_4);
    lv_label_set_text(ui_scr->page_map_lbl_5, "resolution:");
    lv_label_set_long_mode(ui_scr->page_map_lbl_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_5, 4, 2);
    lv_obj_set_size(ui_scr->page_map_lbl_5, 115, 29);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_5, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_5, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_5, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->page_map_lbl_5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_5, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_5, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_lbl_6
    ui_scr->page_map_lbl_6 = lv_label_create(ui_scr->page_map_view_4);
    lv_label_set_text(ui_scr->page_map_lbl_6, "fps:max,min,avg");
    lv_label_set_long_mode(ui_scr->page_map_lbl_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_6, 4, 39);
    lv_obj_set_size(ui_scr->page_map_lbl_6, 219, 34);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_6, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_6, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_6, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->page_map_lbl_6, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_6, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_6, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_lbl_7
    ui_scr->page_map_lbl_7 = lv_label_create(ui_scr->page_map_view_4);
    lv_label_set_text(ui_scr->page_map_lbl_7, "0,0,0");
    lv_label_set_long_mode(ui_scr->page_map_lbl_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_7, 4, 69);
    lv_obj_set_size(ui_scr->page_map_lbl_7, 230, 28);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_7, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_7, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_7, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->page_map_lbl_7, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_7, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_7, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_lbl_8
    ui_scr->page_map_lbl_8 = lv_label_create(ui_scr->page_map_view_4);
    lv_label_set_text(ui_scr->page_map_lbl_8, "jpgsize:max,min,avg");
    lv_label_set_long_mode(ui_scr->page_map_lbl_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_8, 4, 96);
    lv_obj_set_size(ui_scr->page_map_lbl_8, 238, 34);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_8, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_8, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_8, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->page_map_lbl_8, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_8, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_8, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_lbl_9
    ui_scr->page_map_lbl_9 = lv_label_create(ui_scr->page_map_view_4);
    lv_label_set_text(ui_scr->page_map_lbl_9, "0,0,0");
    lv_label_set_long_mode(ui_scr->page_map_lbl_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_9, 4, 127);
    lv_obj_set_size(ui_scr->page_map_lbl_9, 230, 28);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_9, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_9, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_9, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->page_map_lbl_9, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_9, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_9, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_lbl_10
    ui_scr->page_map_lbl_10 = lv_label_create(ui_scr->page_map_view_4);
    lv_label_set_text(ui_scr->page_map_lbl_10, "800x400");
    lv_label_set_long_mode(ui_scr->page_map_lbl_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_map_lbl_10, 114, 3);
    lv_obj_set_size(ui_scr->page_map_lbl_10, 117, 29);
    lv_obj_set_scrollbar_mode(ui_scr->page_map_lbl_10, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_map_lbl_10, GUI_CTRL_LABEL);

    //Set style for page_map_lbl_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_map_lbl_10, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->page_map_lbl_10, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_map_lbl_10, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_map_lbl_10, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_map_img_2
    ui_scr->page_map_img_2 = lv_img_create(ui_scr->page_map);
    lv_img_set_src(ui_scr->page_map_img_2, gui_get_res_path(GUI_RES_TIPS_PNG));
    lv_img_set_pivot(ui_scr->page_map_img_2, 0, 0);
    lv_img_set_angle(ui_scr->page_map_img_2, 0);
    lv_img_set_zoom(ui_scr->page_map_img_2, 256);
    lv_obj_set_pos(ui_scr->page_map_img_2, 360, 147);
    lv_obj_set_size(ui_scr->page_map_img_2, 360, 130);
    lv_obj_add_flag(ui_scr->page_map_img_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_scr->page_map_img_2, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_map_img_2, GUI_CTRL_IMG);

    //Set style for page_map_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->page_map_img_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_update_layout(ui_scr->page_map);
    ui_scr->page_map_del = false;
    i18n_refresh_texts(GUI_SCREEN_PAGE_MAP);

    //Init events for screen
    events_init_page_map(ui);
    return ui_scr->page_map;
}
void unload_scr_page_map(lv_ui *ui)
{
    lv_ui_page_map *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAGE_MAP);
    if (ui_scr->page_map_timer_1 != NULL) {
        lv_timer_del(ui_scr->page_map_timer_1);
        ui_scr->page_map_timer_1 = NULL;
    }
    if (ui_scr->page_map_timer_2 != NULL) {
        lv_timer_del(ui_scr->page_map_timer_2);
        ui_scr->page_map_timer_2 = NULL;
    }
    ui_free_scr_ptr(ui, GUI_SCREEN_PAGE_MAP);
}

#endif
