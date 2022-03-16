#pragma once
#include<string>
class CardReader
{
private:
	long long cardCode;
	std::string lastName;
	std::string firstName;
	std::string sex;
	//create pointer;
public:
	CardReader(long long cardCode , std::string lastName, std::string firstName, std::string sex)
	{
		this->cardCode = cardCode;
		this->lastName = lastName;
		this->firstName = firstName;
		this->sex = sex;
	}
	CardReader() 
	{
		cardCode = 0;
	}
	long long GetCardCode() { return cardCode; }
	std::string GetLastName() { return lastName; }
	std::string GetFirstName() { return firstName; }
	std::string GetSex() { return sex; }

	void SetCardCode(long long cardCode)
	{
		this->cardCode = cardCode;
	}
	void SetLastName(std::string lastName)
	{
		this->lastName = lastName;
	}
	void SetFirstName(std::string firstName)
	{
		this->firstName = firstName;
	}
	void SetSex(std::string sex)
	{
		this->sex = sex;
	}
};