/******************************************
 * Exemplo de aplicação de um Task Manager
 * Autor: Pedro Bertoleti
 * Data: 02/2016
 ******************************************/
#define DEFMAIN

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <machine.h>
#include "platform.h"
#include "HeaderGeral.h"
#include "cmt.h"
#include "s12adc.h"

//variaveis locais:
long ToogleLinha1;
long ToogleLinha2;
long ToogleLinha3;
long ToogleLinha4;

//prototypes locais:
void InicializaVariaveisGlobaisEOutputs(void);
void InicializaHardware(void);
void InicializaTarefas(void);
void Tarefa1(void);
void Tarefa2(void);
void Tarefa3(void);
void Tarefa4(void);
void Tarefa5(void);
void Tarefa6(void);

/******************************************************************************
* Função: InicializaVariaveisGlobais
* Descrição  : Inicializa todas as variáveis globais e outputs usados
* Parâmetros    : nenhum
* Retorno : nenhum
*******************************************************************************/
void InicializaVariaveisGlobaisEOutputs(void)
{
	ToogleLinha1=0;
    ToogleLinha2=0;
    ToogleLinha3=0;
    ToogleLinha4=0;

    LED4 = 0;
    LED5 = 1;
    LED6 = 0;
    LED7 = 1;
    LED8 = 0;
    LED9 = 1;
    LED10 = 0;
    LED11 = 1;
    LED12 = 0;
    LED13= 1;
    LED14= 0;
    LED15= 1;
}

/******************************************************************************
* Função: InicializaHardware
* Descrição  : Inicializa todos os periféricos de hardware utilizados
* Parâmetros    : nenhum
* Retorno : nenhum
*******************************************************************************/

void InicializaHardware(void)
{
	S12ADC_init();
	S12ADC_start();
    lcd_initialize();
    lcd_clear();
}

/******************************************************************************
* Função: InicializaTarefas
* Descrição  : Inicializa todas as tarefas e suas temporizações
* Parâmetros    : nenhum
* Retorno : nenhum
*******************************************************************************/
void InicializaTarefas(void)
{
	//inicialização das tarefas
	TarefasAgendadas[TAREFA_1] = Tarefa1;
	TarefasAgendadas[TAREFA_2] = Tarefa2;
	TarefasAgendadas[TAREFA_3] = Tarefa3;
    TarefasAgendadas[TAREFA_4] = Tarefa4;
    TarefasAgendadas[TAREFA_5] = Tarefa5;
    TarefasAgendadas[TAREFA_6] = Tarefa6;

	//inicialização das temporizações
	PeriodosTarefasAgendadas[TAREFA_1] = PERIODO_EXECUCAO_TAREFA1;
	PeriodosTarefasAgendadas[TAREFA_2] = PERIODO_EXECUCAO_TAREFA2;
	PeriodosTarefasAgendadas[TAREFA_3] = PERIODO_EXECUCAO_TAREFA3;
    PeriodosTarefasAgendadas[TAREFA_4] = PERIODO_EXECUCAO_TAREFA4;
    PeriodosTarefasAgendadas[TAREFA_5] = PERIODO_EXECUCAO_TAREFA5;
    PeriodosTarefasAgendadas[TAREFA_6] = PERIODO_EXECUCAO_TAREFA6;

	//inicializaçãop da temporização atual (esta variará ao longo do programa)
	TemporizacaoAtualTarefas[TAREFA_1] = PERIODO_EXECUCAO_TAREFA1;
	TemporizacaoAtualTarefas[TAREFA_2] = PERIODO_EXECUCAO_TAREFA2;
	TemporizacaoAtualTarefas[TAREFA_3] = PERIODO_EXECUCAO_TAREFA3;
    TemporizacaoAtualTarefas[TAREFA_4] = PERIODO_EXECUCAO_TAREFA4;
    TemporizacaoAtualTarefas[TAREFA_5] = PERIODO_EXECUCAO_TAREFA5;
    TemporizacaoAtualTarefas[TAREFA_6] = PERIODO_EXECUCAO_TAREFA6;

    //sinaliza que não ha tarefas em execução ainda
    HaTarefaEmExecucao = NAO;
}

