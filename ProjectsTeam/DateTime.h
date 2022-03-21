#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<time.h>
#include<string>
using namespace std;

class DateTime
{
public:
	bool FormatDate(string& data);
	string Day(string data);
	string Month(string data);
	string Year(string data);
	int IntYear(string data);

	bool CheckDay(string& data);
	bool CheckMonth(string& data);
	bool CheckYear(string& data);
	bool CheckDate(string& data);

	string CurrentDay();
	string CurrentMonth();
	string CurrentYear();
	string CurrentDate();
};




