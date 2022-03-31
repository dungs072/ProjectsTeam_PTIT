#pragma once
#include"DoublyLinkedList.h"
#include"DateTime.h"
using std::string;
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

