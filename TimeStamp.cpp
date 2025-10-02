#include "TimeStamp.h"

bool TimeStamp::Compare(TimeStamp& time1, TimeStamp& time2)
{
	if (time1._year == time2._year) {
		if (time1._month == time2._month) {
			if (time1._day == time2._day) {
				if (time1._hour == time2._hour) {
					if (time1._minute == time2._minute) {
						return (time1._second < time2._second);
					} else {
						return (time1._minute < time2._minute);
					}
				} else {
					return (time1._hour < time2._hour);
				}
			} else {
				return (time1._day < time2._day);
			}
		} else {
			return (time1._month < time2._month);
		}
	}
	else {
		return (time1._year < time2._year);
	}
}

void TimeStamp::AddAnHour()
{
	++_hour;
	if (_hour > 23) {
		_hour -= 24;
		++_day;
		if (_day > 30) {
			_day -= 30;
			++_month;
			if (_month > 12) {
				_month -= 12;
				++_year;
			}
		}
	}
}

void TimeStamp::Print()
{
	std::cout << _year << "/" << _month << "/" << _day << "-" << _hour << ":" << _minute << ":" << _second << std::endl;
}

TimeStamp::TimeStamp(std::string &time)
{
	_year = std::stoi(time.substr(0, 4));
	_month = std::stoi(time.substr(5, 8));
	_day = std::stoi(time.substr(8, 11));
	_hour = std::stoi(time.substr(11, 14));
	_minute = std::stoi(time.substr(14, 17));
	_second = std::stoi(time.substr(17));
}
