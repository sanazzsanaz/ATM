#pragma once
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "pch.h"
#include "TimeStamp.h"

struct Account
{
	std::string name;
	int balance;
	bool is_registered = false;

	Account(std::string& name);
};

struct Commands
{
	std::string command;
	std::string user_name;
	std::string sender;
	std::string reciever;
	int amount;
	int value;
	TimeStamp time;
	size_t id;
};

// bool CompareCommands(Commands& command1, Commands& command2);

#endif // !STRUCTURES_H