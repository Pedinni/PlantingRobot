/**
 * \file
 * \brief Key debouncing implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements debouncing of up to 4 Keys.
 */

#include "KeyDebounce.h"
//#include "Keys.h"
#include "Debounce.h"
#include "Trigger.h"
#include "Event.h"
#include "FRTOS1.h"

/*!
 * \brief Returns the state of the keys. This directly reflects the value of the port
 * \return Port bits
 */
static DBNC_KeySet KEYDBNC_GetKeys(void) {
  DBNC_KeySet keys = 0;
  	  keys =  ((int)!BTN_9cm_GetVal()  << 0) +
  			  ((int)!BTN_11cm_GetVal() << 1) +
			  ((int)!BTN_12cm_GetVal() << 2) +
			  ((int)!BTN_13cm_GetVal() << 3) +
			  ((int)!BTN_14cm_GetVal() << 4) +
			  ((int)!BTN_AUTO_GetVal() << 5) +

			  ((int)!BTN_Setzeinheit_runter_GetVal() << 6) +
			  ((int)!BTN_Setzeinheit_hoch_GetVal() 	 << 7) +
			  ((int)!BTN_Vereinzeln_GetVal() 		 << 8) +

			  ((int)!BTN_tiefer_GetVal() << 9) +
			  ((int)!BTN_hoeher_GetVal() << 10);
  return keys;
}

/*!
 * \brief Event called in the event of a long key press detected.
 * \param keys The keyboard port content
 * \param event The event kind
 */
static void KEYDBNC_OnDebounceEvent(DBNC_EventKinds event, DBNC_KeySet keys) {
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  {
    uint8_t buf[48];

    UTIL1_strcpy(buf, sizeof(buf), "KEYDBNC_OnDebounceEvent: ");
    UTIL1_strcatNum32u(buf, sizeof(buf), event);
    UTIL1_strcat(buf, sizeof(buf), ", keys: ");
    UTIL1_strcatNum32u(buf, sizeof(buf), keys);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
    SYS1_Print(buf);
  }
#endif
  switch(event) {
    /* pressed */
    case DBNC_EVENT_PRESSED:
      if (keys&(1<<0)) {
        EVNT_SetEvent(EVNT_BTN_9cm_PRESSED);
      } if (keys&(1<<1)) {
        EVNT_SetEvent(EVNT_BTN_11cm_PRESSED);
      } if (keys&(1<<2)) {
        EVNT_SetEvent(EVNT_BTN_12cm_PRESSED);
      } if (keys&(1<<3)) {
        EVNT_SetEvent(EVNT_BTN_13cm_PRESSED);
      } if (keys&(1<<4)) {
        EVNT_SetEvent(EVNT_BTN_14cm_PRESSED);
      } if (keys&(1<<5)) {
        EVNT_SetEvent(EVNT_BTN_AUTO_PRESSED);
      } if (keys&(1<<6)) {
        EVNT_SetEvent(EVNT_BTN_Setzeinheit_runter_PRESSED);
      } if (keys&(1<<7)) {
          EVNT_SetEvent(EVNT_BTN_Setzeinheit_hoch_PRESSED);
      } if (keys&(1<<8)) {
          EVNT_SetEvent(EVNT_BTN_Vereinzelung_PRESSED);
      } if (keys&(1<<9)) {
          EVNT_SetEvent(EVNT_BTN_tiefer_PRESSED);
      } if (keys&(1<<10)) {
          EVNT_SetEvent(EVNT_BTN_hoeher_PRESSED);
      }
      break;

    /* long pressed */
    case DBNC_EVENT_LONG_PRESSED:
    if (keys&(1<<0)) {
    	EVNT_SetEvent(EVNT_BTN_9cm_LPRESSED);
    } if (keys&(1<<1)) {
        EVNT_SetEvent(EVNT_BTN_11cm_LPRESSED);
    } if (keys&(1<<2)) {
        EVNT_SetEvent(EVNT_BTN_12cm_LPRESSED);
    } if (keys&(1<<3)) {
        EVNT_SetEvent(EVNT_BTN_13cm_LPRESSED);
    } if (keys&(1<<4)) {
        EVNT_SetEvent(EVNT_BTN_14cm_LPRESSED);
    } if (keys&(1<<5)) {
        EVNT_SetEvent(EVNT_BTN_AUTO_LPRESSED);
    } if (keys&(1<<6)) {
        EVNT_SetEvent(EVNT_BTN_Setzeinheit_runter_LPRESSED);
    } if (keys&(1<<7)) {
        EVNT_SetEvent(EVNT_BTN_Setzeinheit_hoch_LPRESSED);
    } if (keys&(1<<8)) {
        EVNT_SetEvent(EVNT_BTN_Vereinzelung_LPRESSED);
    } if (keys&(1<<9)) {
        EVNT_SetEvent(EVNT_BTN_hoeher_LPRESSED);
    } if (keys&(1<<10)) {
        EVNT_SetEvent(EVNT_BTN_tiefer_LPRESSED);
    }
     break;

     /* released */
    case DBNC_EVENT_RELEASED:
    if (keys&(1<<0)) {
    	EVNT_SetEvent(EVNT_BTN_9cm_RELEASED);
    } if (keys&(1<<1)) {
        EVNT_SetEvent(EVNT_BTN_11cm_RELEASED);
    } if (keys&(1<<2)) {
        EVNT_SetEvent(EVNT_BTN_12cm_RELEASED);
    } if (keys&(1<<3)) {
        EVNT_SetEvent(EVNT_BTN_13cm_RELEASED);
    } if (keys&(1<<4)) {
        EVNT_SetEvent(EVNT_BTN_14cm_RELEASED);
    } if (keys&(1<<5)) {
        EVNT_SetEvent(EVNT_BTN_AUTO_RELEASED);
    } if (keys&(1<<6)) {
        EVNT_SetEvent(EVNT_BTN_Setzeinheit_runter_RELEASED);
    } if (keys&(1<<7)) {
        EVNT_SetEvent(EVNT_BTN_Setzeinheit_hoch_RELEASED);
    } if (keys&(1<<8)) {
        EVNT_SetEvent(EVNT_BTN_Vereinzelung_RELEASED);
    } if (keys&(1<<9)) {
        EVNT_SetEvent(EVNT_BTN_hoeher_RELEASED);
    } if (keys&(1<<10)) {
        EVNT_SetEvent(EVNT_BTN_tiefer_RELEASED);
    }
      break;
    case DBNC_EVENT_END:
      /*! \todo Implement what you have to do at the end of the debouncing. Check if you have to re-enable interrupts! */
    #if PL_CONFIG_HAS_KBI
      KEY_EnableInterrupts();
    #endif
      break;
  } /* switch */
}

