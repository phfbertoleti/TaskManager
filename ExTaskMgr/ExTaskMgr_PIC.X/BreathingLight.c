/*
 * File:   Dispay7Segs.c
 * Author: Pedro Bertoleti
 * Description:  breathing light module
 */

#define DEFBREATHINGLIGHT
#include <xc.h>
#include "BreathingLight.h"

//Function: refresh breathing light
//Params: nothing
//Return: nothing
void RefreshBreathingLight(void) 
{
    BREATHINGLIGHT = ~BREATHINGLIGHT;
}
