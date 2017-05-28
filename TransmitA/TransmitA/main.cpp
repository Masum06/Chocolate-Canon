#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "uart.c"

int main(void)
{
	DDRD = 0xFF;
	unsigned char i;
	UART_init(); // initialise UART
	stdout = fdevopen(uart_putchar, NULL);
	while (1) {
		UART_send(i); //To send a character
		printf("AT+ROLE=1\r\n"); //Directly printf through uart
		unsigned char c = UART_receive();
		if (c == 'O' || c=='K')
		{
			PORTD = 0xFF;
			_delay_ms(2000);
		}
		PORTD = 0;
		_delay_ms(100);
		i++;
	}
}