/*! \brief This struct contains all the data and pointers needed to have
 *         our debounce FSM reentrant and usable for multiple ISR's.
 */
static DBNC_FSMData KEYDBNC_FSMdata = {
  /* callbacks: */
  KEYDBNC_GetKeys, /* returns bit set of pressed keys */
  KEYDBNC_OnDebounceEvent, /* event callback */
  /* data: */
  DBNC_KEY_IDLE, /* initial state machine state, here the state is stored */
  0, /* key scan value */
  0, /* long key count */
  TRG_KEYPRESS, /* trigger to be used */
  (50/TRG_TICKS_MS), /* debounceTicks */
  (500/TRG_TICKS_MS), /* longKeyTicks for x ms */
};

void KEYDBNC_Process(void) {
  /** \todo check/call DBNC_Process(&KEYDBNC_FSMdata);
   * But be careful: only if we are not debouncing, and if we have a key press if we are polling.
   * And you will need to disable the keyboard interrupts too!
   */
  /*! \todo Only debounce if you are not debouncing already */
  if (KEYDBNC_FSMdata.state==DBNC_KEY_IDLE && KEYDBNC_GetKeys()!=0) { /* a key is pressed and we are not debouncing */
	  DBNC_Process(&KEYDBNC_FSMdata); /* starts the state machine */
  }
}

void KEYDBNC_Init(void) {
  KEYDBNC_FSMdata.state = DBNC_KEY_IDLE;
}

void KEYDBNC_Deinit(void) {
  /* nothing needed */
}
