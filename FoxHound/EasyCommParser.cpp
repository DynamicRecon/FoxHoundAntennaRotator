#include "Arduino.h"
#include "EasyCommParser.h"
#include "config.h"

/*
 Getter properties for Parser,
 Basically sets current stored or detected AZ/EL
 or gets new heading.
*/
void EasyCommParser::SetAz(double value) 
{
  _currentAz = value;
}

void EasyCommParser::SetEl(double value) 
{
  _currentEl = value;
}

bool EasyCommParser::GetStop() 
{
  return _orderStop;
}

bool EasyCommParser::GetReset() 
{
  return _orderReset;
}


void EasyCommParser::Initialize() 
{
  
}

boolean _IsNumber(char *input)
{
  for (int i = 0; input[i] != '\0'; i++)
  {
    if (isalpha(input[i]))
      return false;
  }
   return true;
}

/*
Parse() while serial port has bytes to read parse through those bytes to get new 
heading and properally write back to HamLib.
EasyComm II (202) expression parser
Source: https://gitlab.com/librespacefoundation/satnogs/satnogs-rotator-firmware/blob/master/libraries/easycomm.h
*/
int EasyCommParser::Parse(double &gotoAz, double &gotoEl)
{
    char buffer[BufferSize];
    char *rawData;
    char *data = buffer;
    char incomingByte;
    int bufferCnt = 0;
    char Data[DataSize];
    char AzString[10];
    char ElString[10];
    
    while(Serial.available() > 0) 
	  {
		 incomingByte = Serial.read();
    if (incomingByte == '\n' || incomingByte == '\r') {
		  buffer[bufferCnt] = 0;
		  if(buffer[0] == 'A' && buffer[1] == 'Z') 
		  {
			if(buffer[2] == ' ' && buffer[3] == 'E' && buffer[4] == 'L') 
			{
				 /*Get position*/
         dtostrf(_currentAz,2,2,AzString);
         dtostrf(_currentEl,2,2,ElString);
         Serial.print("AZ" + String(AzString) + " EL" + String(ElString) + "\n");
			} 
			else 
      {
				rawData = strtok_r(data, " ", &data);
				strncpy(Data, rawData+2, 10);
				if(_IsNumber(Data))
				{
					_newAz = atof(Data);
					gotoAz = _newAz;
				}
				
				rawData = strtok_r(data, " ", &data);
				if(rawData[0] == 'E' && rawData[1] == 'L')
				{
					strncpy(Data, rawData+2, 10);
					if(_IsNumber(Data))
					{
						_newEl = atof(Data);
						gotoEl = _newEl;
					}
			  }
			}
		  }
		  /*Stop moving the antenna*/
		  else if (buffer[0] == 'S' && buffer[1] == 'A' && buffer[2] == ' ' && buffer[3] == 'S' && buffer[4] == 'E') 
		  {
			  Serial.print("AZ");
			  Serial.print(" ");
			  Serial.print("EL");
			  _orderStop = true;
		  
		  }
		  /*Reset the Antenna to zero position*/
		  else if(buffer[0] == 'R' && buffer[1] == 'E' && buffer[2] == 'S' && buffer[3] == 'E' && buffer[4] == 'T') 
		  {
		    Serial.print("AZ");
			  Serial.print(" ");
			  Serial.print("EL");
			  _currentAz = gotoAz = 0;
			  _currentEl = gotoEl = 0;
			  _orderReset = true;
		  }
		  bufferCnt = 0;
		/*else up count*/
		} 
		else 
		{
			buffer[bufferCnt] = incomingByte;
			bufferCnt++;
		}
	}
	return bufferCnt;
}
