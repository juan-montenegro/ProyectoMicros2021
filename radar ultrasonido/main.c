/*
 * radar ultrasonido.c
 *
 * Created: 28/01/2022 4:44:55 p. m.
 * Author : Camilo Chavez, Esteban Montenegro, Francisco Mejia
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "StepperLib.h"
#include "UART.h"

#define		F_CPU 8000000UL
#define		SOUND_SPEED	(float) 17450 //(((331.5f*100f) + (0.6f*30.0f)) / 2.0f)

// Global variables for the ICM
volatile unsigned int tSignal[2];
volatile unsigned int ti = 0;
volatile unsigned char icr1Flag = 0;

/////////////////////////////////////////////////////////
// ISR for ICM
ISR(TIMER1_CAPT_vect)
{
	tSignal[ti] = ICR1;
	
	if (ti==0)
	TCCR1B &= ~(1 << ICES1);
	
	ti++;
	if (ti > 1)
	{
		ti = 0;
		icr1Flag = 1;
		TCNT1 = 0;
		TCCR1B |= (1 << ICES1);
	}
}

int main(void)
{
	//Uart iniciacion
	uart_init(9600);
	configPWMTower();
	configDistanceTower();
	
	// Global interrupt enable
	sei();
	
	// Port init
	DDRA = 0x00;
	DDRB |= (1 << 0);
	DDRB |= (1 << 5);
	DDRC = 0x0F;
	
	//iniciacion de variables 
	float anguloMotor=0;
	float rangeSensor;
	char cadena[30];
	char BUFF[6];
	char BUFF2[6];
	
	while(1)
	{
		//TODO:: Please write your application code
		for(int i=0;i<16;i++){	
			
			//SE LLAMA LA FUNCION ULTRASONIDO 
			setTrigger();
			
			// Measuring distance
			while(!icr1Flag);
			icr1Flag = 0;
			rangeSensor = ((tSignal[1] - tSignal[0]) * SOUND_SPEED * 64) / (F_CPU);
			
			anguloMotor= driveStepperOclock(anguloMotor); //se mueve el motor 22.5 angulo
			
			dtostrf(anguloMotor,6,4,BUFF);
			sprintf(cadena,"\n\rAngulo: %s\r\n",BUFF);
			_delay_ms(100);
			Uart_write_txt(cadena);
			
			dtostrf(rangeSensor,6,4,BUFF2);
			sprintf(cadena,"\n\rDistancia: %s \r\n",BUFF2);
			_delay_ms(100);
			Uart_write_txt(cadena);
			
			//Positioning the tower
			setTowerMotion(anguloMotor);
				
		}
			
		PORTC = 0x09;		/* Last step to initial position */
		_delay_ms(1000);
		
		for(int i=0;i<16;i++){	
			
			//SE LLAMA LA FUNCION ULTRASONIDO
			setTrigger();
			
			// Measuring distance
			while(!icr1Flag);
			icr1Flag = 0;
			rangeSensor = ((tSignal[1] - tSignal[0]) * SOUND_SPEED * 64) / (F_CPU);
			
			anguloMotor= driveStepperAnticlock(anguloMotor); //se mueve el motor 22.5 angulo
			
			dtostrf(anguloMotor,6,4,BUFF);
			sprintf(cadena,"\n\rAngulo: %s\r\n",BUFF);
			_delay_ms(100);
			Uart_write_txt(cadena);
			
			dtostrf(rangeSensor,6,4,BUFF2);
			sprintf(cadena,"\n\rDistancia: %s \r\n",BUFF2);
			_delay_ms(100);
			Uart_write_txt(cadena);
			
			//Positioning the tower
			setTowerMotion(anguloMotor);
		}
		
		PORTC = 0x09;
		_delay_ms(1000);
	}
}
