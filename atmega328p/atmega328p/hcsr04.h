/*
 * hcsr04.h
 *
 * Created: 1/02/2022 8:04:12 a. m.
 *  Author: juane
 */ 


#ifndef HCSR04_H_
#define HCSR04_H_

#define		F_CPU	8000000L
#define		ECHO PORTB0
#define		TRIG PORTD7
#include	<util/delay.h>
#define		TRIGGER		10

void configPWMTower();
void configDistanceTower();
void setTrigger();
void setTowerMotion(unsigned char towerPos);

#endif /* HCSR04_H_ */