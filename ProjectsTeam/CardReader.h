#pragma once
#include<iostream>
#include<string>
#include"BSTree.h"
#include"BorrowBook.h"
typedef unsigned long long ulong;
using  std::string;
using std::cout;
using std::endl;
//more efficiency you have to create abstract class to have key code
//for every class must have to use BST Tree
class CardReader 
{
private:
	ulong cardCode;
	string lastName;
	string firstName;
	string sex;
	string state;
	BorrowBookList* listBorrowBook = nullptr;
public:
	CardReader(ulong cardCode ,string firstName,string lastName, string sex,string state)
	{
		this->cardCode = cardCode;
		this->lastName = lastName;
		this->firstName = firstName;
		this->sex = sex;
		this->state = state;
		listBorrowBook = new BorrowBookList();
	}
	CardReader() 
	{
		cardCode = 0;
		lastName = "";
		firstName = "";
		sex = "";
		state = "";
		listBorrowBook = new BorrowBookList();
	}
	~CardReader()
	{
		//delete listBorrowBook;
	}
	ulong GetCardCode() { return cardCode; }
	string GetLastName() { return lastName; }
	string GetFirstName() { return firstName; }
	string GetSex() { return sex; }
	string GetState() { return state; }
	BorrowBookList* GetListBorrowBook() { return listBorrowBook; }
	
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
	void SetListBorrowBook(BorrowBookList* list)
	{
		if (listBorrowBook != nullptr)
		{
			delete listBorrowBook;

		}
		listBorrowBook = list;
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
