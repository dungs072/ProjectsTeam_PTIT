#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include<wx/event.h>
#include<wx/notebook.h>
#include<iostream>
#include<String>
#include<math.h>
#include<time.h>
#include<typeinfo>
#include"BSTree.h"
#include"CheckInput.h"
#include"ISaveFile.h"
typedef unsigned long long ulong;
using std::string;
using namespace DataStructure;
class ReaderCard :public wxFrame
{
private:

	//backend
	BSTree<CardReader>* cardReaderTree;
	CardReader* CreateCardReader(wxTextCtrl** textCtrlList, ulong cardCode);
	CheckInput* checkInput = nullptr;
	//frontend
	wxMenuBar* menuBar;
	wxMenu* file;
	string* stateText;
	string* sexText;
	wxNotebook* noteBook;
	wxCheckBox** sexCheckBox;
	wxCheckBox** stateCheckBox;
	wxTextCtrl** enterText;
	wxTextCtrl** displayText;
	wxBoxSizer* mainHBox;
	wxGrid* grid;
	wxPanel* mainPanel;
	wxPanel* enterTextBackGround;
	wxPanel* searchTextBackGround;
	wxPanel* hotKeyPanel;
	wxPanel* guidePanel;


	void GuideToUser();
	void CreateEnterArea();
	void CreateSearchArea();
	void CreateHotKeyArea();

	void OnChangedPageNoteBook(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnEnter(wxCommandEvent& event);
	void MainKeyDown(int keyCode);
	void OnKeyDown(wxKeyEvent& event);
	void OnGridKeyDown(wxKeyEvent& event);
	void OnGridTexting(wxCommandEvent& event);
	void EditCurrentCell(wxGridEvent& event);
	void OnCardMenu(wxCommandEvent& event);
	void OnShow(wxShowEvent& event);
	void OnKeyDownTextCltrToUpper(wxCommandEvent& event);
	void SaveFile();
	void ShowMessageClear();
	void DeleteSelectedRows();
	void SaveToList(wxTextCtrl** textCtrlList, int length, int& pos);
	void SearchOnList();
	void ModifyTextInput(wxTextCtrl* textCtrl);
	void ModifyTextInput(wxString& wxStr);
	void ModifyString(string& str);
	void ErrorMessageBox(int pos, string message);
	void MakeEnCodeText();
	void WriteHashCode(wxTextCtrl** textCtrlList, ulong& hashCode, wxString& wxStrCode);
	void SetDefaultColorForRow();
	void CastWxStringIntoString(wxString text, string& str);
	
	void OnSelectingGrid(wxGridRangeSelectEvent& event);
	void OnSelectedGrid(wxCommandEvent& event);
	void OnSelectedLabelGrid(wxCommandEvent& event);
	void OnSelectedCell(wxGridEvent& event);
	void SetModeDelete(bool state);


	bool IsWhiteSpaceAllText(wxTextCtrl* textCtrl);
	int CastWxStringToInt(wxTextCtrl* textCtrl);
	ulong CastWxStringToUlong(wxString wxStr);
	ulong CreateHashCode();
	ulong RandomNumber(ulong minNumber, ulong maxNumber);
	string EditCardCode(ulong number, int maxLengthCode);

	int GetMaxLength(int col);

	int count = 0;
	int rowChangedColor = -1;
	int numberRowIsFilled = 0;
	bool isModeDelete = false;
	bool canEdit = true;
	DECLARE_EVENT_TABLE();
public:
	ReaderCard(const wxString& title);
	void LoadData();
	void SetData(BSTree<CardReader>* cardReaders,
				CheckInput* checkInput);
};
const int CARD_MENU = 3;
const int SAVE_FILE = 2;
const int DefaultRows = 30;