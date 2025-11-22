
#include "Communication.h"
#include "Motor.h"
#include "PosSensor.h"
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

/* Fox Hound Rotator Table Data. Gets Vectors for calculation to next position of rotator. */
struct FoxHoundTable 
{
  float Az;               //Antenna azimuth
  float El;               //Antenna elevation
  Vec AntennaPos;         //antenna position
  double AzSet;            //Antenna azimuth set point
  double ElSet;            //Antenna elevation set point
  Vec Target;              //Target Vector
  double AzLast;           //Last antenna azimuth reading
  double ElLast;           //Last antenna element reading
  float AzError;          //Get Diff to Target Vector Azimuth
  float ElError;         //Get Diff to Target Vector Elevation
};

void _ResetRotator(struct FoxHoundTable Table, bool getCal) 
{
  //Reset the rotator table.
  Table.AzSet = 0.0;
  Table.ElSet = 0.0;
  Table.AzLast = 0.0;
  Table.ElLast = 0.0;
  Table.AzError = 0.0f;
  Table.ElError = 0.0f;
  Table.AntennaPos = Vec(0.0,0.0,0.0);
  Table.Target = Vec(0.0,0.0,0.0);

  //reset calibration setting in eeprom.
  if(getCal) 
  {
    _Restore();
  }

  //restore Rotator Mode to: TRACKING.
  ToggleMode(TRACKING);

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

struct Lsm _posSensor;

void _Save() {
  //Save the calibration data to EEPROM
  EEPROM.put(0, _posSensor.Cal);
}

void _Restore() {
  //Restore the calibration data from EEPROM
  EEPROM.get(0, _posSensor.Cal);
}

void _PrintDebug() 
{
  //Print raw sensor data
  Serial.print(_posSensor.Mx); Serial.print(",");
  Serial.print(_posSensor.My); Serial.print(",");
  Serial.print(_posSensor.Mz); Serial.print(",");
  Serial.print(_posSensor.Gx); Serial.print(",");
  Serial.print(_posSensor.Gy); Serial.print(",");
  Serial.println(_posSensor.Gz);
}

void _PrintCal() 
{
  //Print the calibration data
  Serial.print(_posSensor.Cal.Md, 1); Serial.print(",");
  Serial.print(_posSensor.Cal.Me.i, 1); Serial.print(",");
  Serial.print(_posSensor.Cal.Me.j, 1); Serial.print(",");
  Serial.print(_posSensor.Cal.Me.k, 1); Serial.print(",");
  Serial.print(_posSensor.Cal.Ge.i, 1); Serial.print(",");
  Serial.print(_posSensor.Cal.Ge.j, 1); Serial.print(",");
  Serial.print(_posSensor.Cal.Ge.k, 1); Serial.print(",");
  Serial.print(_posSensor.Cal.Ms.i, 1); Serial.print(",");
  Serial.print(_posSensor.Cal.Ms.j, 1); Serial.print(",");
  Serial.print(_posSensor.Cal.Ms.k, 1); Serial.print(",");
  Serial.print(_posSensor.Cal.Gs.i, 1); Serial.print(",");
  Serial.print(_posSensor.Cal.Gs.j, 1); Serial.print(",");
  Serial.println(_posSensor.Cal.Gs.k, 1);
}

void _Calibrate() 
{
  //Process raw accelerometer and magnetometer samples
  bool changed = Calibrate(&_posSensor);
  //Print any changes and beep the speaker to facilitate manual calibration
  if (changed) 
  {
    digitalWrite(SPKPIN, HIGH);     //Sound the piezo buzzer
    _PrintCal();                     //Print the calibration data
  } else 
  {
    digitalWrite(SPKPIN, LOW);      //Silence the piezo buzzer
  }
}

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

/*gets Arduino State. Then processes accordingly...*/
void _ProcessPosition()
{
  ReadGM(&_posSensor);
  switch(GetCurrentMode())
  {
    case DEBUGGING:
      _PrintDebug();
    break;
    case CALIBRATING:
      _Calibrate(); //Do a sensor Calibration.
    break;
    case PAUSING:
      Halt(&_azMot); //Halt Azimuth Motor
      Halt(&_elMot); //Halt Elevation Motor
    break;
    default: //Otherwise start Tracking...
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

  _posSensor.Type = LSM303DLHC;
  _posSensor.Alpha = 0.02;

  Begin(&_posSensor);

  TimerReset(&_t1, 100);
  _ResetRotator(_table, true);
  
}

void loop() 
{
  ProcessCommands(_table.AzSet, _table.ElSet); //get one letter commands from Serial Monitor
  Execute(&_t1, &_ProcessPosition);
  _MoveToTarget();
  delay(STEP_DELAY); //wait.
}
