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

void usart_print(USART_t *usart, char *text);

circular_buf_t* get_cbuf(void);

int num_lines_ready(void);

void take_line(void);



#endif