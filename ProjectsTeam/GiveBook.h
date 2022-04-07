#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include"CardReader.h"
#include"SaveTextFile.h"
#include"BSTree.h"
class GiveBook:public wxFrame
{
private:

	//backend
	SaveTextFile<CardReader>* saveFile = nullptr;
	BSTree<CardReader>* treeCardReader = nullptr;
	CardReader* foundCard = nullptr;


	//front end
	wxPanel* searchPanel;
	wxGrid* grid;
	wxTextCtrl* enterText;
	wxStaticText** displayTitleText;
	wxStaticText** displayText;
	void CreateDisplayInforCard();
	void LoadFile();

	void OnShow(wxShowEvent& event);
public:
	GiveBook(const wxString&  title);
	~GiveBook()//nho xoa cho cac class khac nhaaaaaaaaaaaaaaaaa
	{
		delete[] displayTitleText;
		delete[] displayText;
	}
};

