#include "PosSensor.h"

float get_azimuth()
{
  float pot_deg = map(analogRead(AZ_POS_READ),0,1023,0,360);
  float shaft_deg = pot_deg / AZ_RATIO; //convert to shaft gear position.
  return shaft_deg;
}

float get_inclination()
{
  float pot_deg = map(analogRead(EL_POS_READ),0,1023,0,360);
  float shaft_deg = pot_deg / AZ_RATIO; //convert to shaft gear position.
  return pot_deg;
}
