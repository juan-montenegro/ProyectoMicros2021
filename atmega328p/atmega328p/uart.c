/*
 * uart.c
 *
 * Created: 1/02/2022 8:33:32 a. m.
 *  Author: juane
 */ 
#include <avr/io.h>

/* Define F_CPU in hz here */
#define F_CPU 16000000UL

#include "UART.h"

void uART_init(unsigned int ubrr){
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART Receiver: On
	// USART Transmitter: On
	// USART Mode: Asynchronous
	// USART Baud Rate: 9600
	
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)(ubrr);


	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	/* Set frame format: 8data */
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
	UCSR0A |= (1<<UDRE0);
}

//----------FUNCIONES PARA TRANSMITIR Y RECEPTAR------------------------------------------------

int UART_putc(unsigned char caracter)
{
	while (!(UCSR0A & (1 << UDRE0))); // si el bit 5 del registro UCSRA es 1, entonces esta disponible para enviar datos TRANSMISION
	UDR0=caracter; //me recibe un char para guardarlo en el registro UDR y enviarlo TRANSMISION
}

void UART_puts(char* cadena){
	while(*cadena !=0x00){
		UART_putc(*cadena++);
	}
}


int isUSARTerror() // funcion que me da 1 si hay un error al recibir los datos, mientras sea 0 se puede guardar los datos RECEPTOR
{
	if (((UCSR0A & (1 << FE0)) | (UCSR0A & (1 << DOR0)) | (UCSR0A & (1 << UPE0)))) //bit de error al recibir o desbordamiento o error de paridad
	return 1;
	else
	return 0;
}

unsigned char UART_get(){ //RECEPTOR
	
	if(UCSR0A &(1<<RXC0)){			//si el bit7 del registro UCSRA se ha puesto a 1 (bit RXC esta en 1 cuando hay un dato en el receptor)
		return UDR0;			//devuelve el dato almacenado en el registro UDR
	}
	else{
		return 0;
	}
}