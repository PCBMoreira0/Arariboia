#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <cmath>

extern const int motorRPMLeftPin;
extern const int motorRPMRightPin;

extern TaskHandle_t calculateAverageFrequencyTaskHandle;

extern QueueHandle_t averageMailboxRight;
extern QueueHandle_t averageMailboxLeft;

float frequencyToRPM(float t); // Calculates rpm with formula
void calculateFrequencyISR(); // ISR function 
void calculateAverageFrequency(void *parameters); // Task to calculate frequency
void PrintValuesOnSerial(void *parameters); // Task to constantly show the rpm
void MotorRPMInitialize();
void GetRPM(int *left, int *right);