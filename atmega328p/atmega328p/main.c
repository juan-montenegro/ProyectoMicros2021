/*
 * atmega328p.c
 *
 * Created: 1/02/2022 7:55:39 a. m.
 * Author : juane
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include "stepMotor.h"
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	float anguloMotor=0;
	
	
	// Port init
	DDRD |= (1 << 7);
	DDRC |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
	
    while (1) 
    {
		 //TODO:: Please write your application code
		 for(int i=0;i<512;i++){
			 
			 //SE LLAMA LA FUNCION ULTRASONIDO
			 
			 
			 // Measuring distance
			 			 
			 anguloMotor= driveStepperOclock(anguloMotor); //se mueve el motor 22.5 angulo
		 }
		 PORTC = 0x09;		/* Last step to initial position */
		 _delay_ms(1000);
		 for(int i=0;i<512;i++){
			 
			 //SE LLAMA LA FUNCION ULTRASONIDO
			 
			 
			 // Measuring distance
			 
			 anguloMotor= driveStepperAnticlock(anguloMotor); //se mueve el motor 22.5 angulo
		 }
		 PORTC = 0x09;		/* Last step to initial position */
		 _delay_ms(1000);
    }
}

