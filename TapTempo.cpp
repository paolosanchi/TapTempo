#include <TapTempo.h>

class TapTempo;
typedef void (*buttonEventHandler)(unsigned long&);

TapTempo::TapTempo()
{
	_tapCounter = 0;
}

void TapTempo::setup(unsigned long autoresetTime)
{
	_autoresetTime = autoresetTime;
}

void TapTempo::flush()
{	
	// check for timer timeout
	if (micros() > tapTimeout && _tapCounter > 0)
	{
	  // restart tap counter
	  tapTimeFilter.reset();
	  _tapCounter = 0;
	  Serial.println("Reset!");
	}
}

void TapTempo::tap()
{		   
	flush();
	
	// calculate
	_tapCounter++;
	tapTimer = micros() - lastTapTime;
	
	  Serial.print("micros: ");
	  Serial.println(micros(), DEC);
	  Serial.print("lastTapTime: ");
	  Serial.println(lastTapTime, DEC);
	//lastTapTime = micros();
	unsigned long tapCycle = tapTimeFilter.reading(tapTimer);
	if (_tapCounter >= 2)
	{
		// fire the value updated event
		if (_valueUpdated) { _valueUpdated(tapCycle); }
	}
		
	// store current time
	lastTapTime = micros();
	tapTimeout = micros() + (_autoresetTime);
	
	Serial.print("tap!");
	Serial.println(tapTimeout, DEC);
}

void TapTempo::valueUpdatedHandler(valueEventHandler handler)
{
	_valueUpdated = handler;
}