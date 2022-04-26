#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include<iostream>
#include<string>
#include"BSTree.h"
#include"CardReader.h"
#include"SaveTextFile.h"
#include"SortAlgorithm.h"
#include"CheckInput.h"
//#include"ReaderCard.h"
using namespace DataStructure;
typedef unsigned long long ulong;
using std::string;

class DisplayListCardReader:public wxFrame
{
private:
	//ReaderCard* readerCard = nullptr;
	CheckInput* checkInput;
	BSTree<CardReader>* cardReaderTree;
	string* sexText;
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
	void OnGridKeyDown(wxKeyEvent& event);
	void OnExitMenu(wxCommandEvent& event);
	void OnShow(wxShowEvent& event);
	void OnSelectingGrid(wxGridRangeSelectEvent& event);
	void OnSelectedGrid(wxCommandEvent& event);
	void OnSelectedLabelGrid(wxCommandEvent& event);

	void OnSelectedCell(wxGridEvent& event);
	void OnGridTexting(wxCommandEvent& event);
	int GetMaxLength(int col);

	void LoadData();
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
	//void Swap(CardReader& card1, CardReader& card2);
	void Swap(int i, int j, CardReader** arr);
	int Partition(CardReader** A, int l, int h);
	void QuickSort(CardReader** A, int l, int h);

	//field
	int length = 0;
	bool canEdit = true;
public:
	DisplayListCardReader(const wxString& title);
	void SetCardReaders(BSTree<CardReader>* cardReaders);
	DECLARE_EVENT_TABLE();
};
const int DefaultRow = 30;
const int SORT_CODE = 1;
const int SORT_NAME = 2;
const int EXIT_MENU = 3;

