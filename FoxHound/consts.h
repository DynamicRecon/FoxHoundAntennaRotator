#ifndef CONSTANTS_H
#define CONSTANTS_H

//Filter constants
const float AZALPHA = 0.5; //Alpha value for AZ motor filter: Decrease to slow response time and reduce motor dither.
const float ELALPHA = 0.5; //Alpha value for EL motor filter: Decrease to slow response time and reduce motor dither.
const float LSMALPHA = 0.02; //Alpha value for sensor filter: Decrease to slow response time and ease calibration process.

//Motor drive gains. These set the amount of motor drive close to the set point
const int AZGAIN = 25;   //Azimuth motor gain
const int ELGAIN = 25;   //Elevation motor gain

//beamwidth of antenna to keep tracking sat signal from falling out.
const int BEAM_WIDTH = 5.0;

//set Serial Speed for HamLib 
//and StepDelay for Rotator.
const int SerialSpeed = 19200;
const int StepDelay = 50; //in ms


#endif