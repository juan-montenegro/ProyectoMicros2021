/*
 * uart.h
 *
 * Created: 1/02/2022 8:03:43 a. m.
 *  Author: juane
 */ 


#ifndef UART_H_
#define UART_H_

void uART_init(unsigned int ubrr); // iniciar UART

//----------FUNCIONES PARA TRANSMITIR Y RECEPTAR------------------------------------------------

int iUART_error(); // funcion que me da 1 si hay un error al recibir los datos, mientras sea 0 se puede guardar los datos RECEPTOR
unsigned char UART_get(); //RECEPTOR
void UART_String(char* cadena);//transmitir
void UART_Char(unsigned char caracter);//transmitir

#endif /* UART_H_ */