#pragma
#include<iostream>
#include<string>
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