/*
 * atmega328p.c
 *
 * Created: 1/02/2022 7:55:39 a. m.
 * Author : juane
 */ 

#include <avr/io.h>
#include "stepMotor.h"

int main(void)
{
    /* Replace with your application code */
	unsigned char StepValue;
	
	StepValue = 0x01;
	
	// Port init
	DDRD |= (1 << 7);
	DDRC |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
	
    while (1) 
    {
		 //TODO:: Please write your application code
		 StepValue = driveStepper(StepValue);
    }
}

