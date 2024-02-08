#include <MotorRPM.h>

constexpr int motorRPMPin = GPIO_NUM_2;

// Variables modified by ISR
volatile unsigned long lastTimeMeasured;
volatile unsigned long totalTimeSum;
volatile int totalMeasuresMade = 0;

// Variables to comunication between tasks
QueueHandle_t averageMailbox;
TaskHandle_t calculateAverageFrequencyTaskHandle;
SemaphoreHandle_t sharedDataMutexHandle;

float frequencyToRPM(float signalFrequency){
	constexpr float angularCoefficient = 15.179f;
	constexpr float linearCoefficient = -19.65f;
	return angularCoefficient * signalFrequency + linearCoefficient;
}

IRAM_ATTR void calculateFrequencyISR(){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	unsigned long currentTime = micros();
	xSemaphoreTakeFromISR(sharedDataMutexHandle, &xHigherPriorityTaskWoken);
	totalTimeSum += currentTime - lastTimeMeasured;
	lastTimeMeasured = currentTime;
	totalMeasuresMade++;
	xSemaphoreGiveFromISR(sharedDataMutexHandle, &xHigherPriorityTaskWoken);

	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void calculateAverageFrequency(void *parameters){
	while (1)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		int totalSum = totalTimeSum;
		int totalMeasures = totalMeasuresMade;
		xSemaphoreTake(sharedDataMutexHandle, portMAX_DELAY);
		totalTimeSum = 0;
		totalMeasuresMade = 0;
		xSemaphoreGive(sharedDataMutexHandle);

		float period = (float)totalSum / totalMeasures;
		float frequency = 1 / (period / 1000000);

		xQueueSend(averageMailbox, (void *)&frequency, portMAX_DELAY);
	}

	vTaskDelete(NULL);
}

void PrintValuesOnSerial(void *parameters){
	constexpr int printDelay_ms = 500;

	while (1)
	{
		xTaskNotifyGive(calculateAverageFrequencyTaskHandle);
		float frequency;
		if (xQueueReceive(averageMailbox, (void *)&frequency, portMAX_DELAY))
		{
			int rpm = frequencyToRPM(frequency);

			// Serial.printf("Frequency: %f   RPM: %d\n", frequency, rpm);

			// Comment this if you are not using Wokwi
			Serial.print("Frequency: ");
			Serial.print(frequency);
			Serial.print("   RPM: ");
			Serial.print(rpm);
			Serial.println();

			vTaskDelay(pdMS_TO_TICKS(printDelay_ms));
		}
	}

	vTaskDelete(NULL);
}

void MotorRPMInitialize()
{
	pinMode(motorRPMPin, OUTPUT);
	averageMailbox = xQueueCreate(1, sizeof(float));
	sharedDataMutexHandle = xSemaphoreCreateMutex();
	attachInterrupt(motorRPMPin, calculateFrequencyISR, RISING);
	xTaskCreate(calculateAverageFrequency, "Calculate-Average", 2000, NULL, 1, &calculateAverageFrequencyTaskHandle);
	xTaskCreate(PrintValuesOnSerial, "Show-Display", 1000, NULL, 1, NULL);
}