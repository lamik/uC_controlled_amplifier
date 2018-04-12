/*
 * selektor.h
 *
 *  Created on: 24-07-2013
 *      Author: Mateusz Salamon
 */

#ifndef SELEKTOR_H_
#define SELEKTOR_H_

#define IL_WYJSC 5
#define _PORT PORTA
#define WYJ1 PA0
#define WYJ2 PA1
#define WYJ3 PA2
#define WYJ4 PA3
#define WYJ5 PA4
#define WSZYSTKIE_OFF ~((1<<WYJ1)|(1<<WYJ2)|(1<<WYJ3)|(1<<WYJ4)|(1<<WYJ5))


#include <avr/io.h>

uint8_t wyjscie; //aktywne wyjscie wzmacniacza

void selektor_ustaw_wyj(uint8_t wyj);
void selektor_nastepne(void);


#endif /* SELEKTOR_H_ */
