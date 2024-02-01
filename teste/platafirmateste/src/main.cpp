#include <Arduino.h>
#include <freertos/FreeRTOS.h>

constexpr int pin = GPIO_NUM_2;

// Variables modified by ISR
volatile unsigned long current_duration;
volatile unsigned long total_period;
volatile int count_measures = 0;

// Variables to comunication between tasks
QueueHandle_t average_mailbox;
TaskHandle_t average_task;
SemaphoreHandle_t average_data_mutex;

// Time variables
int show_display_delay = 500; // ms

float rpm_line(float t)
{
  return 15.179 * t - 19.65;
}

void calc_Freq_ISR()
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

void calculate_frequency(void *parameters)
{
  float frequency;

  while (1)
  {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    int total = total_period;
    int count = count_measures;
    xSemaphoreTake(average_data_mutex, portMAX_DELAY);
    total_period = 0;
    count_measures = 0;
    xSemaphoreGive(average_data_mutex);

    float period = (float)total / count;
    frequency = 1 / (period / 1000000);

    xQueueSend(average_mailbox, (void *)&frequency, portMAX_DELAY);
  }

  vTaskDelete(NULL);
}

void show_display(void *parameters)
{
  float frequency;

  while (1)
  {
    xTaskNotifyGive(average_task);
    if (xQueueReceive(average_mailbox, (void *)&frequency, portMAX_DELAY))
    {
      Serial.println(rpm_line(frequency));

      vTaskDelay(show_display_delay / portTICK_PERIOD_MS);
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
    digitalWrite(pin, HIGH);
    pot = analogRead(4);
    float p = ((1 / (pot * v)) / 2) * 1000;
    vTaskDelay(p / portTICK_PERIOD_MS);
    digitalWrite(pin, LOW);
    vTaskDelay(p / portTICK_PERIOD_MS);
  }

  vTaskDelete(NULL);
}

void Initialize()
{
  pinMode(pin, OUTPUT);
  average_mailbox = xQueueCreate(1, sizeof(float));
  average_data_mutex = xSemaphoreCreateMutex();
  attachInterrupt(pin, calc_Freq_ISR, RISING);
  xTaskCreate(calculate_frequency, "Calculate-Average", 2000, NULL, 1, &average_task);
  xTaskCreate(show_display, "Show-Display", 1000, NULL, 1, NULL);
  xTaskCreate(debug_motor, "Debug-Switching", 2000, NULL, 2, NULL);
}

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("--- INICIALIZANDO ---");

  Initialize();

  Serial.println("--- TÉRMINO ---");
}

void loop()
{
}