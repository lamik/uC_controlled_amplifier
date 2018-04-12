/*
 * ir_decode.h
 *
 *  Created on: 2010-09-13
 *       Autor: Miros³aw Kardaœ
 */

#ifndef IR_DECODE_H_
#define IR_DECODE_H_

#include "../common.h"

#define IR_PORT D
#define IR_PIN 6
#define IR_IN (1<<IR_PIN)

// sta³e i zmienne potrzebne na wewnêtrzne cele procedury obs³ugi RC5

#define TIMER1_PRESCALER 8

// przeliczanie tykniêæ Timera1 przy danym preskalerze na mikrosekundy
#define ir_micro_s(num) ((num)*(F_CPU/1000000)/TIMER1_PRESCALER)

// sta³e czasowa i tolerancja wyra¿one w us
#define TOLERANCE 200
#define MIN_HALF_BIT 	ir_micro_s(889	- TOLERANCE)
#define MAX_HALF_BIT 	ir_micro_s(889 + TOLERANCE)
#define MAX_BIT ir_micro_s((889+889) + TOLERANCE)


// ------------------------------------------- definicje klawiszy PILOTA IR
#define IR_UP 16
#define IR_DOWN 17
#define IR_SEL 4
#define IR_MENU 5
#define IR_MUTE 6
#define IR_ONOFF 42
// ------------------------------------------- definicje klawiszy KONIEC

// zmienne charakterystyczne tylko dla obs³ugi RC5
extern volatile uint8_t toggle_bit;		// bit TOGGLE
extern volatile uint8_t address;		// adres
extern volatile uint8_t command;		// komenda

// flaga = 1 - informuje, ¿e odebrany zosta³ nowy kod z pilota
extern volatile uint8_t Ir_key_press_flag;

// deklaracje funkcji dla u¿ytkownika
void ir_init();


#endif /* IR_DECODE_H_ */
