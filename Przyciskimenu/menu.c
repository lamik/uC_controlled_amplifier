/*
 * menu.c
 *
 *  Created on: 09-08-2013
 *      Author: Administrator
 */

#include "menu.h"

//Obsluga przycisku
void SuperDebounce(uint8_t * key_state, volatile uint8_t *KPIN,
		uint8_t key_mask, uint16_t rep_time, uint16_t rep_wait,
		void (*push_proc)(void), void (*rep_proc)(void) ) {

	enum {idle, debounce, go_rep, wait_rep, rep};

	if(!rep_time) rep_time=20;
	if(!rep_wait) rep_wait=150;

	uint8_t key_press = !(*KPIN & key_mask);

	if( key_press && !*key_state ) {
		*key_state = debounce;
		TimerDebounce = 15;
	} else
	if( *key_state  ) {

		if( key_press && debounce==*key_state && !TimerDebounce ) {
			*key_state = 2;
			TimerDebounce=5;
		} else
		if( !key_press && *key_state>1 && *key_state<4 ) {
			if(push_proc) push_proc();						/* KEY_UP */
			*key_state=idle;
		} else
		if( key_press && go_rep==*key_state && !TimerDebounce ) {
			*key_state = wait_rep;
			TimerDebounce=rep_wait;
		} else
		if( key_press && wait_rep==*key_state && !TimerDebounce ) {
			*key_state = rep;
		} else
		if( key_press && rep==*key_state && !TimerDebounce ) {
			TimerDebounce = rep_time;
			if(rep_proc) rep_proc();						/* KEY_REP */
		}
	}
	if( *key_state>=3 && !key_press ) *key_state = idle;
}

void potwierdzenie()
{
	menu_nr = 0;
}

void menu_nastepne()
{
	if(menu_nr < 9)
	menu_nr++;
	else menu_nr = 0;
}
void mute(void)
{
	//wylaczenie wszystkich wyjsc
	wycisz = !wycisz;
	if(!wycisz)
	{
		if(!out_lf) PORTC |= LF_OUT;
		if(!out_rf) PORTC |= RF_OUT;
		if(!out_lr) PORTC |= LR_OUT;
		if(!out_rr) PORTC |= RR_OUT;
	}
	else
	PORTC &= ~(LF_OUT|RF_OUT|LR_OUT|RR_OUT);
}

void wylaczenie()
{
	//przepisanie ustawien do eepromu
	if(volume > 30)
	ustawienia.glosnosc = volume;
	else ustawienia.glosnosc = 30;
	ustawienia.bass = bass;
	ustawienia.treble = treble;
	ustawienia.switch_gain = audio_switch;
	ustawienia.wyjscie = wyjscie;
	ustawienia.lf = att_lf;
	ustawienia.rf = att_rf;
	ustawienia.lr = att_lr;
	ustawienia.rr = att_rr;
	ustawienia.olf = out_lf;
	ustawienia.orf = out_rf;
	ustawienia.olr = out_lr;
	ustawienia.orr = out_rr;

	PORTC &=~(LF_OUT|RF_OUT|LR_OUT|RR_OUT);
	PORTD |= (LED_OFF);
	PORTD &= ~(LED_ON|ZALACZANIE);
	PORTA &= ~((1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4));
	for(int i = 0; i<15;i++)
	{
		lcd_cls();
		lcd_locate(0,(15-i));
		lcd_str("GOODBYE");
		_delay_ms(200);
	}
	_delay_ms(1000);
	lcd_cls();
	off = 1;
	sleep_enable();
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sei();
	sleep_cpu();
}

