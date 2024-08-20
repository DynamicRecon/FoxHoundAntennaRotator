
#include "EasyCommParser.h"
#include "config.h"
#include "PosSensor.h"

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
};

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
  updateFlag |= ((nextAz - currentAz) < 0);
  updateFlag |= ((nextAz - currentAz) == 0);

  //checks next EL pos - current EL pos.
  updateFlag |= ((nextEl - currentEl) > 0);
  updateFlag |= ((nextEl - currentEl) < 0);
  updateFlag |= ((nextEl - currentEl) == 0);
}

void ClearFlag(int &updateFlag)
{
  updateFlag = 0;
}

void ResetAntenna()
{

}

void MoveAz(RotatorState curState)
{
  switch(curState)
  {
    case CW:
      //move antenna CW
      digitalWrite(AZ_DIR_PIN, 0);
      analogWrite(AZ_SPEED_PIN, SET_AZ_SPEED/4);
    break;
    case CCW:
      //move antenna CCW
      digitalWrite(AZ_DIR_PIN, 1);
      analogWrite(AZ_SPEED_PIN, SET_AZ_SPEED/4);
    break;
  }
}

void MoveEl(RotatorState curState)
{
   switch(curState)
   {
    case UP:
      //move antenna UP
      digitalWrite(EL_DIR_PIN, 0);
      analogWrite(EL_SPEED_PIN, SET_EL_SPEED/4);
    break;
    case DN:
      //move antenna DOWN
      digitalWrite(EL_DIR_PIN, 1);
      analogWrite(EL_SPEED_PIN, SET_EL_SPEED/4);
    break;
   }
}


/*run each state within setup() or loop() */
void RunState()
{
   switch(nextState) 
   {
     case RESET:
       //TODO: reset antenna rotator to (AZ: 0, EL: 0)
       ResetAntenna();
     break;
     case IDLE:
      //TODO: hold antenna position
     break;
     case CW:
       MoveAz(nextState);
     break;
     case CCW:
       MoveAz(nextState);
     break;
     case UP:
       MoveEl(nextState);
     break;
     case DN:
       MoveEl(nextState);
     break; 
     default:
     break;
   }
}


void setup() 
{
  // fix serial port at 9600 baud for now.
  Serial.begin(BAUD_RATE);
  pinMode(AZ_SPEED_PIN, OUTPUT);
  pinMode(AZ_DIR_PIN, OUTPUT);
  pinMode(EL_SPEED_PIN, OUTPUT);
  pinMode(EL_DIR_PIN, OUTPUT);
  ToggleState(IDLE); //default machine state to IDLE. 
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
          ToggleState(RESET);
       break;
       case 9: //00001001
          ToggleState(IDLE);
       break;
       case 33: //00100001
          ToggleState(CW);
       break;
       case 17: //00010001
          ToggleState(CCW);
       break;
       case 12: //00001100
          ToggleState(DN);
       break;
       case 10: //00001010
          ToggleState(UP);
    }

  } else 
  {
    ToggleState(IDLE);
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
