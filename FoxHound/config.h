#ifndef _CONFIG_H
#define _CONFIG_H

#include <math.h>
#include <Arduino.h>



const int BAUD_RATE = 9600;

const int AZ_DIR_PIN = 4;  // 1 = CCW, 0 = CW
const int AZ_SPEED_PIN = 3; //PWM pin.
const int SET_AZ_SPEED = 2;

const int EL_DIR_PIN = 7; // 1 = DN, 0 = UP
const int EL_SPEED_PIN = 6; //PWM pin.
const int SET_EL_SPEED = 2;

const double BEAM_WIDTH = 5.0;

// LSM303DLHC acceerometer I2C address is 0x19(25)
const int  ADDR_ACC1 = 0x19;
// LSM303DLHC magnetometer I2C address is 0x1E(30)
const int ADDR_MAG = 0x1E;

//set Serial Speed for HamLib 
//and StepDelay for Rotator.
const int SerialSpeed = 19200;
const int StepDelay = 50; //in ms


float DegToRads(float);
float RadsToDegs(float);

float SetNewTurnRate(int);
int SetNewTimeStep(int);


#endif
