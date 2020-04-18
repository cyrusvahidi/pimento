/***** LEDS.C *****/
/***** Button.cpp *****/
/* Adapted from an in-class implementation of a debounced button
   Debounce state transition formulated by Andrew Mcpherson
*/
#include "LEDS.h"

LEDS::LEDS() {
	curIndex = 0;
	ledPulseTime = 60;
	
}

void LEDS::pulse(BelaContext* context, int frame) {
	digitalWrite(context, frame, ledPins[curIndex], ledStates[curIndex]);
}

void LEDS::next()
{
	curIndex = (curIndex + 1) % NUM_LEDS;
}

void LEDS::setCurrent()
{
	ledStates[curIndex] = HIGH;
}

void LEDS::unsetCurrent()
{
	ledStates[curIndex] = LOW;
}

int LEDS::getPulseTime() 
{
	return ledPulseTime;
}

int LEDS::getNumLEDS()
{
	return NUM_LEDS;
}

int LEDS::getPin(int index)
{
	return ledPins[index];
}
