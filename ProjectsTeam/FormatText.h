#pragma once
#include<string>
using namespace std;
class FormatText
{
public:
	bool IsEmpty(string data);
	bool HasNumber(string data);
	bool DifferentCharacter(string data);
	void FormatString(string& data);
	string CastIntToString(int data);
};
