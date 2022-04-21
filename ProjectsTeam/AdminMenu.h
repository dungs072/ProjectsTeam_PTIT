#pragma once
#include"CheckInput.h"
#include"ReaderCard.h"
#include"DisplayListCardReader.h"
#include"BookTitle.h"
#include"DisplayListTitle.h"
#include"FindInforBook.h"
#include"LendBook.h"
#include"GiveBook.h"
#include"OverDueList.h"
class AdminMenu:public wxFrame
{
private:
	ReaderCard* readerCard;
	DisplayListCardReader* displayCardReader;
	BookTitle* bookTitle;
	DisplayListTitle* displayTitle;
	FindInforBook* findInforBook;
	LendBook* lendBook;
	GiveBook* giveBook;
	OverDueList* overDueList;
	CheckInput* checkInput;
	wxPanel** choicePanel;
	void CreateReaderCardChoice();
	void CreateTitleChoice();
	void CreateBookFunctionChoice();

	//event
	void OnReaderCard(wxCommandEvent& event);
	void OnDisplayCardReader(wxCommandEvent& event);
	void OnTitle(wxCommandEvent& event);
	void OnDisplayTitle(wxCommandEvent& event);
	void OnFindInforBook(wxCommandEvent& event);
	void OnBorrowBook(wxCommandEvent& event);
	void OnGiveBook(wxCommandEvent& event);
	void OnOverDueList(wxCommandEvent& event);

	void OnReaderCardPanel(wxCommandEvent& event);
	void OnTitlePanel(wxCommandEvent& event);
	void OnFunctionBookPanel(wxCommandEvent& event);
	
	void TurnOnPanel(int index);
public:
	AdminMenu(const wxString& title);
	~AdminMenu()
	{
		delete checkInput;
		delete choicePanel;
	}
};

