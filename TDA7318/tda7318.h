/*
 * tda7318.h
 *
 *  Created on: 15-08-2013
 *      Author: Administrator
 */

#ifndef TDA7318_H_
#define TDA7318_H_

#include <avr/io.h>
#include <avr/eeprom.h>

#include "../I2C_TWI/i2c_twi.h"

#define TDA7318_ADR 0x88 //adres przedwzmacniacza
#define LF_OUT (1<<PC5) //wyjscia glosnikowe "1" zalacza, "0" rozlacza
#define RF_OUT (1<<PC4)
#define LR_OUT (1<<PC3)
#define RR_OUT (1<<PC2)

//zmienne
uint8_t volume; //glosnosc
uint8_t att_lf, att_rf, att_lr, att_rr; //wzmocnienia glosnikowe - lewy przod, prawy przod, lewy tyl, prawy tyl
uint8_t audio_switch; //przelacznik audio + wzmocnienei wejscia
uint8_t bass, treble; //ustawienia tonow niskich i wysokich
uint8_t wycisz; //flaga wyciszenia
uint8_t out_lf;
uint8_t out_rf, out_lr, out_rr; //wyjscia glosnikowe
uint8_t outputs; // numer konfiguracji wyjsc


void preamp_vol_plus(void); //zglasnianie
void preamp_vol_minus(void); //sciszanie

void preamp_attlf_plus(void); //wzmocnienia poszczegolnych wyjsc
void preamp_attlf_minus(void);
void preamp_attrf_plus(void);
void preamp_attrf_minus(void);
void preamp_attlr_plus(void);
void preamp_attlr_minus(void);
void preamp_attrr_plus(void);
void preamp_attrr_minus(void);

void preamp_switchgain_plus(void);  //wzmocnienie wejscia
void preamp_switchgain_minus(void);

void preamp_bass_plus(void); //tony
void preamp_bass_minus(void);
void preamp_treble_plus(void);
void preamp_treble_minus(void);

void preamp_select_outputs();

#endif /* TDA7318_H_ */
