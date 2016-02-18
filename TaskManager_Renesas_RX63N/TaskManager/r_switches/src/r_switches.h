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
* File Name    : r_switches.h
* Version      : 1.00
* Description  : Functions for using switches with callback functions. 
************************************************************************************************************************
* History : DD.MM.YYYY Version Description           
*         : 17.01.2012 1.00    First Release            
***********************************************************************************************************************/

#ifndef SWITCHES_API_HEADER_FILE
#define SWITCHES_API_HEADER_FILE

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Used for configuring the code */
#include "r_switches_config.h"


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Version Number of API. */
#define SWITCHES_VERSION_MAJOR           (1)
#define SWITCHES_VERSION_MINOR           (0)

/***********************************************************************************************************************
Public Functions
***********************************************************************************************************************/
void R_SWITCHES_Init(void);

/* Callback prototypes. */
#if defined(SW1_CALLBACK_FUNCTION)
void SW1_CALLBACK_FUNCTION(void);
#endif

#if defined(SW2_CALLBACK_FUNCTION)
void SW2_CALLBACK_FUNCTION(void);
#endif 

#if defined(SW3_CALLBACK_FUNCTION)
void SW3_CALLBACK_FUNCTION(void);
#endif

#endif /* SWITCHES_API_HEADER_FILE */

