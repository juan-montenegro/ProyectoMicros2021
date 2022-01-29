/*
 * radar ultrasonido.c
 *
 * Created: 28/01/2022 4:44:55 p. m.
 * Author : Camilo Chavez, Esteban Montenegro, Francisco Mejia
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
	
	//Iniciación de variables 
	float anguloMotor=0;
	float *anguloReal;
	char cadena[10];
	
	while(1)
	{
		//TODO:: Please write your application code
		for(int i=0;i<16;i++){	
			
			//SE LLAMA LA FUNCION ULTRASONIDO 
			driveStepperOclock(&anguloReal,anguloMotor); //se mueve el motor 22.5 angulo
			
			sprintf(cadena,"\n\rAngulo:\n\r");
			Uart_write_txt(cadena);
				
		}
			
		PORTC = 0x09;		/* Last step to initial position */
		_delay_ms(1000);
		
		for(int i=0;i<16;i++){	
			
			//SE LLAMA LA FUNCION ULTRASONIDO 
			driveStepperAnticlock(&anguloReal,anguloMotor);
			sprintf(cadena,"\n\rAngulo\n\r");
			Uart_write_txt(cadena);
		}
		
		PORTC = 0x09;
		_delay_ms(1000);
	}
}
