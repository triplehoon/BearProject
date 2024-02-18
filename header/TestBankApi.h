#pragma once

// only works one when TEST_BANK_API is define. Should implement true bank api when available.
#ifdef TEST_BANK_API

#include <map>
#include <vector>
#include <string>
#include <cassert>

#include "ErrorCode.h"

namespace BearBank
{
	class TestBankApi
	{
	private:
		TestBankApi(const TestBankApi& other) = delete; // not use
		TestBankApi& operator=(const TestBankApi& other) = delete; // not use
		std::map<std::string, std::string> mCardPinMap;

		std::map<std::string, std::vector<std::string>> mCardAccountMap;

		std::map<std::string, size_t> mAccountBalanceMap;
		TestBankApi();

	public:
		static TestBankApi& GetInstance();

		void SetDefaultData();

		bool CheckPinValid(const std::string cardNumber, const std::string pin);

		eErrorCode GetAccountList(const std::string cardNumber, std::vector<std::string>* outAccountList);

		eErrorCode GetAccountBalance(const std::string accountCode, size_t* outBalance);

		eErrorCode SetAccountBalance(const std::string accountCode, const size_t balance);
	};
}


#endif // TEST_BANK_API
