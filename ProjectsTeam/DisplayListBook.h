#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include"Title.h"
#include"CheckInput.h"
#include"SaveTextFile.h"
class DisplayListBook:public wxFrame
{
private:
	//Backend
	int count = 0;
	int maxItem = 0;
	string* stateBook;
	SaveTextFile<Title>* saveFile;
	TitleList *titleList = nullptr;
	//Frontend
	CheckInput* checkInput = new CheckInput();
	wxGrid* grid;
	wxPanel* enterPanel;
	wxPanel* takeNotePanel;
	wxPanel* guidePanel;
	wxTextCtrl* enterText;
	wxTextCtrl* hideEnterText;
	wxChoice* stateChoice;
	Title* currentTitle;
	wxStaticText* titleGrid;
	wxButton* backButton;
	//Method
	void CreateEnterArea();
	void CreateKeyNoteArea();
	void CreateGuideArea();
	void OnShow(wxShowEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnButtonClicked(wxCommandEvent& event);
	void OnChoice(wxCommandEvent& event);
	void OnEnter(wxCommandEvent& event);
	void EditCurrentCell(wxGridEvent& event);
	bool CheckStateBook(wxString text);
	bool CheckPos(wxString text);

	void ShowMessageClear();
	void DeleteSelectedRows();
	void SaveToList();
	void SaveFile();
	void LoadFile();
public:
	DisplayListBook(const wxString& title);
	void SetTitle(Title* title)
	{
		currentTitle = title;
	}
	void SetListTitle(TitleList* list)
	{
		if (titleList != nullptr)
		{
			delete titleList;
			titleList = nullptr;
		}
		titleList = list;
	}
	DECLARE_EVENT_TABLE();
};

