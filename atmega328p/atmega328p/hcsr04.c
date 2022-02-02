/*
 * hcsr04.c
 *
 * Created: 1/02/2022 8:33:17 a. m.
 *  Author: juane
 */ 

#include <avr/io.h>
#include "hcsr04.h"

/////////////////////////////////////////////////////////
void configPWMTower()
{
	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: 8000.000 kHz
	// Mode: Fast PWM top=FFh
	// OC0 output: Non-Inverted PWM
	TCCR0A = 0x6b; // 0x69
	TCNT0 = 0x00;
	OCR0A = 0x00;
}

/////////////////////////////////////////////////////////
void configDistanceTower()
{
	// ICM conf.
	TCCR1A = 0;
	TIFR0 = (1<<ICF1);
	TCCR1B |= (1 << ICES1) | (1 << CS10);
	TIMSK1 |= (1 << ICIE1);
	TCNT1 = 0;

}

/////////////////////////////////////////////////////////
void setTrigger()
{
	PORTD &= ~(1 << TRIG);
	_delay_ms(TRIGGER);
	PORTD |= (1 << TRIG);
	_delay_us(TRIGGER);
	PORTD &= ~(1 << TRIG);
}

/////////////////////////////////////////////////////////
void setTowerMotion(unsigned char towerPos)
{
	OCR0A = towerPos;
}