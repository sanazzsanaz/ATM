#pragma once
#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include "pch.h"

class TimeStamp
{
public:
	static bool Compare(TimeStamp& time1, TimeStamp& time2);

	void AddAnHour();

	void Print();

	TimeStamp() = default;
	TimeStamp(std::string &time);

private:
	int _year;
	int _month;
	int _day;
	int _hour;
	int _minute;
	int _second;
};

#endif // !TIMESTAMP_H