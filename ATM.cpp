#include "structures.h"
#include "constants.h"
#include "BankNote.h"

/*
* Compares two commands
* returns true if the first command's time is less than second command's time
*/
bool CompareCommands(Commands command1, Commands command2)
{
    return TimeStamp::Compare(command1.time, command2.time);
}

int main()
{
	// Gets number of commands from user
	int count;
	std::cin >> count;
	std::vector<Commands> commands(count);
	std::vector<Account> accounts;
	accounts.reserve(count);

	// Gets all the commands from user
	std::string time;
	for (size_t i = 0; i < commands.size(); ++i) {
		std::cin >> commands[i].command;

		if (commands[i].command == "REGISTER") {
			std::cin >> commands[i].user_name;
			accounts.emplace_back(Account(commands[i].user_name));
		}
		else if (commands[i].command == "DEPOSIT") {
			std::cin >> commands[i].user_name >> commands[i].amount;
			accounts.emplace_back(Account(commands[i].user_name));
		}
		else if (commands[i].command == "WITHDRAW") {
			std::cin >> commands[i].user_name >> commands[i].amount;
			accounts.emplace_back(Account(commands[i].user_name));
		}
		else if (commands[i].command == "TRANSFER") {
			std::cin >> commands[i].sender >> commands[i].reciever >> commands[i].amount;
			accounts.emplace_back(Account(commands[i].sender));
			accounts.emplace_back(Account(commands[i].reciever));
		}
		else if (commands[i].command == "GET_BALANCE") {
			std::cin >> commands[i].user_name;
			accounts.emplace_back(Account(commands[i].user_name));
		}
		else if (commands[i].command == "ADD_BANKNOTE") {
			std::cin >> commands[i].value >> commands[i].amount;
		}

		std::cin >> time;
		commands[i].time = TimeStamp(time);

		commands[i].id = i;
	}

	// Sorts commands according to time
	std::sort(commands.begin(), commands.end(), CompareCommands);

	// Stores results in a vector
	std::vector<std::string> results(count);
	std::vector<Commands> transfer_command;
	BankNote bank_note;
	Errors error;

	for (size_t i = 0; i < commands.size(); ++i) {

		// Transfer to reciever at one hour later
		for (size_t j = 0; j < transfer_command.size(); ++j) {
			if (!TimeStamp::Compare(commands[i].time, transfer_command[j].time)) {
				accounts[transfer_command[j].id].balance += transfer_command[j].amount;
				transfer_command.erase(transfer_command.cbegin() + j);
			}
		}

		// Checks all the commands and stores the result
		if (commands[i].command == "REGISTER") {
			for (size_t j = 0; j < accounts.size(); ++j) {
				if (commands[i].user_name == accounts[j].name) {
					if (accounts[j].is_registered) {
						results[commands[i].id] = error.get_error(kDuplicateUser);
					} else {
						results[commands[i].id] = error.get_error(kRegisterSuccessfully);
						accounts[j].balance = 100;
						accounts[j].is_registered = true;
					}
					break;
				}
			}
		}
		else if (commands[i].command == "DEPOSIT") {
			for (size_t j = 0; j < accounts.size(); ++j) {
				if (commands[i].user_name == accounts[j].name) {
					if (accounts[j].is_registered) {
						accounts[j].balance += commands[i].amount;
						results[commands[i].id] = std::to_string(accounts[j].balance);
						// results[commands[i].id] = commands[i].user_name + ' ' + std::to_string(accounts[j].balance);
					} else {
						results[commands[i].id] = error.get_error(kUserNotFound);
					}
					break;
				}
			}
		}
		else if (commands[i].command == "WITHDRAW") {
			for (size_t j = 0; j < accounts.size(); ++j) {
				if (commands[i].user_name == accounts[j].name) {
					if (accounts[j].is_registered) {
						if (commands[i].amount > 200) {
							results[commands[i].id] = error.get_error(kMaxAmount);
						} else if (accounts[j].balance < commands[i].amount) {
							results[commands[i].id] = error.get_error(kNoFund);
						} else if (!bank_note.Withdraw(commands[i].amount)) {
							results[commands[i].id] = error.get_error(kNoBanknotes);
						} else {
							accounts[j].balance -= commands[i].amount;
							results[commands[i].id] = std::to_string(accounts[j].balance);
							// results[commands[i].id] = commands[i].user_name + ' ' + std::to_string(accounts[j].balance);
						}
					} else {
						results[commands[i].id] = error.get_error(kUserNotFound);
					}
					break;
				}
			}
		}
		else if (commands[i].command == "TRANSFER") {
			for (size_t j = 0; j < accounts.size(); ++j) {
				if (commands[i].sender == accounts[j].name) {
					if (accounts[j].is_registered) {
						for (size_t k = 0; k < accounts.size(); ++k) {
							if (commands[i].reciever == accounts[k].name) {
								if (accounts[k].is_registered) {
									if (commands[i].amount > 3000) {
										results[commands[i].id] = error.get_error(kMaxAmount);
									} else if (accounts[j].balance < commands[i].amount) {
										results[commands[i].id] = error.get_error(kNoFund);
									} else {
										accounts[j].balance -= commands[i].amount;
										results[commands[i].id] = std::to_string(accounts[j].balance);
										// results[commands[i].id] = commands[i].sender + ' ' + std::to_string(accounts[j].balance);

										// Stores command to transfer amount at one hour later
										commands[i].time.AddAnHour();
										commands[i].id = k;
										transfer_command.emplace_back(commands[i]);
									}
								} else {
									results[commands[i].id] = error.get_error(kUserNotFound);
								}
								break;
							}
						}
					} else {
						results[commands[i].id] = error.get_error(kUserNotFound);
					}
					break;
				}
			}
		}
		else if (commands[i].command == "GET_BALANCE") {
			for (size_t j = 0; j < accounts.size(); ++j) {
				if (commands[i].user_name == accounts[j].name) {
					if (accounts[j].is_registered) {
						if (accounts[j].balance < 10) {
							results[commands[i].id] = error.get_error(kNoFund);
						} else {
							accounts[j].balance -= 10;
							results[commands[i].id] = std::to_string(accounts[j].balance);
							// results[commands[i].id] = commands[i].user_name + ' ' + std::to_string(accounts[j].balance);
						}
					} else {
						results[commands[i].id] = error.get_error(kUserNotFound);
					}
					break;
				}
			}
		}
		else if (commands[i].command == "ADD_BANKNOTE") {
			results[commands[i].id] = bank_note.AddBankNote(commands[i].value, commands[i].amount);
		}
	}

	// Prints the results to the console
	for (size_t i = 0; i < results.size(); ++i) {
		std::cout << results[i] << std::endl;
	}

	return EXIT_SUCCESS;
}