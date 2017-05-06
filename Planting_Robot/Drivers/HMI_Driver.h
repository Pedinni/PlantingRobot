/*
 * LED_Driver.h
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */

#ifndef DRIVERS_HMI_DRIVER_H_
#define DRIVERS_HMI_DRIVER_H_

/* Including needed modules to compile this module/procedure */
#include "Application.h"
#include "WAIT1.h"
#include "FRTOS1.h"



#include "KeyDebounce.h"
#include "Event.h"

#include "LED1.h"
#include "LED2.h"
#include "LED3.h"

static void HMI_Task(void *pvParameters);

void HMI_Driver_Init(void);

#endif /* DRIVERS_LED_DRIVER_H_ */
