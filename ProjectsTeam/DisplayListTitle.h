#pragma once
#include<iostream>
#include<wx/wx.h>
#include<wx/grid.h>
#include"CheckInput.h"
#include"SaveTextFile.h"
#include"LinearList.h"
typedef unsigned int uint;
using namespace DataStructure;
class DisplayListTitle :public wxFrame
{
private:
	//backend
	CheckInput* checkInput = new CheckInput();
	SaveTextFile<Title>* saveFile;
	LinearList<Title>* linearList;
	//Frontend
	wxGrid* grid;
	void CreateTakeNoteArea(wxPanel* takeNotePanel);
	void CreateKeyNoteArea(wxPanel* keyNotePanel);
	void EditCurrentCell(wxGridEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void LoadFile();
	void SaveFile();
	void LoadListToTable();
	void EditTable(Title* title, int row);
	//check
	bool CheckISBN(wxString text);
	bool CheckBookName(wxString text);
	bool CheckPageNumber(wxString text);
	bool CheckAuthor(wxString text);
	bool CheckYearPublic(wxString text);
	bool CheckType(wxString text);
	bool CheckDuplicateISBN(wxString text,int row);
	int CompareTitle(Title* t1, Title* t2);
	int maxItem = 0;
public:
	DisplayListTitle(const wxString& title);
	DECLARE_EVENT_TABLE();
};

