/*
 * StepperLib.c
 *
 * Created: 2019-06-19 01:42:49 p.m.
 *  Author: BladimirBaccaCortes
	modificade: camilo chavez
 */ 
#include <avr/io.h>

#define F_CPU 4000000UL
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
float driveStepperOclock(float anguloMotor)
{
	int period;	
	period = 100;

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
	
	/* Rotate Stepper Motor Anticlockwise with Full step sequence */
	
	return anguloMotor;
		
}

void driveStepperAnticlock(float *angulo, float anguloMotor){
	int period;
	period = 100;
	
	(*angulo)= anguloMotor;
	
	PORTC = 0x09;
	anguloMotor -=2.8125;
	_delay_ms(period);
	
	PORTC = 0x01;
	anguloMotor -=2.8125;
	_delay_ms(period);
	
	PORTC = 0x03;
	anguloMotor -=2.8125;
	_delay_ms(period);

	PORTC = 0x02;
	anguloMotor -=2.8125;
	_delay_ms(period);
	
	PORTC = 0x06;
	anguloMotor -=2.8125;
	_delay_ms(period);

	PORTC = 0x04;
	anguloMotor -=2.8125;
	_delay_ms(period);
	
	PORTC = 0x0C;
	anguloMotor -=2.8125;
	_delay_ms(period);

	PORTC = 0x08;
	anguloMotor -=2.8125;
	_delay_ms(period);

}

