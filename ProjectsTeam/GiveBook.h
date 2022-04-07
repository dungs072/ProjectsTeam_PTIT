#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include"CardReader.h"
#include"SaveTextFile.h"
#include"BSTree.h"
#include"CheckInput.h"
typedef unsigned long long ulong;
class GiveBook:public wxFrame
{
private:

	//backend
	CheckInput* checkInput;
	SaveTextFile<CardReader>* saveFile = nullptr;
	BSTree<CardReader>* treeCardReader = nullptr;
	CardReader* foundCard = nullptr;
	int length = 0;

	//front end
	wxPanel* searchPanel;
	wxGrid* grid;
	wxTextCtrl* enterText;
	wxStaticText** displayTitleText;
	wxStaticText** displayText;
	void CreateDisplayInforCard();
	void DisplayCardOnPanel();
	void ClearOldDataOnPanel();
	void LoadFile();

	void OnShow(wxShowEvent& event);
	void OnEnter(wxCommandEvent& event);
	void OnKeyDown(wxKeyEvent& event);
public:
	GiveBook(const wxString&  title);
	~GiveBook()//nho xoa cho cac class khac nhaaaaaaaaaaaaaaaaa
	{
		delete[] displayTitleText;
		delete[] displayText;
	}
	DECLARE_EVENT_TABLE();
};

