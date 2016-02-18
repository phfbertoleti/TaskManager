/******************************************
 * Módulo do cotnrole de timer CMT0
 * Autor: Pedro Bertoleti
 * Data: 02/2016
 *
 * Baseado no arquivo CMT.c original.
 ******************************************/

#include <stdint.h>
#include <stdio.h>
#include "platform.h"
#include "cmt.h"
#include "s12adc.h"
#include "HeaderGeral.h"


/******************************************************************************
Defines gerais
*******************************************************************************/
//Configura ticks de 1ms
#define TICK_INTERVAL (48000000 / 128 / 1000) // 375

/*******************************************************************************
* Função: CMT_init
* Descrição  : Configura timer CMT0 para gerar interrupções a cada 100ms
* Parâmetros: nenhum
* Retorno: nenhum
*
* Função original do exemplo ADC_Repeat
*******************************************************************************/
void CMT_init (void)
{
	FlagGerouInterrupcaoCMT = NAO;

#ifdef PLATFORM_BOARD_RDKRX63N
	SYSTEM.PRCR.WORD = 0xA50B; /* Protect off */
#endif

    /* Power up CMT0 */
    MSTP(CMT0) = 0;   
     
#ifdef PLATFORM_BOARD_RDKRX63N
	SYSTEM.PRCR.WORD = 0xA500; /* Protect on  */
#endif  

    /* Stop the clock */
    CMT.CMSTR0.BIT.STR0 = 0;

    /* Trigger 100 ms from now */
    CMT0.CMCOR = CMT0.CMCNT + TICK_INTERVAL;
    
    /* CMCR - Compare Match Timer Control Register
    b6      CMIE: 1 = Compare match interrupt (CMIn) enabled
    b1:b0   CKS:  2 = Clock selects is PCLK/128 (375 kHz @ PCLK = 48 MHz) 
    */
    CMT0.CMCR.WORD = 0x0042;
    
    /* Set interrupt priority in ICU */
    IPR(CMT0, CMI0) = 0x01;
    
    /* Enable the interrupt in the ICU */
    IEN(CMT0, CMI0) = 1;
    
    /* Start the clock running */ 
    CMT.CMSTR0.BIT.STR0 = 1;
} /* End of function CMT_init() */

/*******************************************************************************
* Function name: CMT_isr
* Description  : Função de tratamento de interrupção
* Parâmetros: nenhum
* Retorno : nenhum
*******************************************************************************/
#pragma interrupt (CMT_isr(vect=VECT(CMT0,CMI0)))
void CMT_isr (void)
{
	long i;

	FlagGerouInterrupcaoCMT = SIM;

	//atualiza a temporização de cada uma das tarefas
    for (i=0; i<NUMERO_TAREFAS; i++)
	{
		if (TemporizacaoAtualTarefas[i] > 0)
			TemporizacaoAtualTarefas[i]--;
	}
}
