/*
 * ms5607.h
 *
 * Created: 1/7/2018 2:35:46 PM
 *  Author: Penguin
 */ 
#ifndef MS5611_H
#define MS5611_H
#include "cubesat_balloon_payload.h"
#include "drivers/spi_comms.h"

/* registers */
#define MS5611_RESET 0x1E
#define D1_CMD 0x48 //Digital Pressure Reading
#define D2_CMD 0x58 //Digital Temperature Reading

#define C1_CMD 0xA2 //Pressure Sensitivity
#define C2_CMD 0xA4 //Pressure Offset
#define C3_CMD 0xA6 //Temperature Coefficient of Pressure Sensitivity
#define C4_CMD 0xA8 //Temperature Coefficient of Pressure Offset
#define C5_CMD 0xAA //Reference Temperature
#define C6_CMD 0xAC //Temperature Coefficient of the Temperature

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