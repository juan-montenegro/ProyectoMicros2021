/*
 * atmega328p.c
 *
 * Created: 1/02/2022 7:55:39 a. m.
 * Author : juane
 */ 
#include <stdio.h>
#include <avr/io.h>

#define F_CPU 8000000UL

#include "stepMotor.h"
#include "uart.h"
#include "hcsr04.h"

#include <util/delay.h>
#include <avr/interrupt.h>


int main(void)
{
    /* Replace with your application code */
	float anguloMotor=0;
	char cadena[30];
	char BUFF[6];
	
	// Port init
	DDRD |= (1 << 7);
	DDRC |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
	
	sei();
	uart_init();

	
    while (1) 
    {
		 //TODO:: Please write your application code
		 for(int i=0;i<512;i++){
			 
			 //SE LLAMA LA FUNCION ULTRASONIDO
			 
			 
			 // Measuring distance
			 			 
			 anguloMotor= driveStepperOclock(anguloMotor); //se mueve el motor 22.5 angulo
			 dtostrf(anguloMotor,6,4,BUFF);
			 sprintf(cadena,"\n\rAngulo: %s\r\n",BUFF);
			 Uart_write_txt(cadena);
			 
		 }
		 PORTC = 0x09;		/* Last step to initial position */
		 _delay_ms(1000);
		 for(int i=0;i<512;i++){
			 
			 //SE LLAMA LA FUNCION ULTRASONIDO
			 
			 
			 // Measuring distance
			 
			 anguloMotor= driveStepperAnticlock(anguloMotor); //se mueve el motor 22.5 angulo
			 
			 dtostrf(anguloMotor,6,4,BUFF);
			 sprintf(cadena,"\n\rAngulo: %s\r\n",BUFF);
			 Uart_write_txt(cadena);
		 }
		 PORTC = 0x09;		/* Last step to initial position */
		 _delay_ms(1000);
    }
}

