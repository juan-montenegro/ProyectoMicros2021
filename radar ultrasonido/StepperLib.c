/*
 * StepperLib.c
 *
 * Created: 2019-06-19 01:42:49 p.m.
 *  Author: BladimirBaccaCortes
	modificade: camilo chavez
 */ 
#include <avr/io.h>

#define F_CPU 8000000UL
#define DELAY_BASE	170
#define PERIOD 10
#define angle 0.08789

#include <util/delay.h>


////////////////////////////////////////////////////
int isButtonPressed(unsigned char bitPos)
{
	if (PINA & bitPos)
	return 1;
	else
	return 0;
}

////////////////////////////////////////////////////
float driveStepperOclock(float anguloMotor)
{
	PORTC = 0x09;
	anguloMotor +=angle;
	_delay_ms(PERIOD);

	PORTC = 0x08;
	anguloMotor +=angle;
	_delay_ms(PERIOD);

	PORTC = 0x0C;
	anguloMotor +=angle;
	_delay_ms(PERIOD);
	
	PORTC = 0x04;
	anguloMotor +=angle;
	_delay_ms(PERIOD);

	PORTC = 0x06;
	anguloMotor +=angle;
	_delay_ms(PERIOD);
	
	PORTC = 0x02;
	anguloMotor +=angle;
	_delay_ms(PERIOD);
	
	PORTC = 0x03;
	anguloMotor +=angle;
	_delay_ms(PERIOD);
	
	PORTC = 0x01;
	anguloMotor +=angle;
	_delay_ms(PERIOD);
	
	/* Rotate Stepper Motor Anticlockwise with half step sequence */
	
	return anguloMotor;
	
}

float driveStepperAnticlock(float anguloMotor){

	PORTC = 0x09;
	anguloMotor -=angle;
	_delay_ms(PERIOD);
	
	PORTC = 0x01;
	anguloMotor -=angle;
	_delay_ms(PERIOD);
	
	PORTC = 0x03;
	anguloMotor -=angle;
	_delay_ms(PERIOD);

	PORTC = 0x02;
	anguloMotor -=angle;
	_delay_ms(PERIOD);
	
	PORTC = 0x06;
	anguloMotor -=angle;
	_delay_ms(PERIOD);

	PORTC = 0x04;
	anguloMotor -=angle;
	_delay_ms(PERIOD);
	
	PORTC = 0x0C;
	anguloMotor -=angle;
	_delay_ms(PERIOD);

	PORTC = 0x08;
	anguloMotor -=angle;
	_delay_ms(PERIOD);

	return anguloMotor;
}

