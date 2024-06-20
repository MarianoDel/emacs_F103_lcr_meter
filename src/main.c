//------------------------------------------------------------------------------
// #### TEMPLATE FOR PROJECTS WITH ARDUINO BLUEPILL - Processor STM32F103C8T6
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### MAIN.C #################################################################
//------------------------------------------------------------------------------

// Includes --------------------------------------------------------------------
#include "stm32f10x.h"
#include "hard.h"
#include "test_functions.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"
#include "adc.h"
#include "i2c.h"

#include "screen.h"
#include "res_menu.h"
#include "ssd1306_display.h"

#include <stdio.h>
#include <string.h>



// Externals -------------------------------------------------------------------
// -- Externals for timers
volatile unsigned short wait_ms_var = 0;
volatile unsigned short timer_standby = 0;
volatile unsigned short timer_led = 0;

// -- Externals for adc
volatile unsigned short adc_ch [ADC_CHANNEL_QUANTITY];


// Globals ---------------------------------------------------------------------


// Module Private Functions ----------------------------------------------------
void TimingDelay_Decrement(void);
void SysTickError (void);
extern void EXTI0_IRQHandler (void);
sw_actions_t CheckActions (void);


// Module Functions ------------------------------------------------------------
int main (void)
{
    // System Clock already configured at this point

    // Gpio Configuration.
    GpioInit ();
    
    // Systick Timer Activation
    // if (SysTick_Config(72000))
    if (SysTick_Config(48000))
        SysTickError();

    // -- Hardware Tests Functions
    // TF_Hardware_Tests ();
    // -- End of Hardware Tests Functions

    // Hardware Setup
    // for supply stability    
    for (int i = 0; i < 3; i++)
    {
        LED_ON;
        Wait_ms(250);
        LED_OFF;
        Wait_ms(250);
    }

    // Oled Init & First Screen
    I2C1_Init();
    SCREEN_Init();
    
    //-- DMA configuration and Init
    // DMAConfig ();
    // DMA_ENABLE;

    //-- ADC Init
    // AdcConfig();
    // AdcStart();


    // Timer Peripherals Activation
    // TIM1_Init();

    // all channels to 0
    // Pwm_U(0);
    // Pwm_V(0);
    // Pwm_W(0); 
    
    // TIM_3_Init();

    // Pwm_Setting_Update_Reset ();
    sw_actions_t actions = do_nothing;
    while (1)
    {
	actions = CheckActions();
	Res_Menu(actions);
	
        // Synchro ();

        // Led_Toggle_Update ();

        // Hall_Update ();
	Hard_UpdateSwitches ();

	display_update_int_state_machine();
    }

}


//--- End of Main ---//
sw_actions_t CheckActions (void)
{
    sw_actions_t actions = do_nothing;
    
    if (Hard_CheckS1() > S_NO)
	actions = selection_up;

    if (Hard_CheckS2() > S_NO)
	actions = selection_enter;
    
    return actions;
}


void TimingDelay_Decrement(void)
{
    if (wait_ms_var)
        wait_ms_var--;

    if (timer_standby)
        timer_standby--;

    if (timer_led)
        timer_led--;

    Hard_Timeouts ();

}


// void EXTI0_IRQHandler (void)
// {
//     if(EXTI->PR & 0x00000001)	//Line0
//     {
//         if (LED)
//             LED_OFF;
//         else
//             LED_ON;

        
//         EXTI->PR |= 0x00000001;
//     }
// }


void SysTickError (void)
{
    //Capture systick error...
    while (1)
    {
        if (LED)
            LED_OFF;
        else
            LED_ON;

        for (unsigned char i = 0; i < 255; i++)
        {
            asm ("nop \n\t"
                 "nop \n\t"
                 "nop \n\t" );
        }
    }
}

//--- end of file ---//

