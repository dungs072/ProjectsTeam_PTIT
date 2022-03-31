#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<ctime>
using namespace std;

class DateTime
{
private:
	time_t now = time(0);
	tm* currentDate = localtime(&now);
	int day = 0;
	int month = 0;
	int year = 0;
	string CastNumberToString(int number, int length);
	int CastStringToNumber(string numStr);
	string Format(int day, int month, int year);
	int CompareDates(string date1, string date2);

public:
	DateTime(){}
	DateTime(int day, int month, int year);
	
	string ToString();
	
	int CompareDate(string date);
	
	bool IsGreaterThanNow();
	/*bool FormatDate(string& data);
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
	string CurrentDate();*/
	void CastDate(string dateStr);
	void SetNow();
	int GetCurrentYear();
	int GetCurrentMonth();
	int GetCurrentDay();
	int GetDay();
	int GetMonth();
	int GetYear();
};




