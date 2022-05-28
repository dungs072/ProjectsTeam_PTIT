#pragma once
#include"DoublyLinkedList.h"
#include"DateTime.h"
using std::string;
using namespace DataStructure;
class BorrowBook
{
private:
	string bookCode;
	DateTime* borrowDate;
	DateTime* returnDate;
	int stateBorrow;
public:
	BorrowBook()
	{
		bookCode = "";
		borrowDate = nullptr;
		returnDate = nullptr;
		stateBorrow = -1;
	}
	BorrowBook(string bookCode, DateTime* borrowDate, DateTime* returnDate, int stateBorrow)
	{
		this->bookCode = bookCode;
		this->borrowDate = borrowDate;
		this->returnDate = returnDate;
		this->stateBorrow = stateBorrow;
	}
	string GetBookCode();
	DateTime* GetBorrowDate();
	DateTime* GetReturnDate();
	int GetStateBorrow();

	void SetBookCode(string bookCode);
	void SetBorrowDate(DateTime* borrowDate);
	void SetReturnDate(DateTime* returnDate);
	void SetStateBorrow(int stateBorrow);
};
class BorrowBookList
{
private:
	DoublyLinkedList<BorrowBook>* borrowBookList = nullptr;
public:
	BorrowBookList()
	{
		borrowBookList = new DoublyLinkedList<BorrowBook>();
	}
	~BorrowBookList()
	{
		borrowBookList->Clear();
		delete borrowBookList;
		borrowBookList = nullptr;
	}
	void AddLast(BorrowBook borrowBook)
	{
		borrowBookList->AddLast(borrowBook);
	}
	DoublyNode<BorrowBook>* Last() { return borrowBookList->Last(); }
	DoublyNode<BorrowBook>* First() { return borrowBookList->First(); }
	int Length()
	{
		return borrowBookList->Length();
	}
	bool Remove(string bookCode)
	{
		DoublyNode<BorrowBook>* tempNode = borrowBookList->First();
		while (tempNode != nullptr)
		{
			if (tempNode->data.GetBookCode() == bookCode&&tempNode->data.GetStateBorrow()==0)
			{
				borrowBookList->Remove(tempNode);
				return true;
			}
			tempNode = tempNode->next;
		}
		return false;
	}
};

