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
	unsigned long currentTime = micros();
	if (currentTime > _resetTime && _tapCounter > 0)
	{
		reset();
	}
	if(currentTime > _beatTime && _lastValue != 0)
	{
		if (_beat)
		{
			_beat(); 
			_beatTime = currentTime + (long(_lastValue) * 1000);
		}
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

int TapTempo::getLastValue()
{
	return _lastValue;
}

bool TapTempo::tap()
{		   
	flush();	// in case the client forget it :)
	
	unsigned long currentTapTime = micros();
	
	_tapCounter++;
	bool newValue = _tapCounter > 1;
	if(newValue){
	
		unsigned long tapDiff = currentTapTime - _lastTapTime;
		
		Serial.println("currentTapTime - currentTapTime =  tapDiff");
		Serial.print(currentTapTime, DEC);
		Serial.print(" - ");
		Serial.print(_lastTapTime, DEC);
		Serial.print(" = ");
		Serial.println(tapDiff, DEC);
		
		Serial.print("tapDiff: ");
		Serial.println(int(tapDiff / 1000), DEC);		

		_lastValue = tapTimeFilter.reading(int(tapDiff / 1000));
		Serial.print("_lastValue: ");
		Serial.println(_lastValue, DEC);
		
		if (_tapCounter >= 2)
		{
			// fire the value updated event
			if (_valueUpdated) { _valueUpdated(_lastValue); }
		}
				
		_resetTimeSpan = long(_lastValue) * 1000 * 2;
	}
	
	// store current time
	_lastTapTime = currentTapTime;
	_resetTime = currentTapTime + _resetTimeSpan;
	_beatTime = currentTapTime + (long(_lastValue) * 1000);
	
	Serial.print("_resetTimeSpan: ");
	Serial.println(_resetTimeSpan, DEC);	
	Serial.print("_resetTime: ");
	Serial.println(_resetTime, DEC);	
	
	return newValue;
}

void TapTempo::valueUpdatedHandler(valueEventHandler handler)
{
	_valueUpdated = handler;
}

void TapTempo::beatHandler(beatEventHandler handler)
{
	_beat = handler;
}