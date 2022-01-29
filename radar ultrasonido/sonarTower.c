// Tower operation functions.
#include <avr/io.h>
#include "sonarTower.h"

/////////////////////////////////////////////////////////
void configPWMTower()
{
	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: 8000.000 kHz
	// Mode: Fast PWM top=FFh
	// OC0 output: Non-Inverted PWM
	TCCR0 = 0x6b; // 0x69
	TCNT0 = 0x00;
	OCR0 = 0x00;
}

/////////////////////////////////////////////////////////
void configDistanceTower()
{
	// ICM conf.
	TCCR1A = 0;
	TIFR = (1<<ICF1);
	TCCR1B |= (1 << ICES1) | (1 << CS11);
	TIMSK |= (1 << TICIE1);
	TCNT1 = 0;
}

/////////////////////////////////////////////////////////
void setTrigger()
{
	PORTB &= ~(1 << 0);
	_delay_ms(TRIGGER);
	PORTB |= (1 << 0);
	_delay_us(TRIGGER);
	PORTB &= ~(1 << 0);
}

/////////////////////////////////////////////////////////
void setTowerMotion(unsigned char towerPos)
{
	OCR0 = towerPos;
}