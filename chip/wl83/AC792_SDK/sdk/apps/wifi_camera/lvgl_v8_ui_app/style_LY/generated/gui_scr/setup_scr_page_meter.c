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

static const char *page_meter_imglist_speed_ones_imgs[10] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\0.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\1.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\2.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\3.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\4.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\5.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\6.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\7.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\8.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\9.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000100.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000101.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000102.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000103.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000104.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000105.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000106.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000107.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000108.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000109.zip"
#endif
};
static const char *page_meter_imglist_speed_tens_imgs[10] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\0.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\1.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\2.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\3.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\4.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\5.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\6.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\7.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\8.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\9.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000100.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000101.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000102.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000103.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000104.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000105.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000106.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000107.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000108.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000109.zip"
#endif
};
static const char *page_meter_imgList_high_low_beam_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_06.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_07.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00010a.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00010b.zip"
#endif
};
static const char *page_meter_anim_pwr_l_imgs[99] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_001.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_002.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_003.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_004.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_005.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_006.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_007.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_008.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_009.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_010.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_011.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_012.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_013.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_014.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_015.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_016.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_017.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_018.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_019.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_020.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_021.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_022.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_023.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_024.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_025.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_026.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_027.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_028.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_029.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_030.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_031.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_032.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_034.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_035.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_036.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_037.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_038.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_039.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_040.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_041.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_042.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_043.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_044.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_045.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_046.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_047.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_048.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_049.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_050.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_051.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_052.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_053.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_054.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_055.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_056.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_057.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_058.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_059.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_060.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_061.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_062.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_063.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_064.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_065.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_066.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_067.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_068.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_069.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_070.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_071.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_072.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_073.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_074.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_075.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_076.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_077.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_078.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_079.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_080.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_081.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_082.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_083.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_084.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_085.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_086.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_087.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_088.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_089.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_090.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_091.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_092.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_093.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_094.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_095.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_096.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_097.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_098.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_099.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_100.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00010c.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00010d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00010e.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00010f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000110.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000111.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000112.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000113.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000114.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000115.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000116.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000117.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000118.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000119.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00011a.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00011b.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00011c.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00011d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00011e.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00011f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000120.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000121.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000122.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000123.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000124.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000125.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000126.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000127.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000128.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000129.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00012a.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00012b.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00012c.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00012d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00012e.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00012f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000130.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000131.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000132.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000133.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000134.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000135.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000136.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000137.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000138.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000139.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00013a.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00013b.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00013c.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00013d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00013e.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00013f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000140.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000141.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000142.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000143.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000144.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000145.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000146.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000147.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000148.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000149.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00014a.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00014b.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00014c.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00014d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00014e.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00014f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000150.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000151.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000152.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000153.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000154.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000155.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000156.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000157.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000158.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000159.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00015a.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00015b.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00015c.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00015d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00015e.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00015f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000160.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000161.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000162.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000163.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000164.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000165.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000166.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000167.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000168.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000169.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00016a.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00016b.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00016c.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00016d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00016e.zip"
#endif
};
static const char *page_meter_anim_pwr_r_imgs[99] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_001.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_002.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_003.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_004.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_005.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_006.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_007.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_008.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_009.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_010.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_011.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_012.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_013.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_014.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_015.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_016.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_017.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_018.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_019.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_020.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_021.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_022.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_023.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_024.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_025.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_026.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_027.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_028.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_029.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_030.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_031.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_032.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_033.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_034.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_035.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_036.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_037.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_038.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_039.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_040.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_041.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_042.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_043.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_044.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_045.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_046.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_047.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_048.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_049.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_050.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_051.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_052.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_053.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_054.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_055.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_056.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_057.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_058.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_059.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_060.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_061.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_062.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_063.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_064.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_065.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_066.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_067.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_068.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_069.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_070.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_071.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_072.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_073.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_074.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_075.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_076.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_077.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_078.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_079.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_080.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_081.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_082.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_083.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_084.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_085.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_086.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_087.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_088.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_089.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_090.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_091.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_092.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_093.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_094.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_095.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_096.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_097.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_098.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_099.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00016f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000170.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000171.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000172.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000173.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000174.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000175.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000176.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000177.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000178.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000179.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00017a.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00017b.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00017c.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00017d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00017e.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00017f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000180.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000181.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000182.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000183.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000184.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000185.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000186.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000187.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000188.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000189.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00018a.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00018b.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00018c.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00018d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00018e.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00018f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000190.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000191.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000192.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000193.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000194.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000195.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000196.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000197.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000198.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000199.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00019a.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00019b.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00019c.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00019d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00019e.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00019f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001a0.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001a1.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001a2.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001a3.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001a4.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001a5.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001a6.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001a7.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001a8.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001a9.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001aa.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001ab.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001ac.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001ad.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001ae.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001af.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001b0.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001b1.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001b2.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001b3.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001b4.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001b5.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001b6.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001b7.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001b8.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001b9.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001ba.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001bb.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001bc.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001bd.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001be.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001bf.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001c0.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001c1.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001c2.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001c3.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001c4.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001c5.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001c6.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001c7.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001c8.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001c9.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001ca.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001cb.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001cc.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001cd.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001ce.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001cf.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001d0.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0001d1.zip"
#endif
};
static const char *page_meter_imglist_1_imgs[3] = {
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
static const char *page_meter_imglist_2_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_25.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_26.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000079.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00007a.zip"
#endif
};
static const char *page_meter_imglist_3_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_23.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_24.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00007b.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00007c.zip"
#endif
};
static const char *page_meter_imglist_4_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_29.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_30.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00007d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00007e.zip"
#endif
};
static const char *page_meter_imglist_5_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_27.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_28.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00007f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000080.zip"
#endif
};
static const char *page_meter_imglist_6_imgs[3] = {
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
static const char *page_meter_imglist_bat_imgs[100] = {
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

lv_obj_t *setup_scr_page_meter(lv_ui *ui)
{
    lv_ui_page_meter *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAGE_METER);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_page_meter));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_page_meter));
        ui->page_meter = ui_scr;
    }

    //Write codes page_meter
    ui_scr->page_meter = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter, GUI_CTRL_SCR);

    //Set style for page_meter. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->page_meter, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_scr->page_meter, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->page_meter, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_road_eco
    ui_scr->page_meter_img_road_eco = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_road_eco, gui_get_res_path(GUI_RES_ROAD_ECO_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_road_eco, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_road_eco, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_road_eco, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_road_eco, 0, 215);
    lv_obj_set_size(ui_scr->page_meter_img_road_eco, 800, 266);
    lv_obj_add_flag(ui_scr->page_meter_img_road_eco, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_road_eco, GUI_CTRL_IMG);

    //Set style for page_meter_img_road_eco. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_road_eco, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_arrow_eco
    ui_scr->page_meter_img_arrow_eco = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_arrow_eco, gui_get_res_path(GUI_RES_ARROW_ECO_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_arrow_eco, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_arrow_eco, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_arrow_eco, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_arrow_eco, 330, 312);
    lv_obj_set_size(ui_scr->page_meter_img_arrow_eco, 142, 127);
    lv_obj_add_flag(ui_scr->page_meter_img_arrow_eco, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_arrow_eco, GUI_CTRL_IMG);

    //Set style for page_meter_img_arrow_eco. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_arrow_eco, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_bat_d
    ui_scr->page_meter_img_bat_d = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_bat_d, gui_get_res_path(GUI_RES_BAT_B_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_bat_d, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_bat_d, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_bat_d, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_bat_d, 320, 442);
    lv_obj_set_size(ui_scr->page_meter_img_bat_d, 160, 12);
    lv_obj_add_flag(ui_scr->page_meter_img_bat_d, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_bat_d, GUI_CTRL_IMG);

    //Set style for page_meter_img_bat_d. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_bat_d, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_position
    ui_scr->page_meter_img_position = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_position, gui_get_res_path(GUI_RES_LAMP_02_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_position, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_position, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_position, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_position, 188, 60);
    lv_obj_set_size(ui_scr->page_meter_img_position, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_position, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_position, GUI_CTRL_IMG);

    //Set style for page_meter_img_position. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_position, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_force_touch
    ui_scr->page_meter_img_force_touch = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_force_touch, gui_get_res_path(GUI_RES_LAMP_03_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_force_touch, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_force_touch, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_force_touch, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_force_touch, 572, 60);
    lv_obj_set_size(ui_scr->page_meter_img_force_touch, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_force_touch, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_force_touch, GUI_CTRL_IMG);

    //Set style for page_meter_img_force_touch. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_force_touch, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_right_turn
    ui_scr->page_meter_img_right_turn = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_right_turn, gui_get_res_path(GUI_RES_LAMP_04_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_right_turn, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_right_turn, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_right_turn, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_right_turn, 740, 60);
    lv_obj_set_size(ui_scr->page_meter_img_right_turn, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_right_turn, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_right_turn, GUI_CTRL_IMG);

    //Set style for page_meter_img_right_turn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_right_turn, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_hdc
    ui_scr->page_meter_img_hdc = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_hdc, gui_get_res_path(GUI_RES_LAMP_05_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_hdc, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_hdc, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_hdc, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_hdc, 20, 104);
    lv_obj_set_size(ui_scr->page_meter_img_hdc, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_hdc, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_hdc, GUI_CTRL_IMG);

    //Set style for page_meter_img_hdc. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_hdc, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_auto
    ui_scr->page_meter_img_auto = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_auto, gui_get_res_path(GUI_RES_LAMP_08_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_auto, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_auto, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_auto, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_auto, 188, 104);
    lv_obj_set_size(ui_scr->page_meter_img_auto, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_auto, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_auto, GUI_CTRL_IMG);

    //Set style for page_meter_img_auto. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_auto, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui_scr->page_meter_img_auto, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_box_open
    ui_scr->page_meter_img_box_open = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_box_open, gui_get_res_path(GUI_RES_LAMP_09_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_box_open, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_box_open, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_box_open, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_box_open, 572, 104);
    lv_obj_set_size(ui_scr->page_meter_img_box_open, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_box_open, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_box_open, GUI_CTRL_IMG);

    //Set style for page_meter_img_box_open. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_box_open, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_side_support
    ui_scr->page_meter_img_side_support = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_side_support, gui_get_res_path(GUI_RES_LAMP_10_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_side_support, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_side_support, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_side_support, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_side_support, 622, 104);
    lv_obj_set_size(ui_scr->page_meter_img_side_support, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_side_support, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_side_support, GUI_CTRL_IMG);

    //Set style for page_meter_img_side_support. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_side_support, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_tcs
    ui_scr->page_meter_img_tcs = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_tcs, gui_get_res_path(GUI_RES_LAMP_11_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_tcs, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_tcs, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_tcs, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_tcs, 740, 104);
    lv_obj_set_size(ui_scr->page_meter_img_tcs, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_tcs, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_tcs, GUI_CTRL_IMG);

    //Set style for page_meter_img_tcs. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_tcs, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_abs
    ui_scr->page_meter_img_abs = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_abs, gui_get_res_path(GUI_RES_LAMP_12_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_abs, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_abs, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_abs, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_abs, 140, 148);
    lv_obj_set_size(ui_scr->page_meter_img_abs, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_abs, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_abs, GUI_CTRL_IMG);

    //Set style for page_meter_img_abs. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_abs, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_limping
    ui_scr->page_meter_img_limping = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_limping, gui_get_res_path(GUI_RES_LAMP_13_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_limping, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_limping, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_limping, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_limping, 188, 148);
    lv_obj_set_size(ui_scr->page_meter_img_limping, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_limping, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_limping, GUI_CTRL_IMG);

    //Set style for page_meter_img_limping. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_limping, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_tapLoc
    ui_scr->page_meter_img_tapLoc = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_tapLoc, gui_get_res_path(GUI_RES_LAMP_14_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_tapLoc, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_tapLoc, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_tapLoc, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_tapLoc, 572, 148);
    lv_obj_set_size(ui_scr->page_meter_img_tapLoc, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_tapLoc, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_tapLoc, GUI_CTRL_IMG);

    //Set style for page_meter_img_tapLoc. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_tapLoc, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_car_fault
    ui_scr->page_meter_img_car_fault = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_car_fault, gui_get_res_path(GUI_RES_LAMP_15_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_car_fault, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_car_fault, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_car_fault, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_car_fault, 622, 148);
    lv_obj_set_size(ui_scr->page_meter_img_car_fault, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_car_fault, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_car_fault, GUI_CTRL_IMG);

    //Set style for page_meter_img_car_fault. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_car_fault, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_P_mode
    ui_scr->page_meter_img_P_mode = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_P_mode, gui_get_res_path(GUI_RES_LAMP_16_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_P_mode, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_P_mode, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_P_mode, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_P_mode, 140, 192);
    lv_obj_set_size(ui_scr->page_meter_img_P_mode, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_P_mode, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_P_mode, GUI_CTRL_IMG);

    //Set style for page_meter_img_P_mode. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_P_mode, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_brake_system_fault
    ui_scr->page_meter_img_brake_system_fault = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_brake_system_fault, gui_get_res_path(GUI_RES_LAMP_17_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_brake_system_fault, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_brake_system_fault, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_brake_system_fault, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_brake_system_fault, 622, 192);
    lv_obj_set_size(ui_scr->page_meter_img_brake_system_fault, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_brake_system_fault, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_brake_system_fault, GUI_CTRL_IMG);

    //Set style for page_meter_img_brake_system_fault. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_brake_system_fault, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_cruisework
    ui_scr->page_meter_img_cruisework = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_cruisework, gui_get_res_path(GUI_RES_LAMP_18_PAGE_METER_IMG_CRUISEWORK_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_cruisework, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_cruisework, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_cruisework, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_cruisework, 477, 16);
    lv_obj_set_size(ui_scr->page_meter_img_cruisework, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_cruisework, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_cruisework, GUI_CTRL_IMG);

    //Set style for page_meter_img_cruisework. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_cruisework, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_lbl_temp
    ui_scr->page_meter_lbl_temp = lv_label_create(ui_scr->page_meter);
    lv_label_set_text(ui_scr->page_meter_lbl_temp, "25°C");
    lv_label_set_long_mode(ui_scr->page_meter_lbl_temp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_meter_lbl_temp, 70, 8);
    lv_obj_set_size(ui_scr->page_meter_lbl_temp, 86, 50);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_lbl_temp, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_lbl_temp, GUI_CTRL_LABEL);

    //Set style for page_meter_lbl_temp. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_lbl_temp, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_scr->page_meter_lbl_temp, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->page_meter_lbl_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->page_meter_lbl_temp, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->page_meter_lbl_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_meter_lbl_temp, &lv_font_montserratMedium_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_meter_lbl_temp, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_lbl_time
    ui_scr->page_meter_lbl_time = lv_label_create(ui_scr->page_meter);
    lv_label_set_text(ui_scr->page_meter_lbl_time, "10:30");
    lv_label_set_long_mode(ui_scr->page_meter_lbl_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_meter_lbl_time, 699, 8);
    lv_obj_set_size(ui_scr->page_meter_lbl_time, 96, 50);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_lbl_time, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_lbl_time, GUI_CTRL_LABEL);

    //Set style for page_meter_lbl_time. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_lbl_time, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_scr->page_meter_lbl_time, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->page_meter_lbl_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->page_meter_lbl_time, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->page_meter_lbl_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_meter_lbl_time, &lv_font_montserratMedium_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_meter_lbl_time, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_lbl_odo_num
    ui_scr->page_meter_lbl_odo_num = lv_label_create(ui_scr->page_meter);
    lv_label_set_text(ui_scr->page_meter_lbl_odo_num, "10260km");
    lv_label_set_long_mode(ui_scr->page_meter_lbl_odo_num, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_meter_lbl_odo_num, 637, 418);
    lv_obj_set_size(ui_scr->page_meter_lbl_odo_num, 159, 50);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_lbl_odo_num, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_lbl_odo_num, GUI_CTRL_LABEL);

    //Set style for page_meter_lbl_odo_num. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_lbl_odo_num, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_scr->page_meter_lbl_odo_num, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->page_meter_lbl_odo_num, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->page_meter_lbl_odo_num, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->page_meter_lbl_odo_num, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_meter_lbl_odo_num, &lv_font_montserratMedium_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->page_meter_lbl_odo_num, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_meter_lbl_odo_num, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_lbl_odo
    ui_scr->page_meter_lbl_odo = lv_label_create(ui_scr->page_meter);
    lv_label_set_text(ui_scr->page_meter_lbl_odo, "ODO");
    lv_label_set_long_mode(ui_scr->page_meter_lbl_odo, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_meter_lbl_odo, 580, 424);
    lv_obj_set_size(ui_scr->page_meter_lbl_odo, 96, 40);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_lbl_odo, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_lbl_odo, GUI_CTRL_LABEL);

    //Set style for page_meter_lbl_odo. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_lbl_odo, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_scr->page_meter_lbl_odo, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->page_meter_lbl_odo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->page_meter_lbl_odo, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->page_meter_lbl_odo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_meter_lbl_odo, &lv_font_montserratMedium_21, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_meter_lbl_odo, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_lbl_bat
    ui_scr->page_meter_lbl_bat = lv_label_create(ui_scr->page_meter);
    lv_label_set_text(ui_scr->page_meter_lbl_bat, "100%");
    lv_label_set_long_mode(ui_scr->page_meter_lbl_bat, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_meter_lbl_bat, 490, 420);
    lv_obj_set_size(ui_scr->page_meter_lbl_bat, 85, 42);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_lbl_bat, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_lbl_bat, GUI_CTRL_LABEL);

    //Set style for page_meter_lbl_bat. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_lbl_bat, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_scr->page_meter_lbl_bat, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->page_meter_lbl_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->page_meter_lbl_bat, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->page_meter_lbl_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_meter_lbl_bat, &lv_font_montserratMedium_28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_meter_lbl_bat, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_lbl_endurance
    ui_scr->page_meter_lbl_endurance = lv_label_create(ui_scr->page_meter);
    lv_label_set_text(ui_scr->page_meter_lbl_endurance, "100km");
    lv_label_set_long_mode(ui_scr->page_meter_lbl_endurance, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_meter_lbl_endurance, 70, 420);
    lv_obj_set_size(ui_scr->page_meter_lbl_endurance, 127, 42);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_lbl_endurance, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_lbl_endurance, GUI_CTRL_LABEL);

    //Set style for page_meter_lbl_endurance. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_lbl_endurance, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_scr->page_meter_lbl_endurance, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->page_meter_lbl_endurance, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->page_meter_lbl_endurance, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->page_meter_lbl_endurance, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_meter_lbl_endurance, &lv_font_montserratMedium_28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_meter_lbl_endurance, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_imglist_speed_ones
    ui_scr->page_meter_imglist_speed_ones = lv_imglist_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_imglist_speed_ones, 406, 100);
    lv_obj_set_size(ui_scr->page_meter_imglist_speed_ones, 132, 132);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_imglist_speed_ones, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_imglist_speed_ones, GUI_CTRL_IMGLIST);

    //Set style for page_meter_imglist_speed_ones. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_imglist_speed_ones, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_imglist_set_src(ui_scr->page_meter_imglist_speed_ones, (const void **) page_meter_imglist_speed_ones_imgs, 10);
    lv_imglist_set_act(ui_scr->page_meter_imglist_speed_ones, 0);

    //Write codes page_meter_imglist_speed_tens
    ui_scr->page_meter_imglist_speed_tens = lv_imglist_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_imglist_speed_tens, 262, 100);
    lv_obj_set_size(ui_scr->page_meter_imglist_speed_tens, 132, 132);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_imglist_speed_tens, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_imglist_speed_tens, GUI_CTRL_IMGLIST);

    //Set style for page_meter_imglist_speed_tens. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_imglist_speed_tens, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_imglist_set_src(ui_scr->page_meter_imglist_speed_tens, (const void **) page_meter_imglist_speed_tens_imgs, 10);
    lv_imglist_set_act(ui_scr->page_meter_imglist_speed_tens, 0);

    //Write codes page_meter_lbl_km
    ui_scr->page_meter_lbl_km = lv_label_create(ui_scr->page_meter);
    lv_label_set_text(ui_scr->page_meter_lbl_km, "km/h");
    lv_label_set_long_mode(ui_scr->page_meter_lbl_km, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_meter_lbl_km, 370, 244);
    lv_obj_set_size(ui_scr->page_meter_lbl_km, 73, 36);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_lbl_km, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_lbl_km, GUI_CTRL_LABEL);

    //Set style for page_meter_lbl_km. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_lbl_km, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_scr->page_meter_lbl_km, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->page_meter_lbl_km, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->page_meter_lbl_km, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->page_meter_lbl_km, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_meter_lbl_km, &lv_font_montserratMedium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->page_meter_lbl_km, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_meter_lbl_km, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_imgList_high_low_beam
    ui_scr->page_meter_imgList_high_low_beam = lv_imglist_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_imgList_high_low_beam, 140, 104);
    lv_obj_set_size(ui_scr->page_meter_imgList_high_low_beam, 40, 40);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_imgList_high_low_beam, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_imgList_high_low_beam, GUI_CTRL_IMGLIST);

    //Set style for page_meter_imgList_high_low_beam. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_imgList_high_low_beam, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_imglist_set_src(ui_scr->page_meter_imgList_high_low_beam, (const void **) page_meter_imgList_high_low_beam_imgs, 2);
    lv_imglist_set_act(ui_scr->page_meter_imgList_high_low_beam, 0);

    //Write codes page_meter_anim_pwr_l
    ui_scr->page_meter_anim_pwr_l = lv_animimg_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_anim_pwr_l, 31, 27);
    lv_obj_set_size(ui_scr->page_meter_anim_pwr_l, 158, 280);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_anim_pwr_l, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_anim_pwr_l, GUI_CTRL_ANIMIMG);
    lv_animimg_set_duration(ui_scr->page_meter_anim_pwr_l, 1980);
    lv_animimg_set_repeat_count(ui_scr->page_meter_anim_pwr_l, -1);
    lv_animimg_set_src(ui_scr->page_meter_anim_pwr_l, (const void **) page_meter_anim_pwr_l_imgs, 99);
    lv_animimg_start(ui_scr->page_meter_anim_pwr_l);

    //Write codes page_meter_anim_pwr_r
    ui_scr->page_meter_anim_pwr_r = lv_animimg_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_anim_pwr_r, 612, 27);
    lv_obj_set_size(ui_scr->page_meter_anim_pwr_r, 158, 280);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_anim_pwr_r, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_anim_pwr_r, GUI_CTRL_ANIMIMG);
    lv_animimg_set_duration(ui_scr->page_meter_anim_pwr_r, 1980);
    lv_animimg_set_repeat_count(ui_scr->page_meter_anim_pwr_r, -1);
    lv_animimg_set_src(ui_scr->page_meter_anim_pwr_r, (const void **) page_meter_anim_pwr_r_imgs, 99);
    lv_animimg_start(ui_scr->page_meter_anim_pwr_r);

    //Write codes page_meter_view_call_in
    ui_scr->page_meter_view_call_in = lv_obj_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_view_call_in, 148, 8);
    lv_obj_set_size(ui_scr->page_meter_view_call_in, 526, 86);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_view_call_in, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget page_meter_view_call_in
    lv_obj_add_flag(ui_scr->page_meter_view_call_in, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->page_meter_view_call_in, GUI_CTRL_CONT);

    //Set style for page_meter_view_call_in. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->page_meter_view_call_in, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_scr->page_meter_view_call_in, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->page_meter_view_call_in, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->page_meter_view_call_in, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_scr->page_meter_view_call_in, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->page_meter_view_call_in, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->page_meter_view_call_in, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->page_meter_view_call_in, 204, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for page_meter_view_call_in
    lv_obj_remove_style(ui_scr->page_meter_view_call_in, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes page_meter_lbl_3
    ui_scr->page_meter_lbl_3 = lv_label_create(ui_scr->page_meter_view_call_in);
    lv_label_set_text(ui_scr->page_meter_lbl_3, "挂断");
    lv_label_set_long_mode(ui_scr->page_meter_lbl_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_meter_lbl_3, 52, 48);
    lv_obj_set_size(ui_scr->page_meter_lbl_3, 58, 30);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_lbl_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_lbl_3, GUI_CTRL_LABEL);

    //Set style for page_meter_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_lbl_3, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->page_meter_lbl_3, lv_color_make(0x9E, 0x9E, 0x9E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_meter_lbl_3, &lv_font_simsun_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->page_meter_lbl_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_meter_lbl_3, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_lbl_phone_num
    ui_scr->page_meter_lbl_phone_num = lv_label_create(ui_scr->page_meter_view_call_in);
    lv_label_set_text(ui_scr->page_meter_lbl_phone_num, "133333333333");
    lv_label_set_long_mode(ui_scr->page_meter_lbl_phone_num, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_meter_lbl_phone_num, 110, 9);
    lv_obj_set_size(ui_scr->page_meter_lbl_phone_num, 291, 41);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_lbl_phone_num, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_lbl_phone_num, GUI_CTRL_LABEL);

    //Set style for page_meter_lbl_phone_num. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_font(ui_scr->page_meter_lbl_phone_num, &lv_font_montserratMedium_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->page_meter_lbl_phone_num, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_meter_lbl_phone_num, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_1
    ui_scr->page_meter_img_1 = lv_img_create(ui_scr->page_meter_view_call_in);
    lv_img_set_src(ui_scr->page_meter_img_1, gui_get_res_path(GUI_RES_HANG_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_1, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_1, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_1, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_1, 59, 7);
    lv_obj_set_size(ui_scr->page_meter_img_1, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_1, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_1, GUI_CTRL_IMG);

    //Write codes page_meter_img_2
    ui_scr->page_meter_img_2 = lv_img_create(ui_scr->page_meter_view_call_in);
    lv_img_set_src(ui_scr->page_meter_img_2, gui_get_res_path(GUI_RES_PICK_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_2, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_2, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_2, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_2, 415, 7);
    lv_obj_set_size(ui_scr->page_meter_img_2, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_2, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_2, GUI_CTRL_IMG);

    //Write codes page_meter_lbl_2
    ui_scr->page_meter_lbl_2 = lv_label_create(ui_scr->page_meter_view_call_in);
    lv_label_set_text(ui_scr->page_meter_lbl_2, "正在呼入");
    lv_label_set_long_mode(ui_scr->page_meter_lbl_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_meter_lbl_2, 165, 51);
    lv_obj_set_size(ui_scr->page_meter_lbl_2, 169, 28);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_lbl_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_lbl_2, GUI_CTRL_LABEL);

    //Set style for page_meter_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->page_meter_lbl_2, lv_color_make(0x9E, 0x9E, 0x9E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_meter_lbl_2, &lv_font_simsun_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->page_meter_lbl_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_meter_lbl_2, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_lbl_4
    ui_scr->page_meter_lbl_4 = lv_label_create(ui_scr->page_meter_view_call_in);
    lv_label_set_text(ui_scr->page_meter_lbl_4, "接听");
    lv_label_set_long_mode(ui_scr->page_meter_lbl_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->page_meter_lbl_4, 408, 48);
    lv_obj_set_size(ui_scr->page_meter_lbl_4, 58, 30);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_lbl_4, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_lbl_4, GUI_CTRL_LABEL);

    //Set style for page_meter_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->page_meter_lbl_4, lv_color_make(0x9E, 0x9E, 0x9E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_meter_lbl_4, &lv_font_simsun_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->page_meter_lbl_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->page_meter_lbl_4, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write Timer page_meter_timer_1
    if (ui_scr->page_meter_timer_1 != NULL) {
        lv_timer_del(ui_scr->page_meter_timer_1);
    }
    ui_scr->page_meter_timer_1 = lv_timer_create(page_meter_timer_1_timer_cb, 50, "");
    lv_timer_set_repeat_count(ui_scr->page_meter_timer_1, -1);

    // Write Timer page_meter_timer_2
    if (ui_scr->page_meter_timer_2 != NULL) {
        lv_timer_del(ui_scr->page_meter_timer_2);
    }
    ui_scr->page_meter_timer_2 = lv_timer_create(page_meter_timer_2_timer_cb, 1000, "");
    lv_timer_set_repeat_count(ui_scr->page_meter_timer_2, -1);

    // Write Timer page_meter_timer_3
    if (ui_scr->page_meter_timer_3 != NULL) {
        lv_timer_del(ui_scr->page_meter_timer_3);
    }
    ui_scr->page_meter_timer_3 = lv_timer_create(page_meter_timer_3_timer_cb, 1000, "");
    lv_timer_set_repeat_count(ui_scr->page_meter_timer_3, -1);

    //Write codes page_meter_imglist_1
    ui_scr->page_meter_imglist_1 = lv_imglist_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_imglist_1, 161, 20);
    lv_obj_set_size(ui_scr->page_meter_imglist_1, 84, 32);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_imglist_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_imglist_1, GUI_CTRL_IMGLIST);

    //Set style for page_meter_imglist_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_imglist_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_imglist_set_src(ui_scr->page_meter_imglist_1, (const void **) page_meter_imglist_1_imgs, 3);
    lv_imglist_set_act(ui_scr->page_meter_imglist_1, 0);

    //Write codes page_meter_img_4
    ui_scr->page_meter_img_4 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_4, gui_get_res_path(GUI_RES_READY_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_4, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_4, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_4, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_4, 344, 24);
    lv_obj_set_size(ui_scr->page_meter_img_4, 108, 24);
    lv_obj_add_flag(ui_scr->page_meter_img_4, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_4, GUI_CTRL_IMG);

    //Set style for page_meter_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_5
    ui_scr->page_meter_img_5 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_5, gui_get_res_path(GUI_RES_TEM_01_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_5, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_5, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_5, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_5, 20, 16);
    lv_obj_set_size(ui_scr->page_meter_img_5, 42, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_5, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_5, GUI_CTRL_IMG);

    //Set style for page_meter_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_5, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_imglist_2
    ui_scr->page_meter_imglist_2 = lv_imglist_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_imglist_2, 565, 16);
    lv_obj_set_size(ui_scr->page_meter_imglist_2, 40, 40);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_imglist_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_imglist_2, GUI_CTRL_IMGLIST);
    lv_imglist_set_src(ui_scr->page_meter_imglist_2, (const void **) page_meter_imglist_2_imgs, 2);
    lv_imglist_set_act(ui_scr->page_meter_imglist_2, 0);

    //Write codes page_meter_imglist_3
    ui_scr->page_meter_imglist_3 = lv_imglist_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_imglist_3, 521, 16);
    lv_obj_set_size(ui_scr->page_meter_imglist_3, 40, 40);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_imglist_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_imglist_3, GUI_CTRL_IMGLIST);

    //Set style for page_meter_imglist_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_imglist_3, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_imglist_set_src(ui_scr->page_meter_imglist_3, (const void **) page_meter_imglist_3_imgs, 2);
    lv_imglist_set_act(ui_scr->page_meter_imglist_3, 0);

    //Write codes page_meter_imglist_4
    ui_scr->page_meter_imglist_4 = lv_imglist_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_imglist_4, 653, 12);
    lv_obj_set_size(ui_scr->page_meter_imglist_4, 40, 40);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_imglist_4, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_imglist_4, GUI_CTRL_IMGLIST);
    lv_imglist_set_src(ui_scr->page_meter_imglist_4, (const void **) page_meter_imglist_4_imgs, 2);
    lv_imglist_set_act(ui_scr->page_meter_imglist_4, 0);

    //Write codes page_meter_imglist_5
    ui_scr->page_meter_imglist_5 = lv_imglist_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_imglist_5, 609, 12);
    lv_obj_set_size(ui_scr->page_meter_imglist_5, 40, 40);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_imglist_5, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_imglist_5, GUI_CTRL_IMGLIST);
    lv_imglist_set_src(ui_scr->page_meter_imglist_5, (const void **) page_meter_imglist_5_imgs, 2);
    lv_imglist_set_act(ui_scr->page_meter_imglist_5, 0);

    //Write codes page_meter_imglist_6
    ui_scr->page_meter_imglist_6 = lv_imglist_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_imglist_6, 270, 428);
    lv_obj_set_size(ui_scr->page_meter_imglist_6, 40, 40);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_imglist_6, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_imglist_6, GUI_CTRL_IMGLIST);

    //Set style for page_meter_imglist_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_imglist_6, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_imglist_set_src(ui_scr->page_meter_imglist_6, (const void **) page_meter_imglist_6_imgs, 3);
    lv_imglist_set_act(ui_scr->page_meter_imglist_6, 1);

    //Write codes page_meter_img_6
    ui_scr->page_meter_img_6 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_6, gui_get_res_path(GUI_RES_LAMP_19_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_6, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_6, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_6, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_6, 20, 428);
    lv_obj_set_size(ui_scr->page_meter_img_6, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_6, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_6, GUI_CTRL_IMG);

    //Set style for page_meter_img_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_img_6, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_img_left_turn
    ui_scr->page_meter_img_left_turn = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_left_turn, gui_get_res_path(GUI_RES_LAMP_01_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_left_turn, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_left_turn, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_left_turn, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_left_turn, 20, 60);
    lv_obj_set_size(ui_scr->page_meter_img_left_turn, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_left_turn, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_left_turn, GUI_CTRL_IMG);

    //Write codes page_meter_imglist_bat
    ui_scr->page_meter_imglist_bat = lv_imglist_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_imglist_bat, 320, 442);
    lv_obj_set_size(ui_scr->page_meter_imglist_bat, 160, 12);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_imglist_bat, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_imglist_bat, GUI_CTRL_IMGLIST);
    lv_imglist_set_src(ui_scr->page_meter_imglist_bat, (const void **) page_meter_imglist_bat_imgs, 100);
    lv_imglist_set_act(ui_scr->page_meter_imglist_bat, 99);

    lv_obj_update_layout(ui_scr->page_meter);
    ui_scr->page_meter_del = false;
    i18n_refresh_texts(GUI_SCREEN_PAGE_METER);

    //Init events for screen
    events_init_page_meter(ui);
    return ui_scr->page_meter;
}
void unload_scr_page_meter(lv_ui *ui)
{
    lv_ui_page_meter *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAGE_METER);
    if (ui_scr->page_meter_timer_1 != NULL) {
        lv_timer_del(ui_scr->page_meter_timer_1);
        ui_scr->page_meter_timer_1 = NULL;
    }
    if (ui_scr->page_meter_timer_2 != NULL) {
        lv_timer_del(ui_scr->page_meter_timer_2);
        ui_scr->page_meter_timer_2 = NULL;
    }
    if (ui_scr->page_meter_timer_3 != NULL) {
        lv_timer_del(ui_scr->page_meter_timer_3);
        ui_scr->page_meter_timer_3 = NULL;
    }
    ui_free_scr_ptr(ui, GUI_SCREEN_PAGE_METER);
}

#endif
