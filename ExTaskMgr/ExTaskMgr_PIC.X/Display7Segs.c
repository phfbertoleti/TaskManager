/*
 * File:   Dispay7Segs.c
 * Author: Pedro Bertoleti
 * Description: 7-seg display module
 */

#define DEFDISPLAY
#include <xc.h>
#include "Display7Seg.h"

//constants
const char NumerosBCD[10][4]={0,0,0,0,    //0
                              1,0,0,0,    //1
                              0,1,0,0,    //2
                              1,1,0,0,    //3
                              0,0,1,0,    //4
                              1,0,1,0,    //5
                              0,1,1,0,    //6
                              1,1,1,0,    //7
                              0,0,0,1,    //8
                              1,0,0,1};   //9
//local prototypes
void ConvertValue(char Value);


//Function: Writes a value to a specific display
//Params: value (0 - 9) and display to write (0, 1 or 2)
//Return: nothing
void WriteDisplay(char Value, char DisplayToWrite) 
{
    switch(DisplayToWrite)
    {
        case SETS_DISPLAY_0:
        {
            DISPLAY_0 = 1;
            DISPLAY_1 = 0;
            DISPLAY_2 = 0;            
            ConvertValue(Value);
            break;
        }
 
        case SETS_DISPLAY_1:
        {
            DISPLAY_0 = 0;
            DISPLAY_1 = 1;
            DISPLAY_2 = 0;
            ConvertValue(Value);
            break;
        }
    
        case SETS_DISPLAY_2:
        {
            DISPLAY_0 = 0;
            DISPLAY_1 = 0;
            DISPLAY_2 = 1;
            ConvertValue(Value);
            break;
        } 
    }
}

//Function: convert decimal value into BCD. The BCD value will be input of a 4511 IC (BCD - 7segs decoder).
//Params: Value to convert to BCD
//Return: nothing
void ConvertValue(char Value)
{
    if (Value > 9)
        return;
    
    BCD_B0 = NumerosBCD[Value][0];
    BCD_B1 = NumerosBCD[Value][1];
    BCD_B2 = NumerosBCD[Value][2];
    BCD_B3 = NumerosBCD[Value][3];     
}

//Function: Set values of all 7-seg displays
//Params: Value of first, second and third displays.
//Return: nothing
void SetValuesDisplays(char FirstValue, char SecondValue, char ThirdValue)
{
    RecentDisplay = SETS_DISPLAY_0;
    DisplayValue[0] = FirstValue;
    DisplayValue[1] = SecondValue;
    DisplayValue[2] = ThirdValue;
}