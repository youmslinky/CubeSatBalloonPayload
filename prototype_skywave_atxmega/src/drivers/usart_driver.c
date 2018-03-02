/*
 * usart_driver.c
 *
 * Created: 1/3/2018 5:50:20 PM
 *  Author: Penguin
 */ 
#include "drivers/usart_driver.h"

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
	usart_set_rx_interrupt_level(&USARTD0, USART_INT_LVL_HI);
	
	
	stdio_serial_init(&USARTC0, &uconfc0);
	usart_set_rx_interrupt_level(&USARTC0, USART_INT_LVL_HI);
	printf("USART INIT SUCCESS\n");
}

ISR(USARTC0_RXC_vect)
{	
	//PORTE.OUT &= ~(1<<1);
	//temp = getchar();
	//putchar(temp);
	//PORTE.OUT |= (1<<1);
	putchar(getchar());
}

ISR(USARTD0_RXC_vect)
{
	char received_byte;
	received_byte = usart_getchar(&USARTD0);
	//putchar(received_byte);
}