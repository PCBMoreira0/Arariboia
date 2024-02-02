#include <Arduino.h>
#include <freertos\FreeRTOS.h>

constexpr int motorRPMPin = GPIO_NUM_2;

// Variables modified by ISR
volatile unsigned long lastTimeMeasured;
volatile unsigned long totalTimeSum;
volatile int totalMeasuresMade = 0;

// Variables to comunication between tasks
QueueHandle_t averageMailbox;
TaskHandle_t calculateAverageFrequencyTaskHandle;
SemaphoreHandle_t sharedDataMutexHandle;

float frequencyToRPM(float signalFrequency)
{
	constexpr float angularCoefficient = 15.179f;
	constexpr float linearCoefficient = -19.65f;
	return angularCoefficient * signalFrequency + linearCoefficient;
}


IRAM_ATTR void calculateFrequencyISR()
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	unsigned long currentTime = micros();
	xSemaphoreTakeFromISR(sharedDataMutexHandle, &xHigherPriorityTaskWoken);
	totalTimeSum += currentTime - lastTimeMeasured;
	lastTimeMeasured = currentTime;
	totalMeasuresMade++;
	xSemaphoreGiveFromISR(sharedDataMutexHandle, &xHigherPriorityTaskWoken);

	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void calculateAverageFrequency(void *parameters)
{
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

void PrintValuesOnSerial(void *parameters)
{
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

void debug_motor(void *parameters)
{
	int pot;
	const float v = 0.02442;
	while (1)
	{
		digitalWrite(motorRPMPin, HIGH);
		pot = analogRead(4);
		float p = ((1 / (pot * v)) / 2) * 1000;
		vTaskDelay(p / portTICK_PERIOD_MS);
		digitalWrite(motorRPMPin, LOW);
		vTaskDelay(p / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

void Initialize()
{
	pinMode(motorRPMPin, OUTPUT);
	averageMailbox = xQueueCreate(1, sizeof(float));
	sharedDataMutexHandle = xSemaphoreCreateMutex();
	attachInterrupt(motorRPMPin, calculateFrequencyISR, RISING);
	xTaskCreate(calculateAverageFrequency, "Calculate-Average", 2000, NULL, 1, &calculateAverageFrequencyTaskHandle);
	xTaskCreate(PrintValuesOnSerial, "Show-Display", 1000, NULL, 1, NULL);
	xTaskCreate(debug_motor, "Debug-Switching", 2000, NULL, 2, NULL);
}

void setup()
{
	Serial.begin(115200);
	vTaskDelay(pdMS_TO_TICKS(1000));
	Serial.printf("\n--- INITIALIZING MOTOR RPM ---\n");

	Initialize();
}

void loop()
{
	vTaskDelete(NULL);
}