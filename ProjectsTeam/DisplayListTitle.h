#pragma once
#include<iostream>
#include<wx/wx.h>
#include<wx/grid.h>
#include"CheckInput.h"
#include"SaveTextFile.h"
#include"LinearList.h"
#include"DisplayListBook.h"
#include"SortAlgorithm.h"
typedef unsigned int uint;
using namespace DataStructure;
class DisplayListTitle :public wxFrame
{
private:
	//backend
	SortAlgorithm<Title>* sort;
	CheckInput* checkInput = new CheckInput();
	SaveTextFile<Title>* saveFile;
	LinearList<Title>* linearList;
	Title* selectedTitle = nullptr;
	//Frontend
	DisplayListBook* listBook;
	wxGrid* grid;
	wxPanel* functionPanel;
	wxBoxSizer* mainHBox;
	wxStaticText* bookNameText;
	wxButton* bookButton;
	bool isTurnOn = true;
	void CreateTakeNoteArea(wxPanel* takeNotePanel);
	void CreateKeyNoteArea(wxPanel* keyNotePanel);
	void CreateFunctionArea();
	void EditCurrentCell(wxGridEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnSelectingGrid(wxGridRangeSelectEvent& event);
	void OnSelectedGrid(wxCommandEvent& event);
	void OnSelectedLabelGrid(wxCommandEvent& event);
	void OnButtonDown(wxCommandEvent& event);
	void OnExitMenu(wxCommandEvent& event);
	void OnShow(wxShowEvent& event);
	void LoadFile();
	void SaveFile();
	void LoadListToTable();
	void EditTable(Title* title, int row);
	void ShowFunctionPanel();
	//check
	bool CheckISBN(wxString text);
	bool CheckBookName(wxString text);
	bool CheckPageNumber(wxString text);
	bool CheckAuthor(wxString text);
	bool CheckYearPublic(wxString text);
	bool CheckType(wxString text);
	bool CheckDuplicateISBN(wxString text,int row);
	//int CompareTitle(Title* t1, Title* t2);
	int maxItem = 0;
public:
	DisplayListTitle(const wxString& title);
	DECLARE_EVENT_TABLE();
};
const int BOOK_ID = 20;

