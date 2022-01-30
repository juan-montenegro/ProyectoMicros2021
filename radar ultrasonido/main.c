/*
 * radar ultrasonido.c
 *
 * Created: 28/01/2022 4:44:55 p. m.
 * Author : Camilo Chavez, Esteban Montenegro, Francisco Mejia
 */ 


#include <avr/io.h>
#include "StepperLib.h"
#include "UART.h"
#define F_CPU 4000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <math.h>



int main(void)
{
	//Uart iniciacion
	uart_init(19200);
	
		/* Set period in between two steps */
	
	// Port init
	DDRA = 0x00;
	DDRC = 0x0F;
	
	//iniciacion de variables 
	float anguloMotor=0;
	//float *anguloReal;
	char cadena[12];
	//float auxiliar;
	
	while(1)
	{
		//TODO:: Please write your application code
		for(int i=0;i<16;i++){	
			
			//SE LLAMA LA FUNCION ULTRASONIDO 
			anguloMotor= driveStepperOclock(anguloMotor); //se mueve el motor 22.5 angulo
			sprintf(cadena,"\n\rAngulo: %f\r\n", anguloMotor);
			Uart_write_txt(cadena);
				
		}
			
		PORTC = 0x09;		/* Last step to initial position */
		_delay_ms(1000);
		
		for(int i=0;i<16;i++){	
			
			//SE LLAMA LA FUNCION ULTRASONIDO 
			anguloMotor=driveStepperAnticlock(anguloMotor);
			sprintf(cadena,"\n\rAngulo: %f\r\n", anguloMotor);
			Uart_write_txt(cadena);
		}
		
		PORTC = 0x09;
		_delay_ms(1000);
	}
}
