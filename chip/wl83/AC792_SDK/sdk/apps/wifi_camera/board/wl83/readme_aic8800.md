现已支持AIC8800 WiFi驱动，如需替换请将当前路径下的Makefile做如下修改：

1. 加入相关库(建议用--start-group \ ，  --end-group \包住)：
    --start-group \
	../../../../cpu/wl83/liba/hsm_ext.a \
	../../../../cpu/wl83/liba/libaicwifi.a \
	../../../../cpu/wl83/liba/sdio_card.a \
	../../../../cpu/wl83/liba/ext_wifi_dev.a \
    --end-group \
2. 删去792内置WiFi库： wl_wifi.a

