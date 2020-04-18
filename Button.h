/***** Button.h *****/
/***** Button.h *****/
// A class to represent a button
// Its debounce state begins on object initialisation
// All values read from the button are debounced by a maintained debounce state

#include <Bela.h>

class Button 
{
	// State machine states
	enum {
		kStateOpen = 0,
		kStateJustClosed,
		kStateClosed,
		kStateJustOpen
	};
	
	public:
		Button(int channel);
		
		void debounce(BelaContext* context, int frame);
		
		bool isOpen();
		
		bool isClosed();
		
		bool wasClosed();
		
	private:
		int debounceState;
		int debounceCounter;
		int debounceInterval;	// 20 ms
		int buttonPreviousValue;
		int channel;
		bool buttonPreviousStateWasClosed;
};