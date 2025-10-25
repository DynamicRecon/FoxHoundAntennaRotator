#ifndef _CONFIG_H
#define _CONFIG_H

#include <math.h>
#include <Arduino.h>



const int BAUD_RATE = 19200;
const int STEP_DELAY = 5000; //ms

//AZ direction pins (set speed by controller)
const int AZ_DIR_PIN_B = 4; 
const int AZ_DIR_PIN_A = 3; 

//EL direction pins (set speed by controller)
const int EL_DIR_PIN_B = 7;
const int EL_DIR_PIN_A = 6; 

//AZ potiemeter pin
const int AZ_POS_READ = A4;
const int EL_POS_READ = A5;

//beamwidth of antenna to keep tracking sat signal from falling out.
const double BEAM_WIDTH = 5.0;

//set Serial Speed for HamLib 
//and StepDelay for Rotator.
const int SerialSpeed = 19200;
const int StepDelay = 50; //in ms


//math helper funcs
float DegToRads(float);
float RadsToDegs(float);


#endif
