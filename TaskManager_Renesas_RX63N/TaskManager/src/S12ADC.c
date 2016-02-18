/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer *
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.    
*******************************************************************************/
/*******************************************************************************
* File Name     : S12ADC.C
* Version       : 1.0
* H/W Platform  : YRDKRX63N
* Description   : Simple driver for the S12ADC (12-bit A/D converter)
*                 This implementation sets up S12ADC in continuous-scan mode.
*                 It scans AN002 only. 
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY     Version     Description
*         : 16.02.2012     1.00        First release
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "platform.h"
#include "s12adc.h"

/*******************************************************************************
* Function name: S12ADC_init
* Description  : Sets up S12ADC in continuous scan mode.
*                The potentiometer on the YRDKRX63N board is connected to AN002.
* Arguments    : none
* Return value : none
*******************************************************************************/
void S12ADC_init (void)
{
#ifdef PLATFORM_BOARD_RDKRX63N
	SYSTEM.PRCR.WORD = 0xA50B; /* Protect off */
#endif

    /* Power up the S12ADC */
    MSTP(S12AD) = 0;
    
    /* Set up the I/O pin that will be used as analog input source. In this 
       demo the potentiometer will be used and is connected to port 42. */
    PORT4.PODR.BIT.B2 = 0;    /* Clear I/O pin data register to low output. */
    PORT4.PDR.BIT.B2  = 0;    /* Set I/O pin direction to input. */
    PORT4.PMR.BIT.B2  = 0;    /* First set I/O pin mode register to GPIO mode. */    
    MPC.P42PFS.BYTE = 0x80;   /* Set port function register to analog input, no interrupt. */    
        
#ifdef PLATFORM_BOARD_RDKRX63N
	SYSTEM.PRCR.WORD = 0xA500; /* Protect on  */
#endif  
    
    /* ADCSR: A/D Control Register  
    b7    ADST     0 a/d conversion start, Stop a scan conversion process
    b6    ADCS     1 Scan mode select, Continuous scan mode
    b5    Reserved 0 This bit is always read as 0. The write value should always be 0.
    b4    ADIE     0 Disables conversion complete IRQ to ICU
    b3:b2 CKS      0 A/D conversion clock select = PCLK/8
    b1    TRGE     0 Disables conversion to start w/ trigger
    b0    EXTRG    0 Trigger select, Scan conversion start by a timer source or software
	*/
    S12AD.ADCSR.BYTE = 0x40;

    /* ADANS0: A/D Channel Select Register 0
    b15:b0  ANS0: Selects analog inputs of the channels AN000 to AN015 that are 
    subjected to A/D conversion
    */
    S12AD.ADANS0.WORD = 0x0004; /* Read AN002, which is connected to the potentiometer */

    /* ADANS1: A/D Channel Select Register 1
	b15:b5  Reserved: These bits are always read as 0. 
                      The write value should always be 0.
    b4:b0   ANS1:     Selects analog inputs of the channels AN016 to AN020 
                      that are subjected to A/D conversion
    */
    S12AD.ADANS1.WORD = 0x0000;

    /* ADADS0: A/D-converted Value Addition Mode Select Register 0
    b15:b0  ADS0: A/D-Converted Value Addition Channel Select for AN000 to AN015.
    */
    S12AD.ADADS0.WORD = 0x0000;

    /* ADADS1: A/D-converted Value Addition Mode Select Register 1
	b15:b5  Reserved: These bits are always read as 0. The write value should always be 0.
    b4:b0   ADS1: A/D-Converted Value Addition Channel Select for AN016 to AN020.
    */
    S12AD.ADADS1.WORD = 0x0000;

    /* ADADC: A/D-Converted Value Addition Count Select Register
    b1:b0   ADC: 00 = 1 time conversion (same as normal conversion)
    */
    S12AD.ADADC.BYTE = 0x00;   /* 1-time conversion */

    /* ADCER: A/D Control Extended Register
    b15     ADRFMT:0  Right align the data in the result registers
    b5      ACE:0 Disables automatic clearing of ADDRn after it is read
    */
    S12AD.ADCER.WORD = 0x0000;   /* Right align data, automatic clearing off. */

    /* ADSTRGR: A/D Start Triggger Select Register
    b7:b4   Reserved. Always read/write 0.
    b3:b0   ADSTRS: 0, Software trigger or ADTRG0#
    */
    S12AD.ADSTRGR.BYTE = 0x00;
    
} /* End of function S12ADC_init() */


/*******************************************************************************
* Function name: S12ADC_start
* Description  : Starts the ADC converter.  It will run continuously.
* Arguments    : none
* Return value : none
*******************************************************************************/
void S12ADC_start (void)
{
    /* Start the A/D converter */
    S12AD.ADCSR.BIT.ADST = 1;
    
} /* End of function S12ADC_start() */


/*******************************************************************************
* Function name: S12ADC_read
* Description  : Reads the results register for channel AN002 of the S12ADC
* Arguments    : none
* Return value : uint16_t - 
*                   the ADC conversion value
*******************************************************************************/
uint16_t S12ADC_read (void)
{
    uint16_t adc_result;
    
    adc_result = S12AD.ADDR2;        /* Read the result register for AN2 */
    
    return adc_result;
        
} /* End of function S12ADC_read() */

/*******************************************************************************
End of file s12adc.c
*******************************************************************************/


