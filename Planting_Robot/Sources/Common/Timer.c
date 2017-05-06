/**
 * \file
 * \brief Timer driver
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for all our timers.
  */

#include "Timer.h"
#include "Event.h"
#include "Trigger.h"

void TMR_OnInterrupt(void) {
	/* this one gets called from an interrupt!!!! */
	TRG_AddTick();
}

void TMR_Init(void) {
}

void TMR_Deinit(void) {
}
