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


// Module Types Constants and Macros -------------------------------------------


// Externals -- Access to the tested Module ------------------------------------
// extern volatile unsigned short show_select_timer;


// Globals -- Externals for the tested Module ----------------------------------
// sw_actions_t switch_actions = selection_none;


// Globals ---------------------------------------------------------------------
static GMutex mutex;
int setup_done = 0;
unsigned int timer_standby = 0;


// Testing Function loop -------------------------------------------------------
gboolean Test_Main_Loop (gpointer user_data)
{
    //first screen
    if (setup_done == 0)
    {
        setup_done = 1;

        SCREEN_Init();

        SCREEN_ShowText2(
            "Kirno    ",
            "   Tech  ",
            "Smart    ",
            "   Driver"
            );
        
        timer_standby = 1300;
    }

    if (setup_done == 1)
    {
        if (timer_standby)
            display_update_int_state_machine ();
        else
            setup_done = 2;
    }

    if (setup_done == 2)
    {
        setup_done = 3;
        //second screen
        SCREEN_ShowText2(
            "         ",
            "Dexel    ",
            "Lighting ",
            "         "
            );
        timer_standby = 1300;
    }

    if (setup_done == 3)
    {
        if (timer_standby)
            display_update_int_state_machine ();
        else
            setup_done = 4;
    }

    if (setup_done == 4)
    {
        setup_done = 5;
        //second screen
        SCREEN_ShowText2(
            "         ",
            "         ",
            "         ",
            "         "
            );
        
        timer_standby = 1300;
    }
    
    if (setup_done == 5)
    {
        if (timer_standby)
            display_update_int_state_machine ();
        else
            setup_done = 6;
    }

    if (setup_done == 6)
    {
	setup_done = 7;
	SCREEN_Text2_Line1(
	    "LINEA 1   ");
	SCREEN_Text2_Line2(
	    " LINEA 2  ");
	SCREEN_Text2_Line3(
	    "  LINEA 3 ");
	SCREEN_Text2_Line4(
	    "   LINEA 4");

        timer_standby = 1300;	
    }

    if (setup_done == 7)
    {
        if (timer_standby)
            display_update_int_state_machine ();
        else
            setup_done = 8;
    }

    if (setup_done == 8)
    {
	setup_done = 9;
	SCREEN_Text2_BlankLine1();
	timer_standby = 500;
    }

    if (setup_done == 9)
    {
        if (timer_standby)
            display_update_int_state_machine ();
        else
            setup_done = 10;
    }

    if (setup_done == 10)
    {
	setup_done = 11;
	SCREEN_Text2_BlankLine2();
	timer_standby = 500;
    }

    if (setup_done == 11)
    {
        if (timer_standby)
            display_update_int_state_machine ();	
        else
            setup_done = 12;
    }

    if (setup_done == 12)
    {
	setup_done = 13;
	SCREEN_Text2_BlankLine3();
	timer_standby = 500;
    }

    if (setup_done == 13)
    {
        if (timer_standby)
            display_update_int_state_machine ();
        else
            setup_done = 14;
    }

    if (setup_done == 14)
    {
	setup_done = 15;
	SCREEN_Text2_BlankLine4();
	timer_standby = 500;
    }

    if (setup_done == 15)
    {
        if (timer_standby)
            display_update_int_state_machine ();
        else
            setup_done = 16;
    }

    // if (resp == resp_finish)
    //     return FALSE;

    // //wraper to clean sw
    // g_mutex_lock (&mutex);

    // if (switch_actions != selection_none)
    //     switch_actions = selection_none;
    
    // g_mutex_unlock (&mutex);
        
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
    // g_mutex_lock (&mutex);
    // switch_actions = selection_dwn;
    // g_mutex_unlock (&mutex);
}

void sw2_button_function (void)
{
    // g_mutex_lock (&mutex);
    // switch_actions = selection_up;
    // g_mutex_unlock (&mutex);
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
