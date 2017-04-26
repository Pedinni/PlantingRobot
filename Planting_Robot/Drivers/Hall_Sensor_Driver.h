/*
 * Hall_Sensor_Driver.h
 *
 *  Created on: 26.04.2017
 *      Author: Patrick
 */

#ifndef DRIVERS_Hall_Sensor_Driver_H_
#define DRIVERS_Hall_Sensor_Driver_H_

/* Including needed modules to compile this module/procedure */
#include "Application.h"
#include "LED1.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "CLS2.h"
#include "Hall_Sensor.h"

static void Hall_Sensor_Task(void *pvParameters);

uint8_t Hall_SensorParseCommand(const unsigned char *cmd, bool *handled, const CLS2_StdIOType *io);

void Hall_Sensor_Driver_Init(void);

#endif /* DRIVERS_Hall_Sensor_Driver_H_ */
