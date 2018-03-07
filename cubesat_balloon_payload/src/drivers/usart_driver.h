/*
 * usart_driver.h
 *
 * Created: 1/3/2018 5:50:02 PM
 *  Author: Penguin
 */ 


#ifndef USART_DRIVER_H
#define USART_DRIVER_H

#include "cubesat_balloon_payload.h"
#include "utility/circular_buff.h"

void usart_comms_init(void);

volatile char temp;

void usart_print(USART_t *usart, char *text);

uint8_t read_gpsdata(void);
int gpsdata_buffer_size(void);
circular_buf_t* get_cbuf(void);
int data_ready(void);
void take_data(void);

uint8_t* return_gps_data(void);

void get_new_data(void);

void set_busy_flag(void);

void clear_busy_flag(void);

_Bool check_busy_flag(void);




#endif