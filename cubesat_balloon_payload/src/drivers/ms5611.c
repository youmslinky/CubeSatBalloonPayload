/*
 * ms5607.c
 *
 * Created: 1/7/2018 2:36:02 PM
 *  Author: Penguin
 */ 

#include "drivers/ms5611.h"
#include "drivers/ntcle100.h"
#include <math.h>
#define MS5607_SLAVE_REGI (&(PORTC.OUT))
#define MS5607_SLAVE_PIN 4

static calib_data calibration_data;
static MS5607_DATA ms5607_data;

//macros to help keep clutter down
//MS5611 Calibration shortcuts
#define C1 calibration_data.pressure_sens
#define C2 calibration_data.pressure_offset
#define C3 calibration_data.temp_coeff_of_pressure_sens
#define C4 calibration_data.temp_coeff_of_pressure_off
#define C5 calibration_data.ref_temp
#define C6 calibration_data.temp_coeff_of_temp


static void set_self_low(void);
static void set_self_high(void);

static int32_t InitialGroundPressure;

uint16_t c1, c2, c3, c4, c5, c6;


void set_self_high(void)
{
	//set_slave_high(MS5607_SLAVE_PIN, MS5607_SLAVE_PIN);
	PORTC.OUTSET = 0b00010000;
}

void set_self_low(void)
{
	//set_slave_low(MS5607_SLAVE_REGI, MS5607_SLAVE_PIN);
	PORTC.OUTCLR = 0b00010000;
}



void ms5607_init()
{
	bInitialGroundPressureSet = false;
	//Reset ms5607
	set_self_low();
	spi_write(MS5611_RESET);
	set_self_high();
	delay_ms(3);
	C1 = PROM_read(0xA2);
	C2 = PROM_read(0xA4);
	C3 = PROM_read(0xA6);
	C4 = PROM_read(0xA8);
	C5 = PROM_read(0xAA);
	C6 = PROM_read(0xAC);	
}

uint32_t get_digi_pressure_value()
{
	set_self_low();
	spi_write(D1_CMD);
	set_self_high();
	delay_ms(10);
	set_self_low();
	spi_write(0x00);
	uint32_t data = spi_read_u32();
	set_self_high();
	return data;
}

uint32_t get_digi_temp_value()
{
	set_self_low();
	spi_write(D2_CMD);
	set_self_high();
	delay_ms(10);
	set_self_low();
	spi_write(0x00);
	uint32_t data = spi_read_u32();
	set_self_high();
	return data;
}

uint16_t PROM_read(uint8_t command)
{
	set_self_low();
	spi_write(command);
	uint16_t data = spi_read_u16();
	set_self_high();
	delay_ms(1);
	return data;
}

MS5607_DATA get_ms6507_data(void)
{
	return ms5607_data;
}

void update_ms5607_data()
{
	//digital temp value
	uint32_t d2 = get_digi_temp_value();
	//digital pressure value
	uint32_t d1 = get_digi_pressure_value();

	//
	int32_t dT = ((int32_t)d2 - ((int32_t)C5<<8));
	int32_t temp = 2000 + (int32_t)(((int64_t)dT * C6)>>23);
	int64_t offset = ((int64_t)C2<<16) + (((int64_t)C4 * (int64_t)dT)>>7);
	int64_t sens = ((int64_t)C1<<15) + (((int64_t)C3 * (int64_t)dT)>>8);

	if(temp < 2000)
	{

	}
	int32_t pressure = (int32_t)((d1 * ((int64_t)sens>>21) - offset)>>15);
	if(!bInitialGroundPressureSet)
	{
		InitialGroundPressure = pressure;
		bInitialGroundPressureSet = true;
	}
	float tempAlt = ((287.058 * get_temp())/9.8) * (log((float)InitialGroundPressure/(float)pressure));
	ms5607_data.altitude = tempAlt;
	ms5607_data.temp = (float)temp/100.0;
	ms5607_data.pressure = (float)pressure/100.0;
}