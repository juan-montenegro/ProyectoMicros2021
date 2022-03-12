/*
 * atmega328p.c
 *
 * Created: 1/02/2022 7:55:39 a. m.
 * Author : juane
 */ 
#include <stdio.h>
#include <avr/io.h>

/* Libraries */
#include "stepMotor.h"
#include "uart.h"
#include "hcsr04.h"

#include <util/delay.h>
#include <avr/interrupt.h>


/* Define F_CPU in hz here */
#define F_CPU 8000000UL

/* Define UART baud rate here */
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

/* Constants */
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
	int mod;
	float anguloMotor=0;
	float ciclo=0;
	float distancia;
	float velocidad;
	
	// Velocidad del sonido en cm/us
	velocidad = (SOUND_SPEED+(0.606*TEMPERATURE)+(0.0124*HUMIDITY))/10000;
	
	float tiempo = 0;
	char cadena[30];
	char BUFF[12];
	char BUFF2[12];
	
	// Port init
	DDRD &= ~(1 << PIND6);
	DDRD |= (1 << TRIG);

	DDRC |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
	PORTB |= (1 << ECHO);
	

	uart_init(MYUBRR);
	configPWMTower();
	configDistanceTower();
	
	// Global interrupt enable
	sei();

	
    while (1) 
    {
		 //TODO:: Please write your application code
		 for(int i=0;i<512;i++){
			mod = i % 16;
			anguloMotor= driveStepperOclock(anguloMotor); //se mueve el motor 22.5 angulo
			if	 (mod == 0){
				//SE LLAMA LA FUNCION ULTRASONIDO
				setTrigger();
				
				// Measuring distance
				while(!icr1Flag);
				icr1Flag = 0;
				
				// Measuring distance
				ciclo = (tSignal[1] - tSignal[0]);
				tiempo = ciclo*32768*2/65536;
				distancia = (tiempo*velocidad)/2;
				dtostrf(anguloMotor,12,4,BUFF);
				sprintf(cadena,"\n\rAngulo: %s \r\n",BUFF);
				Uart_write_txt(cadena);
				
				dtostrf(distancia,12,4,BUFF2);
				sprintf(cadena,"\n\rDistancia: %s cm\r\n",BUFF2);
				Uart_write_txt(cadena);
				
				//Positioning the tower
				setTowerMotion(anguloMotor);
			 }
			 
		 }
		 PORTC = 0x09;		/* Last step to initial position */
		 _delay_ms(1000);
		 for(int i=0;i<512;i++){
			 
			 //SE LLAMA LA FUNCION ULTRASONIDO
			 
			 
			 // Measuring distance
			 mod = i % 16;
			 anguloMotor= driveStepperAnticlock(anguloMotor); //se mueve el motor 22.5 angulo
			 
			 if	 (mod == 0){
				 setTrigger();
				 
				 // Measuring distance
				 while(!icr1Flag);
				 icr1Flag = 0;
				 ciclo = (tSignal[1] - tSignal[0]);
				 tiempo = ciclo*32768*2/65536;
				 distancia = (tiempo*velocidad)/2;
				 				 
				 dtostrf(anguloMotor,12,4,BUFF);
				 sprintf(cadena,"\n\rAngulo: %s \r\n",BUFF);
				 Uart_write_txt(cadena);
				 
				 dtostrf(distancia,12,4,BUFF2);
				 sprintf(cadena,"\n\rDistancia: %s cm\r\n",BUFF2);
				 Uart_write_txt(cadena);
				 
				 //Positioning the tower
				 setTowerMotion(anguloMotor);
			 }
		 }
		 PORTC = 0x09;		/* Last step to initial position */
		 _delay_ms(1000);
    }
}

