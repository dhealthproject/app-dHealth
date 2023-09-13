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
#include "crypto.h"
#include "dhp_helpers.h"
#include "limitations.h"

#include <string.h>

void crypto_derive_private_key(const uint32_t* bip32_path,
                               const uint8_t bip32_path_len,
                               const CurveType_t curve_type,
                               cx_ecfp_private_key_t* private_key) {
    uint8_t raw_private_key[64] = {0};

    BEGIN_TRY {
        TRY {
            // derive the seed with bip32_path
            if (curve_type == CURVE_Ed25519) {
                unsigned char seed_key[] = "ed25519 seed";

                int r = os_derive_bip32_with_seed_no_throw(HDW_ED25519_SLIP10,
                                                           CX_CURVE_Ed25519,
                                                           bip32_path,
                                                           bip32_path_len,
                                                           raw_private_key,
                                                           NULL,
                                                           seed_key,
                                                           sizeof(seed_key) - 1);

                if (r != CX_OK) {
                    THROW(r);
                }
            } else {
                int r = os_derive_bip32_no_throw(CX_CURVE_256K1,
                                                 bip32_path,
                                                 bip32_path_len,
                                                 raw_private_key,
                                                 NULL);

                if (r != CX_OK) {
                    THROW(r);
                }
            }

            // initialize private_key from raw key
            cx_ecfp_init_private_key_no_throw(CX_CURVE_Ed25519,
                                              raw_private_key,
                                              DHP_PRIVATE_KEY_LENGTH,
                                              private_key);
        }
        CATCH_OTHER(e) {
            THROW(e);
        }
        FINALLY {
            explicit_bzero(&raw_private_key, sizeof(raw_private_key));
        }
    }
    END_TRY;
}
