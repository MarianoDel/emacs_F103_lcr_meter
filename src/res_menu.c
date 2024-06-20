//----------------------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### RES_MENU.C #########################################
//----------------------------------------------------------

// Includes --------------------------------------------------------------------
#include "res_menu.h"
#include "screen.h"
#include "resistance_meas.h"

#include <stdio.h>
#include <string.h>


// Module Private Types & Macros -----------------------------------------------
typedef enum {
    RES_INIT,
    RES_MEAS,
    RES_WAIT_FREE
    
} res_state_e;

typedef enum {
    RANGE_AUTO,
    RANGE_OHMS,
    RANGE_KOHMS,
    RANGE_MOHMS
    
} range_selection_e;
    

// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------
res_state_e res_state = RES_INIT;
range_selection_e range_selected = RANGE_AUTO;



// Module Private Functions ----------------------------------------------------


// Module Functions ------------------------------------------------------------
void Res_Menu (sw_actions_t actions)
{
    unsigned short res_int = 0;
    unsigned short res_dec = 0;    
    char multiplier = 0;
    resist_meas_e meas_result = RES_MEAS_NONE;
    char buff [40];
    
    switch (res_state)
    {
    case RES_INIT:
	SCREEN_Clear();

	switch (range_selected)
	{
	case RANGE_OHMS:
	    SCREEN_Text2_Line1("Res.  ohms");	    
	    break;

	case RANGE_KOHMS:
	    SCREEN_Text2_Line1("Res. Kohms");	    
	    break;

	case RANGE_MOHMS:
	    SCREEN_Text2_Line1("Res. Mohms");
	    break;

	case RANGE_AUTO:
	default:
	    SCREEN_Text2_Line1("Resistance");
	    break;
	}
	res_state++;
	break;

    case RES_MEAS:
	switch (range_selected)
	{
	case RANGE_OHMS:
	    multiplier = 'o';    // ohms
	    break;

	case RANGE_KOHMS:
	    multiplier = 'k';    // kilo	    
	    break;

	case RANGE_MOHMS:
	    multiplier = 'm';    // mega
	    break;

	case RANGE_AUTO:
	default:
	    multiplier = 'a';    // auto
	    break;
	}
	
	meas_result = Resistance_Meas(&res_int, &res_dec, &multiplier);
	if (meas_result == RES_MEAS_GETTED)
	{
	    sprintf(buff, "%d.%02d%c",
		    res_int,
		    res_dec,
		    multiplier);
	    SCREEN_Text2_BlankLine2();
	    SCREEN_Text2_Line2(buff);
	}
	else if (meas_result == RES_MEAS_TOO_HIGH)
	{
	    SCREEN_Text2_BlankLine2();
	    SCREEN_Text2_Line2("OL.");
	}

	if ((actions == selection_up) ||
	    (actions == selection_dwn))
	{
	    if (range_selected < RANGE_MOHMS)
		range_selected++;
	    else
		range_selected = RANGE_AUTO;

	    res_state = RES_WAIT_FREE;
	}
	break;

    case RES_WAIT_FREE:
	if (actions == do_nothing)
	    res_state = RES_INIT;
	
	break;
	
    default:
	res_state = RES_INIT;
	break;
    }
    
}


//--- end of file ---//
