/**
 * @file      ral_sx126x.h
 *
 * @brief     Radio abstraction layer definition
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

#ifndef RAL_SX126X_H__
#define RAL_SX126X_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdint.h>
#include <stdbool.h>
#include "ral_defs.h"

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

#define RAL_SX126X_DRV_INSTANTIATE                                                                                    \
    {                                                                                                                 \
        .handles_part = ral_sx126x_handles_part, .reset = ral_sx126x_reset, .init = ral_sx126x_init,                  \
        .wakeup = ral_sx126x_wakeup, .set_sleep = ral_sx126x_set_sleep, .set_standby = ral_sx126x_set_standby,        \
        .set_fs = ral_sx126x_set_fs, .set_tx = ral_sx126x_set_tx, .set_rx = ral_sx126x_set_rx,                        \
        .set_rx_tx_fallback_mode = ral_sx126x_set_rx_tx_fallback_mode,                                                \
        .stop_timer_on_preamble  = ral_sx126x_stop_timer_on_preamble,                                                 \
        .set_rx_duty_cycle = ral_sx126x_set_rx_duty_cycle, .set_lora_cad = ral_sx126x_set_lora_cad,                   \
        .set_tx_cw = ral_sx126x_set_tx_cw, .set_tx_infinite_preamble = ral_sx126x_set_tx_infinite_preamble,           \
        .set_tx_cfg = ral_sx126x_set_tx_cfg, .set_pkt_payload = ral_sx126x_set_pkt_payload,                           \
        .get_pkt_payload = ral_sx126x_get_pkt_payload, .get_irq_status = ral_sx126x_get_irq_status,                   \
        .clear_irq_status         = ral_sx126x_clear_irq_status,                                                      \
        .get_and_clear_irq_status = ral_sx126x_get_and_clear_irq_status,                                              \
        .set_dio_irq_params = ral_sx126x_set_dio_irq_params, .set_rf_freq = ral_sx126x_set_rf_freq,                   \
        .set_pkt_type = ral_sx126x_set_pkt_type, .set_gfsk_mod_params = ral_sx126x_set_gfsk_mod_params,               \
        .set_gfsk_pkt_params = ral_sx126x_set_gfsk_pkt_params, .set_lora_mod_params = ral_sx126x_set_lora_mod_params, \
        .set_lora_pkt_params = ral_sx126x_set_lora_pkt_params, .set_lora_cad_params = ral_sx126x_set_lora_cad_params, \
        .set_lora_symb_nb_timeout = ral_sx126x_set_lora_symb_nb_timeout,                                              \
        .set_flrc_mod_params = ral_sx126x_set_flrc_mod_params, .set_flrc_pkt_params = ral_sx126x_set_flrc_pkt_params, \
        .get_gfsk_rx_pkt_status = ral_sx126x_get_gfsk_rx_pkt_status,                                                  \
        .get_lora_rx_pkt_status = ral_sx126x_get_lora_rx_pkt_status,                                                  \
        .get_flrc_rx_pkt_status = ral_sx126x_get_flrc_rx_pkt_status, .get_rssi_inst = ral_sx126x_get_rssi_inst,       \
        .get_lora_time_on_air_in_ms = ral_sx126x_get_lora_time_on_air_in_ms,                                          \
        .get_gfsk_time_on_air_in_ms = ral_sx126x_get_gfsk_time_on_air_in_ms,                                          \
        .get_flrc_time_on_air_in_ms = ral_sx126x_get_flrc_time_on_air_in_ms,                                          \
        .set_gfsk_sync_word = ral_sx126x_set_gfsk_sync_word, .set_lora_sync_word = ral_sx126x_set_lora_sync_word,     \
        .set_flrc_sync_word = ral_sx126x_set_flrc_sync_word, .set_gfsk_crc_params = ral_sx126x_set_gfsk_crc_params,   \
        .set_flrc_crc_params           = ral_sx126x_set_flrc_crc_params,                                              \
        .set_gfsk_whitening_seed       = ral_sx126x_set_gfsk_whitening_seed,                                          \
        .get_tx_consumption_in_ua      = ral_sx126x_get_tx_consumption_in_ua,                                         \
        .get_gfsk_rx_consumption_in_ua = ral_sx126x_get_gfsk_rx_consumption_in_ua,                                    \
        .get_lora_rx_consumption_in_ua = ral_sx126x_get_lora_rx_consumption_in_ua,                                    \
    }

#define RAL_SX126X_INSTANTIATE( ctx )                         \
    {                                                         \
        .context = ctx, .driver = RAL_SX126X_DRV_INSTANTIATE, \
    }

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */

