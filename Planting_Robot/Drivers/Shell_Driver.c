/*
 * LED_Driver.c
 *
 *  Created on: 25.04.2017
 *      Author: Patrick
 */


#include "Shell_Driver.h"


static int app_value = 0;

static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const CLS2_StdIOType *io) {
  uint8_t res = ERR_OK;
  int32_t tmp;
  const uint8_t *p;
  uint8_t buf[16];

  if (UTIL1_strcmp((char*)cmd, CLS2_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "app help")==0) {
    CLS2_SendHelpStr((unsigned char*)"app", (const unsigned char*)"Group of app commands\r\n", io->stdOut);
    CLS2_SendHelpStr((unsigned char*)"  val <number>", (const unsigned char*)"Set value\r\n", io->stdOut);
    *handled = TRUE;
  } else if ((UTIL1_strcmp((char*)cmd, CLS2_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "app status")==0)) {
    CLS2_SendStatusStr((unsigned char*)"app", (const unsigned char*)"\r\n", io->stdOut);
    UTIL1_Num32sToStr(buf, sizeof(buf), app_value);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
    CLS2_SendStatusStr("  val", buf, io->stdOut);
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, "app val", sizeof("app val")-1)==0) {
    p = cmd+sizeof("app val")-1;
    res = UTIL1_xatoi(&p, &tmp);
    if (res==ERR_OK) {
      app_value = tmp;
      *handled = TRUE;
    }
    return res;
  }
  return res;
}

static const CLS2_ParseCommandCallback CmdParserTable[] =
{
  CLS2_ParseCommand, /* default shell parser */
  ParseCommand, /* my own shell parser */
#if LED_PARSE_COMMAND_ENABLE
  LEDParseCommand,
#endif
  NULL /* Sentinel, must be last */
};

static void Shell_Task(void *pvParameters) {
  (void)pvParameters; /* parameter not used */

  	unsigned char buf[48];
    int cntr = 0;

    app_value = 0; /* init value */
    buf[0] = '\0'; /* init buffer */
    (void)CLS2_ParseWithCommandTable((unsigned char*)CLS2_CMD_HELP, CLS2_GetStdio(), CmdParserTable); /* write help */
    for(;;) { /* wait for input and parse it */
      (void)CLS2_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS2_GetStdio(), CmdParserTable);
      cntr++;
      FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
    }
}

#if 0
void DoUART(void) {
  static unsigned char buffer[64];
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
#endif

void Shell_Driver_Init(void){
	/* Initialisation of the LED_Driver Task*/
	if (FRTOS1_xTaskCreate(Shell_Task, (signed portCHAR *)"Shell_Task", configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY, (xTaskHandle*)NULL) != pdPASS){
	   for(;;){}; /* Out of heap memory? */
	}
}
