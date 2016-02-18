#ifndef _HEADERGERAL_H_
#define _HEADERGERAL_H_

//defines do agendamento de tarefas
#define TAREFA_1                 0
#define TAREFA_2                 1
#define TAREFA_3                 2
#define TAREFA_4                 3
#define TAREFA_5                 4
#define TAREFA_6                 5
#define NUMERO_TAREFAS           6
#define PERIODO_EXECUCAO_TAREFA1 500   //tempo em ms
#define PERIODO_EXECUCAO_TAREFA2 1000  //tempo em ms
#define PERIODO_EXECUCAO_TAREFA3 1500  //tempo em ms
#define PERIODO_EXECUCAO_TAREFA4 2000   //tempo em ms
#define PERIODO_EXECUCAO_TAREFA5 150   //tempo em ms
#define PERIODO_EXECUCAO_TAREFA6 200   //tempo em ms
#define TIMEOUT_TAREFA           500   //tempo em ms
#define SIM                      0x01
#define NAO                      0x00

//prorotypes

#endif

#ifdef DEFMAIN
    #define DEFMAIN extern
#else
    #define DEFMAIN
#endif

//variaveis globais
DEFMAIN void (*TarefasAgendadas[NUMERO_TAREFAS])(void);  //armazena os ponteiros para as funções das tarefas a serem executadas
DEFMAIN long PeriodosTarefasAgendadas[NUMERO_TAREFAS];       //armazena a temporização de cada tarefa
DEFMAIN long TemporizacaoAtualTarefas[NUMERO_TAREFAS];       //armazena quantos milisegundos falta pra executar cada tarefa
DEFMAIN long FlagGerouInterrupcaoCMT;   //sinaliza se foi gerada interrupção de Timer CMT
DEFMAIN volatile long HaTarefaEmExecucao;
DEFMAIN long TimeoutTarefa;

