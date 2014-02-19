#ifndef TapTempo_h
#define TapTempo_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include <movingAvg.h>

typedef void (*valueEventHandler)(int);
typedef void (*beatEventHandler)();

class TapTempo
{
	public:
		TapTempo();
		void setup(unsigned long defaultResetTimeSpan, int beatSubdivisions);

		bool tap();		
		void flush();		
		void reset();		
		void valueUpdatedHandler(valueEventHandler handler);
		void beatHandler(beatEventHandler handler);
		int getLastValue();
		
	private:
		unsigned int _lastValue;
		unsigned int _tapCounter;
		unsigned long _lastTapTime;
		unsigned long _resetTime;
		unsigned long _defaultResetTimeSpan;
		unsigned long _resetTimeSpan;
		unsigned long _beatTime;
		movingAvg tapTimeFilter;
		valueEventHandler _valueUpdated;
		beatEventHandler _beat;
};

#endif
