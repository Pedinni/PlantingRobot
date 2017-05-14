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
	LED_9cm					= 0,
	LED_11cm				= 1,
	LED_12cm				= 2,
	LED_13cm				= 3,
	LED_14cm				= 4,
	LED_auto				= 5,

	LED_Spindel_hoch		= 6,
	LED_Spindel_runter		= 7,
	LED_Vereinzelung		= 8,

	LED_Setztiefe_minus_2	= 9,
	LED_Setztiefe_minus_1	= 10,
	LED_Setztiefe_normal	= 11,
	LED_Setztiefe_plus_1	= 12,
	LED_Setztiefe_plus_2	= 13
}led_t;

typedef enum STATE_{
	OFF		= 0b00,			// Output Hi-Z
	ON		= 0b01,			// Output LOW
	DIM0	= 0b10,			// Output dims
	DIM1	= 0b11			// Output dims
} state_t;

typedef enum BLINK_FREQUENCY_{
	fast	= 50,
	medium	= 200,
	slow	= 500,
} blink_frequency_t;
static void LED_Task(void *pvParameters);

void LED_Driver_Test(void);

void LED_Driver_setVal(led_t led, state_t state);

void LED_Driver_blink(led_t led, int amount, blink_frequency_t frequency);

void LED_Driver_blink_(led_t led, blink_frequency_t frequency);

void LED_Driver_clear_all();

void LED_Driver_pulseAll(bool activ);

void LED_Driver_clear_Topfgroesse();

int LED_Driver_Address_Encoder(led_t led);

uint8_t LEDParseCommand(const unsigned char *cmd, bool *handled, const CLS2_StdIOType *io);

void LED_Driver_Init(void);

#endif /* DRIVERS_LED_DRIVER_H_ */
