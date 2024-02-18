#include "TestBankApi.h"
using namespace BearBank;

TestBankApi::TestBankApi()
{
	SetDefaultData();
}

TestBankApi& BearBank::TestBankApi::GetInstance()
{
	static TestBankApi instance;
	return instance;
}

void BearBank::TestBankApi::SetDefaultData()
{
	mCardPinMap["1234-5678-1234-5678"] = "1234";
	mCardPinMap["9876-5432-9876-5432"] = "9876";

	mCardAccountMap["1234-5678-1234-5678"] = { "1234-56789", "1234-56788" };
	mCardAccountMap["9876-5432-9876-5432"] = { "9876-54321", "9876-54322" };

	mAccountBalanceMap["1234-56789"] = 100;
	mAccountBalanceMap["1234-56788"] = 200;
	mAccountBalanceMap["9876-54321"] = 300;
	mAccountBalanceMap["9876-54322"] = 400;

	// write more test cases if you wants
}

bool BearBank::TestBankApi::CheckPinValid(const std::string cardNumber, const std::string pin)
{
	// Check if the length of card number is exactly 19 characters
	assert(cardNumber.length() == 19);

	// Check if the dashes are in the correct positions
	assert(cardNumber[4] == '-' && cardNumber[9] == '-' && cardNumber[14] == '-');

	// Check if all other characters are digits
	for (size_t i = 0; i < 19; i++) {
		if (i == 4 || i == 9 || i == 14) {
			continue;
		}
		assert(cardNumber[i] >= '0' && cardNumber[i] <= '9');
	}
	
	// Check if the card number exists in the map
	assert(mCardPinMap.find(cardNumber) != mCardPinMap.end());

	if (mCardPinMap[cardNumber] == pin)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

eErrorCode BearBank::TestBankApi::GetAccountList(const std::string cardNumber, std::vector<std::string>* outAccountList)
{
	assert(outAccountList != nullptr);

	// Check if the length of card number is exactly 19 characters
	if (cardNumber.length() != 19)
	{
		return eErrorCode::InvalidCardNumber;
	}
	// Check if the dashes are in the correct positions
	if (cardNumber[4] != '-' && cardNumber[9] != '-' && cardNumber[14] != '-')
	{
		return eErrorCode::InvalidCardNumber;
	}
	// Check if all other characters are digits
	for (size_t i = 0; i < 19; i++) {
		if (i == 4 || i == 9 || i == 14) {
			continue;
		}
		if (cardNumber[i] < '0' && cardNumber[i] > '9')
		{
			return eErrorCode::InvalidCardNumber;
		}
	}

	// Check if the card number exists in the map
	if (mCardPinMap.find(cardNumber) == mCardPinMap.end())
	{
		return eErrorCode::CardNumberNotFound;
	}
	else
	{
		*outAccountList = mCardAccountMap[cardNumber];
		return eErrorCode::Success;
	}
}

eErrorCode BearBank::TestBankApi::GetAccountBalance(const std::string accountCode, size_t* outBalance)
{
	assert(outBalance != nullptr);
	if (mAccountBalanceMap.find(accountCode) == mAccountBalanceMap.end())
	{
		return eErrorCode::AccountNotFound;
	}
	else
	{
		*outBalance = mAccountBalanceMap[accountCode];
		return eErrorCode::Success;
	}
}

eErrorCode BearBank::TestBankApi::SetAccountBalance(const std::string accountCode, const size_t balance)
{
	if (mAccountBalanceMap.find(accountCode) == mAccountBalanceMap.end())
	{
		return eErrorCode::AccountNotFound;
	}
	else
	{
		mAccountBalanceMap[accountCode] = balance;
		return eErrorCode::Success;
	}
}
