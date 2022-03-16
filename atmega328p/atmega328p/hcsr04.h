/*
 * hcsr04.h
 *
 * Created: 1/02/2022 8:04:12 a. m.
 *  Author: juane
 */ 


#ifndef HCSR04_H_
#define HCSR04_H_

#define		ECHO	PINB0
#define		TRIG	PIND7
#define		TRIGGER	10

void initSensor();
void setTrigger();
//void setTowerMotion(unsigned char towerPos);

#endif /* HCSR04_H_ */