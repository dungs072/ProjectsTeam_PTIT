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
	bool isTurnOnEnterPanel = true;
	wxPanel* enterPanel;
	wxPanel* takeNotePanel;
	wxGrid* grid;
	wxTextCtrl** enterText;
	CheckInput* checkInput;
	//method
	void CreateEnterArea(wxPanel* enterPanel);
	void CreateTakeNoteArea(wxPanel* takeNotePanel);
	void CreateKeyNoteArea(wxPanel* keyNotePanel);
	void OnKeyDown(wxKeyEvent& event);
	void OnKeyDownTextCltrToUpper(wxCommandEvent& event);
	void OnEnter(wxCommandEvent& event);
	void EditCurrentCell(wxGridEvent& event);
	void OnExitMenu(wxCommandEvent& event);
	void OnShow(wxShowEvent& event);
	
	void EditTable(Title* title,int row);
	void SwitchPanel(bool state);
	void SwitchEnterText(bool state);
	void SaveToList();
	void SaveFile();
	void LoadFile();
	void LoadListToTable();
	void ShowMessageClear();
	void DeleteSelectedRows();
	void ClearInforInEnterText();
	bool CheckISBN(wxString text);
	bool CheckBookName(wxString text);
	bool CheckPageNumber(wxString text);
	bool CheckAuthor(wxString text);
	bool CheckYearPublic(wxString text);
	bool CheckType(wxString text);
	bool CheckDuplicateISBN(wxString text,int row);
	int CompareTitle(Title* t1, Title* t2);
	//quick sort
	void Swap(Title*t1, Title* t2);
	int partition( int l, int h);
	void QuickSort( int l, int h);
public:
	BookTitle(const wxString& title);
	~BookTitle()
	{
		delete saveFile;
		delete linearList;
		delete[]enterText;
	}
	DECLARE_EVENT_TABLE();

};

