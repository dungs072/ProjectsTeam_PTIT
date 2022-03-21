#pragma once
#include<iostream>
#include<fstream>
#include"CardReader.h"
#include"Title.h"

typedef unsigned long long ulong;
using std::string;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;
template<class T>
class SaveTextFile
{
private:
	string nameFile = "";
private:
	template<typename data_type>
	data_type CastStringToNumber(string strText)
	{
		int i, j;
		data_type number = 0;
		for (i = strText.length() - 1, j = 0; i >= 0; i--, j++)
		{
			if (strText[i] < '0' || strText[i]>'9')
			{
				return -1;
			}
			number += (strText[i] - '0') * pow(10, j);
		}
		return number;
	}
public:

	SaveTextFile(string nameFile)
	{
		this->nameFile = nameFile;
		nameFile += ".txt";
	}
	void WriteToFile(T** arr, int length)
	{
		ofstream osFile;
		osFile.open(nameFile,ios::out|ios::trunc);
		if (osFile.is_open())
		{
			if (std::is_same<T, CardReader>::value)
			{
				CardReader** p = reinterpret_cast<CardReader**>(arr);
				for (int i = 0; i < length; i++)
				{
					osFile << p[i]->GetCardCode() << "  ";
					osFile << p[i]->GetFirstName() << "  ";
					osFile << p[i]->GetLastName() << "  ";
					osFile << p[i]->GetSex() << "  ";
					osFile << p[i]->GetState() << "\n";
				}
			}
			else if (std::is_same<T, Title>::value)
			{
				Title** p = reinterpret_cast<Title**>(arr);
				for (int i = 0; i < length; i++)
				{
					osFile << p[i]->GetISBN() << "  ";
					osFile << p[i]->GetBookName() << "  ";
					osFile << p[i]->GetPageNumber() << "  ";
					osFile << p[i]->GetAuthor() << "  ";
					osFile << p[i]->GetPublicYear() << "  ";
					osFile << p[i]->GetType() << "\n";
				}
			}
			osFile.close();
		}
		else
		{
			std::cout << "error open file" << std::endl;
		}
		

	}
	void ReadFile(T** arr)
	{
		ifstream ifFile(nameFile);
		if (ifFile.is_open())
		{
			string myLine = "";
			if (std::is_same<T, CardReader>::value)
			{
				CardReader** p = reinterpret_cast<CardReader**>(arr);
				int mainIndex = 0;
				while (getline(ifFile, myLine))
				{
					//std::cout << myLine << std::endl;
					string* text = new string[7];
					int index = 0;
					for (int i = 0; i < myLine.length(); i++)
					{
						if (i + 1 != myLine.length()&&myLine[i] == ' ' && myLine[i + 1] == ' ')
						{
							index++;
							i++;
						}
						else
						{
							text[index] += myLine[i];
						}
					}
					ulong number = CastStringToNumber<ulong>(text[0]);
					p[mainIndex] = new CardReader(number, text[1], text[2], text[3], text[4]);
					mainIndex++;
					delete text;
				}
			}
			else if (std::is_same<T, Title>::value)
			{
				Title** p = reinterpret_cast<Title**>(arr);
				int mainIndex = 0;
				while (getline(ifFile, myLine))
				{
					//std::cout << myLine << std::endl;
					string* text = new string[7];
					int index = 0;
					for (int i = 0; i < myLine.length(); i++)
					{
						if (i + 1 != myLine.length() && myLine[i] == ' ' && myLine[i + 1] == ' ')
						{
							index++;
							i++;
						}
						else
						{
							text[index] += myLine[i];
						}
					}
					uint pageNumber = CastStringToNumber<uint>(text[2]);
					uint nxb = CastStringToNumber<uint>(text[4]);
					p[mainIndex] = new Title(text[0], text[1], pageNumber, text[3], nxb,text[5]);
					mainIndex++;
				}
			}
	
			ifFile.close();
		}
		else
		{
			std::cout << "Error open file" << std::endl;
		}
	}
	unsigned int GetLineCount()
	{
		ifstream myfile(nameFile);
		myfile.unsetf(std::ios_base::skipws);

		// count the newlines with an algorithm specialized for counting:
		unsigned int line_count = std::count(
			std::istream_iterator<char>(myfile),
			std::istream_iterator<char>(),
			'\n');
		return line_count;
	}
};

