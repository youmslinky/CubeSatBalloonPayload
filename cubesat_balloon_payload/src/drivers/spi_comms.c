/*
 * spi_comms.c
 *
 * Created: 1/7/2018 1:17:25 PM
 *  Author: Penguin
 */ 
#include "drivers/spi_comms.h"


static uint8_t spi_simple_read(void);


void set_slave_low(register8_t* slave_regi, int pin)
{
	*slave_regi &= ~(pin);
}

void set_slave_high(register8_t* slave_regi, int pin)
{
	*slave_regi |= 1 << pin;
}

void spi_comms_init(void)
{
	
	PORTC.DIRSET = 0b10110000;
	PORTC.DIRCLR = 0b01000000;
	PORTC.OUTSET = 0b10110000;
	//enables spi and sets prescalar to 128
	SPIC.CTRL = 0b01010001;
}

uint8_t spi_simple_read(void)
{
	spi_write(0xFF);
	return SPIC.DATA;
}

uint8_t spi_read_u8()
{
	uint8_t data = spi_simple_read();
	return data;
}

uint16_t spi_read_u16()
{
	uint16_t data = ((uint16_t)spi_simple_read())<<8;
	data += ((uint16_t)spi_simple_read());
	return data;
}

uint32_t spi_read_u32()
{
	uint32_t data;
	data=((uint32_t)spi_simple_read())<<16;
	data+=((uint32_t)spi_simple_read())<<8;
	data+=((uint32_t)spi_simple_read());
	return data;
}

void spi_write(uint8_t command)
{
	SPIC.DATA = command;
	while(!(SPIC.STATUS>>7));
}
