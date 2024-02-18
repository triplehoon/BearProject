#pragma once

// enum class to list error codes

namespace BearBank
{
	enum class eErrorCode
	{
		// Common
		Success = 0,
		UnknownError,
		NetworkError,

		// Account Error
		InsufficientBalance,
		InvalidAmount,
		AccountNotFound,
		NoAccountSelected,

		// Card Errors
		CardAlreadyInserted,
		InvalidCardNumber,
		InvalidPin,

		CardNumberNotFound,
		NoCardInserted,
	};
}