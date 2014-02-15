#ifndef TapTempo_h
#define TapTempo_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include <movingAvg.h>

typedef void (*valueEventHandler)(unsigned long);

class TapTempo
{
	public:
		TapTempo();
		void setup(unsigned long defaultResetTimeSpan);

		void tap();		
		void flush();		
		void reset();		
		void valueUpdatedHandler(valueEventHandler handler);
		
	private:
		unsigned int _tapCounter;
		unsigned long _lastTapTime;
		unsigned long _resetTime;
		unsigned long _defaultResetTimeSpan;
		unsigned long _resetTimeSpan;
		movingAvg tapTimeFilter;
		valueEventHandler _valueUpdated;
};

#endif
