#include "Timer.h"

Timer t;

int ledEvent;

void setup()
{
  Serial.begin(9600);
  int tickEvent = t.every(2000, doSomething, (void*)2);
  Serial.print("2 second tick started id=");
  Serial.println(tickEvent);
  
  pinMode(13, OUTPUT);
  ledEvent = t.oscillate(13, 50, HIGH);
  Serial.print("LED event started id=");
  Serial.println(ledEvent);
  
  int afterEvent = t.after(10000, doAfter, (void*)10);
  Serial.print("After event started id=");
  Serial.println(afterEvent); 
  
}

void loop()
{
  t.update();
}

void doSomething(void* context)
{
  int time = (int)context;
  Serial.print(time);
  Serial.print(" second tick: millis()=");
  Serial.println(millis());
}


void doAfter(void* context)
{
  int time = (int)context;
  Serial.print("stopping the led event after ");
  Serial.print(time);
  Serial.println(" seconds.");
  t.stop(ledEvent);
  t.oscillate(13, 500, HIGH, 5);
}
