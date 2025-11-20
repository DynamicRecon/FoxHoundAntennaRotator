#include "Timer.h"

void Reset(struct Timer *ptrTimer, long period)
{
  ptrTimer->Start = millis();
  ptrTimer->Last = 0;
  ptrTimer->Period = period;

}

bool Timeout(struct Timer *ptrTimer)
{
  return (Elapsed(ptrTimer) >= ptrTimer->Period);
}

long Elapsed(struct Timer *ptrTimer)
{
   return millis() - ptrTimer->Start;
}

long Periods(struct Timer *ptrTimer)
{
  return long(Elapsed(ptrTimer) / ptrTimer->Period);
} 

bool Toggle(struct Timer *ptrTimer)
{
    return (Periods(ptrTimer) % 2);
}

bool Tick(struct Timer *ptrTimer)
{
    long p = Periods(ptrTimer);
    if (p > ptrTimer->Last) 
    {
       ptrTimer->Last = p;
       return true;
    } 
    return false;
}


void Execute(struct Timer *ptrTimer, void (*f)())
{
    if(Tick(ptrTimer)) 
    {
      (*f)();
    }
}