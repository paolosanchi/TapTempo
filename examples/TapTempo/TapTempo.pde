#include <TapTempo.h>
#include <movingAvg.h>
#include <Button.h>

#define TAP 2

TapTempo tap;
Button btn = Button(TAP, BUTTON_PULLDOWN);

void setup()
{
  tap.setup(TAP);
  tap.valueUpdatedHandler(valueChanged);  
  tap.beatHandler(beat);
  
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
  Serial.println(" ");
  Serial.println("TAP!");
  tap.tap();
}

void beat()
{  
  Serial.println("BEAT!");
}

void valueChanged(int val)
{
    Serial.print("New value!");
    Serial.println(val, DEC);
}