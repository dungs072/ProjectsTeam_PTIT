#pragma once
#include<string>
using std::string;
class DateTime
{
public:
	bool CheckDay(string& data);
	bool CheckMonth(string& data);
	bool CheckYear(string& data);
	string ToDay();
	void FormatDate(string& data);
};

