/* ###################################################################
**     Filename    : main.c
**     Project     : Planting_Robot
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-22, 09:36, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "MCUC1.h"
#include "WAIT1.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "XF1.h"
#include "CS1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "SYS1.h"
#include "RTT1.h"
#include "AS2.h"
#include "ASerialLdd2.h"
#include "CLS2.h"
#include "Hall_Sensor.h"
#include "BitIoLdd2.h"
#include "BTN_9cm.h"
#include "BitIoLdd3.h"
#include "BTN_11cm.h"
#include "BitIoLdd4.h"
#include "BTN_12cm.h"
#include "BitIoLdd5.h"
#include "BTN_13cm.h"
#include "BitIoLdd6.h"
#include "BTN_14cm.h"
#include "BitIoLdd7.h"
#include "BTN_AUTO.h"
#include "BitIoLdd8.h"
#include "BTN_tiefer.h"
#include "BitIoLdd9.h"
#include "BTN_hoeher.h"
#include "BitIoLdd10.h"
#include "BTN_Setzeinheit_hoch.h"
#include "BitIoLdd11.h"
#include "BTN_Setzeinheit_runter.h"
#include "BitIoLdd12.h"
#include "BTN_Vereinzeln.h"
#include "BitIoLdd13.h"
#include "ION_Motion_Relais.h"
#include "BitIoLdd14.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "BitIoLdd15.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "BitIoLdd16.h"
#include "GI2C1.h"
#include "CI2C1.h"
#include "TMOUT1.h"
#include "BitIoLdd17.h"
#include "BTN_TC5.h"
#include "BitIoLdd19.h"
#include "PTE5_Pullup.h"
#include "PTA13_Pulldown.h"
#include "Vibra_Motor.h"
#include "BitIoLdd20.h"
#include "PTC.h"
#include "AS3.h"
#include "ASerialLdd3.h"
#include "CLS3.h"
#include "DC_OK.h"
#include "BitIoLdd18.h"
#include "Stop_IN.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Application.h"


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  APP_Start();

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
