/*
 * bno055.h
 *
 * Created: 2/28/2018 4:44:45 PM
 *  Author: jdk0026
 */ 

#ifndef BNO055_H
#define BNO055_H

#include "drivers/twi_comms_driver.h"
#include <asf.h>

/*Quaternion data registers*/
#define BNO055_QUATERNION_DATA_W_LSB_ADDR	(0X20)
#define BNO055_QUATERNION_DATA_W_MSB_ADDR	(0X21)
#define BNO055_QUATERNION_DATA_X_LSB_ADDR	(0X22)
#define BNO055_QUATERNION_DATA_X_MSB_ADDR	(0X23)
#define BNO055_QUATERNION_DATA_Y_LSB_ADDR	(0X24)
#define BNO055_QUATERNION_DATA_Y_MSB_ADDR	(0X25)
#define BNO055_QUATERNION_DATA_Z_LSB_ADDR	(0X26)
#define BNO055_QUATERNION_DATA_Z_MSB_ADDR	(0X27)

/* Linear acceleration data registers*/
#define BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR			(0X28)
#define BNO055_LINEAR_ACCEL_DATA_X_MSB_ADDR			(0X29)
#define BNO055_LINEAR_ACCEL_DATA_Y_LSB_ADDR			(0X2A)
#define BNO055_LINEAR_ACCEL_DATA_Y_MSB_ADDR			(0X2B)
#define BNO055_LINEAR_ACCEL_DATA_Z_LSB_ADDR			(0X2C)
#define BNO055_LINEAR_ACCEL_DATA_Z_MSB_ADDR			(0X2D)

/*Gravity data registers*/
#define BNO055_GRAVITY_DATA_X_LSB_ADDR			(0X2E)
#define BNO055_GRAVITY_DATA_X_MSB_ADDR			(0X2F)
#define BNO055_GRAVITY_DATA_Y_LSB_ADDR			(0X30)
#define BNO055_GRAVITY_DATA_Y_MSB_ADDR			(0X31)
#define BNO055_GRAVITY_DATA_Z_LSB_ADDR			(0X32)
#define BNO055_GRAVITY_DATA_Z_MSB_ADDR			(0X33)

/* Temperature data register*/
#define BNO055_TEMP_ADDR					(0X34)



/* Unit selection register*/
#define BNO055_UNIT_SEL_ADDR				(0X3B)
#define BNO055_DATA_SELECT_ADDR				(0X3C)

/* Mode registers*/
#define BNO055_OPR_MODE_ADDR				(0X3D)
#define BNO055_PWR_MODE_ADDR				(0X3E)

/* Status registers*/
#define BNO055_CALIB_STAT_ADDR				(0X35)
#define BNO055_SELFTEST_RESULT_ADDR			(0X36)
#define BNO055_INTR_STAT_ADDR				(0X37)
#define BNO055_SYS_CLK_STAT_ADDR			(0X38)
#define BNO055_SYS_STAT_ADDR				(0X39)
#define BNO055_SYS_ERR_ADDR					(0X3A)

#define BNO055_TWI_ADDRESS_1				(0X28)	//default address
#define BNO055_TWI_ADDRESS_2				(0X29)	//can be switched to this address if necessary with one of the pins


typedef struct{
	//quaternion (rotation) from fusion mode
	int16_t quat_w;
	int16_t quat_x;
	int16_t quat_y;
	int16_t quat_z;
	
	//linear acceleration from fusion mode
	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
	
	//gravity vector from fusion mode
	int16_t grav_x;
	int16_t grav_y;
	int16_t grav_z;
	
	int8_t temp;
	
	uint8_t status;
}bno055_raw_data_t;


typedef struct{
	//quaternion (rotation) from fusion mode
	double quat_w;
	double quat_x;
	double quat_y;
	double quat_z;
	
	//linear acceleration from fusion mode
	double accel_x;
	double accel_y;
	double accel_z;
	
	//gravity vector from fusion mode
	double grav_x;
	double grav_y;
	double grav_z;
	
	int8_t temp;

}bno055_data_t;


void bno055_get_data(void);

void bno055_process_data(void);

void bno055_data_handler(uint8_t* buffer);

#endif
