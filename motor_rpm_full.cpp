#include <Arduino.h>
#include <freertos\FreeRTOS.h>

#define pin 2

// Variables modified by ISR
volatile unsigned long current_duration;
volatile unsigned long total_period;
volatile int count_measures = 0;

// Variables to comunication between tasks
QueueHandle_t average_mailbox;
TaskHandle_t average_task;

// Time variables
//int calculate_average_delay = 50; // ms

int show_display_delay = 500; // ms

float rpm_line(float t){
  return 15.179 * t - 19.65;
}

void calc_Freq_ISR(){
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  unsigned long duration = micros();
  total_period = duration - current_duration;
  current_duration = duration;

  // Average version
  // unsigned long duration = micros();
  // total_period += duration - current_duration;
  // current_duration = duration;
  // count_measures++;
  
  
  vTaskNotifyGiveFromISR(average_task, &xHigherPriorityTaskWoken);

  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void calculate_frequency(void *parameters){
  float frequency;

  while(1){
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    frequency = 1/((float)total_period/1000000); // ms to seconds
    xQueueOverwrite(average_mailbox, (void *)&frequency);
  }

  // Average version
  /*while(1){
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    float period = (float)total_period / count_measures;
    frequency = 1/(period/1000000);

    xQueueSend(average_mailbox, (void *)&frequency, portMAX_DELAY);
    total_period = 0;
    count_measures = 0;
    vTaskDelay(calculate_average_delay / portTICK_PERIOD_MS);
  }*/
  

  vTaskDelete(NULL);
}

void show_display(void *parameters){
  float frequency;

  while(1){
    if(xQueueReceive(average_mailbox, (void *)&frequency, portMAX_DELAY)){
      Serial.println(rpm_line(frequency));
      
      vTaskDelay(show_display_delay / portTICK_PERIOD_MS);
    }
  }

  vTaskDelete(NULL);
}

void debug_motor(void *parameters){
  while(1){
    digitalWrite(pin, HIGH);
    vTaskDelay(6.4/portTICK_PERIOD_MS);
    digitalWrite(pin, LOW);
    vTaskDelay(6.4/portTICK_PERIOD_MS);
  }

  vTaskDelete(NULL);
}

void Initialize(){
  pinMode(pin, OUTPUT);
  average_mailbox = xQueueCreate(1, sizeof(float));
  attachInterrupt(pin, calc_Freq_ISR, RISING);
  xTaskCreate(calculate_frequency, "Calculate-Average", 2000, NULL, 1, &average_task);
  xTaskCreate(show_display, "Show-Display", 1000, NULL, 1, NULL);
  xTaskCreate(debug_motor, "Debug-Switching", 1000, NULL, 1, NULL);
}

void setup(){
  Serial.begin(9600);
  Serial.println();
  Serial.println("--- INICIALIZANDO ---");
  
  Initialize();

  Serial.println("--- TÉRMINO ---");
}

void loop(){

}
