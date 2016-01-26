/* 
 * Author:     Pedro Bertoleti
 * Description: Header of 7-seg display module
 */


//include guard

#ifndef DISPLAY_H
#define DISPLAY_H

#define BCD_B0    RB0
#define BCD_B1    RB1
#define BCD_B2    RB2
#define BCD_B3    RB3

#define DISPLAY_0 RB4
#define DISPLAY_1 RB5
#define DISPLAY_2 RB6

#define SETS_DISPLAY_0 0
#define SETS_DISPLAY_1 1
#define SETS_DISPLAY_2 2

#endif

//prototypes
void WriteDisplay(char Value, char DisplayToWrite) ;
void SetValuesDisplays(char FirstValue, char SecondValue, char ThirdValue);


#ifdef DEFDISPLAY
    #define DISPLAY extern
#else
    #define DISPLAY 
#endif

//global variables
DISPLAY char RecentDisplay;
DISPLAY char DisplayValue[3];



