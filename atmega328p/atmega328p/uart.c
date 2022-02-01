/*
 * uart.c
 *
 * Created: 1/02/2022 8:33:32 a. m.
 *  Author: juane
 */ 
#include <avr/io.h>
#include "UART.h"

void uart_init(){
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART Receiver: On
	// USART Transmitter: On
	// USART Mode: Asynchronous
	// USART Baud Rate: 9600
	
	DDRD |= (1 << DDD1);// 0b0010, bit 0 de entrada (RXD), bit 1 de salida (TXD)
	PORTD = 0x00;//inicializamos el puerto d en 0
	
	UCSR0A = 0X00;// inicializa en 0
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0); // funciona como receptor y transmisor
	UCSR0C |= (1<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00); //URSEL registro activado, tamaño 8 bits
	UBRR0L = BAUD_VAL;			//PARTE ALTA DE LA VELOCIDAD DE COMUNICACIÓN
	UBRR0H = (BAUD_VAL >> 8);	//PARTE BAJA DE LA VELOCIDAD DE COMUNICACIÓN
	
}

//----------FUNCIONES PARA TRANSMITIR Y RECEPTAR------------------------------------------------

int Uart_write(unsigned char caracter)
{
	while (!(UCSR0A & (1 << UDRE0))); // si el bit 5 del registro UCSRA es 1, entonces esta disponible para enviar datos TRANSMISION
	UDR0=caracter; //me recibe un char para guardarlo en el registro UDR y enviarlo TRANSMISION
	while (!(UCSR0A & (1 << TXC0)));
}

void Uart_write_txt(char* cadena){
	while(*cadena !=0x00){
		Uart_write(*cadena);
		cadena++;
	}
}


int isUSARTerror() // funcion que me da 1 si hay un error al recibir los datos, mientras sea 0 se puede guardar los datos RECEPTOR
{
	if (((UCSR0A & (1 << FE0)) | (UCSR0A & (1 << DOR0)) | (UCSR0A & (1 << UPE0)))) //bit de error al recibir o desbordamiento o error de paridad
	return 1;
	else
	return 0;
}

unsigned char UART_read(){ //RECEPTOR
	
	if(UCSR0A &(1<<RXC0)){			//si el bit7 del registro UCSRA se ha puesto a 1 (bit RXC esta en 1 cuando hay un dato en el receptor)
		return UDR0;			//devuelve el dato almacenado en el registro UDR
	}
	else{
	return 0;}
}