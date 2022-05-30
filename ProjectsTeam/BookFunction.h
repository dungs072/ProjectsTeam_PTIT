#pragma once
#include"Title.h"
#include<wx/wx.h>
using namespace std;
class BookFunction
{
public:
	bool CheckDuplicateBookName(std::string text,TitleList* titleList,int length)
	{
		for (int i = 0; i < length; i++)
		{
			Title* title = titleList->GetList()->GetData(i);
			if (title->	GetBookName() == text)
			{
				return true;
			}
		}
		return false;
	}
};

