#include "Datetime.h"
using namespace std;
DateTime::DateTime(int day,int month,int year)
{

	this->day = day;
	this->month = month;
	this->year = year;
}
bool DateTime::IsGreaterThanNow() //=>ERROR 30/11/2022
{
	string inputDate = Format(day, month, year);
	string nowDate = Format(GetCurrentDay(), GetCurrentMonth(), GetCurrentYear());
	if (CompareDates(inputDate, nowDate) == 1)
	{
		return true;
	}
	return false;
}
int DateTime::GetCurrentDay() { return currentDate->tm_mday; }
int DateTime::GetCurrentMonth() { return currentDate->tm_mon+1; }
int DateTime::GetCurrentYear() { return currentDate->tm_year + 1900; }
int DateTime::CompareDate(string date)
{
	string selfDate = this->ToString();
	reverse(selfDate.begin(), selfDate.end());
	reverse(date.begin(), date.end());
	if (selfDate > date) { return 1; }
	else if (selfDate < date) { return -1; }
	else { return 0; }
}
int DateTime::CompareDates(string date1, string date2)  //ERROR 30/11/2022
{
	reverse(date1.begin(), date1.end());
	reverse(date2.begin(), date2.end());
	if (date1 > date2) { return 1; }
	else if (date1 < date2) { return -1; }
	else return 0;
}
int DateTime::CastStringToNumber(string numStr)
{
	int i, j;
	int number = 0;
	for (i = numStr.length() - 1, j = 0; i >= 0; i--, j++)
	{
		if (numStr[i] < '0' || numStr[i]>'9')
		{
			return -1;
		}
		number += (numStr[i] - '0') * pow(10, j);
	}
	return number;
}
string DateTime:: ToString()
{
	return Format(this->day, this->month, this->year);
}
string DateTime::Format(int day, int month, int year)
{
	return CastNumberToString(day, 2) + "/" +
		CastNumberToString(month, 2) + "/" +
		CastNumberToString(year, 4);
}
string DateTime::CastNumberToString(int number,int length)
{
	string strTemp = "";
	while (number) {
		int temp = number % 10;
		strTemp += temp + '0';
		number /= 10;
	}
	string str = "";
	int i;
	for (i = strTemp.length() - 1; i >= 0; i--)
	{
		str += strTemp[i];
	}
	strTemp = "";
	for (int i = str.length(); i < length; i++)
	{
		strTemp += '0';
	}
	return strTemp+str;
}
void DateTime::SetNow()
{
	day = GetCurrentDay();
	month = GetCurrentMonth();
	year = GetCurrentYear();
}
void DateTime::CastDate(string date)
{
	//cannot cast date
	if (date.length() != 10) { return; }
	string dayStr,monthStr,yearStr;
	for (int i = 0; i < 2; i++)
	{
		dayStr += date[i];
	}
	for (int i = 3; i < 5; i++)
	{
		monthStr += date[i];
	}
	for (int i = 6; i < 10; i++)
	{
		yearStr += date[i];
	}
	day = CastStringToNumber(dayStr);
	month = CastStringToNumber(monthStr);
	year = CastStringToNumber(yearStr);
}
int DateTime::GetDay() { return day; }
int DateTime::GetMonth() { return month; }
int DateTime::GetYear() { return year; }


