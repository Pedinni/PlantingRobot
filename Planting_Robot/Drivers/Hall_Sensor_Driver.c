/*
 * Hall_Sensor_Driver.c
 *
 *  Created on: 26.04.2017
 *      Author: Patrick
 */

#include "Hall_Sensor_Driver.h"

static void Hall_Sensor_Task(void *pvParameters) {
	(void) pvParameters; /* parameter not used */

	for (;;) {
		if(Hall_Sensor_GetVal()){
			LED1_Off();
		} else{
			LED1_On();
		}
		FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
	}
}

void Hall_Sensor_Driver_Init(void) {
	/* Initialisation of the Hall_Sensor_Driver Task*/
	if (FRTOS1_xTaskCreate(Hall_Sensor_Task, (signed portCHAR *)"Hall_Sensor_Task",
			configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY,
			(xTaskHandle*)NULL) != pdPASS) {
		for (;;) {
		}; /* Out of heap memory? */
	}
}

/*
 * Shell Parser
 * not implemented yet!!
 */

#if HALL_SENSOR_PARSE_COMMAND_ENABLE

static int app_value = 0;

uint8_t Hall_SensorParseCommand(const unsigned char *cmd, bool *handled,
		const CLS2_StdIOType *io) {
	uint8_t res = ERR_OK;
	int32_t tmp;
	const uint8_t *p;
	uint8_t buf[16];

	if (UTIL1_strcmp((char*)cmd, CLS2_CMD_HELP) == 0
			|| UTIL1_strcmp((char*)cmd, "Hall_Sensor help") == 0) {
		CLS2_SendHelpStr((unsigned char*) "Hall_Sensor",
				(const unsigned char*) "Group of Hall_Sensor commands\r\n", io->stdOut);
		CLS2_SendHelpStr((unsigned char*) "  led on",
				(const unsigned char*) "Turns LED on\r\n", io->stdOut);
		*handled = TRUE;
	} else if ((UTIL1_strcmp((char*)cmd, CLS2_CMD_STATUS) == 0)
			|| (UTIL1_strcmp((char*)cmd, "app status") == 0)) {
		CLS2_SendStatusStr((unsigned char*) "app",
				(const unsigned char*) "\r\n", io->stdOut);
		UTIL1_Num32sToStr(buf, sizeof(buf), app_value);
		UTIL1_strcat(buf, sizeof(buf), "\r\n");
		CLS2_SendStatusStr("  val", buf, io->stdOut);
		*handled = TRUE;
	} else if (UTIL1_strcmp((char*)cmd, "led on") == 0) {
		LED1_On();
		*handled = TRUE;
	} else if (UTIL1_strcmp((char*)cmd, "led off") == 0) {
		LED1_Off();
		*handled = TRUE;

		return res;
	}
	return res;
}
#endif
