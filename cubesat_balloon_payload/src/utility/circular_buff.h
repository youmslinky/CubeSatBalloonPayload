
/*
 * ringbuff.h
 *
 * Created: 3/5/2018 7:13:37 PM
 *  Author: jdk0026
 */ 

#ifndef CIRCULAR_BUFF_H
#define CIRCULAR_BUFF_H
#include "cubesat_balloon_payload.h"


typedef struct {
	uint8_t * buffer;
	size_t head;
	size_t tail;
	size_t size; //of the buffer
} circular_buf_t;

int circular_buf_reset(circular_buf_t * cbuf);
int circular_buf_put(circular_buf_t * cbuf, uint8_t data);
int circular_buf_get(circular_buf_t * cbuf, uint8_t * data);
_Bool circular_buf_empty(circular_buf_t cbuf);
_Bool circular_buf_full(circular_buf_t cbuf);
int buffer_size(circular_buf_t * cbuf);

#endif