#include "motor_rpm.h"

#define pin 2

// Variables modified by ISR
volatile unsigned long current_duration;
volatile unsigned long total_period;
volatile int count_measures = 0;

// Variables to comunication between tasks
QueueHandle_t average_mailbox;
TaskHandle_t average_task;

// Time variables
//int calculate_average_delay = 100; // ms

int show_display_delay = 500; // ms

float frequencyToRPM(float t){
  return 15.179 * t - 19.65;
}

void calculateFrequencyISR(){
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  unsigned long duration = micros();
  total_period = duration - current_duration;
  current_duration = duration;

  /*
  unsigned long duration = micros();
  total_period += duration - current_duration;
  current_duration = duration;
  count_measures++;
  */
  
  vTaskNotifyGiveFromISR(average_task, &xHigherPriorityTaskWoken);

  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void calculateAverageFrequency(void *parameters){
  float frequency;

  while(1){
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    frequency = 1/((float)total_period/1000000); // ms to seconds
    xQueueSend(average_mailbox, (void *)&frequency, portMAX_DELAY);
  }

  // Average version
  /*
  while(1){
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    float period = (float)total_period / count_measures;
    frequency = 1/(period/1000000);

    xQueueSend(average_mailbox, (void *)&frequency, portMAX_DELAY);

    vTaskDelay(calculate_average_delay / portTICK_PERIOD_MS);
  }
  */

  vTaskDelete(NULL);
}

void PrintValuesOnSerial(void *parameters){
  float frequency;

  while(1){
    if(xQueueReceive(average_mailbox, (void *)&frequency, portMAX_DELAY)){
      Serial.println(frequencyToRPM(frequency));
      
      vTaskDelay(show_display_delay / portTICK_PERIOD_MS);
    }
  }

  vTaskDelete(NULL);
}

void debug_motor(void *parameters){
  while(1){
    digitalWrite(motorRPMPin, HIGH);
    vTaskDelay(500/portTICK_PERIOD_MS);
    digitalWrite(motorRPMPin, LOW);
    vTaskDelay(500/portTICK_PERIOD_MS);
  }

  vTaskDelete(NULL);
}

void Initialize(){
  pinMode(motorRPMPin, OUTPUT);
  average_mailbox = xQueueCreate(5, sizeof(float));
  attachInterrupt(motorRPMPin, calculateFrequencyISR, RISING);
  xTaskCreate(calculateAverageFrequency, "Calculate-Average", 2000, NULL, 1, &average_task);
  xTaskCreate(PrintValuesOnSerial, "Show-Display", 1000, NULL, 1, NULL);
  xTaskCreate(debug_motor, "Debug-Switching", 1000, NULL, 1, NULL);
}