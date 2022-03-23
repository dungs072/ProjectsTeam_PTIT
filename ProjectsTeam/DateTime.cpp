#include "Datetime.h"
#include"FormatText.h"
#include<iostream>
using namespace std;
bool DateTime::FormatDate(string& data) {
	size_t len = data.length();
	if (len < 10) {	
		//cout << "Nhap sai cu phap" << endl;
		return false;
	}
	for (int i = 0; i < len; i++) {
		if (i == 2 || i == 5) {
			if (data[i] != '/') {
				//cout << "Nhap sai cu phap" << endl;
				return false;
			}
			continue;
		}
		if (!(data[i] >= '0' && data[i] <= '9')) {
			//cout << "Nhap sai cu phap" << endl;
			return false;
		}
	}
	return true;
}

string DateTime::Day(string data) {
	string temp = "";
	temp = temp + data[0] + data[1];
	return temp;
}
string DateTime::Month(string data) {
	string temp = "";
	temp = temp + data[3] + data[4];
	return temp;
}
string DateTime::Year(string data) {
	string year = "";
	size_t i = data.length() - 1;
	while (data[i] != '/') {
		year = data[i] + year;
		i--;
	}
	return year;
}
int DateTime::IntYear(string data) {
	int year = 0, count = 1;
	size_t i = data.length() - 1;
	while (data[i] != '/') {
		year = int(data[i] - 48) * count + year;
		count *= 10;
		i--;
	}
	return year;
}

bool DateTime::CheckDay(string& data) {
	if (CheckMonth(data)) {
		string y = Year(data);
		string m = Month(data);
		string d = Day(data);
		if (y == CurrentYear() && m == CurrentMonth() && d > CurrentDay()) {
			//cout << "Nhap sai ngay. Ngay lon hon ngay hien tai" << endl;
			return false;
		}
		if ((m == "01" || m == "03" || m == "05" || m == "07" || m == "08" || m == "10" || m == "12") && d <= "31" && d >= "01") {
			return true;
		}
		else if ((m == "04" || m == "06" || m == "09" || m == "11") && d <= "30" && d >= "01") {
			return true;
		}
		else {
			int temp = IntYear(data);
			bool LeapYear = (temp % 4 == 0 && temp % 100 != 0 || temp % 400 == 0);
			if (LeapYear) {
				if (d <= "28" && d >= "01") {
					return true;
				}
			}
			else if (d <= "29" && d >= "01") {
				return true;
			}
			//cout << "Nhap sai ngay" << endl;
			return false;
		}
	}
	return false;
}
bool DateTime::CheckMonth(string& data) {
	if (Month(data) == "00" || Month(data) > "12") {
		//cout << "Nhap sai thang" << endl;
		return false;
	}
	if (CheckYear(data)) {
		if (Year(data) == CurrentYear()) {
			if (Month(data) > CurrentMonth()) {
				//cout << "Nhap sai thang. Thang lon hon thang hien tai" << endl;
				return false;
			}
			else {
				return true;
			}
		}
		return true;
	}
	return false;
}
bool DateTime::CheckYear(string& data) {
	if (FormatDate(data)) {
		if (data[6] == '0') {
			//cout << "Nhap sai nam" << endl;
			return false;
		}
		if (Year(data).length() > CurrentYear().length() || Year(data) < "2000" || Year(data) > CurrentYear()) {
			//cout << "nhap sai nam" << endl;
			return false;
		}
		return true;
	}
	return false;
}
bool DateTime::CheckDate(string& data) {
	if (!FormatDate(data)) {
		return false;
	}
	else if (!CheckYear(data)) {
		return false;
	}
	else if (!CheckMonth(data)) {
		return false;
	}
	else if (!CheckDay(data)) {
		return false;
	}
	else {
		//cout<<"nhap dung roi kkk.
		return true;
	}
}

string DateTime::CurrentDay() {
	time_t timeNow = time(NULL);
	tm* t = localtime(&timeNow);

	FormatText* temp = new FormatText();
	string str = temp->CastIntToString(t->tm_mday);
	if (str.length() == 1) {
		str = "0" + str;
	}
	return str;
}
string DateTime::CurrentMonth() {
	time_t timeNow = time(NULL);
	tm* t = localtime(&timeNow);

	FormatText* temp = new FormatText();
	string str=temp->CastIntToString(t->tm_mon + 1);
	if (str.length() == 1) {
		str = "0" + str;
	}
	return str;
}
string DateTime::CurrentYear() {
	time_t timeNow = time(NULL);
	tm* t = localtime(&timeNow);

	FormatText* temp = new FormatText();
	string str = temp->CastIntToString(t->tm_year + 1900);
	return str;
}

string DateTime::CurrentDate() {
	time_t timeNow = time(NULL);
	tm* t = localtime(&timeNow);

	FormatText* temp = new FormatText();
	string d = temp->CastIntToString(t->tm_mday);
	if (d.length() == 1) {
		d = "0" + d;
	}

	string m = temp->CastIntToString(t->tm_mon + 1);
	if (m.length() == 1) {
		m = "0" + m;
	}

	string y = temp->CastIntToString(t->tm_year + 1900);

	string date = d + "/" +m + "/" + y;
	return date;
}

