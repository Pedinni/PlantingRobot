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
//#include "CLS1.h"		//add pe component

static void Trinamic_Motion_Task(void *pvParameters);

void Trinamic_Motion_Driver_Init(void);

#endif /* DRIVERS_Trinamic_Motion_DRIVER_H_ */
