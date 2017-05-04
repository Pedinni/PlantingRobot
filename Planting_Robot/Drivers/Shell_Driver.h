/*
 * LED_Driver.h
 *
 *  Created on: 25.04.2017
 *      Author: Patrick
 */

#ifndef DRIVERS_SHELL_DRIVER_H_
#define DRIVERS_SHELL_DRIVER_H_

/* Including needed modules to compile this module/procedure */
#include "Application.h"
#include "LED1.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "CLS2.h"
#include "LED_Driver.h"


static void Shell_Task(void *pvParameters);

void Shell_Driver_Init(void);

void DoUART(void);

#endif /* DRIVERS_LED_DRIVER_H_ */
