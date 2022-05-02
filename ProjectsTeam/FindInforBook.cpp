#include "FindInforBook.h"
FindInforBook::FindInforBook(const wxString& title) :
	wxFrame(NULL, -1, title, wxDefaultPosition, wxSize(1280, 680))
{
	//for sorting
	sort = new SortAlgorithm<Title>();
	sort->Compare = [](Title* t1, Title* t2)
	{
		if (t1->GetType() > t2->GetType()) { return 1; }
		else if (t1->GetType() < t2->GetType()) { return -1; }
		else
		{
			if (t1->GetBookName() > t2->GetBookName()) { return 1; }
			else if (t1->GetBookName() < t2->GetBookName()) { return -1; }
			else return 0;
		}
	};
	
	//Create color
	wxColour lightYellow, lightBlue, red;
	lightYellow.Set(wxT("#E0EBB7"));
	lightBlue.Set(wxT("#7FB1E3"));
	red.Set(wxT("#F74A4A"));
	//create panel
	wxPanel* mainPanel = new wxPanel(this, -1);
	searchPanel = new wxPanel(mainPanel, -1, wxPoint(-1, -1), wxSize(400, 550));
	//Create static text
	titleGridText = new wxStaticText(mainPanel, -1, wxT("MUC SACH CUA: ")
		, wxPoint(-1, -1), wxSize(400, 30), wxALIGN_CENTER);
	checkInput->SetTextSize(titleGridText, 15);
	hideFocusText = new wxTextCtrl(mainPanel,-1,wxT(""),wxPoint(-1,-1),wxSize(10,10));
	hideFocusText->Hide();
	//Create grid
	grid = new wxGrid(mainPanel, -1, wxPoint(-1, -1), wxSize(350, 500));
	grid->CreateGrid(30, 2);
	grid->SetColSize(0, 100);
	grid->SetColSize(1, 180);
	grid->SetColLabelValue(0, wxT("MA SACH"));
	grid->SetColLabelValue(1, wxT("TRANG THAI SACH"));
	grid->SetRowLabelSize(50);
	grid->DisableDragColSize();
	grid->DisableDragRowSize();
	//Create button
	wxButton* exitMenuButton = new wxButton(mainPanel, -1, 
		wxT("EXIT MENU"), wxPoint(10, 600), wxSize(100, 25));
	//Create boxsizer
	wxBoxSizer* mainHBox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* vGridBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vRightBox = new wxBoxSizer(wxVERTICAL);
	//Set box sizer
	vGridBox->Add(titleGridText, 0, wxALIGN_CENTER | wxTOP, 20);
	vGridBox->Add(grid, 0, wxTOP|wxLEFT, 30);
	mainHBox->Add(vGridBox, 0, wxLEFT, 100);
	vRightBox->Add(searchPanel, 0, wxTOP, 50);
	mainHBox->Add(vRightBox, 0, wxLEFT, 200);
	mainPanel->SetSizer(mainHBox);

	//Register event
	grid->Bind(wxEVT_GRID_CELL_CHANGED, &FindInforBook::EditCurrentCell, this);
	Bind(wxEVT_TEXT_ENTER, &FindInforBook::OnEnter, this);
	Bind(wxEVT_SHOW, &FindInforBook::OnShow, this);
	exitMenuButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &FindInforBook::OnExitMenu, this);

	grid->Bind(wxEVT_GRID_RANGE_SELECTING, &FindInforBook::OnSelectingGrid, this);
	grid->Bind(wxEVT_GRID_SELECT_CELL, &FindInforBook::OnSelectedGrid, this);
	grid->Bind(wxEVT_GRID_LABEL_LEFT_CLICK, &FindInforBook::OnSelectedLabelGrid, this);
	grid->Bind(wxEVT_CHAR_HOOK, &FindInforBook::OnGridKeyDown, this);
	grid->Bind(wxEVT_GRID_SELECT_CELL, &FindInforBook::OnSelectedCell, this);
	grid->Bind(wxEVT_TEXT, &FindInforBook::OnGridTexting, this);
	//grid->Bind(wxEVT_GRID_CELL_CHANGING, &FindInforBook::OnCellChanging, this);
	//Set Color
	searchPanel->SetBackgroundColour(lightYellow);
	titleGridText->SetBackgroundColour(lightBlue);
	exitMenuButton->SetBackgroundColour(red);
	CreateDisplayArea();
	Centre();
}
void FindInforBook::CreateDisplayArea()
{
	wxColor displayColor, lightRed, midBlue;
	lightRed.Set(wxT("#FA8E8E"));
	displayColor.Set("#a7d1c1");
	midBlue.Set("#d4f2ff");
	wxStaticText* searchText = new wxStaticText(searchPanel, -1,
		wxT("TIM KIEM"), wxPoint(150, 10), wxSize(100, 20), wxALIGN_CENTER);
	checkInput->SetTextSize(searchText, 10);
	wxStaticText* bookSearchText = new wxStaticText(searchPanel, -1,
		wxT("TEN DAU SACH:  "), wxPoint(10, 80), wxSize(100, 15));
	//checkInput->SetTextSize(bookSearchText, 10);
	searchEnterText = new wxTextCtrl(searchPanel, -1, wxT(""),
		wxPoint(130, 75), wxSize(250, 25), wxTE_CENTER | wxTE_PROCESS_ENTER);
	searchEnterText->SetMaxLength(24);
	displayInforPanel = new wxPanel(searchPanel, -1, wxPoint(10, 150), wxSize(380, 390));

	wxStaticText** nameEnterText = new wxStaticText * [6];
	nameEnterText[0] = new wxStaticText(displayInforPanel, -1,
		wxT("ISBN:"), wxPoint(10, 30), wxSize(100, 15));
	nameEnterText[1] = new wxStaticText(displayInforPanel, -1,
		wxT("TEN SACH:"), wxPoint(10, 80), wxSize(100, 15));
	nameEnterText[2] = new wxStaticText(displayInforPanel, -1,
		wxT("SO TRANG:"), wxPoint(10, 130), wxSize(100, 15));
	nameEnterText[3] = new wxStaticText(displayInforPanel, -1,
		wxT("TAC GIA:"), wxPoint(10, 180), wxSize(100, 15));
	nameEnterText[4] = new wxStaticText(displayInforPanel, -1,
		wxT("NXB:"), wxPoint(10, 230), wxSize(100, 15));
	nameEnterText[5] = new wxStaticText(displayInforPanel, -1,
		wxT("THE LOAI:"), wxPoint(10, 280), wxSize(100, 15));
	displayText = new wxTextCtrl * [6];
	for (int i = 0; i < 6; i++)
	{
		displayText[i] = new wxTextCtrl(displayInforPanel, -1,
			wxT(""), wxPoint(10, 50 + i * 50), wxSize(360, 25), wxTE_CENTER|wxTE_PROCESS_ENTER);
		displayText[i]->SetEditable(false);
		displayText[i]->SetBackgroundColour(midBlue);
		displayText[i]->Connect(wxID_ANY, wxEVT_COMMAND_TEXT_UPDATED,
			(wxObjectEventFunction)&FindInforBook::OnKeyDownTextCltrToUpper);
	}
	displayText[0]->SetMaxLength(4);
	displayText[1]->SetMaxLength(24);
	displayText[2]->SetMaxLength(6);
	displayText[3]->SetMaxLength(17);
	displayText[4]->SetMaxLength(4);
	displayText[5]->SetMaxLength(11);
	//register event
	searchEnterText->Connect(wxID_ANY, wxEVT_COMMAND_TEXT_UPDATED,
		(wxObjectEventFunction)&FindInforBook::OnKeyDownTextCltrToUpper);
	//set color
	searchText->SetBackgroundColour(lightRed);
	displayInforPanel->SetBackgroundColour(displayColor);
}
void FindInforBook::OnKeyDownTextCltrToUpper(wxCommandEvent& _rCommandEvent)
{
	wxTextCtrl* pTextCtrl = dynamic_cast<wxTextCtrl*>(_rCommandEvent.GetEventObject());
	if (pTextCtrl != NULL)
	{
		if (!pTextCtrl->IsModified())
			return;
		long insertionPoint = pTextCtrl->GetInsertionPoint();
		pTextCtrl->ChangeValue(pTextCtrl->GetValue().Upper());
		pTextCtrl->SetInsertionPoint(insertionPoint);
	}
	_rCommandEvent.Skip();
}
void FindInforBook::EditCurrentCell(wxGridEvent& event)
{
	int row = grid->GetGridCursorRow();
	int col = grid->GetGridCursorCol();
	wxString wxOldText = event.GetString();
	if (wxOldText == wxT(""))
	{
		checkInput->ErrorMessageBox("Khong the chinh chua o nay ");
		grid->SetCellValue(row, col, wxOldText);
		return;
	}
	wxString wxNewText = grid->GetCellValue(row, col);
	//main error
	if (checkInput->IsWhiteSpaceAllText(wxNewText))
	{
		checkInput->ErrorMessageBox("Khong duoc bo trong ");
		grid->SetCellValue(row, col, wxOldText);
		return;
	}
	event.Skip();
}
void FindInforBook::EditData(int row, int col, int index)
{
	string bookCode = string(grid->GetCellValue(row, 0).mb_str());
	if (bookCode == "")
	{
		checkInput->ErrorMessageBox("Khong the chinh sua o nay ");
		grid->SetCellValue(row, col, wxT(""));
		return;
	}
	Book* book = &(foundTitle->GetListBook()->FindSinglyNode(bookCode)->data);
	if (book->GetState() == 1)
	{
		checkInput->ErrorMessageBox("SACH DANG MUON KHONG THE CHINH SUA");
		grid->SetCellValue(row, col, checkInput->GetBookState(1));
		return;
	}
	else
	{
		book->SetState(index);
	}
}
void FindInforBook::OnEnter(wxCommandEvent& WXUNUSED(event))
{
	if (searchEnterText->HasFocus())
	{
		if (checkInput->IsWhiteSpaceAllText(searchEnterText->GetValue()))
		{
			checkInput->ErrorMessageBox("KHONG DUOC BO TRONG O NHAP");
			searchEnterText->SetFocus();
			return;
		}

		wxString myWxStr = searchEnterText->GetValue();
		checkInput->ModifyTextInput(myWxStr);
		searchEnterText->SetValue(myWxStr);
		myWxStr = searchEnterText->GetValue();
		if (!CheckBookName(myWxStr))
		{
			checkInput->ErrorMessageBox("LOI TEN SACH");
			
			SetReadOnLyDisplayTable();
			searchEnterText->SetFocus();
			return;
		}
		//Set can edit info
		for (int i = 0; i < 6; i++)
		{
			displayText[i]->SetEditable(true);
		}
		titleGridText->SetLabel(wxT("MUC SACH CUA: ") + searchEnterText->GetValue());
		DisplayInfor(myWxStr);
	}
	else
	{
		bool isBlanket = false;
		for (int i = 0; i < 6; i++)
		{
			wxString tempwxstr = displayText[i]->GetValue();
			checkInput->ModifyTextInput(tempwxstr);
			if (checkInput->IsWhiteSpaceAllText(tempwxstr))
			{
				isBlanket = true;
				UndoTitleData(i);
			}
		}
		if (isBlanket)
		{
			checkInput->ErrorMessageBox("KHONG DUOC BO TRONG");
			return;
		}
		if (displayText[0]->HasFocus())
		{
			wxString tempwxstr = displayText[0]->GetValue();
			checkInput->ModifyTextInput(tempwxstr);
			if (checkInput->IsWhiteSpaceAllText(tempwxstr))
			{
				checkInput->ErrorMessageBox("KHONG DUOC BO TRONG");
				UndoTitleData(0);
				return;
			}
			if (!CheckISBN(tempwxstr))
			{
				checkInput->ErrorMessageBox("LOI ISBN");
				UndoTitleData(0);
				return;
			}
			if (CheckDuplicateISBN(tempwxstr))
			{
				checkInput->ErrorMessageBox("LOI TRUNG ISBN CO TRONG DANH SACH");
				UndoTitleData(0);
				return;
			}
			if (!CheckChangeData()) 
			{ 
				UndoTitleData(0);
				return; 
			}
			displayText[0]->SetValue(tempwxstr);
			ChangeTitleData(0, tempwxstr);
		}
		else if (displayText[1]->HasFocus())
		{
			wxString tempwxstr = displayText[1]->GetValue();
			checkInput->ModifyTextInput(tempwxstr);
			if (checkInput->IsWhiteSpaceAllText(tempwxstr))
			{
				checkInput->ErrorMessageBox("KHONG DUOC BO TRONG");
				UndoTitleData(1);
				return;
			}
			if (!CheckBookName(tempwxstr))
			{
				checkInput->ErrorMessageBox("LOI TEN SACH");
				UndoTitleData(1);
				return;
			}
			if (CheckDuplicateBookName(tempwxstr))
			{
				checkInput->ErrorMessageBox("LOI TRUNG TEN SACH CO TRONG DANH SACH");
				UndoTitleData(1);
				return;
			}
			if (!CheckChangeData()) 
			{
				UndoTitleData(1);
				return; 
			}
			displayText[1]->SetValue(tempwxstr);
			ChangeTitleData(1, tempwxstr);
		}
		else if (displayText[2]->HasFocus())
		{
			wxString tempwxstr = displayText[2]->GetValue();
			checkInput->ModifyTextInput(tempwxstr);
			if (checkInput->IsWhiteSpaceAllText(tempwxstr))
			{
				checkInput->ErrorMessageBox("KHONG DUOC BO TRONG");
				UndoTitleData(2);
				return;
			}
			if (!CheckPageNumber(tempwxstr))
			{
				checkInput->ErrorMessageBox("LOI SO TRANG");
				UndoTitleData(2);
				return;
			}
			if (!CheckChangeData()) 
			{
				UndoTitleData(2);
				return;
			}
			displayText[2]->SetValue(tempwxstr);
			ChangeTitleData(2, tempwxstr);
		}
		else if (displayText[3]->HasFocus())
		{
			wxString tempwxstr = displayText[3]->GetValue();
			checkInput->ModifyTextInput(tempwxstr);
			if (checkInput->IsWhiteSpaceAllText(tempwxstr))
			{
				checkInput->ErrorMessageBox("KHONG DUOC BO TRONG");
				UndoTitleData(3);
				return;
			}
			if (!CheckAuthor(tempwxstr))
			{
				checkInput->ErrorMessageBox("LOI TEN TAC GIA");
				UndoTitleData(3);
				return;
			}
			if (!CheckChangeData())
			{
				UndoTitleData(3);
				return; 
			}
			displayText[3]->SetValue(tempwxstr);
			ChangeTitleData(3, tempwxstr);
		}
		else if (displayText[4]->HasFocus())
		{
			wxString tempwxstr = displayText[4]->GetValue();
			checkInput->ModifyTextInput(tempwxstr);
			if (checkInput->IsWhiteSpaceAllText(tempwxstr))
			{
				checkInput->ErrorMessageBox("KHONG DUOC BO TRONG");
				UndoTitleData(4);
				return;
			}
			if (!CheckYearPublic(tempwxstr))
			{
				checkInput->ErrorMessageBox("LOI NAM XUAT BAN");
				UndoTitleData(4);
				return;
			}
			if (!CheckChangeData()) 
			{
				UndoTitleData(4);
				return;
			}
			displayText[4]->SetValue(tempwxstr);
			ChangeTitleData(4, tempwxstr);
		}
		else if (displayText[5]->HasFocus())
		{
			wxString tempwxstr = displayText[5]->GetValue();
			checkInput->ModifyTextInput(tempwxstr);
			if (checkInput->IsWhiteSpaceAllText(tempwxstr))
			{
				checkInput->ErrorMessageBox("KHONG DUOC BO TRONG");
				UndoTitleData(5);
				return;
			}
			if (!CheckType(tempwxstr))
			{
				checkInput->ErrorMessageBox("LOI THE LOAI");
				UndoTitleData(5);
				return;
			}
			if (!CheckChangeData())
			{
				UndoTitleData(5);
				return;
			}
			displayText[5]->SetValue(tempwxstr);
			ChangeTitleData(5, tempwxstr);
		}
	}
	hideFocusText->SetFocus();
	
}
void FindInforBook::UndoTitleData(int index)
{
	if (foundTitle == nullptr) { return; }
	if (index == 0)
	{
		displayText[index]->SetValue(foundTitle->GetISBN());
	}
	else if (index == 1)
	{
		displayText[index]->SetValue(foundTitle->GetBookName());
	}
	else if (index == 2)
	{
		wxString pageNumber = checkInput->CastIntToString(foundTitle->GetPageNumber());
		displayText[index]->SetValue(pageNumber);
	}
	else if (index == 3)
	{
		displayText[index]->SetValue(foundTitle->GetAuthor());
	}
	else if (index == 4)
	{
		wxString yearPublic = checkInput->CastIntToString(foundTitle->GetPublicYear());
		displayText[index]->SetValue(yearPublic);
	}
	else if (index == 5)
	{
		displayText[index]->SetValue(foundTitle->GetType());
	}
}
void FindInforBook::ChangeTitleData(int index,wxString wxData)
{
	string data = string(wxData.mb_str());
	if (index == 0)
	{
		int i = 0;
		foundTitle->SetISBN(data);
		SinglyNode<Book>* tempBook = foundTitle->GetListBook()->First();
		while (tempBook != nullptr)
		{
			string tempData = tempBook->data.GetBookCode();
			for (int i = 0; i < 4; i++)
			{
				tempData[i] = data[i];
			}
			tempBook->data.SetBookCode(tempData);
			grid->SetCellValue(i, 0, tempBook->data.GetBookCode());
			i++;
			tempBook = tempBook->next;
		}
		//SaveFile();
	}
	else if (index == 1)
	{
		foundTitle->SetBookName(data);
		sort->QuickSort(arr, 0, length);
		//SaveFile();
	}
	else if (index == 2)
	{
		int numberPage = checkInput->CastStringToNumber(data);
		foundTitle->SetPageNumber(numberPage);
		//SaveFile();
	}
	else if (index == 3)
	{
		foundTitle->SetAuthor(data);
		//SaveFile();
	}
	else if (index == 4)
	{
		int yearPublic = checkInput->CastStringToNumber(data);
		foundTitle->SetPublicYear(yearPublic);
		//SaveFile();
	}
	else if (index == 5)
	{
		foundTitle->SetType(data);
		sort->QuickSort(arr, 0, length);
		//SaveFile();
	}
}
void FindInforBook::OnGridKeyDown(wxKeyEvent& event)
{
	int keyCode = event.GetKeyCode();
	int col = grid->GetGridCursorCol();
	int row = grid->GetGridCursorRow();
	if (!canEdit)
	{
		if (checkInput->HasRightEntering(keyCode, false))
		{
			event.Skip();
		}
		return;
	}
	if (col == 1)
	{

		if (checkInput->HasInRangeNumber(keyCode,0,2) || checkInput->HasRightEntering(keyCode, true))
		{
			if (keyCode != '1')
			{
				event.Skip();
				if (checkInput->HasInRangeNumber(keyCode, 0, 2))
				{
					int i = keyCode - '0';
					grid->SetCellValue(row, col, wxT(""));
					grid->SetCellValue(row, col, checkInput->GetBookState(i));
					EditData(row, col, i);
				}
			}
		}
	}
}
void FindInforBook::OnKeyDown(wxKeyEvent& event)
{
	event.StopPropagation();
	if (event.GetKeyCode() == WXK_F2)
	{
		SaveFile();
		event.Skip();
	}
	int keyCode = event.GetKeyCode();
	if (displayText[0]->HasFocus())
	{
		if ((keyCode >= 'a' && keyCode <= 'z') ||
			(keyCode >= 'A' && keyCode <= 'Z') ||
			keyCode == WXK_BACK || keyCode == WXK_RETURN ||
			keyCode == WXK_LEFT || keyCode == WXK_RIGHT )
		{
			event.Skip();
		}
	}
	else if (displayText[3]->HasFocus()||displayText[5]->HasFocus())
	{
		if ((keyCode >= 'a' && keyCode <= 'z') ||
			(keyCode>='A'&&keyCode<='Z')||
			keyCode == WXK_BACK || keyCode == WXK_RETURN ||
			keyCode == WXK_LEFT || keyCode == WXK_RIGHT || keyCode == ' ')
		{
			event.Skip();
		}
	}
	else if (displayText[1]->HasFocus())
	{
		if ((keyCode >= 'a' && keyCode <= 'z') ||
			(keyCode >= 'A' && keyCode <= 'Z') ||
			(keyCode>='0'&&keyCode<='9')||
			keyCode == WXK_BACK || keyCode == WXK_RETURN ||
			keyCode == WXK_LEFT || keyCode == WXK_RIGHT || keyCode == ' ')
		{
			event.Skip();
		}
	}
	else if (displayText[2]->HasFocus()||displayText[4]->HasFocus())
	{
		if ((keyCode >= '0' && keyCode <= '9') ||
			keyCode == WXK_BACK || keyCode == WXK_RETURN ||
			keyCode == WXK_LEFT || keyCode == WXK_RIGHT)
		{
			event.Skip();
		}
	}
	else
	{
		event.Skip();
	}
}
void FindInforBook::SaveFile()
{
	ISaveFile* isaveFile = dynamic_cast<ISaveFile*>(this->GetParent());
	isaveFile->SaveFile();
}
void FindInforBook::LoadData()
{
	length = titleList->GetList()->Length();
	arr = titleList->GetList()->ToArray();
}
void FindInforBook::OnExitMenu(wxCommandEvent& WXUNUSED(event))
{
	this->Hide();
	this->GetParent()->Show();
}
void FindInforBook::OnShow(wxShowEvent& event)
{
	if (event.IsShown())
	{
		LoadData();
		ClearAllOldData();
		SetReadOnLyDisplayTable();
		maxItem = 0;
	}
	event.Skip();
}
void FindInforBook::SetReadOnLyDisplayTable()
{
	for (int i = 0; i < 6; i++)
	{
		displayText[i]->SetEditable(false);
	}
}
void FindInforBook::DisplayInfor(wxString wxstr)
{
	string bookName = string(wxstr.mb_str());
	for (int i = 0; i < length; i++)
	{
		if (arr[i]->GetBookName() == bookName)
		{
			foundTitle = arr[i];
			foundBookIndex = i;
			break;
		}
		else
		{
			foundTitle = nullptr;
		}
	}
	if (foundTitle == nullptr)
	{
		checkInput->ErrorMessageBox("KHONG TIM THAY DAU SACH YEU CAU");
		ClearAllOldData();
		SetReadOnLyDisplayTable();
		return;
	}
	ClearAllOldData();
	displayText[0]->SetLabel(foundTitle->GetISBN());
	displayText[1]->SetLabel(foundTitle->GetBookName());
	displayText[2]->SetLabel(checkInput->CastIntToString(foundTitle->GetPageNumber()));
	displayText[3]->SetLabel(foundTitle->GetAuthor());
	displayText[4]->SetLabel(checkInput->CastIntToString(foundTitle->GetPublicYear()));
	displayText[5]->SetLabel(foundTitle->GetType());

	DisplayOnTable();
}
void FindInforBook::DisplayOnTable()
{
	if (foundTitle == nullptr) { return; }
	
	maxItem = foundTitle->GetListBook()->Length();
	if (maxItem + 1 > grid->GetNumberRows())
	{
		grid->AppendRows(maxItem - grid->GetNumberRows() + 1);
	}
	SinglyNode<Book>* tempBook = foundTitle->GetListBook()->First();
	int i = 0;
	while (tempBook != nullptr)
	{
		int index = tempBook->data.GetState();
		grid->SetCellValue(i, 0, tempBook->data.GetBookCode());
		grid->SetCellValue(i, 1, checkInput->GetBookState(index));
		grid->SetReadOnly(i, 0);
		for (int k = 0; k < 2; k++)
		{
			grid->SetCellAlignment(i, k, wxALIGN_CENTER, wxALIGN_CENTER);
		}
		i++;
		tempBook = tempBook->next;
	}
}
void FindInforBook::ClearAllOldData()
{
	searchEnterText->Clear();
	for (int i = 0; i < 6; i++)
	{
		displayText[i]->SetLabel("");
	}
	for (int i = 0; i < maxItem; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (j == 0)
			{
				grid->SetReadOnly(i, j, false);
			}
			grid->SetCellValue(i,j,"");
		}
	}
	if (maxItem > 30)
	{
		grid->DeleteRows(30, maxItem - 30);
	}
}
bool FindInforBook::CheckBookName(wxString text)
{
	return checkInput->HasNumberAndAlphabet(text);
}
bool FindInforBook::CheckStateBook(wxString text)
{
	checkInput->ModifyTextInput(text);
	if (!checkInput->IsNumber(text)) { return false; }
	int number = checkInput->CastWxStringToInt(text);
	return checkInput->IsInRangeNumber(0, 2, number);
}
bool FindInforBook::CheckISBN(wxString text)
{
	//ISBN CO 4 CHARS AND ALL IS CHAR NOT HAVE NUMBER;
	if (!checkInput->IsAlphabet(text)) { return false; }
	string textstr = string(text.mbc_str());
	return textstr.length() == 4;
}
bool FindInforBook::CheckPageNumber(wxString text)
{
	//page number has 6 number;
	if (!checkInput->IsNumber(text)) { return false; }
	string textstr = string(text.mbc_str());
	return textstr.length() <= 6 && textstr.length() > 0;
}
bool FindInforBook::CheckAuthor(wxString text)
{
	return checkInput->IsWord(text);
}
bool FindInforBook::CheckYearPublic(wxString text)
{
	if (!checkInput->IsNumber(text)) { return false; }
	time_t current = time(0);
	tm* ltm = localtime(&current);
	int currentYear = ltm->tm_year + 1900;
	int yearInput = checkInput->CastWxStringToInt(text);
	//wxMessageBox(wxString::Format("current year: %i and year input: %i", currentYear, yearInput));
	return yearInput <= currentYear;
}
bool FindInforBook::CheckType(wxString text)
{
	return checkInput->IsWord(text);
}
bool FindInforBook::CheckDuplicateISBN(wxString text)
{
	for (int i = 0; i < length; i++)
	{
		if (foundBookIndex == i)
		{
			continue;
		}
		if (arr[i]->GetISBN() == text)
		{
			return true;
		}
	}
	return false;
}
bool FindInforBook::CheckDuplicateBookName(wxString text)
{
	for (int i = 0; i < length; i++)
	{
		if (foundBookIndex == i)
		{
			continue;
		}
		if (arr[i]->GetBookName() == text)
		{
			return true;
		}
	}
	return false;
}
bool FindInforBook::CheckChangeData()
{
	wxMessageDialog* dialog = new wxMessageDialog(NULL,
		wxT("BAN CO CHAC MUON THAY DOI DU LIEU KHONG?"),
		wxT("Warning"),
		wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
	bool state = dialog->ShowModal() == wxID_YES;
	delete dialog;
	return state;
}
void FindInforBook::OnSelectingGrid(wxGridRangeSelectEvent& WXUNUSED(event))
{
	if (grid->IsSelection())
	{
		grid->ClearSelection();
	}
}
void FindInforBook::OnSelectedGrid(wxCommandEvent& WXUNUSED(event))
{
	if (grid->IsSelection())
	{
		grid->ClearSelection();
	}
}
void FindInforBook::OnSelectedLabelGrid(wxCommandEvent& WXUNUSED(event))
{
	if (grid->IsSelection())
	{
		grid->ClearSelection();
	}
}
void FindInforBook::OnSelectedCell(wxGridEvent& event)
{
	int row = event.GetRow();
	int col = event.GetCol();
	grid->ClearSelection();
	canEdit = true;
	event.Skip();
}
void FindInforBook::OnGridTexting(wxCommandEvent& event)
{
	int row = grid->GetGridCursorRow();
	int col = grid->GetGridCursorCol();
	event.SetString(grid->GetCellValue(row, col));
	wxString tempStr = event.GetString();
	int maxLength = GetMaxLength(col);
	if (tempStr.Length() >= maxLength)
	{
		canEdit = false;
	}
	else
	{
		canEdit = true;
	}
	event.Skip();
}
int FindInforBook::GetMaxLength(int col)
{
	if (col == 1)
	{
		return 1;
	}
	return -1;
}
BEGIN_EVENT_TABLE(FindInforBook, wxFrame)
EVT_CHAR_HOOK(FindInforBook::OnKeyDown)
END_EVENT_TABLE()
