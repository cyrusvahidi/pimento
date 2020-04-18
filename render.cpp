#include <Bela.h>
#include "Button.h"
#include "LEDS.h"
#include "Euclidean.h"
#include <math.h>


int gButton1Pin = 15;				// Pin number of the first push button
Button gButton1(gButton1Pin);       // Object maintaining first button's state
int gButton2Pin = 16;				// Pin number of the first push button
Button gButton2(gButton2Pin);       // Object maintaining first button's state

LEDS leds;

// LED stuff
bool isCyclingLeds = false;
int gLedCycleCounter = 0;

// BPM
float bpm = 120.f;
int gPulseInterval;
int gPulseCounter = 0;
int kClockPin = 7;
bool gClockOut = true;

int gFramesSinceClock;

int kPotE1Pulses = 1;
int kPotBPM = 6;

Euclidean euclidean1;
int kEuclidean1Pin = 0;
int gEuclid1Out = 0;
int gEuclidPulseCounter = 0;

void readButton(BelaContext* context, int frame, Button *button) {
	/* Debounce the button
	   If the button is closed and was not closed before, then play the drum
	*/
	button->debounce(context, frame);	
	if (button->isClosed() && !button->wasClosed())
	{
		// Reset LED states
		isCyclingLeds = !isCyclingLeds;
		gLedCycleCounter = 0;
	}
}

void pulse(BelaContext* context, int frame)
{
	if (gPulseCounter < (leds.getPulseTime() / 2.f) * context->audioSampleRate / 1000.0) 
	{
		leds.setCurrent(); 
	} 
	else 
	{
    gClockOut = false;
		leds.unsetCurrent(); 
	}
	if (gPulseCounter++ >= gPulseInterval / 2) 
	{
		gPulseCounter = 0;
    gClockOut = true;
		leds.next();
	} 
  if (++gEuclidPulseCounter >= gPulseInterval / 4 / 2)
  {
    gEuclid1Out = euclidean1.cycle();
    gEuclidPulseCounter = 0;
  } 
	leds.pulse(context, frame);
}

void clockOut(BelaContext* context, int frame) 
{
  if (gClockOut) 
  {
    analogWrite(context, frame, kClockPin, 1.0f);
  } else {
    analogWrite(context, frame, kClockPin, 0.f);
  }
}

void clockIn(BelaContext* context, int frame)
{
    float bpm = analogRead(context, frame / 2, kPotBPM);
   
    bpm = map(bpm, 0.345, 0.001, 60.f, 200.f);
    gPulseInterval = (bpm / 60.f / 4.f) * context->audioSampleRate;
}

int printC = 0;
int printInterval = 1000;

void euclidParamRead(BelaContext* context, int frame)
{
    float euclid1Pulses = analogRead(context, frame / 2, kPotE1Pulses);
    euclid1Pulses = floor(map(euclid1Pulses, 0.0001, 0.34, 0, 16));
    euclidean1.setPulses(euclid1Pulses);
    if (++printC >= printInterval / 1000 * context->audioSampleRate) {
      rt_printf("%f\n", euclid1Pulses);
      printC = 0;
    }
}

void euclidean1Out(BelaContext* context, int frame) 
{
  if (gEuclid1Out) 
  {
    analogWrite(context, frame, kEuclidean1Pin, 1.0f);
  } else {
    analogWrite(context, frame, kEuclidean1Pin, 0.f);
  } 
}

bool setup(BelaContext *context, void *userData)
{
	pinMode(context, 0, gButton1Pin, INPUT);
	for (int i = 0; i < leds.getNumLEDS(); i++) 
	{
		pinMode(context, 0, leds.getPin(i), OUTPUT);	

	}
	
	gPulseInterval = (bpm / 60.f / 4.f) * context->audioSampleRate;

  euclidean1.setPulses(5);
  euclidean1.update1();
	return true;
}

void render(BelaContext *context, void *userData)
{
//  for (unsigned int n = 0; n < context->analogFrames; n++) 
//  {
//    clockOut(context, n);
//    euclidean1Out(context, n);
//  }

	for (unsigned int n = 0; n < context->analogFrames; n++) 
	{
    clockIn(context, n / 2);
    euclidParamRead(context, n / 2);
		readButton(context, n, &gButton1);
    clockOut(context, n/2);
    euclidean1Out(context, n/2);
		pulse(context, n);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}
