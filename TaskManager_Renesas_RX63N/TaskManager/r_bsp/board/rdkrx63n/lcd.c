/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer 
*
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.    
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name	   : lcd.c
* Version      : 1.0 
* Device(s)    : RX
* H/W Platform : YRDKRX63N
* Description  : LCD Module utility functions. Written for RDK Okaya graphic LCD.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 26.10.2011 1.00     First Release
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Processor-specific details */
#include <machine.h>
/* Standard string manipulation & formatting functions */
#include <stdio.h>
#include <string.h>
/* Defines standard variable types used in this function */
#include <stdint.h>
/* Board includes. */
#include "platform.h"
/* Following header file provides function prototypes for LCD controlling functions & macro defines */
#include "lcd.h"
/* Graphics library support */
#include "glyph.h"
/* RSPI package. */
#include "r_rspi_rx600.h"

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
T_glyphHandle lcd_handle;

/***********************************************************************************************************************
* Function name : lcd_initialize
* Description   : Initializes the LCD display. 
* Arguments     : none
* Return Value  : none
***********************************************************************************************************************/
void lcd_initialize(void)
{
    /* Initialize RSPI channel */
    R_RSPI_Init(RSPI_CHANNEL_0);    
    
    if (GlyphOpen(&lcd_handle, 0) == GLYPH_ERROR_NONE)
    {
        /* use Glyph full access direct functions */
        GlyphNormalScreen(lcd_handle);
        GlyphSetFont(lcd_handle, GLYPH_FONT_8_BY_8);
        GlyphClearScreen(lcd_handle);
    }
}

/***********************************************************************************************************************
* Function name : lcd_clear
* Description   : Clears the LCD
* Arguments     : none
* Return Value  : none
***********************************************************************************************************************/
void lcd_clear(void)
{
    GlyphClearScreen(lcd_handle);
}

/***********************************************************************************************************************
* Function name : lcd_display
* Description   : This function controls the LCD writes.
*                 The display supports 8 lines with up to 12 characters per line. Use the defines LCD_LINE1 to 
*                 LCD_LINE8 to specfify the starting position.
*                 For example, to start at the 4th position on line 1:
*                     lcd_display(LCD_LINE1 + 4, "Hello")
* Arguments     : position - 
*                     Line number of display
*                 string - 
*                     Pointer to null terminated string
* Return Value  : none
***********************************************************************************************************************/
void lcd_display(uint8_t position, const uint8_t * string)
{
    uint8_t y = position - (position % 8);
    uint8_t xOffset = (position % 8)<<3;

    /* Draw text lines, 8 pixels high, 96 pixels wide */
    /* Clear the rectangle of this line */
    GlyphEraseBlock(lcd_handle, xOffset, y, (95 - xOffset), y+7);
    GlyphSetXY(lcd_handle, xOffset, y);
    GlyphString(lcd_handle, (uint8_t *)string, strlen((void *)string));

}
