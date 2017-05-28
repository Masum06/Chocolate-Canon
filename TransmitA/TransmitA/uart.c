#include <avr/io.h>
#include <stdio.h>

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

void UART_init(){
	// Normal speed, disable multi-proc
	UCSRA = 0b00000010;
	// Enable Tx and Rx, disable interrupts
	UCSRB = 0b00011000;
	// Asynchronous mode, no parity, 1 stop bit, 8 data bits
	UCSRC = 0b10000110;
	// Baud rate 1200bps, assuming 1MHz clock
	UBRRL = 12;//0x33;
	UBRRH = 0x00;
}

void UART_send(unsigned char data){
	// wait until UDRE flag is set to logic 1
	while ((UCSRA & (1<<UDRE)) == 0x00);
	UDR = data; // Write character to UDR for transmission
}

unsigned char UART_receive(void){
	// Wait until RXC flag is set to logic 1
	while ((UCSRA & (1<<RXC)) == 0x00);
	return UDR; // Read the received character from UDR
}

static int
uart_putchar(char c, FILE *stream)
{
	if (c == '\n')
	uart_putchar('\r', stream);
	while ((UCSRA & (1<<UDRE)) == 0x00);
	UDR = c;
	return 0;
}

