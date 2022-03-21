#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include<ctime>
#include"CheckInput.h"
#include"Title.h"
#include"LinearList.h"
#include"SaveTextFile.h"
using namespace DataStructure;
class BookTitle:public wxFrame
{
private:
	//backend
	SaveTextFile<Title>* saveFile;
	LinearList<Title>* linearList;
	//frontend
	int maxItem = 0;
	wxGrid* grid;
	CheckInput* checkInput;
	wxTextCtrl** enterText;
	//method
	void CreateEnterArea(wxPanel* enterPanel);
	void OnKeyDown(wxKeyEvent& event);
	void OnEnter(wxCommandEvent& event);
	void EditCurrentCell(wxGridEvent& event);

	void SaveToList();
	void SaveFile();
	void LoadFile();
	void ClearInforInEnterText();
	bool CheckISBN(wxString text);
	bool CheckBookName(wxString text);
	bool CheckPageNumber(wxString text);
	bool CheckAuthor(wxString text);
	bool CheckYearPublic(wxString text);
	bool CheckType(wxString text);
	bool CheckDuplicateISBN(wxString text);
	int CompareTitle(Title* t1, Title* t2);
	//quick sort
	void Swap(Title* t1, Title* t2);
	int partition( int l, int h);
	void QuickSort( int l, int h);
public:
	BookTitle(const wxString& title);
	DECLARE_EVENT_TABLE();

};

