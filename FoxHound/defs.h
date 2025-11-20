#ifndef DEFS_H
#define DEFS_H

#define WINDUP_LIMIT 450            //Sets the total number of degrees azimuth rotation in any direction before resetting to zero

#define BAUD_RATE 19200
#define STEP_DELAY 5000 //ms

//Motor pins - Don't change (unless you rewire the circuit)
#define AZFWDPIN  5
#define AZREVPIN  6
#define AZBRKPIN  7
#define ELBRKPIN  8
#define ELFWDPIN  9
#define ELREVPIN 10
//Speaker pins
#define SPKPIN  11    //Attach a piezo buzzer to this pin. It beeps when new calibration data arrives.
#define GNDPIN 12    //Makes a convenient ground pin adjacent to the speaker pin

#define BufferSize 256
#define DataSize 100

//Sensor type definitions
#define LSM303D 0     //For LSM303D sensor
#define LSM303DLHC 1  //For LSM303DLHC sensor

//LSM303D Registers
#define LSM303D_ADDRESS 0b0011101
#define LSM303D_OUT_X_L_A 0x28
#define LSM303D_OUT_X_L_M 0x08
#define LSM303D_CTRL1 0x20
#define LSM303D_CTRL2 0x21
#define LSM303D_CTRL3 0x22
#define LSM303D_CTRL4 0x23
#define LSM303D_CTRL5 0x24
#define LSM303D_CTRL6 0x25
#define LSM303D_CTRL7 0x26
//LSM303DLHC Registers
#define LSM303DLHC_ADDRESS_A 0b0011001
#define LSM303DLHC_ADDRESS_M 0b0011110
#define LSM303DLHC_OUT_X_L_A 0x28
#define LSM303DLHC_OUT_X_H_M 0x03
#define LSM303DLHC_CTRL_REG1_A 0x20
#define LSM303DLHC_CTRL_REG4_A 0x23
#define LSM303DLHC_CRA_REG_M 0x00
#define LSM303DLHC_CRB_REG_M 0x01
#define LSM303DLHC_MR_REG_M 0x02

//eeprom addresses
#define CAL 0x0

#endif