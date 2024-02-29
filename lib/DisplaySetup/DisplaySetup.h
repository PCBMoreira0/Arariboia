#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <lvgl.h>
#include <ui.h>
#include <freertos/FreeRTOS.h>

extern SemaphoreHandle_t lv_mutex;

void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data );
void LV_Task(void *parameters);
void DisplayInit();