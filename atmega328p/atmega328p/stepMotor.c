/*
 * stepMotor.c
 *
 * Created: 1/02/2022 8:05:40 a. m.
 *  Author: juane
 */ 

#include <avr/io.h>

#define F_CPU 8000000UL
#define DELAY_BASE	170

#include <util/delay.h>
#include "stepMotor.h"


////////////////////////////////////////////////////
int isButtonPressed(unsigned char bitPos)
{
	if (PIND7 & bitPos)
	return 1;
	else
	return 0;
}

////////////////////////////////////////////////////
unsigned char driveStepper(unsigned char StepValue)
{
	
	
	PORTC = StepValue;
	
	_delay_ms(DELAY_BASE);
	
	if (!isButtonPressed(0x01))
	{
		StepValue <<= 1;
		
		if (StepValue == 0x10)
		StepValue = 0x01;
	}
	else
	{
		StepValue >>= 1;
		
		if (StepValue == 0x00)
		StepValue = 0x08;
	}
	
	return StepValue;
}