#pragma once
#include<iostream>
#include<string>
#include"SinglyLinkedList.h"
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
	SinglyLinkedList<Book>* bookList = nullptr;
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
		bookList = new SinglyLinkedList<Book>();
	}
	Title()
	{
		this->ISBN = "";
		this->bookName = "";
		this->pageNumber = 0;
		this->author = "";
		this->publicYear = 0;
		this->type = "";
		bookList = new SinglyLinkedList<Book>();
	}
	//Set field;
	void SetISBN(string isbn);
	void SetBookName(string bookName);
	void SetPageNumber(uint pageNumber);
	void SetAuthor(string author);
	void SetPublicYear(uint publicYear);
	void SetType(string type);
	void SetListBook(SinglyLinkedList<Book>* list)
	{
		bookList = list;
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
	SinglyLinkedList<Book>* GetListBook();
};