/******************************************************************************
* Função: Tarefa1
* Descrição  : Função da primeira tarefa
* Parâmetros    : nenhum
* Retorno : nenhum
*******************************************************************************/
void Tarefa1(void)
{
	ToogleLinha1 = ~ToogleLinha1;

	if (ToogleLinha1)
		lcd_display(LCD_LINE1, "TASK  500ms ");
	else
		lcd_display(LCD_LINE1, "            ");
}

/******************************************************************************
* Função: Tarefa2
* Descrição  : Função da segunda tarefa
* Parâmetros    : nenhum
* Retorno : nenhum
*******************************************************************************/
void Tarefa2(void)
{
	ToogleLinha2 = ~ToogleLinha2;

	if (ToogleLinha2)
		lcd_display(LCD_LINE2, "TASK 1000ms ");
	else
		lcd_display(LCD_LINE2, "            ");
}

/******************************************************************************
* Função: Tarefa3
* Descrição  : Função da terceira tarefa
* Parâmetros    : nenhum
* Retorno : nenhum
*******************************************************************************/
void Tarefa3(void)
{
	ToogleLinha3 = ~ToogleLinha3;

	if (ToogleLinha3)
		lcd_display(LCD_LINE3, "TASK 1500ms ");
	else
		lcd_display(LCD_LINE3, "            ");
}

/******************************************************************************
* Função: Tarefa4
* Descrição  : Função da quarta tarefa
* Parâmetros    : nenhum
* Retorno : nenhum
*******************************************************************************/
void Tarefa4(void)
{
	ToogleLinha4 = ~ToogleLinha4;

	if (ToogleLinha4)
		lcd_display(LCD_LINE4, "TASK 2000ms ");
	else
		lcd_display(LCD_LINE4, "            ");
}

/******************************************************************************
* Função: Tarefa5
* Descrição  : Função da quinta tarefa
* Parâmetros    : nenhum
* Retorno : nenhum
*******************************************************************************/
void Tarefa5(void)
{
	uint16_t LeituraADC;
	char LeituraADCString[10];

	LeituraADC = S12ADC_read();
	sprintf(LeituraADCString,"ADC: %04ld",LeituraADC);
	lcd_display(LCD_LINE6, LeituraADCString);
}

/******************************************************************************
* Função: Tarefa6
* Descrição  : Função da sexta tarefa
* Parâmetros    : nenhum
* Retorno : nenhum
*******************************************************************************/
void Tarefa6(void)
{
	LED4 = ~LED4;
	LED5 = ~LED5;
	LED6 = ~LED6;
	LED7 = ~LED7;
	LED8 = ~LED8;
	LED9 = ~LED9;
	LED10 = ~LED10;
	LED11 = ~LED11;
	LED12 = ~LED12;
	LED13= ~LED13;
	LED14= ~LED14;
	LED15= ~LED15;
}


/******************************************************************************
* Função: ExecutaTarefa
* Descrição  : Executa tarefas agendadas na temporização setada
* Parâmetros    : nenhum
* Retorno : nenhum
*******************************************************************************/
void ExecutaTarefa(void)
{
    long i;

	for (i=0; i<NUMERO_TAREFAS; i++)
	{
		//se deve executar, realiza a execução e reinicia temporização
		if ((TarefasAgendadas[i] != 0) && (TemporizacaoAtualTarefas[i] == 0))
        {
			HaTarefaEmExecucao = SIM;
            TarefasAgendadas[i]();  //execução da tarefa
            HaTarefaEmExecucao = NAO;
			TemporizacaoAtualTarefas[i] = PeriodosTarefasAgendadas[i];  //reagendamento da tarefa
		}
	}
}



/******************************************************************************
* Função: main
* Descrição  : Função / programa principal
* Parâmetros    : nenhum
* Retorno : nenhum
*******************************************************************************/
void main(void)
{
	char ValorDisplay[10];

	//inicializa as tarefas e suas temporizações
	InicializaTarefas();

	//inicializa variáveis globais
	InicializaVariaveisGlobaisEOutputs();

    //inicialização de periféricos de hardware
    InicializaHardware();

    //Inicializa Timer CMT0
    CMT_init();
    
    //Loop principal
    while (1)
    {
    	if ((FlagGerouInterrupcaoCMT == SIM)  && (NUMERO_TAREFAS))
    	{
    		FlagGerouInterrupcaoCMT = NAO;
    		ExecutaTarefa();
    	}
    }
}
