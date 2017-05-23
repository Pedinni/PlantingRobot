/*
 * Trinamic_Motion_Driver.c
 *
 *  Created on: 18.05.2017
 *      Author: Patrick
 */

#include "Trinamic_Motion_Driver.h"

#define TARGET_ADDRESS 		0x01
#define MOTOR				0x00

static void Trinamic_Motion_Task(void *pvParameters) {
	(void)pvParameters; /* parameter not used */

	unsigned char value_slow[] = {0x00, 0x00, 0x01, 0x5E};
	unsigned char value_fast[] = {0x00, 0x00, 0x02, 0xBC};
	unsigned char value_stop[] = {0x00, 0x00, 0x00, 0x00};
	unsigned char value_pos1[] = {0x00, 0x00, 0x02, 0xBC};


	for(;;) {
#if 0
		Trinamic_Motion_Test();
#endif
		Trinamic_Motion_sendPacket(MVP, 0x01, value_pos1);
		FRTOS1_vTaskDelay(5000/portTICK_RATE_MS);
	}
}

void Trinamic_Motion_Test(){
	unsigned char value[] 	   = {0x00, 0x00, 0x00, 0x00};
	int i;

	for(i=0;i<350;i+=10){
		value[0] = (i>>24) 	& 0xff;
		value[1] = (i>>16) 	& 0xff;
		value[2] = (i>>8) 	& 0xff;
		value[3] = (i>>0) 	& 0xff;
		Trinamic_Motion_sendPacket(ROR, 0x00, value);
		FRTOS1_vTaskDelay(100/portTICK_RATE_MS);

	}
	for(i=350;i>0;i-=10){
		value[0] = (i>>24) 	& 0xff;
		value[1] = (i>>16) 	& 0xff;
		value[2] = (i>>8) 	& 0xff;
		value[3] = (i>>0) 	& 0xff;
		Trinamic_Motion_sendPacket(ROR, 0x00, value);
		FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
	}
}


/*
 * Sends a char packet to the Driver, wrapping it up with the
 * Target Address and the checksum. The Command Format always
 * consists out of 9 Bytes starting with the Modul address and
 * ending with the calculated Checksum.
 */
void Trinamic_Motion_sendPacket(trinamic_command_t instruction, unsigned char type, unsigned char value[]){
	unsigned char command[9];
	unsigned char checksum = 0;

	command[0] = TARGET_ADDRESS;
	command[1] = instruction;
	command[2] = type;
	command[3] = MOTOR;
	command[4] = value[0];
	command[5] = value[1];
	command[6] = value[2];
	command[7] = value[3];

	/*
	 * calculating the checksum: Adding up all
	 * commands including the module address byte
	 */
	for(int i=0; i<8; i++){
		checksum += command[i];
	}
	command[8] = checksum;

	/*
	 * send the command packet
	 */
	for(int i=0; i<=8; i++){
		CLS3_SendChar(command[i]);
	}
}

void Trinamic_Motion_Driver_Init(void){
	/* Initialisation of the Trinamic_Motion_Driver Task*/
	if(FRTOS1_xTaskCreate(Trinamic_Motion_Task, (signed portCHAR *)"Trinamic_Motion_Task", configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY, (xTaskHandle*)NULL) != pdPASS)
	{
		for(;;){}; /* Out of heap memory? */
	}
}
