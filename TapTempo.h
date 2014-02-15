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
		void setup(unsigned long autoresetTime);

		void tap();		
		void flush();		
		void valueUpdatedHandler(valueEventHandler handler);
		
	private:
		int _tapCounter;
		uint32_t lastTapTime;
		int tapTimer;
		int tapTimeout;
		unsigned long _autoresetTime;
		movingAvg tapTimeFilter;
		valueEventHandler _valueUpdated;
};

#endif
