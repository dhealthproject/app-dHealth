#!/usr/bin/env python3

import sys
import argparse

from pathlib import Path

from ragger.backend import LedgerCommBackend

DHEALTH_LIB_DIRECTORY = (Path(__file__).resolve().parent.parent / "functional").resolve().as_posix()
sys.path.append(DHEALTH_LIB_DIRECTORY)
from apps.dHealth import dHealthClient, TESTNET


parser = argparse.ArgumentParser()
parser.add_argument('--path', help="BIP 32 path to use")
parser.add_argument('--confirm', help="Request confirmation", action="store_true")
args = parser.parse_args()

if args.path is None:
    # Use testnet coin type
    args.path = "m/44'/1'/0'/0'/0'"


with LedgerCommBackend(None, interface="hid") as backend:
    client = dHealthClient(backend)

    if args.confirm:
        with client.send_async_get_public_key_confirm(args.path, TESTNET):
            print("Please accept the request on the device")
        rapdu = client.get_async_response()
    else:
        rapdu = client.send_get_public_key_non_confirm(args.path, TESTNET)

    public_key = client.parse_get_public_key_response(rapdu.data, TESTNET)
    print("Public Key:", public_key.hex())
    print("length: ", len(public_key.hex()))
