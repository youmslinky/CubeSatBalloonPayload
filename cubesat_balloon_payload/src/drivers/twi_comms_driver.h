/*
 * twi_comms_driver.h
 *
 * Created: 1/3/2018 5:51:08 PM
 *  Author: Penguin
 */ 
#ifndef TWI_COMMS_DRIVER_H
#define TWI_COMMS_DRIVER_H
#include "project_skywave.h"




void twi_comms_init(void);


void twi_write(uint8_t slave_address, uint8_t regi, uint8_t data);
//Here we pass whatever function we choose to handle the return data
void twi_read(uint8_t slave_address, uint8_t regi, uint8_t data_length,void(*DataHandler)(uint8_t*));

uint8_t* get_i2c_buffer(void);


#endif