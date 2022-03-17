#pragma once
#include<string>
typedef unsigned long long ulong;
using  std::string;
class CardReader
{
private:
	ulong cardCode;
	string lastName;
	string firstName;
	string sex;
	string state;
	//create pointer;
public:
	CardReader(ulong cardCode ,string lastName,string firstName, string sex,string state)
	{
		this->cardCode = cardCode;
		this->lastName = lastName;
		this->firstName = firstName;
		this->sex = sex;
		this->state = state;
	}
	CardReader() 
	{
		cardCode = 0;
	}
	ulong GetCardCode() { return cardCode; }
	string GetLastName() { return lastName; }
	string GetFirstName() { return firstName; }
	string GetSex() { return sex; }
	string GetState() { return state; }
	void SetCardCode(ulong cardCode)
	{
		this->cardCode = cardCode;
	}
	void SetLastName(string lastName)
	{
		this->lastName = lastName;
	}
	void SetFirstName(string firstName)
	{
		this->firstName = firstName;
	}
	void SetSex(string sex)
	{
		this->sex = sex;
	}
	void SetState(string state)
	{
		this->state = state;
	}
};