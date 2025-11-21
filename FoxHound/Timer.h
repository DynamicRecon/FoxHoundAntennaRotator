#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
#include <Math.h>

struct Timer {
   long Period;
   long Start;
   long Last;
};

void TimerReset(struct Timer *ptrTimer, long period);
bool Timeout(struct Timer *ptrTimer);
long Elapsed(struct Timer *ptrTimer);
long Periods(struct Timer *ptrTimer);
bool Toggle(struct Timer *ptrTimer);
bool Tick(struct Timer *ptrTimer);
void Execute(struct Timer *ptrTimer, void (*f)());


#endif