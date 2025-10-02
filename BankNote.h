#pragma once
#ifndef BANKNOTE_H
#define BANKNOTE_H

#include "pch.h"
#include "constants.h"

class BankNote
{
public:
	std::string AddBankNote(int value, int amount);

	bool Withdraw(int amount);

	BankNote();

private:
	int _value[5];
	int _amount[5];
	int _total_amount;

};

#endif // !BANKNOTE_H