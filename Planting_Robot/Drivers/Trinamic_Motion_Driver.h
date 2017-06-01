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
#include "CLS3.h"
#include "LED_Driver.h"

typedef enum TRINAMIC_COMMAND_{
	ROR			= 1,		// rotate right
	ROL			= 2,		// rotate left
	MST			= 3,		// motor stop
	MVP 		= 4,		// move to position

	SAP 		= 5,		// set axis parameter
	GAP 		= 6,		// get axis parameter
	STAP 		= 7,		// store axis parameter
	RSAP 		= 8,		// restore axis parameter
	SGP			= 9,		// set global parameter
	GGP			= 10,		// get global parameter
	STGP		= 11,		// store global parameter
	RSGP		= 12,		// restore global parameter

	SIO			= 14,		// set output
	GIO			= 15,		// get input/output

	CALC		= 19,		// calculate
	COMP		= 20,		// compare
	JC			= 21,		// jump conditional
} trinamic_command_t;

typedef enum TRINAMIC_AXIS_PARAMETER_{
	acutal_position			= 1,		// Set/get the position counter without moving the motor.
	target_speed			= 2,		// Set/get the desired target velocity.
	max_abs_ramp_velocity	= 4,		// The maximum velocity used for velocity ramp in velocity mode and positioning mode. Set this value to a realistic velocity which the motor can reach!
	max_current				= 6,		// Set/get the max allowed motor current.
	acceleration			= 11,		// Acceleration parameter for ROL, ROR, and the velocity ramp of MVP.

	actual_speed			= 3,		// Get actual velocity of the motor.
	actual_current			= 150,		// Get actual motor current.
	start_current			= 177,		// Motor current for controlled commutation. This parameter is used in commutation mode.

	p_current				= 172,		// P parameter of current PID regulator.
	i_current				= 173,		// I parameter of current PID regulator.
	p_velocity				= 234,		// P parameter of velocity PID regulator.
	i_velocity				= 235,		// I parameter of velocity PID regulator.
	p_position				= 230,		// P parameter of position PID regulator.

	commutation_mode		= 159,		// 0: Block based on hall sensor / 6: FOC based on hall sensor / 7: FOC based on encoder / 8: FOC controlled
	number_of_motor_poles	= 253,		// Number of motor poles.
	hall_sensor_invert		= 254,		// 1: Hall sensor invert. Invert the hall scheme, e.g. used by some Maxon motors.
} trinamic_axis_parameter_t;

static void Trinamic_Motion_Task(void *pvParameters);

void Trinamic_Motion_Driver_Init(void);

void Trinamic_Motion_sendPacket(trinamic_command_t instruction, unsigned char type, int32_t value);

int32_t Trinamic_Motion_receivePacket();

void Trinamic_Motion_Init_Stechprozess();

#endif /* DRIVERS_Trinamic_Motion_DRIVER_H_ */
