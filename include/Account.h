#pragma once

#include <string>

#include "TestBankApi.h"
#include "ErrorCode.h"

namespace BearBank
{
	class Account
	{
	private:
		std::string mAccountCode;
		// assume that the balance is in dollars, there are no cents, and It is always positive
		size_t mBalance;

	public:
		Account(const std::string code, const size_t balance);

		std::string GetAccountCode() const;
		size_t GetBalance() const;

		eErrorCode Withdraw(const size_t amount);
		eErrorCode Deposit(const size_t amount);
	};
}

