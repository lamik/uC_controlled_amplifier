/*
 * menu.h
 *
 *  Created on: 09-08-2013
 *      Author: Administrator
 */

#ifndef MENU_H_
#define MENU_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "../LCD/lcd44780.h"
#include "../1Wire/ds18x20.h"
#include "../TDA7318/tda7318.h"
#include "../RTC/rtc.h"
#include "../SELEKTOR/selektor.h"
#include "../IR_DECODE/ir_decode.h"

#define IR_TIME 50
#define  KEY_DOWN (1<<PA5)
#define  KEY_UP (1<<PA6)
#define  KEY_SEL (1<<PA7)
#define  KEY_MENU (1<<PC7)
#define  KEY_MUTE (1<<PC6)
#define WLACZNIK (1<<PD2)
#define LED_ON (1<<PD4)
#define LED_OFF (1<<PD5)
#define ZALACZANIE (1<<PD3)

volatile uint8_t TimerIR;
volatile uint8_t TimerDebounce;
volatile uint8_t TimerMenu;
typedef struct
{
	uint8_t pusty;
	uint8_t pusty2;
	uint8_t glosnosc;
	uint8_t lf;
	uint8_t rf;
	uint8_t lr;
	uint8_t rr;
	uint8_t switch_gain;
	uint8_t bass;
	uint8_t treble;
	uint8_t olf;
	uint8_t orf;
	uint8_t olr;
	uint8_t orr;
	uint8_t wyjscie;
}TCFG;

extern TCFG ustawienia EEMEM; //ustawienia wzmacniacza trzymane w eeprom


uint8_t k1, k2, k3, k4, k5, k6; //zmienne ram dla przyciskow
uint8_t subzero, cel, cel_fract_bits;	//zmienne temperaturowe
volatile uint8_t off;

//zmienne menu
uint8_t menu_nr; //numer ekranu na wyswietlacznu



void SuperDebounce(uint8_t * key_state, volatile uint8_t *KPIN,
		uint8_t key_mask, uint16_t rep_time, uint16_t rep_wait,
		void (*push_proc)(void), void (*rep_proc)(void) );
void menu_nastepne(void);

void ekran_0();
void ekran_bass();
void ekran_treble();
void ekran_fl();
void ekran_fr();
void ekran_rl();
void ekran_rr();
void ekran_zegar();
void ekran_outputs();
void ekran_inputgain();
void menu(); //funkcja calego menu
void mute(void);
void potwierdzenie(void);

void wylaczenie(); //funkcja zapisujaca ustawienia do eeprom i wylaczajaca wzmacniacz
void wlaczanie(); //wlaczenie wzmacniacza i przywrocenie ustawien sprzed wylaczenia



#endif /* MENU_H_ */
