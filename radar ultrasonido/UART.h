

				
void uart_init(long USART_BAUDRATE); // iniciar UART

//----------FUNCIONES PARA TRANSMITIR Y RECEPTAR------------------------------------------------

int isUSARTerror(); // funcion que me da 1 si hay un error al recibir los datos, mientras sea 0 se puede guardar los datos RECEPTOR
unsigned char UART_read(); //RECEPTOR

void Uart_write_txt(char* cadena);//transmitir
int Uart_write(unsigned char caracter);//transmitir