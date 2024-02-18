#include "AtmController.h"

using namespace BearBank;

AtmController::AtmController() :
	mAccounts(std::vector<Account>()),
	mSelectedAccountIndex(-1),
	mCardNumber(""),
	mPinErrorCount(0)
{
}

AtmController::~AtmController()
{
}

AtmController& BearBank::AtmController::GetInstance()
{
	static AtmController instance;
	return instance;
}

eErrorCode AtmController::InsertCard(const std::string cardNumber)
{
	if (mCardNumber != "")
	{
		return eErrorCode::CardAlreadyInserted;
	}

	// check card number is valid xxxx-xxxxx-xxxx-xxxx
	if (cardNumber.length() != 19)
	{
		return eErrorCode::InvalidCardNumber;
	}
	if (cardNumber[4] != '-' || cardNumber[9] != '-' || cardNumber[14] != '-')
	{
		return eErrorCode::InvalidCardNumber;
	}
	for (size_t i = 0; i < 19; i++)
	{
		if (i == 4 || i == 9 || i == 14)
		{
			continue;
		}
		if (cardNumber[i] < '0' || cardNumber[i] > '9')
		{
			return eErrorCode::InvalidCardNumber;
		}
	}

	mCardNumber = cardNumber;

	//reset account info
	mAccounts = std::vector<Account>();
	mSelectedAccountIndex = -1;

	return eErrorCode::Success;
}

eErrorCode BearBank::AtmController::EnterPin(const std::string pin)
{
	if (mCardNumber == "")
	{
		return eErrorCode::NoCardInserted;
	}

#ifdef TEST_BANK_API
	if (TestBankApi::GetInstance().CheckPinValid(mCardNumber, pin) == false)
	{
		if (++mPinErrorCount >= MAX_PIN_ERROR_COUNT)
		{
			EjectCard();
		}
		return eErrorCode::InvalidPin;
	}
	else
	{
		std::vector<std::string> accountList;
		eErrorCode eCode = TestBankApi::GetInstance().GetAccountList(mCardNumber, &accountList);
		if (eCode != eErrorCode::Success)
		{
			return eCode;
		}

		for (int i = 0; i < accountList.size(); i++)
		{
			size_t balance;
			eCode = TestBankApi::GetInstance().GetAccountBalance(accountList[i], &balance);
			// the eCode always succcess if Test BankApi cases are valid.
			assert(eCode == eErrorCode::Success);
			mAccounts.push_back(Account(accountList[i], balance));
		}
		mSelectedAccountIndex = -1;
		return eErrorCode::Success;
	}
#endif
	return eErrorCode::Success;
}

eErrorCode BearBank::AtmController::GetCurrentCardNumber(std::string* outCardNumber) const
{
	assert(outCardNumber);
	if (mCardNumber == "")
	{
		return eErrorCode::NoCardInserted;
	}
	*outCardNumber = mCardNumber;
	return eErrorCode::Success;
}

size_t BearBank::AtmController::GetAccountCount() const
{
	return mAccounts.size();
}

eErrorCode BearBank::AtmController::ListAccountCodes(std::vector<std::string>* outAccountList) const
{
	assert(outAccountList != nullptr);
	if (mCardNumber == "")
	{
		return eErrorCode::NoCardInserted;
	}
	if (mAccounts.size() == 0)
	{
		return eErrorCode::AccountNotFound;
	}
	for (int i = 0; i < mAccounts.size(); i++)
	{
		outAccountList->push_back(mAccounts[i].GetAccountCode());
	}
	return eErrorCode();
}

eErrorCode BearBank::AtmController::SelectAccount(const std::string accountCode)
{
	if (mCardNumber == "")
	{
		return eErrorCode::NoCardInserted;
	}
	for (int i = 0; i < mAccounts.size(); i++)
	{
		if (mAccounts[i].GetAccountCode() == accountCode)
		{
			mSelectedAccountIndex = i;
			return eErrorCode::Success;
		}
	}
	return eErrorCode::AccountNotFound;
}

eErrorCode BearBank::AtmController::SelectAccount(const size_t accountIndex)
{
	if (mCardNumber == "")
	{
		mSelectedAccountIndex = -1;
		return eErrorCode::NoCardInserted;
	}
	if (accountIndex >= mAccounts.size())
	{
		mSelectedAccountIndex = -1;
		return eErrorCode::AccountNotFound;
	}
	mSelectedAccountIndex = accountIndex;
	return eErrorCode::Success;
}

eErrorCode BearBank::AtmController::GetCurrentAccountCode(std::string* outAccountCode) const
{
	assert(outAccountCode);
	if (mCardNumber == "")
	{
		return eErrorCode::NoCardInserted;
	}
	if (mSelectedAccountIndex == -1)
	{
		return eErrorCode::AccountNotFound;
	}
	*outAccountCode = mAccounts[mSelectedAccountIndex].GetAccountCode();
	return eErrorCode::Success;
}

eErrorCode BearBank::AtmController::GetBalance(size_t* outBalance)
{
	if (mCardNumber == "")
	{
		return eErrorCode::NoCardInserted;
	}
	if (mSelectedAccountIndex == -1)
	{
		return eErrorCode::NoAccountSelected;
	}
	*outBalance = mAccounts[mSelectedAccountIndex].GetBalance();
	return eErrorCode::Success;
}

eErrorCode BearBank::AtmController::Deposit(const size_t amount)
{
	if (mCardNumber == "")
	{
		return eErrorCode::NoCardInserted;
	}
	if (mSelectedAccountIndex == -1)
	{
		return eErrorCode::NoAccountSelected;
	}
	return mAccounts[mSelectedAccountIndex].Deposit(amount);
}

eErrorCode BearBank::AtmController::Withdraw(const size_t amount)
{
	if (mCardNumber == "")
	{
		return eErrorCode::NoCardInserted;
	}
	if (mSelectedAccountIndex == -1)
	{
		return eErrorCode::NoAccountSelected;
	}
	return mAccounts[mSelectedAccountIndex].Withdraw(amount);
}

eErrorCode BearBank::AtmController::EjectCard()
{
	// ecject card, reset card number and account info
	mCardNumber = "";
	mAccounts = std::vector<Account>();
	mSelectedAccountIndex = -1;
	mPinErrorCount = 0;
	return eErrorCode::Success;
}
