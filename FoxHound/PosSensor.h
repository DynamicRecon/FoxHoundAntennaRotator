#ifndef POSSENSOR_H
#define POSSENSOR_H

#include <Wire.h>
#include <Arduino.h>
#include <Math.h>
#include "config.h"

void setup_sensor();

double get_inclination();
double get_azimuth();

void notify_pos(double &curAz, double &curEl);

#endif