/*
 * hcsr04.c
 *
 * Created: 1/02/2022 8:33:17 a. m.
 *  Author: juane
 */ 

#include <avr/io.h>

/* Define F_CPU in hz here */
#define F_CPU 16000000UL

#include "hcsr04.h"
#include <util/delay.h>
#include <avr/interrupt.h>



/////////////////////////////////////////////////////////
void initSensor()
{
	DDRD |= (1 << TRIG);
	DDRB &= ~(1 << ECHO);
	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: 8000000 Hz
	// Mode: Fast PWM top=FFh
	// OC0 output: Non-Inverted PWM
	TCCR0A = 0x6b; // 0x69
	TCCR1A = 0;
	TCCR0B = 0;
	
	TCNT0 = 0x00;
	TCNT1 = 0;
	//OCR0A = 0x00;
	
	// ICM conf.
	TIFR0 |= (1 << OCF0A);
	
	// Noice reduction enable
	// TCCR1B |= (1 << ICNC1);
	
	// PreScaling to 64
	TCCR1B |= (1 << CS10) | (1 << CS11);
	
	// Read Int. at: rising edge, falling edge
	TIMSK1 |= (1 << ICIE1);
	//TIMSK1 |= (1 << OCIE1A);
	
	// Read Int. at: rising edge
	TCCR1B |= (1 << ICES1);
}

/////////////////////////////////////////////////////////
void setTrigger()
{
	PORTD &= ~(1 << TRIG);
	_delay_ms(1);
	PORTD |= (1 << TRIG);
	_delay_us(TRIGGER);
	PORTD &= ~(1 << TRIG);
}

/////////////////////////////////////////////////////////
/*
void setTowerMotion(unsigned char towerPos)
{
	OCR0A = towerPos;
}*/