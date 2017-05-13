/*
 * LED_Driver.h
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */

#ifndef DRIVERS_ION_Motion_DRIVER_H_
#define DRIVERS_ION_Motion_DRIVER_H_

/* Including needed modules to compile this module/procedure */
#include "FRTOS1.h"
#include "CLS1.h"
#include "LED1.h"
#include "ION_Motion_Relais.h"
#include "Hall_Sensor.h"

typedef enum ION_COMMAND_{
	drive_setzeinheit_backward 		= 5,			//1
	drive_setzeinheit_forward 		= 4,			//0
	drive_vereinzelung_backward 	= 1,			//5
	drive_vereinzelung_forward 		= 0,			//4
	set_encoder_vereinzelung		= 22,			//23
	set_encoder_setzeinheit			= 23,			//22
	read_motor_currents				= 49,
	set_position_vereinzelung 		= 65,			//66
	set_position_setzeinheit 		= 66			//65
} ion_command_t;

typedef enum Position_{
	Topf_9	= 0,
	Topf_11,
	Topf_12,
	Topf_13,
	Topf_14,
	Topf_auto,
	Counts_Vereinzelung,
	Offset_Vereinzelung
}position_t;

#define numberOfCurrentSamples	5

typedef struct ION_MOTION_DATA_{
	position_t 	Topfgroesse;
	int			EncoderVereinzelung;
	int			Motor1CurrentSamples[numberOfCurrentSamples];
	int			Motor2CurrentSamples[numberOfCurrentSamples];
	int			Motor1Current;						//Vereinzelung
	int			Motor2Current;						//Setzeinheit
}ion_motion_data_t;

static void ION_Motion_Task(void *pvParameters);

void ION_SimpleSerialTest(void);

void ION_PacketSerialTest(void);

unsigned short crc16(unsigned char *packet, int nBytes);

void setPosition(ion_command_t command, position_t pos);

void setMotorSpeed(ion_command_t command, int speed);

void ION_Motion_sendPacket(unsigned char packet[], int packetlength);

void getMotorCurrent(void);

void ION_Motion_Driver_Init(void);

#endif /* DRIVERS_LED_DRIVER_H_ */
