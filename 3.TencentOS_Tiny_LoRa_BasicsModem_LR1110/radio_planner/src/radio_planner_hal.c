/*!
 * \file      radio_planner_hal.c
 *
 * \brief     Implements the Radio planner Hardware Abstraction Layer functions
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
 * ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdint.h>   // C99 types
#include <stdbool.h>  // bool type

#include "smtc_modem_hal.h"
#include "radio_planner_hal.h"

#if defined( _GNSS_SNIFF_ENABLE )
#if defined( LR1110_MODEM )
#include "gnss_ctrl_api.h"
#include "wifi_ctrl_api.h"
#elif defined( LR1110_TRANSCEIVER )
#include "lr1110_gnss_types.h"
#include "lr1110_gnss.h"
#else
#error "GNSS functionality can't be used !"
#endif
#endif  // _GNSS_SNIFF_ENABLE

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE MACROS-----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE CONSTANTS -------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE TYPES -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE VARIABLES -------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DECLARATION -------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */

void rp_hal_critical_section_begin( void )
{
    smtc_modem_hal_disable_modem_irq( );
}

void rp_hal_critical_section_end( void )
{
    smtc_modem_hal_enable_modem_irq( );
}

void rp_hal_timer_stop( void )
{
    smtc_modem_hal_stop_timer( );
}

void rp_hal_timer_start( void* rp, uint32_t alarm_in_ms, void ( *callback )( void* context ) )
{
    smtc_modem_hal_start_timer( alarm_in_ms, callback, rp );
}

uint32_t rp_hal_timestamp_get( void )
{
    return smtc_modem_hal_get_time_in_ms( );
}

uint8_t rp_hal_irq_get_pending( void )
{
    return smtc_modem_hal_irq_is_radio_irq_pending( ) ? 1 : 0;
}

#if defined( LR1110_MODEM )

#if defined( _GNSS_SNIFF_ENABLE )
void rp_hal_get_gnss_conso_us( uint32_t* p_radio_t, uint32_t* p_arc_process_t )
{
    Gnss_get_conso_us( p_radio_t, p_arc_process_t );
}
#endif  // _GNSS_SNIFF_ENABLE

#if defined( _WIFI_SNIFF_ENABLE )
void rp_hal_get_wifi_conso_us( uint32_t* p_radio_t, uint32_t* p_arc_process_t )
{
    Wifi_get_conso_us( p_radio_t, p_arc_process_t );
}
#endif  // _WIFI_SNIFF_ENABLE

#endif  // LR1110_MODEM

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DEFINITION --------------------------------------------
 */

/* --- EOF ------------------------------------------------------------------ */
