#include "FormatText.h"
#include<string>
using namespace std;
bool FormatText::IsEmpty(string data) {
	if (data == "") { return true; }
	while (data[0] == ' ' || data[0] == '\t') {
		data.erase(0, 1);
	}
	return data == "";
}
bool FormatText::HasNumber(string data) {
	int len = data.length();
	for (int i = 0; i < len; i++) {
		if (data[i] >= '0' && data[i] <= '9') {
			return true;
		}
	}
	return false;
}
bool FormatText::DifferentCharacter(string data)
{
	int len = data.length();
	for (int i = 0; i < len; i++)
	{
		if (!((data[i] >= 'a' && data[i] <= 'z') || (data[i] >= 'A' && data[i] <= 'Z')))
		{
			if (data[i] != ' ' || data[i] != '\t')
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}
void FormatText::FormatString(string& data)
{
	//chuoi rong
	if (data == "")return;

	// viet hoa tat ca ki tu trong mang
	int len = data.length();
	for (int i = 0; i < len; i++) {
		data[i] = toupper(data[i]);
		//truong hop sai dau space bang tab. vd: ho\tnhan
		if (data[i] == '\t') {
			data[i] = ' ';
		}
	}

	//xoa ki tu sai khac dau tien
	while (!(data[0] >= 'A' && data[0] <= 'Z'))
	{
		//truong hop rong. vd: " ."
		if (data == "")return;
		data.erase(0, 1);
	}

	//xoa ki tu sai khac cuoi cung
	while (!(data[data.length() - 1] >= 'A' && data[data.length() - 1] <= 'Z')) {
		data.erase(data.length() - 1, 1);
	}
	if (data.length() <= 1)return;

	//xoa ki tu khac, so, tab, khoang trang thua,... trong chuoi
	for (int i = 0; i < data.length() - 1;) {
		if (!((data[i] >= 'a' && data[i] <= 'z') || (data[i] >= 'A' && data[i] <= 'Z')))
		{
			if (data[i] != ' ') {
				data.erase(i, 1);
			}
			else if (data[i + 1] == ' ') {
				data.erase(i, 1);
			}
			else {
				i++;
			}
		}
		else {
			i++;
		}
	}
}
string FormatText::CastIntToString(int data) {
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
		str+= strTemp[i];
	}
	return str;
}