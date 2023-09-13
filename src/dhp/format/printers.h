/*******************************************************************************
 *   DHP Wallet
 *   (c) 2017 Ledger
 *   (c) 2023 dHealth
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
 ********************************************************************************/
#ifndef LEDGER_APP_DHP_PRINTERS_H
#define LEDGER_APP_DHP_PRINTERS_H

#include <stdint.h>
#include "parse/dhp_parse.h"

enum _parser_error {
    E_SUCCESS = 0,
    E_NOT_ENOUGH_DATA = -1,
    E_INVALID_DATA = -2,
    E_TOO_MANY_FIELDS = -3,
};

int snprintf_hex(char *dst,
                 uint16_t maxLen,
                 const uint8_t *src,
                 uint16_t dataLength,
                 uint8_t reverse);
int snprintf_hex2ascii(char *dst, uint16_t maxLen, const uint8_t *src, uint16_t dataLength);
int snprintf_ascii(char *dst, uint16_t maxLen, const uint8_t *src, uint16_t dataLength);
int snprintf_number(char *dst, uint16_t maxLen, uint64_t value);
int snprintf_mosaic(char *dst, uint16_t maxLen, const mosaic_t *mosaic, char *asset);

#endif  // LEDGER_APP_DHP_PRINTERS_H
