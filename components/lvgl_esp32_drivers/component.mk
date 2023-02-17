# LVGL ESP32 drivers

# Define sources and include dirs
COMPONENT_SRCDIRS := . lvgl_tft
COMPONENT_ADD_INCLUDEDIRS := .

# LVGL is supposed to be used as a ESP-IDF component
# -> lvlg is already in the include path
# -> we use simple include
CFLAGS += -DLV_LVGL_H_INCLUDE_SIMPLE

# TFT display drivers
COMPONENT_ADD_INCLUDEDIRS += lvgl_tft


$(call compile_only_if,$(CONFIG_LV_TFT_DISPLAY_CONTROLLER_ILI9488),lvgl_tft/ili9488.o)
$(call compile_only_if,$(CONFIG_LV_TFT_DISPLAY_PROTOCOL_SPI),lvgl_tft/disp_spi.o)
