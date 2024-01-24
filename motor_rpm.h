#include <Arduino.h>
#include <freertos\FreeRTOS.h>

float rpm_line(float t); // Calculates rpm with formula
void calc_Freq_ISR(); // ISR function 
void calculate_frequency(void *parameters); // Task to calculate frequency
void show_display(void *parameters); // Task to constantly show the rpm
void debug_motor(void *parameters); // Task to simulate motor signal
void Initialize();