#include <displayDebug.h>

void debugTask(void *parameters){
    while(1){
        char RPM_L[4];
        char RPM_R[4];
        char Current_L[4];
        char Current_R[4];
        char Voltage[4];
        char Current[4];
        int randomNumber; 
        randomNumber = random(0, 1000);
        sprintf(RPM_L, "%d", randomNumber);
        randomNumber = random(0, 1000);
        sprintf(RPM_R, "%d", randomNumber);
        randomNumber = random(0, 1000);
        sprintf(Current_L, "%d", randomNumber);
        randomNumber = random(0, 1000);
        sprintf(Current_R, "%d", randomNumber);
        randomNumber = random(0, 1000);
        sprintf(Voltage, "%d", randomNumber);
        randomNumber = random(0, 1000);
        sprintf(Current, "%d", randomNumber);
        
        bool warningActivate = false;
        /*if(abs(std::stoi(RPM_L) - std::stoi(RPM_R)) > 250){
            warningActivate = true;
        }*/

        xSemaphoreTake(lv_mutex, portMAX_DELAY);
        lv_label_set_text(ui_RPM_L, RPM_L);
        lv_label_set_text(ui_RPM_R, RPM_R);
        lv_label_set_text(ui_Current_RPM_L, Current_L);
        lv_label_set_text(ui_Current_RPM_R, Current_R);
        lv_label_set_text(ui_Battery_Value, Voltage);
        lv_label_set_text(ui_Solar_Panel_Value, Current);
        if(warningActivate && !lv_obj_has_flag(ui_RPM_Warning, LV_OBJ_FLAG_HIDDEN)) lv_obj_add_flag(ui_RPM_Warning, LV_OBJ_FLAG_HIDDEN);
        else if(warningActivate && lv_obj_has_flag(ui_RPM_Warning, LV_OBJ_FLAG_HIDDEN)) lv_obj_clear_flag(ui_RPM_Warning, LV_OBJ_FLAG_HIDDEN);
        xSemaphoreGive(lv_mutex);

        constexpr int displayRefreshRate = 500;
        vTaskDelay(pdMS_TO_TICKS(displayRefreshRate));
    }

    vTaskDelete(NULL);
}

void DisplayDebugInit(){
    xTaskCreate(debugTask, "debugTask", 2048, NULL, 1, NULL);
}