/*
 * ntcle100.h
 *
 * Created: 1/3/2018 5:50:30 PM
 *  Author: Penguin
 */ 

#ifndef NTCLE100_H
#define NTCLE100_H
#include "project_skywave.h"

void ntcle100_init(void);

SW_STATUS ntcle100_startup(void);

uint16_t get_adc_reading(void);

float get_voltage(uint16_t adc_reading);

uint32_t get_resistance(float voltage);

float calc_temp(uint32_t resistance, _Bool bShouldReturnInCelsius);

float get_temp(void);



#endif