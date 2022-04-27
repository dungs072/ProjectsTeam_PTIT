#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include"CheckInput.h"
#include"Title.h"
#include"SortAlgorithm.h"
class MostBorrowings:public wxFrame
{
private:
	//backend
	TitleList* titleList;
	
	CheckInput* checkInput;
	SortAlgorithm<Title>* sort;
	//front-end
	wxGrid* grid;

	void LoadListToTable(Title** arr);
	void ClearOldData(Title** arr);
	void OnShow(wxShowEvent& event);
	void OnExitMenu(wxCommandEvent& event);
public:
	MostBorrowings(const wxString& title);
	void SetTitleList(TitleList* titleList)
	{
		this->titleList = titleList;
	}
};

