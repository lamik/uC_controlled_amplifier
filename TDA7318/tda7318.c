/*
 * tda7318.c
 *
 *  Created on: 15-08-2013
 *      Author: Administrator
 */
#include "tda7318.h"



//Volume+
void preamp_vol_plus(void)
{
	if(volume > 0)
		{
			wycisz = 0;
			volume--;
			TWI_start();
			TWI_write(TDA7318_ADR);
			TWI_write(0b00000000 | volume);
			TWI_stop();
		}
}

//Volume-
void preamp_vol_minus(void)
{
	if(volume < 63)
		{
			wycisz = 0;
			volume++;
			TWI_start();
			TWI_write(TDA7318_ADR);
			TWI_write(0b00000000 | volume);
			TWI_stop();
		}
}

//ATT LF +
void preamp_attlf_plus(void)
{
	if(att_lf > 0)
	{
		att_lf--;
		TWI_start();
		TWI_write(TDA7318_ADR);
		TWI_write(0b10000000 | att_lf);
		TWI_stop();
	}
}

//ATT LF-
void preamp_attlf_minus(void)
{
	if(att_lf < 31)
	{
		att_lf++;
		TWI_start();
		TWI_write(TDA7318_ADR);
		TWI_write(0b10000000 | att_lf);
		TWI_stop();
	}
}
//ATT RF +
void preamp_attrf_plus(void)
{
	if(att_rf > 0)
	{
		att_rf--;
		TWI_start();
		TWI_write(TDA7318_ADR);
		TWI_write(0b10100000 | att_rf);
		TWI_stop();
	}
}

//ATT RF-
void preamp_attrf_minus(void)
{
	if(att_rf < 31)
	{
		att_rf++;
		TWI_start();
		TWI_write(TDA7318_ADR);
		TWI_write(0b10100000 | att_rf);
		TWI_stop();
	}
}

//ATT LR +
void preamp_attlr_plus(void)
{
	if(att_lr > 0)
	{
		att_lr--;
		TWI_start();
		TWI_write(TDA7318_ADR);
		TWI_write(0b11000000 | att_lr);
		TWI_stop();
	}
}

//ATT LR-
void preamp_attlr_minus(void)
{
	if(att_lr < 31)
	{
		att_lr++;
		TWI_start();
		TWI_write(TDA7318_ADR);
		TWI_write(0b11000000 | att_lr);
		TWI_stop();
	}
}

//ATT RR +
void preamp_attrr_plus(void)
{
	if(att_rr > 0)
	{
		att_rr--;
		TWI_start();
		TWI_write(TDA7318_ADR);
		TWI_write(0b11100000 | att_rr);
		TWI_stop();
	}
}
//ATT RR-
void preamp_attrr_minus(void)
{
	if(att_rr < 31)
	{
		att_rr++;
		TWI_start();
		TWI_write(TDA7318_ADR);
		TWI_write(0b11100000 | att_rr);
		TWI_stop();
	}
}

//Audio Switch gain+
void preamp_switchgain_plus(void)
{
	if(audio_switch > 0)
	{
		audio_switch--;
		TWI_start();
		TWI_write(TDA7318_ADR);
		TWI_write(0b01000000 | (audio_switch<<3));
		TWI_stop();
	}
}

//Audio Switch gain-

void preamp_switchgain_minus(void)
{
	if(audio_switch < 3)
	{
		audio_switch++;
		TWI_start();
		TWI_write(TDA7318_ADR);
		TWI_write(0b01000000 | (audio_switch<<3));
		TWI_stop();
	}
}

