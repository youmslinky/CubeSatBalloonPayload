/*
 * imu.c
 *
 * Created: 1/5/2018 7:37:59 PM
 *  Author: Penguin
 */ 
#include "drivers/imu_driver.h"

static uint8_t genericData;

void imu_init(void)
{
	//reset and WAIT
	twi_write(0x28, 0x6B, 0b10000000);
	delay_ms(100);
	//something to do with clock source?
	twi_write(0x28, 0x6B, 0x01);
	//enable accel and gyro
	twi_write(0x28, 0x6C, 0x00);	
	//int initialization
	twi_write(0x28, 0x37, 0x10);
	twi_write(0x28, 0x38, 0x01);
	PORTF.PIN2CTRL = PORT_OPC_PULLDOWN_gc|PORT_ISC_RISING_gc;
	PORTF.INT0MASK = ~(1<<2);
	PORTF.INTCTRL = PORT_INT0LVL_HI_gc;
}

// ISR(PORTE_INT0_vect)
// {
// 	
// }

_Bool mpu_9250_who_am_i(void)
{
	twi_read(MPU_9250_ADDR, 0x75, 1, MPU9250_GenericDataHandler);
	if(genericData == 0x71)
	{
		printf("DEVICE FOUND\n");
		return true;
	}
	printf("%#x\n", genericData);
	return false;
}

uint8_t ak8963_device_check(void)
{
	return 1;
}

void MPU9250_MainDataHandler(uint8_t* buffer)
{
	
}

void clearMainData(void)
{
	
}

void MPU9250_GenericDataHandler(uint8_t* buffer)
{
	genericData = buffer[0];
}

