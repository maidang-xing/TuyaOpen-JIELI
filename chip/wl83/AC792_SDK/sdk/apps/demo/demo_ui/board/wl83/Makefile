
# make 编译并下载
# make VERBOSE=1 显示编译详细过程
# make clean 清除编译临时文件
#
# 注意： Linux 下编译方式：
#     1. 从 http://pkgman.jieliapp.com/doc/all 处找到下载链接
#     2. 下载后，解压到 /opt/jieli 目录下，保证
#       /opt/jieli/common/bin/clang 存在（注意目录层次）
#     3. 确认 ulimit -n 的结果足够大（建议大于8096），否则链接可能会因为打开文件太多而失败
#       可以通过 ulimit -n 8096 来设置一个较大的值
#

# 工具路径设置
ifeq ($(OS), Windows_NT)
# Windows 下工具链位置
TOOL_DIR := C:/JL/pi32/bin
CC    := clang.exe
CXX   := clang.exe
LD    := pi32v2-lto-wrapper.exe
AR    := llvm-ar.exe
MKDIR := mkdir_win -p
RM    := rm -rf

SYS_LIB_DIR := 
SYS_INC_DIR := 
EXT_CFLAGS  := # Windows 下不需要 -D__SHELL__
export PATH:=$(TOOL_DIR);$(PATH)

## 后处理脚本
FIXBAT          := ../../../../../tools/utils/fixbat.exe # 用于处理 utf8->gbk 编码问题
POST_SCRIPT     := ../../../../../cpu/wl83/tools/download.bat
RUN_POST_SCRIPT := ..\..\..\..\..\cpu\wl83\tools\download.bat
else
# Linux 下工具链位置
TOOL_DIR := /opt/jieli/pi32v2/bin
CC    := clang
CXX   := clang
LD    := lto-wrapper
AR    := lto-ar
MKDIR := mkdir -p
RM    := rm -rf
export OBJDUMP := $(TOOL_DIR)/objdump
export OBJCOPY := $(TOOL_DIR)/objcopy
export OBJSIZEDUMP := $(TOOL_DIR)/objsizedump

SYS_LIB_DIR := $(TOOL_DIR)/../lib/r3
SYS_INC_DIR := $(TOOL_DIR)/../include
EXT_CFLAGS  := -D__SHELL__ # Linux 下需要这个保证正确处理 download.c
export PATH:=$(TOOL_DIR):$(PATH)

## 后处理脚本
FIXBAT          := touch # Linux下不需要处理 bat 编码问题
POST_SCRIPT     := ../../../../../cpu/wl83/tools/download.sh
RUN_POST_SCRIPT := bash $(POST_SCRIPT)
endif

CC  := $(TOOL_DIR)/$(CC)
CXX := $(TOOL_DIR)/$(CXX)
LD  := $(TOOL_DIR)/$(LD)
AR  := $(TOOL_DIR)/$(AR)
# 输出文件设置
OUT_ELF   := ../../../../../cpu/wl83/tools/sdk.elf
OBJ_FILE  := $(OUT_ELF).objs.txt
# 编译路径设置
BUILD_DIR := objs
# 工程路径前缀
ROOT_PREFIX := ../../../../..

# 编译参数设置
CFLAGS := \
	-target pi32v2 \
	-integrated-as \
	-mcpu=r3 \
	-mfprev1 \
	-Wuninitialized \
	-Wno-invalid-noreturn \
	-fno-common \
	-integrated-as \
	-Oz \
	-g \
	-flto \
	-fallow-pointer-null \
	-fprefer-gnu-section \
	-femulated-tls \
	-Wno-shift-negative-value \
	-Wframe-larger-than=2560 \
	-mllvm -pi32v2-large-program=true \
	-fms-extensions \
	-w \
	-fno-unwind-tables \
	-ffunction-sections \
	-fdata-sections \
	-fmessage-length=0 \


# C++额外的编译参数
CXXFLAGS := \
	-std=gnu++14 \
	-fno-exceptions \
	-fno-rtti \


# 宏定义
DEFINES := \
	-DSUPPORT_MS_EXTENSIONS \
	-DCONFIG_RELEASE_ENABLE \
	-DCONFIG_CPU_WL83 \
	-DMAX_AUDIO_ADC_CHANNEL_NUM=2 \
	-DCONFIG_UCOS_ENABLE \
	-DCONFIG_THREAD_ENABLE \
	-D__GCC_PI32V2__ \
	-DCONFIG_NEW_ECC_ENABLE \
	-DCONFIG_DEMO_UI_PROJECT_ENABLE \
	-DVM_MAX_PAGE_ALIGN_SIZE_CONFIG=64*1024 \
	-DVM_MAX_SECTOR_ALIGN_SIZE_CONFIG=64*1024 \
	-DVM_ITEM_MAX_NUM=256 \
	-DRLOTTIE_COMMIT_HASH=\"492fbb753924ae7cad27072a2b6ddedde88dc4bd\" \
	-DFREETYPE_COMMIT_HASH=\"ef54557bda3b17da1b7e42e8e207efd1842bcc05\" \
	-DFT2_BUILD_LIBRARY \
	-DLVGL_COMMIT_HASH=\"release_v9.3_c033a98afddd65aaafeebea625382a94020fe4a7\" \
	-D_XOPEN_SOURCE=700 \
	-D_GNU_SOURCE \
	-D__ELF__ \


DEFINES += $(EXT_CFLAGS) # 额外的一些定义

# 头文件搜索路径
INCLUDES := \
	-I../../../../../include_lib/c++ \
	-I../../../../../include_lib/c++/include \
	-I../../../../../include_lib/newlib/include \
	-I../../../../../include_lib/c++/simple_pthread \
	-I../../../../../include_lib \
	-I../../../../../include_lib/driver \
	-I../../../../../include_lib/driver/device \
	-I../../../../../include_lib/driver/cpu/wl83 \
	-I../../../../../include_lib/system \
	-I../../../../../include_lib/system/generic \
	-I../../../../../include_lib/btctrler \
	-I../../../../../include_lib/btctrler/port/wl83 \
	-I../../../../../include_lib/update \
	-I../../../../../include_lib/btstack/third_party/common \
	-I../../../../../include_lib/btstack/third_party/rcsp \
	-I../../../../../include_lib/utils \
	-I../../../../../include_lib/utils/syscfg \
	-I../../../../../include_lib/utils/event \
	-I../../../../../apps \
	-I../../../../../apps/demo/demo_ui/include \
	-I../../../../../apps/demo/demo_ui/board/wl83 \
	-I../../../../../include_lib/system/os \
	-I../../../../../apps/common/usb \
	-I../../../../../apps/common/include \
	-I../../../../../apps/common/system \
	-I../../../../../apps/common/system/perf_counter \
	-I../../../../../apps/common/lzw \
	-I../../../../../include_lib/net/lwip_2_2_0/lwip/app/ctp \
	-I../../../../../include_lib/driver/device/video \
	-I../../../../../apps/common/lcd/include \
	-I../../../../../include_lib/driver/device/video/pipeline \
	-I../../../../../include_lib/driver/device/video/pipeline/buffer \
	-I../../../../../include_lib/driver/device/video/pipeline/core \
	-I../../../../../apps/common/example/third_party/rlottie_impl/inc \
	-I../../../../../apps/common/example/third_party/rlottie_impl/src/vector \
	-I../../../../../apps/common/example/third_party/rlottie_impl/src/vector/freetype \
	-I../../../../../apps/common/example/third_party/freetype/include \
	-I../../../../../include_lib/driver/cpu/wl83/asm \
	-I../../../../../apps/common/lvgl_v9 \
	-I../../../../../apps/common/lvgl_v9/examples/porting \
	-I../../../../../apps/common/lvgl_v9/examples/libs/freetype \
	-I../../../../../apps/common \
	-I../../../../../apps/common/lvgl_v9/demos \
	-I../../../../../apps/common/lvgl_v9/demos/benchmark \
	-I../../../../../apps/common/lvgl_v9/demos/keypad_encoder \
	-I../../../../../apps/common/lvgl_v9/demos/multilang \
	-I../../../../../apps/common/lvgl_v9/demos/music \
	-I../../../../../apps/common/lvgl_v9/demos/render \
	-I../../../../../apps/common/lvgl_v9/demos/scroll \
	-I../../../../../apps/common/lvgl_v9/demos/stress \
	-I../../../../../apps/common/lvgl_v9/demos/vector_graphic \
	-I../../../../../apps/common/lvgl_v9/demos/transform \
	-I../../../../../apps/common/lvgl_v9/demos/widgets \
	-I../../../../../apps/common/lvgl_v9/demos/flex_layout \


