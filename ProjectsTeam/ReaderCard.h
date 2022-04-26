#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include<wx/event.h>
#include<wx/notebook.h>
#include<iostream>
#include<String>
#include<math.h>
#include<time.h>
#include"BSTree.h"
#include"SaveTextFile.h"
#include"CheckInput.h"
typedef unsigned long long ulong;
using std::string;
using namespace DataStructure;
class ReaderCard :public wxFrame
{
private:

	//backend
	BSTree<CardReader>* cardReaderTree;
	CardReader* CreateCardReader(wxTextCtrl** textCtrlList, ulong cardCode);
	SaveTextFile<CardReader>* saveFile;
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

	void MoveDownToAnotherTextCtrl(wxTextCtrl** textCtrl, int length);
	void MoveUpToAnotherTextCtrl(wxTextCtrl** textCtrl, int length);
	void GuideToUser();
	void SetTextSize(wxStaticText& text, int size);
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
	void UpperWxString(wxString& wxStr);
	void WriteHashCode(wxTextCtrl** textCtrlList, ulong& hashCode, wxString& wxStrCode);
	void SetDefaultColorForRow();
	void CastWxStringIntoString(wxString text, string& str);
	
	void OnSelectingGrid(wxGridRangeSelectEvent& event);
	void OnSelectedGrid(wxCommandEvent& event);
	void OnSelectedLabelGrid(wxCommandEvent& event);
	void OnSelectedCell(wxGridEvent& event);
	void SetModeDelete(bool state);


	bool IsWhiteSpaceAllText(wxTextCtrl* textCtrl);
	bool IsWhiteSpaceAllText(wxString wxStr);
	bool IsWord(wxTextCtrl* textCtrl);
	bool IsWord(wxString wxStr);
	bool IsRightSex(wxString& wxStr);
	bool IsRightCodeState(int maxNum, int number);
	int CastWxStringToInt(wxTextCtrl* textCtrl);
	int CastWxStringToInt(wxString wxStr);
	ulong CastWxStringToUlong(wxString wxStr);
	ulong CreateHashCode();
	ulong RandomNumber(ulong minNumber, ulong maxNumber);
	string UpperText(string text);
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
	void SetCardReaders(BSTree<CardReader>* cardReaders);
};
const int CARD_MENU = 3;
const int SAVE_FILE = 2;
const int DefaultRows = 30;