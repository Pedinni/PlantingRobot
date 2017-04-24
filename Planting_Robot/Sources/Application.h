/*
 * Application.h
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */

#ifndef SOURCES_APPLICATION_H_
#define SOURCES_APPLICATION_H_

#include "FRTOS1.h"
#include "UTIL1.h"
#include "LED1.h"
//#include "LED_Driver.h"

#endif /* SOURCES_APPLICATION_H_ */

#define IR_SENSOR_TASK_IS_ACTIVE 	(0)
#define LED_TASK_IS_ACTIVE 			(1)
#define ION_MOTION_TASK_IS_ACTIVE 	(1)

void APP_Start(void);
void APP_InitComponents(void);

