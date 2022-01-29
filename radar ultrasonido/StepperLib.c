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
void driveStepper(float *angulo)
{
	int period;	
	period = 100;
	
	float anguloMotor=0;
	(*angulo) = anguloMotor;
	
	for(int i=0;i<16;i++)
	{
		PORTC = 0x09;
		anguloMotor +=2.8125;
		_delay_ms(period);
		PORTC = 0x08;
		anguloMotor +=2.8125;
		_delay_ms(period);
		PORTC = 0x0C;
		anguloMotor +=2.8125;
		_delay_ms(period);
		PORTC = 0x04;
		anguloMotor +=2.8125;
		_delay_ms(period);
		PORTC = 0x06;
		anguloMotor +=2.8125;
		_delay_ms(period);
		PORTC = 0x02;
		anguloMotor +=2.8125;
		_delay_ms(period);
		PORTC = 0x03;
		anguloMotor +=2.8125;
		_delay_ms(period);
		PORTC = 0x01;
		anguloMotor +=2.8125;
		_delay_ms(period);
	}
	PORTC = 0x09;		/* Last step to initial position */
	_delay_ms(period);
	_delay_ms(1000);

	/* Rotate Stepper Motor Anticlockwise with Full step sequence */
	for(int i=0;i<16;i++)
	{
		PORTC = 0x09;
		_delay_ms(period);
		PORTC = 0x01;
		_delay_ms(period);
		PORTC = 0x03;
		_delay_ms(period);
		PORTC = 0x02;
		_delay_ms(period);
		PORTC = 0x06;
		_delay_ms(period);
		PORTC = 0x04;
		_delay_ms(period);
		PORTC = 0x0C;
		_delay_ms(period);
		PORTC = 0x08;
		_delay_ms(period);
	}
	PORTC = 0x09;
	_delay_ms(period);
	_delay_ms(1000);
}

