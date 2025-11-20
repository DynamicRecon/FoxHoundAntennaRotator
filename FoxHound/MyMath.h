#ifndef MYMATH_H
#define MYMATH_H

#include <math.h>
#include <Arduino.h>

//Math Vector Class
class Vec {
  public:
    Vec();
    Vec(float I, float J, float K);
    Vec Cross(Vec b);
    float Dot(Vec b);
    float Mod();
    Vec Unit();
    Vec Neg();
    float i, j, k; //Vector type comprising three orthogonal components.
  private:
};

//math helper funcs
float DegToRads(float);
float RadsToDegs(float);
float DiffAngle(float a, float b);
float lpf(float Value, float alpha);

#endif
