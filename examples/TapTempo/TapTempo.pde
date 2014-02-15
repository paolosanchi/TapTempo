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