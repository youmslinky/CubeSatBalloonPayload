/*
 * twi_comms_driver.c
 *
 * Created: 1/3/2018 5:51:21 PM
 *  Author: Penguin
 */ 
#include "drivers/twi_comms_driver.h"

#define SPEED 5000

static twi_package_t univ_pkt;
static uint8_t buffer[128];

void twi_comms_init(void)
{
	twi_options_t twi_conf = 
	{
		.speed = SPEED,
		.speed_reg = TWI_BAUD(32000000, SPEED)
	};

	
	twi_master_init(TWI_MASTER, &twi_conf);
	twi_master_enable(TWI_MASTER);
	univ_pkt.no_wait = false;
	univ_pkt.addr_length = 1;
	univ_pkt.length = 1;
	univ_pkt.buffer = buffer;
	printf("TWI INIT SUCCESS\n");
}

void twi_write(uint8_t slave_address, uint8_t regi, uint8_t data)
{
	univ_pkt.chip = slave_address;
	univ_pkt.addr[0] = regi;
	buffer[0] = data;
	univ_pkt.length = 1;
	twi_master_write(TWI_MASTER, &univ_pkt);
}

void twi_read(uint8_t slave_address, uint8_t regi, uint8_t data_length, void(*DataHandler)(uint8_t*))
{
	univ_pkt.chip = slave_address;
	univ_pkt.addr[0] = regi;
	univ_pkt.length = data_length;
	twi_master_read(TWI_MASTER, &univ_pkt);
	DataHandler(buffer);
}

uint8_t* get_i2c_buffer(void)
{
	return buffer;
}
