#pragma once
#include<iostream>
#include<string>
using std::string;
typedef unsigned int uint;
class Title
{
private:
	string ISBN;
	string bookName;
	uint pageNumber;
	string author;
	uint publicYear;
	string type;
	//con tro nua;
public:
	Title(string ISBN, string bookName, uint pageNumber,
		string author, uint publicYear, string type)
	{
		this->ISBN = ISBN;
		this->bookName = bookName;
		this->pageNumber = pageNumber;
		this->author = author;
		this->publicYear = publicYear;
		this->type = type;
	}
	Title(){}
	//Set field;
	void SetISBN(string isbn);
	void SetBookName(string bookName);
	void SetPageNumber(uint pageNumber);
	void SetAuthor(string author);
	void SetPublicYear(uint publicYear);
	void SetType(string type);

	//Get field;
	string GetISBN();
	string GetBookName();
	uint GetPageNumber();
	string GetAuthor();
	uint GetPublicYear();
	string GetType();
};

