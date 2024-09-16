#ifndef _CONFIG_H
#define _CONFIG_H

#include <math.h>
#include <Arduino.h>



const int BAUD_RATE = 19200;
const int STEP_DELAY = 50; //ms

//AZ direction pins (set speed by controller)
const int AZ_DIR_PIN_B = 4; 
const int AZ_DIR_PIN_A = 3; 

//EL direction pins (set speed by controller)
const int EL_DIR_PIN_B = 7;
const int EL_DIR_PIN_A = 6; 

//beamwidth of antenna to keep tracking sat signal from falling out.
const double BEAM_WIDTH = 5.0;

// LSM303DLHC acceerometer I2C address is 0x19(25)
const int  ADDR_ACC1 = 0x19;
// LSM303DLHC magnetometer I2C address is 0x1E(30)
const int ADDR_MAG = 0x1E;

//set Serial Speed for HamLib 
//and StepDelay for Rotator.
const int SerialSpeed = 19200;
const int StepDelay = 50; //in ms


//math helper funcs
float DegToRads(float);
float RadsToDegs(float);

//direct set variables from arduino analog pins (if neeeded)
float SetNewTurnRate(int);
int SetNewTimeStep(int);


#endif
