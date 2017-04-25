/*
 * LED_Driver.c
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */


#include "Shell_Driver.h"


static void Shell_Task(void *pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    DoUART();
  }
}

static unsigned char buffer[64];

void DoUART(void) {
  buffer[0] = '\0'; /* initialize buffer for ReadLine() */
  for(;;) {
    CLS2_SendStr("Type in some text with CR or LF at the end...\r\n", CLS2_GetStdio()->stdOut);
    LED1_Neg();
    WAIT1_Waitms(1000);
    if (CLS2_ReadLine(buffer, buffer, sizeof(buffer), CLS2_GetStdio())) {
      /* line read */
      CLS2_SendStr("You entered:\r\n", CLS2_GetStdio()->stdOut);
      CLS2_SendStr(buffer, CLS2_GetStdio()->stdOut);
      buffer[0] = '\0';
    }
  }
}

void Shell_Driver_Init(void){
	/* Initialisation of the LED_Driver Task*/
	if (FRTOS1_xTaskCreate(Shell_Task, (signed portCHAR *)"Shell_Task", configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY, (xTaskHandle*)NULL) != pdPASS){
	   for(;;){}; /* Out of heap memory? */
	}
}
