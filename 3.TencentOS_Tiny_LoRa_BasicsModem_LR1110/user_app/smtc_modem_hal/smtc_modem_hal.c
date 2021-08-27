/*!
 * \file      smtc_modem_hal.c
 *
 * \brief     Modem Hardware Abstraction Layer API implementation.
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

#include "smtc_hal_adc.h"
#include "smtc_hal_flash.h"
#include "smtc_hal_gpio.h"
#include "smtc_hal_lp_timer.h"
#include "smtc_hal_mcu.h"
#include "smtc_hal_rng.h"
#include "smtc_hal_rtc.h"
#include "smtc_hal_trace.h"
#include "smtc_hal_uart.h"
#include "smtc_hal_watchdog.h"

#include "modem_pinout.h"

// for variadic args
#include <stdio.h>
#include <stdarg.h>

// for memcpy
#include <string.h>

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE MACROS-----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE CONSTANTS -------------------------------------------------------
 */
// STM32L431RCT6 Flash is 256KB
#define ADDR_FLASH_LORAWAN_CONTEXT ADDR_FLASH_PAGE_126
#define ADDR_FLASH_MODEM_CONTEXT ADDR_FLASH_PAGE_127
#define ADDR_FLASH_DEVNONCE_CONTEXT ADDR_FLASH_PAGE_125
/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE TYPES -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE VARIABLES -------------------------------------------------------
 */

static hal_gpio_irq_t radio_dio_irq;
uint8_t __attribute__( ( section( ".noinit" ) ) ) saved_crashlog[CRASH_LOG_SIZE];
volatile bool __attribute__( ( section( ".noinit" ) ) ) crashlog_available;

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DECLARATION -------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */

/* ------------ Reset management ------------*/
void smtc_modem_hal_reset_mcu( void )
{
    hal_mcu_reset( );
}

/* ------------ Watchdog management ------------*/

void smtc_modem_hal_reload_wdog( void )
{
    watchdog_reload( );
}

/* ------------ Time management ------------*/

void smtc_modem_hal_wait_us( const int32_t microseconds )
{
    hal_mcu_wait_us( microseconds );
}

uint32_t smtc_modem_hal_get_time_in_s( void )
{
    return hal_rtc_get_time_s( );
}

uint32_t smtc_modem_hal_get_compensate_time_in_s( void )
{
    return hal_rtc_get_time_s( );
}

int32_t smtc_modem_hal_get_time_compensation_in_s( void )
{
    return 0;
}

uint32_t smtc_modem_hal_get_time_in_ms( void )
{
    return hal_rtc_get_time_ms( );
}

/* ------------ Timer management ------------*/

void smtc_modem_hal_start_timer( const uint32_t milliseconds, void ( *callback )( void* context ), void* context )
{
    hal_lp_timer_start( milliseconds, &( hal_lp_timer_irq_t ){ .context = context, .callback = callback } );
}

void smtc_modem_hal_stop_timer( void )
{
    hal_lp_timer_stop( );
}

/* ------------ IRQ management ------------*/

void smtc_modem_hal_disable_modem_irq( void )
{
    hal_gpio_irq_disable( );
    hal_lp_timer_irq_disable( );
}

void smtc_modem_hal_enable_modem_irq( void )
{
    hal_gpio_irq_enable( );
    hal_lp_timer_irq_enable( );
}

void smtc_modem_hal_disable_all_irq( void )
{
    hal_mcu_disable_irq( );
}

void smtc_modem_hal_enable_all_irq( void )
{
    hal_mcu_enable_irq( );
}
/* ------------ Context saving management ------------*/

void smtc_modem_hal_context_restore( const modem_context_type_t ctx_type, uint8_t* buffer, const uint32_t size )
{
    switch( ctx_type )
    {
    case CONTEXT_MODEM:
        hal_flash_read_buffer( ADDR_FLASH_MODEM_CONTEXT, buffer, size );
        break;
    case CONTEXT_LR1MAC:
        hal_flash_read_buffer( ADDR_FLASH_LORAWAN_CONTEXT, buffer, size );
        break;
    case CONTEXT_DEVNONCE:
        hal_flash_read_buffer( ADDR_FLASH_DEVNONCE_CONTEXT, buffer, size );
        break;
    default:
        smtc_modem_hal_mcu_panic( );
        break;
    }
}

