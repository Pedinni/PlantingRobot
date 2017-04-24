/*
 * ION_Motion_Driver.c
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */


#include "ION_Motion_Driver.h"


static void ION_Motion_Task(void *pvParameters) {
  (void)pvParameters; /* parameter not used */
  bool sent = 0;
  for(;;) {
	  if(sent != 1){
		  sent = 1;
		  CLS1_SendNum8u(128, CLS1_GetStdio()->stdOut);				// Adress:	(128)
		  CLS1_SendNum8u(6, CLS1_GetStdio()->stdOut);				// Command: Drive M1 (6)
		  CLS1_SendNum8u(80, CLS1_GetStdio()->stdOut);				// Value:	Drive motor 1 forward or reverse. Valid data range is 0 - 127.
		  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	// 			A value of 0 = full speed reverse, 64 = stop and 127 = full speed forward
		  unsigned int packet[3];
		  packet[0] = 128;
		  packet[1] = 6;
		  packet[2] = 80;

		  //packet = (unsigned char*)packet;

		  /*
		  strcpy(packet,"128");
		  strcpy(packet,"6");
		  strcpy(packet,"80");
		   */
		  //unsigned int crc = crc16(packet, sizeof(packet));

		  //CLS1_SendNum16u(crc, CLS1_GetStdio()->stdOut);		// CRC 2 Byte

	  }
  }
}

//Calculates CRC16 of nBytes of data in byte array message
/*
unsigned int crc16(unsigned char *packet, int nBytes) {
	unsigned int crc;
	for (int byte = 0; byte < nBytes; byte++) {
		crc = crc ^ ((unsigned int)packet[byte] << 8);
		for (unsigned char bit = 0; bit < 8; bit++) {
			if (crc & 0x8000) {
				crc = (crc << 1) ^ 0x1021;
			} else {
				crc = crc << 1;
			}
		}
	}
	return crc;
}
*/
