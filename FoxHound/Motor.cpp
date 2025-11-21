#include "Motor.h"

void _Infrared(struct MotorData *ptrMotorData, float err)
{
   //unimplemented, TODO: pull some code from the FoxIR Sketch for this procedure.
}

void _PwmDir(struct MotorData *ptrMotorData, float err)
{
   //Calculate the speed. Then filter the result.
   ptrMotorData->LastPass = 0; //reset filter.
   float dv = constrain(err * ptrMotorData->Gain, -255, 255);
   dv = Lpf(dv, ptrMotorData->Alpha, ptrMotorData->LastPass);

   //For interfacing with the LMD18200T DC Motor H-Bridge
   //Set motor speed;
   if(abs(err) < 0.5)
   {
     analogWrite(ptrMotorData->FwdPin, 0); //disengage the motor. When error is too small to reduce dither. (noise and current consumption)
   } else 
   {
     analogWrite(ptrMotorData->FwdPin, (byte)(dv)); //drive the motor
   }
   
   //tell the motor which way to turn...
   digitalWrite(ptrMotorData->RevPin, (dv > 0) ? HIGH : LOW);
}

void _FwdRev(struct MotorData *ptrMotorData, float err)
{
  //Calculate the speed. Then filter the result.
  ptrMotorData->LastPass = 0; //reset filter.
  float dv = constrain(err * ptrMotorData->Gain, -255, 255);
  dv = Lpf(dv, ptrMotorData->Alpha, ptrMotorData->LastPass);

  //For interfacing with L298N H-bridge.
  //Set the Motor Speed.
  if(abs(err) < 0.5)
  {
    analogWrite(ptrMotorData->FwdPin, 0);
    analogWrite(ptrMotorData->RevPin, 0);
  } else 
  {
    if(dv > 0)
    {
      analogWrite(ptrMotorData->FwdPin, (byte)(dv));
      analogWrite(ptrMotorData->RevPin, 0);
    } else
    {
      analogWrite(ptrMotorData->FwdPin, 0);
      analogWrite(ptrMotorData->RevPin, (byte)(dv));
    }
  } 
} 

void _AcMotr(struct MotorData *ptrMotorData, float err)
{
   //Ac Motor Driver
   /*
      Reduce the Antenna pointing error in deg (err) to the minError (mininum Error)
      by driving the motor at full speed until the max Error is reached. Then start pulsing the motor for
      a set on time (onTime) followed by a set off time (offTime) until the max off time is reached (maxxOffTime).
      Stop driving the motor when the antenna pointing error is less than the min error.
   */ 
   
   //Constants
   const int ON_TIME = 20; // on pulse time (ms)
   const int MIN_ERR = 1; //min error to start driving
   const int MAX_OFF_TIME = 100; //max off time (ms)
   const int MAX_ERR = 20; //max error at full speed.

   //vars
   unsigned long offTime;
   ptrMotorData->LastPass = 0; //reset filter.

   //Low pass Filter (reduce abrupt changes in speed)
   err = Lpf(err, ptrMotorData->Alpha, ptrMotorData->LastPass);
   float absErr = abs(err); //Get the abs magnitude of the error.

   //check if the error is above the min error.
   if(absErr >= MIN_ERR)
   {
    //If it is then generate the PWM signals.
    if (absErr > MAX_ERR)
    {
      offTime = 0;
    } else 
    {
      offTime = float(MAX_OFF_TIME) * (float(MAX_ERR) - absErr) / float(MAX_ERR);
    }

    unsigned long thisTime = millis(); //Current Time.
    if(thisTime > (ptrMotorData->LastTime + offTime))
    {
      //The drive pulse has time has completed.
      digitalWrite(ptrMotorData->FwdPin, LOW);
      digitalWrite(ptrMotorData->RevPin, LOW);

    }

    if(thisTime > (ptrMotorData->LastTime + ON_TIME + offTime))
    {
      bool dir = (err <= 0);
      //The PWM cycle has completed. Start another drive pulse.
      if (err <= 0)
      {
        digitalWrite(ptrMotorData->RevPin, HIGH);
      } else
      {
        digitalWrite(ptrMotorData->FwdPin, HIGH);
      }
      ptrMotorData->LastTime = thisTime;
    }
   } else 
   {
     //the min errorhas been reached so stop the drive.
     digitalWrite(ptrMotorData->FwdPin, LOW);
     digitalWrite(ptrMotorData->RevPin, LOW);
   }
}


void Halt(struct MotorData *ptrMotorData)
{
    Drive(ptrMotorData, 0.0);
}

void Drive(struct MotorData *ptrMotorData, float err)
{
    switch(ptrMotorData->Type)
    {
      case PWMDIR:
        _PwmDir(ptrMotorData, err);
      break;
      case FWDREV:
        _FwdRev(ptrMotorData, err);
      break;
      case ACMOTR:
        _AcMotr(ptrMotorData, err);
      break;
      case INFRARED:
        _Infrared(ptrMotorData, err);
      break;
    }
}