void wlaczanie()
{
	uint8_t tmp_b, tmp_t;
	//przepisanie ustawien do eepromu
	PORTD |= LED_ON;

		volume = ustawienia.glosnosc;
		bass = ustawienia.bass;
		treble = ustawienia.treble;
		audio_switch = ustawienia.switch_gain;
		wyjscie = ustawienia.wyjscie;
		att_lf = ustawienia.lf;
		att_rf = ustawienia.rf;
		att_lr = ustawienia.lr;
		att_rr = ustawienia.rr;
		out_lf = ustawienia.olf;
		out_rf = ustawienia.orf;
		out_lr = ustawienia.olr;
		out_rr = ustawienia.orr;
		switch (bass)
				{
				case 0: tmp_b = 0b00000000; //-14dB
								break;
				case 1: tmp_b = 0b00000001; //-12dB
								break;
				case 2: tmp_b = 0b00000010; //-10dB
								break;
				case 3: tmp_b = 0b00000011; //-8dB
								break;
				case 4: tmp_b = 0b00000100; //-6dB
								break;
				case 5: tmp_b = 0b00000101; //-4dB
								break;
				case 6: tmp_b = 0b00000110; //-2dB
								break;
				case 7: tmp_b = 0b00000111; //0dB
								break;
				case 8: tmp_b = 0b00001110; //2dB
								break;
				case 9: tmp_b = 0b00001101; //4dB
								break;
				case 10: tmp_b = 0b00001100; //6dB
								break;
				case 11: tmp_b = 0b00001011; //8dB
								break;
				case 12: tmp_b = 0b00001010; //10dB
								break;
				case 13: tmp_b = 0b00001001; //12dB
								break;
				case 14: tmp_b = 0b00001000; //14dB
								break;
				default: tmp_b = 0b00000111; //0dB
								break;
				}
		switch (treble)
		{
		case 0: tmp_t = 0b00000000; //-14dB
						break;
		case 1: tmp_t = 0b00000001; //-12dB
						break;
		case 2: tmp_t = 0b00000010; //-10dB
						break;
		case 3: tmp_t = 0b00000011; //-8dB
						break;
		case 4: tmp_t = 0b00000100; //-6dB
						break;
		case 5: tmp_t = 0b00000101; //-4dB
						break;
		case 6: tmp_t = 0b00000110; //-2dB
						break;
		case 7: tmp_t = 0b00000111; //0dB
						break;
		case 8: tmp_t = 0b00001110; //2dB
						break;
		case 9: tmp_t = 0b00001101; //4dB
						break;
		case 10: tmp_t = 0b00001100; //6dB
						break;
		case 11: tmp_t = 0b00001011; //8dB
						break;
		case 12: tmp_t = 0b00001010; //10dB
						break;
		case 13: tmp_t = 0b00001001; //12dB
						break;
		case 14: tmp_t = 0b00001000; //14dB
						break;
		default: tmp_t = 0b00000111; //0dB
						break;
		}

		//wyslanie wszystkiego do tda
		TWI_start();
		TWI_write(0b00000000 | volume);
		TWI_write(0b10000000 | att_lf);
		TWI_write(0b10100000 | att_rf);
		TWI_write(0b11000000 | att_lr);
		TWI_write(0b11100000 | att_rr);
		TWI_write(0b01000000 | (audio_switch<<3));
		TWI_write(0b01100000 | tmp_b);
		TWI_write(0b01110000 | tmp_t);
		TWI_stop();

		if(!out_lf) PORTC |= LF_OUT;
		if(!out_rf) PORTC |= RF_OUT;
		if(!out_lr) PORTC |= LR_OUT;
		if(!out_rr) PORTC |= RR_OUT;

		PORTD |= ZALACZANIE;

		for(int i = 0; i<15;i++)
			{
				lcd_cls();
				lcd_locate(0,(15-i));
				lcd_str("HELLO");
				_delay_ms(200);
			}		_delay_ms(2000);

		selektor_ustaw_wyj(wyjscie);
		menu_nr = 0;
		PORTD |= LED_ON;
		PORTD &= ~LED_OFF;
		off = 0;
}
void ekran_0()
{
	lcd_cls();
	lcd_int(cel); //wyswietlenie temperatury
	lcd_str("\x80""  "); //znak celsjusza
	switch (wyjscie)  //wyjswietlenie atywnego wyjscia
	{
		case 0:
				lcd_str(" CD   ");
			break;
		case 1:
				lcd_str(" PC   ");
			break;
		case 2:
				lcd_str("DVR   ");
			break;
		case 3:
				lcd_str("TAPE  ");
			break;
		case 4:
				lcd_str(" AUX  ");
			break;
	}
	//wyswietlenie godziny
	if(h<10)
			{
				lcd_char('0');
				lcd_int(h);
			}
			else
				lcd_int(h);
				lcd_char(':');
		if(min<10)
			{
			lcd_char('0');
			lcd_int(min);
			}
			else
				lcd_int(min);
	//druga linia
	lcd_locate(1,0);
	if(!wycisz)
	{
	lcd_str("VOLUME:-");
	lcd_int((volume*125)/100);
	lcd_char('.');
	lcd_int((volume*125)%100);
	lcd_locate(1,13);
	lcd_str("dB");
	}
	else
	lcd_str("      MUTE      ");

	SuperDebounce(&k1, &PINA, KEY_DOWN, 4, 4, preamp_vol_minus, preamp_vol_minus); //glosnosc
	SuperDebounce(&k2, &PINA, KEY_UP, 4, 4, preamp_vol_plus, preamp_vol_plus);
	SuperDebounce(&k3, &PINA, KEY_SEL, 4, 4, selektor_nastepne, NULL);
	SuperDebounce(&k4, &PINC, KEY_MENU, 4, 4, menu_nastepne, NULL);
	SuperDebounce(&k5, &PINC, KEY_MUTE, 4, 4, mute, NULL);
//	SuperDebounce(&k6, &PIND, WLACZNIK, 4, 4, wylaczenie, NULL);

	if(Ir_key_press_flag)
	{
		Ir_key_press_flag = 0;
		if(address == 10 && command == IR_UP)
		{
			preamp_vol_plus();
			TimerIR = IR_TIME/2;
		}
		if(address == 10 && command == IR_DOWN)
		{
			preamp_vol_minus();
			TimerIR = IR_TIME/2;
		}
		if(!TimerIR)
		{
		if(address == 10 && command == IR_SEL)
		{
			selektor_nastepne();
			TimerIR = IR_TIME;
		}
		if(address == 10 && command == IR_MENU)
		{
			menu_nastepne();
			TimerIR = IR_TIME;
		}
		if(address == 10 && command == IR_MUTE)
		{
			mute();
			TimerIR = IR_TIME;
		}
		if(address == 10 && command == IR_ONOFF)
		{
			wylaczenie();
		}
		}
		command=0xff;
		address=0xff;
	}
}

