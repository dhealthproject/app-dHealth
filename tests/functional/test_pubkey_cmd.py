from ragger.backend import SpeculosBackend
from ragger.backend.interface import RaisePolicy
from ragger.navigator import NavInsID, NavIns

from apps.dHealth import dHealthClient, ErrorType
from utils import ROOT_SCREENSHOT_PATH

# Proposed DHP derivation paths for tests ###
DHEALTH_PATH = "m/44'/10111'/0'/0'/0'"

SPECULOS_EXPECTED_PUBLIC_KEY = "e521d51965c3d432af417e19c5f2a967"\
                               "c73f3410d81b85b474ed2e63fbaa00b6"


def check_get_public_key_resp(backend, public_key):
    if isinstance(backend, SpeculosBackend):
        # Check against nominal Speculos seed expected results
        print(public_key.hex())
        assert public_key.hex() == SPECULOS_EXPECTED_PUBLIC_KEY


def test_get_public_key_non_confirm(backend):
    client = dHealthClient(backend)
    response = client.send_get_public_key_non_confirm(DHEALTH_PATH).data
    public_key = client.parse_get_public_key_response(response)
    check_get_public_key_resp(backend, public_key)


def test_get_public_key_confirm_accepted(firmware, backend, navigator, test_name):
    client = dHealthClient(backend)
    with client.send_async_get_public_key_confirm(DHEALTH_PATH):
        if firmware.device.startswith("nano"):
            navigator.navigate_until_text_and_compare(NavInsID.RIGHT_CLICK,
                                                      [NavInsID.BOTH_CLICK],
                                                      "Approve",
                                                      ROOT_SCREENSHOT_PATH,
                                                      test_name)
        else:
            instructions = [
                NavInsID.USE_CASE_REVIEW_TAP,
                NavIns(NavInsID.TOUCH, (200, 335)),
                NavInsID.USE_CASE_ADDRESS_CONFIRMATION_EXIT_QR,
                NavInsID.USE_CASE_ADDRESS_CONFIRMATION_CONFIRM,
                NavInsID.USE_CASE_STATUS_DISMISS
            ]
            navigator.navigate_and_compare(ROOT_SCREENSHOT_PATH,
                                           test_name,
                                           instructions)
    response = client.get_async_response().data
    public_key = client.parse_get_public_key_response(response)
    check_get_public_key_resp(backend, public_key)


# In this test we check that the GET_PUBLIC_KEY in confirmation mode replies an error if the user refuses
def test_get_public_key_confirm_refused(firmware, backend, navigator, test_name):
    client = dHealthClient(backend)

    if firmware.device.startswith("nano"):
        with client.send_async_get_public_key_confirm(DHEALTH_PATH):
            backend.raise_policy = RaisePolicy.RAISE_NOTHING
            navigator.navigate_until_text_and_compare(NavInsID.RIGHT_CLICK,
                                                      [NavInsID.BOTH_CLICK],
                                                      "Reject",
                                                      ROOT_SCREENSHOT_PATH,
                                                      test_name)
        rapdu = client.get_async_response()
        assert rapdu.status == ErrorType.ADDRESS_REJECTED
        assert len(rapdu.data) == 0
    else:
        instructions_set = [
            [
                NavInsID.USE_CASE_REVIEW_REJECT,
                NavInsID.USE_CASE_STATUS_DISMISS
            ],
            [
                NavInsID.USE_CASE_REVIEW_TAP,
                NavInsID.USE_CASE_ADDRESS_CONFIRMATION_CANCEL,
                NavInsID.USE_CASE_STATUS_DISMISS
            ]
        ]
        for i, instructions in enumerate(instructions_set):
            with client.send_async_get_public_key_confirm(DHEALTH_PATH):
                backend.raise_policy = RaisePolicy.RAISE_NOTHING
                navigator.navigate_and_compare(ROOT_SCREENSHOT_PATH,
                                               test_name + f"/part{i}",
                                               instructions)
            rapdu = client.get_async_response()
            assert rapdu.status == ErrorType.ADDRESS_REJECTED
            assert len(rapdu.data) == 0
