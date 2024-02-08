#include <debugMotor.h>

void DebugMotor(void *parameters)
{
	constexpr float potentiometerCoeficient = 0.02442;
	// UBaseType_t uxHighWaterMark;

	while (1)
	{
		int potentiometerValue = analogRead(4);
		float delayTime;
		if(potentiometerValue == 0){
			delayTime = 0;
		}else{
			delayTime = ((1 / (potentiometerValue * potentiometerCoeficient)) / 2) * 1000;
		}

		if(delayTime != 0){
			digitalWrite(motorRPMPin, HIGH);
			vTaskDelay(delayTime / portTICK_PERIOD_MS);
			digitalWrite(motorRPMPin, LOW);
			vTaskDelay(delayTime / portTICK_PERIOD_MS);
		}

		// uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
		// Serial.print("High water mark (words) da task atual: ");
		// Serial.println(uxHighWaterMark);
	}

	vTaskDelete(NULL);
}

void DebugMotorInit(){
	xTaskCreate(DebugMotor, "DebugMotor", 1024, NULL, 1, NULL);
}
