#include "PosSensor.h"


double right_triangle_distance(int a, int b)
{
  return sqrt(pow(a, 2) + pow(b, 2));
}


void setup_sensor()
{
  delay(300);
}

/*
* calibrate_device(): calibrates the LSM303 Sensor for use.
* Both Magnetometer and Accelrometer
*/
void calibrate_device() 
{
  
}

float get_azimuth()
{
  int pot_deg = map(analogRead(AZ_POS_READ),0,1023,0,360);
  return pot_deg;
}

float get_inclination()
{
  int pot_deg = map(analogRead(EL_POS_READ),0,1023,0,360);
  return pot_deg;
}

// void get_inclination_xy(int &accX, int &accY, int &accZ) {
//   unsigned int data[6];
//   // Start I2C transmission
//   Wire.beginTransmission(ADDR_ACC1);
//   // Select control register 1
//   Wire.write(0x20);
//   // Enable X, Y, Z-Axis
//   Wire.write(0x27);
//   // Stop I2C transmission
//   Wire.endTransmission();

//   // Start I2C transmission
//   Wire.beginTransmission(ADDR_ACC1);
//   // Select control register 4
//   Wire.write(0x23);
//   // Full scale 2000 dps, continuous update
//   Wire.write(0x00);
//   // Stop I2C transmission
//   Wire.endTransmission();

//   for (int i = 0; i < 6; i++) {
//     // Start I2C Transmission
//     Wire.beginTransmission(ADDR_ACC1);
//     // Select data register
//     Wire.write((40 + i));
//     // Stop I2C Transmission
//     Wire.endTransmission();

//     // Request 6 byte of data
//     // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
//     Wire.requestFrom(ADDR_ACC1, 1);

//     if (Wire.available() == 1) {
//       data[i] = Wire.read();
//     }
//   }

//   // Convert the data
//   int xAccl = (data[1] * 256) + data[0];
//   int yAccl = (data[3] * 256) + data[2];
//   int zAccl = (data[5] * 256) + data[4];

//   //pass by values
//   accX = xAccl;
//   accY = yAccl;
//   accZ = zAccl;
// }

/*
void get_azimuth_xy(int &magX, int &magY, int &magZ)
{
   unsigned int data[6];

   // Start I2C Transmission
  Wire.beginTransmission(ADDR_MAG);
  // Select Mode select register
  Wire.write(0x02);
  // Continuous conversion mode
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

   // Start I2C Transmission
  Wire.beginTransmission(ADDR_MAG);
  // Select CRA register
  Wire.write(0x00);
  // Temperatuer disabled, Data output rate = 15Hz
  Wire.write(0x10);
  // Stop I2C Transmission
  Wire.endTransmission();

   // Start I2C Transmission
  Wire.beginTransmission(ADDR_MAG);
  // Select gain configuration register
  Wire.write(0x01);
  // Gain +/-1.3
  Wire.write(0x20);
  // Stop I2C Transmission
  Wire.endTransmission();

  for (int i = 0; i < 6; i++)
  {
    // Start I2C Transmission
    Wire.beginTransmission(ADDR_MAG);
    // Select data register
    Wire.write((3 + i));
    // Stop I2C Transmission
    Wire.endTransmission();

    // Request 6 byte of data
    // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
    Wire.requestFrom(ADDR_MAG, 1);

    if (Wire.available() == 1)
    {
      data[i] = Wire.read();
    }
  }

    // Convert the data
    int xMag =  (data[0] * 256) + data[1];
    int yMag =  (data[4] * 256) + data[5];
    int zMag =  (data[2] * 256) + data[3];

   //pass by values.
   magX = xMag;
   magY = yMag;
   magZ = zMag;

}
*/

/*
void notify_pos(double &curAz, double &curEl)
{
  unsigned int data[6];
  
  int xAccl, yAccl, zAccl;
  int xMag, yMag, zMag;
  
  get_inclination_xy(xAccl, yAccl, zAccl);
  double theta = xAccl / right_triangle_distance(yAccl, zAccl);
  curEl = atan(theta) * 180 / M_PI; //antenna rotator tilt

  get_azimuth_xy(xMag, yMag, zMag);
  curAz = atan2(yMag, xMag) * 180 / M_PI; //antenna rotator heading
}
*/