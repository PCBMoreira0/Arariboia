#include <DisplayUpdate.h>

void DisplayUpdate(void *parameters){
	constexpr int updateDelay_ms = 150;

	while(1){

		// Motor RPM
		xTaskNotifyGive(calculateAverageFrequencyTaskHandle);
		float frequencyRight;
		float frequencyLeft;
		if (xQueueReceive(averageMailboxRight, (void *)&frequencyRight, portMAX_DELAY) && xQueueReceive(averageMailboxLeft, (void *)&frequencyLeft, portMAX_DELAY))
		{
			int rpmRight = frequencyToRPM(frequencyRight);
			int rpmLeft = frequencyToRPM(frequencyLeft);
			std::string rpmRightString = std::to_string(rpmRight);
			std::string rpmLeftString = std::to_string(rpmLeft);

			bool warningActivate = false;
        	if(abs(rpmRight - rpmLeft) > 50){
            	warningActivate = true;
        	}

			xSemaphoreTake(lv_mutex, portMAX_DELAY);
			lv_label_set_text(ui_RPM_L, rpmLeftString.c_str());
			lv_label_set_text(ui_RPM_R, rpmRightString.c_str());
			if(warningActivate && lv_obj_has_flag(ui_RPM_Warning, LV_OBJ_FLAG_HIDDEN)){
			 	lv_obj_clear_flag(ui_RPM_Warning, LV_OBJ_FLAG_HIDDEN);
			}
        	else if(!warningActivate && !lv_obj_has_flag(ui_RPM_Warning, LV_OBJ_FLAG_HIDDEN)){
				lv_obj_add_flag(ui_RPM_Warning, LV_OBJ_FLAG_HIDDEN);
			}
			xSemaphoreGive(lv_mutex);
		}

		vTaskDelay(pdMS_TO_TICKS(updateDelay_ms));
	}

	vTaskDelete(NULL);
}

void DisplayUpdateInit(){
    xTaskCreate(DisplayUpdate, "DisplayUpdate", 2048, NULL, 1, NULL);
}