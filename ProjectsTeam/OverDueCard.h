#pragma once
#include"CardReader.h"
class OverDueCard
{
private:
	CardReader* cardReader = nullptr;
	int numberDayOverDue = -1;
public:
	~OverDueCard()
	{
		/*if (cardReader != nullptr)
		{
			delete cardReader;
		}*/
	}
	OverDueCard() {}
	OverDueCard(CardReader* cardReader, int numberDayOverDue)
	{
		this->cardReader = cardReader;
		this->numberDayOverDue = numberDayOverDue;
	}
	CardReader* GetCardReader()
	{
		return cardReader;
	}
	int GetNumberDayOverDue()
	{
		return numberDayOverDue;
	}
};

