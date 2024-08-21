
#include "EasyCommParser.h"
#include "config.h"
#include "PosSensor.h"

/*
* https://github.com/martinhj/LSM303DLHCreading/blob/master/LSM303DLHC.ino
* example code to add the correct sensor needed for rotator.
* this will get compass bearings and accelrometer readings...
*
*/


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
  IDLE,
  CW,
  CCW,
  UP,
  DN
};

RotatorState prevState = IDLE;
RotatorState nextState = IDLE;

/* Toggle the states of the Rotator 
*  Switch between prevState -> nextState of machine.
*/
void toggle_state(RotatorState toggleState)
{
  prevState = nextState; //store current state.
  nextState = toggleState; //toggle to next state.
}


void move_to_target()
{
 switch(nextState)
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
void run_state()
{
   if ((nextAz - currentAz) == BEAM_WIDTH && (nextEl - currentEl) == BEAM_WIDTH)
   {
      toggle_state(IDLE);
   } else if ((nextAz - currentAz) > BEAM_WIDTH)
   {
      toggle_state(CW);
   } else if ((nextAz - currentAz) < BEAM_WIDTH)
   {
      toggle_state(CCW);
   } else if ((nextEl - currentEl) >  BEAM_WIDTH)
   {
      toggle_state(UP);
   } else if ((nextEl - currentEl) < BEAM_WIDTH)
   {
      toggle_state(DN);
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
  toggle_state(IDLE); //default machine state to IDLE. 
  setup_sensor();
}

void loop() 
{
   bufferRx = parser.Parse(nextAz, nextEl);
   notify_pos(currentAz, currentEl); //update position from sensor.
   parser.SetAz(currentAz);
   parser.SetEl(currentEl);
   run_state(); //toggle state.
   move_to_target(); //move antenna.
}
