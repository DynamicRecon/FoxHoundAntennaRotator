#ifndef POSSENSOR_H
#define POSSENSOR_H

#include <Arduino.h>
#include <Math.h>
#include "config.h"

/*
* Uses two potiemeters to measure the turning of the shaft.
*/


//startup sensor.
void setup_sensor();

//seperate functions
// void get_inclination_xy(int &accX, int &accY, int &accZ);
// void get_azimuth_xy(int &magX, int &magY, int &magZ);

void calibrate_device();
float get_azimuth();
float get_inclination();


//return position from sensor
// void notify_pos(double &curAz, double &curEl);

#endif