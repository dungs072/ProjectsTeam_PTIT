#include "BorrowBook.h"
string BorrowBook::GetBookCode()
{
	return bookCode;
}
DateTime* BorrowBook::GetBorrowDate()
{
	return borrowDate;
}
DateTime* BorrowBook::GetReturnDate()
{
	return returnDate;
}
int BorrowBook::GetStateBorrow()
{
	return stateBorrow;
}
void BorrowBook::SetBookCode(string bookCode)
{
	this->bookCode = bookCode;
}
void BorrowBook::SetBorrowDate(DateTime* borrowDate)
{
	this->borrowDate = borrowDate;
}
void BorrowBook::SetReturnDate(DateTime* returnDate)
{
	this->returnDate = returnDate;
}
void BorrowBook::SetStateBorrow(int stateBorrow)
{
	this->stateBorrow = stateBorrow;
}
