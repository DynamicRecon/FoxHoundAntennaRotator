#ifndef POSSENSOR_H
#define POSSENSOR_H

#include<Arduino.h>
#include<Math.h>
#include<Wire.h>
#include <EEPROM.h>

#include "MyMath.h"

enum SensorType 
{
   LSM303D,
   LSM303DLHC
};

struct Cal 
{
    int Offset;
    int Scale;
    int Min;
    int Max;
};

struct Cal _lsmCal;

void ResetCal(struct Cal *ptrCal);
void ComputeCal(struct Cal *ptrCal);
void SampleCal(struct Cal *ptrCal, int a, bool changed);

#endif