#include <Arduino.h>
#include <freertos\FreeRTOS.h>

float frequencyToRPM(float t); // Calculates rpm with formula
void calculateFrequencyISR(); // ISR function 
void calculateAverageFrequency(void *parameters); // Task to calculate frequency
void PrintValuesOnSerial(void *parameters); // Task to constantly show the rpm
void debug_motor(void *parameters); // Task to simulate motor signal
void Initialize();