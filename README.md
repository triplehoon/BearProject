# Introduction

This code is Atm Control code for bear robotics assignment.


# Requirements

- based on ubuntu
- C++11
- CMake
- g++

# How To Clone


```bash
git clone {repo}
```

# How To Build

```bash
sudo apt install g++ cmake
cd {repo}
mkdir build
cd build
cmake ..
make
```

# How To Run

```bash
./BearProject
```

# Simple code explanation

## Account.h
Class for account. It has balance and account number.

## AtmController.h
Singleton class for atm controller. First incerst card and then enter pin.
The account list will be shown, if the pin is correct. Then user can select the account and see the balance, withdraw money or deposit money.

## ErrorCodes.h
Enum class for error codes. It is used for error handling.

## TestBankApi.h
Also singleton class for mocking real bank api, testing. In the code, there are hard coded card, pin and account list with balance. TestCases.h is matching with this class. To use this class, you have to define TEST_BANK_API in preprocessor.
The functions containing the TestBankApi have to reimplement for real bank api.

## TestCases.h
Class for testing. Four test cases are implemented.

## main.cpp
Main file for running the code.