# 需要编译的 .c 文件
c_SRC_FILES := \
	../../../../../apps/common/c++/cpp_run_init.c \
	../../../../../apps/common/camera/GC1084_DVP/GC1084_DVP.c \
	../../../../../apps/common/camera/GC1084_DVP/GC1084_DVP_ae.c \
	../../../../../apps/common/camera/GC1084_DVP/GC1084_DVP_awb.c \
	../../../../../apps/common/camera/GC1084_DVP/GC1084_DVP_iq.c \
	../../../../../apps/common/camera/N5_DVP/N5_DVP.c \
	../../../../../apps/common/camera/SP140A_dvp/sp140a_dvp.c \
	../../../../../apps/common/camera/SP140A_dvp/sp140a_dvp_ae.c \
	../../../../../apps/common/camera/SP140A_dvp/sp140a_dvp_awb.c \
	../../../../../apps/common/camera/SP140A_dvp/sp140a_dvp_iq.c \
	../../../../../apps/common/camera/TVP5150A_DVP.c \
	../../../../../apps/common/camera/bf20a6/bf20a6.c \
	../../../../../apps/common/camera/gc0308/gc0308.c \
	../../../../../apps/common/camera/gc1084_mipi/gc1084_mipi.c \
	../../../../../apps/common/camera/gc1084_mipi/gc1084_mipi_ae.c \
	../../../../../apps/common/camera/gc1084_mipi/gc1084_mipi_awb.c \
	../../../../../apps/common/camera/gc1084_mipi/gc1084_mipi_iq.c \
	../../../../../apps/common/camera/gc2145_mipi/gc2145_mipi.c \
	../../../../../apps/common/camera/h63p_dvp/h63p_dvp.c \
	../../../../../apps/common/camera/h63p_dvp/h63p_dvp_ae.c \
	../../../../../apps/common/camera/h63p_dvp/h63p_dvp_awb.c \
	../../../../../apps/common/camera/h63p_dvp/h63p_dvp_iq.c \
	../../../../../apps/common/camera/h63p_mipi/h63p_mipi.c \
	../../../../../apps/common/camera/h63p_mipi/h63p_mipi_ae.c \
	../../../../../apps/common/camera/h63p_mipi/h63p_mipi_awb.c \
	../../../../../apps/common/camera/h63p_mipi/h63p_mipi_iq.c \
	../../../../../apps/common/camera/isp_scenes.c \
	../../../../../apps/common/camera/isp_tools.c \
	../../../../../apps/common/camera/nt99141.c \
	../../../../../apps/common/camera/ov2659/ov2659.c \
	../../../../../apps/common/camera/sc1245_dvp/sc1245.c \
	../../../../../apps/common/camera/sc1245_dvp/sc1245_ae.c \
	../../../../../apps/common/camera/sc1245_dvp/sc1245_awb.c \
	../../../../../apps/common/camera/sc1245_dvp/sc1245_iq.c \
	../../../../../apps/common/camera/sc1336_mipi/sc1336_mipi.c \
	../../../../../apps/common/camera/sc1336_mipi/sc1336_mipi_ae.c \
	../../../../../apps/common/camera/sc1336_mipi/sc1336_mipi_awb.c \
	../../../../../apps/common/camera/sc1336_mipi/sc1336_mipi_iq.c \
	../../../../../apps/common/camera/sc1345_mipi/SC1345_mipi.c \
	../../../../../apps/common/camera/sc1345_mipi/SC1345_mipi_ae.c \
	../../../../../apps/common/camera/sc1345_mipi/SC1345_mipi_awb.c \
	../../../../../apps/common/camera/sc1345_mipi/SC1345_mipi_iq.c \
	../../../../../apps/common/camera/sc1346_mipi/SC1346_mipi.c \
	../../../../../apps/common/camera/sc1346_mipi/SC1346_mipi_ae.c \
	../../../../../apps/common/camera/sc1346_mipi/SC1346_mipi_awb.c \
	../../../../../apps/common/camera/sc1346_mipi/SC1346_mipi_iq.c \
	../../../../../apps/common/camera/xs9950_mipi/xs9950_mipi.c \
	../../../../../apps/common/config/log_config/lib_driver_config.c \
	../../../../../apps/common/config/log_config/lib_power_config.c \
	../../../../../apps/common/config/log_config/lib_system_config.c \
	../../../../../apps/common/config/log_config/lib_ui_config.c \
	../../../../../apps/common/config/log_config/lib_update_config.c \
	../../../../../apps/common/config/user_cfg.c \
	../../../../../apps/common/debug/debug.c \
	../../../../../apps/common/debug/debug_user.c \
	../../../../../apps/common/dma2d_gpu/dma2d_common_api.c \
	../../../../../apps/common/dma2d_gpu/gpu_common_api.c \
	../../../../../apps/common/example/peripheral/lcd/lcd_driver_test.c \
	../../../../../apps/common/example/third_party/freetype/src/autofit/autofit.c \
	../../../../../apps/common/example/third_party/freetype/src/base/ftbase.c \
	../../../../../apps/common/example/third_party/freetype/src/base/ftbitmap.c \
	../../../../../apps/common/example/third_party/freetype/src/base/ftdebug.c \
	../../../../../apps/common/example/third_party/freetype/src/base/ftglyph.c \
	../../../../../apps/common/example/third_party/freetype/src/base/ftinit.c \
	../../../../../apps/common/example/third_party/freetype/src/base/ftmm.c \
	../../../../../apps/common/example/third_party/freetype/src/base/ftsystem.c \
	../../../../../apps/common/example/third_party/freetype/src/bdf/bdf.c \
	../../../../../apps/common/example/third_party/freetype/src/bzip2/ftbzip2.c \
	../../../../../apps/common/example/third_party/freetype/src/cache/ftcache.c \
	../../../../../apps/common/example/third_party/freetype/src/cff/cff.c \
	../../../../../apps/common/example/third_party/freetype/src/cid/type1cid.c \
	../../../../../apps/common/example/third_party/freetype/src/dlg/dlgwrap.c \
	../../../../../apps/common/example/third_party/freetype/src/gxvalid/gxvalid.c \
	../../../../../apps/common/example/third_party/freetype/src/gzip/ftgzip.c \
	../../../../../apps/common/example/third_party/freetype/src/lzw/ftlzw.c \
	../../../../../apps/common/example/third_party/freetype/src/otvalid/otvalid.c \
	../../../../../apps/common/example/third_party/freetype/src/pcf/pcf.c \
	../../../../../apps/common/example/third_party/freetype/src/pfr/pfr.c \
	../../../../../apps/common/example/third_party/freetype/src/psaux/psaux.c \
	../../../../../apps/common/example/third_party/freetype/src/pshinter/pshinter.c \
	../../../../../apps/common/example/third_party/freetype/src/psnames/psnames.c \
	../../../../../apps/common/example/third_party/freetype/src/raster/raster.c \
	../../../../../apps/common/example/third_party/freetype/src/sdf/sdf.c \
	../../../../../apps/common/example/third_party/freetype/src/sfnt/sfnt.c \
	../../../../../apps/common/example/third_party/freetype/src/smooth/smooth.c \
	../../../../../apps/common/example/third_party/freetype/src/svg/svg.c \
	../../../../../apps/common/example/third_party/freetype/src/truetype/truetype.c \
	../../../../../apps/common/example/third_party/freetype/src/type1/type1.c \
	../../../../../apps/common/example/third_party/freetype/src/type42/type42.c \
	../../../../../apps/common/example/third_party/freetype/src/winfonts/winfnt.c \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/stb/rlottie_stb_image.c \
	../../../../../apps/common/iic/iic.c \
	../../../../../apps/common/iic/iic_api.c \
	../../../../../apps/common/iic/software_iic.c \
	../../../../../apps/common/lcd/lcd_driver/fb_component/fb_combine.c \
	../../../../../apps/common/lcd/lcd_driver/fb_component/fb_lcd.c \
	../../../../../apps/common/lcd/lcd_driver/fb_component/fb_out_dev.c \
	../../../../../apps/common/lcd/lcd_driver/fb_component/fb_rotate.c \
	../../../../../apps/common/lcd/lcd_driver/lcd_driver.c \
	../../../../../apps/common/lcd/lcd_driver/lcd_scenes.c \
	../../../../../apps/common/lcd/lcd_driver/lcd_tools.c \
	../../../../../apps/common/lcd/lcd_driver/mcu_lcd/lcd_mcu_ili9481_320x480.c \
	../../../../../apps/common/lcd/lcd_driver/mcu_lcd/lcd_mcu_ili9488_320x480.c \
	../../../../../apps/common/lcd/lcd_driver/mcu_lcd/lcd_mcu_st7789v_240x320.c \
	../../../../../apps/common/lcd/lcd_driver/mipi_lcd/lcd_mipi_fl7707_480x1280.c \
	../../../../../apps/common/lcd/lcd_driver/mipi_lcd/lcd_mipi_ili9881c_800x1280.c \
	../../../../../apps/common/lcd/lcd_driver/mipi_lcd/lcd_mipi_jd9165ba_1024x600.c \
	../../../../../apps/common/lcd/lcd_driver/mipi_lcd/lcd_mipi_st7701s_480x640_rotate_90.c \
	../../../../../apps/common/lcd/lcd_driver/mipi_lcd/lcd_mipi_st7701s_480x800.c \
	../../../../../apps/common/lcd/lcd_driver/mipi_lcd/lcd_mipi_st7701s_480x800_rotate_90.c \
	../../../../../apps/common/lcd/lcd_driver/mipi_lcd/lcd_mipi_st7703_720x720.c \
	../../../../../apps/common/lcd/lcd_driver/mipi_lcd/lcd_mipi_st77922_480x480.c \
	../../../../../apps/common/lcd/lcd_driver/rgb_lcd/lcd_rgb_fl58202_800x480.c \
	../../../../../apps/common/lcd/lcd_driver/rgb_lcd/lcd_rgb_hx8264_800x480.c \
	../../../../../apps/common/lcd/lcd_driver/rgb_lcd/lcd_rgb_ssd2828_720x1280.c \
	../../../../../apps/common/lcd/lcd_driver/rgb_lcd/lcd_rgb_st7701s_480x800.c \
	../../../../../apps/common/lcd/lcd_driver/rgb_lcd/lcd_rgb_xxxx_1280x800.c \
	../../../../../apps/common/lcd/lcd_driver/rgb_lcd/lcd_rgb_xxxx_480x272.c \
	../../../../../apps/common/lcd/lcd_driver/spi_lcd/lcd_spi_gc9307_172x320.c \
	../../../../../apps/common/lcd/lcd_driver/spi_lcd/lcd_spi_gc9307_240x296.c \
	../../../../../apps/common/lcd/lcd_driver/spi_lcd/lcd_spi_nv3006a_142x428.c \
	../../../../../apps/common/lcd/touch_driver/cst3240.c \
	../../../../../apps/common/lcd/touch_driver/cst816d.c \
	../../../../../apps/common/lcd/touch_driver/ft6236.c \
	../../../../../apps/common/lcd/touch_driver/gt1151.c \
	../../../../../apps/common/lcd/touch_driver/gt911.c \
	../../../../../apps/common/lcd/touch_driver/gt9271.c \
	../../../../../apps/common/lcd/touch_driver/tp_driver.c \
	../../../../../apps/common/lvgl_v9/demos/benchmark/assets/img_benchmark_avatar.c \
	../../../../../apps/common/lvgl_v9/demos/benchmark/assets/img_benchmark_lvgl_logo_argb.c \
	../../../../../apps/common/lvgl_v9/demos/benchmark/assets/img_benchmark_lvgl_logo_rgb.c \
	../../../../../apps/common/lvgl_v9/demos/benchmark/assets/lv_font_benchmark_montserrat_12_aligned.c \
	../../../../../apps/common/lvgl_v9/demos/benchmark/assets/lv_font_benchmark_montserrat_14_aligned.c \
	../../../../../apps/common/lvgl_v9/demos/benchmark/assets/lv_font_benchmark_montserrat_16_aligned.c \
	../../../../../apps/common/lvgl_v9/demos/benchmark/assets/lv_font_benchmark_montserrat_18_aligned.c \
	../../../../../apps/common/lvgl_v9/demos/benchmark/assets/lv_font_benchmark_montserrat_20_aligned.c \
	../../../../../apps/common/lvgl_v9/demos/benchmark/assets/lv_font_benchmark_montserrat_24_aligned.c \
	../../../../../apps/common/lvgl_v9/demos/benchmark/assets/lv_font_benchmark_montserrat_26_aligned.c \
	../../../../../apps/common/lvgl_v9/demos/benchmark/lv_demo_benchmark.c \
	../../../../../apps/common/lvgl_v9/demos/keypad_encoder/lv_demo_keypad_encoder.c \
	../../../../../apps/common/lvgl_v9/demos/lv_demos.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_corner_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_list_pause.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_list_pause_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_list_play.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_list_play_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_loop.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_loop_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_next.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_next_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_pause.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_pause_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_play.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_play_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_prev.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_prev_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_rnd.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_btn_rnd_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_corner_left.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_corner_left_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_corner_right.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_corner_right_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_cover_1.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_cover_1_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_cover_2.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_cover_2_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_cover_3.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_cover_3_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_icon_1.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_icon_1_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_icon_2.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_icon_2_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_icon_3.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_icon_3_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_icon_4.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_icon_4_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_list_border.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_list_border_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_logo.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_slider_knob.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_slider_knob_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_wave_bottom.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_wave_bottom_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_wave_top.c \
	../../../../../apps/common/lvgl_v9/demos/music/assets/img_lv_demo_music_wave_top_large.c \
	../../../../../apps/common/lvgl_v9/demos/music/lv_demo_music.c \
	../../../../../apps/common/lvgl_v9/demos/music/lv_demo_music_list.c \
	../../../../../apps/common/lvgl_v9/demos/music/lv_demo_music_main.c \
	../../../../../apps/common/lvgl_v9/demos/render/assets/img_render_arc_bg.c \
	../../../../../apps/common/lvgl_v9/demos/render/assets/img_render_lvgl_logo_argb8888.c \
	../../../../../apps/common/lvgl_v9/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.c \
	../../../../../apps/common/lvgl_v9/demos/render/assets/img_render_lvgl_logo_i1.c \
	../../../../../apps/common/lvgl_v9/demos/render/assets/img_render_lvgl_logo_l8.c \
	../../../../../apps/common/lvgl_v9/demos/render/assets/img_render_lvgl_logo_rgb565.c \
	../../../../../apps/common/lvgl_v9/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.c \
	../../../../../apps/common/lvgl_v9/demos/render/assets/img_render_lvgl_logo_rgb565a8.c \
	../../../../../apps/common/lvgl_v9/demos/render/assets/img_render_lvgl_logo_rgb888.c \
	../../../../../apps/common/lvgl_v9/demos/render/assets/img_render_lvgl_logo_xrgb8888.c \
	../../../../../apps/common/lvgl_v9/demos/render/lv_demo_render.c \
	../../../../../apps/common/lvgl_v9/demos/stress/lv_demo_stress.c \
	../../../../../apps/common/lvgl_v9/demos/vector_graphic/assets/img_demo_vector_avatar.c \
	../../../../../apps/common/lvgl_v9/demos/vector_graphic/lv_demo_vector_graphic.c \
	../../../../../apps/common/lvgl_v9/demos/widgets/assets/img_clothes.c \
	../../../../../apps/common/lvgl_v9/demos/widgets/assets/img_demo_widgets_avatar.c \
	../../../../../apps/common/lvgl_v9/demos/widgets/assets/img_demo_widgets_needle.c \
	../../../../../apps/common/lvgl_v9/demos/widgets/assets/img_lvgl_logo.c \
	../../../../../apps/common/lvgl_v9/demos/widgets/lv_demo_widgets.c \
	../../../../../apps/common/lvgl_v9/examples/anim/lv_example_anim_1.c \
	../../../../../apps/common/lvgl_v9/examples/anim/lv_example_anim_2.c \
	../../../../../apps/common/lvgl_v9/examples/anim/lv_example_anim_3.c \
	../../../../../apps/common/lvgl_v9/examples/anim/lv_example_anim_4.c \
	../../../../../apps/common/lvgl_v9/examples/anim/lv_example_anim_timeline_1.c \
	../../../../../apps/common/lvgl_v9/examples/assets/animimg001.c \
	../../../../../apps/common/lvgl_v9/examples/assets/animimg002.c \
	../../../../../apps/common/lvgl_v9/examples/assets/animimg003.c \
	../../../../../apps/common/lvgl_v9/examples/assets/emoji/img_emoji_F617.c \
	../../../../../apps/common/lvgl_v9/examples/assets/img_caret_down.c \
	../../../../../apps/common/lvgl_v9/examples/assets/img_cogwheel_argb.c \
	../../../../../apps/common/lvgl_v9/examples/assets/img_cogwheel_indexed16.c \
	../../../../../apps/common/lvgl_v9/examples/assets/img_cogwheel_rgb.c \
	../../../../../apps/common/lvgl_v9/examples/assets/img_hand.c \
	../../../../../apps/common/lvgl_v9/examples/assets/img_skew_strip.c \
	../../../../../apps/common/lvgl_v9/examples/assets/img_star.c \
	../../../../../apps/common/lvgl_v9/examples/assets/img_svg_img.c \
	../../../../../apps/common/lvgl_v9/examples/assets/imgbtn_left.c \
	../../../../../apps/common/lvgl_v9/examples/assets/imgbtn_mid.c \
	../../../../../apps/common/lvgl_v9/examples/assets/imgbtn_right.c \
	../../../../../apps/common/lvgl_v9/examples/event/lv_example_event_bubble.c \
	../../../../../apps/common/lvgl_v9/examples/event/lv_example_event_button.c \
	../../../../../apps/common/lvgl_v9/examples/event/lv_example_event_click.c \
	../../../../../apps/common/lvgl_v9/examples/event/lv_example_event_draw.c \
	../../../../../apps/common/lvgl_v9/examples/event/lv_example_event_streak.c \
	../../../../../apps/common/lvgl_v9/examples/get_started/lv_example_get_started_1.c \
	../../../../../apps/common/lvgl_v9/examples/get_started/lv_example_get_started_2.c \
	../../../../../apps/common/lvgl_v9/examples/get_started/lv_example_get_started_3.c \
	../../../../../apps/common/lvgl_v9/examples/get_started/lv_example_get_started_4.c \
	../../../../../apps/common/lvgl_v9/examples/grad/lv_example_grad_1.c \
	../../../../../apps/common/lvgl_v9/examples/grad/lv_example_grad_2.c \
	../../../../../apps/common/lvgl_v9/examples/grad/lv_example_grad_3.c \
	../../../../../apps/common/lvgl_v9/examples/grad/lv_example_grad_4.c \
	../../../../../apps/common/lvgl_v9/examples/layouts/flex/lv_example_flex_1.c \
	../../../../../apps/common/lvgl_v9/examples/layouts/flex/lv_example_flex_2.c \
	../../../../../apps/common/lvgl_v9/examples/layouts/flex/lv_example_flex_3.c \
	../../../../../apps/common/lvgl_v9/examples/layouts/flex/lv_example_flex_4.c \
	../../../../../apps/common/lvgl_v9/examples/layouts/flex/lv_example_flex_5.c \
	../../../../../apps/common/lvgl_v9/examples/layouts/flex/lv_example_flex_6.c \
	../../../../../apps/common/lvgl_v9/examples/layouts/grid/lv_example_grid_1.c \
	../../../../../apps/common/lvgl_v9/examples/layouts/grid/lv_example_grid_2.c \
	../../../../../apps/common/lvgl_v9/examples/layouts/grid/lv_example_grid_3.c \
	../../../../../apps/common/lvgl_v9/examples/layouts/grid/lv_example_grid_4.c \
	../../../../../apps/common/lvgl_v9/examples/layouts/grid/lv_example_grid_5.c \
	../../../../../apps/common/lvgl_v9/examples/layouts/grid/lv_example_grid_6.c \
	../../../../../apps/common/lvgl_v9/examples/libs/barcode/lv_example_barcode_1.c \
	../../../../../apps/common/lvgl_v9/examples/libs/bmp/lv_example_bmp_1.c \
	../../../../../apps/common/lvgl_v9/examples/libs/ffmpeg/lv_example_ffmpeg_1.c \
	../../../../../apps/common/lvgl_v9/examples/libs/ffmpeg/lv_example_ffmpeg_2.c \
	../../../../../apps/common/lvgl_v9/examples/libs/freetype/lv_example_freetype_1.c \
	../../../../../apps/common/lvgl_v9/examples/libs/freetype/lv_example_freetype_2.c \
	../../../../../apps/common/lvgl_v9/examples/libs/freetype/lv_example_freetype_3.c \
	../../../../../apps/common/lvgl_v9/examples/libs/gif/img_bulb_gif.c \
	../../../../../apps/common/lvgl_v9/examples/libs/gif/lv_example_gif_1.c \
	../../../../../apps/common/lvgl_v9/examples/libs/libjpeg_turbo/lv_example_libjpeg_turbo_1.c \
	../../../../../apps/common/lvgl_v9/examples/libs/libpng/img_png_demo.c \
	../../../../../apps/common/lvgl_v9/examples/libs/libpng/lv_example_libpng_1.c \
	../../../../../apps/common/lvgl_v9/examples/libs/lodepng/img_wink_png.c \
	../../../../../apps/common/lvgl_v9/examples/libs/lodepng/lv_example_lodepng_1.c \
	../../../../../apps/common/lvgl_v9/examples/libs/qrcode/lv_example_qrcode_1.c \
	../../../../../apps/common/lvgl_v9/examples/libs/rlottie/lv_example_rlottie_1.c \
	../../../../../apps/common/lvgl_v9/examples/libs/rlottie/lv_example_rlottie_2.c \
	../../../../../apps/common/lvgl_v9/examples/libs/rlottie/lv_example_rlottie_approve.c \
	../../../../../apps/common/lvgl_v9/examples/libs/svg/lv_example_svg_1.c \
	../../../../../apps/common/lvgl_v9/examples/libs/tiny_ttf/lv_example_tiny_ttf_1.c \
	../../../../../apps/common/lvgl_v9/examples/libs/tiny_ttf/lv_example_tiny_ttf_2.c \
	../../../../../apps/common/lvgl_v9/examples/libs/tiny_ttf/lv_example_tiny_ttf_3.c \
	../../../../../apps/common/lvgl_v9/examples/libs/tiny_ttf/ubuntu_font.c \
	../../../../../apps/common/lvgl_v9/examples/libs/tjpgd/lv_example_tjpgd_1.c \
	../../../../../apps/common/lvgl_v9/examples/others/file_explorer/lv_example_file_explorer_1.c \
	../../../../../apps/common/lvgl_v9/examples/others/file_explorer/lv_example_file_explorer_2.c \
	../../../../../apps/common/lvgl_v9/examples/others/file_explorer/lv_example_file_explorer_3.c \
	../../../../../apps/common/lvgl_v9/examples/others/font_manager/lv_example_font_manager_1.c \
	../../../../../apps/common/lvgl_v9/examples/others/font_manager/lv_example_font_manager_2.c \
	../../../../../apps/common/lvgl_v9/examples/others/font_manager/lv_example_font_manager_3.c \
	../../../../../apps/common/lvgl_v9/examples/others/fragment/lv_example_fragment_1.c \
	../../../../../apps/common/lvgl_v9/examples/others/fragment/lv_example_fragment_2.c \
	../../../../../apps/common/lvgl_v9/examples/others/gestures/lv_example_gestures.c \
	../../../../../apps/common/lvgl_v9/examples/others/gridnav/lv_example_gridnav_1.c \
	../../../../../apps/common/lvgl_v9/examples/others/gridnav/lv_example_gridnav_2.c \
	../../../../../apps/common/lvgl_v9/examples/others/gridnav/lv_example_gridnav_3.c \
	../../../../../apps/common/lvgl_v9/examples/others/gridnav/lv_example_gridnav_4.c \
	../../../../../apps/common/lvgl_v9/examples/others/gridnav/lv_example_gridnav_5.c \
	../../../../../apps/common/lvgl_v9/examples/others/ime/lv_example_ime_pinyin_1.c \
	../../../../../apps/common/lvgl_v9/examples/others/ime/lv_example_ime_pinyin_2.c \
	../../../../../apps/common/lvgl_v9/examples/others/imgfont/lv_example_imgfont_1.c \
	../../../../../apps/common/lvgl_v9/examples/others/monkey/lv_example_monkey_1.c \
	../../../../../apps/common/lvgl_v9/examples/others/monkey/lv_example_monkey_2.c \
	../../../../../apps/common/lvgl_v9/examples/others/monkey/lv_example_monkey_3.c \
	../../../../../apps/common/lvgl_v9/examples/others/observer/lv_example_observer_1.c \
	../../../../../apps/common/lvgl_v9/examples/others/observer/lv_example_observer_2.c \
	../../../../../apps/common/lvgl_v9/examples/others/observer/lv_example_observer_3.c \
	../../../../../apps/common/lvgl_v9/examples/others/observer/lv_example_observer_4.c \
	../../../../../apps/common/lvgl_v9/examples/others/observer/lv_example_observer_5.c \
	../../../../../apps/common/lvgl_v9/examples/others/observer/lv_example_observer_6.c \
	../../../../../apps/common/lvgl_v9/examples/others/snapshot/lv_example_snapshot_1.c \
	../../../../../apps/common/lvgl_v9/examples/others/xml/lv_example_xml_1.c \
	../../../../../apps/common/lvgl_v9/examples/others/xml/lv_example_xml_2.c \
	../../../../../apps/common/lvgl_v9/examples/porting/lv_port_disp.c \
	../../../../../apps/common/lvgl_v9/examples/porting/lv_port_disp_no_fb.c \
	../../../../../apps/common/lvgl_v9/examples/porting/lv_port_fs.c \
	../../../../../apps/common/lvgl_v9/examples/porting/lv_port_indev.c \
	../../../../../apps/common/lvgl_v9/examples/porting/osal/lv_example_osal.c \
	../../../../../apps/common/lvgl_v9/examples/scroll/lv_example_scroll_1.c \
	../../../../../apps/common/lvgl_v9/examples/scroll/lv_example_scroll_2.c \
	../../../../../apps/common/lvgl_v9/examples/scroll/lv_example_scroll_3.c \
	../../../../../apps/common/lvgl_v9/examples/scroll/lv_example_scroll_4.c \
	../../../../../apps/common/lvgl_v9/examples/scroll/lv_example_scroll_5.c \
	../../../../../apps/common/lvgl_v9/examples/scroll/lv_example_scroll_6.c \
	../../../../../apps/common/lvgl_v9/examples/scroll/lv_example_scroll_7.c \
	../../../../../apps/common/lvgl_v9/examples/scroll/lv_example_scroll_8.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_1.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_10.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_11.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_12.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_13.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_14.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_15.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_16.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_17.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_18.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_19.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_2.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_3.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_4.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_5.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_6.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_7.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_8.c \
	../../../../../apps/common/lvgl_v9/examples/styles/lv_example_style_9.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/animimg/lv_example_animimg_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/arc/lv_example_arc_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/arc/lv_example_arc_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/arc/lv_example_arc_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/bar/lv_example_bar_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/bar/lv_example_bar_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/bar/lv_example_bar_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/bar/lv_example_bar_4.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/bar/lv_example_bar_5.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/bar/lv_example_bar_6.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/bar/lv_example_bar_7.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/button/lv_example_button_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/button/lv_example_button_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/button/lv_example_button_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/buttonmatrix/lv_example_buttonmatrix_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/buttonmatrix/lv_example_buttonmatrix_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/buttonmatrix/lv_example_buttonmatrix_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/calendar/lv_example_calendar_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/calendar/lv_example_calendar_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/canvas/lv_example_canvas_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/canvas/lv_example_canvas_10.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/canvas/lv_example_canvas_11.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/canvas/lv_example_canvas_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/canvas/lv_example_canvas_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/canvas/lv_example_canvas_4.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/canvas/lv_example_canvas_5.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/canvas/lv_example_canvas_6.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/canvas/lv_example_canvas_7.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/canvas/lv_example_canvas_8.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/canvas/lv_example_canvas_9.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/chart/lv_example_chart_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/chart/lv_example_chart_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/chart/lv_example_chart_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/chart/lv_example_chart_4.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/chart/lv_example_chart_5.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/chart/lv_example_chart_6.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/chart/lv_example_chart_7.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/chart/lv_example_chart_8.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/checkbox/lv_example_checkbox_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/checkbox/lv_example_checkbox_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/dropdown/lv_example_dropdown_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/dropdown/lv_example_dropdown_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/dropdown/lv_example_dropdown_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/image/lv_example_image_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/image/lv_example_image_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/image/lv_example_image_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/image/lv_example_image_4.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/image/lv_example_image_5.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/imagebutton/lv_example_imagebutton_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/keyboard/lv_example_keyboard_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/keyboard/lv_example_keyboard_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/keyboard/lv_example_keyboard_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/label/lv_example_label_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/label/lv_example_label_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/label/lv_example_label_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/label/lv_example_label_4.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/label/lv_example_label_5.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/label/lv_example_label_6.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/led/lv_example_led_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/line/lv_example_line_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/list/lv_example_list_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/list/lv_example_list_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/lottie/lv_example_lottie_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/lottie/lv_example_lottie_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/lottie/lv_example_lottie_approve.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/menu/lv_example_menu_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/menu/lv_example_menu_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/menu/lv_example_menu_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/menu/lv_example_menu_4.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/menu/lv_example_menu_5.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/msgbox/lv_example_msgbox_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/msgbox/lv_example_msgbox_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/obj/lv_example_obj_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/obj/lv_example_obj_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/obj/lv_example_obj_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/roller/lv_example_roller_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/roller/lv_example_roller_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/roller/lv_example_roller_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/scale/lv_example_scale_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/scale/lv_example_scale_10.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/scale/lv_example_scale_11.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/scale/lv_example_scale_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/scale/lv_example_scale_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/scale/lv_example_scale_4.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/scale/lv_example_scale_5.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/scale/lv_example_scale_6.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/scale/lv_example_scale_7.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/scale/lv_example_scale_8.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/scale/lv_example_scale_9.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/slider/lv_example_slider_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/slider/lv_example_slider_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/slider/lv_example_slider_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/slider/lv_example_slider_4.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/span/lv_example_span_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/spinbox/lv_example_spinbox_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/spinner/lv_example_spinner_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/switch/lv_example_switch_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/switch/lv_example_switch_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/table/lv_example_table_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/table/lv_example_table_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/tabview/lv_example_tabview_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/tabview/lv_example_tabview_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/textarea/lv_example_textarea_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/textarea/lv_example_textarea_2.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/textarea/lv_example_textarea_3.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/textarea/lv_example_textarea_4.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/tileview/lv_example_tileview_1.c \
	../../../../../apps/common/lvgl_v9/examples/widgets/win/lv_example_win_1.c \
	../../../../../apps/common/lvgl_v9/lvgl_main.c \
	../../../../../apps/common/lvgl_v9/lvgl_v9_main_task_init.c \
	../../../../../apps/common/lvgl_v9/src/core/lv_group.c \
	../../../../../apps/common/lvgl_v9/src/core/lv_obj.c \
	../../../../../apps/common/lvgl_v9/src/core/lv_obj_class.c \
	../../../../../apps/common/lvgl_v9/src/core/lv_obj_draw.c \
	../../../../../apps/common/lvgl_v9/src/core/lv_obj_event.c \
	../../../../../apps/common/lvgl_v9/src/core/lv_obj_id_builtin.c \
	../../../../../apps/common/lvgl_v9/src/core/lv_obj_pos.c \
	../../../../../apps/common/lvgl_v9/src/core/lv_obj_property.c \
	../../../../../apps/common/lvgl_v9/src/core/lv_obj_scroll.c \
	../../../../../apps/common/lvgl_v9/src/core/lv_obj_style.c \
	../../../../../apps/common/lvgl_v9/src/core/lv_obj_style_gen.c \
	../../../../../apps/common/lvgl_v9/src/core/lv_obj_tree.c \
	../../../../../apps/common/lvgl_v9/src/core/lv_refr.c \
	../../../../../apps/common/lvgl_v9/src/display/lv_display.c \
	../../../../../apps/common/lvgl_v9/src/draw/dma2d/lv_draw_dma2d.c \
	../../../../../apps/common/lvgl_v9/src/draw/dma2d/lv_draw_dma2d_fill.c \
	../../../../../apps/common/lvgl_v9/src/draw/dma2d/lv_draw_dma2d_img.c \
	../../../../../apps/common/lvgl_v9/src/draw/jl/jldma2d/lv_draw_jldma2d.c \
	../../../../../apps/common/lvgl_v9/src/draw/jl/jldma2d/lv_draw_jldma2d_fill.c \
	../../../../../apps/common/lvgl_v9/src/draw/jl/jldma2d/lv_draw_jldma2d_img.c \
	../../../../../apps/common/lvgl_v9/src/draw/jl/jlvg/lv_draw_jlvg.c \
	../../../../../apps/common/lvgl_v9/src/draw/jl/jlvg/lv_draw_jlvg_common.c \
	../../../../../apps/common/lvgl_v9/src/draw/jl/jlvg/lv_draw_jlvg_fill.c \
	../../../../../apps/common/lvgl_v9/src/draw/jl/jlvg/lv_draw_jlvg_img.c \
	../../../../../apps/common/lvgl_v9/src/draw/jl/jlvg/lv_draw_jlvg_letter.c \
	../../../../../apps/common/lvgl_v9/src/draw/lv_draw.c \
	../../../../../apps/common/lvgl_v9/src/draw/lv_draw_3d.c \
	../../../../../apps/common/lvgl_v9/src/draw/lv_draw_arc.c \
	../../../../../apps/common/lvgl_v9/src/draw/lv_draw_buf.c \
	../../../../../apps/common/lvgl_v9/src/draw/lv_draw_image.c \
	../../../../../apps/common/lvgl_v9/src/draw/lv_draw_label.c \
	../../../../../apps/common/lvgl_v9/src/draw/lv_draw_line.c \
	../../../../../apps/common/lvgl_v9/src/draw/lv_draw_mask.c \
	../../../../../apps/common/lvgl_v9/src/draw/lv_draw_rect.c \
	../../../../../apps/common/lvgl_v9/src/draw/lv_draw_triangle.c \
	../../../../../apps/common/lvgl_v9/src/draw/lv_draw_vector.c \
	../../../../../apps/common/lvgl_v9/src/draw/lv_image_decoder.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/blend/lv_draw_sw_blend.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/blend/lv_draw_sw_blend_to_al88.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888_premultiplied.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/blend/lv_draw_sw_blend_to_i1.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/blend/lv_draw_sw_blend_to_l8.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565_swapped.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/blend/lv_draw_sw_blend_to_rgb888.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw_arc.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw_border.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw_box_shadow.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw_fill.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw_grad.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw_img.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw_letter.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw_line.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw_mask.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw_mask_rect.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw_transform.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw_triangle.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw_utils.c \
	../../../../../apps/common/lvgl_v9/src/draw/sw/lv_draw_sw_vector.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_draw_buf_vg_lite.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_draw_vg_lite.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_draw_vg_lite_arc.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_draw_vg_lite_border.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_draw_vg_lite_box_shadow.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_draw_vg_lite_fill.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_draw_vg_lite_img.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_draw_vg_lite_label.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_draw_vg_lite_layer.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_draw_vg_lite_line.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_draw_vg_lite_mask_rect.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_draw_vg_lite_triangle.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_draw_vg_lite_vector.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_vg_lite_decoder.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_vg_lite_grad.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_vg_lite_math.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_vg_lite_path.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_vg_lite_pending.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_vg_lite_stroke.c \
	../../../../../apps/common/lvgl_v9/src/draw/vg_lite/lv_vg_lite_utils.c \
	../../../../../apps/common/lvgl_v9/src/drivers/evdev/lv_evdev.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_binfont_loader.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_dejavu_16_persian_hebrew.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_fmt_txt.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_10.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_12.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_14.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_14_aligned.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_16.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_18.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_20.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_22.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_24.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_26.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_28.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_28_compressed.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_30.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_32.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_34.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_36.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_38.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_40.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_42.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_44.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_46.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_48.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_montserrat_8.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_simsun_14_cjk.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_simsun_16_cjk.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_source_han_sans_sc_14_cjk.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_source_han_sans_sc_16_cjk.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_unscii_16.c \
	../../../../../apps/common/lvgl_v9/src/font/lv_font_unscii_8.c \
	../../../../../apps/common/lvgl_v9/src/indev/lv_indev.c \
	../../../../../apps/common/lvgl_v9/src/indev/lv_indev_gesture.c \
	../../../../../apps/common/lvgl_v9/src/indev/lv_indev_scroll.c \
	../../../../../apps/common/lvgl_v9/src/layouts/flex/lv_flex.c \
	../../../../../apps/common/lvgl_v9/src/layouts/grid/lv_grid.c \
	../../../../../apps/common/lvgl_v9/src/layouts/lv_layout.c \
	../../../../../apps/common/lvgl_v9/src/libs/barcode/code128.c \
	../../../../../apps/common/lvgl_v9/src/libs/barcode/lv_barcode.c \
	../../../../../apps/common/lvgl_v9/src/libs/bin_decoder/lv_bin_decoder.c \
	../../../../../apps/common/lvgl_v9/src/libs/bmp/lv_bmp.c \
	../../../../../apps/common/lvgl_v9/src/libs/expat/xmlparse.c \
	../../../../../apps/common/lvgl_v9/src/libs/expat/xmlrole.c \
	../../../../../apps/common/lvgl_v9/src/libs/expat/xmltok.c \
	../../../../../apps/common/lvgl_v9/src/libs/expat/xmltok_impl.c \
	../../../../../apps/common/lvgl_v9/src/libs/expat/xmltok_ns.c \
	../../../../../apps/common/lvgl_v9/src/libs/ffmpeg/lv_ffmpeg.c \
	../../../../../apps/common/lvgl_v9/src/libs/freetype/lv_freetype.c \
	../../../../../apps/common/lvgl_v9/src/libs/freetype/lv_freetype_glyph.c \
	../../../../../apps/common/lvgl_v9/src/libs/freetype/lv_freetype_image.c \
	../../../../../apps/common/lvgl_v9/src/libs/freetype/lv_freetype_jlvg_ext.c \
	../../../../../apps/common/lvgl_v9/src/libs/freetype/lv_freetype_outline.c \
	../../../../../apps/common/lvgl_v9/src/libs/freetype/lv_ftsystem.c \
	../../../../../apps/common/lvgl_v9/src/libs/fsdrv/lv_fs_cbfs.c \
	../../../../../apps/common/lvgl_v9/src/libs/fsdrv/lv_fs_fatfs.c \
	../../../../../apps/common/lvgl_v9/src/libs/fsdrv/lv_fs_littlefs.c \
	../../../../../apps/common/lvgl_v9/src/libs/fsdrv/lv_fs_memfs.c \
	../../../../../apps/common/lvgl_v9/src/libs/fsdrv/lv_fs_posix.c \
	../../../../../apps/common/lvgl_v9/src/libs/fsdrv/lv_fs_stdio.c \
	../../../../../apps/common/lvgl_v9/src/libs/fsdrv/lv_fs_uefi.c \
	../../../../../apps/common/lvgl_v9/src/libs/fsdrv/lv_fs_win32.c \
	../../../../../apps/common/lvgl_v9/src/libs/gif/gifdec.c \
	../../../../../apps/common/lvgl_v9/src/libs/gif/lv_gif.c \
	../../../../../apps/common/lvgl_v9/src/libs/libjpeg_turbo/lv_libjpeg_turbo.c \
	../../../../../apps/common/lvgl_v9/src/libs/libpng/lv_libpng.c \
	../../../../../apps/common/lvgl_v9/src/libs/lodepng/lodepng.c \
	../../../../../apps/common/lvgl_v9/src/libs/lodepng/lv_lodepng.c \
	../../../../../apps/common/lvgl_v9/src/libs/lz4/lz4.c \
	../../../../../apps/common/lvgl_v9/src/libs/qrcode/lv_qrcode.c \
	../../../../../apps/common/lvgl_v9/src/libs/qrcode/qrcodegen.c \
	../../../../../apps/common/lvgl_v9/src/libs/rle/lv_rle.c \
	../../../../../apps/common/lvgl_v9/src/libs/rlottie/lv_rlottie.c \
	../../../../../apps/common/lvgl_v9/src/libs/rlottie/lv_rlottie_example_fingerprint.c \
	../../../../../apps/common/lvgl_v9/src/libs/svg/lv_svg.c \
	../../../../../apps/common/lvgl_v9/src/libs/svg/lv_svg_decoder.c \
	../../../../../apps/common/lvgl_v9/src/libs/svg/lv_svg_parser.c \
	../../../../../apps/common/lvgl_v9/src/libs/svg/lv_svg_render.c \
	../../../../../apps/common/lvgl_v9/src/libs/svg/lv_svg_token.c \
	../../../../../apps/common/lvgl_v9/src/libs/tiny_ttf/lv_tiny_ttf.c \
	../../../../../apps/common/lvgl_v9/src/libs/tjpgd/lv_tjpgd.c \
	../../../../../apps/common/lvgl_v9/src/libs/tjpgd/tjpgd.c \
	../../../../../apps/common/lvgl_v9/src/lv_init.c \
	../../../../../apps/common/lvgl_v9/src/misc/cache/class/lv_cache_lru_ll.c \
	../../../../../apps/common/lvgl_v9/src/misc/cache/class/lv_cache_lru_rb.c \
	../../../../../apps/common/lvgl_v9/src/misc/cache/instance/lv_image_cache.c \
	../../../../../apps/common/lvgl_v9/src/misc/cache/instance/lv_image_header_cache.c \
	../../../../../apps/common/lvgl_v9/src/misc/cache/lv_cache.c \
	../../../../../apps/common/lvgl_v9/src/misc/cache/lv_cache_entry.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_anim.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_anim_timeline.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_area.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_array.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_async.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_bidi.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_circle_buf.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_color.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_color_op.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_event.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_fs.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_grad.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_iter.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_ll.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_log.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_lru.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_math.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_matrix.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_palette.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_profiler_builtin.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_rb.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_style.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_style_gen.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_templ.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_text.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_text_ap.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_timer.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_tree.c \
	../../../../../apps/common/lvgl_v9/src/misc/lv_utils.c \
	../../../../../apps/common/lvgl_v9/src/osal/lv_os.c \
	../../../../../apps/common/lvgl_v9/src/osal/lv_os_jieli.c \
	../../../../../apps/common/lvgl_v9/src/osal/lv_os_none.c \
	../../../../../apps/common/lvgl_v9/src/others/file_explorer/lv_file_explorer.c \
	../../../../../apps/common/lvgl_v9/src/others/font_manager/lv_font_manager.c \
	../../../../../apps/common/lvgl_v9/src/others/font_manager/lv_font_manager_recycle.c \
	../../../../../apps/common/lvgl_v9/src/others/fragment/lv_fragment.c \
	../../../../../apps/common/lvgl_v9/src/others/fragment/lv_fragment_manager.c \
	../../../../../apps/common/lvgl_v9/src/others/gridnav/lv_gridnav.c \
	../../../../../apps/common/lvgl_v9/src/others/ime/lv_ime_pinyin.c \
	../../../../../apps/common/lvgl_v9/src/others/imgfont/lv_imgfont.c \
	../../../../../apps/common/lvgl_v9/src/others/monkey/lv_monkey.c \
	../../../../../apps/common/lvgl_v9/src/others/observer/lv_observer.c \
	../../../../../apps/common/lvgl_v9/src/others/snapshot/lv_snapshot.c \
	../../../../../apps/common/lvgl_v9/src/others/sysmon/lv_sysmon.c \
	../../../../../apps/common/lvgl_v9/src/others/test/lv_test_display.c \
	../../../../../apps/common/lvgl_v9/src/others/test/lv_test_helpers.c \
	../../../../../apps/common/lvgl_v9/src/others/test/lv_test_indev.c \
	../../../../../apps/common/lvgl_v9/src/others/test/lv_test_indev_gesture.c \
	../../../../../apps/common/lvgl_v9/src/others/test/lv_test_screenshot_compare.c \
	../../../../../apps/common/lvgl_v9/src/others/vg_lite_tvg/vg_lite_matrix.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/lv_xml.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/lv_xml_base_types.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/lv_xml_component.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/lv_xml_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/lv_xml_style.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/lv_xml_update.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/lv_xml_utils.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/lv_xml_widget.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_arc_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_bar_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_button_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_buttonmatrix_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_calendar_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_canvas_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_chart_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_checkbox_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_dropdown_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_event_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_image_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_keyboard_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_label_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_obj_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_roller_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_scale_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_slider_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_spangroup_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_table_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_tabview_parser.c \
	../../../../../apps/common/lvgl_v9/src/others/xml/parsers/lv_xml_textarea_parser.c \
	../../../../../apps/common/lvgl_v9/src/stdlib/builtin/lv_mem_core_builtin.c \
	../../../../../apps/common/lvgl_v9/src/stdlib/builtin/lv_sprintf_builtin.c \
	../../../../../apps/common/lvgl_v9/src/stdlib/builtin/lv_string_builtin.c \
	../../../../../apps/common/lvgl_v9/src/stdlib/builtin/lv_tlsf.c \
	../../../../../apps/common/lvgl_v9/src/stdlib/clib/lv_mem_core_clib.c \
	../../../../../apps/common/lvgl_v9/src/stdlib/clib/lv_sprintf_clib.c \
	../../../../../apps/common/lvgl_v9/src/stdlib/clib/lv_string_clib.c \
	../../../../../apps/common/lvgl_v9/src/stdlib/lv_mem.c \
	../../../../../apps/common/lvgl_v9/src/stdlib/micropython/lv_mem_core_micropython.c \
	../../../../../apps/common/lvgl_v9/src/stdlib/rtthread/lv_mem_core_rtthread.c \
	../../../../../apps/common/lvgl_v9/src/stdlib/rtthread/lv_sprintf_rtthread.c \
	../../../../../apps/common/lvgl_v9/src/stdlib/rtthread/lv_string_rtthread.c \
	../../../../../apps/common/lvgl_v9/src/stdlib/uefi/lv_mem_core_uefi.c \
	../../../../../apps/common/lvgl_v9/src/themes/default/lv_theme_default.c \
	../../../../../apps/common/lvgl_v9/src/themes/lv_theme.c \
	../../../../../apps/common/lvgl_v9/src/themes/mono/lv_theme_mono.c \
	../../../../../apps/common/lvgl_v9/src/themes/simple/lv_theme_simple.c \
	../../../../../apps/common/lvgl_v9/src/tick/lv_tick.c \
	../../../../../apps/common/lvgl_v9/src/widgets/3dtexture/lv_3dtexture.c \
	../../../../../apps/common/lvgl_v9/src/widgets/animimage/lv_animimage.c \
	../../../../../apps/common/lvgl_v9/src/widgets/arc/lv_arc.c \
	../../../../../apps/common/lvgl_v9/src/widgets/bar/lv_bar.c \
	../../../../../apps/common/lvgl_v9/src/widgets/button/lv_button.c \
	../../../../../apps/common/lvgl_v9/src/widgets/buttonmatrix/lv_buttonmatrix.c \
	../../../../../apps/common/lvgl_v9/src/widgets/calendar/lv_calendar.c \
	../../../../../apps/common/lvgl_v9/src/widgets/calendar/lv_calendar_chinese.c \
	../../../../../apps/common/lvgl_v9/src/widgets/calendar/lv_calendar_header_arrow.c \
	../../../../../apps/common/lvgl_v9/src/widgets/calendar/lv_calendar_header_dropdown.c \
	../../../../../apps/common/lvgl_v9/src/widgets/canvas/lv_canvas.c \
	../../../../../apps/common/lvgl_v9/src/widgets/chart/lv_chart.c \
	../../../../../apps/common/lvgl_v9/src/widgets/checkbox/lv_checkbox.c \
	../../../../../apps/common/lvgl_v9/src/widgets/dropdown/lv_dropdown.c \
	../../../../../apps/common/lvgl_v9/src/widgets/image/lv_image.c \
	../../../../../apps/common/lvgl_v9/src/widgets/imagebutton/lv_imagebutton.c \
	../../../../../apps/common/lvgl_v9/src/widgets/keyboard/lv_keyboard.c \
	../../../../../apps/common/lvgl_v9/src/widgets/label/lv_label.c \
	../../../../../apps/common/lvgl_v9/src/widgets/led/lv_led.c \
	../../../../../apps/common/lvgl_v9/src/widgets/line/lv_line.c \
	../../../../../apps/common/lvgl_v9/src/widgets/list/lv_list.c \
	../../../../../apps/common/lvgl_v9/src/widgets/lottie/lv_lottie.c \
	../../../../../apps/common/lvgl_v9/src/widgets/menu/lv_menu.c \
	../../../../../apps/common/lvgl_v9/src/widgets/msgbox/lv_msgbox.c \
	../../../../../apps/common/lvgl_v9/src/widgets/objx_templ/lv_objx_templ.c \
	../../../../../apps/common/lvgl_v9/src/widgets/property/lv_animimage_properties.c \
	../../../../../apps/common/lvgl_v9/src/widgets/property/lv_dropdown_properties.c \
	../../../../../apps/common/lvgl_v9/src/widgets/property/lv_image_properties.c \
	../../../../../apps/common/lvgl_v9/src/widgets/property/lv_keyboard_properties.c \
	../../../../../apps/common/lvgl_v9/src/widgets/property/lv_label_properties.c \
	../../../../../apps/common/lvgl_v9/src/widgets/property/lv_obj_properties.c \
	../../../../../apps/common/lvgl_v9/src/widgets/property/lv_roller_properties.c \
	../../../../../apps/common/lvgl_v9/src/widgets/property/lv_slider_properties.c \
	../../../../../apps/common/lvgl_v9/src/widgets/property/lv_style_properties.c \
	../../../../../apps/common/lvgl_v9/src/widgets/property/lv_textarea_properties.c \
	../../../../../apps/common/lvgl_v9/src/widgets/roller/lv_roller.c \
	../../../../../apps/common/lvgl_v9/src/widgets/scale/lv_scale.c \
	../../../../../apps/common/lvgl_v9/src/widgets/slider/lv_slider.c \
	../../../../../apps/common/lvgl_v9/src/widgets/span/lv_span.c \
	../../../../../apps/common/lvgl_v9/src/widgets/spinbox/lv_spinbox.c \
	../../../../../apps/common/lvgl_v9/src/widgets/spinner/lv_spinner.c \
	../../../../../apps/common/lvgl_v9/src/widgets/switch/lv_switch.c \
	../../../../../apps/common/lvgl_v9/src/widgets/table/lv_table.c \
	../../../../../apps/common/lvgl_v9/src/widgets/tabview/lv_tabview.c \
	../../../../../apps/common/lvgl_v9/src/widgets/textarea/lv_textarea.c \
	../../../../../apps/common/lvgl_v9/src/widgets/tileview/lv_tileview.c \
	../../../../../apps/common/lvgl_v9/src/widgets/win/lv_win.c \
	../../../../../apps/common/lzw/lzwlib.c \
	../../../../../apps/common/lzw/lzwtester.c \
	../../../../../apps/common/system/device_mount.c \
	../../../../../apps/common/system/init.c \
	../../../../../apps/common/system/init_expand.c \
	../../../../../apps/common/system/perf_counter/example/main.c \
	../../../../../apps/common/system/perf_counter/perf_counter.c \
	../../../../../apps/common/system/version.c \
	../../../../../apps/common/update/update.c \
	../../../../../apps/common/video/simple_avi_unpkg.c \
	../../../../../apps/demo/demo_ui/app_main.c \
	../../../../../apps/demo/demo_ui/board/wl83/board_develop.c \
	../../../../../cpu/wl83/adc_api.c \
	../../../../../cpu/wl83/debug.c \
	../../../../../cpu/wl83/debug_exception.c \
	../../../../../cpu/wl83/setup.c \


