#include <Arduino.h>
#include <freertos/FreeRTOS.h>

constexpr int motorRPMPin = GPIO_NUM_36;

// Variables modified by ISR
volatile unsigned long current_duration;
volatile unsigned long total_period;
volatile int count_measures = 0;

// Variables to comunication between tasks
QueueHandle_t average_mailbox;
TaskHandle_t average_task;
SemaphoreHandle_t average_data_mutex;


float frequencyToRPM(float signalFrequency)
{
	constexpr float angularCoefficient = 15.179f;
	constexpr float linearCoefficient = -19.65f;
	return angularCoefficient * signalFrequency + linearCoefficient;
}

IRAM_ATTR void calculateFrequencyISR() 
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	unsigned long duration = micros();
	xSemaphoreTakeFromISR(average_data_mutex, &xHigherPriorityTaskWoken);
	total_period += duration - current_duration;
	current_duration = duration;
	count_measures++;
	xSemaphoreGiveFromISR(average_data_mutex, &xHigherPriorityTaskWoken);

	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void calculateAverageFrequency(void *parameters) {
	while (1) {
	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	int total = total_period;
	int count = count_measures;
	xSemaphoreTake(average_data_mutex, portMAX_DELAY);
	total_period = 0;
	count_measures = 0;
	xSemaphoreGive(average_data_mutex);

	float period = (float)total / count;
	float frequency = 1 / (period / 1000000);

	xQueueSend(average_mailbox, (void *)&frequency, portMAX_DELAY);
	}

	vTaskDelete(NULL);
}

void printValues(void *parameters) {

	// Time variables
	constexpr int show_display_delay_ms = 250;
	float frequency;

	while (1) {
	xTaskNotifyGive(average_task);
	if (xQueueReceive(average_mailbox, (void *)&frequency, portMAX_DELAY)) {
		float rpm = frequencyToRPM(frequency);
		
		/*
		if (rpm != NAN) {
		Serial.printf("RPM not detected\n");
		} else {
		Serial.printf("RPM: %f\n", rpm);
		
		}
		*/
		Serial.printf("Frequency: %.0f\t RPM: %.0f\n", frequency, rpm);
		vTaskDelay(pdMS_TO_TICKS(show_display_delay_ms));
	}
	}

	vTaskDelete(NULL);
}


//! WOKWI DEBUG
void debug_motor(void *parameters) {
	int pot;
	const float potentiometerConstant = 0.02442f;
	while (1)
	{
	digitalWrite(motorRPMPin, HIGH);
	pot = analogRead(4);
	float p = ((1 / (pot * potentiometerConstant)) / 2) * 1000;
	vTaskDelay(p / portTICK_PERIOD_MS);
	digitalWrite(motorRPMPin, LOW);
	vTaskDelay(p / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

void Initialize() {
	pinMode(motorRPMPin, INPUT);
	average_mailbox = xQueueCreate(1, sizeof(float));
	average_data_mutex = xSemaphoreCreateMutex();
	attachInterrupt(motorRPMPin, calculateFrequencyISR, RISING);
	xTaskCreate(calculateAverageFrequency, "Calculate-Average", 4096, NULL, 1, &average_task);
	xTaskCreate(printValues, "Show-Display", 4096, NULL, 1, NULL);
	//xTaskCreate(debug_motor, "Debug-Switching", 2000, NULL, 2, NULL);
}

void setup() {
	Serial.begin(115200);
	vTaskDelay(pdMS_TO_TICKS(1000));
	Serial.printf("\n---INICIALIZANDO---\n");
	Initialize();
}

void loop() {
	vTaskDelete(NULL);
}