//////////////////////////////////////////////////////////////////////////////
// *
// * Predmetni projekat iz predmeta OAiS DSP 1
// * Godina: 2017
// *
// * Zadatak: Uklanjanje periodicnog suma upotrebom notch filtra
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
#include "print_number.h"
#include "math.h"
#include "Dsplib.h"
#include "window.h"
#include "iir.h"

/* Frekvencija odabiranja */
#define SAMPLE_RATE 8000L

/* Velicina prozora za racunanje FFT-a */
/* TODO Dodeliti velicinu bloka kod racunanja FFT*/
#define FFT_SIZE 128

/* Niz za smestanje odbiraka ulaznog signala */
#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

Int16 SavedBufferL[AUDIO_IO_SIZE];
Int16 OutputBufferL[AUDIO_IO_SIZE];
Int16 OutputBufferR[AUDIO_IO_SIZE];

Int32 Power[FFT_SIZE/2];
Int32 MaxPower;

Int16 x_history_l[2];
Int16 y_history_l[2];
Int16 x_history_r[2];
Int16 y_history_r[2];

#define r 0.87

Int16 filtar_880Hz[6] = {32767, -25248 , 32767,
								32767, -r*25248 , r*r*32768 };
Int16 filtar_1540Hz[6] = {32767, -11583 , 32767,
								32767, -r*11583 , r*r*32768 };
Int16 filtar_2100Hz[6] = {32767, 2571 , 32767,
								32767, r*2571 , r*r*32768 };
Int16 filtar_2560Hz[6] = {32767, 13952 , 32767,
								32767, r*13952 , r*r*32768 };

Int16 delta[128];

