/*
 * Principal.c
 * Autor: Pedro Bertoleti
 * Data: Jan/2016
 * Description: 
 * This software is a task manager for 8-bit PIC microcontrollers.
 * WARNING: be careful when programming the tasks. Tasks must be as fast as possible (due to real-time features of this task manager)
 */

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = XT 
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

//General defines
#define _XTAL_FREQ                 4000000      //clock frequency: 4MHz

#define MACHINE_CYCLE              (4/_XTAL_FREQ)   //In 8-bit PICs (at least, in 16F series ones), one instruction is executed only after 4 machine/clock cycles.
#define YES                        1
#define NO                         0
#define TIMER0_INIT_VALUE          131

//Tasks scheduling defines
#define INDEX_TAREFA_1                 0
#define INDEX_TAREFA_2                 1
#define INDEX_TAREFA_3                 2
#define INDEX_TAREFA_4                 3
#define NUMBER_OF_TASKS                4
#define TIME_TO_EXECUTE_TASK1          200   //time unit: ms
#define TIME_TO_EXECUTE_TASK2          1000  //time unit: ms
#define TIME_TO_EXECUTE_TASK3          1000  //time unit: ms
#define TIME_TO_EXECUTE_TASK4          100   //time unit: ms
#define TASK_TIMEOUT                   500   //time unit: ms

//Global variables
void (*ScheduledTasks[NUMBER_OF_TASKS])(void);  //It stores the function pointers of Task.
int TimeScheduledTasks[NUMBER_OF_TASKS];        //It stores the task큦 times (time period to execute)
int RecentTasksTimeToExecute[NUMBER_OF_TASKS];  //It stores the recent task큦 times ("time to execute" each task)
char Timer0IntGeneraed;                         //It indicates if a TImer0 interrupt has been generated
volatile char TaskIsExecuting;                  //It indicated if a task in executing (important information for consider task timeout validation)
int TaskTimeout;

//prototypes: 
//1-General functions
void ConfigTimer0(void);
void InitTasks(void);
void ExecuteTask(void);

//2-Tasks functions (each task has its own function)
void Task1(void);
void Task2(void);
void Task3(void);
void Task4(void);

/*
 *  Implementation
 */

//Function: Configures Timer0 registers
//Params: nothing
//Return: nothing
void ConfigTimer0(void)
{
    //To understand Timer0 calculations and values, read the following instructions: 
    //- PIC큦 Timer0 has 8-bits, so its counter range (TMR0 register) is from 00h to FFh.
    //- In this specific case, a 1:8 Pre-scaler is used. So, in the following calculation, preScaler = 8
    //- On 8-bit PIC microcontrollers, one instruction is executed only after 4 machine cycles. So, the "real software clock" is 1/4 of input clock frequency. It means:
    //   TimeCycleMachine = 4*CycleOsc = 4*(1/Fosc) =  4 / Fosc  
    //- The time to generate Timer0 interrupt is calculated by:
    //  Toverflow = 256 * TimeCycleMachine * preScaler  (256 = FFh, value of TMR0 when generated Timer0 interrupt)
    // What means: Toverflow_max = 256 * 0,000001 * 8 = 2,048ms
    // 
    // We need 1ms to generate Timer0 Interrupt. What implies:
    // 0,001 = (256-TMR0) * 0,000001 * 8 -> TMR0 = 131
    
    
    OPTION_REGbits.PS = 0b010; //configs pre-scaler for 1:8
    OPTION_REGbits.PSA = 0;    //It indicates that Timer0 is used as Timer (it can be used as counter, timer ou dedicated to WatchDog Timer)
    OPTION_REGbits.T0CS=0;     //It sets Timer0 clock as input microcontroller clock
    INTCONbits.TMR0IE =1;      //Enable Timer0 interrupt
    INTCONbits.GIE=1;          //Enable ALL interrupts (it큦 necessary when working with interrupt on 16F PIC series)
    TMR0 = TIMER0_INIT_VALUE;  //Set initial value of TMR0 register (for counting 1ms, as we need)
    Timer0IntGeneraed = NO;    
}

