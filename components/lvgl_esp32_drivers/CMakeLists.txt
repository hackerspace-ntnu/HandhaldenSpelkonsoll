if(ESP_PLATFORM)

file(GLOB SOURCES *.c)
set(LVGL_INCLUDE_DIRS . lvgl_tft)
list(APPEND SOURCES "lvgl_tft/disp_driver.c")

if(CONFIG_LV_TFT_DISPLAY_CONTROLLER_ILI9488)
    list(APPEND SOURCES "lvgl_tft/ili9488.c")
else()
    message(WARNING "LVGL ESP32 drivers: Display controller not defined.")
endif()

if(CONFIG_LV_TFT_DISPLAY_PROTOCOL_SPI)
    list(APPEND SOURCES "lvgl_tft/disp_spi.c")
endif()

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS ${LVGL_INCLUDE_DIRS}
                       REQUIRES lvgl)

target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_LVGL_H_INCLUDE_SIMPLE")

else()
    message(FATAL_ERROR "LVGL ESP32 drivers: ESP_PLATFORM is not defined. Try reinstalling ESP-IDF.")
endif()
