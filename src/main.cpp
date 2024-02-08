#include <Arduino.h>
#include <freertos\FreeRTOS.h>
#include <MotorRPM.h>
#include <debugMotor.h>

void setup()
{
	Serial.begin(115200);
	vTaskDelay(pdMS_TO_TICKS(1000));
	Serial.printf("\n--- INITIALIZING MOTOR RPM ---\n");
	MotorRPMInitialize();

	DebugMotorInit();
}

void loop()
{
	vTaskDelete(NULL);
}