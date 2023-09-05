/*****************************************************************************
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

#include <stddef.h>   // size_t
#include <stdint.h>   // uint*_t
#include <stdbool.h>  // bool

#include "../types.h"


/**
 * Parse APDU command from byte buffer.
 *
 * @param[in]  buf
 *   Byte buffer with raw APDU command.
 * @param[in]  buf_len
 *   Length of byte buffer.
 *
 * 
 * @param[out] cmd
 *   Structured APDU command (CLA, INS, P1, P2, Lc, Command data).
 * 
 * @return true if success, false otherwise.
 */
bool apdu_parser( uint8_t* buf, size_t buf_len, ApduCommand_t* cmd );
