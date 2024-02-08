#include <Arduino.h>
#include <freertos\FreeRTOS.h>
#include <MotorRPM.h>

void debug_motor(void *parameters)
{
	int pot;
	const float v = 0.02442;
	while (1)
	{
		pot = analogRead(4);
		float p;
		if(pot == 0){
			p = 0;
		}else{
			p = ((1 / (pot * v)) / 2) * 1000;
		}

		if(p != 0){
			digitalWrite(motorRPMPin, HIGH);
			vTaskDelay(p / portTICK_PERIOD_MS);
			digitalWrite(motorRPMPin, LOW);
			vTaskDelay(p / portTICK_PERIOD_MS);
		}
	}

	vTaskDelete(NULL);
}

void setup()
{
	Serial.begin(115200);
	vTaskDelay(pdMS_TO_TICKS(1000));
	Serial.printf("\n--- INITIALIZING MOTOR RPM ---\n");
	MotorRPMInitialize();
	xTaskCreate(debug_motor, "debugs", 4096, NULL, 1, NULL);
}

void loop()
{
	vTaskDelete(NULL);
}