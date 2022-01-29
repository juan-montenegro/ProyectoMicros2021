/*
 * radar ultrasonido.c
 *
 * Created: 28/01/2022 4:44:55 p. m.
 * Author : camilo chavez, Esteban Montenegro, Franciscos Mejia
 */ 


#include <avr/io.h>
#include "StepperLib.h"
#include "UART.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void)
{
	//Uart iniciacion
	uart_init();
	
		/* Set period in between two steps */
	
	// Port init
	DDRA = 0x00;
	DDRC = 0x0F;
	
	while(1)
	{
		//TODO:: Please write your application code
		driveStepper();
	}
}
