/*
 * FSM.c
 *
 *		Polls the buttons and creates an event
 *
 *		Created on: 09.05.2017
 *      Author: Patrick
 */

#include "FSM.h"

#define vereinzelungSteps	2000

fsm_data_t fsmData = {
		Startup,
		Topf_9,
		0,
		LED_Setztiefe_normal
};

void FSM_UserInput_EventHandler(EVNT_Handle event) {
	/*! \todo handle events */
	switch(event) {
	case EVNT_BTN_9cm_LPRESSED:
		fsmData.fsmState = Ready;
	case EVNT_BTN_9cm_PRESSED:
		setPosition(set_position_setzeinheit, Topf_9);
		fsmData.positionSetzeinheit = Topf_9;

		LED_Driver_clear_Topfgroesse();
		LED_Driver_blink(LED_9cm,5,fast);
		LED_Driver_setVal(LED_9cm,ON);
		break;

	case EVNT_BTN_11cm_LPRESSED:
		fsmData.fsmState = Ready;
	case EVNT_BTN_11cm_PRESSED:
		setPosition(set_position_setzeinheit, Topf_11);
		fsmData.positionSetzeinheit = Topf_11;

		LED_Driver_clear_Topfgroesse();
		LED_Driver_blink(LED_11cm,5,fast);
		LED_Driver_setVal(LED_11cm,ON);
		break;

	case EVNT_BTN_12cm_LPRESSED:
		fsmData.fsmState = Ready;
	case EVNT_BTN_12cm_PRESSED:
		setPosition(set_position_setzeinheit, Topf_12);
		fsmData.positionSetzeinheit = Topf_12;

		LED_Driver_clear_Topfgroesse();
		LED_Driver_blink(LED_12cm,5,fast);
		LED_Driver_setVal(LED_12cm,ON);
		break;

	case EVNT_BTN_13cm_LPRESSED:
		fsmData.fsmState = Ready;
	case EVNT_BTN_13cm_PRESSED:
		setPosition(set_position_setzeinheit, Topf_13);
		fsmData.positionSetzeinheit = Topf_13;

		LED_Driver_clear_Topfgroesse();
		LED_Driver_blink(LED_13cm,5,fast);
		LED_Driver_setVal(LED_13cm,ON);
		break;

	case EVNT_BTN_14cm_LPRESSED:
		fsmData.fsmState = Ready;
	case EVNT_BTN_14cm_PRESSED:
		setPosition(set_position_setzeinheit, Topf_14);
		fsmData.positionSetzeinheit = Topf_14;

		LED_Driver_clear_Topfgroesse();
		LED_Driver_blink(LED_14cm,5,fast);
		LED_Driver_setVal(LED_14cm,ON);
		break;

	case EVNT_BTN_AUTO_LPRESSED:
		//fsmData.fsmState = Ready;						//kein State-Wechsel, da Auto Topfgrössenerkennung nicht implementiert
	case EVNT_BTN_AUTO_PRESSED:
		setPosition(set_position_setzeinheit, Topf_auto);		//ToDo: Automatische Topfgrössenerkennung
		fsmData.positionSetzeinheit = Topf_auto;

		LED_Driver_clear_Topfgroesse();
		LED_Driver_blink(LED_AUTO,5,fast);
		//LED_Driver_setVal(LED_AUTO,ON);				//Auto Push button nicht leuchten lassen, da Auto Topfgrössenerkennung nicht implementiert
		break;

	case EVNT_BTN_Setzeinheit_runter_PRESSED:
		setEncoderValue(set_encoder_vereinzelung,0);
		break;

	case EVNT_BTN_Setzeinheit_hoch_PRESSED:
		break;

	case EVNT_BTN_Vereinzelung_PRESSED:
		//fsmData.positionVereinzelung -= vereinzelungSteps;
		setPosition(set_position_vereinzelung, Counts_Vereinzelung);
		LED_Driver_blink(LED_Vereinzelung,2,medium);
		break;

	case EVNT_BTN_hoeher_PRESSED:
		LED_Driver_setVal(fsmData.LED_Setztiefe, OFF);
		if(fsmData.LED_Setztiefe == LED_Setztiefe_minus_2)
			fsmData.LED_Setztiefe = LED_Setztiefe_minus_1;
		else if(fsmData.LED_Setztiefe == LED_Setztiefe_plus_2)
			LED_Driver_blink(LED_Setztiefe_plus_2,2,fast);
		else
			fsmData.LED_Setztiefe = fsmData.LED_Setztiefe-2;

		LED_Driver_setVal(fsmData.LED_Setztiefe,ON);
		//ToDo: update höhe des Setzprozesses in der Spindel Funktion bsp.:	Spindel_Driver_Set_Setztiefe(fsmData.LED_Setztiefe)
		break;

	case EVNT_BTN_tiefer_PRESSED:
		LED_Driver_setVal(fsmData.LED_Setztiefe, OFF);
		if(fsmData.LED_Setztiefe == LED_Setztiefe_minus_1)
			fsmData.LED_Setztiefe = LED_Setztiefe_minus_2;
		else if(fsmData.LED_Setztiefe == LED_Setztiefe_minus_2)
			LED_Driver_blink(LED_Setztiefe_minus_2,2,fast);
		else
			fsmData.LED_Setztiefe = fsmData.LED_Setztiefe+2;

		LED_Driver_setVal(fsmData.LED_Setztiefe,ON);
		//ToDo: update höhe des Setzprozesses in der Spindel Funktion bsp.:	Spindel_Driver_Set_Setztiefe(fsmData.LED_Setztiefe)
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
		LED_Driver_pulseAll(FALSE);
		LED_Driver_clear_all();
		fsmData.fsmState = Init;
		break;
    default:
    	break;
   } /* switch */
}

static void FSM_Task(void *pvParameters) {
	(void)pvParameters; /* parameter not used */

	LED_Driver_clear_all();
	ION_Motion_Relais_ClrVal();
	for(;;) {
		switch(fsmData.fsmState){
		case Startup:
			LED_Driver_pulseAll(TRUE);
			EVNT_HandleEvent(FSM_Startup_EventHandler, TRUE);
			break;
		case Init:
			ION_Motion_Relais_SetVal();

			LED_Driver_blink(LED_Vereinzelung, 2, medium);
			ION_Motion_Init_Vereinzelung();// ToDo: Init Vereinzelung 		(Encoder Steps)

			LED_Driver_blink(LED_AUTO, 2, medium);
			// ToDo: Init Verstellmechanik 	(Endanschlag)

			LED_Driver_blink(LED_Setzeinheit_hoch, 2, medium);
			// ToDo: Init Setzeinheit	 		(Endanschlag)

			fsmData.fsmState = UserInput;
			LED_Driver_setVal(LED_Setztiefe_normal,ON);
			LED_Driver_setVal(LED_9cm,ON);
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
