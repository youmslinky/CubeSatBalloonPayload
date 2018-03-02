/*
 * ntcle100.c
 *
 * Created: 1/3/2018 5:50:40 PM
 *  Author: Penguin
 */ 
#include "drivers/ntcle100.h"
#include <math.h>

#define FIXED_RESISTOR 16000
#define RESISTOR_ONE FIXED_RESISTOR
#define NTCLE100_SAMPLE_AMOUNT 10
void ntcle100_init(void)
{
	//enable adca
	ADCA.CTRLA = 0b00000001;
	//enable unsigned 12 bit res
	ADCA.CTRLB = 0b00000000;
	//[5:4] = 01 for Vcc/1.6 as ref voltage
	ADCA.REFCTRL = 0b00010000;
	//set prescalar to 128 (idk why though)
	ADCA.PRESCALER = 0b00000101;
	//ADCA.PRESCALER = 0b00000000;
	ADCA.CAL = adc_get_calibration_data(ADC_CAL_ADCA);
	ADCA.CH0.CTRL = 0b00000001;
	ADCA.CH0.MUXCTRL = 0b00000000;
}

SW_STATUS ntcle100_startup(void)
{
	return SW_GREEN;
}

uint16_t get_adc_reading(void)
{
	//start conversion
	ADCA.CH0.CTRL |= 0b10000000;
	//wait for conversion
	while(ADCA.CH0.INTFLAGS == 0);
	uint16_t reading = ADCA.CH0.RES;
	//printf("Reading: %u\n", reading);
	return reading;
}

float get_voltage(uint16_t adc_reading)
{
	float voltage = (adc_reading * 2.0625) / 4096.0;
	//printf("Voltage: %f\n", voltage);
	return voltage;
}

uint32_t get_resistance(float voltage)
{
	float voltage_drop = 3.27 - voltage;
	//printf("DROP: %f\n", voltage_drop);
	uint32_t resistance = (voltage * RESISTOR_ONE) / voltage_drop;
	//printf("Resistance: %lu\n", resistance);
	return resistance;
}

float calc_temp(uint32_t resistance, _Bool bShouldReturnInCelsius)
{
	double var_a = 0.003354016;
	double var_b =  0.0002569850 * log(resistance/10000.0);
	double var_c =  0.000002620131 * (2 * (log(resistance/10000.0)));
	double var_d =  0.00000006383091 * (3 * (log(resistance/10000.0)));
	float temp_in_kelvin = (float)(1/(var_a + var_b + var_c + var_d));
	return bShouldReturnInCelsius ? (temp_in_kelvin - 273.15) : temp_in_kelvin;
}

float get_temp(void)
{
	float sum = 0;
	for(int x = 0; x < NTCLE100_SAMPLE_AMOUNT; x++)
	{
		sum += calc_temp(get_resistance(get_voltage(get_adc_reading())), true);
	}
	return sum/NTCLE100_SAMPLE_AMOUNT;
}