void main( void )
{
	int broj = 0;
	int i;
	int indMaxPow = 0;

	/* Inicijalizaija razvojne ploce */
	EZDSP5535_init( );

    /* Inicijalizacija LCD kontrolera */
	initPrintNumber();

	printf("\n Uklanjanje sinusoidalnog suma iz signala \n");

    /* Podesavanje ulazne i izlazne datoteke za simulaciju AD/DA konvertora */
	aic3204_set_input_filename("../input4.pcm");
	aic3204_set_output_filename("../output4.pcm");

    /* Inicijalizacija veze sa AIC3204 kodekom (AD/DA) */
    aic3204_hardware_init();

    /* Inicijalizacija AIC3204 kodeka */
	aic3204_init();

    aic3204_dma_init();

    /* Postavljanje vrednosti frekvencije odabiranja i pojacanja na kodeku */
    set_sampling_frequency_and_gain(SAMPLE_RATE, 0);

	for(i=0; i<2; i++)
	{
		x_history_l[i] = 0;
		y_history_l[i] = 0;
		x_history_r[i] = 0;
		y_history_r[i] = 0;
	}
	delta[0] = 16000;
	for (i=1; i<128; i++)
	{
		delta[i] = 0;
	}
	for(i=0; i<AUDIO_IO_SIZE; i++)
	    			{
	    				OutputBufferL[i] = second_order_IIR(delta[i], filtar_880Hz, x_history_l, y_history_l);
	    				OutputBufferR[i] = second_order_IIR(InputBufferR[i], filtar_880Hz, x_history_r, y_history_r);
	    			}
    while(broj != 1000)
	{


    	aic3204_read_block(InputBufferL, InputBufferR);

		/* TODO */

    	/* Cuvanje bufera prije racunanja DFT */
    	for(i=0; i<AUDIO_IO_SIZE; i++)
    	{
    		SavedBufferL[i] = InputBufferL[i];
    	}

    	/* Prozoriranje */
    	for(i=0; i<AUDIO_IO_SIZE; i++)
    	{
    		InputBufferL[i] = _smpy(InputBufferL[i], p_window[i]);
    	}

    	/* Racunanje DFT */
    	rfft(InputBufferL, FFT_SIZE, SCALE);

    	/* Racunanje spektra snage */
    	Power[0] = (Int32)InputBufferL[0] * InputBufferL[0];
    	for(i=2; i<AUDIO_IO_SIZE; i=i+2)
    	{
    		Power[i/2] = (Int32)InputBufferL[i] * InputBufferL[i] + (Int32)InputBufferL[i + 1] * InputBufferL[i + 1];
    	}

    	/* Nalazenje indeksa maksimalnog koeficijenta u spektru */
    	MaxPower = Power[0];
    	for(i=1; i<FFT_SIZE/2; i++)
    	{
    		if(Power[i] > MaxPower)
    		{
    			MaxPower = Power[i];
    			indMaxPow = i;
    		}
    	}

    	switch(indMaxPow)
    	{
    		case 14:
    			printf("%d\tPrepoznata frekevencija: 880Hz\n", broj++);
    			for(i=0; i<AUDIO_IO_SIZE; i++)
    			{
    				OutputBufferL[i] = second_order_IIR(SavedBufferL[i], filtar_880Hz, x_history_l, y_history_l);
    				OutputBufferR[i] = second_order_IIR(InputBufferR[i], filtar_880Hz, x_history_r, y_history_r);
    			}
    			break;
    		case 24:
    		    printf("%d\tPrepoznata frekevencija: 1540Hz\n", broj++);
    			for(i=0; i<AUDIO_IO_SIZE; i++)
    			{
    				OutputBufferL[i] = second_order_IIR(SavedBufferL[i], filtar_1540Hz, x_history_l, y_history_l);
    				OutputBufferR[i] = second_order_IIR(InputBufferR[i], filtar_1540Hz, x_history_r, y_history_r);
    			}
    		    break;
    		case 25:
    		    printf("%d\tPrepoznata frekevencija: 1540Hz\n", broj++);
    			for(i=0; i<AUDIO_IO_SIZE; i++)
    			{
    				OutputBufferL[i] = second_order_IIR(SavedBufferL[i], filtar_1540Hz, x_history_l, y_history_l);
    				OutputBufferR[i] = second_order_IIR(InputBufferR[i], filtar_1540Hz, x_history_r, y_history_r);
    			}
    		    break;
    		case 33:
    		    printf("%d\tPrepoznata frekevencija: 2100Hz\n", broj++);
    			for(i=0; i<AUDIO_IO_SIZE; i++)
    			{
    				OutputBufferL[i] = second_order_IIR(SavedBufferL[i], filtar_2100Hz, x_history_l, y_history_l);
    				OutputBufferR[i] = second_order_IIR(InputBufferR[i], filtar_2100Hz, x_history_r, y_history_r);
    			}
    		    break;
    		case 34:
    		    printf("%d\tPrepoznata frekevencija: 2100Hz\n", broj++);
    			for(i=0; i<AUDIO_IO_SIZE; i++)
    			{
    				OutputBufferL[i] = second_order_IIR(SavedBufferL[i], filtar_2100Hz, x_history_l, y_history_l);
    				OutputBufferR[i] = second_order_IIR(InputBufferR[i], filtar_2100Hz, x_history_r, y_history_r);
    			}
    		    break;
    		case 41:
    		    printf("%d\tPrepoznata frekevencija: 2560Hz\n", broj++);
    			for(i=0; i<AUDIO_IO_SIZE; i++)
    			{
    				OutputBufferL[i] = second_order_IIR(SavedBufferL[i], filtar_2560Hz, x_history_l, y_history_l);
    				OutputBufferR[i] = second_order_IIR(InputBufferR[i], filtar_2560Hz, x_history_r, y_history_r);
    			}
    		    break;
    		default:
    			printf("%d\tNije prepoznata nijedna frekvencija\n", broj++);
    			for(i=0; i<AUDIO_IO_SIZE; i++)
    			{
    				OutputBufferL[i] = SavedBufferL[i];
    				OutputBufferR[i] = InputBufferR[i];
    			}
    	}

		aic3204_write_block(OutputBufferL, OutputBufferR);
	}

	/* Prekid veze sa AIC3204 kodekom */
    aic3204_disable();

    printf( "\n***Kraj programa***\n" );
	SW_BREAKPOINT;
}