void ekran_bass()
{
	lcd_cls();
	lcd_str("      BASS      ");
	lcd_locate(1,0);
	lcd_str("--------------- ");
	lcd_locate(1,bass);
	lcd_char('+');
	SuperDebounce(&k1, &PINA, KEY_DOWN, 4, 4, preamp_bass_minus, NULL);
	SuperDebounce(&k2, &PINA, KEY_UP, 4, 4, preamp_bass_plus, NULL);
	SuperDebounce(&k4, &PINC, KEY_MENU, 4, 4, menu_nastepne, NULL);
	SuperDebounce(&k5, &PINC, KEY_MUTE, 4, 4, potwierdzenie, NULL);
	SuperDebounce(&k6, &PIND, WLACZNIK, 4, 4, wylaczenie, NULL);

	if(Ir_key_press_flag)
	{
		if(address == 10 && command == IR_UP)
		{
			preamp_bass_plus();
			TimerIR = IR_TIME;
		}
		if(address == 10 && command == IR_DOWN)
		{
			preamp_bass_minus();
			TimerIR = IR_TIME;
		}
		if(address == 10 && command == IR_MENU)
		{
			menu_nastepne();
			TimerIR = IR_TIME;
		}
		if(address == 10 && command == IR_MUTE)
		{
			potwierdzenie();
			TimerIR = IR_TIME;
		}
		if(address == 10 && command == IR_ONOFF)
		{
			wylaczenie();
			TimerIR = IR_TIME;
		}
	Ir_key_press_flag = 0;
	command=0xff;
	address=0xff;
	}
}

