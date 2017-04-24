/*
 * Application.c
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */

#include "Application.h"
#include "LED_Driver.c"
#include "IR_Sensor_Driver.c"
#include "ION_Motion_Driver.c"


/*
 * Starting up the Application
 */
void APP_Start(){
	APP_InitComponents();
	APP_CreateTasks();
	vTaskStartScheduler(); 			// start the RTOS, create the IDLE task and run my tasks (if any)
	__asm volatile("cpsie i");		// Enable Interrupts
}


/*
 * Initializing the defined Components
 */
void APP_InitComponents(void){
	CLS1_Init();
	SYS1_Init();
	RTT1_Init();
	UTIL1_Init();
#if LED_TASK_IS_ACTIVE
	LED1_Init();
#endif
#if IR_SENSOR_TASK_IS_ACTIVE
	AdcLdd1_Init();
#endif

/*	Argument for ADC initialisation?
#if	ION_MOTION_TASK_IS_ACTIVE
	ASerialLdd1_Init();
#endif
*/
}

/*
 * Creating the defined RTOS Tasks
 */
void APP_CreateTasks(void){
#if LED_TASK_IS_ACTIVE
	/* Initialisation of the LED_Driver Task*/
	if (FRTOS1_xTaskCreate(
	    LED_Task,  /* pointer to the task */
	    (signed portCHAR *)"LED_Task", /* task name for kernel awareness debugging */
	    configMINIMAL_STACK_SIZE, /* task stack size */
	    (void*)NULL, /* optional task startup argument */
	    tskIDLE_PRIORITY,  /* initial priority */
	    (xTaskHandle*)NULL /* optional task handle to create */
	   ) != pdPASS)
	{
	   for(;;){}; /* Out of heap memory? */
	}
#endif

#if IR_SENSOR_TASK_IS_ACTIVE
	/* Initialisation of the IR_Sensor_Driver Task*/
		if (FRTOS1_xTaskCreate(
		    IR_Sensor_Task,  /* pointer to the task */
		    (signed portCHAR *)"IR_Sensor_Task", /* task name for kernel awareness debugging */
		    configMINIMAL_STACK_SIZE, /* task stack size */
		    (void*)NULL, /* optional task startup argument */
		    tskIDLE_PRIORITY,  /* initial priority */
		    (xTaskHandle*)NULL /* optional task handle to create */
		   ) != pdPASS)
		{
		   for(;;){}; /* Out of heap memory? */
		}
#endif

#if ION_MOTION_TASK_IS_ACTIVE
	/* Initialisation of the IR_Sensor_Driver Task*/
		if (FRTOS1_xTaskCreate(
				ION_Motion_Task,  /* pointer to the task */
		    (signed portCHAR *)"ION_Motion_Task", /* task name for kernel awareness debugging */
		    configMINIMAL_STACK_SIZE, /* task stack size */
		    (void*)NULL, /* optional task startup argument */
		    tskIDLE_PRIORITY,  /* initial priority */
		    (xTaskHandle*)NULL /* optional task handle to create */
		   ) != pdPASS)
		{
		   for(;;){}; /* Out of heap memory? */
		}
#endif


}

