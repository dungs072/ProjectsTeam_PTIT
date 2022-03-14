#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include<wx/event.h>
#include<wx/notebook.h>
#include<wx/time.h>
#include<iostream>
#include<String>
#include<math.h>

namespace Library
{
	class ReaderCard :public wxFrame
	{
	private:
		wxMenuBar* menuBar;
		wxMenu* file;
		std::string* stateText;
		wxNotebook* noteBook;
		wxTextCtrl** enterText;
		wxTextCtrl** enterText2;
		wxBoxSizer* mainHBox;
		wxGrid* grid;
		wxPanel* mainPanel;
		wxPanel* enterTextBackGround;
		wxPanel* insertTextBackGround;
		wxPanel* guidePanel;
		wxPanel* noteTableBackGround;
		void MoveDownToAnotherTextCtrl(wxTextCtrl** textCtrl, int length);
		void MoveUpToAnotherTextCtrl(wxTextCtrl** textCtrl, int length);
		void GuideToUser();
		void SetTextSize(wxStaticText& text, int size);
		void CreateEnterArea();
		void CreateInsertArea();
		void CreateNoteArea();
		void OnEnter(wxCommandEvent& event);
		void OnKeyDown(wxKeyEvent& event);
		void OnSearch(wxCommandEvent& event);
		void ShowMessageClear();
		void DeleteSelectedRows();
		void SaveToList(wxTextCtrl** textCtrlList, int length, int& pos);
		void InsertToList();
		void ModifyTextInput(wxTextCtrl* textCtrl);
		void ModifyTextInput(wxString& wxStr);
		void ModifyString(std::string& str);
		void ErrorMessageBox(int pos, std::string message);
		void MakeStateCodeText();
		void UpperWxString(wxTextCtrl* textCtrl);
		void UpperWxString(wxString& wxStr);
		void WriteHashCodeToCell(int pos, wxTextCtrl** textCtrlList);
		void WriteHashCodeToCell(int row);
		void EditCurrentCell(wxGridEvent& event);
		bool IsWhiteSpaceAllText(wxTextCtrl* textCtrl);
		bool IsWhiteSpaceAllText(wxString wxStr);
		bool IsWord(wxTextCtrl* textCtrl);
		bool IsWord(wxString wxStr);
		bool IsRightSex(wxTextCtrl* textCtrl);
		bool IsRightSex(wxString& wxStr);
		bool IsRightCodeState(int maxNum, int number);
		int CastWxStringToInt(wxTextCtrl* textCtrl);
		int CastWxStringToInt(wxString wxStr);
		long long CreateHashCode(wxTextCtrl** textCltrList);
		long long CreateHashCode(int row);
		long long HashCode(std::string str);
		std::string UpperText(std::string text);
		std::string EditCardCode(long long number, int maxLengthCode);
		int count = 0;
		DECLARE_EVENT_TABLE();
	public:
		ReaderCard(const wxString& title);
	};
	const int LOOKUP_ID = 1;
	const int DefaultRows = 25;

}

