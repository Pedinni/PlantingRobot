/*
 * LED_Driver.c
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */


#include "LED_Driver.h"


static void LED_Task(void *pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}
