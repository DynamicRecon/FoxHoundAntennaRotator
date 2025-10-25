#include "PosSensor.h"


float get_azimuth()
{
  int pot_deg = map(analogRead(AZ_POS_READ),0,1023,0,360);
  return pot_deg;
}

float get_inclination()
{
  int pot_deg = map(analogRead(EL_POS_READ),0,1023,0,360);
  return pot_deg;
}
