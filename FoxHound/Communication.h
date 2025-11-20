#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <WString.h>


#include "defs.h"
#include "consts.h"
#include "MyMath.h"

enum Tokens 
{
	UNKNOWN,
	KEYWORD,
	NUMBER,
	OPERATOR,
	EOL
};

struct Token {
	Tokens tok;
	char *value;
};

/*
  EasyCommParser Class:
  Parses the EasyComm II commands from Serial Port
  then sends those commands to the program loop to turn
  the rotator correctly.
*/

class EasyCommParser 
{
   private:
	   double _currentAz = 0.0;
	   double _currentEl = 0.0;
	   double _newAz = 0.0;
	   double _newEl = 0.0;
	   bool _orderStop = false;
	   bool _orderReset = false;
	public:
	  void  SetAz(double);
	  void  SetEl(double);
	  bool GetStop();
	  bool GetReset();
		void Initialize();
	  int Parse(double &gotoAz, double &gotoEl);
};

#endif
