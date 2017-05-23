/*
 * Trinamic_Motion_Driver.h
 *
 *  Created on: 18.05.2017
 *      Author: Patrick
 */

#ifndef DRIVERS_Trinamic_Motion_DRIVER_H_
#define DRIVERS_Trinamic_Motion_DRIVER_H_

/* Including needed modules to compile this module/procedure */
#include "FRTOS1.h"
#include "LED2.h"
#include "Stop_IN.h"
#include "CLS3.h"

typedef enum TRINAMIC_COMMAND_{
	ROR			= 1,		// rotate right
	ROL			= 2,		// rotate left
	MST			= 3,		// motor stop
	MVP 		= 4,		// move to position

	SAP 		= 5,		// set axis parameter
	GAP 		= 6,		// get axis parameter
	STAP 		= 7,		// store axis parameter
	RSAP 		= 8,		// restore axis parameter
	SGP			= 9,		// set global parameter
	GGP			= 10,		// get global parameter
	STGP		= 11,		// store global parameter
	RSGP		= 12,		// restore global parameter

	SIO			= 14,		// set output
	GIO			= 15,		// get input/output

	CALC		= 19,		// calculate
	COMP		= 20,		// compare
	JC			= 21,		// jump conditional
} trinamic_command_t;

static void Trinamic_Motion_Task(void *pvParameters);

void Trinamic_Motion_Driver_Init(void);

void Trinamic_Motion_sendPacket(unsigned char instruction, unsigned char type, unsigned char value[]);

#endif /* DRIVERS_Trinamic_Motion_DRIVER_H_ */
