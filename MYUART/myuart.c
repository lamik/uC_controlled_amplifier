#include "myuart.h"


void uart_init( uint16_t ubrr ) //inicjalizacja USART
{
	/* Set baud rate */
	UBRR0H = (uint8_t)(ubrr>>8);
	UBRR0L = (uint8_t)ubrr;
	/* Enable transmitter */
	UCSR0B = (1<<TXEN0);
}

void uart_putc( char data ) //wyslanie pojedynczego znaku
{
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) );
/* Put data into buffer, sends the data */
UDR0 = data;
}

void uart_puts( char * s )
{
	while( *s) uart_putc(*s++);
}

void uart_put_int(uint8_t liczba, uint8_t radix)
{
	char buf[17];
	itoa(liczba,buf,radix);
	uart_puts(buf);
}

void uart_puts_P(const char * s)
{
	register char c;
	while ((c = pgm_read_byte( s++))) uart_putc(c);
}