//Bass+
void preamp_bass_plus(void)
{
	uint8_t tmp=0;
	if(bass < 14)
	{
		bass++;
		switch (bass)
		{
		case 0: tmp = 0b00000000; //-14dB
						break;
		case 1: tmp = 0b00000001; //-12dB
						break;
		case 2: tmp = 0b00000010; //-10dB
						break;
		case 3: tmp = 0b00000011; //-8dB
						break;
		case 4: tmp = 0b00000100; //-6dB
						break;
		case 5: tmp = 0b00000101; //-4dB
						break;
		case 6: tmp = 0b00000110; //-2dB
						break;
		case 7: tmp = 0b00000111; //0dB
						break;
		case 8: tmp = 0b00001110; //2dB
						break;
		case 9: tmp = 0b00001101; //4dB
						break;
		case 10: tmp = 0b00001100; //6dB
						break;
		case 11: tmp = 0b00001011; //8dB
						break;
		case 12: tmp = 0b00001010; //10dB
						break;
		case 13: tmp = 0b00001001; //12dB
						break;
		case 14: tmp = 0b00001000; //14dB
						break;
		}
		TWI_start();
		TWI_write(TDA7318_ADR);
		TWI_write(0b01100000 | tmp);
		TWI_stop();
	}
}
//Bass-
void preamp_bass_minus(void)
{
	uint8_t tmp=0;
	if(bass > 0)
	{
		bass--;
		switch (bass)
		{
		case 0: tmp = 0b00000000; //-14dB
						break;
		case 1: tmp = 0b00000001; //-12dB
						break;
		case 2: tmp = 0b00000010; //-10dB
						break;
		case 3: tmp = 0b00000011; //-8dB
						break;
		case 4: tmp = 0b00000100; //-6dB
						break;
		case 5: tmp = 0b00000101; //-4dB
						break;
		case 6: tmp = 0b00000110; //-2dB
						break;
		case 7: tmp = 0b00000111; //0dB
						break;
		case 8: tmp = 0b00001110; //2dB
						break;
		case 9: tmp = 0b00001101; //4dB
						break;
		case 10: tmp = 0b00001100; //6dB
						break;
		case 11: tmp = 0b00001011; //8dB
						break;
		case 12: tmp = 0b00001010; //10dB
						break;
		case 13: tmp = 0b00001001; //12dB
						break;
		case 14: tmp = 0b00001000; //14dB
						break;
		}
		TWI_start();
		TWI_write(TDA7318_ADR);
		TWI_write(0b01100000 | tmp);
		TWI_stop();
	}
}
//Treble+
void preamp_treble_plus(void)
{
	uint8_t tmp=0;
	if(treble < 14)
	{
		treble++;
		switch (treble)
		{
		case 0: tmp = 0b00000000; //-14dB
						break;
		case 1: tmp = 0b00000001; //-12dB
						break;
		case 2: tmp = 0b00000010; //-10dB
						break;
		case 3: tmp = 0b00000011; //-8dB
						break;
		case 4: tmp = 0b00000100; //-6dB
						break;
		case 5: tmp = 0b00000101; //-4dB
						break;
		case 6: tmp = 0b00000110; //-2dB
						break;
		case 7: tmp = 0b00000111; //0dB
						break;
		case 8: tmp = 0b00001110; //2dB
						break;
		case 9: tmp = 0b00001101; //4dB
						break;
		case 10: tmp = 0b00001100; //6dB
						break;
		case 11: tmp = 0b00001011; //8dB
						break;
		case 12: tmp = 0b00001010; //10dB
						break;
		case 13: tmp = 0b00001001; //12dB
						break;
		case 14: tmp = 0b00001000; //14dB
						break;
		}
		TWI_start();
		TWI_write(TDA7318_ADR);
		TWI_write(0b01110000 | tmp);
		TWI_stop();
	}
}

//Treble-
void preamp_treble_minus(void)
{
	uint8_t tmp=0;
	if(treble > 0)
	{
		treble--;
		switch (treble)
		{
		case 0: tmp = 0b00000000; //-14dB
						break;
		case 1: tmp = 0b00000001; //-12dB
						break;
		case 2: tmp = 0b00000010; //-10dB
						break;
		case 3: tmp = 0b00000011; //-8dB
						break;
		case 4: tmp = 0b00000100; //-6dB
						break;
		case 5: tmp = 0b00000101; //-4dB
						break;
		case 6: tmp = 0b00000110; //-2dB
						break;
		case 7: tmp = 0b00000111; //0dB
						break;
		case 8: tmp = 0b00001110; //2dB
						break;
		case 9: tmp = 0b00001101; //4dB
						break;
		case 10: tmp = 0b00001100; //6dB
						break;
		case 11: tmp = 0b00001011; //8dB
						break;
		case 12: tmp = 0b00001010; //10dB
						break;
		case 13: tmp = 0b00001001; //12dB
						break;
		case 14: tmp = 0b00001000; //14dB
						break;
		}
		TWI_start();
		TWI_write(TDA7318_ADR);
		TWI_write(0b01110000 | tmp);
		TWI_stop();
	}
}

void preamp_select_outputs()
{
	if(outputs < 5)
		outputs++;
	else outputs = 0;

	switch(outputs)
	{
	case 0:
	{
		out_lf = 1;
		out_rf = 0;
		out_lr = 0;
		out_rr = 0;
		PORTC |= LF_OUT;
		PORTC &=~(RF_OUT|LR_OUT|RR_OUT);
		break;
	}
	case 1:
	{
		out_lf = 0;
		out_rf = 1;
		out_lr = 0;
		out_rr = 0;
		PORTC |= RF_OUT;
		PORTC &=~(LF_OUT|LR_OUT|RR_OUT);
		break;
	}
	case 2:
	{
		out_lf = 0;
		out_rf = 0;
		out_lr = 1;
		out_rr = 0;
		PORTC |= LR_OUT;
		PORTC &=~(LF_OUT|RF_OUT|RR_OUT);
		break;
	}
	case 3:
	{
		out_lf = 0;
		out_rf = 0;
		out_lr = 0;
		out_rr = 1;
		PORTC |= RR_OUT;
		PORTC &=~(LF_OUT|LR_OUT|RF_OUT);
		break;
	}
	case 4:
	{
		out_lf = 1;
		out_rf = 1;
		out_lr = 0;
		out_rr = 0;
		PORTC |= (RF_OUT|LF_OUT);
		PORTC &=~(LR_OUT|RR_OUT);
		break;
	}
	case 5:
	{
		out_lf = 0;
		out_rf = 0;
		out_lr = 1;
		out_rr = 1;
		PORTC |= (LR_OUT|RR_OUT);
		PORTC &=~(RF_OUT|LF_OUT);
		break;
	}
	}

}

