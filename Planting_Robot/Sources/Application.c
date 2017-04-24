/*
 * Application.c
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */

#include "Application.h"
#include "LED_Driver.h"
#include "IR_Sensor_Driver.h"
#include "ION_Motion_Driver.h"


/*
 * Starting up the Application
 */
void APP_Start(){
	APP_InitComponents();
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
	LED_Driver_Init();
#endif
#if ION_MOTION_TASK_IS_ACTIVE
	ION_Motion_Driver_Init();
#endif
#if IR_SENSOR_TASK_IS_ACTIVE
	IR_Sensor_Driver_Init();
	AdcLdd1_Init();
#endif
}
