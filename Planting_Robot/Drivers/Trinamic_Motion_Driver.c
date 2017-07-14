/*
 * Trinamic_Motion_Driver.c
 *
 *  Created on: 18.05.2017
 *      Author: Patrick
 */

#include "Trinamic_Motion_Driver.h"

#define TARGET_ADDRESS 		0x01
#define MOTOR				0x00

#define P_TORQUE_PID		500
#define I_TORQUE_PID		260
#define P_VELOCITY_PID		2000
#define I_VELOCITY_PID		100
#define P_POSITION_PID		20000

#define VELOCITY_RAMP_ACCEL	35000

#define CURRENT_LIMIT_INIT_HOCH				2000
//#define CURRENT_LIMIT_INIT_RUNTER			500
#define CURRENT_LIMIT_STECHPROZESS_HOCH		10000
#define CURRENT_LIMIT_STECHPROZESS_RUNTER	10000

#define COUNTS_OFFSET_OBEN			6			// 4
#define COUNTS_POSITION_STANDARD	44			// Schätzwert (3 Umdrehungen)		Todo: Messen
#define COUNTS_POSITION_UNTEN		50			// Schätzwert (4 Umdrehungen)		Todo: Messen
#define COUTNS_SETZTIEFE_VERSTELLEN	3			// Schätzwert
#define COUNTS_OFFSET_UNTEN			4

#define DELAY_STECHPROZESS			1000			// Schätzwert

#define TIME_TO_GO_UP_AGAIN		150				// Must be set to ca. 200ms to reach the specifications in the Pflichtenheft (ms)

static int countsSetztiefe = COUNTS_POSITION_STANDARD;		// 12 Hall counts = 1 Revolutions

static void Trinamic_Motion_Task(void *pvParameters) {
	(void)pvParameters; /* parameter not used */

	for(;;) {
#if 0
		Trinamic_Motion_Test();
#endif
#if 0
		LED2_On();
		Trinamic_Motion_sendPacket(ROL, 0x01, 500);
		FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
#endif
	}
}

void Trinamic_Motion_Test(){
	int i;

	for(i=0;i<350;i+=10){
		Trinamic_Motion_sendPacket(ROR, 0x00, i);
		FRTOS1_vTaskDelay(100/portTICK_RATE_MS);

	}
	for(i=350;i>0;i-=10){
		Trinamic_Motion_sendPacket(ROR, 0x00, i);
		FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
	}
}

void Trinamic_Motion_DriveToZero(){
	Trinamic_Motion_sendPacket(SAP, max_current, 2000);
	Trinamic_Motion_sendPacket(MVP, 0x00, 0);
}

void Trinamic_Motion_Stechprozess(){
	FRTOS1_vTaskDelay(DELAY_STECHPROZESS/portTICK_RATE_MS);
	Trinamic_Motion_sendPacket(SAP, max_current, CURRENT_LIMIT_STECHPROZESS_HOCH);
	Trinamic_Motion_sendPacket(MVP, 0x00, countsSetztiefe);
	FRTOS1_vTaskDelay(TIME_TO_GO_UP_AGAIN/portTICK_RATE_MS);
	Trinamic_Motion_sendPacket(MVP, 0x00, 0);
}

/*
 * Mit dieser Methode kann die Setztiefe eingestellt werden. Dabei wird die Abweichung von der
 * Standardtiefe in Hall Counts angegeben. Eine positie Zahl bedeutet eine tiefer Setztiefe.
 */
void Trinamic_Motion_setSetztiefe(led_t Setztiefe){
	int setztiefeOffset = 0;

	switch(Setztiefe){
		case LED_Setztiefe_normal:
			setztiefeOffset = 0;
			break;
		case LED_Setztiefe_minus_1:
			setztiefeOffset = COUTNS_SETZTIEFE_VERSTELLEN;
			break;
		case LED_Setztiefe_minus_2:
			setztiefeOffset = 2 * COUTNS_SETZTIEFE_VERSTELLEN;
			break;
		case LED_Setztiefe_plus_1:
			setztiefeOffset = -COUTNS_SETZTIEFE_VERSTELLEN;
			break;
		case LED_Setztiefe_plus_2:
			setztiefeOffset = -2 * COUTNS_SETZTIEFE_VERSTELLEN;
			break;
		default:
			break;
	}

	if((COUNTS_POSITION_STANDARD + setztiefeOffset) > (COUNTS_POSITION_UNTEN)){
		countsSetztiefe = COUNTS_POSITION_UNTEN;
	} else if((COUNTS_POSITION_STANDARD + setztiefeOffset) < 0){
		countsSetztiefe = 0;
	} else{
		countsSetztiefe = COUNTS_POSITION_STANDARD + setztiefeOffset;
	}
}

