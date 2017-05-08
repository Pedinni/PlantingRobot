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
#include "LED2.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "CLS2.h"
#include "ION_Motion_Relais.h"
#include "GI2C1.h"

typedef enum LED_{
	LED_9cm,
	LED_11cm,
	LED_12cm,
	LED_13cm,
	LED_14cm,
	LED_AUTO,
	LED_Spindel_runter,
	LED_Spindel_hoch,
	LED_Vereinzelung,
	LED_Setztiefe_hoeher,
	LED_Setztiefe_tiefer
}led_t;

static void LED_Task(void *pvParameters);

uint8_t LEDParseCommand(const unsigned char *cmd, bool *handled, const CLS2_StdIOType *io);

void LED_Driver_Init(void);

#endif /* DRIVERS_LED_DRIVER_H_ */
