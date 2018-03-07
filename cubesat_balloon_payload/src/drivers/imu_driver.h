/*
 * imu_driver.h
 *
 * Created: 1/5/2018 7:38:35 PM
 *  Author: Penguin
 */ 
#ifndef IMU_DRIVER_H
#define IMU_DRIVER_H


#include "cubesat_balloon_payload.h"
#include "twi_comms_driver.h"

typedef struct{
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
	
	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
	
	int16_t mag_x;
	int16_t mag_y;
	int16_t mag_z;
	
	int16_t temp;
	
	uint8_t status;
}mpu9250_main_data;
void imu_init(void);

_Bool mpu_9250_who_am_i(void);

uint8_t ak8963_device_check(void);

void MPU9250_MainDataHandler(uint8_t* buffer);

void clearMainData(void);

void MPU9250_GenericDataHandler(uint8_t* buffer);




#endif