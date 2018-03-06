/*
 * usart_driver.c
 *
 * Created: 1/3/2018 5:50:20 PM
 *  Author: Penguin
 */ 
#include "drivers/usart_driver.h"
#include <string.h>

#define CIRCULAR_BUFFER_SIZE 512

volatile uint8_t gpsdata[512];


volatile char tempChar;
volatile int numDataReady = 0;


static uint8_t circbuffer[CIRCULAR_BUFFER_SIZE];
static circular_buf_t cbuf;





void usart_comms_init()
{
	static usart_serial_options_t uconfc0 =
	{
		.baudrate = 115200,
		.stopbits = true,
		.paritytype = USART_PMODE_DISABLED_gc,
		.charlength = USART_CHSIZE_8BIT_gc,
	};
	
	/*
	static usart_rs232_options_t uconf3 =
	{
		.baudrate = 115200,
		.stopbits = true,
		.paritytype = USART_PMODE_DISABLED_gc,
		.charlength = USART_CHSIZE_8BIT_gc
	};
	*/
	
	static usart_rs232_options_t uconfd0 =
	{
		.baudrate = 9600,
		.stopbits = true,
		.paritytype = USART_PMODE_DISABLED_gc,
		.charlength = USART_CHSIZE_8BIT_gc,
	};


	usart_init_rs232(&USARTD0, &uconfd0);
	usart_set_rx_interrupt_level(&USARTD0, USART_INT_LVL_LO);
	
	
	stdio_serial_init(&USARTC0, &uconfc0);
	usart_set_rx_interrupt_level(&USARTC0, USART_INT_LVL_HI);
	printf("USART INIT SUCCESS\n");
	
	
	circular_buf_reset(&cbuf);
	cbuf.size = CIRCULAR_BUFFER_SIZE;
	cbuf.buffer = circbuffer;
}

void usart_print(USART_t *usart, char *text)
{
	while(*text)
	{
		usart_putchar(usart,*text++);
	}
}

ISR(USARTC0_RXC_vect)
{	
	//PORTE.OUT &= ~(1<<1);
	//temp = getchar();
	//putchar(temp);
	//PORTE.OUT |= (1<<1);
	putchar(getchar());
}


uint8_t newline_count = 0;
uint8_t buffer_position = 0;
_Bool gpsdata_ready = false;
volatile char current_char;





ISR(USARTD0_RXC_vect)
{
// 	putchar(usart_getchar(&USARTD0);
	current_char = usart_getchar(&USARTD0);
	if(circular_buf_full(cbuf))
	{
		printf("buffer is full, overwriting old data!\n");
	}
	if(current_char == '\n') numDataReady++;
	circular_buf_put(&cbuf, current_char);
	//putchar(current_char);

}

uint8_t read_gpsdata(void)
{
	uint8_t data;
	circular_buf_get(&cbuf,&data);
	return data;
}

int gpsdata_buffer_size(void)
{
	return cbuf.head - cbuf.tail;
}

circular_buf_t* get_cbuf(void)
{
	return &cbuf;
}

int data_ready(void)
{
	return numDataReady;
}

void take_data(void)
{
	numDataReady--;
}