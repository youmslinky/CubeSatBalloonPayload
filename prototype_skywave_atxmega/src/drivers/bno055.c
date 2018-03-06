/*
 * bno055.c
 *
 * Created: 2/28/2018 4:44:26 PM
 *  Author: jdk0026
 */ 



//#include <math.h>
#include "drivers/bno055.h"

static bno055_raw_data_t bno055_raw_data;
bno055_data_t bno055_data;
static int single_byte_data;


int bno055_is_alive(void)
{
	//read chip id register 0x00, it should be 0xA0 for bno055
	twi_read(BNO055_TWI_ADDRESS_1,0x00,1,single_byte_handler);
	
	if(single_byte_data == 0xA0)
	{
		printf("bn055 is alive\n");
		return 1;
	}
	return 0;
}


void bno055_setmode_NDOF(void)
{
	//set operating mode to ndof (nine degrees of freedom)
	twi_write(0x28,BNO055_OPR_MODE_ADDR,0b00001100); 
}

void bno055_get_data(void)
{
	twi_read(0x28,BNO055_QUATERNION_DATA_W_LSB_ADDR,21,bno055_data_handler);
}

void bno055_process_data(void){
	bno055_data.quat_w = (double)(bno055_raw_data.quat_w/QUAT_CONVERSION_FACTOR);
	bno055_data.quat_x = (double)(bno055_raw_data.quat_w/QUAT_CONVERSION_FACTOR);
	bno055_data.quat_y = (double)(bno055_raw_data.quat_w/QUAT_CONVERSION_FACTOR);
	bno055_data.quat_z = (double)(bno055_raw_data.quat_w/QUAT_CONVERSION_FACTOR);
	
	bno055_data.accel_x = (double)(bno055_raw_data.accel_x/LINEAR_ACCEL_CONVERSION_FACTOR);
	bno055_data.accel_y = (double)(bno055_raw_data.accel_y/LINEAR_ACCEL_CONVERSION_FACTOR);
	bno055_data.accel_z = (double)(bno055_raw_data.accel_z/LINEAR_ACCEL_CONVERSION_FACTOR);
	
	bno055_data.grav_x = (double)(bno055_raw_data.grav_x/GRAVITY_ACCEL_CONVERSION_FACTOR);
	bno055_data.grav_y = (double)(bno055_raw_data.grav_y/GRAVITY_ACCEL_CONVERSION_FACTOR);
	bno055_data.grav_z = (double)(bno055_raw_data.grav_z/GRAVITY_ACCEL_CONVERSION_FACTOR);
	
	
	//printf("temp: %d\n",bno055_raw_data.temp);
	printf("quat : w:%lf x:%lf y:%lf z:%lf\n",bno055_data.quat_w,bno055_data.quat_x,bno055_data.quat_y,bno055_data.quat_z);
	printf("accel: x:%lf y:%lf z:%lf\n",bno055_data.accel_x,bno055_data.accel_y,bno055_data.accel_z);
	printf("gravity: x:%lf y:%lf z:%lf\n",bno055_data.grav_x,bno055_data.grav_y,bno055_data.grav_z);
	//printf("gravity mag: %lf\n",sqrt(pow(bno055_data.grav_x,2.0)+pow(bno055_data.grav_y,2.0)+pow(bno055_data.grav_z,2.0)));
	
}

void bno055_data_handler(uint8_t* buffer)
{
	//printf("%d\n",buffer[0]);
	bno055_raw_data.quat_w = buffer[0]   | (buffer[1]<<8);
	bno055_raw_data.quat_x = buffer[2]   | (buffer[3]<<8);
	bno055_raw_data.quat_y = buffer[4]   | (buffer[5]<<8);
	bno055_raw_data.quat_z = buffer[6]   | (buffer[7]<<8);
	
	bno055_raw_data.accel_x = buffer[8]  | (buffer[9]<<8);
	bno055_raw_data.accel_y = buffer[10] | (buffer[11]<<8);
	bno055_raw_data.accel_z = buffer[12] | (buffer[13]<<8);
	
	bno055_raw_data.grav_x = buffer[14]  | (buffer[15]<<8);
	bno055_raw_data.grav_y = buffer[16]  | (buffer[17]<<8);
	bno055_raw_data.grav_z = buffer[18]  | (buffer[19]<<8);
	
	bno055_raw_data.temp = buffer[20];
	
	
}

void single_byte_handler(uint8_t *buffer)
{
	single_byte_data = buffer[0];

}