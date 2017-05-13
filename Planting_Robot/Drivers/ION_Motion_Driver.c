/*
 * ION_Motion_Driver.c
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */

#include "ION_Motion_Driver.h"

#define address	0x80

#define position_Topf_9 	0
#define position_Topf_11 	1000
#define position_Topf_12 	2000
#define position_Topf_13 	3000
#define position_Topf_14 	4000

#define CountsVereinzelung	-3000
#define OffsetVereinzelung	-2068

#define InitSetzeinheitSpeed	60			// Geschwindigkeit mit welcher der Motor für die Setzeinheit auf den Anschlag zufährt
#define InitSetzeinheitCurrent	10			// Schwellwert ab welchem der Motor als blockiert eingestuft wird (Einheit auf Anschlag) 10 = 0.1A

ion_motion_data_t IONdata ={
		0,
		0,
		0,
		0,
		0,
		0
};

static void ION_Motion_Task(void *pvParameters) {
	(void)pvParameters; /* parameter not used */

	int currentM1 	= 0;
	int currentPos 	= 0;
	ION_Motion_Relais_SetVal();

	FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
	ION_Motion_Init_Setzeinheit();

	for(;;) {
		//setMotorSpeed(drive_setzeinheit_backward,100);
		//FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
		//getMotorCurrent();
		//FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
	}
}

/*
 * Nur zu Debugg Zwecken verwenden. Zu unsicher für den Feldbetrieb!!
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
		FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
	}
	for(int i = 0; i < 100; i++){
		setMotorSpeed(drive_vereinzelung_forward,100-i);
		FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
	}
}

void setPosition(ion_command_t command, position_t pos){
	int encodedPosition;

	switch(pos){
	case Topf_9:
		encodedPosition = position_Topf_9; break;
	case Topf_11:
		encodedPosition = position_Topf_11; break;
	case Topf_12:
		encodedPosition = position_Topf_12; break;
	case Topf_13:
		encodedPosition = position_Topf_13; break;
	case Topf_14:
		encodedPosition = position_Topf_14; break;
	case Counts_Vereinzelung:
		IONdata.EncoderVereinzelung += CountsVereinzelung;
		encodedPosition = IONdata.EncoderVereinzelung;
		break;
	case Offset_Vereinzelung:
		IONdata.EncoderVereinzelung += OffsetVereinzelung;
		encodedPosition = IONdata.EncoderVereinzelung;
		break;
	default:
		break;
	}

	int packetSize = 21;
	unsigned char packet[packetSize];
	unsigned short crc = 0;

	packet[0] = address;

	packet[1] = command;	// command

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
		packet[17-i] = (unsigned char)(encodedPosition>>(i*8));		// Position (4 Bytes)
	}

	packet[18] = 1;			//Buffer If a value of 1 is used the current running command is stopped,
							//any other commands in the buffer are deleted and the new command is executed.

	crc = crc16(packet,19);
	packet[19] = (char)(crc>>8);				// CRC1
	packet[20] = (char)crc;						// CRC2
	ION_Motion_sendPacket(packet, (&packet)[1]-packet);
}

/*
 * Initializes the "Vereinzelung" by turning the motor until the hall sensor gets a signal,
 * then clear the encoder counts and drive till the hole mask matches.
 */
void ION_Motion_Init_Vereinzelung(){
	setMotorSpeed(drive_vereinzelung_backward,100);
	while(Hall_Sensor_GetVal()){
		//ToDo: timeout einbauen
	}
	setEncoderValue(set_encoder_vereinzelung,0);
	FRTOS1_vTaskDelay(1/portTICK_RATE_MS);
	setMotorSpeed(drive_vereinzelung_backward,0);
	FRTOS1_vTaskDelay(1/portTICK_RATE_MS);
	setPosition(set_position_vereinzelung, Offset_Vereinzelung);
}

/*
 * Initializes the "Vereinzelung" by turning the motor until the hall sensor gets a signal,
 * then clear the encoder counts and drive till the hole mask matches.
 */
void ION_Motion_Init_Setzeinheit(){
	setMotorSpeed(drive_setzeinheit_backward, InitSetzeinheitSpeed);
	FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
	while(IONdata.Motor2Current < InitSetzeinheitCurrent){
		getMotorCurrent();
		//ToDo: timeout einbauen
	}
	setMotorSpeed(drive_setzeinheit_backward,0);
	setEncoderValue(set_encoder_setzeinheit,0);
	setPosition(set_position_setzeinheit, position_Topf_9);
}

/*
 * param command:	defines the command, modi
 * param speed:		0... 127 	0=stop / 127=fullspeed
 */
void setMotorSpeed(ion_command_t command, int speed){
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
 * param motor: FALSE = Motor 1 (Vereinzelung), TRUE = Motor 2 (Setzmechanik)
 */
void getMotorCurrent(void){
	ion_command_t command = read_motor_currents;
	unsigned char data = 0;
	int packetSize = 2;
	int current = 0;
	unsigned char packet[packetSize];

	packet[0] = address;
	packet[1] = command;			//Command: Read Motor Currents

	AS1_ClearRxBuf();				//clear GPS RX buffer, as it already could contain some data
	ION_Motion_sendPacket(packet, (&packet)[1]-packet);

	FRTOS1_vTaskDelay(10/portTICK_RATE_MS);		// Wait some time for the packet to get sent

	for(int i=3; i>=0; i--){
		AS1_RecvChar(&data);
		current = current | (int)(data<<(i*8));
	}

	while(AS1_GetCharsInRxBuf()!=0){
		AS1_RecvChar(&data);
	}

	for(int i=(numberOfCurrentSamples-1); i>0; i--){
		IONdata.Motor1CurrentSamples[i] = IONdata.Motor1CurrentSamples[i-1];
		IONdata.Motor2CurrentSamples[i] = IONdata.Motor2CurrentSamples[i-1];
	}

	IONdata.Motor1CurrentSamples[0] = current >> 16;
	IONdata.Motor2CurrentSamples[0] = current &  0xFFFF;

	int sum1 = 0, sum2 = 0;

	for(int i=0; i<numberOfCurrentSamples; i++){
		sum1 += IONdata.Motor1CurrentSamples[i];
		sum2 += IONdata.Motor2CurrentSamples[i];
	}

	IONdata.Motor1Current = sum1 / numberOfCurrentSamples;
	IONdata.Motor2Current = sum2 / numberOfCurrentSamples;
}

void setEncoderValue(ion_command_t command, int value){
	int packetSize = 8;
	unsigned char packet[packetSize];
	unsigned short crc = 0;

	packet[0] = address;
	packet[1] = command;

	packet[2] = (char)(value>>24);		// Encoder Value Byte 1... 4
	packet[3] = (char)(value>>16);
	packet[4] = (char)(value>>8);
	packet[5] = (char)(value>>0);

	crc = crc16(packet,6);
	packet[6] = (char)(crc>>8);			// CRC1
	packet[7] = (char)(crc>>0);			// CRC2

	ION_Motion_sendPacket(packet, (&packet)[1]-packet);
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
