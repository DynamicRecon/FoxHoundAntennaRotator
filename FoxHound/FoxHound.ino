
#include "EasyCommParser.h"
#include "config.h"
#include "PosSensor.h"


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
      digitalWrite(EL_DIR_PIN_A, 0);
      digitalWrite(EL_DIR_PIN_B, 0);
      digitalWrite(AZ_DIR_PIN_A, 0);
      digitalWrite(AZ_DIR_PIN_B, 1);
    break;
    case CCW:
      //move antenna CCW
      digitalWrite(EL_DIR_PIN_A, 0);
      digitalWrite(EL_DIR_PIN_B, 0);
      digitalWrite(AZ_DIR_PIN_A, 1);
      digitalWrite(AZ_DIR_PIN_B, 0);
    break;
    case UP:
      //move antenna UP
      digitalWrite(EL_DIR_PIN_A, 0);
      digitalWrite(EL_DIR_PIN_B, 1);
      digitalWrite(AZ_DIR_PIN_A, 0);
      digitalWrite(AZ_DIR_PIN_B, 0);
    break;
    case DN:
      //move antenna DOWN
      digitalWrite(EL_DIR_PIN_A, 1);
      digitalWrite(EL_DIR_PIN_B, 0);
      digitalWrite(AZ_DIR_PIN_A, 0);
      digitalWrite(AZ_DIR_PIN_B, 0);
    break;
    case IDLE:
      digitalWrite(EL_DIR_PIN_A, 0);
      digitalWrite(EL_DIR_PIN_B, 0);
      digitalWrite(AZ_DIR_PIN_A, 0);
      digitalWrite(AZ_DIR_PIN_B, 0);
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
  pinMode(AZ_DIR_PIN_A, OUTPUT);
  pinMode(AZ_DIR_PIN_B, OUTPUT);
  pinMode(EL_DIR_PIN_A, OUTPUT);
  pinMode(EL_DIR_PIN_B, OUTPUT);
  toggle_state(IDLE); //default machine state to IDLE. 
  setup_sensor();
}

void loop() 
{
   notify_pos(currentAz, currentEl);
   parser.SetAz(currentAz);
   parser.SetEl(currentEl);
   parser.Parse(nextAz, nextEl);
   run_state(); //toggle state.
   move_to_target(); //move antenna.
   delay(STEP_DELAY);
}
