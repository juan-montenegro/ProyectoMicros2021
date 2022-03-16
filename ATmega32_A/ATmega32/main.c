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
#define	SOUND_SPEED	(float) 331.4	// Velocidad a 0°C (m/s)
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
	//Uart iniciacion
	uart_init(9600);
	configPWMTower();
	configDistanceTower();
	
	// Global interrupt enable
	sei();
	
	// Port init
	DDRA = 0x00;
	DDRB |= (1 << 0);
	DDRD |= (1 << 5);
	DDRC = 0x0F;
	
	//iniciacion de variables 
	int mod;
	float anguloMotor=0;
	float ciclo=0;
	float distancia;
	float velocidad;
	velocidad = (SOUND_SPEED+(0.606*TEMPERATURE)+(0.0124*HUMIDITY))/10000;
	float tiempo = 0;
	char cadena[30];
	char BUFF[12];
	char BUFF2[12];
	
	// Global interrupt enable
	sei();

	
	while (1)
	{
		//TODO:: Please write your application code
		for(int i=0;i<512;i++){
			
			//SE LLAMA LA FUNCION ULTRASONIDO
			
			
			// Measuring distance
			mod = i % 16;
			anguloMotor= driveStepperOclock(anguloMotor); //se mueve el motor 22.5 angulo
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
