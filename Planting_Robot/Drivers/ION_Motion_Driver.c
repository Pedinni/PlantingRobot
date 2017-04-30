/*
 * ION_Motion_Driver.c
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */

#include "ION_Motion_Driver.h"

#define address	0x80

static void ION_Motion_Task(void *pvParameters) {
	(void)pvParameters; /* parameter not used */
	int currentM1 = 0;
	for(;;) {
#if 1
		currentM1 = getMotor1Current();
		FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
#endif
#if 0
		setPosition(Topf_9);
		FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);

		setPosition(Topf_11);
		FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);

		setPosition(Topf_12);
		FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);

		setPosition(Topf_13);
		FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);

		setPosition(Topf_14);
		FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);
#endif

	}
}

/*
 * Nur zu Debugg Zwecken verwenden. Zu unsicher f�r den Feldbetrieb!!
 *
 * Diese Methode funktioniert nur wenn der Motor Controller auf Simple Serial konfiguriert ist.
 * In diesem Betriebsmodus kann lediglich ein 1 Byte langer Befehl gesendet werden, welcher
 * das Motoren PWM steuert. Auch wird keine Checksumme berechnet und der TX Pin des Motor
 * Controllers wird nicht angeschlossen.
 *
 * In this mode S1 accepts TTL level byte commands. Standard serial mode is one way serial data.
 * RoboClaw can receive only. A standard 8N1 format is used. Which is 8 bits, no parity bits and
 * 1 stop bit.
 */
void ION_SimpleSerialTest(void){
	unsigned char packet[3];
	packet[0] = 64;				// stop
	packet[1] = 1;				// full reverse
	packet[2] = 127;			// full forward

	CLS1_SendChar(packet[0]);
	LED1_Off();
	FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);

	CLS1_SendChar(packet[1]);
	LED1_On();
	FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);
}

/*
 * Packet serial is a buffered bidirectional serial mode. More sophisticated instructions can be sent
 * to RoboClaw. The basic command structures consist of an address byte, command byte, data
 * bytes and a CRC16 16bit checksum. The amount of data each command will send or receive can
 * vary.
 */
void ION_PacketSerialTest(void){
	setMotorSpeed(drive_vereinzelung_forward,0);
	LED1_Off();
	FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);

	LED1_On();
	for(int i = 0; i < 100; i++){
		setMotorSpeed(drive_vereinzelung_forward,i);
		FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
	}
	for(int i = 0; i < 100; i++){
		setMotorSpeed(drive_vereinzelung_forward,100-i);
		FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
	}
}

void setPosition(position_t pos){
	int packetSize = 21;
	unsigned char packet[packetSize];
	unsigned short crc = 0;

	packet[0] = address;

	packet[1] = 65;			// command

	packet[2] = 0;			// Accel (4 Bytes)
	packet[3] = 0;
	packet[4] = 0;
	packet[5] = 0;

	packet[6] = 0;			// Speed (4 Bytes)
	packet[7] = 0;
	packet[8] = 0;
	packet[9] = 0;

	packet[10] = 0;			// Deccel (4 Bytes)
	packet[11] = 0;
	packet[12] = 0;
	packet[13] = 0;

	for(int i = 0; i < 4; i++){
		packet[17-i] = (unsigned char)(pos>>(i*8));		// Position (4 Bytes)
	}

	packet[18] = 1;

	crc = crc16(packet,19);
	packet[19] = (char)(crc>>8);				// CRC1
	packet[20] = (char)crc;						// CRC2
	ION_Motion_sendPacket(packet, (&packet)[1]-packet);
}

/*
 * param command:	defines the command, modi
 * param speed:		0... 127 	0=stop / 127=fullspeed
 */
void setMotorSpeed(command_t command, int speed){
	int packetSize = 5;
	unsigned char packet[packetSize];
	unsigned short crc = 0;

	packet[0] = address;
	packet[1] = command;

	if(speed > 127){
		packet[2] = 127;
	}
	else if(speed < 0){
		packet[2] = 0;
	} else{
		packet[2] = speed;
	}

	crc = crc16(packet,3);
	packet[3] = (char)(crc>>8);				// CRC1
	packet[4] = (char)crc;					// CRC2

	ION_Motion_sendPacket(packet, (&packet)[1]-packet);
}

/*
 * param command:	defines the command, modi
 * param speed:		0... 127 	0=stop / 127=fullspeed
 */
int getMotor1Current(){
	unsigned char data;
	int current = 0, packetSize = 2;
	unsigned char packet[packetSize];

	packet[0] = address;
	packet[1] = 49;					//Command: Read Motor Currents

	AS1_ClearRxBuf();				//clear GPS RX buffer, as it already could contain some data
	ION_Motion_sendPacket(packet, (&packet)[1]-packet);

	FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);

	while(AS1_GetCharsInRxBuf()!=0){
		if(AS1_RecvChar(&data)==ERR_OK){

		} else{
			for(;;){}		// Cant receive char
		}
	}
/*	AS1_RecvChar(&data);
	current = (int)data;
	AS1_RecvChar(&data);
	current = current<<8 & (int)data;

	for(int i = 0; i < 4; i++){
		AS1_RecvChar(&data);
	}
	*/
	return current/100;			//Datasheet p. 71
}

/*
 * Sends a char packet to the Driver
 */
void ION_Motion_sendPacket(unsigned char packet[], int packetlength){
		for(int i=0; i<packetlength; i++){
			CLS1_SendChar(packet[i]);
		}
}

/*
 * Calculates CRC16 of nBytes of data in byte array message
 */
unsigned short crc16(unsigned char *packet, int nBytes) {
	unsigned short crc = 0;
	for (int byte = 0; byte < nBytes; byte++) {
		crc = crc ^ ((unsigned short)packet[byte] << 8);
		for (unsigned char bit = 0; bit < 8; bit++) {
			if (crc & 0x8000) {
				crc = (crc << 1) ^ 0x1021;
			} else {
				crc = crc << 1;
			}
		}
	}
	return crc;
}

void ION_Motion_Driver_Init(void){
	/* Initialisation of the IR_Sensor_Driver Task*/
	if (FRTOS1_xTaskCreate(
		ION_Motion_Task,  /* pointer to the task */
	    (signed portCHAR *)"ION_Motion_Task", /* task name for kernel awareness debugging */
	    configMINIMAL_STACK_SIZE, /* task stack size */
	    (void*)NULL, /* optional task startup argument */
	    tskIDLE_PRIORITY,  /* initial priority */
	    (xTaskHandle*)NULL /* optional task handle to create */
	) != pdPASS)
	{
		for(;;){}; /* Out of heap memory? */
	}
}
