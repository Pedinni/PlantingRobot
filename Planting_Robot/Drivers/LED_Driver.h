/*
 * LED_Driver.h
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */

#ifndef DRIVERS_LED_DRIVER_H_
#define DRIVERS_LED_DRIVER_H_

/* Including needed modules to compile this module/procedure */
#include "Application.h"
#include "LED1.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "CLS2.h"


#endif /* DRIVERS_LED_DRIVER_H_ */

static void LED_Task(void *pvParameters);

uint8_t LEDParseCommand(const unsigned char *cmd, bool *handled, const CLS2_StdIOType *io);

void LED_Driver_Init(void);