# 需要编译的 .S 文件
S_SRC_FILES := \
	../../../../../include_lib/driver/version.z.S \
	../../../../../include_lib/system/version.z.S \
	../../../../../include_lib/update/version.z.S \
	../../../../../include_lib/utils/version.z.S \
	../../../../../lib/utils/version.z.S \


# 需要编译的 .s 文件
s_SRC_FILES :=


# 需要编译的 .cpp 文件
cpp_SRC_FILES := \
	../../../../../apps/common/c++/cxx_runtime.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/binding/c/lottieanimation_capi.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottieanimation.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottieitem.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottieitem_capi.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottiekeypath.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottieloader.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottiemodel.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottieparser.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottieproxymodel.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/freetype/v_ft_math.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/freetype/v_ft_raster.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/freetype/v_ft_stroker.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/varenaalloc.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vbezier.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vbitmap.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vbrush.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vdasher.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vdebug.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vdrawable.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vdrawhelper.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vdrawhelper_common.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vdrawhelper_neon.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vdrawhelper_sse2.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/velapsedtimer.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vimageloader.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vinterpolator.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vmatrix.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vpainter.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vpath.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vpathmesure.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vraster.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vrect.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vrle.cpp \


# 需要编译的 .cc 文件
cc_SRC_FILES :=


