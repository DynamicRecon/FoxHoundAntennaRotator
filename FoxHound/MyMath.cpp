#include "MyMath.h"

Vec::Vec() 
{
  //Constructor
  i = 0;
  j = 0;
  k = 0;
}

Vec::Vec(float I, float J, float K) 
{
  //Constructor
  i = I;
  j = J;
  k = K;
}

Vec Vec::Cross(Vec b) 
{
  //Returns the vector cross product of two vectors.
  return Vec(j * b.k - k * b.j, k * b.i - i * b.k, i * b.j - j * b.i);
}

float Vec::Dot(Vec b) 
{
  //Returns the scalar dot product of two vectors.
  return i * b.i + j * b.j + k * b.k;
}

float Vec::Mod() 
{
  //Returns the scalar modulus of a vector.
  return sqrt(i * i + j * j + k * k);
}

Vec Vec::Unit() 
{
  //Returns the unit vector of a vector.
  float modulus = Mod();
  return Vec(i / modulus, j / modulus, k / modulus);
}

Vec Vec::Neg() 
{
  //Returns the vector negative of a vector.
  return Vec( -i, -j, -k);
}

float DegToRads(float value) 
{ 
  return  M_PI * value / 180.0; 
}
float RadsToDegs(float value) 
{ 
  return (180.0 / M_PI) * value; 
}

float DegToRads(double value)
{
  return value * (M_PI / 180);
}

float DiffAngle(float a, float b) 
{
  //Calculate the acute angle between two angles in -180..180 degree format
  float diff = a - b;
  if (diff < -180) diff += 360;
  if (diff > 180) diff -= 360;
  return diff;
}

Vec AzElToVec(double az, double el, int r)
{
   double x = r * cos(DegToRads(el)) * cos(DegToRads(az));
   double y = r * cos(DegToRads(el)) * sin(DegToRads(az));
   double z = r * sin(DegToRads(el));
   return Vec(float(x), float(y), float(z));
}

/*Low Pass Filter for smoothing waveforms*/
float Lpf(struct Filter *fil, float Value)
{
  //Low pass filter - Decrease alpha to increase damping factor
  float result = (fil->Alpha * Value) + fil->Last * (1 - fil->Alpha);
  fil->Last = result;
  return result;
}

double VecDistance(Vec a, Vec b)
{
  double dx = b.i - a.i;
  double dy = b.j - a.j;
  double dz = b.k - a.k;

  double dv = pow(dx, 2) + pow(dy, 2) + pow(dz, 2);
  return sqrt(dv);
}