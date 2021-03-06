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

// Almanac loaded from loracloud at 03/07/2020 with python script
static const lr1110_gnss_almanac_full_update_bytestream_t full_almanac = {
    0x80, 0xC0, 0x01, 0x8B, 0x01, 0x03, 0xEA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x52, 0x43, 0x28, 0x8F, 0x02, 0xF5, 0x27, 0x8C, 0xC8, 0x6B, 0x20, 0xD7, 0x63, 0xA8, 0xFF, 0xDF, 0x00, 0x01, 0x00,
    0x01, 0x57, 0x43, 0x28, 0x0C, 0x05, 0x19, 0x27, 0x75, 0xD2, 0xF2, 0xBD, 0xB4, 0x60, 0xA3, 0xFF, 0x6F, 0x00, 0x01, 0x00,
    0x02, 0x7C, 0x43, 0x28, 0xC6, 0x00, 0x5E, 0x27, 0x29, 0x9E, 0x16, 0x1F, 0x36, 0x8E, 0xA6, 0xFF, 0x37, 0x00, 0x01, 0x00,
    0x03, 0x3C, 0x43, 0x28, 0x33, 0x00, 0x1A, 0x27, 0x74, 0xF7, 0x41, 0x95, 0x2D, 0xBA, 0xA9, 0xFF, 0x1B, 0x00, 0x01, 0x00,
    0x04, 0x40, 0x43, 0x28, 0x88, 0x01, 0xD5, 0x26, 0xF3, 0x3F, 0x02, 0x21, 0xE5, 0x8C, 0xA3, 0xFF, 0xA4, 0x01, 0x01, 0x00,
    0x05, 0x07, 0x43, 0x28, 0x78, 0x00, 0xF0, 0x27, 0x59, 0xD0, 0xEF, 0xD4, 0x81, 0x63, 0xA7, 0xFF, 0xD2, 0x00, 0x01, 0x00,
    0x06, 0x33, 0x43, 0x28, 0x97, 0x03, 0xD4, 0x26, 0x26, 0xAA, 0xD2, 0x9E, 0xFA, 0xE3, 0xA8, 0xFF, 0xA6, 0x01, 0x01, 0x00,
    0x07, 0x47, 0x43, 0x28, 0x5E, 0x01, 0x7F, 0x27, 0x2A, 0x25, 0x89, 0xFD, 0x38, 0x38, 0xA9, 0xFF, 0xD3, 0x00, 0x01, 0x00,
    0x08, 0x50, 0x43, 0x28, 0x64, 0x00, 0xCE, 0x26, 0xA1, 0x2E, 0x00, 0x49, 0x36, 0xB8, 0xA8, 0xFF, 0x69, 0x00, 0x01, 0x00,
    0x09, 0x38, 0x43, 0x28, 0x72, 0x01, 0x5D, 0x27, 0xB9, 0x73, 0x91, 0x94, 0x16, 0x8E, 0xA6, 0xFF, 0xBB, 0x00, 0x01, 0x00,
    0x0A, 0x51, 0x43, 0x28, 0x1B, 0x04, 0x32, 0x25, 0x64, 0xB3, 0x71, 0x51, 0x6B, 0x50, 0xA3, 0xFF, 0x5D, 0x00, 0x01, 0x00,
    0x0B, 0x3D, 0x43, 0x28, 0x0D, 0x02, 0xDA, 0x27, 0x8B, 0x8D, 0x74, 0x2F, 0x0C, 0x11, 0xAA, 0xFF, 0x17, 0x00, 0x01, 0x00,
    0x0C, 0x3B, 0x43, 0x28, 0x12, 0x01, 0x6B, 0x27, 0x79, 0x03, 0x38, 0x2B, 0x0E, 0xBE, 0xA9, 0xFF, 0x0B, 0x00, 0x01, 0x00,
    0x0D, 0x39, 0x43, 0x28, 0xF4, 0x02, 0x1E, 0x27, 0x03, 0x17, 0x27, 0xB2, 0x22, 0xBC, 0xA7, 0xFF, 0x05, 0x00, 0x01, 0x00,
    0x0E, 0x4B, 0x43, 0x28, 0x2B, 0x03, 0xCF, 0x25, 0x7F, 0xFD, 0x19, 0x24, 0x88, 0xB4, 0xA2, 0xFF, 0x02, 0x00, 0x01, 0x00,
    0x0F, 0x75, 0x43, 0x28, 0xEE, 0x02, 0xDC, 0x27, 0xFD, 0x41, 0xE6, 0x19, 0xD1, 0x11, 0xA7, 0xFF, 0x01, 0x00, 0x01, 0x00,
    0x10, 0x5A, 0x43, 0x28, 0x63, 0x03, 0x14, 0x28, 0x5B, 0x1C, 0x24, 0xBD, 0x33, 0x3B, 0xA8, 0xFF, 0x91, 0x01, 0x01, 0x00,
    0x11, 0x55, 0x43, 0x28, 0x2B, 0x00, 0x4A, 0x27, 0xA0, 0xDF, 0x32, 0x69, 0x86, 0x64, 0xA5, 0xFF, 0xC8, 0x00, 0x01, 0x00,
    0x12, 0x4D, 0x43, 0x28, 0x6C, 0x02, 0x02, 0x28, 0xA4, 0x87, 0x4F, 0x43, 0x0F, 0x3D, 0xAC, 0xFF, 0x64, 0x00, 0x01, 0x00,
    0x13, 0x2C, 0x43, 0x28, 0x57, 0x01, 0x14, 0x26, 0xC9, 0xB2, 0xDD, 0x6C, 0xB7, 0x88, 0xA1, 0xFF, 0x32, 0x00, 0x01, 0x00,
    0x14, 0x22, 0x46, 0x28, 0x1A, 0x06, 0xDA, 0x26, 0xDA, 0x68, 0x4F, 0xCA, 0xCA, 0x60, 0xA9, 0xFF, 0x19, 0x00, 0x01, 0x00,
    0x15, 0x77, 0x43, 0x28, 0xCB, 0x01, 0xF2, 0x25, 0x68, 0xFA, 0x1D, 0xD2, 0xA5, 0x8A, 0x9F, 0xFF, 0x0C, 0x00, 0x01, 0x00,
    0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x17, 0x2B, 0x43, 0x28, 0x7E, 0x02, 0x26, 0x26, 0x61, 0xD2, 0x29, 0x1B, 0x04, 0xE1, 0xA4, 0xFF, 0x39, 0x00, 0x01, 0x00,
    0x18, 0x70, 0x43, 0x28, 0x55, 0x02, 0x56, 0x27, 0x78, 0x85, 0x53, 0x26, 0x3A, 0x0E, 0xA8, 0xFF, 0x1C, 0x00, 0x01, 0x00,
    0x19, 0x27, 0x43, 0x28, 0x38, 0x01, 0x91, 0x26, 0xD1, 0x6B, 0x0D, 0x09, 0xC3, 0x0C, 0xA4, 0xFF, 0x0E, 0x00, 0x01, 0x00,
    0x1A, 0x3E, 0x43, 0x28, 0x21, 0x02, 0xD7, 0x27, 0xDC, 0x1E, 0x7B, 0x17, 0xD0, 0x38, 0xAA, 0xFF, 0x07, 0x00, 0x01, 0x00,
    0x1B, 0x3B, 0x43, 0x28, 0xB4, 0x04, 0xD2, 0x27, 0x24, 0x3E, 0xC8, 0xC6, 0xF8, 0x11, 0xA9, 0xFF, 0x03, 0x00, 0x01, 0x00,
    0x1C, 0x0D, 0x43, 0x28, 0x67, 0x00, 0x26, 0x28, 0x8B, 0x2D, 0x4B, 0x51, 0xAF, 0x3B, 0xAB, 0xFF, 0xA8, 0x01, 0x01, 0x00,
    0x1D, 0x22, 0x43, 0x28, 0x35, 0x01, 0x3B, 0x26, 0x32, 0xA8, 0x57, 0x8C, 0xE2, 0xE4, 0xA5, 0xFF, 0xD4, 0x00, 0x01, 0x00,
    0x1E, 0x16, 0x43, 0x28, 0x71, 0x02, 0x03, 0x27, 0x70, 0x9C, 0x84, 0x05, 0x9E, 0xE4, 0xA7, 0xFF, 0x6A, 0x00, 0x01, 0x00,
    0x1F, 0x5D, 0x43, 0x28, 0x0A, 0x01, 0xF9, 0x26, 0x69, 0x3B, 0x02, 0x9D, 0x90, 0xB8, 0xA8, 0xFF, 0x35, 0x00, 0x01, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x22, 0x48, 0xBC, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x66, 0x00, 0x00, 0xB7, 0x00, 0x01, 0x00,
    0x23, 0x91, 0xBC, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6A, 0x16, 0x00, 0x00, 0x9A, 0x00, 0x01, 0x00,
    0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x25, 0x48, 0xBC, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9F, 0xF4, 0x00, 0x00, 0x3E, 0x02, 0x01, 0x00,
    0x26, 0xF2, 0xBB, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x2D, 0x00, 0x00, 0xF4, 0x03, 0x01, 0x00,
    0x27, 0xB8, 0xBA, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x27, 0x00, 0x00, 0xCF, 0x01, 0x01, 0x00,
    0x28, 0x7E, 0xBB, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x3B, 0x00, 0x00, 0x5A, 0x03, 0x01, 0x00,
    0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x2A, 0x57, 0xBF, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0x63, 0x00, 0x00, 0xE1, 0x00, 0x01, 0x00,
    0x2B, 0x5F, 0xBC, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCF, 0xAC, 0x00, 0x00, 0x69, 0x01, 0x01, 0x00,
    0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x2D, 0xC0, 0xBB, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0xA4, 0x00, 0x00, 0xD9, 0x03, 0x01, 0x00,
    0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x30, 0x48, 0xBC, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8E, 0x03, 0x00, 0x00, 0xE0, 0x01, 0x01, 0x00,
    0x31, 0xD8, 0xBB, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x5A, 0x00, 0x00, 0x07, 0x02, 0x01, 0x00,
    0x32, 0xF1, 0xBC, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB7, 0xB3, 0x00, 0x00, 0x28, 0x01, 0x01, 0x00,
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
    0x40, 0x4E, 0xC0, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBA, 0x66, 0x00, 0x00, 0x87, 0x01, 0x02, 0x01,
    0x41, 0x1B, 0xBB, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAE, 0x3B, 0x00, 0x00, 0x39, 0x06, 0x02, 0x01,
    0x42, 0xE8, 0xB7, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x4E, 0x00, 0x00, 0xE6, 0x01, 0x02, 0x01,
    0x43, 0xAC, 0xBB, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB3, 0x71, 0x00, 0x00, 0x09, 0x06, 0x02, 0x01,
    0x44, 0x04, 0xBA, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9A, 0x29, 0x00, 0x00, 0x05, 0x06, 0x02, 0x01,
    0x45, 0x77, 0xBB, 0x32, 0x75, 0x02, 0x7B, 0x26, 0xA4, 0xEF, 0xA5, 0xA6, 0x67, 0xBD, 0xEC, 0xFF, 0xF8, 0x01, 0x02, 0x01,
    0x46, 0x83, 0xBB, 0x32, 0xF5, 0x01, 0x9E, 0x24, 0x7B, 0xAF, 0x9A, 0x94, 0x66, 0x0F, 0xE4, 0xFF, 0x06, 0x06, 0x02, 0x01,
    0x47, 0x8F, 0xBB, 0x32, 0x2B, 0x01, 0x2B, 0x2A, 0x9A, 0x5C, 0xDF, 0x8F, 0x1A, 0x67, 0xE9, 0xFF, 0xF9, 0x01, 0x02, 0x01,
    0x48, 0xFC, 0xB9, 0x32, 0xDC, 0x01, 0xB0, 0x26, 0x43, 0xE3, 0xE5, 0x9F, 0x1D, 0xBF, 0xEC, 0xFF, 0x04, 0x07, 0x02, 0x01,
    0x49, 0xDE, 0xB9, 0x32, 0xC0, 0x01, 0xAF, 0x24, 0xCB, 0x9C, 0x99, 0x96, 0x1C, 0x0F, 0xE4, 0xFF, 0xBE, 0x07, 0x02, 0x01,
    0x4A, 0x23, 0x45, 0x29, 0x79, 0x00, 0x56, 0x28, 0x1E, 0x08, 0x9D, 0xA8, 0xAD, 0x47, 0xB8, 0xFF, 0x61, 0x00, 0x02, 0x01,
    0x4B, 0x2B, 0x45, 0x29, 0x3E, 0x00, 0x48, 0x28, 0x9E, 0x29, 0x80, 0xA7, 0x3A, 0x47, 0xB8, 0xFF, 0x8E, 0x07, 0x02, 0x01,
    0x4C, 0x79, 0xBB, 0x32, 0xF2, 0x00, 0x95, 0x28, 0x43, 0x49, 0xC9, 0x92, 0x54, 0x66, 0xE6, 0xFF, 0x82, 0x07, 0x02, 0x01,
    0x4D, 0x20, 0x45, 0x29, 0x65, 0x00, 0x28, 0x27, 0x40, 0x77, 0x6E, 0xE5, 0x04, 0x9C, 0xB4, 0xFF, 0x7F, 0x00, 0x02, 0x01,
    0x4E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x4F, 0x23, 0xBB, 0x32, 0xBD, 0x00, 0x1C, 0x27, 0xE7, 0xFB, 0x76, 0x97, 0xE3, 0xBC, 0xED, 0xFF, 0x7E, 0x00, 0x02, 0x01,
    0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x52, 0x23, 0x45, 0x29, 0x40, 0x00, 0x44, 0x27, 0x3A, 0xF9, 0x01, 0xD3, 0xF2, 0x9B, 0xB4, 0xFF, 0x3C, 0x00, 0x02, 0x01,
    0x53, 0x26, 0x45, 0x29, 0x3D, 0x00, 0x44, 0x27, 0xB6, 0x08, 0xBD, 0xE2, 0xF9, 0x9B, 0xB4, 0xFF, 0xC1, 0x07, 0x02, 0x01,
    0x54, 0x27, 0x45, 0x29, 0x37, 0x00, 0x3D, 0x27, 0xE9, 0xAF, 0x52, 0xDC, 0x0D, 0x9C, 0xB5, 0xFF, 0x3F, 0x00, 0x02, 0x01,
    0x55, 0x25, 0x45, 0x29, 0x31, 0x00, 0x3D, 0x27, 0x1C, 0xBA, 0xF6, 0xF1, 0x0C, 0x9C, 0xB4, 0xFF, 0xC0, 0x07, 0x02, 0x01,
    0x56, 0x1F, 0x45, 0x29, 0x15, 0x00, 0xCF, 0x26, 0x8B, 0x2B, 0x5C, 0xAB, 0xF4, 0xF1, 0xB2, 0xFF, 0xEF, 0x07, 0x02, 0x01,
    0x57, 0x1F, 0x45, 0x29, 0x14, 0x00, 0xCF, 0x26, 0x1D, 0x17, 0x73, 0x00, 0xF2, 0xF1, 0xB2, 0xFF, 0xE3, 0x07, 0x02, 0x01,
    0x58, 0x20, 0x45, 0x29, 0x13, 0x00, 0xDB, 0x26, 0x02, 0xF5, 0x7C, 0x01, 0xE5, 0xF0, 0xB2, 0xFF, 0x1E, 0x00, 0x02, 0x01,
    0x59, 0x22, 0x45, 0x29, 0x25, 0x00, 0xDC, 0x26, 0x2F, 0x32, 0xEE, 0x03, 0xEA, 0xF0, 0xB3, 0xFF, 0xE0, 0x07, 0x02, 0x01,
    0x5A, 0x28, 0x45, 0x29, 0x2D, 0x00, 0x5C, 0x27, 0x1E, 0x37, 0x3C, 0x2A, 0x9D, 0x47, 0xB6, 0xFF, 0x1F, 0x00, 0x02, 0x01,
    0x5B, 0x29, 0x45, 0x29, 0x0A, 0x00, 0x5B, 0x27, 0xDB, 0x0B, 0x98, 0x75, 0x9B, 0x47, 0xB6, 0xFF, 0x0C, 0x00, 0x02, 0x01,
    0x5C, 0x24, 0x45, 0x29, 0x13, 0x00, 0x52, 0x27, 0x66, 0xE5, 0xF7, 0x3B, 0x0E, 0x46, 0xB6, 0xFF, 0xF1, 0x07, 0x02, 0x01,
    0x5D, 0x28, 0x45, 0x29, 0x1C, 0x00, 0x52, 0x27, 0x84, 0x30, 0x77, 0x11, 0x13, 0x46, 0xB6, 0xFF, 0x0F, 0x00, 0x02, 0x01,
    0x5E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x5F, 0x22, 0x45, 0x29, 0x29, 0x00, 0x36, 0x27, 0xCE, 0x37, 0x64, 0xD4, 0xBF, 0x9B, 0xB4, 0xFF, 0xFD, 0x07, 0x02, 0x01,
    0x60, 0x23, 0x45, 0x29, 0x25, 0x00, 0x36, 0x27, 0xCB, 0x63, 0x8E, 0xE8, 0xBE, 0x9B, 0xB3, 0xFF, 0x03, 0x00, 0x02, 0x01,
    0x61, 0x27, 0x45, 0x29, 0x23, 0x00, 0x3E, 0x27, 0xF6, 0xA8, 0x28, 0x18, 0x37, 0x46, 0xB5, 0xFF, 0xFC, 0x07, 0x02, 0x01,
    0x62, 0x26, 0x45, 0x29, 0x2B, 0x00, 0x3F, 0x27, 0x67, 0xF7, 0x60, 0x0A, 0x36, 0x46, 0xB6, 0xFF, 0xFE, 0x07, 0x02, 0x01,
    0x63, 0x1F, 0x45, 0x29, 0x39, 0x00, 0xDD, 0x26, 0xEA, 0xBF, 0xFC, 0xB6, 0xD5, 0xF1, 0xB2, 0xFF, 0x01, 0x00, 0x02, 0x01,
    0x64, 0x1E, 0x45, 0x29, 0x2E, 0x00, 0xDE, 0x26, 0x44, 0xEE, 0x04, 0xC9, 0xD3, 0xF1, 0xB3, 0xFF, 0xFF, 0x07, 0x02, 0x01,
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