# 需要编译的 .cxx 文件
cxx_SRC_FILES :=


# 链接参数
LFLAGS := \
	--plugin-opt=-pi32v2-always-use-itblock=false \
	--plugin-opt=-enable-ipra=true \
	--plugin-opt=-pi32v2-merge-max-offset=4096 \
	--plugin-opt=-pi32v2-enable-simd=true \
	--plugin-opt=mcpu=r3 \
	--plugin-opt=-global-merge-on-const \
	--plugin-opt=-inline-threshold=5 \
	--plugin-opt=-inline-max-allocated-size=32 \
	--plugin-opt=-inline-normal-into-special-section=true \
	--plugin-opt=-dont-used-symbol-list=malloc,free,sprintf,printf,puts,putchar \
	--plugin-opt=save-temps \
	--plugin-opt=-pi32v2-enable-rep-memop \
	--plugin-opt=-emulated-tls \
	--sort-common \
	--plugin-opt=-used-symbol-file=../../../../../cpu/wl83/sdk_used_list.used \
	--plugin-opt=-enable-movable-region=true \
	--plugin-opt=-movable-region-section-prefix=.movable.slot. \
	--plugin-opt=-movable-region-stub-section-prefix=.movable.stub. \
	--plugin-opt=-movable-region-prefix=.movable.region. \
	--plugin-opt=-movable-region-stub-prefix=__movable_stub_ \
	--plugin-opt=-movable-region-stub-swi-number=-2 \
	--plugin-opt=-movable-region-map-file-list=../../../../../apps/common/movable/funcname.txt \
	--plugin-opt=-movable-region-section-map-file-list=../../../../../apps/common/movable/section.txt \
	--plugin-opt=-movable-region-exclude-func-file-list=../../../../../apps/common/movable/exclude.txt \
	--plugin-opt=-pi32v2-large-program=true \
	--plugin-opt=-pi32v2-csync-before-rti=true \
	--start-group \
	../../../../../cpu/wl83/liba/cpu.a \
	../../../../../cpu/wl83/liba/event.a \
	../../../../../cpu/wl83/liba/system.a \
	../../../../../cpu/wl83/liba/cfg_tool.a \
	../../../../../cpu/wl83/liba/fs.a \
	../../../../../cpu/wl83/liba/common_lib.a \
	../../../../../cpu/wl83/liba/update.a \
	../../../../../cpu/wl83/liba/video.a \
	--end-group \
	../../../../../cpu/wl83/liba/lvgl_v9_extend.a \
	../../../../../include_lib/newlib/pi32v2-lib/libm.a \
	../../../../../include_lib/newlib/pi32v2-lib/libc.a \
	../../../../../include_lib/newlib/pi32v2-lib/libcompiler_rt.a \
	-T../../../../../cpu/wl83/sdk.ld \
	-M=../../../../../cpu/wl83/tools/sdk.map \
	--plugin-opt=mcpu=r3 \
	--plugin-opt=-mattr=+fprev1 \



