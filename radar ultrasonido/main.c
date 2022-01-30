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
#include <stdio.h>
#include <math.h>



int main(void)
{
	//Uart iniciacion
	uart_init(9600);
	
	/* Set period in between two steps */
	
	// Port init
	DDRA = 0x00;
	DDRC = 0x0F;
	
	//iniciacion de variables 
	float anguloMotor=0;
	char cadena[24];
	char BUFF[12];
	float a = 22.5;
	
	while(1)
	{
		//TODO:: Please write your application code
		for(int i=0;i<16;i++){	
			
			//SE LLAMA LA FUNCION ULTRASONIDO 
			anguloMotor= driveStepperOclock(anguloMotor); //se mueve el motor 22.5 angulo
			dtostrf(anguloMotor,12,4,BUFF);
			sprintf(cadena,"\n\rAngulo: %s \r\n", BUFF);
			_delay_ms(100);
			Uart_write_txt(cadena);
				
		}
			
		PORTC = 0x09;		/* Last step to initial position */
		_delay_ms(1000);
		
		for(int i=0;i<16;i++){	
			
			//SE LLAMA LA FUNCION ULTRASONIDO 
			anguloMotor=driveStepperAnticlock(anguloMotor);
			dtostrf(anguloMotor,12,4,BUFF);
			sprintf(cadena,"\n\rAngulo: %s \r\n", BUFF);
			Uart_write_txt(cadena);
		}
		
		PORTC = 0x09;
		_delay_ms(1000);
	}
}
