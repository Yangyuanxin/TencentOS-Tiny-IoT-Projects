/*!
 * \file      lr1_mac_utilities.c
 *
 * \brief     LoRaWan utilities definition
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
 *-----------------------------------------------------------------------------------
 * --- DEPENDENCIES -----------------------------------------------------------------
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "lr1mac_utilities.h"
#include "smtc_modem_hal.h"
#include "lr1mac_defs.h"

void memcpy1( uint8_t* dst, const uint8_t* src, uint16_t size )
{
    while( size-- )
    {
        *dst++ = *src++;
    }
}

void memcpy1_r( uint8_t* dst, const uint8_t* src, uint16_t size )
{
    const uint8_t* p = src + ( size - 1 );
    while( size-- )
    {
        *dst++ = *p--;
    }
}

void memset1( uint8_t* dst, uint8_t value, uint16_t size )
{
    while( size-- )
    {
        *dst++ = value;
    }
}

uint32_t lr1mac_utilities_crc( uint8_t* buf, int len )
{
    uint32_t crc = 0xFFFFFFFA;
    while( len-- > 0 )
    {
        crc = crc ^ *buf++;
        for( int i = 0; i < 8; i++ )
        {
            uint32_t mask = -( crc & 1 );
            crc           = ( crc >> 1 ) ^ ( 0xEDB88320 & mask );
        }
    }
    return ~crc + 3;
}

uint32_t lr1mac_utilities_get_symb_time_us( const uint16_t nb_symb, const ral_lora_sf_t sf, const ral_lora_bw_t bw )
{
    uint32_t sf_val;
    uint32_t bw_khz;

    // clang-format off
    switch(sf)
    {
        case RAL_LORA_SF5:  sf_val = 5;     break;
        case RAL_LORA_SF6:  sf_val = 6;     break;
        case RAL_LORA_SF7:  sf_val = 7;     break;
        case RAL_LORA_SF8:  sf_val = 8;     break;
        case RAL_LORA_SF9:  sf_val = 9;     break;
        case RAL_LORA_SF10: sf_val = 10;    break;
        case RAL_LORA_SF11: sf_val = 11;    break;
        case RAL_LORA_SF12: sf_val = 12;    break;
        default:
            return 0;
            break;
    }
    switch (bw)
    {
        case RAL_LORA_BW_007_KHZ:   bw_khz = 7;      break;
        case RAL_LORA_BW_010_KHZ:   bw_khz = 10;     break;
        case RAL_LORA_BW_015_KHZ:   bw_khz = 15;     break;
        case RAL_LORA_BW_020_KHZ:   bw_khz = 20;     break;
        case RAL_LORA_BW_031_KHZ:   bw_khz = 31;     break;
        case RAL_LORA_BW_041_KHZ:   bw_khz = 41;     break;
        case RAL_LORA_BW_062_KHZ:   bw_khz = 62;     break;
        case RAL_LORA_BW_125_KHZ:   bw_khz = 125;    break;
        case RAL_LORA_BW_200_KHZ:   bw_khz = 203;    break;
        case RAL_LORA_BW_250_KHZ:   bw_khz = 250;    break;
        case RAL_LORA_BW_400_KHZ:   bw_khz = 406;    break;
        case RAL_LORA_BW_500_KHZ:   bw_khz = 500;    break;
        case RAL_LORA_BW_800_KHZ:   bw_khz = 812;    break;
        case RAL_LORA_BW_1600_KHZ:  bw_khz = 1625;   break;
         default:
            return 0;
            break;
    }
    // clang-format on

    return ( ( ( uint32_t ) nb_symb * 1000 ) << sf_val ) / bw_khz;
}

uint8_t SMTC_GET_BIT8( const uint8_t* array, uint8_t index )
{
    return ( ( ( ( array )[( index ) / 8] ) >> ( ( index ) % 8 ) ) & 0x01 );
}
void SMTC_SET_BIT8( uint8_t* array, uint8_t index )
{
    ( ( ( array )[( index ) / 8] ) |= ( 1 << ( ( index ) % 8 ) ) );
}
void SMTC_CLR_BIT8( uint8_t* array, uint8_t index )
{
    ( ( ( array )[( index ) / 8] ) &= ~( 1 << ( ( index ) % 8 ) ) );
}
void SMTC_PUT_BIT8( uint8_t* array, uint8_t index, uint8_t bit )
{
    ( ( ( bit ) &0x01 ) ? ( SMTC_SET_BIT8( array, ( index ) ) ) : ( SMTC_CLR_BIT8( array, ( index ) ) ) );
}

uint8_t SMTC_ARE_CLR_BYTE8( uint8_t* array, uint8_t length )
{
    for( uint8_t i = 0; i < length; i++ )
    {
        if( array[i] != 0 )
        {
            return false;
        }
    }
    return true;
}

uint8_t SMTC_GET_BIT16( const uint16_t* array, uint8_t index )
{
    return ( ( ( ( array )[( index ) / 16] ) >> ( ( index ) % 16 ) ) & 0x01 );
}
void SMTC_SET_BIT16( uint16_t* array, uint8_t index )
{
    ( ( ( array )[( index ) / 16] ) |= ( 1 << ( ( index ) % 16 ) ) );
}
void SMTC_CLR_BIT16( uint16_t* array, uint8_t index )
{
    ( ( ( array )[( index ) / 16] ) &= ~( 1 << ( ( index ) % 16 ) ) );
}
void SMTC_PUT_BIT16( uint16_t* array, uint8_t index, uint8_t bit )
{
    ( ( ( bit ) &0x01 ) ? ( SMTC_SET_BIT16( array, ( index ) ) ) : ( SMTC_CLR_BIT16( array, ( index ) ) ) );
}

uint8_t SMTC_ARE_CLR_BYTE16( uint16_t* array, uint8_t length )
{
    for( uint8_t i = 0; i < length; i++ )
    {
        if( array[i] != 0 )
        {
            return false;
        }
    }
    return true;
}

status_lorawan_t lr1mac_rx_payload_min_size_check( uint8_t rx_payload_size )
{
    status_lorawan_t status = OKLORAWAN;
    if( rx_payload_size < MIN_LORAWAN_PAYLOAD_SIZE )
    {
        status = ERRORLORAWAN;
        SMTC_MODEM_HAL_TRACE_ERROR( " CheckRxPayloadLength = %d \n", rx_payload_size );
    }
    return ( status );
}

status_lorawan_t lr1mac_rx_mhdr_extract( uint8_t* rx_payload, uint8_t* rx_mtype, uint8_t* rx_major,
                                         uint8_t* tx_ack_bit )
{
    status_lorawan_t status = OKLORAWAN;
    *rx_mtype               = rx_payload[0] >> 5;
    *rx_major               = rx_payload[0] & 0x3;
    if( ( *rx_mtype == JOIN_REQUEST ) || ( *rx_mtype == UNCONF_DATA_UP ) || ( *rx_mtype == CONF_DATA_UP ) ||
        ( *rx_mtype == REJOIN_REQUEST ) || ( *rx_mtype == PROPRIETARY ) || ( *rx_major != LORAWANR1 ) )
    {
        status = ERRORLORAWAN;
        SMTC_MODEM_HAL_TRACE_MSG( " BAD RX MHDR\n " );
    }
    *tx_ack_bit = ( *rx_mtype == CONF_DATA_DOWN ) ? 1 : 0;

    return ( status );
}

int lr1mac_rx_fhdr_extract( uint8_t* rx_payload, uint8_t rx_payload_size, uint8_t* rx_fopts_length,
                            uint16_t* fcnt_dwn_tmp, uint32_t dev_addr, uint8_t* rx_fport, uint8_t* rx_payload_empty,
                            uint8_t* rx_fctrl, uint8_t* rx_fopts )
{
    int      status       = OKLORAWAN;
    uint32_t dev_addr_tmp = 0;
    dev_addr_tmp          = rx_payload[1] + ( rx_payload[2] << 8 ) + ( rx_payload[3] << 16 ) + ( rx_payload[4] << 24 );
    status                = ( dev_addr_tmp == dev_addr ) ? OKLORAWAN : ERRORLORAWAN;
    *rx_fctrl             = rx_payload[5];

    *fcnt_dwn_tmp    = rx_payload[6] + ( rx_payload[7] << 8 );
    *rx_fopts_length = *rx_fctrl & 0x0F;
    memcpy1( &rx_fopts[0], &rx_payload[8], *rx_fopts_length );
    // case empty payload without fport :
    if( rx_payload_size > 8 + MICSIZE + *rx_fopts_length )
    {
        *rx_fport         = rx_payload[8 + *rx_fopts_length];
        *rx_payload_empty = 0;
    }
    else
    {
        *rx_payload_empty = 1;
        SMTC_MODEM_HAL_TRACE_MSG( " EMPTY MSG \n" );
    }
    /**************************/
    /* manage Fctrl Byte      */
    /**************************/
    if( status == ERRORLORAWAN )
    {
        SMTC_MODEM_HAL_TRACE_ERROR( " Bad DevAddr %x\n ", dev_addr_tmp );
    }
    return ( status );
}

