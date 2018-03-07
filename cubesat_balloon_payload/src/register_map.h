/*
 * register_map.h
 *
 * Created: 1/7/2018 7:30:00 PM
 *  Author: Penguin
 */ 
#ifndef REGISTER_MAP_H
#define REGISTER_MAP_H

//--MS5611--
#define MS5611_RESET 0x1E 
#define D1_CMD 0x48 //Digital Pressure Reading
#define D2_CMD 0x58 //Digital Temperature Reading


#define C1_CMD 0xA2 //Pressure Sensitivity
#define C2_CMD 0xA4 //Pressure Offset
#define C3_CMD 0xA6 //Temperature Coefficient of Pressure Sensitivity
#define C4_CMD 0xA8 //Temperature Coefficient of Pressure Offset
#define C5_CMD 0xAA //Reference Temperature
#define C6_CMD 0xAC //Temperature Coefficient of the Temperature

//--MPU9250--
//slave addresses
#define MPU_9250_ADDR 0b1101000 //MPU9250 Gyro + Accel slave address
#define AK8963_ADDR 0x0C		//MPU9250 Mag slave address
//


//--BNO055--
//registers are mapped in bno055.h




#endif