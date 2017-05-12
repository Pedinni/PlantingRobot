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
	drive_setzeinheit_forward 		= 0,			//0
	drive_setzeinheit_backward 		= 1,			//1
	drive_vereinzelung_forward 		= 4,			//4
	drive_vereinzelung_backward 	= 5,			//5
	set_encoder_setzeinheit			= 22,			//22
	set_encoder_vereinzelung		= 23,			//23
	set_position_setzeinheit 		= 65,			//65
	set_position_vereinzelung 		= 66			//66
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

typedef struct ION_MOTION_DATA_{
	position_t 	Topfgroesse;
	int			EncoderVereinzelung;
}ion_motion_data_t;

static void ION_Motion_Task(void *pvParameters);

void ION_SimpleSerialTest(void);

void ION_PacketSerialTest(void);

unsigned short crc16(unsigned char *packet, int nBytes);

void setPosition(ion_command_t command, position_t pos);

void setMotorSpeed(ion_command_t command, int speed);

void ION_Motion_sendPacket(unsigned char packet[], int packetlength);

int getMotor1Current();

void ION_Motion_Driver_Init(void);

#endif /* DRIVERS_LED_DRIVER_H_ */