int lr1mac_fcnt_dwn_accept( uint16_t fcnt_dwn_tmp, uint32_t* fcnt_lorawan )
{
    int      status       = OKLORAWAN;
    uint16_t fcnt_dwn_lsb = ( *fcnt_lorawan & 0x0000FFFF );
    uint32_t fcnt_dwn_msb = ( *fcnt_lorawan & 0xFFFF0000 );
    if( ( fcnt_dwn_tmp > fcnt_dwn_lsb ) || ( *fcnt_lorawan == 0xFFFFFFFF ) )
    {
        if( *fcnt_lorawan == 0xFFFFFFFF )  // manage the case of the first downlink with fcnt down = 0
        {
            *fcnt_lorawan = fcnt_dwn_tmp;
        }
        else
        {
            *fcnt_lorawan = fcnt_dwn_msb + fcnt_dwn_tmp;
        }
    }
    else if( ( fcnt_dwn_lsb - fcnt_dwn_tmp ) > MAX_FCNT_GAP )
    {
        *fcnt_lorawan = fcnt_dwn_msb + 65536 + fcnt_dwn_tmp;
    }
    else
    {
        status = ERRORLORAWAN;
        SMTC_MODEM_HAL_TRACE_WARNING(
            " FcntDwn is not acceptable fcntDwnReceive = %u "
            "fcntLoraStack = %d\n",
            fcnt_dwn_tmp, ( *fcnt_lorawan ) );
    }
    return ( status );
}

valid_dev_addr_t lr1mac_check_dev_addr( uint32_t dev_addr_unicast, uint32_t* dev_addr_multi_cast,
                                        uint8_t nb_dev_addr_multi_cast, uint32_t dev_addr_to_test )
{
    valid_dev_addr_t status = UNVALID_DEV_ADDR;

    if( dev_addr_unicast == dev_addr_to_test )
    {
        return VALID_DEV_ADDR_UNICAST;
    }

    if( ( dev_addr_multi_cast != NULL ) && ( nb_dev_addr_multi_cast > 0 ) )
    {
        if( nb_dev_addr_multi_cast >= UNVALID_DEV_ADDR )
        {
            smtc_modem_hal_lr1mac_panic( );
        }

        for( valid_dev_addr_t i = 0; i < nb_dev_addr_multi_cast; i++ )
        {
            if( dev_addr_to_test == dev_addr_multi_cast[i] )
            {
                return i;
            }
        }
    }

    return status;
}