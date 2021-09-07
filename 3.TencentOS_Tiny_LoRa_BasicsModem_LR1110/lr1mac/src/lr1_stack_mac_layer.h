/*!
 * \file      lr1_stack_mac_layer.h
 *
 * \brief     LoRaWan stack mac layer definition
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

#ifndef __LR1_STACK_MAC_LAYER_H__
#define __LR1_STACK_MAC_LAYER_H__
#ifdef __cplusplus
extern "C" {
#endif
/*
 *-----------------------------------------------------------------------------------
 * --- DEPENDENCIES -----------------------------------------------------------------
 */
#include "smtc_real_defs.h"
#include "lr1mac_defs.h"
#include "radio_planner.h"
#include "smtc_duty_cycle.h"
#include "smtc_lbt.h"

/*
 *-----------------------------------------------------------------------------------
 * --- PUBLIC TYPES -----------------------------------------------------------------
 */
typedef struct lr1_stack_mac_s
{
    mac_context_t mac_context;
    smtc_real_t   real;  // Region Abstraction Layer
    smtc_dtc_t*   dtc_obj;
    smtc_lbt_t*   lbt_obj;

    void ( *push_callback )( void* );
    void* push_context;

    uint16_t nb_of_reset;
    /* LoraWan Context */

    /*******************************************/
    /*      Update by Link ADR command         */
    /*******************************************/
    uint8_t  tx_data_rate;
    uint8_t  tx_data_rate_adr;
    int8_t   tx_power;
    uint16_t channel_mask;
    uint8_t  nb_trans;
    uint8_t  nb_trans_cpt;
    /********************************************/
    /*     Update by RxParamaSetupRequest       */
    /********************************************/
    uint8_t  rx2_data_rate;
    uint32_t rx2_frequency;
    uint8_t  rx1_dr_offset;
    /********************************************/
    /*     Update by NewChannelReq command      */
    /********************************************/
    // NbOfActiveChannel value are valid

    /********************************************/
    /*   Update by RxTimingSetupReq command     */
    /********************************************/
    int rx1_delay_s;
    /********************************************/
    /*   Update by TxParamSetupReq command      */
    /********************************************/
    uint8_t max_eirp_dbm;
    bool    uplink_dwell_time;
    bool    downlink_dwell_time;
    /********************************************/
    /*   Update by DutyCycleReq command         */
    /********************************************/
    uint32_t max_duty_cycle_index;
    /********************************************/
    /*   Other Data To store                    */
    /********************************************/
    uint32_t fcnt_up;
    uint32_t fcnt_dwn;
    uint32_t dev_addr;
    uint8_t  nwk_skey[16];
    uint8_t  app_skey[16];
    uint8_t  app_key[16];
    uint8_t  dev_eui[8];
    uint8_t  app_eui[8];
    bool     otaa_device;
    /*******************************************/
    /* what about keys: AppEUI:Nwskey:AppSkey  */
    /*******************************************/

    // LoRaWan Mac Data for uplink
    uint8_t tx_fport;
    uint8_t tx_mtype;
    uint8_t tx_major_bits;
    uint8_t tx_fctrl;
    uint8_t tx_ack_bit;
    uint8_t app_payload_size;
    uint8_t tx_payload_size;
    uint8_t tx_payload[255];
    uint8_t tx_fopts_length;
    uint8_t tx_fopts_data[15];
    uint8_t tx_fopts_lengthsticky;
    uint8_t tx_fopts_datasticky[15];
    uint8_t tx_fopts_current_length;
    uint8_t tx_fopts_current_data[15];
    // LoRaWan Mac Data for downlink
    uint8_t               rx_mtype;
    uint8_t               rx_major;
    uint8_t               rx_fctrl;
    uint8_t               rx_ack_bit;
    uint8_t               rx_fopts_length;
    uint8_t               rx_fopts[15];
    uint8_t               rx_payload_size;  //@note Have to by replace by a fifo objet to manage class c
    uint8_t               rx_payload[255];  //@note Have to by replace by a fifo objet to manage class c
    uint8_t               rx_payload_empty;
    user_rx_packet_type_t available_app_packet;
    rx_packet_type_t      valid_rx_packet;
    receive_win_t         receive_window_type;

    // LoRaWan Mac Data for duty-cycle
    uint32_t tx_duty_cycle_time_off_ms;
    uint32_t tx_duty_cycle_timestamp_ms;

    // LoRaWan Mac Data for join
    uint16_t dev_nonce;
    uint8_t  cf_list[16];

    // LoRaWan Mac Data for nwk Ans
    uint8_t nwk_payload[NWK_REQ_PAYLOAD_MAX_SIZE];  //@note resize this buffer
    uint8_t nwk_payload_size;

    uint8_t nwk_ans[NWK_ANS_PAYLOAD_MAX_SIZE];  //@note reuse user payload data or at least reduce size or use opt byte
    uint8_t nwk_ans_size;

    // LoraWan Config
    int           adr_ack_cnt;
    int           adr_ack_cnt_confirmed_frame;
    int           adr_ack_limit;
    int           adr_ack_delay;
    uint8_t       adr_ack_req;
    uint8_t       adr_enable;
    dr_strategy_t adr_mode_select;
    dr_strategy_t adr_mode_select_tmp;
    uint32_t      adr_custom;
    uint16_t      no_rx_packet_count;
    uint16_t      no_rx_packet_count_in_mobile_mode;

    // Join Duty cycle management
    uint32_t next_time_to_join_seconds;
    uint32_t retry_join_cpt;
    uint32_t first_join_timestamp;

    uint8_t            tx_sf;
    modulation_type_t  tx_modulation_type;
    lr1mac_bandwidth_t tx_bw;
    uint32_t           tx_frequency;
    uint32_t           rx1_frequency;
    uint8_t            rx1_sf;
    lr1mac_bandwidth_t rx1_bw;
    modulation_type_t  rx1_modulation_type;
    uint8_t            rx2_sf;
    lr1mac_bandwidth_t rx2_bw;
    modulation_type_t  rx2_modulation_type;
    uint8_t            sync_word;
    rx_win_type_t      current_win;

    // initially implemented in phy layer
    lr1mac_radio_state_t   radio_process_state;
    radio_planner_t*       rp;
    uint32_t               rx_timeout_ms;
    uint32_t               rx_timeout_symb_in_ms;
    uint16_t               rx_window_symb;
    join_status_t          join_status;
    rp_status_t            planner_status;
    lr1mac_down_metadata_t rx_metadata;
    uint32_t               isr_tx_done_radio_timestamp;
    int16_t                fine_tune_board_setting_delay_ms[16];
    int32_t                rx_offset_ms;
    uint32_t               timestamp_failsafe;
    uint32_t               dev_addr_isr;
    uint8_t                type_of_ans_to_send;
    uint8_t                nwk_payload_index;
    lr1mac_states_t        lr1mac_state;
    uint32_t               rtc_target_timer_ms;
    uint8_t                send_at_time;
    bool                   available_link_adr;
    uint8_t                is_lorawan_modem_certification_enabled;
    lr1mac_tx_status_t     lr1mac_tx_status;
    uint8_t                stack_id4rp;
    uint32_t               crystal_error;
} lr1_stack_mac_t;

