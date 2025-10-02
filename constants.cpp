#include "constants.h"

Errors::Errors()
{
	_errors[kDuplicateUser] = "Duplicate User!";
	_errors[kRegisterSuccessfully] = "Registered Successfully";
	_errors[kUserNotFound] = "No Such User Found!";
	_errors[kMaxAmount] = "Maximum Amount Exceeded!";
	_errors[kNoFund] = "Not Enough Fund!";
	_errors[kNoBanknotes] = "Not Enough Banknotes!";
}

std::string Errors::get_error(ErrorCodes index)
{
	return _errors[index];
}