c_OBJS    := $(c_SRC_FILES:%.c=%.c.o)
S_OBJS    := $(S_SRC_FILES:%.S=%.S.o)
s_OBJS    := $(s_SRC_FILES:%.s=%.s.o)
cpp_OBJS  := $(cpp_SRC_FILES:%.cpp=%.cpp.o)
cxx_OBJS  := $(cxx_SRC_FILES:%.cxx=%.cxx.o)
cc_OBJS   := $(cc_SRC_FILES:%.cc=%.cc.o)

OBJS      := $(c_OBJS) $(S_OBJS) $(s_OBJS) $(cpp_OBJS) $(cxx_OBJS) $(cc_OBJS)
DEP_FILES := $(OBJS:%.o=%.d)


OBJS      := $(addprefix $(BUILD_DIR)/, $(OBJS:$(ROOT_PREFIX)/%=%))
DEP_FILES := $(addprefix $(BUILD_DIR)/, $(DEP_FILES:$(ROOT_PREFIX)/%=%))


VERBOSE ?= 0
ifeq ($(VERBOSE), 1)
QUITE :=
else
QUITE := @
endif

# 一些旧的 make 不支持 file 函数，需要 make 的时候指定 LINK_AT=0 make
LINK_AT ?= 1

# 表示下面的不是一个文件的名字，无论是否存在 all, clean, pre_build 这样的文件
# 还是要执行命令
# see: https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY: all clean pre_build

