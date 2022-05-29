#include "CheckInput.h"
size_t CheckInput::CastStringToNumber(string strText)
{
	int i, j;
	size_t number = 0;
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
bool CheckInput::IsInRangeNumber(int startNumber, int endNumber,int number)
{
	return number >= startNumber && number <= endNumber;
}
bool CheckInput::IsNumber(wxString text)
{
	string strText = string(text.mb_str());
	for (int i = 0; i < strText.length(); i++)
	{
		if (strText[i] < '0' || strText[i]>'9')
		{
			return false;
		}
	}
	return true;
}
bool CheckInput::IsAlphabet(wxString text)
{
	std::string strText = std::string(text.mb_str());
	for (int i = 0; i < strText.length(); i++)
	{
		if (!(strText[i] >= 'a' && strText[i] <= 'z'))
		{
			if (!(strText[i] >= 'A' && strText[i] <= 'Z'))
			{
					return false;
			}
		}
	}
	return true;
}
bool CheckInput::IsWhiteSpaceAllText(wxString text)
{
	std::string strText = std::string(text.mb_str());
	if (strText == "") { return true; }
	for (char str : strText)
	{
		if (str != ' ')
		{
			return false;
		}
	}
	return true;
}
bool CheckInput::HasNumberAlphabetAndComma(wxString text)
{
	std::string strText = std::string(text.mb_str());
	for (int i = 0; i < strText.length(); i++)
	{
		if ((strText[i] >= 'A' && strText[i] <= 'Z') ||
			(strText[i] >= 'a' && strText[i] <= 'z') ||
			(strText[i] >= '0' && strText[i] <= '9') ||
			(strText[i]==',')||
			(strText[i] == ' '))
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}
bool CheckInput::HasNumberAndAlphabet(wxString text)
{
	std::string strText = std::string(text.mb_str());
	for (int i = 0; i < strText.length(); i++)
	{
		if ((strText[i] >= 'A' && strText[i] <= 'Z') ||
			(strText[i] >= 'a' && strText[i] <= 'z') ||
			(strText[i] >= '0' && strText[i] <= '9') ||
			(strText[i]==' '))
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}
bool CheckInput::IsWord(wxString text)
{
	std::string strText = std::string(text.mb_str());
	for (int i = 0; i < strText.length(); i++)
	{
		if (!(strText[i] >= 'a' && strText[i] <= 'z'))
		{
			if (!(strText[i] >= 'A' && strText[i] <= 'Z'))
			{
				if (strText[i] != ' ')
					return false;
			}
		}
	}
	return true;
}
bool CheckInput::IsRightSex(wxString text)
{
	std::string strText = std::string(text.mb_str());
	strText = UpperText(strText);
	if (strText == "") { return false; }
	ModifyString(strText);
	wxString myWxString(strText.c_str(), wxConvUTF8);
	if (strText == "NAM" || strText == "NU")
	{
		text = myWxString;
		return true;
	}
	return false;
}
bool CheckInput::IsRightCodeState(int maxNumber, int currentNumber)
{
	return currentNumber >= 0 && currentNumber <= maxNumber;
}

void CheckInput::ModifyTextInput(wxString& text)
{
	if (text == "") { return; }
	std::string strText = std::string(text.mb_str());
	ModifyString(strText);
	wxString myWxString(strText.c_str(), wxConvUTF8);
	text = myWxString;
}
void CheckInput::ModifyString(string& strText)
{
	for (int i = 0; i < strText.length(); i++)
	{
		if (strText[i] == ' ' && strText[i + 1] == ' ')
		{
			strText.erase(strText.begin() + i);
			i--;
		}
	}
	if (strText[0] == ' ')
	{
		strText.erase(strText.begin());
	}
	int length = strText.length();
	if (length == 0)
	{
		return;
	}
	if (strText[length - 1] == ' ')
	{
		strText.erase(strText.begin() + length - 1);
	}
}
void CheckInput::UpperWxString(wxString& text)
{
	std::string strText = std::string(text.mb_str());
	strText = UpperText(strText);
	wxString myWxString(strText.c_str(), wxConvUTF8);
	text = myWxString;
}
string CheckInput::UpperText(string text)
{
	for (int i = 0; i < text.length(); i++)
	{
		if ((text[i] >= 'Z' && text[i] <= 'A'))
		{
			return "";
		}
		if (text[i] <= 'z' && text[i] >= 'a')
		{
			text[i] -= 32;
		}
	}
	return text;
}
string CheckInput::CastIntToString(int data)
{
	string strTemp = "";
	while (data) {
		int temp = data % 10;
		strTemp += temp + '0';
		data /= 10;
	}
	string str = "";
	int i;
	for (i = strTemp.length() - 1; i >= 0; i--)
	{
		str += strTemp[i];
	}
	if (str == "")
	{
		str = "0";
	}
	return str;
}
int CheckInput::CastWxStringToInt(wxString text)
{
	int i, j;
	int number = 0;
	string strText = string(text.mb_str());
	if (!IsNumber(text)) { return -1; }
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
void CheckInput::ErrorMessageBox(string message)
{
	wxString myWxString(message.c_str(), wxConvUTF8);
	wxMessageBox(myWxString);
}
void CheckInput::SetTextSize(wxStaticText* text, int size)
{
	wxFont tempFont = text->GetFont();
	tempFont.SetPointSize(size);
	text->SetFont(tempFont);
}
void CheckInput::MoveDownToAnotherTextCtrl(wxTextCtrl** textCtrl, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (textCtrl[i]->HasFocus())
		{
			if (i < length - 1)
			{
				textCtrl[i + 1]->SetFocus();
				return;
			}
			else if (i == length - 1)
			{
				textCtrl[0]->SetFocus();
				return;
			}

		}
	}
}
void CheckInput::MoveUpToAnotherTextCtrl(wxTextCtrl** textCtrl, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (textCtrl[i]->HasFocus())
		{
			if (i > 0)
			{
				textCtrl[i - 1]->SetFocus();
				return;
			}
			else if (i == 0)
			{
				textCtrl[length - 1]->SetFocus();
				return;
			}
		}
	}
}
void CheckInput::ClearInforInEnterText(wxTextCtrl** enterText,int length)
{
	for (int i = 0; i < length; i++)
	{
		enterText[i]->Clear();
	}
}
string CheckInput::EditCardCode(ulong number, int maxLengthCode)
{
	std::string codeReader = "";
	std::string rawCodeReader = "";
	int lengthNumber = 0;
	while (number != 0)
	{
		int tempNumber = number;
		for (int i = 0; i < 10; i++)
		{
			tempNumber -= i;
			if (tempNumber % 10 == 0)
			{
				lengthNumber++;
				number -= i;
				number /= 10;
				rawCodeReader += (i + '0');
			}
			tempNumber = number;
		}
	}
	//reverse string
	std::reverse(rawCodeReader.begin(), rawCodeReader.end());
	for (int i = 0; i < maxLengthCode - lengthNumber; i++)
	{
		codeReader += "0";
	}
	codeReader += rawCodeReader;
	return codeReader;
}
