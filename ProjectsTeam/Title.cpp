#include "Title.h"
void Title::SetISBN(string isbn)
{
	this->ISBN = isbn;
}
void Title::SetBookName(string bookName)
{
	this->bookName = bookName;
}
void Title::SetAuthor(string author)
{
	this->author = author;
}
void Title::SetPageNumber(uint pageNumber)
{
	this->pageNumber = pageNumber;
}
void Title::SetPublicYear(uint publicYear)
{
	this->publicYear = publicYear;
}
void Title::SetType(string type)
{
	this->type = type;
}
string Title::GetISBN() { return ISBN; }
string Title::GetBookName() { return bookName; }
uint Title::GetPageNumber() { return pageNumber; }
string Title::GetAuthor() { return author; }
uint Title::GetPublicYear() { return publicYear; }
string Title::GetType() { return type; }
BookList* Title:: GetListBook() { return bookList; }
uint Title::GetCountBorrow() { return countBorrow; }
