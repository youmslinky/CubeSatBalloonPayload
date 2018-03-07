/*
 * ms5607.h
 *
 * Created: 1/7/2018 2:35:46 PM
 *  Author: Penguin
 */ 
#ifndef MS5611_H
#define MS5611_H
#include "project_skywave.h"
#include "drivers/spi_comms.h"

typedef struct calib_data
{
	uint16_t pressure_sens;
	uint16_t pressure_offset;
	uint16_t temp_coeff_of_pressure_sens;
	uint16_t temp_coeff_of_pressure_off;
	uint16_t ref_temp;
	uint16_t temp_coeff_of_temp;
	}calib_data;

typedef struct MS5607_DATA
{
	float temp;
	float pressure;
	float altitude;
}MS5607_DATA;
	
void ms5607_init(void);
void update_ms5607_data(void);

_Bool bInitialGroundPressureSet;
uint32_t get_digi_pressure_value(void);
uint32_t get_digi_temp_value(void);

uint16_t PROM_read(uint8_t command);

MS5607_DATA get_ms6507_data(void);








#endif