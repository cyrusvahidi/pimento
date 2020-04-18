/***** Button.cpp *****/
/* Adapted from an in-class implementation of a debounced button
   Debounce state transition formulated by Andrew Mcpherson
*/
#include "Button.h"

Button::Button(int channel) {
	this->channel = channel;
	debounceCounter = 0;
	debounceInterval = 882;
	debounceState = kStateOpen;
	buttonPreviousValue = 0;
	buttonPreviousStateWasClosed = false;
}

void Button::debounce(BelaContext* context, int frame) {
	int value = digitalRead(context, frame, channel);	
   	if(debounceState == kStateOpen) {
   		// Button is not pressed, could be pressed anytime
   		// Input: look for switch closure
  		// digitalWrite(context, n, gLEDPin, LOW);
   		if (value == LOW && buttonPreviousValue == HIGH) {
   			debounceState = kStateJustClosed;
   		}
 		buttonPreviousStateWasClosed = false;
   	}
   	else if (debounceState == kStateJustClosed) {
  		// Button was just pressed, wait for debounce
   		// Input: run counter, wait for timeout
   		if (debounceInterval <= ++debounceCounter) {
   			debounceState = kStateClosed;
   			debounceCounter = 0;
   		}
  		buttonPreviousStateWasClosed = false;
   	}
   	else if (debounceState == kStateClosed) {
   		// Button is pressed, could be released anytime
   		// Input: look for switch opening
   		// digitalWrite(context, n, gLEDPin, HIGH);
   		if (value == HIGH) {                               
   			debounceState = kStateJustOpen;  
   		}
   		buttonPreviousStateWasClosed = true;
   	}
   	else if (debounceState == kStateJustOpen) {
   		// Button was just released, wait for debounce              
   		// Input: run counter, wait for timeout
   		if (debounceInterval <= ++debounceCounter) {
   			debounceState = kStateOpen;
   			debounceCounter = 0;
   		}
  		buttonPreviousStateWasClosed = false;
   	}

   	// Update the previous button value
   	buttonPreviousValue = value;
}

bool Button::isOpen() {
	return debounceState == kStateOpen;
}

bool Button::isClosed() {
	return debounceState == kStateClosed;
}

bool Button::wasClosed() {
	return buttonPreviousStateWasClosed;
}
