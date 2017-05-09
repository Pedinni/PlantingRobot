/*
 * HMI_Driver.c
 *
 *		Polls the buttons and creates an event
 *
 *		Created on: 30.04.2017
 *      Author: Patrick
 */


#include "HMI_Driver.h"

static int currentPos = 0;

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

static void HMI_Task(void *pvParameters) {
	(void)pvParameters; /* parameter not used */

	for(;;) {
		KEYDBNC_Process();
		//EVNT_HandleEvent(APP_EventHandler, TRUE);			//Events get Handled in the FSM
		FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
	}
}

void HMI_Driver_Init(void){
	/* Initialisation of the HMI_Driver Task*/
	if (FRTOS1_xTaskCreate(HMI_Task, (signed portCHAR *)"HMI_Task", configMINIMAL_STACK_SIZE, (void*)NULL, 1, (xTaskHandle*)NULL) != pdPASS){
	   for(;;){}; /* Out of heap memory? */
	}
}