void smtc_modem_hal_context_store( const modem_context_type_t ctx_type, const uint8_t* buffer, const uint32_t size )
{
    switch( ctx_type )
    {
    case CONTEXT_MODEM:
        hal_flash_erase_page( ADDR_FLASH_MODEM_CONTEXT, 1 );
        hal_flash_write_buffer( ADDR_FLASH_MODEM_CONTEXT, buffer, size );
        break;
    case CONTEXT_LR1MAC:
        hal_flash_erase_page( ADDR_FLASH_LORAWAN_CONTEXT, 1 );
        hal_flash_write_buffer( ADDR_FLASH_LORAWAN_CONTEXT, buffer, size );
        break;
    case CONTEXT_DEVNONCE:
        hal_flash_erase_page( ADDR_FLASH_DEVNONCE_CONTEXT, 1 );
        hal_flash_write_buffer( ADDR_FLASH_DEVNONCE_CONTEXT, buffer, size );
        break;
    default:
        smtc_modem_hal_mcu_panic( );
        break;
    }
}

/* ------------ Crashlog management ------------*/

void smtc_modem_hal_store_crashlog( uint8_t crashlog[CRASH_LOG_SIZE] )
{
    memcpy( &saved_crashlog, crashlog, CRASH_LOG_SIZE );
}

void smtc_modem_hal_restore_crashlog( uint8_t crashlog[CRASH_LOG_SIZE] )
{
    memcpy( crashlog, &saved_crashlog, CRASH_LOG_SIZE );
}

void smtc_modem_hal_set_crashlog_status( bool available )
{
    crashlog_available = available;
}

bool smtc_modem_hal_get_crashlog_status( void )
{
    return crashlog_available;
}

/* ------------ Random management ------------*/

uint32_t smtc_modem_hal_get_random_nb( void )
{
    return hal_rng_get_random( );
}

uint32_t smtc_modem_hal_get_random_nb_in_range( const uint32_t val_1, const uint32_t val_2 )
{
    return hal_rng_get_random_in_range( val_1, val_2 );
}

int32_t smtc_modem_hal_get_signed_random_nb_in_range( const int32_t val_1, const int32_t val_2 )
{
    return hal_rng_get_signed_random_in_range( val_1, val_2 );
}

/* ------------ Radio env management ------------*/

void smtc_modem_hal_irq_config_radio_irq( void ( *callback )( void* context ), void* context )
{
    radio_dio_irq.pin      = RADIO_DIOX;
    radio_dio_irq.callback = callback;
    radio_dio_irq.context  = context;

    hal_gpio_irq_attach( &radio_dio_irq );
}

bool smtc_modem_hal_irq_is_radio_irq_pending( void )
{
    return hal_gpio_is_pending_irq( RADIO_DIOX );
}

void smtc_modem_hal_start_radio_tcxo( void )
{
    // put here the code that will start the tcxo if needed
}

void smtc_modem_hal_stop_radio_tcxo( void )
{
    // put here the code that will stop the tcxo if needed
}

/* ------------ Environment management ------------*/

uint8_t smtc_modem_hal_get_battery_level( void )
{
    return 254;
}

int8_t smtc_modem_hal_get_temperature( void )
{
//    int8_t temperature;
//    hal_adc_init( );
//    temperature = hal_adc_get_temp( );
//    hal_adc_deinit( );
//    return temperature;
    
    return 0;
}

uint8_t smtc_modem_hal_get_voltage( void )
{
//    uint16_t measure_vref_mv = 0;
//    hal_adc_init( );
//    measure_vref_mv = hal_adc_get_vref_int( );
//    hal_adc_deinit( );

//    // convert voltage from mv to cloud readable (1/50V = 20mv)
//    return ( uint8_t )( measure_vref_mv / 20 );
    
    return 0;
}

/* ------------ Trace management ------------*/

void smtc_modem_hal_print_trace( const char* fmt, ... )
{
    va_list args;
    va_start( args, fmt );
    hal_trace_print( fmt, args );
    va_end( args );
}

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DEFINITION --------------------------------------------
 */

/* --- EOF ------------------------------------------------------------------ */
