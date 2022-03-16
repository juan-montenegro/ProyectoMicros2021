/*
 * stepMotor.c
 *
 * Created: 1/02/2022 8:05:40 a. m.
 *  Author: juane
 */ 

#include <avr/io.h>

/* Define F_CPU in hz here */
#define F_CPU 16000000UL

#include "stepMotor.h"
#include <util/delay.h>
#include <math.h>


////////////////////////////////////////////////////
int isButtonPressed(unsigned char bitPos)
{
	if (PIND6 & bitPos)
	return 1;
	else
	return 0;
}

////////////////////////////////////////////////////
float driveStepperOclock(float anguloMotor)
{
	PORTC = 0x09;
	_delay_ms(PERIOD);

	PORTC = 0x08;
	_delay_ms(PERIOD);

	PORTC = 0x0C;
	_delay_ms(PERIOD);
	
	PORTC = 0x04;
	_delay_ms(PERIOD);

	PORTC = 0x06;
	_delay_ms(PERIOD);
	
	PORTC = 0x02;
	_delay_ms(PERIOD);
	
	PORTC = 0x03;
	_delay_ms(PERIOD);
	
	PORTC = 0x01;
	_delay_ms(PERIOD);
	
	/* Rotate Stepper Motor Anticlockwise with half step sequence */
	anguloMotor +=angle;

	return anguloMotor;
	
}

float driveStepperAnticlock(float anguloMotor){

	PORTC = 0x09;
	_delay_ms(PERIOD);
	
	PORTC = 0x01;
	_delay_ms(PERIOD);
	
	PORTC = 0x03;
	_delay_ms(PERIOD);

	PORTC = 0x02;
	_delay_ms(PERIOD);
	
	PORTC = 0x06;
	_delay_ms(PERIOD);

	PORTC = 0x04;
	_delay_ms(PERIOD);
	
	PORTC = 0x0C;
	_delay_ms(PERIOD);

	PORTC = 0x08;
	_delay_ms(PERIOD);

	anguloMotor -=angle;
	return anguloMotor;
}