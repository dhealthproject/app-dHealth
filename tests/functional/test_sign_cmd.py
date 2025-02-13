import pytest
from json import load

from ragger.backend.interface import RaisePolicy
from ragger.navigator import NavInsID, NavIns

from apps.dHealth import dHealthClient, ErrorType
from apps.dHealth_transaction_builder import encode_txn_context
from utils import ROOT_SCREENSHOT_PATH, CORPUS_DIR, CORPUS_FILES

# Proposed DHP derivation paths for tests ###
DHEALTH_PATH = "m/44'/1'/0'/0'/0'"


def load_transaction_from_file(transaction_filename):
    with open(CORPUS_DIR / transaction_filename, "r") as f:
        transaction = load(f)
    return encode_txn_context(transaction)


def check_transaction(test_name, firmware, backend, navigator, transaction_filename):
    transaction = load_transaction_from_file(transaction_filename)
    nem = dHealthClient(backend)
    with nem.send_async_sign_message(DHEALTH_PATH, transaction):
        if firmware.device.startswith("nano"):
            navigator.navigate_until_text_and_compare(NavInsID.RIGHT_CLICK,
                                                      [NavInsID.BOTH_CLICK,
                                                       NavIns(NavInsID.WAIT, ([0]))],
                                                      "Approve",
                                                      ROOT_SCREENSHOT_PATH,
                                                      test_name)
        else:
            navigator.navigate_until_text_and_compare(NavInsID.USE_CASE_REVIEW_TAP,
                                                      [NavInsID.USE_CASE_REVIEW_CONFIRM,
                                                       NavInsID.USE_CASE_STATUS_DISMISS],
                                                      "Hold to sign",
                                                      ROOT_SCREENSHOT_PATH,
                                                      test_name)
    # Missing signature verification


@pytest.mark.parametrize("transaction_filename", CORPUS_FILES)
def test_sign_tx_accepted(test_name, firmware, backend, navigator, transaction_filename):
    folder_name = test_name + "/" + transaction_filename.replace(".json", "")
    check_transaction(folder_name, firmware, backend, navigator, transaction_filename)


def test_sign_tx_refused(test_name, firmware, backend, navigator):
    transaction = load_transaction_from_file("transfer_transaction.json")
    client = dHealthClient(backend)

    if firmware.device.startswith("nano"):
        with client.send_async_sign_message(DHEALTH_PATH, transaction):
            backend.raise_policy = RaisePolicy.RAISE_NOTHING
            navigator.navigate_until_text_and_compare(NavInsID.RIGHT_CLICK,
                                                      [NavInsID.BOTH_CLICK],
                                                      "Reject",
                                                      ROOT_SCREENSHOT_PATH,
                                                      test_name)
        rapdu = client.get_async_response()
        assert rapdu.status == ErrorType.TRANSACTION_REJECTED
        assert len(rapdu.data) == 0
    else:
        for i in range(4):
            instructions = [NavInsID.USE_CASE_REVIEW_TAP] * i
            instructions += [NavInsID.USE_CASE_REVIEW_REJECT,
                             NavInsID.USE_CASE_CHOICE_CONFIRM,
                             NavInsID.USE_CASE_STATUS_DISMISS]
            with client.send_async_sign_message(DHEALTH_PATH, transaction):
                backend.raise_policy = RaisePolicy.RAISE_NOTHING
                navigator.navigate_and_compare(ROOT_SCREENSHOT_PATH,
                                               test_name + f"/part{i}",
                                               instructions)
            rapdu = client.get_async_response()
            assert rapdu.status == ErrorType.TRANSACTION_REJECTED
            assert len(rapdu.data) == 0
