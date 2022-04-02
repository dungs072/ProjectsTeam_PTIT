#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include"CardReader.h"
#include"SaveTextFile.h"
#include"CheckInput.h"
#include"BSTree.h"
#include"LinearList.h"
#include"ControlDateTime.h"
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
	ControlDateTime* controlDateTime;

	wxPanel* searchPanel;
	wxPanel* displayInforPanel;
	
	wxGrid* titleGrid;
	wxGrid* bookGrid;

	wxButton* selectedTitleButton;
	wxButton* selectedBookButton;
	wxButton* backTitleButton;
	//for dialog
	wxButton* okButton;
	wxButton* cancelButton;

	//wxTextEntryDialog* entryDateDialog;
	//for creating dialog
	wxDialog* dialog;
	wxChoice* yearChoice;
	wxChoice* monthChoice;
	wxChoice* dayChoice;

	//for creating dialog

	wxTextCtrl* enterSearchText;
	wxTextCtrl* hideFocusText;
	wxStaticText* titleGridText;
	wxStaticText** displayPersonText;
	wxStaticText** displayNameBookText;
	wxStaticText** displayDateBookText;
	void CreateSearchPanel();
	void DisplayCardOnPanel();
	void DisplayBookBorrow();
	void DisplayBookJustBorrow();
	void LoadListTitleToTable();
	void LoadListBookToTable();
	void ClearOldDataInInforPanel();
	void ClearOldDataInTitleGrid();
	void ClearOldDataInBookGrid();
	void SetDefaultGrid();
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
	void OnOkButton(wxCommandEvent& event);
	void OnCancelButton(wxCommandEvent& event);

	void OnYearSelection(wxCommandEvent& event);
	void OnMonthSelection(wxCommandEvent& event);

	void ProccessYearSelection();
	void ProccessMonthSelection();
	void SetDefaultValueDateTime();

	bool ProccessCurrentDate();

	const int maxBookLend = 3;
	int maxCard = 0;
	int maxTitle = 0;
	int maxBook = 0;
	int bookRowChange = 0;
	int borrowingBookCount = 0;
	wxArrayString yearArray, monthArray, dayArray;
public:

	LendBook(const wxString& title);
	DECLARE_EVENT_TABLE();
};

