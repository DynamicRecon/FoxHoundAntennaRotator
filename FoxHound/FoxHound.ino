
#include "EasyCommParser.h"

/*
* https://github.com/martinhj/LSM303DLHCreading/blob/master/LSM303DLHC.ino
* example code to add the correct sensor needed for rotator.
* this will get compass bearings and accelrometer readings...
*
*/



//rotator machine input int flag (antenna position)
int inputFlag = 0;

//current pos from accelrometer:
double currentAz = 0.0;
double currentEl = 0.0;

//next position from Com Port:
double nextAz = 0.0;
double nextEl = 0.0;

//count of chars recieved from com port:
int bufferRx = 0;

//setup serial port EasyComm parser.
EasyCommParser parser;

enum RotatorState
{
  RESET,
  IDLE,
  CW,
  CCW,
  UP,
  DN
}

RotatorState prevState;
RotatorState nextState;

/* Toggle the states of the Rotator 
*  Switch between prevState -> nextState of machine.
*/
void ToggleState(RotatorState toggleState)
{
  prevState = nextState; //store current state.
  nextState = toggleState; //toggle to next state.
}

void UpdateFlag(int &updateFlag)
{
  //checks next AZ pos - current AZ pos.
  updateFlag |= ((nextAz - currentAz) > 0);
  updateFlag |= ((nextAz - currentAx) < 0);
  updateFlag |= ((nextAz - currentAz) == 0);

  //checks next EL pos - current EL pos.
  updateFlag |= ((nextEl - currentEl) > 0);
  updateFlag |= ((nextEl - currentEl) < 0);
  updateFlag |= ((nextEl - currentEl) == 0));
}

void ClearFlag(int &updateFlag)
{
  updateFlag = 0;
}

/*run each state within setup() or loop() */
void RunState()
{
   switch(nextState) 
   {
     case RotatorState.RESET:
       //TODO: reset antenna rotator to (AZ: 0, EL: 0)
     break;
     case RotatorState.IDLE:
      //TODO: hold antenna position
     break;
     case RotatorState.CW:
      //TODO: move antenna clockwise
     break;
     case RotatorState.CCW:
     //TODO: move antenna counter-clockwise
     break;
     case RotatorState.UP:
     //TODO: move antenna up
     break;
     case RotatorState.DN:
     //TODO: move antenn down.
     break;
     default:
     break;
   }
}


void setup() 
{
  // fix serial port at 9600 baud for now.
  Serial.begin(9600);
  ToggleState(RotatorState.IDLE); //default machine state to IDLE. 
  ClearFlag(inputFlag); 
}

void loop() 
{
  // any data from serial event;
  bufferRx = parser.Parse(nextAz, nextEl);
  if(bufferRx > 0)
  {
    UpdateFlag(inputFlag); //updates flag from a range of bool flags.
    switch(inputFlag) 
    {
       case 0: //00000000
          ToggleState(RotatorState.RESET);
       break;
       case 9: //00001001
          ToggleState(RotatorState.IDLE);
       break;
       case 33: //00100001
          ToggleState(RotatorState.CW);
       break;
       case 17: //00010001
          ToggleState(RotatorState.CCW);
       break;
       case 12: //00001100
          ToggleState(RotatorState.DN);
       break;
       case 10: //00001010
          ToggleState(RotatorState.UP);
    }

  } else 
  {
    ToggleState(RotatorState.IDLE);
  }
    RunState(); //run out state.
}

/*pulls next pos of rotator from com port*/
void serialEvent() 
{
   parser.Parse(nextAz, nextEl);
   parser.SetAz(currentAz);
   parser.SetEl(currentEl);
}
