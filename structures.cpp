#include "structures.h"

// bool CompareCommands(Commands command1, Commands command2)
// {
//     return TimeStamp::Compare(command1.time, command2.time);
// }

Account::Account(std::string& name)
{
    this->name = name;
}
