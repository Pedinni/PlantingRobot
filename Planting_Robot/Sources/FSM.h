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
	Startup = 0,
	Init,
	UserInput,
	Ready,
	Stechprozess,
	Vereinzelung
} fsm_state_t;

typedef enum POS_SETZEINHEIT_{
	fsm_pos_9cm = 0,
	fsm_pos_11cm,
	fsm_pos_12cm,
	fsm_pos_13cm,
	fsm_pos_14cm,
	fsm_pos_auto
} pos_setzeinheit_t;

typedef struct FSM_DATA_{
	fsm_state_t 		fsmState;
	pos_setzeinheit_t 	positionSetzeinheit;
	int					positionVereinzelung;
	led_t 				LED_Setztiefe;
} fsm_data_t;

static void FSM_Task(void *pvParameters);

void FSM_Init(void);

#endif /* DRIVERS_LED_DRIVER_H_ */
