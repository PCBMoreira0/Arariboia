#include <debugMotor.h>

void DebugMotorRight(void *parameters)
{
	constexpr float potentiometerCoeficient = 0.02442;
	// UBaseType_t uxHighWaterMark;

	while (1)
	{
		int potentiometerValue = analogRead(35);
		float delayTime;
		if(potentiometerValue == 0){
			delayTime = 0;
		}else{
			delayTime = ((1 / (potentiometerValue * potentiometerCoeficient)) / 2) * 1000;
		}

		if(delayTime != 0){
			digitalWrite(motorRPMRightPin, HIGH);
			vTaskDelay(delayTime / portTICK_PERIOD_MS);
			digitalWrite(motorRPMRightPin, LOW);
			vTaskDelay(delayTime / portTICK_PERIOD_MS);
		}

		// uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
		// Serial.print("High water mark (words) da task atual: ");
		// Serial.println(uxHighWaterMark);
	}

	vTaskDelete(NULL);
}

void DebugMotorLeft(void *parameters)
{
	constexpr float potentiometerCoeficient = 0.02442;
	// UBaseType_t uxHighWaterMark;

	while (1)
	{
		int potentiometerValue = analogRead(34);
		float delayTime;
		if(potentiometerValue == 0){
			delayTime = 0;
		}else{
			delayTime = ((1 / (potentiometerValue * potentiometerCoeficient)) / 2) * 1000;
		}

		if(delayTime != 0){
			digitalWrite(motorRPMLeftPin, HIGH);
			vTaskDelay(delayTime / portTICK_PERIOD_MS);
			digitalWrite(motorRPMLeftPin, LOW);
			vTaskDelay(delayTime / portTICK_PERIOD_MS);
		}

		// uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
		// Serial.print("High water mark (words) da task atual: ");
		// Serial.println(uxHighWaterMark);
	}

	vTaskDelete(NULL);
}

void DebugMotorInit(){
	pinMode(34, INPUT);
	pinMode(35, INPUT);
	xTaskCreate(DebugMotorRight, "DebugMotorRight", 2048, NULL, 1, NULL);
	xTaskCreate(DebugMotorLeft, "DebugMotorLeft", 2048, NULL, 1, NULL);
}
