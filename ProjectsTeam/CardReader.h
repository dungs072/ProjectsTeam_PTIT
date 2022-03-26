#pragma once
#include<iostream>
#include<string>
#include"SinglyLinkedList.h"
typedef unsigned long long ulong;
using namespace DataStructure;
using  std::string;
using std::cout;
using std::endl;
class CardReader
{
private:
	ulong cardCode;
	string lastName;
	string firstName;
	string sex;
	string state;
	
public:
	CardReader(ulong cardCode ,string firstName,string lastName, string sex,string state)
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
		lastName = "";
		firstName = "";
		sex = "";
		state = "";
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
	void DisplayCardReader()
	{
		cout << "card code: " << cardCode << endl;
		cout << "first name: " << firstName << endl;
		cout << "Last name: " << lastName << endl;
		cout << "Sex: " <<sex << endl;
		cout << "state " << state << endl;
		cout << endl;
	}
};