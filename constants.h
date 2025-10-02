#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "pch.h"

enum ErrorCodes
{
	kDuplicateUser, kRegisterSuccessfully, kUserNotFound, kMaxAmount, kNoFund, kNoBanknotes
};

enum BankNoteCodes
{
	kOne, kFive, kTen, kFifty, kHundred
};

class Errors
{
public:
	Errors();

	std::string get_error(ErrorCodes index);

private:
	std::string _errors[6];

};

#endif // !CONSTANTS_H