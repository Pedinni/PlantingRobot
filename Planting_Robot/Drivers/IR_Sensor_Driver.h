/*
 * LED_Driver.h
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */

#ifndef DRIVERS_IR_SENSOR_DRIVER_H_
#define DRIVERS_IR_SENSOR_DRIVER_H_

/* Including needed modules to compile this module/procedure */
#include "LED1.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "AD1.h"

#endif /* DRIVERS_LED_DRIVER_H_ */

#define Erkenndistanz	5000		//ca. 40cm

static void IR_Sensor_Task(void *pvParameters);

void IR_Sensor_Driver_Init();
