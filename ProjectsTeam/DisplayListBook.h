#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include"Title.h"
#include"CheckInput.h"
#include"ISaveFile.h"
class DisplayListBook:public wxFrame
{
private:
	//Backend
	int count = 0;
	int maxItem = 0;
	string* stateBook;
	TitleList *titleList = nullptr;
	CheckInput* checkInput;
	//Frontend
	wxWindow* grandPas;
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
	void OnGridKeyDown(wxKeyEvent& event);
	void OnButtonClicked(wxCommandEvent& event);
	void OnChoice(wxCommandEvent& event);
	void OnEnter(wxCommandEvent& event);
	void EditCurrentCell(wxGridEvent& event);
	void EditData(int row, int col,int index);
	bool CheckPos(wxString text);

	void ShowMessageClear();
	void DeleteSelectedRows();
	void SaveToList();
	void SaveFile();
	void LoadData();

	void OnKeyDownTextCltrToUpper(wxCommandEvent& _rCommandEvent);
	void OnSelectingGrid(wxGridRangeSelectEvent& event);
	void OnSelectedGrid(wxCommandEvent& event);
	void OnSelectedLabelGrid(wxCommandEvent& event);

	void OnSelectedCell(wxGridEvent& event);
	void OnGridTexting(wxCommandEvent& event);
	int GetMaxLength(int col);
	void MainKeyDown(int keyCode);

	void SetModeDelete(bool state);
	bool isModeDelete = false;
	bool canEdit = true;
public:
	DisplayListBook(const wxString& title);
	void SetTitle(Title* title)
	{
		currentTitle = title;
	}
	void SetData(TitleList* list,CheckInput* checkInput)
	{
		this->titleList = list;
		this->checkInput = checkInput;
	}
	void SetGrandPas(wxWindow* grandPas)
	{
		this->grandPas = grandPas;
	}
	DECLARE_EVENT_TABLE();
};