# 不要使用 make 预设置的规则
# see: https://www.gnu.org/software/make/manual/html_node/Suffix-Rules.html
.SUFFIXES:

all: pre_build $(OUT_ELF)
	$(info +POST-BUILD)
	$(QUITE) $(RUN_POST_SCRIPT) sdk

pre_build:
	$(info +PRE-BUILD)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P ../../../../../cpu/wl83/sdk_used_list.c -o ../../../../../cpu/wl83/sdk_used_list.used
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P ../../../../../apps/common/movable/section.c -o ../../../../../apps/common/movable/section.txt
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P ../../../../../cpu/wl83/sdk_ld.c -o ../../../../../cpu/wl83/sdk.ld
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P ../../../../../cpu/wl83/tools/download.c -o $(POST_SCRIPT)
	$(QUITE) $(FIXBAT) $(POST_SCRIPT)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P ../../../../../cpu/wl83/tools/isd_config_rule.c -o ../../../../../cpu/wl83/tools/isd_config.ini
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P ../../../../../cpu/wl83/tools/isd_config_rule_loader.c -o ../../../../../cpu/wl83/tools/isd_config_loader.ini

clean:
	$(QUITE) $(RM) $(OUT_ELF)
	$(QUITE) $(RM) $(BUILD_DIR)



