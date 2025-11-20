#include "PosSensor.h"

void ResetCal(struct Cal *ptrCal)
{
  struct Cal newCal = { 0, 0, 32767, -32768 };
  ptrCal = &newCal;
}

void ComputeCal(struct Cal *ptrCal)
{

  int min = ptrCal->Min;
  int max = ptrCal->Max;
   //Compute the offset and scaling factors
  ptrCal->Offset = int((long(max) + long(min)) / 2L);
  ptrCal->Scale = int((long(max) - long(min)) / 2L);
}

void SampleCal(struct Cal *ptrCal, int a, bool changed)
{
  //Process a new calibration sample
  if (a > ptrCal->Max) 
  {
    ptrCal->Max = a;
    ComputeCal(ptrCal);
    changed = true;
  }
  if (a < ptrCal->Min) 
  {
    ptrCal->Min = a;
    ComputeCal(ptrCal);
    changed = true;
  }
  return changed;
}