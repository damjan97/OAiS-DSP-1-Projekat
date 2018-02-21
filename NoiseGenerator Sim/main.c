//////////////////////////////////////////////////////////////////////////////
// *
// * Predmetni projekat iz predmeta OAiS DSP 1
// * Godina: 2017
// *
// * Zadatak: Generator periodicnog suma
// * Autor: Damjan Glamocic    RA65/2015
// *
// *
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5535.h"
#include "ezdsp5535_i2c.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "ezdsp5535_i2s.h"
#include "ezdsp5535_sar.h"
#include "print_number.h"
#include "gen_sinus.h"
#include "math.h"

/* Frekvencija odabiranja */
#define SAMPLE_RATE 8000L

/* Niz za smestanje odbiraka ulaznog signala */
#pragma DATA_ALIGN(bufferL,4)
Int16 bufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(bufferR,4)
Int16 bufferR[AUDIO_IO_SIZE];
Int16 sine[AUDIO_IO_SIZE];

Uint16 pressedNow;
Uint16 pressedBefore;
int frequency;
float ph;
Int32 a;

void main( void )
{
	frequency = 0;
	int i;
	ph = 0;
	int broj = 0;
    /* Inicijalizaija razvojne ploce */
    EZDSP5535_init( );

    /* Inicijalizacija kontrolera za ocitavanje vrednosti pritisnutog dugmeta*/
    EZDSP5535_SAR_init();

    /* Inicijalizacija LCD kontrolera */
    initPrintNumber();

	printf("\n Dodavanje suma u signal \n");

    /* Podesavanje ulazne i izlazne datoteke za simulaciju AD/DA konvertora */
	aic3204_set_input_filename("../input.pcm");
	aic3204_set_output_filename("../output.pcm");

    /* Inicijalizacija veze sa AIC3204 kodekom (AD/DA) */
    aic3204_hardware_init();

    /* Inicijalizacija AIC3204 kodeka */
	aic3204_init();

    aic3204_dma_init();

    /* Postavljanje vrednosti frekvencije odabiranja i pojacanja na kodeku */
    set_sampling_frequency_and_gain(SAMPLE_RATE, 0);

	clearLCD();
    setWritePointerToFirstChar();
	
	while(broj != 1000)
	{

		aic3204_read_block(bufferL, bufferR);

		/* TODO : Generisati sum zadate frekvencije i sabrati sa ulznim signalom. */

		pressedNow = EZDSP5535_SAR_getKey();
		if(frequency == 0)
		{
			clearLCD();
			printChar('0');
			printChar(' ');
			printChar('H');
			printChar('z');
		}
		if(pressedNow == SW1 && pressedNow != pressedBefore) {
			clearLCD();
			if(frequency == 880)
			{
				printChar('8');
				printChar('8');
				printChar('0');
				printChar(' ');
				printChar('H');
				printChar('z');
				frequency = 1540;
			}else if(frequency == 1540)
			{
				printChar('1');
				printChar('5');
				printChar('4');
				printChar('0');
				printChar(' ');
				printChar('H');
				printChar('z');
				frequency = 2100;
			}else if (frequency == 2100)
			{
				printChar('2');
				printChar('1');
				printChar('0');
				printChar('0');
				printChar(' ');
				printChar('H');
				printChar('z');
				frequency = 2560;
			}else if (frequency == 2560)
			{
				printChar('2');
				printChar('5');
				printChar('6');
				printChar('0');
				printChar(' ');
				printChar('H');
				printChar('z');
				frequency = 880;
			}else
			{
				frequency = 880;
			}
		}
		pressedBefore = pressedNow;


		gen_sinus_table(AUDIO_IO_SIZE, 16000, (float)frequency/SAMPLE_RATE, &ph, sine);
		for(i = 0; i < AUDIO_IO_SIZE; i++)
		{
			a = (Int32)bufferL[i] + sine[i];
			if (a > 32767)
			{
				a = 32767;
			}else if(a < -32768)
			{
				a = -32768;
			}
			bufferL[i] = a;
			a = (Int32)bufferR[i] + sine[i];
			if (a > 32767)
			{
				a = 32767;
			}else if(a < -32768)
			{
				a = -32768;
			}
			bufferR[i] = a;
		}

		printf("%d\n", broj ++);
		if(broj == 200)
		{
			frequency = 880;
		}else if(broj == 400)
		{
			frequency = 1540;
		}
		else if(broj == 600)
		{
			frequency = 2100;
		}
		else if(broj == 800)
		{
			frequency = 2560;
		}

		aic3204_write_block(bufferL, bufferR);

	}

	/* Prekid veze sa AIC3204 kodekom */
    aic3204_disable();

    printf( "\n***Kraj programa***\n" );
	SW_BREAKPOINT;
}


