#pragma once
#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include "pch.h"
#include "TimeStamp.h"

class Accounts
{
public:
	/*void Sort();
	int RunCommands(std::string& result);

	void set_command_order(int command_order);
	void set_command(std::string& command);
	void set_time(TimeStamp& time);
	void set_amount(int amount);

	int get_size();

	Accounts();*/

private:
	std::string _name;
	int _balance;
	bool _is_registerd;

	std::vector<std::string> _command;
	std::vector<TimeStamp> _time;
	std::vector<int> _amount;
	std::vector<int> _command_order;

	int _size;
};

#endif // !ACCOUNTS_H