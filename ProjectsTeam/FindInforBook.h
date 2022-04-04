#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include"CheckInput.h"
#include"SaveTextFile.h"
#include"LinearList.h"
#include"SortAlgorithm.h"
using std::string;
class FindInforBook:public wxFrame
{
private:
	//Backend
	SortAlgorithm<Title>* sort;
	CheckInput* checkInput;
	SaveTextFile<Title>* saveFile;
	Title* foundTitle = nullptr;
	Title** arr = nullptr;
	string* stateBook;
	//FontEnd
	wxGrid* grid;
	wxPanel* searchPanel;
	wxPanel* displayInforPanel;
	wxTextCtrl* searchEnterText;
	wxTextCtrl** displayText;
	wxTextCtrl* hideFocusText;
	wxStaticText* titleGridText;
	//Method
	void CreateDisplayArea();
	void DisplayInfor(wxString wxstr);
	void DisplayOnTable();
	void ClearAllOldData();
	void SaveFile();
	void LoadFile();
	void UndoTitleData(int index);
	void ChangeTitleData(int index,wxString data);
	void SetReadOnLyDisplayTable();

	bool CheckChangeData();
	bool CheckBookName(wxString text);
	bool CheckStateBook(wxString text);
	bool CheckISBN(wxString text);
	bool CheckPageNumber(wxString text);
	bool CheckAuthor(wxString text);
	bool CheckYearPublic(wxString text);
	bool CheckType(wxString text);
	bool CheckDuplicateISBN(wxString text);
	bool CheckDuplicateBookName(wxString text);

	void OnExitMenu(wxCommandEvent& event);
	void OnKeyDownTextCltrToUpper(wxCommandEvent& _rCommandEvent);
	void EditCurrentCell(wxGridEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnEnter(wxCommandEvent& event);
	void OnShow(wxShowEvent& event);

	int maxItem = 0;
	int length = 0;
	int foundBookIndex = 0;
public:
	FindInforBook(const wxString& title);
	~FindInforBook()
	{
		delete sort;
		delete checkInput;
		delete saveFile;
		delete[] stateBook;
		delete[]displayText;
	}
	DECLARE_EVENT_TABLE();
};

