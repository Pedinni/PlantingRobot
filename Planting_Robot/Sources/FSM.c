/*
 * FSM.c
 *
 *		Polls the buttons and creates an event
 *
 *		Created on: 09.05.2017
 *      Author: Patrick
 */

#include "FSM.h"

fsm_data_t fsmData = {
		Startup,
		Standby,
		LED_Setztiefe_normal
};

void FSM_UserInput_EventHandler(EVNT_Handle event) {
	/*! \todo handle events */
	switch(event) {
	case EVNT_BTN_9cm_LPRESSED:
		fsmData.fsmState = Ready;
	case EVNT_BTN_9cm_PRESSED:
		setPosition(position_setzeinheit, Topf_9);
		fsmData.positionSetzeinheit = Topf_9;

		LED_Driver_clear_Topfgroesse();
		LED_Driver_blink(LED_9cm,5,high);
		LED_Driver_setVal(LED_9cm,ON);
		break;

	case EVNT_BTN_11cm_LPRESSED:
		fsmData.fsmState = Ready;
	case EVNT_BTN_11cm_PRESSED:
		setPosition(position_setzeinheit, Topf_11);
		fsmData.positionSetzeinheit = Topf_11;

		LED_Driver_clear_Topfgroesse();
		LED_Driver_blink(LED_11cm,5,high);
		LED_Driver_setVal(LED_11cm,ON);
		break;

	case EVNT_BTN_12cm_LPRESSED:
		fsmData.fsmState = Ready;
	case EVNT_BTN_12cm_PRESSED:
		setPosition(position_setzeinheit, Topf_12);
		fsmData.positionSetzeinheit = Topf_12;

		LED_Driver_clear_Topfgroesse();
		LED_Driver_blink(LED_12cm,5,high);
		LED_Driver_setVal(LED_12cm,ON);
		break;

	case EVNT_BTN_13cm_LPRESSED:
		fsmData.fsmState = Ready;
	case EVNT_BTN_13cm_PRESSED:
		setPosition(position_setzeinheit, Topf_13);
		fsmData.positionSetzeinheit = Topf_13;

		LED_Driver_clear_Topfgroesse();
		LED_Driver_blink(LED_13cm,5,high);
		LED_Driver_setVal(LED_13cm,ON);
		break;

	case EVNT_BTN_14cm_LPRESSED:
		fsmData.fsmState = Ready;
	case EVNT_BTN_14cm_PRESSED:
		setPosition(position_setzeinheit, Topf_14);
		fsmData.positionSetzeinheit = Topf_14;

		LED_Driver_clear_Topfgroesse();
		LED_Driver_blink(LED_14cm,5,high);
		LED_Driver_setVal(LED_14cm,ON);
		break;

	case EVNT_BTN_AUTO_LPRESSED:
		//fsmData.fsmState = Ready;						//kein State-Wechsel, da Auto Topfgrössenerkennung nicht implementiert
	case EVNT_BTN_AUTO_PRESSED:
		setPosition(position_setzeinheit, Standby);		//ToDo: Automatische Topfgrössenerkennung
		fsmData.positionSetzeinheit = Standby;

		LED_Driver_clear_Topfgroesse();
		LED_Driver_blink(LED_AUTO,5,high);
		//LED_Driver_setVal(LED_AUTO,ON);				//Auto Push button nicht leuchten lassen, da Auto Topfgrössenerkennung nicht implementiert
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

void FSM_Startup_EventHandler(EVNT_Handle event) {
	/*! \todo handle events */
	switch(event) {
	case EVNT_BTN_9cm_LPRESSED:				// Any Button Long Press
	case EVNT_BTN_11cm_LPRESSED:
	case EVNT_BTN_12cm_LPRESSED:
	case EVNT_BTN_13cm_LPRESSED:
	case EVNT_BTN_14cm_LPRESSED:
	case EVNT_BTN_AUTO_LPRESSED:
	case EVNT_BTN_Setzeinheit_runter_LPRESSED:
	case EVNT_BTN_Setzeinheit_hoch_LPRESSED:
	case EVNT_BTN_Vereinzelung_LPRESSED:
	case EVNT_BTN_hoeher_LPRESSED:
	case EVNT_BTN_tiefer_LPRESSED:
		 fsmData.fsmState = Init;
		break;
    default:
    	break;
   } /* switch */
}

static void FSM_Task(void *pvParameters) {
	(void)pvParameters; /* parameter not used */

	LED_Driver_clear_all();
	for(;;) {
		switch(fsmData.fsmState){
		case Startup:
			// TODO: Pulse all LEDs
			EVNT_HandleEvent(FSM_Startup_EventHandler, TRUE);
			break;
		case Init:
			// Init Vereinzelung (Encoder Steps)
			// Init Setzmechanik (Endanschlag)
			// Init Spindel		 (Endanschlag)
			LED_Driver_blink(LED_AUTO, 5, low);
			fsmData.fsmState = UserInput;
			break;

		case UserInput:
			EVNT_HandleEvent(FSM_UserInput_EventHandler, TRUE);			// konfigurieren, manuelle Steuerung
			break;

		case Ready:
			//EVNT_HandleEvent(FSM_Ready_EventHandler, TRUE);				// Stoppen, neu konfigurieren
			break;

		case Vereinzelung:
			break;

		case Stechprozess:
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
