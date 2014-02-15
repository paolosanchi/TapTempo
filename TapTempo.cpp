#include <TapTempo.h>

class TapTempo;
typedef void (*buttonEventHandler)(unsigned long&);

TapTempo::TapTempo()
{
	_tapCounter = 0;
}

void TapTempo::setup(unsigned long defaultResetTimeSpan)
{
	_defaultResetTimeSpan = defaultResetTimeSpan * 1000000;
	reset();
}

void TapTempo::flush()
{	
	// check for timer timeout
	unsigned long currentTapTime = micros();
	if (currentTapTime > _resetTime && _tapCounter > 0)
	{
		reset();
	}
}

void TapTempo::reset()
{
	// restart tap counter
	tapTimeFilter.reset();
	_tapCounter = 0;
	_resetTimeSpan = _defaultResetTimeSpan;
	
	Serial.println(" ");
	Serial.print("Reset! ");
}

void TapTempo::tap()
{		   
	flush();	// in case the client forget it :)
	
	unsigned long currentTapTime = micros();
	
	_tapCounter++;
	if(_tapCounter > 1){
	
		unsigned long tapDiff = currentTapTime - _lastTapTime;
		
		Serial.println("currentTapTime - currentTapTime =  tapDiff");
		Serial.print(currentTapTime, DEC);
		Serial.print(" - ");
		Serial.print(_lastTapTime, DEC);
		Serial.print(" = ");
		Serial.println(tapDiff, DEC);
		
		Serial.print("tapDiff: ");
		Serial.println(int(tapDiff / 1000), DEC);		

		int tapCycle = tapTimeFilter.reading(int(tapDiff / 1000));
		Serial.print("tapCycle: ");
		Serial.println(tapCycle, DEC);
		
		if (_tapCounter >= 2)
		{
			// fire the value updated event
			if (_valueUpdated) { _valueUpdated(tapCycle); }
		}
				
		_resetTimeSpan = long(tapCycle) * 1000 * 2;
	}
	
	// store current time
	_lastTapTime = currentTapTime;
	_resetTime = currentTapTime + _resetTimeSpan;
	
	Serial.print("_resetTimeSpan: ");
	Serial.println(_resetTimeSpan, DEC);	
	Serial.print("_resetTime: ");
	Serial.println(_resetTime, DEC);	
}

void TapTempo::valueUpdatedHandler(valueEventHandler handler)
{
	_valueUpdated = handler;
}