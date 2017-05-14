/*
 * LED_Driver.c
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */


#include "LED_Driver.h"
#include <math.h>

#define LP3943_Address 	0b1100000

#define LED_9CM					(0x0600 + 0)		// Adress, Bits to Shift
#define LED_11CM				(0x0600 + 2)
#define LED_12CM				(0x0600 + 4)
#define LED_13CM				(0x0600 + 6)
#define LED_14CM				(0x0700 + 0)
#define LED_AUTO				(0x0700 + 2)

#define LED_SPINDEL_HOCH		(0x0900 + 2)
#define LED_SPINDEL_RUNTER		(0x0900 + 4)
#define LED_VEREINZELUNG		(0x0900 + 6)

#define LED_SETZTIEFE_PLUS_2	(0x0800 + 0)
#define LED_SETZTIEFE_PLUS_1	(0x0800 + 2)
#define LED_SETZTIEFE_NORMAL	(0x0800 + 4)
#define LED_SETZTIEFE_MINUS_1	(0x0800 + 6)
#define LED_SETZTIEFE_MINUS_2	(0x0900 + 0)


static TaskHandle_t LED_Pulse_Task_Handle = NULL;

static void LED_Task(void *pvParameters) {
  (void)pvParameters; /* parameter not used */
  //LED1_On();
  for(;;) {
//	  LED_Driver_Test();
//	  LED_Driver_setLED(LED_9cm);
	  FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}

static void LED_Pulse_Task(void *pvParameters) {
	  (void)pvParameters; /* parameter not used */

	  uint8_t writeData[2] = {0x02,0x00};
	  GI2C1_SelectSlave(LP3943_Address);
	  GI2C1_WriteBlock(writeData,sizeof(writeData),GI2C1_SEND_STOP);

	  /*
	   * If the LEDs shall not totaly shut down during Pulse session.
	   *
	  for(int i = 0; i<15; i++){
		  uint8_t writeData[2] = {0x03,(uint8_t)i};
		  GI2C1_WriteBlock(writeData,sizeof(writeData),GI2C1_SEND_STOP);
		  FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
	  }
	  */
	  for(;;) {
		  for(int i = 0; i<255; i++){
			  uint8_t writeData[2] = {0x03,(uint8_t)i};
			  GI2C1_WriteBlock(writeData,sizeof(writeData),GI2C1_SEND_STOP);
			  FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
		  }
		  for(int i = 255; i>0; i--){
			  uint8_t writeData[2] = {0x03,(uint8_t)i};
			  GI2C1_WriteBlock(writeData,sizeof(writeData),GI2C1_SEND_STOP);
		  	  FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
		  }
	  }
}

void LED_Driver_pulseAll(bool activ){
	if(activ && LED_Pulse_Task_Handle == NULL){
		if (FRTOS1_xTaskCreate(LED_Pulse_Task, (signed portCHAR *)"LED_Pulse_Task", configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY, &LED_Pulse_Task_Handle) != pdPASS){
			for(;;){}; /* Out of heap memory? */
		}
	} else if (activ && LED_Pulse_Task_Handle != NULL) {
		vTaskResume(LED_Pulse_Task_Handle);
	} else{
		if(LED_Pulse_Task_Handle){
			vTaskSuspend(LED_Pulse_Task_Handle);
		}
	}
	LED_Driver_setVal(LED_9cm ,DIM0);
	LED_Driver_setVal(LED_11cm ,DIM0);
	LED_Driver_setVal(LED_12cm ,DIM0);
	LED_Driver_setVal(LED_13cm ,DIM0);
	LED_Driver_setVal(LED_14cm ,DIM0);
	LED_Driver_setVal(LED_auto ,DIM0);
	LED_Driver_setVal(LED_Spindel_hoch ,DIM0);
	LED_Driver_setVal(LED_Spindel_runter ,DIM0);
	LED_Driver_setVal(LED_Vereinzelung ,DIM0);
	LED_Driver_setVal(LED_Setztiefe_minus_1 ,DIM0);
	LED_Driver_setVal(LED_Setztiefe_minus_2 ,DIM0);
	LED_Driver_setVal(LED_Setztiefe_normal ,DIM0);
	LED_Driver_setVal(LED_Setztiefe_plus_1 ,DIM0);
	LED_Driver_setVal(LED_Setztiefe_plus_2 ,DIM0);
}

void LED_Driver_Init(void){
	/* Initialisation of the LED_Driver Task*/
	if (FRTOS1_xTaskCreate(LED_Task, (signed portCHAR *)"LED_Task", configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY, (xTaskHandle*)NULL) != pdPASS){
	   for(;;){}; /* Out of heap memory? */
	}
}

void LED_Driver_Test(void){
	//uint8_t writeRegister[1] = {0x06};
	uint8_t writeData[2] = {0x06,0b01010101};
	GI2C1_SelectSlave(LP3943_Address);
	uint8_t err = GI2C1_WriteBlock(writeData,sizeof(writeData),GI2C1_SEND_STOP);
}

void LED_Driver_setVal(led_t led, state_t state){
	int LED_address = LED_Driver_Address_Encoder(led);
	GI2C1_SelectSlave(LP3943_Address);
	uint8_t writeData[2] = {LED_address>>8, 0x00};		// Register, Value

	GI2C1_WriteBlock(writeData,1,GI2C1_DO_NOT_SEND_STOP);			//Read LS0 Register
	GI2C1_ReadBlock(&writeData[1],1,GI2C1_SEND_STOP);				//Read LS0 Register

	uint8_t op1 = (0xFC<<(uint8_t)LED_address);								// create Bitmask for clearing the state of the corresponding led
	uint8_t op2 = pow(2,(uint8_t)LED_address) - 1;
	uint8_t clearMask = op1 | op2;

	writeData[1] = writeData[1] &  clearMask;						// clear state which gets written
	writeData[1] = writeData[1] | state << (uint8_t)LED_address;			// write state
	GI2C1_WriteBlock(writeData,sizeof(writeData),GI2C1_SEND_STOP);	// Send new LED Register
}

void LED_Driver_blink(led_t led, int amount, blink_frequency_t frequency){
	for(int i =0; i<amount; i++){
		LED_Driver_setVal(led,ON);
		FRTOS1_vTaskDelay(frequency/portTICK_RATE_MS);
		LED_Driver_setVal(led,OFF);
		FRTOS1_vTaskDelay(frequency/portTICK_RATE_MS);
	}
}

/*
 * Blink a specified LED with a specified frequency.
 * PSC Values of the LED Driver Timer were calculated as followd:
 * PSC = (T * 160) - 1
 */
void LED_Driver_blink_(led_t led, blink_frequency_t frequency){
	uint8_t PSCValue = 0;
	switch(frequency){
	case fast:		PSCValue = 15;
		break;
	case medium:	PSCValue = 63;
		break;
	case slow:		PSCValue = 159;
		break;
	}
	uint8_t writeData[2] = {0x04, PSCValue};
	GI2C1_SelectSlave(LP3943_Address);
	GI2C1_WriteBlock(writeData,sizeof(writeData),GI2C1_SEND_STOP);

	LED_Driver_setVal(led,DIM1);
}

void LED_Driver_clear_Topfgroesse(){
	LED_Driver_setVal(LED_9cm,OFF);
	LED_Driver_setVal(LED_11cm,OFF);
	LED_Driver_setVal(LED_12cm,OFF);
	LED_Driver_setVal(LED_13cm,OFF);
	LED_Driver_setVal(LED_14cm,OFF);
	LED_Driver_setVal(LED_auto,OFF);
}

void LED_Driver_clear_all(){
	LED_Driver_setVal(LED_9cm,OFF);
	LED_Driver_setVal(LED_11cm,OFF);
	LED_Driver_setVal(LED_12cm,OFF);
	LED_Driver_setVal(LED_13cm,OFF);
	LED_Driver_setVal(LED_14cm,OFF);
	LED_Driver_setVal(LED_auto,OFF);
	LED_Driver_setVal(LED_Spindel_hoch,OFF);
	LED_Driver_setVal(LED_Spindel_runter,OFF);
	LED_Driver_setVal(LED_Setztiefe_minus_1,OFF);
	LED_Driver_setVal(LED_Setztiefe_minus_2,OFF);
	LED_Driver_setVal(LED_Setztiefe_normal,OFF);
	LED_Driver_setVal(LED_Setztiefe_plus_1,OFF);
	LED_Driver_setVal(LED_Setztiefe_plus_2,OFF);
	LED_Driver_setVal(LED_Vereinzelung,OFF);
}

int LED_Driver_Address_Encoder(led_t led){
	switch(led){
	case LED_9cm:  return LED_9CM;
	case LED_11cm: return LED_11CM;
	case LED_12cm: return LED_12CM;
	case LED_13cm: return LED_13CM;
	case LED_14cm: return LED_14CM;
	case LED_auto: return LED_AUTO;

	case LED_Spindel_hoch: 	 return LED_SPINDEL_HOCH;
	case LED_Spindel_runter: return LED_SPINDEL_RUNTER;
	case LED_Vereinzelung:   return LED_VEREINZELUNG;

	case LED_Setztiefe_plus_2:  return LED_SETZTIEFE_PLUS_2;
	case LED_Setztiefe_plus_1:  return LED_SETZTIEFE_PLUS_1;
	case LED_Setztiefe_normal:  return LED_SETZTIEFE_NORMAL;
	case LED_Setztiefe_minus_1: return LED_SETZTIEFE_MINUS_1;
	case LED_Setztiefe_minus_2: return LED_SETZTIEFE_MINUS_2;
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
