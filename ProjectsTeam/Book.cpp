#include"Book.h"
string Book::GetBookCode()
{
	return bookCode;
}
int Book::GetState()
{
	return state;
}
string Book::GetPos()
{
	return pos;
}
void Book:: SetBookCode(string bookCode)
{
	this->bookCode = bookCode;
}
void Book::SetState(int state)
{
	this->state = state;
}
void Book::SetPos(string pos)
{
	this->pos = pos;
}