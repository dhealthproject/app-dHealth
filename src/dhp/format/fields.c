/*******************************************************************************
*   DHP Wallet
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
#include "fields.h"
#include "common.h"
#include "limitations.h"

void resolve_fieldname(const field_t *field, char* dst) {
    // Get field if field's data type is Int8 (0x01)
    if (field->dataType == STI_INT8) {
        switch (field->id) {
            CASE_FIELDNAME(DHP_INT8_MAM_REMOVAL_DELTA, "Min Removal")
            CASE_FIELDNAME(DHP_INT8_MAM_APPROVAL_DELTA, "Min Approval")
        }
    }

    // Resolve field name if field's data type is UInt8 (0x02)
    if (field->dataType == STI_UINT8) {
        switch (field->id) {
            CASE_FIELDNAME(DHP_UINT8_TXN_MESSAGE_TYPE, "Message Type")
            CASE_FIELDNAME(DHP_UINT8_MOSAIC_COUNT, "Mosaics")
            CASE_FIELDNAME(DHP_UINT8_MSC_ACTION, "Change Direction")
            CASE_FIELDNAME(DHP_UINT8_NS_REG_TYPE, "Namespace Type")
            CASE_FIELDNAME(DHP_UINT8_AA_TYPE, "Alias Type")
            CASE_FIELDNAME(DHP_UINT8_MD_DIV, "Divisibility")
            CASE_FIELDNAME(DHP_UINT8_KL_TYPE, "Action")
            CASE_FIELDNAME(DHP_UINT8_MD_TRANS_FLAG, "Transferable")
            CASE_FIELDNAME(DHP_UINT8_MD_SUPPLY_FLAG, "Supply Mutable")
            CASE_FIELDNAME(DHP_UINT8_MD_RESTRICT_FLAG, "Restrictable")
            CASE_FIELDNAME(DHP_UINT8_MAM_ADD_COUNT, "Address Add Num")
            CASE_FIELDNAME(DHP_UINT8_MAM_DEL_COUNT, "Address Del Num")
        }
    }

    // Resolve field name if field's data type is Int16 (0x03)
    if (field->dataType == STI_INT16) {
        if (field->id == DHP_INT16_VALUE_DELTA) {
            snprintf(dst, MAX_FIELDNAME_LEN, "Value Size Delta");
            return;
        }
    }

    // Resolve field name if field's data type is UInt16 (0x04)
    if (field->dataType == STI_UINT16) {
        switch (field->id) {
            CASE_FIELDNAME(DHP_UINT16_TRANSACTION_TYPE, "Transaction Type")
            CASE_FIELDNAME(DHP_UINT16_INNER_TRANSACTION_TYPE, "Inner TX Type")
            CASE_FIELDNAME(DHP_UINT16_TRANSACTION_DETAIL_TYPE, "Detail TX Type")
            CASE_FIELDNAME(DHP_UINT16_ENTITY_RESTRICT_OPERATION, "Operation Type")
            CASE_FIELDNAME(DHP_UINT16_AR_RESTRICT_TYPE, "Restriction Flag")
            CASE_FIELDNAME(DHP_UINT16_AR_RESTRICT_DIRECTION, "Restriction Flag")
            CASE_FIELDNAME(DHP_UINT16_AR_RESTRICT_OPERATION, "Restriction Flag")
        }
    }

    // Resolve field name if field's data type is UInt32 (0x05)
    if (field->dataType == STI_UINT32) {
        switch (field->id) {
            CASE_FIELDNAME(DHP_UINT32_VKL_START_POINT, "Start point")
            CASE_FIELDNAME(DHP_UINT32_VKL_END_POINT, "End point")
        }
    }

    // Resolve field name if field's data type is UInt64 (0x06)
    if (field->dataType == STI_UINT64) {
        switch (field->id) {
            CASE_FIELDNAME(DHP_UINT64_DURATION, "Duration")
            CASE_FIELDNAME(DHP_UINT64_PARENTID, "Parent ID")
            CASE_FIELDNAME(DHP_UINT64_MSC_AMOUNT, "Change Amount")
            CASE_FIELDNAME(DHP_UINT64_NS_ID, "Namespace ID")
            CASE_FIELDNAME(DHP_UINT64_MOSAIC_ID, "Mosaic ID")
            CASE_FIELDNAME(DHP_UINT64_METADATA_KEY, "Metadata Key")
        }
    }

    // Resolve field name if field's data type is Hash256 (0x07)
    if (field->dataType == STI_HASH256) {
        switch (field->id) {
            CASE_FIELDNAME(DHP_HASH256_AGG_HASH, "Agg. Tx Hash")
            CASE_FIELDNAME(DHP_HASH256_HL_HASH, "Tx Hash")
        }
    }

    // Resolve field name if field's data type is Public Key (0x08)
    if (field->dataType == STI_PUBLIC_KEY) {
        switch (field->id) {
            CASE_FIELDNAME(DHP_PUBLICKEY_ACCOUNT_KEY_LINK, "Linked Acct. PbK")
            CASE_FIELDNAME(DHP_PUBLICKEY_NODE_KEY_LINK, "Linked Node PbK")
            CASE_FIELDNAME(DHP_PUBLICKEY_VOTING_KEY_LINK, "Linked Vot. PbK")
            CASE_FIELDNAME(DHP_PUBLICKEY_VRF_KEY_LINK, "Linked Vrf PbK")
        }
    }

    // Resolve field name if field's data type is Address (0x09)
    if (field->dataType == STI_ADDRESS) {
        switch (field->id) {
            CASE_FIELDNAME(DHP_STR_RECIPIENT_ADDRESS, "Recipient")
            CASE_FIELDNAME(DHP_STR_METADATA_ADDRESS, "Target Address")
            CASE_FIELDNAME(DHP_STR_ADDRESS, "Address")
        }
    }

    // Resolve field name if field's data type is Mosaic Currency (0xA1)
    if (field->dataType == STI_MOSAIC_CURRENCY) {
        switch (field->id) {
            CASE_FIELDNAME(DHP_MOSAIC_AMOUNT, "Amount")
            CASE_FIELDNAME(DHP_MOSAIC_HL_QUANTITY, "Lock Quantity")
        }
    }

    // Resolve field name if field's data type is DHP Currency (0xA0)
    if (field->dataType == STI_DHP) {
        if (field->id == DHP_UINT64_TXN_FEE) {
            snprintf(dst, MAX_FIELDNAME_LEN, "Fee");
            return;
        }
    }

    // Resolve field name if field's data type is Message (0xA2)
    if (field->dataType == STI_MESSAGE) {
        switch (field->id) {
            CASE_FIELDNAME(DHP_STR_TXN_MESSAGE, "Message")
            CASE_FIELDNAME(DHP_STR_METADATA_VALUE, "Value")
        }
    }

    // Resolve field name if field's data type is Hex Message (0xA4)
    if (field->dataType == STI_HEX_MESSAGE) {
        switch (field->id) {
            CASE_FIELDNAME(DHP_STR_TXN_HARVESTING, "Harvesting Message")
            CASE_FIELDNAME(DHP_STR_TXN_HARVESTING_1, "Harvest. Msg 1")
            CASE_FIELDNAME(DHP_STR_TXN_HARVESTING_2, "Harvest. Msg 2")
            CASE_FIELDNAME(DHP_STR_TXN_HARVESTING_3, "Harvest. Msg 3")
        }
    }

    // Resolve field name if field's data type is STR (0x17)
    if (field->dataType == STI_STR) {
        switch (field->id) {
            CASE_FIELDNAME(DHP_UNKNOWN_MOSAIC, "Unknown Mosaic")
            CASE_FIELDNAME(DHP_STR_RECIPIENT_ADDRESS, "Recipient")
            CASE_FIELDNAME(DHP_STR_NAMESPACE, "Name")
        }
    }

    // Resolve field name if field's data type is UInt8 Addition (0xA5)
    if (field->dataType == STI_UINT8_ADDITION) {
        switch (field->id) {
            CASE_FIELDNAME(DHP_UINT8_AA_RESTRICTION, "Addition Count")
            CASE_FIELDNAME(DHP_UINT8_AM_RESTRICTION, "Addition Count")
            CASE_FIELDNAME(DHP_UINT8_AO_RESTRICTION, "Addition Count")
        }
    }

    // Resolve field name if field's data type is UInt8 Deletion (0xA6)
    if (field->dataType == STI_UINT8_DELETION) {
        switch (field->id) {
            CASE_FIELDNAME(DHP_UINT8_AA_RESTRICTION, "Deletion Count")
            CASE_FIELDNAME(DHP_UINT8_AM_RESTRICTION, "Deletion Count")
            CASE_FIELDNAME(DHP_UINT8_AO_RESTRICTION, "Deletion Count")
        }
    }

    // Default case
    snprintf(dst, MAX_FIELDNAME_LEN, "Unknown Field");
}
