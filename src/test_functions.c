//------------------------------------------------
// ## Internal Test Functions Module
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### TEST_FUNCTIONS.C #########################
//------------------------------------------------

// Includes --------------------------------------------------------------------
#include "test_functions.h"
#include "stm32f10x.h"
#include "hard.h"
#include "tim.h"
#include "adc.h"
#include "tim.h"
#include "i2c.h"
#include "screen.h"
#include "ssd1306_display.h"

#include <stdio.h>
#include <string.h>



// Module Private Types Constants & Macros -------------------------------------


// Externals -------------------------------------------------------------------
extern volatile unsigned char adc_int_seq_ready;
extern volatile unsigned short adc_ch [];
extern volatile unsigned short timer_standby;


// Globals ---------------------------------------------------------------------


// Module Private Functions ----------------------------------------------------
void TF_Led (void);
void TF_Oled_Screen_Int2 (void);


// Module Functions ------------------------------------------------------------
void TF_Hardware_Tests (void)
{
    // TF_Led ();

    TF_Oled_Screen_Int2 ();
}


void TF_Led (void)
{
    while (1)
    {
        if (LED)
	{
            LED_OFF;
	    PB5_ON;
	}
        else
	{
            LED_ON;
	    PB5_OFF;
	}
	Wait_ms(500);

	// LED_OFF;	
        // Wait_ms(500);
	// LED_ON;
        // Wait_ms(500);
    }
}


void TF_Oled_Screen_Int2 (void)
{
    // OLED Init
    Wait_ms(500);    //for supply stability
    I2C1_Init();
    Wait_ms(10);

    for (int i = 0; i < 6; i++)
    {
	if (LED)
	    LED_OFF;
	else
	    LED_ON;

	Wait_ms(500);
    }
    
    //primer pantalla
    LED_ON;
    SCREEN_Init();
    LED_OFF;

    int a = 1;

    while (1)
    {
        if ((a == 1) &&
            (!timer_standby))
        {
            LED_ON;
            display_contrast (255);        
            SCREEN_ShowText2(
                "Primera  ",
                " Pantalla",
                "         ",
                "         "
                );

            LED_OFF;
            timer_standby = 5000;
            a++;
        }

        if ((a == 2) &&
            (!timer_standby))
        {        
            LED_ON;
            display_contrast (10);
            SCREEN_ShowText2(
                "         ",
                "         ",
                "Segunda  ",
                " Pantalla"
                );
            LED_OFF;
            timer_standby = 5000;
            a++;
        }

        if ((a == 3) &&
            (!timer_standby))
        {
            LED_ON;
            display_contrast (255);        
            display_invert(1);
            SCREEN_ShowText2(
                "Third    ",
                "  Screen ",
                "         ",
                "         "
                );
            LED_OFF;
            timer_standby = 5000;
            a++;
        }


        if ((a == 4) &&
            (!timer_standby))
        {        
            LED_ON;
            display_invert(0);
            SCREEN_ShowText2(
                "         ",
                "         ",            
                "Forth    ",
                "  Screen "
                );
            LED_OFF;
            timer_standby = 5000;
            a = 1;            
        }

        display_update_int_state_machine ();
    }
}


//--- end of file ---//