/*
 *-----------------------------------------------------------------------------------
 *--- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------------
 */
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_mac_init( lr1_stack_mac_t* lr1_mac, lorawan_keys_t* lorawan_keys,
                         smtc_real_region_types_t smtc_real_region_types );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_mac_session_init( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_mac_tx_frame_build( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_mac_tx_frame_encrypt( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_mac_tx_radio_start( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_mac_tx_radio_free_lbt( lr1_stack_mac_t* lr1_mac );

/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_mac_radio_busy_lbt( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_mac_radio_abort_lbt( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_mac_rx_radio_start( lr1_stack_mac_t* lr1_mac, const rx_win_type_t type, const uint32_t time_to_start );

/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
int lr1_stack_mac_downlink_check_under_it( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_mac_rp_callback( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
int lr1_stack_mac_radio_state_get( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_mac_rx_timer_configure( lr1_stack_mac_t* lr1_mac, const rx_win_type_t type );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
rx_packet_type_t lr1_stack_mac_rx_frame_decode( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_mac_update_tx_done( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_mac_update( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
status_lorawan_t lr1_stack_mac_cmd_parse( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_mac_join_request_build( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
status_lorawan_t lr1_stack_mac_join_accept( lr1_stack_mac_t* lr1_mac );

/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
uint8_t lr1_stack_mac_min_tx_dr_get( lr1_stack_mac_t* lr1_mac );

/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
uint8_t lr1_stack_mac_max_tx_dr_get( lr1_stack_mac_t* lr1_mac );

/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
uint16_t lr1_stack_mac_mask_tx_dr_channel_up_dwell_time_check( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_rx1_join_delay_set( lr1_stack_mac_t* lr1_mac );
/*!
 * \brief
 * \remark
 * \param [IN]  none
 * \param [OUT] return
 */
void lr1_stack_rx2_join_dr_set( lr1_stack_mac_t* lr1_mac );

/*!
 * \brief lr1_stack_network_next_free_duty_cycle_ms_get
 * \remark duty cycle time off left about the network duty-cycle request
 * \param [IN]  lr1_stack_mac_t
 * \return duty-cycle time-off left, 0 if no pending limitation
 */
int32_t lr1_stack_network_next_free_duty_cycle_ms_get( lr1_stack_mac_t* lr1_mac );

/*!
 * \brief lr1_stack_toa_get
 * \remark
 * \param [IN]  lr1_stack_mac_t
 * \return toa of the urrent tx frame
 */
uint32_t lr1_stack_toa_get( lr1_stack_mac_t* lr1_mac );

/**
 * @brief
 *
 * @param lr1_mac
 * @return uint8_t return the Nb Trans configured
 */
uint8_t lr1_stack_nb_trans_get( lr1_stack_mac_t* lr1_mac );

/**
 * @brief
 *
 * @param lr1_mac
 * @param [in] nb_trans set the Number of NbTrans
 * @return status_lorawan_t
 */
status_lorawan_t lr1_stack_nb_trans_set( lr1_stack_mac_t* lr1_mac, uint8_t nb_trans );

/**
 * @brief
 *
 * @param lr1_mac
 * @return uint32_t
 */
uint32_t lr1_stack_get_crystal_error( lr1_stack_mac_t* lr1_mac );

/**
 * @brief
 *
 * @param lr1_mac
 * @param [in] crystal_error
 */
void lr1_stack_set_crystal_error( lr1_stack_mac_t* lr1_mac, uint32_t crystal_error );

/*!
 * \brief tx launch call back for rp
 * \remark
 * \param
 * \return
 */
void lr1_stack_mac_tx_lora_launch_callback_for_rp( void* rp_void );
void lr1_stack_mac_tx_gfsk_launch_callback_for_rp( void* rp_void );
void lr1_stack_mac_rx_lora_launch_callback_for_rp( void* rp_void );
void lr1_stack_mac_rx_gfsk_launch_callback_for_rp( void* rp_void );

#ifdef __cplusplus
}
#endif

#endif  // __LR1_STACK_MAC_LAYER_H__