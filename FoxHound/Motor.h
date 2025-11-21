#ifndef MOTOR_H
#define MOTOR_H

#include <Wire.h>
#include <Arduino.h>
#include<Math.h>

#include "MyMath.h"



enum MotorMode 
{
  PWMDIR,
  FWDREV,
  ACMOTR,
  INFRARED
};

struct MotorData {
     MotorMode Type;
     int Gain;
     float Alpha;
     int LastPass;
     int FwdPin;
     int RevPin;
     unsigned long LastTime;
};

void Halt(struct MotorData *ptrMotorData);
void Drive(struct MotorData *ptrMotorData, float err);




#endif