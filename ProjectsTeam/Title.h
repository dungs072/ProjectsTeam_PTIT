#pragma once
#include<iostream>
#include<string>
#include"LinearList.h"
#include"Book.h"
using namespace DataStructure;
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
	BookList* bookList = nullptr;
	uint countBorrow;
public:
	Title(string ISBN, string bookName, uint pageNumber,
		string author, uint publicYear, string type,int count)
	{
		this->ISBN = ISBN;
		this->bookName = bookName;
		this->pageNumber = pageNumber;
		this->author = author;
		this->publicYear = publicYear;
		this->type = type;
		bookList = new BookList();
		this->countBorrow = count;
	}
	Title()
	{
		this->ISBN = "";
		this->bookName = "";
		this->pageNumber = 0;
		this->author = "";
		this->publicYear = 0;
		this->type = "";
		bookList = new BookList();
		this->countBorrow = 0;
	}
	~Title()
	{
		//delete bookList;
	}
	//Set field;
	void SetISBN(string isbn);
	void SetBookName(string bookName);
	void SetPageNumber(uint pageNumber);
	void SetAuthor(string author);
	void SetPublicYear(uint publicYear);
	void SetType(string type);
	void SetListBook(BookList* list)
	{
		if (bookList != nullptr)
		{
			delete bookList;
			bookList = nullptr;
		}
		bookList = list;
	}
	void SetCountBorrow(uint countBorrow)
	{
		this->countBorrow = countBorrow;
	}
	void Display()
	{
		std::cout << "ISBN: " << ISBN << std::endl;
		std::cout << "book name: " << bookName << std::endl;
		std::cout << "pageNumber: " << pageNumber << std::endl;
		std::cout << "author: " << author << std::endl;
		std::cout << "publicYear: " << publicYear << std::endl;
		std::cout << "Type: " << type << std::endl;
	}
	//Get field;
	string GetISBN();
	string GetBookName();
	uint GetPageNumber();
	string GetAuthor();
	uint GetPublicYear();
	string GetType();
	BookList* GetListBook();
	uint GetCountBorrow();
	bool HasBorrowBook()
	{
		SinglyNode<Book>* tempBook = bookList->First();
		while (tempBook != nullptr)
		{
			if (tempBook->data.GetState() == 1)
			{
				return true;
			}
			tempBook = tempBook->next;
		}
		return false;
	}
};
class TitleList
{
private:
	LinearList<Title>* listTitle = nullptr;
public:
	TitleList(int maxLength)
	{
		listTitle = new LinearList<Title>(maxLength);
	}
	~TitleList()
	{
		listTitle->~LinearList();
	}
	LinearList<Title>* GetList()
	{
		return listTitle;
	}
	bool HasInList(string ISBN, int& pos)
	{
		for (int i = 0; i < listTitle->Length(); i++)
		{
			if (listTitle->GetData(i)->GetISBN() == ISBN)
			{
				pos = i;
				return true;
			}
		}
		pos = -1;
		return false;
	}
	void Delete(string ISBN)
	{
		int pos = 0;
		if (!HasInList(ISBN, pos)) { return; }
		if (pos == -1) { return; }
		listTitle->Delete(pos);
	}
	Title* GetData(string ISBN)
	{
		int pos = -1;
		if (!HasInList(ISBN, pos)) { return nullptr; }
		if (pos == -1) { return nullptr; }
		return listTitle->GetData(pos);
	}
};

