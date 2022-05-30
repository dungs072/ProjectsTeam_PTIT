#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include<ctime>
#include"CheckInput.h"
#include"Title.h"
#include"ISaveFile.h"
#include"BookFunction.h"
using namespace DataStructure;
class BookTitle:public wxFrame
{
private:
	//backend
	TitleList* titleList;
	CheckInput* checkInput;
	BookFunction* bookFunction;
	//frontend
	int maxItem = 0;
	bool isTurnOnEnterPanel = true;
	wxPanel* enterPanel;
	wxPanel* takeNotePanel;
	wxGrid* grid;
	wxTextCtrl** enterText;
	
	//method
	void CreateEnterArea(wxPanel* enterPanel);
	void CreateTakeNoteArea(wxPanel* takeNotePanel);
	void CreateKeyNoteArea(wxPanel* keyNotePanel);
	void OnKeyDown(wxKeyEvent& event);
	void OnGridKeyDown(wxKeyEvent& event);
	void MainKeyDown(int keyDown);
	void OnKeyDownTextCltrToUpper(wxCommandEvent& event);
	void OnEnter(wxCommandEvent& event);
	void EditCurrentCell(wxGridEvent& event);
	void OnExitMenu(wxCommandEvent& event);
	void OnShow(wxShowEvent& event);

	void OnSelectingGrid(wxGridRangeSelectEvent& event);
	void OnSelectedGrid(wxCommandEvent& event);
	void OnSelectedLabelGrid(wxCommandEvent& event);

	void OnSelectedCell(wxGridEvent& event);
	void OnGridTexting(wxCommandEvent& event);
	int GetMaxLength(int col);
	
	void EditTable(Title* title,int row);
	void SwitchPanel(bool state);
	void SwitchEnterText(bool state);
	void SaveToList();
	void SaveFile();
	void LoadData();
	void LoadListToTable();
	void ShowMessageClear();
	void DeleteSelectedRows();
	void ClearInforInEnterText();
	void ClearOldDataInGrid();
	bool CheckISBN(wxString text);
	bool CheckBookName(wxString text);
	bool CheckPageNumber(wxString text);
	bool CheckAuthor(wxString text);
	bool CheckYearPublic(wxString text);
	bool CheckType(wxString text);
	bool CheckDuplicateISBN(wxString text,int row);

	void SetModeDelete(bool state);
	int CompareTitle(Title* t1, Title* t2);


	bool isModeDelete = false;
	bool canEdit = true;
	//quick sort
	void Swap(Title*t1, Title* t2);
	int partition( int l, int h);
	void QuickSort( int l, int h);
public:
	BookTitle(const wxString& title);
	~BookTitle()
	{
		delete[]enterText;
	}
	void SetData(TitleList* titleList,CheckInput* checkInput,BookFunction* bookFunction)
	{
		this->titleList = titleList;
		this->checkInput = checkInput;
		this->bookFunction = bookFunction;
	}
	DECLARE_EVENT_TABLE();

};
