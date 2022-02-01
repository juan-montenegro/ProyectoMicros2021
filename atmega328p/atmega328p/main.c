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
	DDRC |= (1 << 6);
	DDRC = 0xff;
	
    while (1) 
    {
		 //TODO:: Please write your application code
		 StepValue = driveStepper(StepValue);
    }
}

