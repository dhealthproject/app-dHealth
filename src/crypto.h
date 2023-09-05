/*****************************************************************************
 *   Ledger App Boilerplate.
 *   (c) 2020 Ledger SAS.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *****************************************************************************/
#pragma once

#include <stdint.h>  
#include "os.h"


/**
 * Supported cryptographic curves
 */
typedef enum
{
    CURVE_Ed25519 = 1,
    CURVE_256K1   = 2

} CurveType_t;




/**
 * Derive private key given BIP32 path.
 *
 * @param[in]  bip32_path
 *   Pointer to buffer with BIP32 path. 
 *   For example the bip32 path m/44'/93'/5'/0/0 would be represented as follows:
 *	 uint32_t bip32Path[] = {44 | 0x80000000, 93 | 0x80000000, 5 | 0x80000000, 0, 0};
 *
 * @param[in]  bip32_path_len
 *   Size of 'bip32_path[]' array
 *
 * @param[in]  curve_type
 *   The curve type
 *
 * @param[out] private_key
 *   The derived private key result.
 *
 */
void crypto_derive_private_key( const uint32_t*        bip32_path,
                                const uint8_t          bip32_path_len,
                                const CurveType_t      curve_type,
                                cx_ecfp_private_key_t* private_key    );