void ekran_treble()
{
	lcd_cls();
	lcd_str("     TREBLE     ");
	lcd_locate(1,0);
	lcd_str("--------------- ");
	lcd_locate(1,treble);
	lcd_char('+');
	SuperDebounce(&k1, &PINA, KEY_DOWN, 4, 4, preamp_treble_minus, NULL);
	SuperDebounce(&k2, &PINA, KEY_UP, 4, 4, preamp_treble_plus, NULL);
	SuperDebounce(&k4, &PINC, KEY_MENU, 4, 4, menu_nastepne, NULL);
	SuperDebounce(&k5, &PINC, KEY_MUTE, 4, 4, potwierdzenie, NULL);
	SuperDebounce(&k6, &PIND, WLACZNIK, 4, 4, wylaczenie, NULL);

	if(Ir_key_press_flag)
	{
		if(address == 10 && command == IR_UP)
		{
			preamp_treble_plus();
			TimerIR = IR_TIME;
		}
		if(address == 10 && command == IR_DOWN)
		{
			preamp_treble_minus();
			TimerIR = IR_TIME;
		}
		if(address == 10 && command == IR_MENU)
		{
			menu_nastepne();
			TimerIR = IR_TIME;
		}
		if(address == 10 && command == IR_MUTE)
		{
			potwierdzenie();
			TimerIR = IR_TIME;
		}
		if(address == 10 && command == IR_ONOFF)
		{
			wylaczenie();
		}
	Ir_key_press_flag = 0;
	command=0xff;
	address=0xff;
	}
}

void ekran_fl()
{
	lcd_cls();
	lcd_str("   FRONT LEFT   ");
	lcd_locate(1,0);
	lcd_str(" ATT: -");
	lcd_int((att_lf*125)/100);
	lcd_char('.');
	lcd_int((att_lf*125)%100);
	lcd_locate(1,12);
	lcd_str("dB");
	SuperDebounce(&k1, &PINA, KEY_DOWN, 4, 4, preamp_attlf_minus, NULL);
	SuperDebounce(&k2, &PINA, KEY_UP, 4, 4, preamp_attlf_plus, NULL);
	SuperDebounce(&k4, &PINC, KEY_MENU, 4, 4, menu_nastepne, NULL);
	SuperDebounce(&k5, &PINC, KEY_MUTE, 4, 4, potwierdzenie, NULL);
	SuperDebounce(&k6, &PIND, WLACZNIK, 4, 4, wylaczenie, NULL);

	if(Ir_key_press_flag)
	{
		if(address == 10 && command == IR_UP)
		{
			preamp_attlf_plus();
		}
		if(address == 10 && command == IR_DOWN)
		{
			preamp_attlf_minus();
		}
		if(address == 10 && command == IR_MENU)
		{
			menu_nastepne();
		}
		if(address == 10 && command == IR_MUTE)
		{
			potwierdzenie();
		}
		if(address == 10 && command == IR_ONOFF)
		{
			wylaczenie();
		}
	Ir_key_press_flag = 0;
	command=0xff;
	address=0xff;
	TimerIR = IR_TIME;
	}
}

void ekran_fr()
{
	lcd_cls();
	lcd_str("   FRONT RIGHT  ");
	lcd_locate(1,0);
	lcd_str(" ATT: -");
	lcd_int((att_rf*125)/100);
	lcd_char('.');
	lcd_int((att_rf*125)%100);
	lcd_locate(1,12);
	lcd_str("dB");
	SuperDebounce(&k1, &PINA, KEY_DOWN, 4, 4, preamp_attrf_minus, NULL);
	SuperDebounce(&k2, &PINA, KEY_UP, 4, 4, preamp_attrf_plus, NULL);
	SuperDebounce(&k4, &PINC, KEY_MENU, 4, 4, menu_nastepne, NULL);
	SuperDebounce(&k5, &PINC, KEY_MUTE, 4, 4, potwierdzenie, NULL);
	SuperDebounce(&k6, &PIND, WLACZNIK, 4, 4, wylaczenie, NULL);

	if(Ir_key_press_flag)
	{
		if(address == 10 && command == IR_UP)
		{
			preamp_attrf_plus();
		}
		if(address == 10 && command == IR_DOWN)
		{
			preamp_attrf_minus();
		}
		if(address == 10 && command == IR_MENU)
		{
			menu_nastepne();
		}
		if(address == 10 && command == IR_MUTE)
		{
			potwierdzenie();
		}
		if(address == 10 && command == IR_ONOFF)
		{
			wylaczenie();
		}
	Ir_key_press_flag = 0;
	command=0xff;
	address=0xff;
	TimerIR = IR_TIME;
	}
}

