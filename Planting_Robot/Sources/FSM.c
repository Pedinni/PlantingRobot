/*
 * FSM.c
 *
 *		Polls the buttons and creates an event
 *
 *		Created on: 09.05.2017
 *      Author: Patrick
 */

#include "FSM.h"

fsm_state_t fsmState = Init;

void FSM_Init_EventHandler(EVNT_Handle event) {
	/*! \todo handle events */
	switch(event) {
	case EVNT_BTN_9cm_PRESSED:
		setPosition(position_setzeinheit, Topf_9);
		for(int i=0; i<5;i++){
			LED_Driver_setVal(LED_9cm,ON);
			FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
			LED_Driver_setVal(LED_9cm,OFF);
			FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
		}
		LED_Driver_setVal(LED_9cm,ON);

		fsmState = Ready;
		break;
	case EVNT_BTN_9cm_LPRESSED:
		break;

	case EVNT_BTN_11cm_PRESSED:
		break;
	case EVNT_BTN_11cm_LPRESSED:
		break;

	case EVNT_BTN_12cm_PRESSED:
		break;
	case EVNT_BTN_12cm_LPRESSED:
		break;

	case EVNT_BTN_13cm_PRESSED:
		break;
	case EVNT_BTN_13cm_LPRESSED:
		break;

	case EVNT_BTN_14cm_PRESSED:
		break;
	case EVNT_BTN_14cm_LPRESSED:
		break;
	case EVNT_BTN_14cm_RELEASED:
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

static void FSM_Task(void *pvParameters) {
	(void)pvParameters; /* parameter not used */



	for(;;) {
		KEYDBNC_Process();

		switch(fsmState){
		case Init:
			EVNT_HandleEvent(FSM_Init_EventHandler, TRUE);				// Todo: Für jeden case einen anderen Eventhandler??
			break;

		case Ready:
			break;

		case Vereinzelung:
			break;

		case Stechprozess:
			break;

		case Ausloesung:
			break;

		default:
			break;
		}
		FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
	}
}

void FSM_Init(void){
	/* Initialisation of the FSM Task*/
	if (FRTOS1_xTaskCreate(FSM_Task, (signed portCHAR *)"FSM_Task", configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY, (xTaskHandle*)NULL) != pdPASS){
	   for(;;){}; /* Out of heap memory? */
	}
}
