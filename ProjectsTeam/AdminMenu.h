#pragma once
#include"CheckInput.h"
#include"ReaderCard.h"
#include"DisplayListCardReader.h"
#include"BookTitle.h"
#include"DisplayListTitle.h"
class AdminMenu:public wxFrame
{
private:
	ReaderCard* readerCard;
	DisplayListCardReader* displayCardReader;
	BookTitle* bookTitle;
	DisplayListTitle* displayTitle;
	CheckInput* checkInput;
	wxPanel** choicePanel;
	void CreateReaderCardChoice();
	void CreateTitleChoice();

	//event
	void OnReaderCard(wxCommandEvent& event);
	void OnDisplayCardReader(wxCommandEvent& event);
	void OnTitle(wxCommandEvent& event);
	void OnDisplayTitle(wxCommandEvent& event);
	void OnReaderCardPanel(wxCommandEvent& event);
	void OnTitlePanel(wxCommandEvent& event);
	void TurnOnPanel(int index);
public:
	AdminMenu(const wxString& title);
};