/**
 * @see ral_handles_part
 */
bool ral_sx126x_handles_part( const char* part_number );

/**
 * @see ral_reset
 */
ral_status_t ral_sx126x_reset( const void* context );

/**
 * @see ral_init
 */
ral_status_t ral_sx126x_init( const void* context );

/**
 * @see ral_wakeup
 */
ral_status_t ral_sx126x_wakeup( const void* context );

/**
 * @see ral_set_sleep
 */
ral_status_t ral_sx126x_set_sleep( const void* context, const bool retain_config );

/**
 * @see ral_set_standby
 */
ral_status_t ral_sx126x_set_standby( const void* context, ral_standby_cfg_t standby_cfg );

/**
 * @see ral_set_fs
 */
ral_status_t ral_sx126x_set_fs( const void* context );

/**
 * @see ral_set_tx
 */
ral_status_t ral_sx126x_set_tx( const void* context );

/**
 * @see ral_set_rx
 */
ral_status_t ral_sx126x_set_rx( const void* context, const uint32_t timeout_in_ms );

/**
 * @see ral_set_rx_tx_fallback_mode
 */
ral_status_t ral_sx126x_set_rx_tx_fallback_mode( const void* context, const ral_fallback_modes_t ral_fallback_mode );

/**
 * @see ral_stop_timer_on_preamble
 */
ral_status_t ral_sx126x_stop_timer_on_preamble( const void* context, const bool enable );

/**
 * @see ral_set_rx_duty_cycle
 */
ral_status_t ral_sx126x_set_rx_duty_cycle( const void* context, const uint32_t rx_time_in_ms,
                                           const uint32_t sleep_time_in_ms );

/**
 * @see ral_set_lora_cad
 */
ral_status_t ral_sx126x_set_lora_cad( const void* context );

/**
 * @see ral_set_tx_cw
 */
ral_status_t ral_sx126x_set_tx_cw( const void* context );

/**
 * @see ral_set_tx_infinite_preamble
 */
ral_status_t ral_sx126x_set_tx_infinite_preamble( const void* context );

/**
 * @see ral_set_tx_cfg
 */
ral_status_t ral_sx126x_set_tx_cfg( const void* context, const int8_t output_pwr_in_dbm, const uint32_t rf_freq_in_hz );

/**
 * @see ral_set_pkt_payload
 */
ral_status_t ral_sx126x_set_pkt_payload( const void* context, const uint8_t* buffer, const uint16_t size );

/**
 * @see ral_get_pkt_payload
 */
ral_status_t ral_sx126x_get_pkt_payload( const void* context, uint16_t max_size_in_bytes, uint8_t* buffer,
                                         uint16_t* size_in_bytes );

/**
 * @see ral_get_irq_status
 */
ral_status_t ral_sx126x_get_irq_status( const void* context, ral_irq_t* irq );

/**
 * @see ral_clear_irq_status
 */
ral_status_t ral_sx126x_clear_irq_status( const void* context, const ral_irq_t irq );

/**
 * @see ral_get_and_clear_irq_status
 */
ral_status_t ral_sx126x_get_and_clear_irq_status( const void* context, ral_irq_t* irq );

/**
 * @see ral_set_dio_irq_params
 */
ral_status_t ral_sx126x_set_dio_irq_params( const void* context, const ral_irq_t irq );

/**
 * @see ral_set_rf_freq
 */
ral_status_t ral_sx126x_set_rf_freq( const void* context, const uint32_t freq_in_hz );

/**
 * @see ral_set_pkt_type
 */
ral_status_t ral_sx126x_set_pkt_type( const void* context, const ral_pkt_type_t pkt_type );

/**
 * @see ral_set_gfsk_mod_params
 */
ral_status_t ral_sx126x_set_gfsk_mod_params( const void* context, const ral_gfsk_mod_params_t* params );

/**
 * @see ral_set_gfsk_pkt_params
 */
ral_status_t ral_sx126x_set_gfsk_pkt_params( const void* context, const ral_gfsk_pkt_params_t* params );

/**
 * @see ral_set_lora_mod_params
 */
ral_status_t ral_sx126x_set_lora_mod_params( const void* context, const ral_lora_mod_params_t* params );

/**
 * @see ral_set_lora_pkt_params
 */
ral_status_t ral_sx126x_set_lora_pkt_params( const void* context, const ral_lora_pkt_params_t* params );

/**
 * @see ral_set_lora_cad_params
 */
