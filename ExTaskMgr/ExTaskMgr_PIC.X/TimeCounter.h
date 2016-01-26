/* 
 * Author:     Pedro Bertoleti
 * Description: Header of time counter module
 */


//include guard

#ifndef DISPLAY_H
#define DISPLAY_H

#endif

//prototypes
void RefreshTimeCounter(void);
void InitTimeCounter(void);
void EnableOrDisableTimeCounter(char YesOrNo);


#ifdef DEFTEMPORIZADOR
    #define TEMP extern
#else
    #define TEMP 
#endif

//global variables
TEMP char TimeCounterValue[3];
TEMP char EnableTimeCounter;




