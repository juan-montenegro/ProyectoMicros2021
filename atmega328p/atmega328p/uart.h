/*
 * uart.h
 *
 * Created: 1/02/2022 8:03:43 a. m.
 *  Author: juane
 */ 


#ifndef UART_H_
#define UART_H_

#define FOSC		8000000
#define BAUD		9600
#define BAUD_VAL	FOSC/8/BAUD-1

void uart_init(unsigned int MYUBRR); // iniciar UART

//----------FUNCIONES PARA TRANSMITIR Y RECEPTAR------------------------------------------------

int isUSARTerror(); // funcion que me da 1 si hay un error al recibir los datos, mientras sea 0 se puede guardar los datos RECEPTOR
unsigned char UART_read(); //RECEPTOR

void Uart_write_txt(char* cadena);//transmitir
int Uart_write(unsigned char caracter);//transmitir

#endif /* UART_H_ */