ral_status_t ral_sx126x_set_lora_cad_params( const void* context, const ral_lora_cad_params_t* params );

/**
 * @see ral_set_lora_symb_nb_timeout
 */
ral_status_t ral_sx126x_set_lora_symb_nb_timeout( const void* context, const uint8_t nb_of_symbs );

/**
 * @see ral_set_flrc_mod_params
 */
ral_status_t ral_sx126x_set_flrc_mod_params( const void* context, const ral_flrc_mod_params_t* params );

/**
 * @see ral_set_flrc_pkt_params
 */
ral_status_t ral_sx126x_set_flrc_pkt_params( const void* context, const ral_flrc_pkt_params_t* params );

/**
 * @see ral_get_gfsk_rx_pkt_status
 */
ral_status_t ral_sx126x_get_gfsk_rx_pkt_status( const void* context, ral_gfsk_rx_pkt_status_t* rx_pkt_status );

/**
 * @see ral_get_lora_rx_pkt_status
 */
ral_status_t ral_sx126x_get_lora_rx_pkt_status( const void* context, ral_lora_rx_pkt_status_t* rx_pkt_status );

/**
 * @see ral_get_flrc_rx_pkt_status
 */
ral_status_t ral_sx126x_get_flrc_rx_pkt_status( const void* context, ral_flrc_rx_pkt_status_t* rx_pkt_status );

/**
 * @see ral_get_rssi_inst
 */
ral_status_t ral_sx126x_get_rssi_inst( const void* context, int16_t* rssi_in_dbm );

/**
 * @see ral_get_lora_time_on_air_in_ms
 */
uint32_t ral_sx126x_get_lora_time_on_air_in_ms( const ral_lora_pkt_params_t* pkt_p,
                                                const ral_lora_mod_params_t* mod_p );

/**
 * @see ral_get_gfsk_time_on_air_in_ms
 */
uint32_t ral_sx126x_get_gfsk_time_on_air_in_ms( const ral_gfsk_pkt_params_t* pkt_p,
                                                const ral_gfsk_mod_params_t* mod_p );

/**
 * @see ral_get_flrc_time_on_air_in_ms
 */
uint32_t ral_sx126x_get_flrc_time_on_air_in_ms( const ral_flrc_pkt_params_t* pkt_p,
                                                const ral_flrc_mod_params_t* mod_p );
/**
 * @see ral_set_gfsk_sync_word
 */
ral_status_t ral_sx126x_set_gfsk_sync_word( const void* context, const uint8_t* sync_word,
                                            const uint8_t sync_word_len );

/**
 * @see ral_set_lora_sync_word
 */
ral_status_t ral_sx126x_set_lora_sync_word( const void* context, const uint8_t sync_word );

/**
 * @see ral_set_flrc_sync_word
 */
ral_status_t ral_sx126x_set_flrc_sync_word( const void* context, const uint8_t* sync_word,
                                            const uint8_t sync_word_len );

/**
 * @see ral_set_gfsk_crc_params
 */
ral_status_t ral_sx126x_set_gfsk_crc_params( const void* context, const uint16_t seed, const uint16_t polynomial );

/**
 * @see ral_set_flrc_crc_params
 */
ral_status_t ral_sx126x_set_flrc_crc_params( const void* context, const uint32_t seed );

/**
 * @see ral_set_gfsk_whitening_seed
 */
ral_status_t ral_sx126x_set_gfsk_whitening_seed( const void* context, const uint16_t seed );

/**
 * @see ral_get_tx_consumption_in_ua
 */
ral_status_t ral_sx126x_get_tx_consumption_in_ua( const void* context, const int8_t output_pwr_in_dbm,
                                                  const uint32_t rf_freq_in_hz, uint32_t* pwr_consumption_in_ua );

/**
 * @see ral_get_gfsk_rx_consumption_in_ua
 */
ral_status_t ral_sx126x_get_gfsk_rx_consumption_in_ua( const void* context, const uint32_t br_in_bps,
                                                       const uint32_t bw_dsb_in_hz, const bool rx_boosted,
                                                       uint32_t* pwr_consumption_in_ua );

/**
 * @see ral_get_lora_rx_consumption_in_ua
 */
ral_status_t ral_sx126x_get_lora_rx_consumption_in_ua( const void* context, const ral_lora_bw_t bw,
                                                       const bool rx_boosted, uint32_t* pwr_consumption_in_ua );
#ifdef __cplusplus
}
#endif

#endif  // RAL_SX126X_H__

/* --- EOF ------------------------------------------------------------------ */