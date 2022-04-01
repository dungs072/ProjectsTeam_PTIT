#pragma once
#include<wx/wx.h>
#include<iostream>
#include<ctime>
using std::to_string;
using std::string;
class ControlDateTime
{
private:
	string* day;	
	string* month;
	string* year;
	time_t now = time(0);
	tm* ltm = localtime(&now);
public:

	ControlDateTime();
	string* GetDay()
	{
		return day;
	}
	string* GetMonth()
	{
		return month;
	}
	string* GetYear()
	{
		return year;
	}
	int GetCurrenDay()
	{
		return ltm->tm_mday;
	}
	int GetCurrentMonth()
	{
		return ltm->tm_mon + 1;
	}
	int GetCurrentYear()
	{
		return ltm->tm_year + 1900;
	}
	bool IsLeapYear(int year)
	{
		return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
	}
};

