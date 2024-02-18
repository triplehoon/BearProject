#include "Account.h"

using namespace BearBank;

Account::Account(const std::string code, const size_t balance) :
	mAccountCode(code),
	mBalance(balance)
{
}

std::string Account::GetAccountCode() const
{
	return mAccountCode;
}


size_t Account::GetBalance() const
{
	return mBalance;
}

eErrorCode BearBank::Account::Withdraw(const size_t amount)
{
	if (mBalance < amount)
	{
		return eErrorCode::InsufficientBalance;
	}
	mBalance -= amount;
#ifdef TEST_BANK_API
	return TestBankApi::GetInstance().SetAccountBalance(mAccountCode, mBalance);
#endif
	return eErrorCode::Success;
}

eErrorCode BearBank::Account::Deposit(const size_t amount)
{
	// check size_t overflow
	if (mBalance + amount < mBalance)
	{
		return eErrorCode::InvalidAmount;
	}

	mBalance += amount;
#ifdef TEST_BANK_API
	return TestBankApi::GetInstance().SetAccountBalance(mAccountCode, mBalance);
#endif
	return eErrorCode::Success;
}
