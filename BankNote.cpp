#include "BankNote.h"

std::string BankNote::AddBankNote(int value, int amount)
{
	size_t i = 0;
	while (i < 5)
	{
		if (_amount[i] == value) {
			break;
		}
		++i;
	}
	
	_value[i] += amount;
	_total_amount += (_amount[i] * amount);

	return std::to_string(_total_amount);
}

bool BankNote::Withdraw(int amount)
{
	if (amount < _total_amount) {
		int value[5]{};

		while (amount > 99) {
			amount -= 100;
			++value[kHundred];
		}
		if (value[kHundred] > _value[kHundred]) {
			return false;
		}

		while (amount > 49) {
			amount -= 50;
			++value[kFifty];
		}
		if (value[kFifty] > _value[kFifty]) {
			return false;
		}

		while (amount > 9) {
			amount -= 10;
			++value[kTen];
		}
		if (value[kTen] > _value[kTen]) {
			return false;
		}

		while (amount > 4) {
			amount -= 5;
			++value[kFive];
		}
		if (value[kFive] > _value[kFive]) {
			return false;
		}

		while (amount > 0) {
			amount -= 1;
			++value[kOne];
		}
		if (value[kOne] > _value[kOne]) {
			return false;
		}

		for (size_t i = 0; i < 5; ++i)
		{
			_value[i] -= value[i];
			_total_amount -= (_amount[i] * value[i]);
		}
		return true;
	}

	return false;
}

BankNote::BankNote()
{
	_amount[kOne] = 1;
	_amount[kFive] = 5;
	_amount[kTen] = 10;
	_amount[kFifty] = 50;
	_amount[kHundred] = 100;

	_total_amount = 0;
	for (size_t i = 0; i < 5; i++) {
		_value[i] = 10;
		_total_amount += (_amount[i] * _value[i]);
	}
}
