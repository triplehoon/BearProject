#pragma once
#include <iostream>

#include "AtmController.h"

using namespace BearBank;

inline void TestCase1()
{
	// insert card with invalid card number
	AtmController& atmController = AtmController::GetInstance();
	std::cout << "Test insterting card with invalid card number" << std::endl;
	eErrorCode result = atmController.InsertCard("1234-56789-1234-544");
	if (result != eErrorCode::InvalidCardNumber)
	{
		std::cout << "Test failed: " << "InvalidCardNumber 1" << std::endl;
		assert(false);
		return;
	}
	if (eErrorCode::NoCardInserted != atmController.EnterPin("1234"))
	{
		std::cout << "Test failed: " << "InvalidCardNumber 2" << std::endl;
		assert(false);
		return;
	}
	std::cout << "Test passed" << std::endl;
	atmController.EjectCard();
}
inline void TestCase2()
{
	// insert correct card number
	AtmController& atmController = AtmController::GetInstance();
	std::cout << "Test insterting card with valid card number" << std::endl;
	eErrorCode result = atmController.InsertCard("1234-5678-1234-5678");
	if (result != eErrorCode::Success)
	{
		std::cout << "Test failed: " << "validCardNumber 1" << std::endl;
	}

	// enter invalid pin
	result = atmController.EnterPin("2345");
	if (result != eErrorCode::InvalidPin)
	{
		std::cout << "Test failed: " << "InvalidPin 1" << std::endl;
		assert(false);
		return;
	}

	// enter invalid pin for 4 times more
	for (int i = 0; i < 4; ++i)
	{
		atmController.EnterPin("2345");
	}

	// if card is exist it is fail
	std::string cardNumber = "";
	result = atmController.GetCurrentCardNumber(&cardNumber);
	if (result != eErrorCode::NoCardInserted)
	{
		std::cout << "Test failed: " << "InvalidPin 2" << std::endl;
		assert(false);
		return;
	}
	std::cout << "Test passed" << std::endl;
	atmController.EjectCard();
}
inline void TestCase3()
{
	// insert correct card number
	AtmController& atmController = AtmController::GetInstance();
	std::cout << "Test insterting card with valid card number" << std::endl;
	eErrorCode result = atmController.InsertCard("1234-5678-1234-5678");
	if (result != eErrorCode::Success)
	{
		std::cout << "Test failed: " << "validCardNumber 1" << std::endl;
	}

	// enter valid pin
	result = atmController.EnterPin("1234");
	if (result != eErrorCode::Success)
	{
		std::cout << "Test failed: " << "validPin 1" << std::endl;
		assert(false);
		return;
	}

	// get accounts
	std::vector<std::string> accountList;
	result = atmController.ListAccountCodes(&accountList);
	if (result != eErrorCode::Success)
	{
		std::cout << "Test failed: " << "ListAccountCodes 1" << std::endl;
		assert(false);
		return;
	}
	if (accountList.size() != 2)
	{
		std::cout << "Test failed: " << "ListAccountCodes 2" << std::endl;
		assert(false);
		return;
	}
	if (accountList[0] != "1234-56789" || accountList[1] != "1234-56788")
	{
		std::cout << "Test failed: " << "ListAccountCodes 3" << std::endl;
		assert(false);
		return;
	}

	// get balance for each account
	result = atmController.SelectAccount(0);
	if (result != eErrorCode::Success)
	{
		std::cout << "Test failed: " << "SelectAccount 1" << std::endl;
		assert(false);
		return;
	}
	result = atmController.SelectAccount("1234-56788");
	if (result != eErrorCode::Success)
	{
		std::cout << "Test failed: " << "SelectAccount 2" << std::endl;
		assert(false);
		return;
	}
	std::string accountCode = "";
	result = atmController.GetCurrentAccountCode(&accountCode);
	if (result != eErrorCode::Success)
	{
		std::cout << "Test failed: " << "GetCurrentAccountCode 1" << std::endl;
		assert(false);
		return;
	}
	if (accountCode != "1234-56788")
	{
		std::cout << "Test failed: " << "GetCurrentAccountCode 2" << std::endl;
		assert(false);
		return;
	}
	size_t balance = 0;
	result = atmController.GetBalance(&balance);
	if (result != eErrorCode::Success)
	{
		std::cout << "Test failed: " << "GetBalance 1" << std::endl;
		assert(false);
		return;
	}
	if (balance != 200)
	{
		std::cout << "Test failed: " << "GetBalance 2" << std::endl;
		assert(false);
		return;
	}
	atmController.EjectCard();
}
inline void TestCase4()
{
	AtmController& atmController = AtmController::GetInstance();
	std::cout << "Test insterting card with valid card number" << std::endl;
	eErrorCode result = atmController.InsertCard("1234-5678-1234-5678");
	result = atmController.EnterPin("1234");
	std::vector<std::string> accountList;
	result = atmController.ListAccountCodes(&accountList);
	result = atmController.SelectAccount(0);

	// test deposit
	std::cout << "Test deposit" << std::endl;
	size_t balance = 0;
	result = atmController.GetBalance(&balance);
	if (result != eErrorCode::Success)
	{
		std::cout << "Test failed: " << "GetBalance 1" << std::endl;
		assert(false);
		return;
	}
	if (balance != 100)
	{
		std::cout << "Test failed: " << "GetBalance 2" << std::endl;
		assert(false);
		return;
	}
	result = atmController.Deposit(100);
	if (result != eErrorCode::Success)
	{
		std::cout << "Test failed: " << "Deposit 1" << std::endl;
		assert(false);
		return;
	}
	result = atmController.GetBalance(&balance);
	if (result != eErrorCode::Success)
	{
		std::cout << "Test failed: " << "GetBalance 3" << std::endl;
		assert(false);
		return;
	}
	if (balance != 200)
	{
		std::cout << "Test failed: " << "GetBalance 4" << std::endl;
		assert(false);
		return;
	}
	//test withdraw
	std::cout << "Test withdraw" << std::endl;
	result = atmController.Withdraw(300);
	if (result != eErrorCode::InsufficientBalance)
	{
		std::cout << "Test failed: " << "Withdraw 1" << std::endl;
		assert(false);
		return;
	}
	result = atmController.Withdraw(100);
	if (result != eErrorCode::Success)
	{
		std::cout << "Test failed: " << "Withdraw 2" << std::endl;
		assert(false);
		return;
	}
	result = atmController.GetBalance(&balance);
	if (result != eErrorCode::Success)
	{
		std::cout << "Test failed: " << "GetBalance 5" << std::endl;
		assert(false);
		return;
	}
	if (balance != 100)
	{
		std::cout << "Test failed: " << "GetBalance 6" << std::endl;
		assert(false);
		return;
	}
#ifdef TEST_BANK_API
	TestBankApi::GetInstance().SetDefaultData();
#endif // TEST_BANK_API

	atmController.EjectCard();
}
