#pragma once
#include<wx/wx.h>
#include<iostream>
using std::string;
class CheckInput
{
public:
	bool IsNumber(wxString text);
	bool IsAlphabet(wxString text);
	bool IsWhiteSpaceAllText(wxString text);
	bool IsWord(wxString text);
	bool IsRightSex(wxString text);
	bool IsRightCodeState(int maxNumber, int currentNumber);
	void ModifyTextInput(wxString& text);
	void ModifyString(string& str);
	void UpperWxString(wxString& text);
	string UpperText(string str);
	int CastWxStringToInt(wxString text);
	void ErrorMessageBox(string message);
	void SetTextSize(wxStaticText* text, int size);
	void MoveDownToAnotherTextCtrl(wxTextCtrl** textCtrl, int length);
	void MoveUpToAnotherTextCtrl(wxTextCtrl** textCtrl, int length);
};