void ekran_rl()
{
	lcd_cls();
	lcd_str("   REAR LEFT   ");
	lcd_locate(1,0);
	lcd_str(" ATT: -");
	lcd_int((att_lr*125)/100);
	lcd_char('.');
	lcd_int((att_lr*125)%100);
	lcd_locate(1,12);
	lcd_str("dB");
	SuperDebounce(&k1, &PINA, KEY_DOWN, 4, 4, preamp_attlr_minus, NULL);
	SuperDebounce(&k2, &PINA, KEY_UP, 4, 4, preamp_attlr_plus, NULL);
	SuperDebounce(&k4, &PINC, KEY_MENU, 4, 4, menu_nastepne, NULL);
	SuperDebounce(&k5, &PINC, KEY_MUTE, 4, 4, potwierdzenie, NULL);
	SuperDebounce(&k6, &PIND, WLACZNIK, 4, 4, wylaczenie, NULL);

	if(Ir_key_press_flag)
	{
		if(address == 10 && command == IR_UP)
		{
			preamp_attlr_plus();
		}
		if(address == 10 && command == IR_DOWN)
		{
			preamp_attlr_minus();
		}
		if(address == 10 && command == IR_MENU)
		{
			menu_nastepne();
		}
		if(address == 10 && command == IR_MUTE)
		{
			potwierdzenie();
		}
		if(address == 10 && command == IR_ONOFF)
		{
			wylaczenie();
		}
	Ir_key_press_flag = 0;
	command=0xff;
	address=0xff;
	TimerIR = IR_TIME;
	}
}

void ekran_rr()
{
	lcd_cls();
	lcd_str("   REAR RIGHT  ");
	lcd_locate(1,0);
	lcd_str(" ATT: -");
	lcd_int((att_rr*125)/100);
	lcd_char('.');
	lcd_int((att_rr*125)%100);
	lcd_locate(1,12);
	lcd_str("dB");
	SuperDebounce(&k1, &PINA, KEY_DOWN, 4, 4, preamp_attrr_minus, NULL);
	SuperDebounce(&k2, &PINA, KEY_UP, 4, 4, preamp_attrr_plus, NULL);
	SuperDebounce(&k4, &PINC, KEY_MENU, 4, 4, menu_nastepne, NULL);
	SuperDebounce(&k5, &PINC, KEY_MUTE, 4, 4, potwierdzenie, NULL);
	SuperDebounce(&k6, &PIND, WLACZNIK, 4, 4, wylaczenie, NULL);

	if(Ir_key_press_flag)
	{
		if(address == 10 && command == IR_UP)
		{
			preamp_attrr_plus();
		}
		if(address == 10 && command == IR_DOWN)
		{
			preamp_attrr_minus();
		}
		if(address == 10 && command == IR_MENU)
		{
			menu_nastepne();
		}
		if(address == 10 && command == IR_MUTE)
		{
			potwierdzenie();
		}
		if(address == 10 && command == IR_ONOFF)
		{
			wylaczenie();
		}
	Ir_key_press_flag = 0;
	command=0xff;
	address=0xff;
	TimerIR = IR_TIME;
	}
}

void ekran_zegar()
{
	lcd_cls();
	lcd_str("CLOCK");
	lcd_locate(0,8);
	if(h<10)
				{
					lcd_char('0');
					lcd_int(h);
				}
				else
					lcd_int(h);
					lcd_char(':');
			if(min<10)
				{
				lcd_char('0');
				lcd_int(min);
				}
				else
					lcd_int(min);
	lcd_locate(1,0);
	lcd_str(" SET");
	lcd_locate(1,8);
	lcd_str("\x81""\x81 ""\x82""\x82");

	SuperDebounce(&k1, &PINA, KEY_DOWN, 4, 4, rtc_dodajgodzine, NULL);
	SuperDebounce(&k2, &PINA, KEY_UP, 4, 4, rtc_dodajminute, NULL);
	SuperDebounce(&k4, &PINC, KEY_MENU, 4, 4, menu_nastepne, NULL);
	SuperDebounce(&k5, &PINC, KEY_MUTE, 4, 4, potwierdzenie, NULL);
	SuperDebounce(&k6, &PIND, WLACZNIK, 4, 4, wylaczenie, NULL);

		if(Ir_key_press_flag)
		{
			if(address == 10 && command == IR_UP)
			{
				rtc_dodajgodzine();
			}
			if(address == 10 && command == IR_DOWN)
			{
				rtc_dodajminute();
			}
			if(address == 10 && command == IR_MENU)
			{
				menu_nastepne();
			}
			if(address == 10 && command == IR_MUTE)
			{
				potwierdzenie();
			}
			if(address == 10 && command == IR_ONOFF)
			{
				wylaczenie();
			}
		Ir_key_press_flag = 0;
		command=0xff;
		address=0xff;
		TimerIR = IR_TIME;
		}
}

