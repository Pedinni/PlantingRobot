/*
 * LED_Driver.h
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */

#ifndef DRIVERS_ION_Motion_DRIVER_H_
#define DRIVERS_ION_Motion_DRIVER_H_

/* Including needed modules to compile this module/procedure */
#include "FRTOS1.h"
#include "CLS1.h"
#include "LED1.h"



static void ION_Motion_Task(void *pvParameters);

void ION_SimpleSerialTest(void);

void ION_PacketSerialTest(void);

unsigned short crc16(unsigned char *packet, int nBytes);

void ION_Motion_Driver_Init(void);

#endif /* DRIVERS_LED_DRIVER_H_ */