bool LeapYear(int year) {
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}
int SoNgayCuaThang(int month, int year)
{
	if (LeapYear(year) && month == 2)
		return 29;
	int monthTable[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	return monthTable[month];
}
int SoNgayTrongNam(const int day, const int month, const int year)
{
	int d = day;
	int t = month;
	while (t > 1)
	{
		d += SoNgayCuaThang(t - 1, year);
		--t;
	}
	return d;
}

int DateTime::operator -(DateTime& D) {
	int res;
	int temp1 = SoNgayTrongNam(day, month, year);
	int temp2 = SoNgayTrongNam(D.day, D.month, D.year);
	if (year == D.year)
	{
		return temp1 - temp2 + 1;
	}
	else
	{
		int tempYear = year;
		res = temp1;
		while (tempYear != D.year) {
			tempYear--;
			if (LeapYear(tempYear)) {
				res += 366;
			}
			else {
				res += 365;
			}
		}
		res -= temp2 + 1;
	}
	return res;
}



//bool DateTime::FormatDate(string& data) {
//	size_t len = data.length();
//	if (len < 10) {	
//		//cout << "Nhap sai cu phap" << endl;
//		return false;
//	}
//	for (int i = 0; i < len; i++) {
//		if (i == 2 || i == 5) {
//			if (data[i] != '/') {
//				//cout << "Nhap sai cu phap" << endl;
//				return false;
//			}
//			continue;
//		}
//		if (!(data[i] >= '0' && data[i] <= '9')) {
//			//cout << "Nhap sai cu phap" << endl;
//			return false;
//		}
//	}
//	return true;
//}
//
//string DateTime::Day(string data) {
//	string temp = "";
//	temp = temp + data[0] + data[1];
//	return temp;
//}
//string DateTime::Month(string data) {
//	string temp = "";
//	temp = temp + data[3] + data[4];
//	return temp;
//}
//string DateTime::Year(string data) {
//	string year = "";
//	size_t i = data.length() - 1;
//	while (data[i] != '/') {
//		year = data[i] + year;
//		i--;
//	}
//	return year;
//}
//int DateTime::IntYear(string data) {
//	int year = 0, count = 1;
//	size_t i = data.length() - 1;
//	while (data[i] != '/') {
//		year = int(data[i] - 48) * count + year;
//		count *= 10;
//		i--;
//	}
//	return year;
//}
//
//bool DateTime::CheckDay(string& data) {
//	if (CheckMonth(data)) {
//		string y = Year(data);
//		string m = Month(data);
//		string d = Day(data);
//		if (y == CurrentYear() && m == CurrentMonth() && d > CurrentDay()) {
//			//cout << "Nhap sai ngay. Ngay lon hon ngay hien tai" << endl;
//			return false;
//		}
//		if ((m == "01" || m == "03" || m == "05" || m == "07" || m == "08" || m == "10" || m == "12") && d <= "31" && d >= "01") {
//			return true;
//		}
//		else if ((m == "04" || m == "06" || m == "09" || m == "11") && d <= "30" && d >= "01") {
//			return true;
//		}
//		else {
//			int temp = IntYear(data);
//			bool LeapYear = (temp % 4 == 0 && temp % 100 != 0 || temp % 400 == 0);
//			if (LeapYear) {
//				if (d <= "28" && d >= "01") {
//					return true;
//				}
//			}
//			else if (d <= "29" && d >= "01") {
//				return true;
//			}
//			//cout << "Nhap sai ngay" << endl;
//			return false;
//		}
//	}
//	return false;
//}
//bool DateTime::CheckMonth(string& data) {
//	if (Month(data) == "00" || Month(data) > "12") {
//		//cout << "Nhap sai thang" << endl;
//		return false;
//	}
//	if (CheckYear(data)) {
//		if (Year(data) == CurrentYear()) {
//			if (Month(data) > CurrentMonth()) {
//				//cout << "Nhap sai thang. Thang lon hon thang hien tai" << endl;
//				return false;
//			}
//			else {
//				return true;
//			}
//		}
//		return true;
//	}
//	return false;
//}
//bool DateTime::CheckYear(string& data) {
//	if (FormatDate(data)) {
//		if (data[6] == '0') {
//			//cout << "Nhap sai nam" << endl;
//			return false;
//		}
//		if (Year(data).length() > CurrentYear().length() || Year(data) < "2000" || Year(data) > CurrentYear()) {
//			//cout << "nhap sai nam" << endl;
//			return false;
//		}
//		return true;
//	}
//	return false;
//}
//bool DateTime::CheckDate(string& data) {
//	if (!FormatDate(data)) {
//		return false;
//	}
//	else if (!CheckYear(data)) {
//		return false;
//	}
//	else if (!CheckMonth(data)) {
//		return false;
//	}
//	else if (!CheckDay(data)) {
//		return false;
//	}
//	else {
//		//cout<<"nhap dung roi kkk.
//		return true;
//	}
//}
//
//string DateTime::CurrentDay() {
//	time_t timeNow = time(NULL);
//	tm* t = localtime(&timeNow);
//
//	FormatText* temp = new FormatText();
//	string str = temp->CastIntToString(t->tm_mday);
//	if (str.length() == 1) {
//		str = "0" + str;
//	}
//	return str;
//}
//string DateTime::CurrentMonth() {
//	time_t timeNow = time(NULL);
//	tm* t = localtime(&timeNow);
//
//	FormatText* temp = new FormatText();
//	string str=temp->CastIntToString(t->tm_mon + 1);
//	if (str.length() == 1) {
//		str = "0" + str;
//	}
//	return str;
//}
//string DateTime::CurrentYear() {
//	time_t timeNow = time(NULL);
//	tm* t = localtime(&timeNow);
//
//	FormatText* temp = new FormatText();
//	string str = temp->CastIntToString(t->tm_year + 1900);
//	return str;
//}
//
//string DateTime::CurrentDate() {
//	time_t timeNow = time(NULL);
//	tm* t = localtime(&timeNow);
//
//	FormatText* temp = new FormatText();
//	string d = temp->CastIntToString(t->tm_mday);
//	if (d.length() == 1) {
//		d = "0" + d;
//	}
//
//	string m = temp->CastIntToString(t->tm_mon + 1);
//	if (m.length() == 1) {
//		m = "0" + m;
//	}
//
//	string y = temp->CastIntToString(t->tm_year + 1900);
//
//	string date = d + "/" +m + "/" + y;
//	return date;
//}
//string DateTime::ToString()
//{
//	return "dd/mm/yy";
//}
//void DateTime::CastDate(string dateStr)
//{
//	day = 0;
//	year = 0;
//	month = 0;
//}


