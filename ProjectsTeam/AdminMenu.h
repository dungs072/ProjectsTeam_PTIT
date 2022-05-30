#pragma once
#include"SaveTextFile.h"
#include"BSTree.h"
#include"CheckInput.h"
#include"ReaderCard.h"
#include"DisplayListCardReader.h"
#include"BookTitle.h"
#include"DisplayListTitle.h"
#include"FindInforBook.h"
#include"LendBook.h"
#include"GiveBook.h"
#include"OverDueList.h"
#include"MostBorrowings.h"
#include"ISaveFile.h"
class AdminMenu:public wxFrame,public ISaveFile
{
private:
	//data is stored in heap memory
	SaveTextFile<CardReader>* cardReaderFile;
	SaveTextFile<Title>* titleFile;
	BSTree<CardReader>* treeCardReader;
	TitleList* titleList;
	//---------------------------------//

	
	ReaderCard* readerCard;
	DisplayListCardReader* displayCardReader;
	BookTitle* bookTitle;
	DisplayListTitle* displayTitle;
	FindInforBook* findInforBook;
	LendBook* lendBook;
	GiveBook* giveBook;
	OverDueList* overDueList;
	MostBorrowings* mostBorrowings;
	CheckInput* checkInput;
	BookFunction* bookFunction;

	wxColor darkYellow,lightYellow,
			blueGreen,lightOrange,
			lightBlack,orange,red,green,darkRed;

	wxStaticText* runningText;
	wxPanel** choicePanel;

	wxTimer timer;

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
	void OnMostBorrowings(wxCommandEvent& event);

	void OnReaderCardPanel(wxCommandEvent& event);
	void OnTitlePanel(wxCommandEvent& event);
	void OnFunctionBookPanel(wxCommandEvent& event);

	void OnExit(wxCommandEvent& event);
	void OnMainMenu(wxCommandEvent& event);

	void OnTimer(wxTimerEvent& event);
	void OnShow(wxShowEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	
	void TurnOnPanel(int index);

	void LoadDataIntoTempMemory();

	void SaveFile();

	int distance = -550;

public:
	AdminMenu(const wxString& title);
	~AdminMenu()
	{
		//delete checkInput;
		delete choicePanel;
		delete treeCardReader;
		delete titleList;

		delete readerCard;
		delete displayCardReader;
		delete bookTitle;
		delete displayTitle;
		delete findInforBook;
		delete lendBook;
		delete giveBook;
		delete overDueList;
		delete mostBorrowings;
	}
	wxDECLARE_EVENT_TABLE();

};
const int TIMER_ID = 7;

