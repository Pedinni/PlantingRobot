/*
 * HMI_Driver.c
 *
 *		Polls the buttons and creates an event
 *
 *		Created on: 30.04.2017
 *      Author: Patrick
 */


#include "HMI_Driver.h"


void APP_EventHandler(EVNT_Handle event) {
	/*! \todo handle events */
	switch(event) {
	case EVNT_STARTUP:
	{
		int i;
		for (i=0;i<5;i++) {
			LED1_Neg();
			WAIT1_Waitms(50);
		}
		LED1_Off();
		break;
	}
	case EVNT_BTN_9cm_PRESSED:
		LED1_On();
		break;
	case EVNT_BTN_11cm_PRESSED:
		LED1_Off();
		break;
	case EVNT_BTN_12cm_PRESSED:

		break;
	case EVNT_BTN_13cm_PRESSED:

		break;
	case EVNT_BTN_14cm_PRESSED:

		break;
	case EVNT_BTN_AUTO_PRESSED:

		break;
	case EVNT_BTN_Setzeinheit_runter_PRESSED:

		break;
	case EVNT_BTN_Setzeinheit_hoch_PRESSED:

		break;
	case EVNT_BTN_Vereinzelung_PRESSED:

		break;
	case EVNT_BTN_hoeher_PRESSED:

		break;
	case EVNT_BTN_tiefer_PRESSED:

		break;
    default:
    	break;
   } /* switch */
}

static void HMI_Task(void *pvParameters) {
	(void)pvParameters; /* parameter not used */

	for(;;) {
		KEYDBNC_Process();
		EVNT_HandleEvent(APP_EventHandler, TRUE);
		FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
	}
}

void HMI_Driver_Init(void){
	/* Initialisation of the HMI_Driver Task*/
	if (FRTOS1_xTaskCreate(HMI_Task, (signed portCHAR *)"HMI_Task", configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY, (xTaskHandle*)NULL) != pdPASS){
	   for(;;){}; /* Out of heap memory? */
	}
}
