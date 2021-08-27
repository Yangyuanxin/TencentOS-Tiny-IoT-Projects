/*!
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

#include "lr1110_gnss.h"

// Almanac loaded from loracloud at 2021-04-06 with python script
static const lr1110_gnss_almanac_full_update_bytestream_t full_almanac = {
    0x80, 0xD8, 0x02, 0x5A, 0x97, 0xB6, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x4A, 0x43, 0x28, 0xB9, 0x02, 0x16, 0x28, 0x46, 0x5D, 0xAE, 0x21, 0xBE, 0x97, 0xAA, 0xFF, 0xDF, 0x00, 0x01, 0x00,
    0x01, 0x33, 0x43, 0x28, 0x31, 0x05, 0x39, 0x27, 0xC3, 0x67, 0xBB, 0xC1, 0x60, 0x94, 0xAA, 0xFF, 0x6F, 0x00, 0x01, 0x00,
    0x02, 0x27, 0x43, 0x28, 0xDB, 0x00, 0x75, 0x27, 0xDB, 0x30, 0xA8, 0x21, 0x0B, 0xC2, 0xAA, 0xFF, 0x37, 0x00, 0x01, 0x00,
    0x03, 0x68, 0x43, 0x28, 0x4C, 0x00, 0x24, 0x27, 0x6C, 0xA1, 0xD8, 0x86, 0x11, 0xEE, 0xAA, 0xFF, 0x1B, 0x00, 0x01, 0x00,
    0x04, 0x96, 0x43, 0x28, 0x89, 0x01, 0xED, 0x26, 0x07, 0xCE, 0xDB, 0x23, 0x92, 0xC0, 0xA8, 0xFF, 0xA4, 0x01, 0x01, 0x00,
    0x05, 0x62, 0x43, 0x28, 0x97, 0x00, 0x11, 0x28, 0x1D, 0x68, 0xD9, 0xD6, 0x68, 0x97, 0xA9, 0xFF, 0xD2, 0x00, 0x01, 0x00,
    0x06, 0x10, 0x43, 0x28, 0xC2, 0x03, 0xCB, 0x26, 0x2F, 0x45, 0x84, 0xA0, 0xB5, 0x17, 0xA7, 0xFF, 0xA6, 0x01, 0x01, 0x00,
    0x07, 0x0E, 0x43, 0x28, 0x9F, 0x01, 0x70, 0x27, 0xAC, 0xB7, 0xC9, 0x00, 0x02, 0x6C, 0xA5, 0xFF, 0xD3, 0x00, 0x01, 0x00,
    0x08, 0x80, 0x43, 0x28, 0x7F, 0x00, 0xD9, 0x26, 0xE5, 0xC9, 0xBB, 0x4A, 0x04, 0xEC, 0xA8, 0xFF, 0x69, 0x00, 0x01, 0x00,
    0x09, 0x3F, 0x43, 0x28, 0xAF, 0x01, 0x74, 0x27, 0x84, 0x09, 0x7C, 0x97, 0xED, 0xC1, 0xA9, 0xFF, 0xBB, 0x00, 0x01, 0x00,
    0x0A, 0x0A, 0x44, 0x28, 0xEB, 0x03, 0x44, 0x25, 0xEA, 0x3D, 0x29, 0x55, 0x97, 0x83, 0xA0, 0xFF, 0x5D, 0x00, 0x01, 0x00,
    0x0B, 0x71, 0x43, 0x28, 0x2C, 0x02, 0xAF, 0x27, 0x69, 0x27, 0x9E, 0x30, 0xF2, 0x44, 0xA8, 0xFF, 0x17, 0x00, 0x01, 0x00,
    0x0C, 0x3F, 0x43, 0x28, 0x42, 0x01, 0x74, 0x27, 0xD1, 0x9D, 0xAF, 0x28, 0x09, 0xF2, 0xAB, 0xFF, 0x0B, 0x00, 0x01, 0x00,
    0x0D, 0x65, 0x43, 0x28, 0x22, 0x00, 0x03, 0x27, 0x44, 0x40, 0x3D, 0x62, 0xDF, 0x43, 0xA8, 0xFF, 0x05, 0x00, 0x01, 0x00,
    0x0E, 0x0C, 0x43, 0x28, 0x59, 0x03, 0xDA, 0x25, 0x2C, 0x90, 0xB7, 0x27, 0x0A, 0xE8, 0xA7, 0xFF, 0x02, 0x00, 0x01, 0x00,
    0x0F, 0x42, 0x43, 0x28, 0x24, 0x03, 0xB0, 0x27, 0xAD, 0xDB, 0x3D, 0x1B, 0xB5, 0x45, 0xA9, 0xFF, 0x01, 0x00, 0x01, 0x00,
    0x10, 0x0F, 0x43, 0x28, 0x6C, 0x03, 0x09, 0x28, 0x08, 0xB5, 0x05, 0xC0, 0x26, 0x6F, 0xAA, 0xFF, 0x91, 0x01, 0x01, 0x00,
    0x11, 0x3F, 0x43, 0x28, 0x53, 0x00, 0x6C, 0x27, 0x62, 0x65, 0x46, 0x79, 0x41, 0x98, 0xA7, 0xFF, 0xC8, 0x00, 0x01, 0x00,
    0x12, 0x28, 0x43, 0x28, 0x58, 0x02, 0xFA, 0x27, 0xCF, 0x1B, 0x6D, 0x49, 0xFE, 0x70, 0xA6, 0xFF, 0x64, 0x00, 0x01, 0x00,
    0x13, 0x48, 0x3F, 0x28, 0x8B, 0x01, 0x30, 0x26, 0xDE, 0x4B, 0xFD, 0x7A, 0x2C, 0xBC, 0xA7, 0xFF, 0x32, 0x00, 0x01, 0x00,
    0x14, 0x4D, 0x43, 0x28, 0x32, 0x06, 0xFC, 0x26, 0xB5, 0xBD, 0xB1, 0xD0, 0x64, 0x94, 0xA4, 0xFF, 0x19, 0x00, 0x01, 0x00,
    0x15, 0x09, 0x43, 0x28, 0xCF, 0x01, 0x0D, 0x26, 0xEB, 0x8D, 0xFB, 0xD6, 0x11, 0xBE, 0xA8, 0xFF, 0x0C, 0x00, 0x01, 0x00,
    0x16, 0x34, 0x43, 0x28, 0x47, 0x00, 0x40, 0x27, 0x4D, 0x4D, 0x26, 0x68, 0xFB, 0xC0, 0xA9, 0xFF, 0xCC, 0x01, 0x01, 0x00,
    0x17, 0x5C, 0x43, 0x28, 0xD3, 0x02, 0x1E, 0x26, 0xD5, 0x6B, 0x0D, 0x1E, 0x8E, 0x14, 0xA8, 0xFF, 0x39, 0x00, 0x01, 0x00,
    0x18, 0x31, 0x43, 0x28, 0x8B, 0x02, 0x2B, 0x27, 0x2C, 0x1A, 0x04, 0x27, 0xFA, 0x41, 0xA7, 0xFF, 0x1C, 0x00, 0x01, 0x00,
    0x19, 0x76, 0x43, 0x28, 0x7C, 0x01, 0x64, 0x26, 0x9D, 0xFE, 0x27, 0x0C, 0x4D, 0x40, 0xA6, 0xFF, 0x0E, 0x00, 0x01, 0x00,
    0x1A, 0x42, 0x43, 0x28, 0x64, 0x02, 0xC9, 0x27, 0xB8, 0xB5, 0x6F, 0x18, 0xB1, 0x6C, 0xA7, 0xFF, 0x07, 0x00, 0x01, 0x00,
    0x1B, 0x3D, 0x43, 0x28, 0x8C, 0x04, 0xA7, 0x27, 0x68, 0xD4, 0x2F, 0xC9, 0xDB, 0x45, 0xA7, 0xFF, 0x03, 0x00, 0x01, 0x00,
    0x1C, 0x39, 0x43, 0x28, 0x6E, 0x00, 0x1D, 0x28, 0x29, 0xBD, 0xD9, 0x55, 0xA7, 0x6F, 0xA8, 0xFF, 0xA8, 0x01, 0x01, 0x00,
    0x1D, 0x54, 0x43, 0x28, 0x4A, 0x01, 0x30, 0x26, 0x3A, 0x40, 0x1A, 0x8D, 0x70, 0x18, 0xA6, 0xFF, 0xD4, 0x00, 0x01, 0x00,
    0x1E, 0x69, 0x43, 0x28, 0x8C, 0x02, 0xF8, 0x26, 0x14, 0x2F, 0x71, 0x0A, 0x64, 0x18, 0xA9, 0xFF, 0x6A, 0x00, 0x01, 0x00,
    0x1F, 0x2F, 0x43, 0x28, 0x3B, 0x01, 0x03, 0x27, 0x12, 0xD4, 0x46, 0x9E, 0x6A, 0xEC, 0xA8, 0xFF, 0x35, 0x00, 0x01, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x23, 0x91, 0xBC, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6A, 0x16, 0x00, 0x00, 0x9A, 0x00, 0x01, 0x00,
    0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x25, 0x48, 0xBC, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9F, 0xF4, 0x00, 0x00, 0x3E, 0x02, 0x01, 0x00,
    0x26, 0xF2, 0xBB, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x2D, 0x00, 0x00, 0xF4, 0x03, 0x01, 0x00,
    0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x28, 0x28, 0xBC, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x3B, 0x00, 0x00, 0x5A, 0x03, 0x01, 0x00,
    0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x2A, 0x80, 0xBB, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x91, 0x63, 0x00, 0x00, 0xE1, 0x00, 0x01, 0x00,
    0x2B, 0x55, 0xBC, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCE, 0xAC, 0x00, 0x00, 0x69, 0x01, 0x01, 0x00,
    0x2C, 0x48, 0xBD, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0x42, 0x00, 0x00, 0x50, 0x01, 0x01, 0x00,
    0x2D, 0xDF, 0xBB, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0xA4, 0x00, 0x00, 0xD9, 0x03, 0x01, 0x00,
    0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x2F, 0x2F, 0xBB, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0xA7, 0x00, 0x00, 0x8E, 0x02, 0x01, 0x00,
    0x30, 0x48, 0xBC, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8E, 0x03, 0x00, 0x00, 0xE0, 0x01, 0x01, 0x00,
    0x31, 0x97, 0xBB, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x5A, 0x00, 0x00, 0x07, 0x02, 0x01, 0x00,
    0x32, 0x15, 0xBB, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB7, 0xB3, 0x00, 0x00, 0x28, 0x01, 0x01, 0x00,
    0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x40, 0x0B, 0xBF, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDB, 0x66, 0x00, 0x00, 0x87, 0x01, 0x02, 0x01,
    0x41, 0x55, 0xBC, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x3B, 0x00, 0x00, 0x39, 0x06, 0x02, 0x01,
    0x42, 0x72, 0xC1, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x4E, 0x00, 0x00, 0xE6, 0x01, 0x02, 0x01,
    0x43, 0x3E, 0xBD, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB5, 0x71, 0x00, 0x00, 0x09, 0x06, 0x02, 0x01,
    0x44, 0x82, 0xC0, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x29, 0x00, 0x00, 0x05, 0x06, 0x02, 0x01,
    0x45, 0x21, 0xBA, 0x32, 0xCB, 0x02, 0x8E, 0x26, 0x60, 0xB6, 0x9D, 0xA6, 0x59, 0xF7, 0xEB, 0xFF, 0xF8, 0x01, 0x02, 0x01,
    0x46, 0x97, 0xBA, 0x32, 0x16, 0x02, 0x3C, 0x24, 0x60, 0x73, 0xEC, 0x98, 0xD7, 0x48, 0xEA, 0xFF, 0x06, 0x06, 0x02, 0x01,
    0x47, 0xCC, 0xBA, 0x32, 0x59, 0x01, 0x6F, 0x2A, 0x18, 0x22, 0x4C, 0x92, 0xD3, 0xA0, 0xE9, 0xFF, 0xF9, 0x01, 0x02, 0x01,
    0x48, 0x4E, 0xBA, 0x32, 0x0A, 0x02, 0xC2, 0x26, 0x3D, 0xAB, 0x94, 0x9F, 0x13, 0xF9, 0xEC, 0xFF, 0x04, 0x07, 0x02, 0x01,
    0x49, 0xFA, 0xBA, 0x32, 0xC3, 0x01, 0x4F, 0x24, 0xF8, 0x63, 0xAF, 0x97, 0x91, 0x48, 0xE9, 0xFF, 0xBE, 0x07, 0x02, 0x01,
    0x4A, 0x21, 0x45, 0x29, 0x7E, 0x00, 0x5F, 0x28, 0x49, 0x76, 0xA9, 0xB1, 0xE1, 0x7C, 0xB6, 0xFF, 0x61, 0x00, 0x02, 0x01,
    0x4B, 0x22, 0x45, 0x29, 0x43, 0x00, 0x51, 0x28, 0x24, 0x91, 0x66, 0xB6, 0x6C, 0x7C, 0xB5, 0xFF, 0x8E, 0x07, 0x02, 0x01,
    0x4C, 0x52, 0xBA, 0x32, 0xFC, 0x00, 0xDB, 0x28, 0x13, 0x0C, 0x7E, 0x98, 0xF3, 0x9F, 0xE8, 0xFF, 0x82, 0x07, 0x02, 0x01,
    0x4D, 0x22, 0x45, 0x29, 0x5F, 0x00, 0x3A, 0x27, 0x7D, 0xEF, 0x62, 0xE4, 0x18, 0xD1, 0xB7, 0xFF, 0x7F, 0x00, 0x02, 0x01,
    0x4E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x4F, 0xD3, 0xB9, 0x32, 0xED, 0x00, 0x2E, 0x27, 0x5F, 0xBD, 0x3F, 0x9B, 0xE0, 0xF6, 0xEC, 0xFF, 0x7E, 0x00, 0x02, 0x01,
    0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x52, 0x27, 0x45, 0x29, 0x42, 0x00, 0x56, 0x27, 0x59, 0x74, 0x9D, 0xCE, 0x0D, 0xD1, 0xB8, 0xFF, 0x3C, 0x00, 0x02, 0x01,
    0x53, 0x29, 0x45, 0x29, 0x39, 0x00, 0x56, 0x27, 0xB8, 0x83, 0x3B, 0xDE, 0x14, 0xD1, 0xB8, 0xFF, 0xC1, 0x07, 0x02, 0x01,
    0x54, 0x28, 0x45, 0x29, 0x36, 0x00, 0x4E, 0x27, 0xC5, 0x2B, 0x26, 0xD7, 0x26, 0xD1, 0xB7, 0xFF, 0x3F, 0x00, 0x02, 0x01,
    0x55, 0x26, 0x45, 0x29, 0x2A, 0x00, 0x4E, 0x27, 0xE8, 0x34, 0xD6, 0xED, 0x25, 0xD1, 0xB7, 0xFF, 0xC0, 0x07, 0x02, 0x01,
    0x56, 0x22, 0x45, 0x29, 0x04, 0x00, 0xB5, 0x26, 0xCA, 0x46, 0x5C, 0x07, 0xE2, 0x26, 0xB6, 0xFF, 0xEF, 0x07, 0x02, 0x01,
    0x57, 0x23, 0x45, 0x29, 0x28, 0x00, 0xB5, 0x26, 0x3D, 0x77, 0xD4, 0x17, 0xE0, 0x26, 0xB5, 0xFF, 0xE3, 0x07, 0x02, 0x01,
    0x58, 0x26, 0x45, 0x29, 0x1E, 0x00, 0xC2, 0x26, 0x89, 0x5B, 0xF8, 0x11, 0xD7, 0x25, 0xB6, 0xFF, 0x1E, 0x00, 0x02, 0x01,
    0x59, 0x24, 0x45, 0x29, 0x31, 0x00, 0xC3, 0x26, 0xF2, 0x9D, 0x38, 0x0F, 0xDD, 0x25, 0xB6, 0xFF, 0xE0, 0x07, 0x02, 0x01,
    0x5A, 0x24, 0x45, 0x29, 0x2E, 0x00, 0x65, 0x27, 0x28, 0xB3, 0xC6, 0x24, 0x98, 0x7C, 0xB2, 0xFF, 0x1F, 0x00, 0x02, 0x01,
    0x5B, 0x23, 0x45, 0x29, 0x03, 0x00, 0x64, 0x27, 0x97, 0x46, 0x77, 0xB1, 0x97, 0x7C, 0xB2, 0xFF, 0x0C, 0x00, 0x02, 0x01,
    0x5C, 0x24, 0x45, 0x29, 0x12, 0x00, 0x59, 0x27, 0x0B, 0x70, 0xFF, 0x27, 0x07, 0x7B, 0xB2, 0xFF, 0xF1, 0x07, 0x02, 0x01,
    0x5D, 0x21, 0x45, 0x29, 0x24, 0x00, 0x58, 0x27, 0x48, 0xAD, 0x8E, 0x0B, 0x0D, 0x7B, 0xB1, 0xFF, 0x0F, 0x00, 0x02, 0x01,
    0x5E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x5F, 0x25, 0x45, 0x29, 0x2B, 0x00, 0x48, 0x27, 0xF1, 0xB5, 0xFB, 0xCC, 0xD7, 0xD0, 0xB7, 0xFF, 0xFD, 0x07, 0x02, 0x01,
    0x60, 0x25, 0x45, 0x29, 0x21, 0x00, 0x48, 0x27, 0xE4, 0xE2, 0x34, 0xE0, 0xD5, 0xD0, 0xB7, 0xFF, 0x03, 0x00, 0x02, 0x01,
    0x61, 0x27, 0x45, 0x29, 0x29, 0x00, 0x45, 0x27, 0x41, 0x25, 0x5A, 0x12, 0x2C, 0x7B, 0xB2, 0xFF, 0xFC, 0x07, 0x02, 0x01,
    0x62, 0x23, 0x45, 0x29, 0x34, 0x00, 0x45, 0x27, 0x14, 0x70, 0x89, 0x08, 0x2B, 0x7B, 0xB3, 0xFF, 0xFE, 0x07, 0x02, 0x01,
    0x63, 0x23, 0x45, 0x29, 0x26, 0x00, 0xC4, 0x26, 0x41, 0x2B, 0xDC, 0xC2, 0xC7, 0x26, 0xB6, 0xFF, 0x01, 0x00, 0x02, 0x01,
    0x64, 0x23, 0x45, 0x29, 0x23, 0x00, 0xC4, 0x26, 0x0D, 0x4E, 0x9E, 0xE0, 0xC6, 0x26, 0xB7, 0xFF, 0xFF, 0x07, 0x02, 0x01,
    0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x6A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x6B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x6F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x7A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x7B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x7D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
};
