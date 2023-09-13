/*******************************************************************************
 *   DHP Wallet
 *    (c) 2020 Ledger
 *    (c) 2023 dHealth
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
#ifndef LEDGER_APP_DHP_TRANSACTION_H
#define LEDGER_APP_DHP_TRANSACTION_H

#include "common.h"
#include "dhp/parse/dhp_parse.h"

typedef void (*result_action_t)(unsigned int result);

void review_transaction(fields_array_t* fields, action_t onApprove, action_t onReject);

#endif  // LEDGER_APP_DHP_TRANSACTION_H
