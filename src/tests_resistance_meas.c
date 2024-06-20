//---------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    TEST PLATFORM FOR FIRMWARE
// ##
// #### TESTS_RESISTANCE_MEAS.C ###############
//---------------------------------------------

// Includes Modules for tests --------------------------------------------------
#include "resistance_meas.h"


//helper modules
#include "tests_ok.h"
// #include "tests_vector_utils.h"

#include <stdio.h>
#include <string.h>


// Globals externals for module to test ----------------------------------------


// Externals globals from module to test ---------------------------------------


// Globals locals --------------------------------------------------------------


// Module Auxialiary Functions -------------------------------------------------


// Module Functions for testing ------------------------------------------------
void Test_ConvertAdcToOhms (void);
void Test_ConvertAdcToKOhms (void);
    

// Module Functions ------------------------------------------------------------


int main (int argc, char *argv[])
{

    // Test_ConvertAdcToOhms ();

    Test_ConvertAdcToKOhms ();    

    return 0;
}


void Test_ConvertAdcToOhms (void)
{
    int error = 0;
    unsigned short res_int;
    unsigned short res_dec;

    printf("\nTest adc to ohms convertion...\n");

    for (int i = 0; i < 10; i++)
    {
	ConvertAdcToOhms(i, &res_int, &res_dec);
	printf("adc: %d res: %d.%d\n", i, res_int, res_dec); 
    }

    ConvertAdcToOhms(4069, &res_int, &res_dec);
    printf ("max points on: 4069 res: %d.%d\n", res_int, res_dec); 
    // for (int i = 0; i < 4095; i += 10)
    // {
    // 	ConvertAdcToOhms(i, &res_int, &res_dec);
    // 	printf("adc: %d res%d: %d.%02d\n", i, res, res_int, res_dec);
    // }
}


void Test_ConvertAdcToKOhms (void)
{
    int error = 0;
    unsigned short res_int;
    unsigned short res_dec;

    printf("\nTest adc to kohms convertion...\n");

    for (int i = 0; i < 10; i++)
    {
	ConvertAdcToKOhms(i, &res_int, &res_dec);
	printf("adc: %d res: %d.%dk\n", i, res_int, res_dec); 
    }

    ConvertAdcToKOhms(4069, &res_int, &res_dec);
    printf ("max points on: 4069 res: %d.%dk\n", res_int, res_dec); 
    // for (int i = 0; i < 4095; i += 10)
    // {
    // 	ConvertAdcToOhms(i, &res_int, &res_dec);
    // 	printf("adc: %d res%d: %d.%02d\n", i, res, res_int, res_dec);
    // }
}




// Module Mocked Functions -----------------------------------------------------
void Left_To_LowRes (void)
{
}


void Right_To_Gnd (void)
{
}


unsigned short AdcGetConversion (void)
{
    return 0;
}

void AdcConvertChannel (unsigned char channel)
{
}

unsigned char AdcConvertSingleChannelFinishFlag (void)
{
    return 1;
}


void Wait_ms (unsigned short a)
{
}


//--- end of file ---//