ifeq ($(LINK_AT), 1)
$(OUT_ELF): $(OBJS)
	$(info +LINK $@)
	$(shell $(MKDIR) $(@D))
	$(file >$(OBJ_FILE), $(OBJS))
	$(QUITE) $(LD) -o $(OUT_ELF) @$(OBJ_FILE) $(LFLAGS) $(LIBPATHS) $(LIBS)
else
$(OUT_ELF): $(OBJS)
	$(info +LINK $@)
	$(shell $(MKDIR) $(@D))
	$(QUITE) $(LD) -o $(OUT_ELF) $(OBJS) $(LFLAGS) $(LIBPATHS) $(LIBS)
endif


$(BUILD_DIR)/%.c.o : $(ROOT_PREFIX)/%.c
	$(info +CC $<)
	$(QUITE) $(MKDIR) $(@D)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -MMD -MF $(@:.o=.d) -c $< -o $@

$(BUILD_DIR)/%.S.o : $(ROOT_PREFIX)/%.S
	$(info +AS $<)
	$(QUITE) $(MKDIR) $(@D)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -MMD -MF $(@:.o=.d) -c $< -o $@

$(BUILD_DIR)/%.s.o : $(ROOT_PREFIX)/%.s
	$(info +AS $<)
	$(QUITE) $(MKDIR) $(@D)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -MMD -MF $(@:.o=.d) -c $< -o $@

$(BUILD_DIR)/%.cpp.o : $(ROOT_PREFIX)/%.cpp
	$(info +CXX $<)
	$(QUITE) $(MKDIR) $(@D)
	$(QUITE) $(CXX) $(CXXFLAGS) $(CFLAGS) $(DEFINES) $(INCLUDES) -MMD -MF $(@:.o=.d) -c $< -o $@

$(BUILD_DIR)/%.cxx.o : $(ROOT_PREFIX)/%.cxx
	$(info +CXX $<)
	$(QUITE) $(MKDIR) $(@D)
	$(QUITE) $(CXX) $(CXXFLAGS) $(CFLAGS) $(DEFINES) $(INCLUDES) -MMD -MF $(@:.o=.d) -c $< -o $@

$(BUILD_DIR)/%.cc.o : $(ROOT_PREFIX)/%.cc
	$(info +CXX $<)
	$(QUITE) $(MKDIR) $(@D)
	$(QUITE) $(CXX) $(CXXFLAGS) $(CFLAGS) $(DEFINES) $(INCLUDES) -MMD -MF $(@:.o=.d) -c $< -o $@

-include $(DEP_FILES)
