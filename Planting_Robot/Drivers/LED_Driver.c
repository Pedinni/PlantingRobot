/*
 * LED_Driver.c
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */


#include "LED_Driver.h"


static void LED_Task(void *pvParameters) {
  (void)pvParameters; /* parameter not used */
  LED1_On();
  for(;;) {
    //LED1_Neg();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}

void LED_Driver_Init(void){
	/* Initialisation of the LED_Driver Task*/
	if (FRTOS1_xTaskCreate(LED_Task, (signed portCHAR *)"LED_Task", configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY, (xTaskHandle*)NULL) != pdPASS){
	   for(;;){}; /* Out of heap memory? */
	}
}


/*
 * Shell Parser
 */

#if LED_PARSE_COMMAND_ENABLE

static int app_value = 0;

uint8_t LEDParseCommand(const unsigned char *cmd, bool *handled, const CLS2_StdIOType *io) {
  uint8_t res = ERR_OK;
  int32_t tmp;
  const uint8_t *p;
  uint8_t buf[16];

  if (UTIL1_strcmp((char*)cmd, CLS2_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "led help")==0) {
    CLS2_SendHelpStr((unsigned char*)"LED", (const unsigned char*)"Group of LED commands\r\n", io->stdOut);
    CLS2_SendHelpStr((unsigned char*)"  led on", (const unsigned char*)"Turns LED on\r\n", io->stdOut);
    CLS2_SendHelpStr((unsigned char*)"  led off", (const unsigned char*)"Turns LED off\r\n", io->stdOut);
    *handled = TRUE;
  } else if ((UTIL1_strcmp((char*)cmd, CLS2_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "app status")==0)) {
    CLS2_SendStatusStr((unsigned char*)"app", (const unsigned char*)"\r\n", io->stdOut);
    UTIL1_Num32sToStr(buf, sizeof(buf), app_value);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
    CLS2_SendStatusStr("  val", buf, io->stdOut);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "led on")==0) {
	  LED1_On();
      *handled = TRUE;
  }	else if (UTIL1_strcmp((char*)cmd, "led off")==0) {
  	  LED1_Off();
      *handled = TRUE;

      return res;
  }
  return res;
}
#endif
