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
#include "Shell_Driver.h"
#include "Hall_Sensor_Driver.h"
#include "HMI_Driver.h"


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
	SYS1_Init();
	RTT1_Init();
	UTIL1_Init();
	LED1_Init();
	LED2_Init();
	LED3_Init();
	AS1_Init();
	CLS1_Init();
	PTC_Init();
	GI2C1_Init();

#if LED_IS_ACTIVE
	LED_Driver_Init();
#endif
#if ION_MOTION_IS_ACTIVE
//	AS1_Init();							//30.04.2017
//	CLS1_Init();						//30.04.2017
	ION_Motion_Driver_Init();
#endif
#if IR_SENSOR_IS_ACTIVE
	IR_Sensor_Driver_Init();
	AdcLdd1_Init();
#endif
#if SHELL_IS_ACTIVE
	AS2_Init();
	CLS2_Init();
	Shell_Driver_Init();
#endif
#if HALL_SENSOR_IS_ACTIVE
	Hall_Sensor_Driver_Init();
#endif
#if HMI_IS_ACTIVE
	HMI_Driver_Init();
#endif
#if FSM_IS_ACTIVE
	FSM_Init();
#endif
	EVNT_Init();
	TMR_Init();
	TRG_Init();
	KEYDBNC_Init();

	EVNT_SetEvent(EVNT_STARTUP);
}
