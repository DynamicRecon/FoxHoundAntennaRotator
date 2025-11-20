
#include "Communication.h"
#include "Motor.h"
#include "MyMath.h"
#include "defs.h"

/*Enum of antenna's current state.*/
enum RotatorState
{
  IDLE,
  CW,
  CCW,
  UP,
  DN
};

enum RotatorMode
{
  TRACKING, 
  MONITORING, 
  DEMONSTRATING, 
  CALIBRATING, 
  DEBUGGING, 
  PAUSING
};    //Rotator controller modes

RotatorMode _prevMode = TRACKING;
RotatorMode _nextMode = TRACKING;

void _ToggleMode(RotatorMode toggleMode) 
{
  _prevMode = _nextMode;
  _nextMode = toggleMode;
}

//Rotator state variables.
RotatorState prevState = IDLE;
RotatorState nextState = IDLE;

/* Toggle the states of the Rotator 
*  Switch between prevState -> nextState of machine.
*  returns void.
*/
void _ToggleState(RotatorState toggleState)
{
  prevState = nextState; //store current state.
  nextState = toggleState; //toggle to next state.
}

bool windup;            //Antenna windup condition

/* Fox Hound Rotator Struct */
struct FoxHoundTable 
{
  float Az;               //Antenna azimuth
  float El;               //Antenna elevation
  float AzSet;            //Antenna azimuth set point
  float ElSet;            //Antenna elevation set point
  float AzLast;           //Last antenna azimuth reading
  float ElLast;           //Last antenna element reading
  float AzWindup;         //Antenna windup angle from startup azimuth position
  float AzOffset;         //Antenna azimuth offset for whole revolutions
  float AzSpeed;          //Antenna azimuth motor speed
  float ElSpeed;          //Antenna elevation motor speed
  float AzError;          //Antenna azimuth error
  float ElError;          //Antenna elevation error
  float AzInc;            //AZ increment for demo mode
  float ElInc;            //EL increment for demo mode
};

void _ResetRotator(struct FoxHoundTable *ptrTable, bool getCal) 
{
  //Reset the rotator table.
  ptrTable->AzSet = 0.0;
  ptrTable->ElSet = 0.0;
  ptrTable->AzLast = 0.0;
  ptrTable->ElLast = 0.0;
  ptrTable->AzWindup = 0.0;
  ptrTable->AzOffset = 0.0;
  ptrTable->AzSpeed = 0.0;
  ptrTable->ElSpeed = 0.0;
  ptrTable->AzError = 0.0;
  ptrTable->ElError = 0.0;
  ptrTable->AzInc = 0.05;
  ptrTable->ElInc = 0.05;
  
  //reset calibration setting in eeprom.
  if(getCal) 
  {

  }

  //restore Rotator Mode to: TRACKING.
  _ToggleMode(TRACKING);

}

//count of chars recieved from com port:
int _bufferRx = 0;

//setup serial port EasyComm parser.
EasyCommParser parser;

/*
 * procedure turns on the motors in the rotator to poiint the antenna.
 * returns void.
*/
void _MoveToTarget()
{
 switch(nextState)
 {
    case CW:
      //move antenna CW
      
    break;
    case CCW:
      //move antenna CCW
      
    break;
    case UP:
      //move antenna UP
      
    break;
    case DN:
      //move antenna DOWN
      
    break;
    case IDLE:
      //stop.
      
    break;
  }

}



/*
* procedure calculates any difference in changes between next rotation and current position
* then toggle's the antennas state from IDLE -> CW, CCW, UP, DN states to adjust
* the antennas rotation.
* returns void.
*/
void RunState()
{
   
}

void setup() 
{
  // fix serial port at 9600 baud for now.
  Serial.begin(BAUD_RATE);
  //Set speaker pins to outputs
  pinMode(SPKPIN, OUTPUT);
  pinMode(GNDPIN, OUTPUT);
  digitalWrite(GNDPIN, LOW);

  pinMode(AZBRKPIN, OUTPUT);
  pinMode(ELBRKPIN, OUTPUT);
  digitalWrite(AZBRKPIN, LOW);
  digitalWrite(ELBRKPIN, LOW);
  
  _ToggleState(IDLE); //default machine state to IDLE. 
  _MoveToTarget();
  
}

void loop() 
{
  
  delay(STEP_DELAY); //wait.
}
