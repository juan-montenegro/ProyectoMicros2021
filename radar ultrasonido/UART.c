/*
 * CFile1.c
 *
 * Created: 24/01/2022 9:53:31 p. m.
 *  Author: camilo chavez
 */ 

#include <avr/io.h>
#include "UART.h"

#define F_CPU 4000000UL
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void uart_init(long USART_BAUDRATE){
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART Receiver: On
	// USART Transmitter: On
	// USART Mode: Asynchronous
	// USART Baud Rate: 9600
	
	DDRD = 0X02;// 0b0010, bit 0 de entrada (RXD), bit 1 de salida (TXD)
	PORTD= 0x00;//inicializamos el puerto d en 0
	
	UCSRA = 0X00;// inicializa en 0
	UCSRB |= (1<<RXEN) | (1<<TXEN); // funciona como receptor y transmisor
	UCSRC |= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0); //URSEL registro activado, tamaño 8 bits
	UBRRL = BAUD_PRESCALE;			//PARTE ALTA DE LA VELOCIDAD DE COMUNICACIÓN
	UBRRH = (BAUD_PRESCALE >> 8);	//PARTE BAJA DE LA VELOCIDAD DE COMUNICACIÓN
	
}

//----------FUNCIONES PARA TRANSMITIR Y RECEPTAR------------------------------------------------

int Uart_write(unsigned char caracter)
{
	while (!(UCSRA & (1 << UDRE))); // si el bit 5 del registro UCSRA es 1, entonces esta disponible para enviar datos TRANSMISION
	UDR=caracter; //me recibe un char para guardarlo en el registro UDR y enviarlo TRANSMISION
}

void Uart_write_txt(char* cadena){
	while(*cadena !=0x00){
		Uart_write(*cadena);
		cadena++;
	}
}


int isUSARTerror() // funcion que me da 1 si hay un error al recibir los datos, mientras sea 0 se puede guardar los datos RECEPTOR
{
	if (((UCSRA & (1 << FE)) | (UCSRA & (1 << DOR)) | (UCSRA & (1 << PE)))) //bit de error al recibir o desbordamiento o error de paridad
	return 1;
	else
	return 0;
}

unsigned char UART_read(){ //RECEPTOR
	
	if(UCSRA &(1<<RXC)){			//si el bit7 del registro UCSRA se ha puesto a 1 (bit RXC esta en 1 cuando hay un dato en el receptor)
		return UDR;			//devuelve el dato almacenado en el registro UDR
	}
	else{
	return 0;}
}