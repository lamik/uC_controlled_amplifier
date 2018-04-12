/*
 * rtc.h
 *
 *  Created on: 29-07-2013
 *      Author: Administrator
 */
#include "avr/io.h"
#include "../I2C_TWI/i2c_twi.h"

#ifndef RTC_H_
#define RTC_H_

#define RTC_ADRES_ZAPIS 0xA0
#define RTC_ADRES_ODCZYT 0xA1

uint8_t sek, min, h; //zmienne zegarowe

//uint8_t dec2bcd(uint8_t dec); //zamiana dziesietnych na bcd
//uint8_t bcd2dec(uint8_t bcd); //zamiana bcd na dziesietne

void rtc_wpisz_czas(uint8_t minuty, uint8_t godziny); //wpisanie czasu do zegarka
void rtc_odczytaj_czas(uint8_t * sekundy, uint8_t * minuty, uint8_t * godziny);
void rtc_dodajgodzine();
void rtc_dodajminute();

#endif /* RTC_H_ */
