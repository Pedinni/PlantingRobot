/*
 * Application.h
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */

#ifndef SOURCES_APPLICATION_H_
#define SOURCES_APPLICATION_H_

#include "PE_Types.h" /* common Processor Expert types: bool, NULL, ... */
#include "Cpu.h" /* for PEcfg_RoboV2/PEcfg_RoboV1 */

#include "FRTOS1.h"
#include "UTIL1.h"
#include "LED1.h"
#include "Shell_Driver.h"
//#include "LED_Driver.h"

#include "Event.h"
#include "Timer.h"
#include "Trigger.h"

/*
 * Configuration of Components
 */
#define IR_SENSOR_IS_ACTIVE 		(0)
#define LED_IS_ACTIVE 				(0)
#define ION_MOTION_IS_ACTIVE 		(0)
#define SHELL_IS_ACTIVE				(1)
#define HALL_SENSOR_IS_ACTIVE		(1)
#define HMI_IS_ACTIVE				(1)
#define FSM_IS_ACTIVE				(1)


/*
 * Configuration of Shell
 */
#define LED_PARSE_COMMAND_ENABLE			LED_IS_ACTIVE && SHELL_IS_ACTIVE			&& (1)
#define HALL_SENSOR_PARSE_COMMAND_ENABLE	HALL_SENSOR_IS_ACTIVE && SHELL_IS_ACTIVE	&& (0)

void APP_Start(void);
void APP_InitComponents(void);

#endif /* SOURCES_APPLICATION_H_ */
