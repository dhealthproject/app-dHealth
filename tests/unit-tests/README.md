# Tests

Minimal tests for the dHealth application.

## Build

Building tests requires [CMake](https://cmake.org/) and [cmocka](https://cmocka.org/).

Once they have been installed: run:

```shell
mkdir build && cd build
cmake ..
make
```

## Running tests

In the unit-tests folder, run:

```shell
./test_transaction_parser.py
build/test_bip32_path_extraction
```
