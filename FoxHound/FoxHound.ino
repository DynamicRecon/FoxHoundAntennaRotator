
#include "Communication.h"
#include "Motor.h"
#include "MyMath.h"
#include "Timer.h"
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


bool windup;            //Antenna windup condition
struct Timer _t1; //timer struct
struct FoxHoundTable _table;
struct MotorData _azMot = { FWDREV, 25, 0.5, 0, AZFWDPIN, AZREVPIN, 0 }; //AZ Motor Settings
struct MotorData _elMot = { FWDREV, 25, 0.5, 0, ELFWDPIN, ELREVPIN, 0 }; //EL Motor Settings
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


void SetMode()
{
  switch(_nextMode)
  {
    case DEBUGGING:
    break;
    case CALIBRATING:
    break;
    case PAUSING:
    break;
    default:
    break;
  }
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

  TimerReset(&_t1, 100);
  _ResetRotator(&_table, true);
  
}

void loop() 
{
  
  delay(STEP_DELAY); //wait.
}
