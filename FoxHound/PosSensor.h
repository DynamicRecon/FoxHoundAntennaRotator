#ifndef POSSENSOR_H
#define POSSENSOR_H

#include <Wire.h>
#include <Arduino.h>
#include "config.h"

void setup_sensor();

void notify_pos(double &curAz, double &curEl);

#endif