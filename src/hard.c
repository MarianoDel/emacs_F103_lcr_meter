//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### HARD.C ################################
//---------------------------------------------

// Includes --------------------------------------------------------------------
#include "hard.h"
#include "stm32f10x.h"


// Module Private Types Constants and Macros -----------------------------------
#define SWITCHES_TIMER_RELOAD    10
#define SWITCHES_THRESHOLD_FULL    300    // 3 secs.
#define SWITCHES_THRESHOLD_HALF    100    // 1 sec
#define SWITCHES_THRESHOLD_MIN    5    // 50 ms



// Externals -------------------------------------------------------------------



// Globals ---------------------------------------------------------------------
volatile unsigned char switches_timer = 0;
unsigned short s1 = 0;
unsigned short s2 = 0;


// Module Functions ------------------------------------------------------------
void Hard_Timeouts (void)
{
    if (switches_timer)
	switches_timer--;
}


void Hard_UpdateSwitches (void)
{
    //revisa los switches cada 10ms o cada SWITCHES_TIMER_RELOAD
    if (!switches_timer)
    {
        if (S1_PIN)
            s1++;
        else if (s1 > 50)
            s1 -= 50;
        else if (s1 > 10)
            s1 -= 5;
        else if (s1)
            s1--;

        if (S2_PIN)
            s2++;
        else if (s2 > 50)
            s2 -= 50;
        else if (s2 > 10)
            s2 -= 5;
        else if (s2)
            s2--;

        switches_timer = SWITCHES_TIMER_RELOAD;
    }
}


switch_state_t Hard_CheckS1 (void)	//cada check tiene 10ms
{
    if (s1 > SWITCHES_THRESHOLD_FULL)
        return S_FULL;

    if (s1 > SWITCHES_THRESHOLD_HALF)
        return S_HALF;

    if (s1 > SWITCHES_THRESHOLD_MIN)
        return S_MIN;

    return S_NO;
}


switch_state_t Hard_CheckS2 (void)
{
    if (s2 > SWITCHES_THRESHOLD_FULL)
        return S_FULL;

    if (s2 > SWITCHES_THRESHOLD_HALF)
        return S_HALF;

    if (s2 > SWITCHES_THRESHOLD_MIN)
        return S_MIN;

    return S_NO;
}


//---- end of file ----//
