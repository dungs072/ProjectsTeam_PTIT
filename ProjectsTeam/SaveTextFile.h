#pragma once
#include<iostream>
#include<fstream>
#include"CardReader.h"
#include"Title.h"
#include"wx/wx.h"
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
	int lengthList = 0;
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
	~SaveTextFile()
	{
		
	}
	void WriteToFile(T** arr, int length)
	{
		
		ofstream osFile;
		osFile.open(nameFile, ios::out | ios::trunc);
		if (osFile.is_open())
		{
			osFile << length << endl;
			if (length == 0)
			{
				return;
			}
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
					if (p[i]->GetListBorrowBook()->Length() > 0)
					{
						DoublyNode<BorrowBook>* temp = p[i]->GetListBorrowBook()->First();
						while (temp != nullptr)
						{
							string returnDateStr = temp->data.GetReturnDate() == nullptr ? 
											"null" : temp->data.GetReturnDate()->ToString();
							osFile << " -" << temp->data.GetBookCode()
								<< "  " << temp->data.GetBorrowDate()->ToString()
								<< "  " << returnDateStr
								<< "  " <<temp->data.GetStateBorrow() << endl;
							temp = temp->next;
						}
					}
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
					osFile << p[i]->GetType() << "  ";
					osFile << p[i]->GetCountBorrow()<<"\n";
					if (p[i]->GetListBook()->Length() > 0)
					{
						SinglyNode<Book>* temp = p[i]->GetListBook()->First();
						while (temp != nullptr)
						{
							osFile << " -" << temp->data.GetBookCode()
								<< "  " << temp->data.GetState()
								<< "  " << temp->data.GetPos() << endl;
							temp = temp->next;
						}
					}
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
			bool isOneTime = false;
			string myLine = "";
			if (std::is_same<T, CardReader>::value)
			{
				CardReader** p = reinterpret_cast<CardReader**>(arr);
				int mainIndex = 0;
				while (getline(ifFile, myLine))
				{
					if (!isOneTime)
					{
						isOneTime = true;
						continue;
					}
					if (myLine.find(" -") < myLine.length())
					{
						
						string* childText = new string[4];
						int childIndex = 0;
						for (int i = 2; i < myLine.length(); i++)
						{
							if (i + 1 != myLine.length() &&
								myLine[i] == ' ' && myLine[i + 1] == ' ')
							{
								childIndex++;
								i++;
							}
							else
							{
								childText[childIndex] += myLine[i];
							}
						}
						DateTime* borrowDate = new DateTime();
						borrowDate->CastDate(childText[1]);
						DateTime* returnDate = nullptr;
						if (childText[2] != "null")
						{
							returnDate = new DateTime();
							returnDate->CastDate(childText[2]);
						}					
						int state = CastStringToNumber<int>(childText[3]);
						BorrowBook borrowBook(childText[0], borrowDate, returnDate, state);
						p[mainIndex - 1]->GetListBorrowBook()->AddLast(borrowBook);
						delete[] childText;
					}
					else
					{
						string* text = new string[5];
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
						ulong number = CastStringToNumber<ulong>(text[0]);
						p[mainIndex] = new CardReader(number, text[1], text[2], text[3], text[4]);
						mainIndex++;
						delete[] text;
					}
				}
			}
			else if (std::is_same<T, Title>::value)
			{
				Title** p = reinterpret_cast<Title**>(arr);
				int mainIndex = 0;
				
				while (getline(ifFile, myLine))
				{
					if (!isOneTime)
					{
						isOneTime = true;
						continue;
					}

					if (myLine.find(" -") < myLine.length())
					{
						
						string* childText = new string[3];
						int childIndex = 0;
						for (int i = 2; i < myLine.length(); i++)
						{
							if (i + 1 != myLine.length() && 
								myLine[i] == ' ' && myLine[i + 1] == ' ')
							{
								childIndex++;
								i++;
							}
							else
							{
								childText[childIndex] += myLine[i];
							}
						}
						int state = CastStringToNumber<int>(childText[1]);
						Book book(childText[0], state, childText[2]);
						p[mainIndex - 1]->GetListBook()->Add(book);
						delete []childText;
					}
					else
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
						uint countBorrow = CastStringToNumber<uint>(text[6]);
						p[mainIndex] = new Title(text[0], text[1], pageNumber, text[3], nxb, text[5],countBorrow);
						mainIndex++;
						delete[]text;
					}
					
				}
			}

			ifFile.close();
		}
		else
		{
			std::cout << "Error open file" << std::endl;
		}
	}
	unsigned int GetSizeArray()
	{
		ifstream ifFile(nameFile);
		if (ifFile.is_open())
		{
			string myLine = "";
			while (getline(ifFile, myLine))
			{
				lengthList = CastStringToNumber<int>(myLine);
				break;
			}
			ifFile.close();
		}
		return lengthList;
	}
	void ClearData()
	{
		ofstream ofs;
		ofs.open(nameFile, std::ofstream::out | std::ofstream::trunc);
		ofs.close();
	}
};

