#ifndef POSSENSOR_H
#define POSSENSOR_H

#include <Arduino.h>
#include <Math.h>
#include "config.h"

/*
* Uses two potiemeters to measure the turning of the shaft.
* Reads 0 to 1023 to 0 to 360 degree integer value.
* not accurate but with 5 deg beam width. This could be corrected.
*/

float get_azimuth();
float get_inclination();

#endif