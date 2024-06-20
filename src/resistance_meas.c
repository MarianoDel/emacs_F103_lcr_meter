//----------------------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### RESISTANCE_MEAS.C ##################################
//----------------------------------------------------------

// Includes --------------------------------------------------------------------
#include "resistance_meas.h"
#include "adc.h"

#include <stdint.h>
// Module Private Types & Macros -----------------------------------------------
#define TWO_THIRD_ADC    2730

#define R_UP_OHMS    410
#define MAX_ADC_IN_OHMS    ((0xFFFF * 4095) / (R_UP_OHMS + 0xFFFF))

#define R_UP_KOHMS    820
#define MAX_ADC_IN_KOHMS    ((0xFFFF * 4095) / (R_UP_KOHMS + 0xFFFF))

// Externals -------------------------------------------------------------------
extern void Left_To_LowRes (void);
extern void Right_To_Gnd (void);


// Globals ---------------------------------------------------------------------


// Module Private Functions ----------------------------------------------------
unsigned char ConvertAdcToOhms (unsigned short adc,
				unsigned short * pres_int,
				unsigned short * pres_dec);

unsigned char ConvertAdcToKOhms (unsigned short adc,
				 unsigned short * pres_int,
				 unsigned short * pres_dec);

resist_meas_e Resistance_GetOhms (unsigned short * pres_int,
				  unsigned short * pres_dec);

unsigned char LookStable (unsigned char channels,
			  unsigned char adc_ch1,
			  unsigned char adc_ch2);

void Resistance_GetKOhms (void);
void Resistance_GetMOhms (void);
void Resistance_GetAuto (void);
unsigned short ModuleDiff (unsigned short a, unsigned short b);

// Module Functions ------------------------------------------------------------
resist_meas_e Resistance_Meas (unsigned short * res_int,
			       unsigned short * res_dec,
			       char * multiplier)
{
    char range = *multiplier;
    
    // check multiplier first
    switch (range)
    {
    case 'o':
	Resistance_GetOhms(res_int, res_dec);
	break;

    case 'k':
	Resistance_GetKOhms();
	break;

    case 'm':
	Resistance_GetMOhms();
	break;

    case 'a':
    default:
	Resistance_GetAuto();
	break;
    }
    
    return RES_MEAS_NONE;
}


resist_meas_e Resistance_GetOhms (unsigned short * pres_int,
				  unsigned short * pres_dec)
{
    unsigned short adc1 = 0;
    unsigned short adc2 = 0;    
    unsigned char stable = 0;

    // low range with single R
    Left_To_LowRes ();
    Right_To_Gnd();
    
    stable = LookStable(1, ADC_Channel_1, 0);

    // check if meas is stable
    if (!stable)
	return RES_MEAS_TOO_HIGH;
    
    AdcConvertChannel(ADC_Channel_1);
    while(!AdcConvertSingleChannelFinishFlag());
    adc1 = AdcGetConversion();

    if (adc1 < TWO_THIRD_ADC)
    {
	ConvertAdcToOhms (adc1, pres_int, pres_dec);
	return RES_MEAS_GETTED;
    }

    stable = LookStable(2, ADC_Channel_1, ADC_Channel_6);

    // check if two meas are stable
    if (!stable)
	return RES_MEAS_TOO_HIGH;
    
    AdcConvertChannel(ADC_Channel_1);
    while(!AdcConvertSingleChannelFinishFlag());
    adc1 = AdcGetConversion();

    AdcConvertChannel(ADC_Channel_6);
    while(!AdcConvertSingleChannelFinishFlag());
    adc2 = AdcGetConversion();

    if (adc1 < adc2)
	adc1 = adc2;
    
    ConvertAdcToOhms (adc1 - adc2, pres_int, pres_dec);
    return RES_MEAS_GETTED;
}


unsigned char LookStable (unsigned char channels,
			  unsigned char adc_ch1,
			  unsigned char adc_ch2)
{
    unsigned char stable = 0;
    unsigned short diff1 = 0;
    unsigned short diff2 = 0;
    unsigned short adc1 = 0;
    unsigned short adc2 = 0;
    unsigned short last_adc1 = 0;
    unsigned short last_adc2 = 0;
    
    for (int i = 0; i < 100; i++)
    {
	Wait_ms(5);

	AdcConvertChannel(adc_ch1);
	while(!AdcConvertSingleChannelFinishFlag());
	adc1 = AdcGetConversion();
	diff1 = ModuleDiff (adc1, last_adc1);
	last_adc1 = adc1;

	if (channels == 2)
	{
	    AdcConvertChannel(adc_ch2);
	    while(!AdcConvertSingleChannelFinishFlag());
	    adc2 = AdcGetConversion();
	    diff2 = ModuleDiff (adc2, last_adc2);
	    last_adc2 = adc2;
	}

	if ((diff1 < 3) && (diff2 < 3))
	{
	    stable = 1;
	    break;
	}
    }
    
    return stable;
    
}


unsigned char ConvertAdcToOhms (unsigned short adc,
				unsigned short * pres_int,
				unsigned short * pres_dec)
{
    unsigned int calc_dec = 0;
    unsigned int calc_int = 0;

    // sanity check, max adc points for 65536 ohms
    printf("max adc points: %d\n", MAX_ADC_IN_OHMS);
    if (adc > MAX_ADC_IN_OHMS)
	return 1;
    
    unsigned short div = 4095 - adc;
    calc_dec = adc * R_UP_OHMS * 10;
    calc_dec = calc_dec / div;

    calc_int = adc * R_UP_OHMS;
    calc_int = calc_int / div;
    *pres_int = (unsigned short) calc_int;

    calc_dec = calc_dec - calc_int * 10;
    *pres_dec = (unsigned short) calc_dec;

    return 0;
}


unsigned char ConvertAdcToKOhms (unsigned short adc,
				 unsigned short * pres_int,
				 unsigned short * pres_dec)
{
    unsigned int calc_dec = 0;
    unsigned int calc_int = 0;

    // sanity check, max adc points for 65536 ohms
    printf("max adc points: %d\n", MAX_ADC_IN_KOHMS);
    if (adc > MAX_ADC_IN_KOHMS)
	return 1;
    
    unsigned short div = 4095 - adc;
    calc_dec = adc * R_UP_KOHMS;
    calc_dec = calc_dec / div;

    calc_int = adc * R_UP_KOHMS;
    calc_int = calc_int / div;
    *pres_int = (unsigned short) calc_int;

    calc_dec = calc_dec - calc_int * 10;
    *pres_dec = (unsigned short) calc_dec;

    return 0;
}




void Resistance_GetAuto (void)
{
    // check range
    // Left_To_HighRes ();
    // Right_To_Gnd();
    // for (int i = 0; i < 100; i++)
    // {
    // 	Wait_ms(5);
    // 	AdcConvertChannel(ADC_Channel_1);
    // 	while(!AdcConvertSingleChannelFinishFlag());
    // 	conv = AdcGetConversion();
    // 	unsigned short diff;

    // 	diff = 
    // 	if (conv 
    
}


void Resistance_GetKOhms (void)
{
}


void Resistance_GetMOhms (void)
{
}



unsigned short ModuleDiff (unsigned short a, unsigned short b)
{
    if (a > b)
	return a - b;

    return b - a;
}
//--- end of file ---//
