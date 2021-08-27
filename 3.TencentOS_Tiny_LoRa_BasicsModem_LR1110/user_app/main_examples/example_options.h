/**
 * @file      example_options.h
 *
 * @brief     User options to be used in example applications
 *
 * Revised BSD License
 * Copyright Semtech Corporation 2020. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Semtech corporation nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef EXAMPLE_OPTIONS_H
#define EXAMPLE_OPTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdint.h>   // C99 types
#include <stdbool.h>  // bool type

#include "smtc_modem_api.h"
/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

// clang-format off

/**
 * @brief LoRaWAN User credentials
 * 
 */
#define USER_LORAWAN_DEVICE_EUI     { 0x20, 0x21, 0x08, 0x25, 0x20, 0x21, 0x08, 0x25 }
#define USER_LORAWAN_JOIN_EUI       { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
#define USER_LORAWAN_APP_KEY        { 0x20, 0x21, 0x08, 0x25, 0x20, 0x21, 0x08, 0x25, \
                                      0x20, 0x21, 0x08, 0x25, 0x20, 0x21, 0x08, 0x25 }

// 1A 66 3C 77 2D 88 40 F0                           
// 1A 2B 3C 4D 5E 6F 7A 8B 9C A1 B2 C3 D4 E5 F6 88

/**
 * @brief Modem Region define
 * 
 */
#if defined( CHINA_RP_1_DEMO )
#define MODEM_EXAMPLE_REGION    SMTC_MODEM_REGION_CN_470_RP_1_0
#else
#define MODEM_EXAMPLE_REGION    SMTC_MODEM_REGION_EU_868
#endif


/**
 * @brief Modem GNSS assistance position defines
 * @remark Only used in GNSS and GEOLOCATION example with lr1110 transceiver
 */

#if defined( CHINA_RP_1_DEMO )
#define MODEM_EXAMPLE_ASSISTANCE_POSITION_LAT  (22.531529)
#define MODEM_EXAMPLE_ASSISTANCE_POSITION_LONG  (113.950881)
#define MODEM_EXAMPLE_ASSISTANCE_POSITION_TEXT  "ShenZhen, CHINA"
#else
#define MODEM_EXAMPLE_ASSISTANCE_POSITION_LAT  (45.181454)
#define MODEM_EXAMPLE_ASSISTANCE_POSITION_LONG  (5.720893)
#define MODEM_EXAMPLE_ASSISTANCE_POSITION_TEXT  "Grenoble, FRANCE"
#endif

// clang-format on

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */

#ifdef __cplusplus
}
#endif

#endif  // EXAMPLE_OPTIONS_H

/* --- EOF ------------------------------------------------------------------ */
