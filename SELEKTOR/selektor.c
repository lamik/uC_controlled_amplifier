/*
 * selektor.c
 *
 *  Created on: 24-07-2013
 *      Author: Mateusz Salamon
 */

#include "selektor.h"
#include <util/delay.h>



void selektor_ustaw_wyj(uint8_t wyj) //ustawienie aktywnego wyjscia
{
	_PORT &= WSZYSTKIE_OFF; //wyzerowanie wyjsc
	_delay_ms(1);
	_PORT |= (1<<wyj); //ustawienie wybranego wyjscia
}

void selektor_nastepne() //przelaczenie wyjscia na kolejne
{
	if(wyjscie<(IL_WYJSC-1)) //zmienna wyboru kolejnego wejscia
	{
		wyjscie+=1;
	} else wyjscie=WYJ1;

	_PORT &= WSZYSTKIE_OFF; //wyzerowanie wyjsc
	_delay_ms(1);
	_PORT |= (1<<wyjscie); //ustawienie kolejnego wyjscia
}

