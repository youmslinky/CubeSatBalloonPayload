/*
 * spi_comms.h
 *
 * Created: 1/7/2018 1:17:15 PM
 *  Author: Penguin
 */ 
#ifndef SPI_COMMS_H
#define SPI_COMMS_H

#include "project_skywave.h"

void set_slave_low(register8_t* slave_regi, int pin);
	
void set_slave_high(register8_t* slave_regi, int pin);

void spi_comms_init(void);
	
void spi_write(uint8_t command);
uint8_t spi_read_u8(void);
uint16_t spi_read_u16(void);
uint32_t spi_read_u32(void);








#endif
