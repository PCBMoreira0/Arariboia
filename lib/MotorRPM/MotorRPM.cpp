#include <MotorRPM.h>

constexpr int motorRPMLeftPin = GPIO_NUM_25;
constexpr int motorRPMRightPin = GPIO_NUM_26;

// Variables modified by ISR
// Right Motor
volatile unsigned long lastTimeMeasuredRight;
volatile unsigned long totalTimeSumRight;
volatile int totalMeasuresMadeRight = 0;

// Left Motor
volatile unsigned long lastTimeMeasuredLeft;
volatile unsigned long totalTimeSumLeft;
volatile int totalMeasuresMadeLeft = 0;

// Variables to comunication between tasks
QueueHandle_t averageMailboxRight;
QueueHandle_t averageMailboxLeft;

TaskHandle_t calculateAverageFrequencyTaskHandle;
SemaphoreHandle_t sharedDataMutexHandle;

float frequencyToRPM(float signalFrequency)
{
	constexpr float angularCoefficient = 31.0974029f;
	constexpr float linearCoefficient = -37.8278051f;

	if (signalFrequency <= 0)
		return 0;

	return angularCoefficient * signalFrequency + linearCoefficient;
}

float errorMarginCorrect(float wrongFrequency)
{
	constexpr float angularCoefficient = 0.071789;
	constexpr float linearCoefficient = -3.391956;

	return angularCoefficient * wrongFrequency + linearCoefficient;
}

IRAM_ATTR void calculateFrequencyRightISR()
{
	constexpr int threshold = 500;

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	int analogValue = analogRead(motorRPMRightPin);
	if (analogValue > threshold)
	{
		unsigned long currentTime = micros();
		xSemaphoreTakeFromISR(sharedDataMutexHandle, &xHigherPriorityTaskWoken);

		totalTimeSumRight += currentTime - lastTimeMeasuredRight;
		lastTimeMeasuredRight = currentTime;
		totalMeasuresMadeRight++;

		xSemaphoreGiveFromISR(sharedDataMutexHandle, &xHigherPriorityTaskWoken);

		portYIELD_FROM_ISR();
	}
}

IRAM_ATTR void calculateFrequencyLeftISR()
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	unsigned long currentTime = micros();
	xSemaphoreTakeFromISR(sharedDataMutexHandle, &xHigherPriorityTaskWoken);

	totalTimeSumLeft += currentTime - lastTimeMeasuredLeft;
	lastTimeMeasuredLeft = currentTime;
	totalMeasuresMadeLeft++;

	xSemaphoreGiveFromISR(sharedDataMutexHandle, &xHigherPriorityTaskWoken);

	portYIELD_FROM_ISR();
}

void calculateAverageFrequency(void *parameters)
{
	while (1)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		int totalSumRight = totalTimeSumRight;
		int totalSumLeft = totalTimeSumLeft;

		int totalMeasuresRight = totalMeasuresMadeRight;
		int totalMeasureLeft = totalMeasuresMadeLeft;

		xSemaphoreTake(sharedDataMutexHandle, portMAX_DELAY);
		totalTimeSumRight = 0;
		totalTimeSumLeft = 0;
		totalMeasuresMadeRight = 0;
		totalMeasuresMadeLeft = 0;
		xSemaphoreGive(sharedDataMutexHandle);

		// Right
		float periodRight = (float)totalSumRight / totalMeasuresRight;
		float frequencyRight;

		if (isnan(periodRight))
		{
			frequencyRight = 0;
		}
		else
		{
			frequencyRight = 1 / (periodRight / 1000000);
		}

		// Left
		float periodLeft = (float)totalSumLeft / totalMeasureLeft;
		float frequencyLeft;

		if (isnan(periodLeft))
		{
			frequencyLeft = 0;
		}
		else
		{
			frequencyLeft = 1 / (periodLeft / 1000000);
		}

		frequencyRight = errorMarginCorrect(frequencyRight);
		frequencyLeft = errorMarginCorrect(frequencyLeft);

		xQueueSend(averageMailboxRight, (void *)&frequencyRight, portMAX_DELAY);
		xQueueSend(averageMailboxLeft, (void *)&frequencyLeft, portMAX_DELAY);
	}

	vTaskDelete(NULL);
}

void PrintValuesOnSerial(void *parameters)
{
	constexpr int printDelay_ms = 500;

	while (1)
	{
		xTaskNotifyGive(calculateAverageFrequencyTaskHandle);
		float frequencyRight;
		float frequencyLeft;
		if (xQueueReceive(averageMailboxRight, (void *)&frequencyRight, portMAX_DELAY) && xQueueReceive(averageMailboxLeft, (void *)&frequencyLeft, portMAX_DELAY))
		{
			int rpmRight = frequencyToRPM(frequencyRight);
			int rpmLeft = frequencyToRPM(frequencyLeft);

			// Serial.printf("Frequency L: %f   RPM L: %d\n", frequencyLeft, rpmLeft);
			// Serial.printf("Frequency R: %f   RPM R: %d\n", frequencyRight, rpmRight);

			// Comment this if you are not using Wokwi
			Serial.print("Frequency L: ");
			Serial.print(frequencyLeft);
			Serial.print("   RPM L: ");
			Serial.print(rpmLeft);
			Serial.println();
			Serial.print("Frequency R: ");
			Serial.print(frequencyRight);
			Serial.print("   RPM R: ");
			Serial.print(rpmRight);
			Serial.println();
			Serial.println();

			vTaskDelay(pdMS_TO_TICKS(printDelay_ms));
		}
	}

	vTaskDelete(NULL);
}

void MotorRPMInitialize()
{
	pinMode(motorRPMRightPin, INPUT);
	pinMode(motorRPMLeftPin, INPUT);

	averageMailboxRight = xQueueCreate(1, sizeof(float));
	averageMailboxLeft = xQueueCreate(1, sizeof(float));

	sharedDataMutexHandle = xSemaphoreCreateMutex();

	attachInterrupt(motorRPMRightPin, calculateFrequencyRightISR, RISING);
	attachInterrupt(motorRPMLeftPin, calculateFrequencyLeftISR, RISING);

	xTaskCreate(calculateAverageFrequency, "Calculate-Average", 1010, NULL, 1, &calculateAverageFrequencyTaskHandle);
	xTaskCreate(PrintValuesOnSerial, "Show-Display", 2030, NULL, 1, NULL);
}