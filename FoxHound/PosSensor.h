#ifndef POSSENSOR_H
#define POSSENSOR_H

#include <Wire.h>
#include <Arduino.h>
#include <Math.h>
#include "config.h"

/*
*https://github.com/ControlEverythingCommunity/LSM303DLHC/blob/master/Arduino/LSM303DLHC.ino
* example code to add the correct sensor needed for rotator.
* this will get compass bearings and accelrometer readings...
*
*/

void setup_sensor();

double get_inclination();
double get_azimuth();

void notify_pos(double &curAz, double &curEl);

#endif