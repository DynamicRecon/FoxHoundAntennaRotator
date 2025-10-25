
#include <math.h>
#include <Arduino.h>
#include "config.h"

float DegToRads(float value) { return  M_PI * value / 180.0; }
float RadsToDegs(float value) { return (180.0 / M_PI) * value; }
