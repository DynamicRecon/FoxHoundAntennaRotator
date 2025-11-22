#ifndef POSSENSOR_H
#define POSSENSOR_H

#include<Arduino.h>
#include<Math.h>
#include<Wire.h>
#include <EEPROM.h>

#include "MyMath.h"
#include "defs.h"

enum SensorType 
{
   LSM303D,
   LSM303DLHC
};

struct Lsm 
{
  SensorType Type;
  float Alpha;
  int Mx, My, Mz, Gx, Gy, Gz = 0;
  float Az, El = 0.0f;
  struct {float Md = 0.0f; Vec Me, Ge, Ms, Gs = Vec(0.0f,0.0f,0.0f); } Cal;
};



void Begin(struct Lsm *lsm);
bool Calibrate(struct Lsm *lsm);
void ReadGM(struct Lsm *lsm);
Vec GetVector(struct Lsm *lsm); //converts sensor data to vector.
void ResetSensor(struct Lsm *lsm);
void CalStart(struct Lsm *lsm);

#endif