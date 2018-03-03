/*
 * usart_driver.c
 *
 * Created: 1/3/2018 5:50:20 PM
 *  Author: Penguin
 */ 
#include "drivers/usart_driver.h"
#include <string.h>
volatile uint8_t gpsdata[512];
static uint8_t gpsdata_old[512];
volatile char tempChar;
int tempCounter;
_Bool dataReady;

void usart_comms_init()
{
	dataReady = false;
	tempCounter = 0;
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
volatile char stuff;
_Bool firsttry = false;

#define RING_BUFF_SIZE 2048
char ring_buff[RING_BUFF_SIZE];
uint16_t ring_buff_rd = 0;
uint16_t ring_buff_wr = 0;


ISR(USARTD0_RXC_vect)
{
	stuff = usart_getchar(&USARTD0);

	//putchar(usart_getchar(&USARTD0));
//  	tempChar = usart_getchar(&USARTD0);
//  	if(tempChar == '\r')
//  	{
// 	 	newline_count++;
//  	}
//  	gpsdata[tempCounter++] = tempChar;
//  	if(newline_count >= 1)
//  	{
// 	 	dataReady = true;
// 	 	newline_count = 0;
// 	 	tempCounter = 0;
//  	}

	//usart_putchar(usart_getchar(&))

	
	
	
	

// 	uint8_t recieved_char;
// 	recieved_char = usart_getchar(&USARTD0);
// 	gpsdata[buffer_position] = recieved_char;
// 	buffer_position++;
// 	if(recieved_char == '\n')
// 	{
// 		newline_count++;
// 	}
// 	if(newline_count == 4)
// 	{
// 		//printf(gpsdata);
// 		strcpy(gpsdata_old,gpsdata);
// 		gpsdata_ready = true;
// 		buffer_position = 0;
// 		newline_count = 0;
// 	}
}

uint8_t* return_gps_data(void){
	//gpsdata_ready = false;
	return gpsdata;

}

void get_new_data(void){
	gpsdata_ready = false;
}

void set_busy_flag(void)
{
	dataReady = true;
}

void clear_busy_flag(void)
{
	dataReady = false;
}

_Bool check_busy_flag(void)
{
	return dataReady;
}
