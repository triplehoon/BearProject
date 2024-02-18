#pragma once
#define MAX_PIN_ERROR_COUNT (5)

#include <string>
#include <vector>

#include "Account.h"


namespace BearBank
{
	// Singleton class, Because ATM is a single machine.
	class AtmController
	{
	private:
		AtmController();
		AtmController(const AtmController& other) = delete; // not use
		AtmController& operator=(const AtmController& other) = delete; // not use
		~AtmController();

		std::vector<Account> mAccounts;
		
		// if no account is selected, mSelectedAccountIndex is -1
		int mSelectedAccountIndex;

		std::string mCardNumber;

		size_t mPinErrorCount;

	public:
		static AtmController& GetInstance();

		eErrorCode InsertCard(const std::string cardNumber);
		eErrorCode EnterPin(const std::string pin);
		eErrorCode GetCurrentCardNumber(std::string* outCardNumber) const;

		size_t GetAccountCount() const;
		eErrorCode ListAccountCodes(std::vector<std::string>* outAccountList) const;
		eErrorCode SelectAccount(const std::string accountCode);
		eErrorCode SelectAccount(const size_t accountIndex);
		eErrorCode GetCurrentAccountCode(std::string* outAccountCode) const;

		eErrorCode GetBalance(size_t* outBalance);
		eErrorCode Deposit(const size_t amount);
		eErrorCode Withdraw(const size_t amount);
		eErrorCode EjectCard();

	};
}

