//----------------------------------------------------
// Tests for gtk lib
// Implementation of tests_lcd_application.h functions
//----------------------------------------------------

#include <gtk/gtk.h>
#include <stdint.h>
#include "tests_oled_application.h"

// Application Includes needed for this test
#include "screen.h"
#include "ssd1306_display.h"
#include "res_menu.h"
#include "resistance_meas.h"

#include "switches_answers.h"

// Module Types Constants and Macros -------------------------------------------


// Externals -- Access to the tested Module ------------------------------------
// extern volatile unsigned short show_select_timer;


// Globals -- Externals for the tested Module ----------------------------------
sw_actions_t switch_actions = do_nothing;


// Globals ---------------------------------------------------------------------
static GMutex mutex;
int setup_done = 0;
unsigned int timer_standby = 0;


// Testing Function loop -------------------------------------------------------
gboolean Test_Main_Loop (gpointer user_data)
{
    if (!setup_done)
    {
	SCREEN_Init ();
	setup_done = 1;
    }
    
    Res_Menu(switch_actions);
    display_update_int_state_machine();

    // if (resp == resp_finish)
    //     return FALSE;

    //wraper to clean sw
    g_mutex_lock (&mutex);

    if (switch_actions != do_nothing)
        switch_actions = do_nothing;
    
    g_mutex_unlock (&mutex);
        
    return TRUE;
}


gboolean Test_Timeouts_Loop_1ms (gpointer user_data)
{
    if (timer_standby)
        timer_standby--;
    // //timeout lcd_utils internal
    // if (show_select_timer)
    //     show_select_timer--;

    return TRUE;
}


gboolean Test_Timeouts_Loop_1000ms (gpointer user_data)
{
    return TRUE;
}


// Module Implemantation of buttons functions
void sw1_button_function (void)
{
    g_mutex_lock (&mutex);
    switch_actions = selection_dwn;
    g_mutex_unlock (&mutex);
}

void sw2_button_function (void)
{
    g_mutex_lock (&mutex);
    switch_actions = selection_up;
    g_mutex_unlock (&mutex);
}


// Module Mocked Functions
int test_num = 0;
resist_meas_e Resistance_Meas (unsigned short * res_int,
			       unsigned short * res_dec,
			       char * multiplier)
{
    resist_meas_e answer = RES_MEAS_NONE;
    
    if (timer_standby)
	return answer;
    
    timer_standby = 2000;

    switch (test_num)
    {
    case 0:
	answer = RES_MEAS_GETTED;

	*res_int = 10;
	*res_dec = 10;
	*multiplier = 'k';
	
	test_num++;
	break;

    case 1:
	answer = RES_MEAS_GETTED;

	*res_int = 100;
	*res_dec = 1;
	*multiplier = 'k';
	
	test_num++;
	break;

    case 2:
	answer = RES_MEAS_TOO_HIGH;
	test_num++;
	break;

    default:
	test_num = 0;
	break;
    }

    return answer;
}
// Nedded by menues module provided by hard module
// void UpdateSwitches (void)
// {
// }

// resp_sw_t Check_SW_SEL (void)
// {
//     resp_sw_t sw = SW_NO;
    
//     g_mutex_lock (&mutex);

//     if (switch_actions == selection_enter)
//         sw = SW_MIN;
    
//     g_mutex_unlock (&mutex);
    
//     return sw;    
// }

// unsigned char Check_SW_DWN (void)
// {
//     unsigned char a = 0;
    
//     g_mutex_lock (&mutex);

//     if (switch_actions == selection_dwn)
//         a = 1;
    
//     g_mutex_unlock (&mutex);
    
//     return a;
// }


// unsigned char Check_SW_UP (void)
// {
//     unsigned char a = 0;
    
//     g_mutex_lock (&mutex);

//     if (switch_actions == selection_up)
//         a = 1;
    
//     g_mutex_unlock (&mutex);
    
//     return a;
// }


//--- end of file ---//
