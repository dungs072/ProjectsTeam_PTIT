#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include<iostream>
#include<string>
#include"BSTree.h"
#include"CardReader.h"
#include"SaveTextFile.h"
//#include"ReaderCard.h"
using namespace DataStructure;
typedef unsigned long long ulong;
using std::string;

class DisplayListCardReader:public wxFrame
{
private:
	//ReaderCard* readerCard = nullptr;
	BSTree<CardReader>* cardReaderTree;
	string* stateText;
	SaveTextFile<CardReader>* saveFile;
	wxGrid* grid;
	wxStaticText* gridLabel;
	void SetTextSize(wxStaticText* text, int size);
	void DisplayTabel(bool state);
	// event
	void OnSortCode(wxCommandEvent& event);
	void OnSortName(wxCommandEvent& event);
	void EditCurrentCell(wxGridEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnExitMenu(wxCommandEvent& event);

	void LoadFile();
	void SaveFile();
	void DisplayCell(CardReader** arr,int length);
	void ErrorMessageBox(string message);
	void ClearGridValue();
	wxString CastUlongToWxString(ulong number);
	string EditCardCode(ulong number, int maxLengthCode);
	//Check Error InPut
	bool IsWhiteSpaceAllText(wxString text);
	bool IsWord(wxString text);
	bool IsRightSex(wxString text);
	bool IsRightCodeState(int maxNumber, int currentNumber);
	void ModifyTextInput(wxString& text);
	void ModifyString(string& str);
	void UpperWxString(wxString& text);
	string UpperText(string str);
	int CastWxStringToInt(wxString text);

	//quickSort
	void Swap(CardReader* card1, CardReader* card2);
	int Partition(CardReader** A, int l, int h);
	void QuickSort(CardReader** A, int l, int h);

	//field
	int length = 0;
public:
	DisplayListCardReader(const wxString& title);
	DECLARE_EVENT_TABLE();
};
const int DefaultRow = 30;
const int SORT_CODE = 1;
const int SORT_NAME = 2;
const int EXIT_MENU = 3;

