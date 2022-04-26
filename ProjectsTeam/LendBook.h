#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include<cmath>
#include"CardReader.h"
#include"SaveTextFile.h"
#include"CheckInput.h"
#include"BSTree.h"
#include"ControlDateTime.h"
typedef unsigned long long ulong;
class LendBook:public wxFrame
{
private:

	//Back end
	BSTree<CardReader>* treeCardReader;
	TitleList* titleList;
	CardReader* foundCardReader = nullptr;
	Title* selectedTitle = nullptr;
	Book* selectedBook = nullptr;
	SaveTextFile<CardReader>* cardFile;
	SaveTextFile<Title>* titleFile;
	CheckInput* checkInput;
	ControlDateTime* controlDateTime;

	wxPanel* searchPanel;
	wxPanel* displayInforPanel;
	
	wxGrid* titleGrid;
	wxGrid* bookGrid;
	wxGrid* borrowingBookGrid;

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
	void DeleteBorrowingBook();
	void SetValueAfterDelete(string bookCode);
	void SaveFile();
	void LoadData();

	void OnShow(wxShowEvent& event);
	void OnShowDialog(wxShowEvent& event);
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

	void OnSelectingBorrowingBookGrid(wxGridRangeSelectEvent& event);
	void OnSelectedBorrowingBookGrid(wxCommandEvent& event);
	void OnSelectedLabelBorrowingBookGrid(wxCommandEvent& event);

	void OnBackTitleButtonClicked(wxCommandEvent& event);
	void OnOkButton(wxCommandEvent& event);
	void OnCancelButton(wxCommandEvent& event);

	void OnYearSelection(wxCommandEvent& event);
	void OnMonthSelection(wxCommandEvent& event);

	void OnEnterTextFocus(wxFocusEvent& _rCommandEvent);
	void OnExitMenuButton(wxCommandEvent& event);

	void ProccessYearSelection();
	void ProccessMonthSelection();

	void SetDefaultRangeDateTime();
	void ProccessLeapYear();
	bool ProccessCurrentDate();
	
	bool HasBorrowingDayLong();

	void TitleGridFocus();
	void BookGridFocus();
	void BorrowingGridFocus();
	void ShowMessageClear();
	const int maxBookLend = 3;
	int maxCard = 0;
	int maxTitle = 0;
	int maxBook = 0;
	int bookRowChange = 0;
	int borrowingBookCount = 0;
	wxArrayString yearArray, monthArray, dayArray;
public:

	LendBook(const wxString& title);
	void SetData(BSTree<CardReader>* cardReaders, TitleList* titlelist)
	{
		this->treeCardReader = cardReaders;
		this->titleList = titlelist;
	}
	DECLARE_EVENT_TABLE();
};

