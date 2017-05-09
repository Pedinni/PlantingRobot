/*
 * FSM.c
 *
 *		Polls the buttons and creates an event
 *
 *		Created on: 09.05.2017
 *      Author: Patrick
 */

#include "FSM.h"

void FSM_EventHandler(EVNT_Handle event) {
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
		ION_Motion_Relais_SetVal();
		break;
	}
	case EVNT_BTN_9cm_PRESSED:
		LED_Driver_setVal(LED_9cm,ON);
		break;
	case EVNT_BTN_9cm_LPRESSED:
		LED_Driver_setVal(LED_9cm,OFF);

	case EVNT_BTN_11cm_PRESSED:
		LED_Driver_setVal(LED_11cm,ON);
		break;
	case EVNT_BTN_11cm_LPRESSED:
		LED_Driver_setVal(LED_11cm,OFF);
		break;

	case EVNT_BTN_12cm_PRESSED:
		LED_Driver_setVal(LED_12cm,ON);
		break;
	case EVNT_BTN_12cm_LPRESSED:
		LED_Driver_setVal(LED_12cm,OFF);
		break;

	case EVNT_BTN_13cm_PRESSED:
		LED_Driver_setVal(LED_13cm,ON);
		break;
	case EVNT_BTN_13cm_LPRESSED:
		LED_Driver_setVal(LED_13cm,OFF);
		break;

	case EVNT_BTN_14cm_PRESSED:
		LED_Driver_setVal(LED_14cm,ON);
		break;
	case EVNT_BTN_14cm_LPRESSED:
		break;
	case EVNT_BTN_14cm_RELEASED:
		LED_Driver_setVal(LED_14cm,OFF);
		break;

	case EVNT_BTN_AUTO_PRESSED:
		LED_Driver_setVal(LED_AUTO,ON);
		break;

	case EVNT_BTN_Setzeinheit_runter_PRESSED:
		LED_Driver_setVal(LED_Setzeinheit_runter,ON);
		break;

	case EVNT_BTN_Setzeinheit_hoch_PRESSED:
		LED_Driver_setVal(LED_Setzeinheit_hoch,ON);
		break;

	case EVNT_BTN_Vereinzelung_PRESSED:
		//ION_PacketSerialTest();
		LED_Driver_setVal(LED_Vereinzelung,ON);
		//setPosition(position_vereinzelung, currentPos += 1000);
		//setPosition(position_setzeinheit, currentPos += 1000);
		break;

	case EVNT_BTN_hoeher_PRESSED:
		LED_Driver_setVal(LED_Setztiefe_normal,ON);
		FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
		LED_Driver_setVal(LED_Setztiefe_plus_1,ON);
		FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
		LED_Driver_setVal(LED_Setztiefe_plus_2,ON);
		FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
		LED_Driver_setVal(LED_Setztiefe_normal,OFF);
		LED_Driver_setVal(LED_Setztiefe_plus_1,OFF);
		LED_Driver_setVal(LED_Setztiefe_plus_2,OFF);
		break;

	case EVNT_BTN_tiefer_PRESSED:
		LED_Driver_setVal(LED_Setztiefe_normal,ON);
		FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
		LED_Driver_setVal(LED_Setztiefe_minus_1,ON);
		FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
		LED_Driver_setVal(LED_Setztiefe_minus_2,ON);
		FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
		LED_Driver_setVal(LED_Setztiefe_normal,OFF);
		LED_Driver_setVal(LED_Setztiefe_minus_1,OFF);
		LED_Driver_setVal(LED_Setztiefe_minus_2,OFF);
		break;

    default:
    	break;
   } /* switch */
}

static void FSM_Task(void *pvParameters) {
	(void)pvParameters; /* parameter not used */

	fsm_state_t fsmState = Init;

	for(;;) {
		KEYDBNC_Process();



		switch(fsmState){
		case Init:
			LED_Driver_setVal(LED_9cm,ON);
			FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
			LED_Driver_setVal(LED_9cm,OFF);
			FRTOS1_vTaskDelay(500/portTICK_RATE_MS);

			EVNT_HandleEvent(FSM_EventHandler, TRUE);				// Todo: Für jeden case einen anderen Eventhandler??
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
