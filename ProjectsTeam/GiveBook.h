#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include"CardReader.h"
#include"SaveTextFile.h"
#include"BSTree.h"
#include"Title.h"
#include"CheckInput.h"
#include"ControlDateTime.h"
typedef unsigned long long ulong;
class GiveBook:public wxFrame
{
private:


	//backend
	ControlDateTime* controlDateTime = nullptr;
	CheckInput* checkInput;
	SaveTextFile<CardReader>* saveFileCard = nullptr;
	SaveTextFile<Title>* saveFileTitle = nullptr;
	BSTree<CardReader>* treeCardReader = nullptr;
	TitleList* titleList = nullptr;
	CardReader* foundCard = nullptr;
	BorrowBook** listBorrowBook = nullptr;
	Book** listBook = nullptr;
	int lengthCard = 0;
	int lengthTitle = 0;

	//front end
	wxPanel* searchPanel;
	wxGrid* grid;
	wxTextCtrl* enterText;
	wxTextCtrl* focusText;
	wxStaticText** displayTitleText;
	wxStaticText** displayText;


	wxDialog* dialog;
	wxChoice* yearChoice;
	wxChoice* monthChoice;
	wxChoice* dayChoice;
	//button
	wxButton* okButton;
	wxButton* cancelButton;
	wxButton* giveBookButton;
	wxButton* lostBookButton;
	void CreateDisplayInforCard();
	void DisplayCardOnPanel();
	void DisplayBorrowingBook(BorrowBook borrowBook, Book book, Title title,int row);
	void FindInforBorrowBook();
	void ClearOldDataOnPanel();
	void ClearOldDataOnGrid();
	void ClearOldDataInBackEnd();
	void LoadData();
	void SaveFile();

	void OnShow(wxShowEvent& event);
	void OnEnter(wxCommandEvent& event);
	void OnKeyDown(wxKeyEvent& event);

	void OnGiveBook(wxCommandEvent& event);
	void OnLostBook(wxCommandEvent& event);

	void OnSelectingGrid(wxGridRangeSelectEvent& event);
	void OnSelectedGrid(wxCommandEvent& event);
	void OnSelectedLabelGrid(wxCommandEvent& event);

	void OnYearSelection(wxCommandEvent& event);
	void OnMonthSelection(wxCommandEvent& event);
	void ProccessYearSelection();
	void ProccessMonthSelection();

	void SetDefaultRangeDateTime();
	void ProccessLeapYear();
	bool ProccessCurrentDate();
	void OnShowDialog(wxShowEvent& event);
	void OnOkButton(wxCommandEvent& event);
	void OnCancelButton(wxCommandEvent& event);
	void OnExitMenuButton(wxCommandEvent& event);

	bool hasRightSelection = false;
	int index = -1;
	string bookCodeSelected = "";
	wxArrayString yearArray, monthArray, dayArray;
	
public:
	GiveBook(const wxString&  title);
	~GiveBook()//nho xoa cho cac class khac nhaaaaaaaaaaaaaaaaa
	{
		delete[] displayTitleText;
		delete[] displayText;
		delete[]listBorrowBook;
		delete[]listBook;
		delete saveFileCard;
		delete saveFileTitle;
		delete checkInput;
		delete foundCard;
		delete searchPanel;
		delete grid;
		delete controlDateTime;
	}
	void SetData(BSTree<CardReader>* treeCard, TitleList* titleList)
	{
		this->treeCardReader = treeCard;
		this->titleList = titleList;
	}
	DECLARE_EVENT_TABLE();
};