//Function: initialize and schedule tasks
//Params: nothing
//Return: nothing
void InitTasks(void)
{
	//init function pointers of tasks
	ScheduledTasks[INDEX_TAREFA_1] = Task1;
	ScheduledTasks[INDEX_TAREFA_2] = Task2;
	ScheduledTasks[INDEX_TAREFA_3] = Task3;
    ScheduledTasks[INDEX_TAREFA_4] = Task4;
	
	//init temporization values of each task. These values do no change during execution
	TimeScheduledTasks[INDEX_TAREFA_1] = TIME_TO_EXECUTE_TASK1;
	TimeScheduledTasks[INDEX_TAREFA_2] = TIME_TO_EXECUTE_TASK2;
	TimeScheduledTasks[INDEX_TAREFA_3] = TIME_TO_EXECUTE_TASK3;
    TimeScheduledTasks[INDEX_TAREFA_4] = TIME_TO_EXECUTE_TASK4;
	
	//init recent temporization values of each task. These values will change during execution (they큥e used to decide which task must be executed)
	RecentTasksTimeToExecute[INDEX_TAREFA_1] = TIME_TO_EXECUTE_TASK1;
	RecentTasksTimeToExecute[INDEX_TAREFA_2] = TIME_TO_EXECUTE_TASK2;
	RecentTasksTimeToExecute[INDEX_TAREFA_3] = TIME_TO_EXECUTE_TASK3;	
    RecentTasksTimeToExecute[INDEX_TAREFA_4] = TIME_TO_EXECUTE_TASK4;	
    
    //It indicates that there큦 no task executing
    TaskIsExecuting = NO;
}

//Function: Execute tasks
//Params: nothing
//Return: nothing
void ExecuteTask(void)
{
    char i;
	for (i=0; i<NUMBER_OF_TASKS; i++)
	{
		//Check if it큦 time to execute a task
		if ((ScheduledTasks[i] != 0) && (RecentTasksTimeToExecute[i] == 0))
        {
			TaskIsExecuting = YES;
            TaskTimeout = TASK_TIMEOUT;
            ScheduledTasks[i]();  //executes the task
            TaskIsExecuting = NO;
			RecentTasksTimeToExecute[i] = TimeScheduledTasks[i];  //reagendamento da tarefa
		}
	}
}

//Function: Task 1 function
//Params: nothing
//Return: nothing
void Task1(void)
{
    
}

//Function: Task 2 function
//Params: nothing
//Return: nothing
void Task2(void)
{
    
}

//Function: Task 3 function
//Params: nothing
//Return: nothing
void Task3(void)
{
    
}

//Function: Task 4 function
//Params: nothing
//Return: nothing
void Task4(void)
{
    
}

//Function: handle interrupts (every PIC interrupt will call this function, so inside it it큦 need to filter which one must be handled)
//Params: nothing
//Return: nothing
void interrupt isr(void)
{
    char  i;
	
    //check if Timer0 interupt was triggered
	if (TMR0IF && T0IF)   
    {
        Timer0IntGeneraed = YES;
		
		//Refresh "time to execute" of each task        
		for (i=0; i<NUMBER_OF_TASKS; i++)
		{
			if (RecentTasksTimeToExecute[i] > 0)
				RecentTasksTimeToExecute[i]--;			
		}
			
        if (TaskIsExecuting == YES)
        {
            TaskTimeout--;
            
            if (!TaskTimeout)
            {
                //Timeout has reached (possibly a task has crashed. Microcontroller must be reset)
                PCLATH=0;    
                PCL=0;                    
            }
        }
        
		T0IF = 0;                 //set trigger for Timer0 interrupt (so it can be generated again)
        INTCONbits.TMR0IF = 0;   
        TMR0 = TIMER0_INIT_VALUE; //Set initial value of TMR0 register (for counting 1ms, as we need)
    }   
}

/*
 *  Main function
 */
void main(void) 
{
	/*
     * example of input and output configuration. It can be changed according to what you need
     */
    TRISB = 0x00;            //configures all bits of PORTB as outputs
    PORTB = 0;               //sets all portb큦 outputs to 0    
    TRISA = 0xFF;            //configures all bits of PORTA as inputs
    
    //init tasks and config Timer0
    InitTasks();   
	ConfigTimer0();
    
	//main loop 
    while(1)                      
    {
        //Verification: check if there큦 a task to be executed
        if ((Timer0IntGeneraed == YES)  && (NUMBER_OF_TASKS)) 
        {
            Timer0IntGeneraed = NO;  
            ExecuteTask();			
        }
    }
}
