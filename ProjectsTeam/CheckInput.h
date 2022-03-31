#pragma once
#include<wx/wx.h>
#include<iostream>
#include"DateTime.h"
using std::string;
typedef unsigned long long ulong;
class CheckInput
{
	string* cardState = new string[2]{ "KHOA","HOAT DONG" };
	string* stateBook = new string[3]{ "CHO MUON DUOC","DA CO DOC GIA MUON","DA THANH LY" };
public:
	bool IsInRangeNumber(int startNumber, int endNumber,int number);
	bool IsNumber(wxString text);
	bool IsAlphabet(wxString text);
	bool IsWhiteSpaceAllText(wxString text);
	bool IsWord(wxString text);
	bool HasNumberAlphabetAndComma(wxString text);
	bool HasNumberAndAlphabet(wxString text);
	bool IsRightSex(wxString text);
	bool IsRightCodeState(int maxNumber, int currentNumber);
	void ModifyTextInput(wxString& text);
	void ModifyString(string& str);
	void UpperWxString(wxString& text);
	string UpperText(string str);
	string CastIntToString(int data);
	int CastStringToNumber(string text);
	int CastWxStringToInt(wxString text); 
	void ErrorMessageBox(string message);
	void SetTextSize(wxStaticText* text, int size);
	void MoveDownToAnotherTextCtrl(wxTextCtrl** textCtrl, int length);
	void MoveUpToAnotherTextCtrl(wxTextCtrl** textCtrl, int length);
	void ClearInforInEnterText(wxTextCtrl** enterText, int length);

	template<typename T>
	void DeleteObject(T** arr, int length)
	{
		for (int i = 0; i < length; i++)
		{
			delete arr[i];
		}
		delete []arr;
	}
	template<typename T>
	T ToNumber(wxString strText)
	{
		int i, j;
		T number = 0;
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
	string GetCardState(int index)
	{
		if (index < 0 || index>1) { return""; }
		return cardState[index];
	}
	string GetBookState(int index)
	{
		if (index < 0 || index>2) { return""; }
		return stateBook[index];
	}
};

