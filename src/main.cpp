#include <Arduino.h>
#include <MotorRPM.h>
#include <DisplaySetup.h>
#include <DisplayUpdate.h>

// Debug
// #include <debugMotor.h>

void setup()
{
	Serial.begin(115200);
	// DisplayInit();

	MotorRPMInitialize();
	// DebugMotorInit();

	DisplayUpdateInit();
}

void loop()
{
	vTaskDelete(NULL);
}