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

typedef enum Command_{
	drive_vereinzelung_forward 		= 0,
	drive_vereinzelung_backward 	= 1,
	drive_setzeinheit_forward 		= 4,
	drive_setzeinheit_backward 		= 5
}command_t;

typedef enum Position_{
	Topf_9		= 0,
	Topf_11		= 1000,
	Topf_12		= 2000,
	Topf_13		= 3000,
	Topf_14		= 4000,
}position_t;

static void ION_Motion_Task(void *pvParameters);

void ION_SimpleSerialTest(void);

void ION_PacketSerialTest(void);

unsigned short crc16(unsigned char *packet, int nBytes);

void ION_Motion_Driver_Init(void);

#endif /* DRIVERS_LED_DRIVER_H_ */
