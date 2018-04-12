/*
 * rtc.c
 *
 *  Created on: 29-07-2013
 *      Author: Administrator
 */


#include "rtc.h"

//zamiana liczb
uint8_t dec2bcd(uint8_t dec)
{
	return ((dec/10<<4|(dec%10)));
}
uint8_t bcd2dec(uint8_t bcd)
{
	return ((((bcd)>>4&0x0F)*10)+((bcd)&0xF));
}
//zapis godziny do zegara
void rtc_wpisz_czas(uint8_t minuty, uint8_t godziny)
{
	minuty = dec2bcd(minuty);
	godziny = dec2bcd(godziny);
	TWI_start();
	TWI_write(RTC_ADRES_ZAPIS);
	TWI_write(0x01);
	TWI_write(0);
	TWI_write(0);
	TWI_write(minuty);
	TWI_write(godziny);
	TWI_stop();
}
//odczytywanie z zegara

void rtc_odczytaj_czas(uint8_t * sekundy, uint8_t * minuty, uint8_t * godziny)
{
	TWI_start();
	TWI_write(RTC_ADRES_ZAPIS);
	TWI_write(0x02);
	TWI_start();
	TWI_write(RTC_ADRES_ODCZYT);
	*sekundy = bcd2dec(TWI_read(1));
	*minuty = bcd2dec(TWI_read(1));
	*godziny = bcd2dec(TWI_read(0));
	TWI_stop();
}

void rtc_dodajgodzine()
{
	uint8_t h_tmp;
	if(h<23)
		h_tmp = h+1;
	else h_tmp = 0;
	h_tmp = dec2bcd(h_tmp);
	TWI_start();
	TWI_write(RTC_ADRES_ZAPIS);
	TWI_write(0x04);
	TWI_write(h_tmp);
	TWI_stop();
}

void rtc_dodajminute()
{
	uint8_t min_tmp;
	if(min<59)
		min_tmp = min+1;
	else min_tmp = 0;
	min_tmp = dec2bcd(min_tmp);
	TWI_start();
	TWI_write(RTC_ADRES_ZAPIS);
	TWI_write(0x01);
	TWI_write(0);
	TWI_write(0);
	TWI_write(min_tmp);
	TWI_stop();
}


