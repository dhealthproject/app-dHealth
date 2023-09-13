#!/usr/bin/env python3

import sys

from pathlib import Path

from ragger.backend import LedgerCommBackend

DHEALTH_LIB_DIRECTORY = (Path(__file__).resolve().parent.parent / "functional").resolve().as_posix()
sys.path.append(DHEALTH_LIB_DIRECTORY)
from apps.dHealth import dHealthClient


def main():
    with LedgerCommBackend(None, interface="hid") as backend:
        zilliqa = dHealthClient(backend)
        version = zilliqa.send_get_version()
        print("v{}.{}.{}".format(version[0], version[1], version[2]))


if __name__ == "__main__":
    main()
