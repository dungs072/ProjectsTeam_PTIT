#pragma
#include<iostream>
#include<string>
#include"SinglyLinkedList.h"
using namespace DataStructure;
using std::string;
class Book
{
private:
	string bookCode;
	int state = 0;
	string pos;
public:
	Book() {};
	Book(string bookCode, int state, string pos) {
		this->bookCode = bookCode;
		this->state = state;
		this->pos = pos;
	};
	string GetBookCode();
	int GetState();
	string GetPos();

	void SetBookCode(string code);
	void SetState(int state);
	void SetPos(string pos);

};
class BookList
{
private:
	SinglyLinkedList<Book>* listBook = nullptr;
public:
	BookList()
	{
		listBook = new SinglyLinkedList<Book>();
	}
	~BookList()
	{
		listBook->Clear();
	}
	void Add(Book book)
	{
		listBook->Add(book);
	}
	void Remove(string code)
	{

		if (listBook->First() == nullptr) { return; }
		SinglyNode<Book>* prev = nullptr;
		SinglyNode<Book>* p = listBook->First();
		while (p != nullptr)
		{
			if (p->data.GetBookCode() == code)
			{
				listBook->Remove(prev, p);
				break;
			}
			prev = p;
			p = p->next;
		}
		
	}
	SinglyNode<Book>* FindSinglyNode(string code)
		{
			if (listBook->First() == nullptr) { return nullptr; }
			SinglyNode<Book>* p = listBook->First();
			while (p != nullptr)
			{
				if (p->data.GetBookCode() == code)
				{
					return p;
				}
				p = p->next;
			}
			return nullptr;
		}
	SinglyNode<Book>* First()
	{
		return listBook->First();
	}
	int Length()
	{
		return listBook->Length();
	}
	SinglyLinkedList<Book>* GetList()
	{
		return listBook;
	}
	void Clear()
	{
		listBook->Clear();
	}
};