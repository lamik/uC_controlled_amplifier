/*
 * main.c
 *
 *  Created on: 24-07-2013
 *      Author: Mateusz Salamon
 */

//pliki zalaczeniowe
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#include "RTC/rtc.h"
#include "1Wire/ds18x20.h"
#include "SELEKTOR/selektor.h"
#include "MYUART/myuart.h"
#include "TERMINAL/term.h"
#include "Przyciskimenu/menu.h"
#include "TDA7318/tda7318.h"
#include "IR_DECODE/ir_decode.h"

#define LED (1<<PB7)

//zmienne globalne

uint8_t czujniki_cnt;  //liczba czujnikow
TCFG ustawienia EEMEM;
volatile uint8_t Timer1, Timer2, Timer3, Timer4; // Timery programowe
//znaki LCD
const uint8_t celsiusz[] PROGMEM = {0x1C, 0x14, 0x1C, 0x00, 0x07, 0x04, 0x04, 0x07}; //stopnie celsjusza
const uint8_t strzalka_gora[] PROGMEM = {0x04, 0x0E, 0x15, 0x04, 0x04, 0x04, 0x04, 0x04}; //strzaleczka podkreslenia
const uint8_t strzalka_dol[] PROGMEM = {0x04, 0x04, 0x04, 0x04, 0x04, 0x15, 0x0E, 0x04}; //w dol
const uint8_t nuta[] PROGMEM = {0x06, 0x05, 0x06, 0x05, 0x04, 0x1C, 0x1C, 0x18}; // nutka sygnalizacji zalaczenia wejscia

//deklaracje funkcji
void display_temp_uart(uint8_t cel, uint8_t cel_fract_bits); //odczyt temperatury i wyrzucenie na terminal
void display_time_uart(uint8_t sekundy, uint8_t minuty, uint8_t godziny ); //wyswuetlenie czasu

//petla main
int main(void)
{
	//inicjalizacja portow
	DDRA = 0b00011111;
	DDRB = 0b10000000;
	DDRC = 0b00111100;
	DDRD = 0b10111000;

	PORTA = 0b11100000;
//	PORTB = 0b00000000;
	PORTC = 0b11000000;
	PORTD = 0b00000100;


	//inicjalizacja uart
	uart_init( __UBRR);
	i2cSetBitrate(100);
	ir_init();
	lcd_init();


	//inicjalizacja timer0 - przerwanie co 4ms
		TCCR0A |= (1<<WGM01); //CTC
		TCCR0B |= (1<<CS02)|(1<<CS00); //preskaler 1024
		OCR0A = 155; //co 10ms
		TIMSK0 |= (1<<OCIE0A);

	//przerwanie INT0
	EIMSK |= (1<<INT0);
	SMCR |= (1<<SM1);

		//pomiar temperatury
		czujniki_cnt = search_sensors();
		DS18X20_start_meas(DS18X20_POWER_EXTERN, NULL);

		uart_puts("Termometr");
//		lcd_str("Wzmacniacz by");
//		lcd_locate(1,1);
//		lcd_str("Lamik");

		lcd_defchar_P(0x80,celsiusz);
		lcd_defchar_P(0x81,strzalka_gora);
		lcd_defchar_P(0x82,strzalka_dol);
		lcd_defchar_P(0x83,nuta);


		out_lf=1;
		sleep_disable();
		wlaczanie();
		lcd_cls();
	sei(); //zezwolenie na przerwanie
	//petla glowna programu
	while(1)
	{

		if(!Timer1)
		{
			menu();
			Timer1 = 1;
		}
		//zdarzenie co 100ms
		if(!Timer2)
		{

			tr_cls(1);
			rtc_odczytaj_czas(&sek,&min,&h);

//			display_temp_uart(cel,cel_fract_bits); //wyswietlenie temperatury
//			display_time_uart(sek,min,h);
//			uart_puts(" \r\n Volume: ");
//			uart_put_int(volume,10);
//			uart_puts(" \r\n Bass: ");
//			uart_put_int(bass,10);
//			uart_puts(" \r\n Treble: ");
//			uart_put_int(treble,10);
//			uart_puts(" \r\n LF: ");
//			uart_put_int(att_lf,10);
//			uart_puts(" \r\n RF: ");
//			uart_put_int(att_rf,10);
//			uart_puts(" \r\n LR: ");
//			uart_put_int(att_lr,10);
//			uart_puts(" \r\n RR: ");
//			uart_put_int(att_rr,10);
//			uart_puts(" \r\n Audio switch: ");
//			uart_put_int(audio_switch,10);
//			uart_puts(" \r\n Lewy przod: ");
//			uart_put_int(out_lf,10);
//			uart_puts(" \r\n Prawy przod: ");
//			uart_put_int(out_rf,10);
//			uart_puts(" \r\n Lewy tyl: ");
//			uart_put_int(out_lr,10);
//			uart_puts(" \r\n Prawy tyl: ");
//			uart_put_int(out_rr,10);
//			uart_puts(" \r\n Wyjscie: ");
//			uart_put_int(wyjscie,10);
//
//
//
//							uart_puts(" \r\n Adres pilota: ");
//							uart_put_int(address,10);
//							uart_puts(" \r\n Komenda klawisza: ");
//							uart_put_int(command,10);
//						Ir_key_press_flag=0;
//						command=0xff;
//						address=0xff;

			Timer2 = 10;
		}

		//zdarzenie co 1s
		if(!Timer3)
		{
			//odebranie temperatury i ponmowny pomiar
			DS18X20_read_meas(gSensorIDs[0],&subzero,&cel,&cel_fract_bits);
			DS18X20_start_meas(DS18X20_POWER_EXTERN, NULL);

			//odczyt z RTC
			PORTB ^= LED; //debug led

			Timer3 = 100; //wyzerowanie flagi
		}
	}
}

void display_temp_uart(uint8_t cel, uint8_t cel_fract_bits)
{
	uart_puts("Temperatura: ");
	uart_put_int(cel,10);
	uart_putc('.');
	uart_put_int(cel_fract_bits,10);
	uart_puts(" *C \r\n");
}

void display_time_uart(uint8_t sekundy, uint8_t minuty, uint8_t godziny )
{
	uart_puts("\r\n");
	if(godziny<10)
		{
			uart_putc('0');
			uart_put_int(godziny,10);
		}
		else
	uart_put_int(godziny,10);
	uart_putc(':');
	if(minuty<10)
		{
			uart_putc('0');
			uart_put_int(minuty,10);
		}
		else
	uart_put_int(minuty,10);
	uart_putc(':');
	if(sekundy<10)
	{
		uart_putc('0');
		uart_put_int(sekundy,10);
	}
	else
	uart_put_int(sekundy,10);
	uart_puts("\r\n");
}

//Timer0 do obslugi timerow programowych
ISR(TIMER0_COMPA_vect)
{
	//przerwanie co 10ms
	uint16_t n;

//	Timery do obslugi SCR
	n = Timer1;		/* 100Hz Timer1 */
	if (n) Timer1 = --n;
	n = Timer2;		/* 100Hz Timer2 */
	if (n) Timer2 = --n;
	n = Timer3;		/* 100Hz Timer2 */
	if (n) Timer3 = --n;
	n = TimerDebounce;
	if (n) TimerDebounce = --n;
	n = TimerIR;
	if (n) TimerIR = --n;
}

ISR(INT0_vect)
{
	if(off==1)
	{
		sleep_disable();
		wlaczanie();
	}
	else wylaczenie();
}


