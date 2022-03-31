#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include"CardReader.h"
#include"SaveTextFile.h"
#include"CheckInput.h"
#include"BSTree.h"
#include"LinearList.h"
typedef unsigned long long ulong;
class LendBook:public wxFrame
{
private:

	//Back end
	BSTree<CardReader>* treeCardReader;
	LinearList<Title>* linearList;
	CardReader* foundCardReader = nullptr;
	Title* selectedTitle = nullptr;
	Book* selectedBook = nullptr;
	SaveTextFile<CardReader>* saveFile;
	SaveTextFile<Title>* readFile;
	CheckInput* checkInput;

	wxPanel* searchPanel;
	wxPanel* displayInforPanel;
	
	wxGrid* titleGrid;
	wxGrid* bookGrid;

	wxButton* selectedTitleButton;
	wxButton* selectedBookButton;
	wxButton* backTitleButton;

	wxTextCtrl* enterSearchText;
	wxTextCtrl* hideFocusText;
	wxStaticText* titleGridText;
	wxStaticText** displayPersonText;
	wxStaticText** displayNameBookText;
	wxStaticText** displayDateBookText;
	void CreateSearchPanel();
	void DisplayCardOnPanel();
	void DisplayBookBorrow();
	void LoadListTitleToTable();
	void LoadListBookToTable();
	void ClearOldDataInTitleGrid();
	void ClearOldDataInBookGrid();
	void LoadFile();

	void OnShow(wxShowEvent& event);
	void OnEnter(wxCommandEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnSelectingTitleGrid(wxGridRangeSelectEvent& event);
	void OnSelectedTitleGrid(wxCommandEvent& event);
	void OnSelectedLabelTitleGrid(wxCommandEvent& event);
	void OnSelectedTitleButtonClicked(wxCommandEvent& event);

	void OnSelectingBookGrid(wxGridRangeSelectEvent& event);
	void OnSelectedBookGrid(wxCommandEvent& event);
	void OnSelectedLabelBookGrid(wxCommandEvent& event);
	void OnSelectedBookButtonClicked(wxCommandEvent& event);

	void OnBackTitleButtonClicked(wxCommandEvent& event);

	const int maxBookLend = 3;
	int maxCard = 0;
	int maxTitle = 0;
	int maxBook = 0;
	int bookRowChange = 0;
	int borrowBookCount = 0;
public:

	LendBook(const wxString& title);
	DECLARE_EVENT_TABLE();
};

