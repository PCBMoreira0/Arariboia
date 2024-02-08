#include <Arduino.h>
#include <freertos\FreeRTOS.h>

extern const int motorRPMPin;

float frequencyToRPM(float t); // Calculates rpm with formula
void calculateFrequencyISR(); // ISR function 
void calculateAverageFrequency(void *parameters); // Task to calculate frequency
void PrintValuesOnSerial(void *parameters); // Task to constantly show the rpm
void MotorRPMInitialize();