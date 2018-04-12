/*
 * mkuart.h
 *
 *  Created on: 2010-09-04
 *       Autor: Miros³aw Kardaœ
 */

#ifndef MKUART_H_
#define MKUART_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

#define BAUD 9600		// prêdkoœæ transmisji
#define __UBRR (( F_CPU  + BAUD * 8UL  ) / (16UL * BAUD) -1) // obliczamy UBRR

void uart_init( uint16_t ubrr );

void uart_putc( char data );
void uart_puts( char * s );
void uart_put_int(uint8_t liczba, uint8_t radix);
void uart_puts_P(const char * s);

#endif /* MKUART_H_ */
