/*
 * stepMotor.c
 *
 * Created: 1/02/2022 8:05:40 a. m.
 *  Author: juane
 */ 

#include <avr/io.h>

#define DELAY_BASE	170
#define PERIOD 10
#define angle 0.08789
#include <util/delay.h>


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