void ekran_outputs()
{
	lcd_cls();
	lcd_str(" FL ");
	if(!out_lf) lcd_char('X');
	else lcd_str("\x83");

	lcd_locate(0,11);
	lcd_str("FR ");
	if(!out_rf) lcd_char('X');
	else lcd_str("\x83");

	lcd_locate(1,1);
	lcd_str("RL ");
	if(!out_lr) lcd_char('X');
	else lcd_str("\x83");

	lcd_locate(1,11);
	lcd_str("RR ");
	if(!out_rr) lcd_char('X');
	else lcd_str("\x83");

	SuperDebounce(&k2, &PINA, KEY_SEL, 4, 4, preamp_select_outputs, NULL);
	SuperDebounce(&k4, &PINC, KEY_MENU, 4, 4, menu_nastepne, NULL);
	SuperDebounce(&k5, &PINC, KEY_MUTE, 4, 4, potwierdzenie, NULL);
	SuperDebounce(&k6, &PIND, WLACZNIK, 4, 4, wylaczenie, NULL);

	if(Ir_key_press_flag)
			{
				if(address == 10 && command == IR_SEL)
				{
					preamp_select_outputs();
				}

				if(address == 10 && command == IR_MENU)
				{
					menu_nastepne();
				}
				if(address == 10 && command == IR_MUTE)
				{
					potwierdzenie();
				}
				if(address == 10 && command == IR_ONOFF)
				{
					wylaczenie();
				}
			Ir_key_press_flag = 0;
			command=0xff;
			address=0xff;
			TimerIR = IR_TIME;
			}
}

void ekran_inputgain()
{
	lcd_cls();
		lcd_str("   INPUT GAIN   ");
		lcd_locate(1,4);

		lcd_int(((3-audio_switch)*625)/100);
		lcd_char('.');
		lcd_int(((3-audio_switch)*625)%100);
		lcd_locate(1,10);
		lcd_str("dB");
		SuperDebounce(&k1, &PINA, KEY_DOWN, 4, 4, preamp_switchgain_minus, NULL);
		SuperDebounce(&k2, &PINA, KEY_UP, 4, 4, preamp_switchgain_plus, NULL);
		SuperDebounce(&k4, &PINC, KEY_MENU, 4, 4, menu_nastepne, NULL);
		SuperDebounce(&k5, &PINC, KEY_MUTE, 4, 4, potwierdzenie, NULL);
		SuperDebounce(&k6, &PIND, WLACZNIK, 4, 4, wylaczenie, NULL);

		if(Ir_key_press_flag)
		{
			if(address == 10 && command == IR_UP)
			{
				preamp_switchgain_plus();
			}
			if(address == 10 && command == IR_DOWN)
			{
				preamp_switchgain_minus();
			}
			if(address == 10 && command == IR_MENU)
			{
				menu_nastepne();
			}
			if(address == 10 && command == IR_MUTE)
			{
				potwierdzenie();
			}
			if(address == 10 && command == IR_ONOFF)
			{
				wylaczenie();
			}
		Ir_key_press_flag = 0;
		command=0xff;
		address=0xff;
		TimerIR = IR_TIME;
		}
}

void menu()
{
 switch(menu_nr)
 {
 	 case 0: ekran_0();
 	 break;
 	 case 1: ekran_bass();
 	 break;
	 case 2: ekran_treble();
	 break;
 	 case 3: ekran_outputs();
 	 break;
 	 case 4: ekran_fl();
 	 break;
 	 case 5: ekran_fr();
 	 break;
 	 case 6: ekran_rl();
 	 break;
 	 case 7: ekran_rr();
 	 break;
 	 case 8: ekran_inputgain();
 	 break;
 	 case 9: ekran_zegar();
 	 break;
// 	 case 10: ekran_off();
// 	 break;

 	 default: ekran_0();
 	 break;

 }
}
