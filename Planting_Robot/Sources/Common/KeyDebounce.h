/**
 * \file
 * \brief Key debouncing interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements debouncing for multiple keys.
 */

#ifndef KEYDEBOUNCE_H_
#define KEYDEBOUNCE_H_

#include "Application.h"

#include "BTN_9cm.h"
#include "BTN_11cm.h"
#include "BTN_12cm.h"
#include "BTN_13cm.h"
#include "BTN_14cm.h"
#include "BTN_AUTO.h"
#include "BTN_Setzeinheit_hoch.h"
#include "BTN_Setzeinheit_runter.h"
#include "BTN_Vereinzeln.h"
#include "BTN_hoeher.h"
#include "BTN_tiefer.h"

/*!
 * \brief Kicks the debouncing state machine.
 */
void KEYDBNC_Process(void);

/*!
 * \brief Driver initialization.
 */
void KEYDBNC_Init(void);

/*!
 * \brief Driver de-initialization.
 */
void KEYDBNC_Deinit(void);
#endif /* PL_CONFIG_HAS_DEBOUNCE */

