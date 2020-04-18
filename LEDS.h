/***** LEDS.h *****/
/***** LEDS.h *****/
/***** LEDS.h *****/
// A class to represent a LEDS

#include <Bela.h>

class LEDS
{
	public:
		LEDS();
		
		
		void pulse(BelaContext* context, int frame);	
		void next();
		
		void setCurrent();
		void unsetCurrent();
		
		int getPulseTime();
		int getNumLEDS();
		
		int getPin(int index);
		
	private:
		const int NUM_LEDS = 10;
		
		int curIndex;
		int ledPulseTime;	    // time for led pulse to stay on
		int ledPins[10] = {6,7,10,2,3,0,1,4,5,8};
		int ledStates[10] = {LOW};
};
