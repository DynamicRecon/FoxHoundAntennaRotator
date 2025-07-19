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

//startup sensor.
void setup_sensor();

//seperate functions
void get_inclination_xy(int &accX, int &accY, int &accZ);
void get_azimuth_xy(int &magX, int &magY, int &magZ);

//return position from sensor
void notify_pos(double &curAz, double &curEl);

//test
int assert(const char *type, double test_value);

#endif