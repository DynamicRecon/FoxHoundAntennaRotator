
#include <math.h>
#include <Arduino.h>
#include "config.h"

float DegToRads(float value) { return  M_PI * value / 180.0; }
float RadsToDegs(float value) { return (180.0 / M_PI) * value; }

float SetNewTurnRate(int pin) 
{
  float ret = 0.0;
  int val = analogRead(pin);
  if (val <= 0) 
  {
     return 0.0;
    
  }
  //map 0 to 10 to between 0 and 1 floating value
  ret = DegToRads(val / 100);
  return ret;
}

int SetNewTimeStep(int pin) 
{
  int ret = 0;
  int val = analogRead(pin);
  if(val <= 0) 
  {
      return 0;  
  }
  ret = map(val, 0, 1023, 0, 1000);
  return ret;
}
