/*
 * FSM.h
 *
 *  Created on: 09.05.2017
 *      Author: Patrick
 */

#ifndef FSM_H_
#define FSM_H_

/* Including needed modules to compile this module/procedure */
#include "Application.h"
#include "WAIT1.h"
#include "FRTOS1.h"

#include "KeyDebounce.h"
#include "Event.h"

#include "LED_Driver.h"
#include <ION_Motion_Driver.h>

typedef enum FSM_STATE_{
	Init = 0,
	Ready,
	Vereinzelung,
	Stechprozess,
	Ausloesung
} fsm_state_t;

static void FSM_Task(void *pvParameters);

void FSM_Init(void);

#endif /* DRIVERS_LED_DRIVER_H_ */
