TapTempo
========

An Arduino tap tempo library
----------------------------

With this library you can obtain the time difference between multiple input.
It is still in developement, please, give me a couple of day to wire everything up.

Every idea to enanche it are welcome!

Usage sample
------------
```
#include <TapTempo.h>
#include <movingAvg.h>
#include <Button.h>

#define TAP 2

TapTempo tap;
Button btn = Button(TAP, BUTTON_PULLDOWN);

void setup()
{
  tap.setup(2);
  tap.valueUpdatedHandler(onValueChange);  
  
  btn.clickHandler(onTempoClick);
  Serial.begin(9600);
}

void loop()
{  
  tap.flush();
  btn.isPressed();
}

void onTempoClick(Button &b)
{
  tap.tap();
}

void onValueChange(unsigned long val)
{
    Serial.print("New value: ");
    Serial.println(val, DEC);
}
```
