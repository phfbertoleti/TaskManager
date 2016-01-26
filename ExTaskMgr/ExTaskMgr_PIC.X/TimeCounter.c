/*
 * File:   TimeCounter.c
 * Author: Pedro Bertoleti
 * Description: Time counter module
 */

#define DEFTEMPORIZADOR
#include <xc.h>
#include "TimeCounter.h"


//Function: init time counter
//Parms: nothing
//Return: nothing
void InitTimeCounter(void)
{
    TimeCounterValue[0] = 0;
    TimeCounterValue[1] = 0;
    TimeCounterValue[2] = 0;
}

//Function: Refresh time counter
//Parms: nothing
//Return: nothing
void RefreshTimeCounter(void)
{
    if (!EnableTimeCounter)
        return;
    
    TimeCounterValue[2]++;
    
    if (TimeCounterValue[2] > 9)
    {
        TimeCounterValue[2] = 0;
        TimeCounterValue[1]++;
    }
    
    if (TimeCounterValue[1] > 9)
    {
        TimeCounterValue[1] = 0;
        TimeCounterValue[0]++;
    }
    
    if (TimeCounterValue[0] > 9)
        InitTimeCounter();    
}



//Function: enable or disable time counter
//Parms: nothing
//Return: nothing
void EnableOrDisableTimeCounter(char YesOrNo)
{
    EnableTimeCounter = YesOrNo;
}