void Trinamic_Motion_Init_Stechprozess(){
	int32_t motorCurrent = 0;
	/*
	 * Configure Motor Characteristics
	 */
	Trinamic_Motion_sendPacket(SAP, commutation_mode, 6);
	Trinamic_Motion_sendPacket(SAP, number_of_motor_poles, 4);
	Trinamic_Motion_sendPacket(SAP, hall_sensor_invert, 1);

	/*
	 * Configure PI Parameter of the Torque, Velocity and Position Control
	 */
	Trinamic_Motion_sendPacket(SAP, p_current, P_TORQUE_PID);
	Trinamic_Motion_sendPacket(SAP, i_current, I_TORQUE_PID);
	Trinamic_Motion_sendPacket(SAP, p_velocity, P_VELOCITY_PID);
	Trinamic_Motion_sendPacket(SAP, i_velocity, I_VELOCITY_PID);
	Trinamic_Motion_sendPacket(SAP, p_position, P_POSITION_PID);
	Trinamic_Motion_sendPacket(SAP, acceleration, VELOCITY_RAMP_ACCEL);

	/*
	 * Drive to upper mechanical stop and set Hall Counter to 0 - upperOffset
	 */
	Trinamic_Motion_sendPacket(SAP, max_current, CURRENT_LIMIT_INIT_HOCH);
	Trinamic_Motion_sendPacket(ROL, 0x00, 200);
	//FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);

	while(abs(motorCurrent) < (CURRENT_LIMIT_INIT_HOCH-100)){
		FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
		AS3_ClearRxBuf();
		Trinamic_Motion_sendPacket(GAP, actual_current, 0x00);
		//FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
		motorCurrent = Trinamic_Motion_receivePacket();
		//ToDo: timeout einbauen
	}
	//Trinamic_Motion_sendPacket(MST, 0x00, 0x00);
	Trinamic_Motion_sendPacket(SAP, acutal_position, 0x00 - COUNTS_OFFSET_OBEN);		//0x00 - COUNTS_OFFSET_OBEN

	/*
	 * Drive to resting position (Counts = 0)
	 */
	Trinamic_Motion_sendPacket(MVP, 0x00, 0);
}

/*
 * Sends a char packet to the Driver, wrapping it up with the
 * Target Address and the checksum. The Command Format always
 * consists out of 9 Bytes starting with the Modul address and
 * ending with the calculated Checksum.
 */
void Trinamic_Motion_sendPacket(trinamic_command_t instruction, trinamic_axis_parameter_t type, int32_t value){
	unsigned char command[9];
	unsigned char checksum = 0;

	command[0] = TARGET_ADDRESS;
	command[1] = instruction;
	command[2] = type;
	command[3] = MOTOR;
	command[4] = (value>>24)  & 0xFF;	//value[0];
	command[5] = (value>>16)  & 0xFF;	//value[1];
	command[6] = (value>>8)   & 0xFF;	//value[2];
	command[7] = (value>>0)   & 0xFF;	//value[3];

	/*
	 * calculating the checksum: Adding up all
	 * commands including the module address byte
	 */
	for(int i=0; i<8; i++){
		checksum += command[i];
	}
	command[8] = checksum;

	/*
	 * send the command packet
	 */
	for(int i=0; i<=8; i++){
		CLS3_SendChar(command[i]);
	}
	FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
}

int32_t Trinamic_Motion_receivePacket(){
	unsigned char data_byte;
	unsigned char data[9];
	int32_t value = 0;

	for(int i=0; i<9; i++){
		AS3_RecvChar(&data_byte);
		data[i] = data_byte;
	}
	value = ((data[4]<<24) | (data[5]<<16) | (data[6]<<8) | (data[7]<<0));
	return value;
}

void Trinamic_Motion_Driver_Init(void){
	/* Initialisation of the Trinamic_Motion_Driver Task*/
	if(FRTOS1_xTaskCreate(Trinamic_Motion_Task, (signed portCHAR *)"Trinamic_Motion_Task", configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY, (xTaskHandle*)NULL) != pdPASS)
	{
		for(;;){}; /* Out of heap memory? */
	}
}
