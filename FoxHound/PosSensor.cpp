#include "PosSensor.h"

/* PRIVATE STRUCTS AND GLOBALS */
struct Cal 
{
    int Offset;
    int Scale;
};

struct Cal CalMX;
struct Cal CalMY;
struct Cal CalMZ;
struct Cal CalGX;
struct Cal CalGY;
struct Cal CalGZ;

struct Filter FilMx;
struct Filter FilMy;
struct Filter FilMz;
struct Filter FilGx;
struct Filter FilGy;
struct Filter FilGz;

int _min = 32767;
int _max = -32768;


void ResetCal(struct Cal cal)
{
  cal = { 0, 0 };
}

void ComputeCal(struct Cal cal)
{
   //Compute the offset and scaling factors
  cal.Offset = int((long(_max) + long(_min)) / 2L);
  cal.Scale = int((long(_max) - long(_min)) / 2L);
}

bool SampleCal(struct Cal cal, int a, bool changed)
{
  //Process a new calibration sample
  if (a > _max) 
  {
    _max = a;
    ComputeCal(cal);
    changed = true;
  }
  if (a < _min) 
  {
    _max = a;
    ComputeCal(cal);
    changed = true;
  }
  return changed;
}

void _WriteReg(byte address, byte reg, byte value)
{
  //I2C write to register at address
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

byte _ReadReg(byte address, byte reg)
{
  //I2C read from register at address
  byte value;
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(address, (byte)1);
  value = Wire.read();
  Wire.endTransmission();
  return value;
}

void _ReadG(struct Lsm *lsm)
{
   switch(lsm->Type) 
   {
     case LSM303D:
       //Read the 3D accelerometer to determine the gravitational field vector
      Wire.beginTransmission((byte)LSM303D_ADDRESS);
      Wire.write(LSM303D_OUT_X_L_A | 0x80);
      Wire.endTransmission();
      Wire.requestFrom((byte)LSM303D_ADDRESS, (byte)6);
      if(Wire.available() == 6)
      {
          //Read 8-bit values
          byte  xl = Wire.read();
          byte  xh = Wire.read();
          byte  yl = Wire.read();
          byte  yh = Wire.read();
          byte  zl = Wire.read();
          byte  zh = Wire.read();
          //Assemble 16-bit values and perform the axis transformation
          lsm->Gx = ((yh << 8) | yl);
          lsm->Gy = -((xh << 8) | xl);
          lsm->Gz = -((zh << 8) | zl);

          //Low pass filter the sensor data as it improves the calibration procedure
          lsm->Gx = Lpf(&FilGx, lsm->Gx);
          lsm->Gy = Lpf(&FilGy, lsm->Gy);
          lsm->Gz = Lpf(&FilGz, lsm->Gz);
      }
     break;
     case LSM303DLHC:
       //Read the 3D accelerometer to determine the gravitational field vector
      Wire.beginTransmission((byte)LSM303DLHC_ADDRESS_A);
      Wire.write(LSM303DLHC_OUT_X_L_A | 0x80);
      Wire.endTransmission();
      Wire.requestFrom((byte)LSM303DLHC_ADDRESS_A, (byte)6);
      if (Wire.available() == 6) 
      {
        //Read 8-bit values
        byte  xl = Wire.read();
        byte  xh = Wire.read();
        byte  yl = Wire.read();
        byte  yh = Wire.read();
        byte  zl = Wire.read();
        byte  zh = Wire.read();
        //Assemble 16-bit values and perform the axis transformation
        lsm->Gx = ((yh << 8) | yl);
        lsm->Gy = -((xh << 8) | xl);
        lsm->Gz = -((zh << 8) | zl);

        //Low pass filter the sensor data as it improves the calibration procedure
        lsm->Gx = Lpf(&FilGx, lsm->Gx);
        lsm->Gy = Lpf(&FilGy, lsm->Gy);
        lsm->Gz = Lpf(&FilGz, lsm->Gz);
      }
     break;
   }
}

void _ReadM(struct Lsm *lsm)
{
   switch(lsm->Type)
   {
     case LSM303D:
       //Read the 3D magnetometer to determine the magnetic field vector
      Wire.beginTransmission((byte)LSM303D_ADDRESS);
      Wire.write(LSM303D_OUT_X_L_M | 0x80);
      Wire.endTransmission();
      Wire.requestFrom((byte)LSM303D_ADDRESS, (byte)6);
      if (Wire.available() == 6) 
      {
         //Read 8-bit values
        byte xl = Wire.read();
        byte xh = Wire.read();
        byte yl = Wire.read();
        byte yh = Wire.read();
        byte zl = Wire.read();
        byte zh = Wire.read();
        //Assemble 16-bit values and perform the axis transformation
        lsm->Mx = -((yh << 8) | yl);
        lsm->My = ((xh << 8) | xl);
        lsm->Mz = ((zh << 8) | zl);

        //Low pass filter the sensor data as it improves the calibration procedure
        lsm->Mx = Lpf(&FilMx, lsm->Mx);
        lsm->My = Lpf(&FilMy, lsm->My);
        lsm->Mz = Lpf(&FilMz, lsm->Mz);

      }
     break;
     case LSM303DLHC:
        //Read the 3D magnetometer to determine the magnetic field vector
        Wire.beginTransmission((byte)LSM303DLHC_ADDRESS_M);
        Wire.write(LSM303DLHC_OUT_X_H_M | 0x80);
        Wire.endTransmission();
        Wire.requestFrom((byte)LSM303DLHC_ADDRESS_M, (byte)6);
        if (Wire.available() == 6) 
        {
          //Read 8-bit values
          byte xh = Wire.read();
          byte xl = Wire.read();
          byte zh = Wire.read();
          byte zl = Wire.read();
          byte yh = Wire.read();
          byte yl = Wire.read();
          //Assemble 16-bit values and perform the axis transformation
          lsm->Mx = -((yh << 8) | yl);
          lsm->My = ((xh << 8) | xl);
          lsm->Mz = ((zh << 8) | zl);

          //Low pass filter the sensor data as it improves the calibration procedure
          lsm->Mx = Lpf(&FilMx, lsm->Mx);
          lsm->My = Lpf(&FilMy, lsm->My);
          lsm->Mz = Lpf(&FilMz, lsm->Mz);
       }
     break;
    

   }
}

void ResetSensor(struct Lsm *lsm)
{
   Wire.begin();
  switch(lsm->Type)
  {
    case LSM303D:
      _WriteReg(LSM303D_ADDRESS, LSM303D_CTRL1, 0b01010111); //Acc output data rate = 50Hz all Acc axes enabled.
      _WriteReg(LSM303D_ADDRESS, LSM303D_CTRL2, 0b00000000); //Acc full scale = +/- 2g
      _WriteReg(LSM303D_ADDRESS, LSM303D_CTRL5, 0b01100100); //Mag output data rate = 6.25HzMag resolution = high;
      _WriteReg(LSM303D_ADDRESS, LSM303D_CTRL6, 0b00100000); //Mag full scale = +/- 4gauss
      _WriteReg(LSM303D_ADDRESS, LSM303D_CTRL7, 0b00000000); //Mag low power mode = Off. Mag sensor mode = Continuous-conversion
    break;

    case LSM303DLHC:
      _WriteReg(LSM303DLHC_ADDRESS_A, LSM303DLHC_CTRL_REG1_A, 0b01000111); //Acc output data rate = 50Hz all Acc axes enabled.
      _WriteReg(LSM303DLHC_ADDRESS_A, LSM303DLHC_CTRL_REG4_A, 0b00001000); //Acc full scale = +/- 2g, High Resolution Enable
      _WriteReg(LSM303DLHC_ADDRESS_M, LSM303DLHC_CRA_REG_M, 0b00011000); //Mag output data rate = 30Hz
      _WriteReg(LSM303DLHC_ADDRESS_M, LSM303DLHC_CRB_REG_M, 0b00101000); //Mag full scale = +/- 1.3g
      _WriteReg(LSM303DLHC_ADDRESS_M, LSM303DLHC_MR_REG_M, 0b00000000); //Mag Continuous Conversion Mode
    break;
  }
}

void CalStart(struct Lsm *lsm)
{
  ResetCal(CalMX);
  ResetCal(CalMY);
  ResetCal(CalMZ);
  ResetCal(CalGX);
  ResetCal(CalGY);
  ResetCal(CalGZ);
}


void Begin(struct Lsm *lsm)
{
   ResetSensor(lsm);
   FilGx.Alpha = lsm->Alpha;
   FilGy.Alpha = lsm->Alpha;
   FilGz.Alpha = lsm->Alpha;

   FilMx.Alpha = lsm->Alpha;
   FilMy.Alpha = lsm->Alpha;
   FilMz.Alpha = lsm->Alpha;

   for(int i = 0; i < 50; i++) ReadGM(lsm);
}

bool Calibrate(struct Lsm *lsm)
{
   bool changed = false;
   changed = SampleCal(CalMX, lsm->Mx, changed);
   changed = SampleCal(CalMY, lsm->My, changed);
   changed = SampleCal(CalMZ, lsm->Mz, changed);
   changed = SampleCal(CalGX, lsm->Gx, changed);
   changed = SampleCal(CalGY, lsm->Gy, changed);
   changed = SampleCal(CalGZ, lsm->Gz, changed);

   if(changed)
   {
     //Calculate the error vectors
    lsm->Cal.Me = Vec(CalMX.Offset, CalMY.Offset, CalMZ.Offset);
    lsm->Cal.Ge = Vec(CalGX.Offset, CalGY.Offset, CalGZ.Offset);
    //Caclulate the scaling vectors
    lsm->Cal.Ms = Vec(CalMX.Scale, CalMY.Scale, CalMZ.Scale);
    lsm->Cal.Gs = Vec(CalGX.Scale, CalGY.Scale, CalGZ.Scale);
   }

}

void ReadGM(struct Lsm *lsm)
{
  ResetSensor(lsm);
  _ReadG(lsm);
  _ReadM(lsm);
}

Vec GetVector(struct Lsm *lsm)
{
  const float RAD2DEG = 57.295779513;   //Degrees per radian
  //Get the antenna azimuth and elevation angles
  //Get the unit vectors for the earth's magnetic and gravitational fields
  //For each component subtract the error and divide by the scaling factor
   ReadGM(lsm);
   Vec M = Vec((lsm->Mx - lsm->Cal.Me.i) / lsm->Cal.Ms.i, (lsm->My - lsm->Cal.Me.j) / lsm->Cal.Ms.j, (lsm->Mz - lsm->Cal.Me.k) / lsm->Cal.Ms.k).Unit();
   Vec G = Vec((lsm->Gx - lsm->Cal.Ge.i) / lsm->Cal.Ms.i, (lsm->Gy - lsm->Cal.Ge.j) / lsm->Cal.Gs.j, (lsm->Gz - lsm->Cal.Ge.k) / lsm->Cal.Gs.k).Unit();

  //Define the antenna axes as the main reference axes
  const Vec X = Vec(1.0, 0.0, 0.0);         //The antenna X vector
  const Vec Y = Vec(0.0, 1.0, 0.0);         //The antenna Y (boresight) vector
  const Vec Z = Vec(0.0, 0.0, 1.0);         //The antenna Z vector 

  //Compute the magnetic ground axes relative to the antenna axes
  Vec E = G.Cross(M);                   //The magnetic East vector
  Vec N = E.Cross(G);                   //The magnetic North vector
  Vec U = G.Neg();                        //The magnetic Up vector

  //Compute the projections of the antenna axes onto the magnetic ground axes
  float Xn = X.Dot(N);                     //The scalar projection of X onto N
  float Xe = X.Dot(E);                     //The scalar projection of X onto E
  float Yu = Y.Dot(U);                     //The scalar projection of Y onto U
  float Zu = Z.Dot(U);                     //The scalar projection of Z onto U

  //Compute the true antenna pointing angles relative to the magnetic ground axes
  lsm->Az = atan2(-Xn, Xe) * RAD2DEG + lsm->Cal.Md;  //The azimuth angle in degrees using the X-axis
  lsm->El = atan2(Yu, Zu) * RAD2DEG;            //The elevation angle in degrees using the Y-axis

  if (lsm->Az > 180) lsm->Az = lsm->Az - 360;           //Ensure azimuth is in -180..180 format after adding D

  return AzElToVec(double(lsm->Az), double(lsm->El), 1);

}