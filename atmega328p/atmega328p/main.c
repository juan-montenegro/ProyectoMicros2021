/*
 * atmega328p.c
 *
 * Created: 1/02/2022 7:55:39 a. m.
 * Author : juane
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

/* Define F_CPU in hz here */
#define F_CPU 16000000UL

/* Define UART baud rate here */
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

/* Libraries */
#include "stepMotor.h"
#include "uart.h"
#include "hcsr04.h"

#include <util/delay.h>
#include <avr/interrupt.h>

/* Define constants */
#define	SOUND_SPEED	(float) 331.4	// Velocidad a 0°C
#define TEMPERATURE (float) 30.0	// Temperatura
#define HUMIDITY	(float) 80.0	// Humedad

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
    /* Replace with your application code */
	int mod=0;
	float aMotor=0;
	float ciclo=0;
	float distancia;
	float velocidad;
	int cont = 0;
	unsigned char CH = 0x00;
	unsigned char START = 0x61;
	unsigned char STOP = 0x73;
	// Velocidad del sonido en cm/us
	velocidad = (SOUND_SPEED+(0.606*TEMPERATURE)+(0.0124*HUMIDITY))/10000;
	
	float tiempo = 0;
	char cadena[30];
	char BUFF[12];
	char BUFF2[12];
	
	// Port init
	//DDRD &= ~(1 << PIND6);
	
	DDRC |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
	
	UART_init(MYUBRR);
	initSensor();
	// Global interrupt enable
	do
		{
			CH = UART_get();
		} while (CH != START);
	sei();
	
	//UART_String("\n\rNo|Angulo|Distancia\r\n");
    while (1) 
    {
		 //TODO:: Please write your application code
		 for(int i=0;i<STEP;i++){
			//mod = (i+1) % 16;
			cli();
			CH = UART_get();
			if (CH == STOP)
			{
				do
				{
					CH = UART_get();
				} while (CH != START);
			}
			if	 (mod == 0){
				//SE LLAMA LA FUNCION ULTRASONIDO
				sei();
				
				setTrigger();
				
				// Measuring distance
				while(!icr1Flag);
				icr1Flag = 0;
				
				// Measuring distance
				ciclo = (tSignal[1] - tSignal[0]);
				tiempo = ciclo*(32768*8)/65536;
				distancia = (tiempo*velocidad)/2;
				
				// Send Data
				dtostrf(aMotor,8,4,BUFF);
				dtostrf(distancia,8,4,BUFF2);
				sprintf(cadena,"\n\r%d|%s|%s|%d\r\n",cont ,BUFF ,BUFF2,i);
				UART_String(cadena);
				
				cont = cont + 1;
			 }
			 mod++;
			 if(mod==16){
				 mod=0;
			 }
			aMotor= dsOclock(aMotor); //se mueve el motor 7.031 angulo
			
		 }
		 PORTC = 0x09;		/* Last step to initial position */
		 _delay_ms(1000);
		 aMotor=0;
		 for(int i=0;i<STEP;i++){
			 //mod = (i+1) % 16;
			 cli();
			 CH = UART_get();
			 if (CH == STOP)
			 {
				 do
				 {
					 CH = UART_get();
				 } while (CH != START);
			 }
			 if	 (mod == 0){
				 sei();
				 setTrigger();
				 
				 
				 // Measuring distance
				 while(!icr1Flag);
				 icr1Flag = 0;
				 
				 // Measuring distance
				 ciclo = (tSignal[1] - tSignal[0]);
				 tiempo = ciclo*(32768*8)/65536;
				 distancia = (tiempo*velocidad)/2;
				 
				 // Send Data
				 dtostrf(aMotor,8,4,BUFF);
				 dtostrf(distancia,8,4,BUFF2);
				 if (cont == 32)
				 {
					 sprintf(cadena,"\n\r%d|-%s|%s|%d\r\n",0 ,BUFF ,BUFF2,i);
				 }
				 else{
					 sprintf(cadena,"\n\r%d|-%s|%s|%d\r\n",cont ,BUFF ,BUFF2,i);
				 }
				 UART_String(cadena);
				 cont = cont - 1;
			 }
			mod++;
			if(mod==16){
				mod=0;
			}
			aMotor= dsAnticlock(aMotor); //se mueve el motor 0.7031 angulo
		 }
		 PORTC = 0x09;		/* Last step to initial position */
		 _delay_ms(1000);
		 aMotor=0;
    }
}

