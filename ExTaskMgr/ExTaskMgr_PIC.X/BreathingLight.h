/* 
 * Author:     Pedro Bertoleti
 * Description: Header of breathing light module
 */


//include guard

#ifndef BREATHINGLIGHT_H
#define BREATHINGLIGHT_H

#define BREATHINGLIGHT RB7

#endif

//prototypes
void RefreshBreathingLight(void);


#ifdef DEFBREATHINGLIGHT
    #define BLIGHT extern
#else
    #define BLIGHT 
#endif




