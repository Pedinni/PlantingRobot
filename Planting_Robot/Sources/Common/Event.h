/**
 * \file
 * \brief Event driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic event driver. We are using numbered events starting with zero.
 * EVNT_HandleEvent() can be used to process the pending events. Note that the event with the number zero
 * has the highest priority and will be handled first
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "Application.h"

typedef enum EVNT_Handle {
	EVNT_STARTUP,            /*!< System startup Event */

	EVNT_BTN_9cm_PRESSED,
	EVNT_BTN_9cm_RELEASED,
	EVNT_BTN_9cm_LPRESSED,

	EVNT_BTN_11cm_PRESSED,
	EVNT_BTN_11cm_RELEASED,
    EVNT_BTN_11cm_LPRESSED,

	EVNT_BTN_12cm_PRESSED,
	EVNT_BTN_12cm_RELEASED,
    EVNT_BTN_12cm_LPRESSED,

	EVNT_BTN_13cm_PRESSED,
	EVNT_BTN_13cm_RELEASED,
    EVNT_BTN_13cm_LPRESSED,

	EVNT_BTN_14cm_PRESSED,
	EVNT_BTN_14cm_RELEASED,
    EVNT_BTN_14cm_LPRESSED,

	EVNT_BTN_AUTO_PRESSED,
	EVNT_BTN_AUTO_RELEASED,
    EVNT_BTN_AUTO_LPRESSED,

	EVNT_BTN_Setzeinheit_runter_PRESSED,
	EVNT_BTN_Setzeinheit_runter_RELEASED,
    EVNT_BTN_Setzeinheit_runter_LPRESSED,

	EVNT_BTN_Setzeinheit_hoch_PRESSED,
	EVNT_BTN_Setzeinheit_hoch_RELEASED,
    EVNT_BTN_Setzeinheit_hoch_LPRESSED,

	EVNT_BTN_Vereinzelung_PRESSED,
	EVNT_BTN_Vereinzelung_RELEASED,
    EVNT_BTN_Vereinzelung_LPRESSED,

	EVNT_BTN_tiefer_PRESSED,
	EVNT_BTN_tiefer_RELEASED,
    EVNT_BTN_tiefer_LPRESSED,

	EVNT_BTN_hoeher_PRESSED,
	EVNT_BTN_hoeher_RELEASED,
    EVNT_BTN_hoeher_LPRESSED,

	EVNT_NOF_EVENTS       /*!< Must be last one! */
} EVNT_Handle;

/*!
 * \brief Sets an event.
 * \param[in] event The handle of the event to set.
 */
void EVNT_SetEvent(EVNT_Handle event);

/*!
 * \brief Clears an event.
 * \param[in] event The event handle of the event to clear.
 */
void EVNT_ClearEvent(EVNT_Handle event);

/*!
 * \brief Returns the status of an event.
 * \param[in] event The event handler of the event to check.
 * \return TRUE if the event is set, FALSE otherwise.
 */
bool EVNT_EventIsSet(EVNT_Handle event);

/*!
 * \brief Returns the status of an event. As a side effect, the event gets cleared.
 * \param[in] event The event handler of the event to check.
 * \return TRUE if the event is set, FALSE otherwise.
 */
bool EVNT_EventIsSetAutoClear(EVNT_Handle event);

/*!
 * \brief Routine to check if an event is pending. If an event is pending, the event is cleared and the provided callback is called.
 * \param[in] callback Callback routine to be called. The event handle is passed as argument to the callback.
 * \param[in] clearEvent If TRUE, it will clear the event in the EVNT_HandleEvent(), otherwise not.
 */
void EVNT_HandleEvent(void (*callback)(EVNT_Handle), bool clearEvent);

/*! \brief Event module initialization */
void EVNT_Init(void);

/*! \brief Event module de-initialization */
void EVNT_Deinit(void);

#endif /* EVENT_H_ */
