/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include "project_skywave.h"
#include "drivers/usart_driver.h"
#include "drivers/ntcle100.h"
#include "drivers/imu_driver.h"
#include "drivers/ms5611.h"
#include "drivers/bno055.h"
#include "drivers/ultimate_gps_driver.h"
#include "utility/circular_buff.h"



int main (void)
{
	//config pins
	//config clocks and peripherals and stuff
	//initializers
	
	board_init();
	
	sysclk_init();
	
	irq_initialize_vectors();
		
		
	//eventually enable this
	cpu_irq_enable();

	sysclk_enable_peripheral_clock(&TWIF);
	sysclk_enable_peripheral_clock(&ADCA);
	sysclk_enable_peripheral_clock(&USARTC0);
	sysclk_enable_peripheral_clock(&USARTD0);
	sysclk_enable_peripheral_clock(&SPIC);
	
	usart_comms_init();
	twi_comms_init();


	PORTE.DIR |= (1<<0) | (1<<1);
	//PORTD.DIR &= ~(1<<2); //not sure what this was for


	//pins for bno055
	//enable pullups and output for portf pins 0, 1 (sda,scl)
	PORTF.PIN0CTRL = PORT_OPC_WIREDANDPULL_gc;
	PORTF.PIN1CTRL = PORT_OPC_WIREDANDPULL_gc;

	//enable pins for virtual serial port to computer
	PORTC.OUT |= 0b00001000;
	PORTC.DIR |= 0b00001000;


	//set pin to output for writing to the openlogger
	PORTD.DIR |= 0b00001000;

	delay_ms(1000);
	//set up bno055
	while (!(bno055_is_alive())){}
	bno055_setmode_NDOF();

	delay_ms(1000);


	circular_buf_t *gps_cbuf = get_cbuf();

	while (1) 
	{
		
		
		uint8_t data;
		if(data_ready() >= 1)
		{
			while(1)
			{
				circular_buf_get(gps_cbuf,&data);
				printf("%c",data);
				if(data == '\n') break;
			}
			take_data();
		}
		printf("numdataready: %d\n",data_ready());
		
		//usart_putchar(&USARTD0,'t');  //write to openlogger

		//usart_print(&USARTD0,"hello\n");
		
		bno055_get_data();
		bno055_process_data();
		PORTE.OUT ^= (1<<0);
		delay_ms(200);
		
	}
}
