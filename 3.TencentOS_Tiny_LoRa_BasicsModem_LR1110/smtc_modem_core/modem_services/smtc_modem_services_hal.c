/**
 * @file      smtc_modem_services_hal.c
 *
 * @brief     Implementation of smtc_modem_services hal functions
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

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdint.h>   // C99 types
#include <stdbool.h>  // bool type
#include <string.h>   // memcpy, memset
// for variadic args
#include <stdio.h>
#include <stdarg.h>

#include "smtc_modem_services_hal.h"
#include "smtc_crypto.h"
#include "smtc_modem_hal.h"
#include "modem_context.h"

#if defined( _GNSS_SNIFF_ENABLE )
#if defined( LR1110_TRANSCEIVER )
#include "lr1110_gnss.h"
#endif
#endif  //_GNSS_SNIFF_ENABLE

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

void smtc_modem_services_aes_encrypt( const uint8_t* raw_buffer, uint16_t size, const uint8_t* key,
                                      uint8_t aes_ctr_nonce[14], uint8_t* enc_buffer )
{
    uint32_t address = ( uint32_t )( aes_ctr_nonce[6] ) | ( uint32_t )( aes_ctr_nonce[7] << 8 ) |
                       ( uint32_t )( aes_ctr_nonce[8] << 16 ) | ( uint32_t )( aes_ctr_nonce[9] << 24 );
    uint8_t  dir              = aes_ctr_nonce[5];
    uint32_t sequence_counter = ( uint32_t )( aes_ctr_nonce[10] ) | ( uint32_t )( aes_ctr_nonce[11] << 8 ) |
                                ( uint32_t )( aes_ctr_nonce[12] << 16 ) | ( uint32_t )( aes_ctr_nonce[13] << 24 );
    // lora_crypto can be used here
    lora_crypto_payload_encrypt( raw_buffer, size, key, address, dir, sequence_counter, enc_buffer );
}

uint32_t smtc_modem_services_get_time_s( void )
{
    return smtc_modem_hal_get_compensate_time_in_s( );
}

uint32_t smtc_modem_services_get_dm_upload_sctr( void )
{
    return modem_get_dm_upload_sctr( );
}

void smtc_modem_services_set_dm_upload_sctr( uint32_t ctr )
{
    modem_set_dm_upload_sctr( ctr );
}
#if defined( _GNSS_SNIFF_ENABLE )
#if defined( LR1110_TRANSCEIVER )
radio_return_code_t smtc_modem_services_lr1110_gnss_get_context_status( const void* radio_ctx, uint8_t buff[9] )
{
    if( lr1110_gnss_get_context_status( radio_ctx, buff ) != LR1110_STATUS_OK )
    {
        return MODEM_SERVICES_RADIO_ERROR;
    }
    return MODEM_SERVICES_RADIO_OK;
}

radio_return_code_t smtc_modem_services_lr1110_gnss_push_dmc_msg( const void* radio_ctx, uint8_t* buff,
                                                                  uint16_t buff_len )
{
    if( lr1110_gnss_push_dmc_msg( radio_ctx, buff, buff_len ) != LR1110_STATUS_OK )
    {
        return MODEM_SERVICES_RADIO_ERROR;
    }
    return MODEM_SERVICES_RADIO_OK;
}
#endif
#endif  //_GNSS_SNIFF_ENABLE
/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DEFINITION --------------------------------------------
 */

/* --- EOF ------------------------------------------------------------------ */
