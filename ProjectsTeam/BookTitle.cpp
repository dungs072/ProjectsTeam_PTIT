#include "BookTitle.h"
BookTitle::BookTitle(const wxString& title) : wxFrame(NULL, -1,
	title, wxDefaultPosition, wxSize(1280, 680))
{
	//create color;
	wxColour lightYellow, lightBlue, red, middleYellow;
	middleYellow.Set("#ECFF82");
	lightYellow.Set(wxT("#E0EBB7"));
	lightBlue.Set(wxT("#7FB1E3"));
	red.Set(wxT("#F74A4A"));
	//create panel
	wxPanel* mainPanel = new wxPanel(this, -1);
	enterPanel = new wxPanel(mainPanel, -1,
		wxDefaultPosition, wxSize(375, 400));
	takeNotePanel = new wxPanel(mainPanel, -1,
		wxDefaultPosition, wxSize(375, 220));
	wxPanel* keyNotePanel = new wxPanel(mainPanel, -1,
		wxDefaultPosition, wxSize(570, 30));
	//Create Button
	wxButton* exitMenu = new wxButton(mainPanel, -1,
		wxT("EXIT MENU"), wxPoint(10, 600), wxSize(100, 30));

	//create wxStatic Text
	wxStaticText* gridTitle = new wxStaticText(mainPanel, -1,
		wxT("DANH SACH DAU SACH"), wxPoint(-1, -1), wxSize(400, 40), wxALIGN_CENTER);
	checkInput->SetTextSize(gridTitle, 20);

	//create BoxSizer
	wxBoxSizer* vGridBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vRightBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vEnterBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* mainHBox = new wxBoxSizer(wxHORIZONTAL);
	//create Grid
	grid = new wxGrid(mainPanel, -1, wxPoint(-1, -1), wxSize(745, 500));
	grid->CreateGrid(30, 6);
	grid->SetColLabelValue(0, wxT("ISBN"));
	grid->SetColLabelValue(1, wxT("TEN SACH"));
	grid->SetColLabelValue(2, wxT("SO TR"));
	grid->SetColLabelValue(3, wxT("TAC GIA"));
	grid->SetColLabelValue(4, wxT("NXB"));
	grid->SetColLabelValue(5, wxT("THE LOAI"));
	for (int i = 0; i < 6; i++)
	{
		if (i == 0 || i == 2 || i == 4) { grid->SetColSize(i, 50); continue; }
		if (i == 1) { grid->SetColSize(i, 200); continue; }
		grid->SetColSize(i, 164);
	}
	grid->SetRowLabelSize(50);
	grid->DisableDragColSize();
	grid->DisableDragRowSize();
	grid->SetSelectionMode(wxGrid::wxGridSelectionModes::wxGridSelectRows);
	//Set sizer
	vGridBox->Add(gridTitle, 0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 20);
	vGridBox->Add(grid, 0, wxLEFT | wxTOP, 20);
	vGridBox->Add(keyNotePanel, 0, wxTOP | wxALIGN_CENTER, 10);
	vRightBox->Add(enterPanel, 0, wxLEFT | wxTOP, 10);
	vRightBox->Add(takeNotePanel, 0, wxLEFT | wxTOP, 10);
	mainHBox->Add(vGridBox, 0, wxLEFT, 30);
	mainHBox->Add(vRightBox);
	mainPanel->SetSizer(mainHBox);

	//Create areas;
	CreateEnterArea(enterPanel);
	CreateTakeNoteArea(takeNotePanel);
	CreateKeyNoteArea(keyNotePanel);

	//Register event
	grid->Bind(wxEVT_GRID_RANGE_SELECTING, &BookTitle::OnSelectingGrid, this);
	grid->Bind(wxEVT_GRID_SELECT_CELL, &BookTitle::OnSelectedGrid, this);
	grid->Bind(wxEVT_GRID_LABEL_LEFT_CLICK, &BookTitle::OnSelectedLabelGrid, this);
	grid->Bind(wxEVT_GRID_CELL_CHANGED, &BookTitle::EditCurrentCell, this);
	grid->Bind(wxEVT_CHAR_HOOK, &BookTitle::OnGridKeyDown, this);
	grid->Bind(wxEVT_GRID_SELECT_CELL, &BookTitle::OnSelectedCell, this);
	grid->Bind(wxEVT_TEXT, &BookTitle::OnGridTexting, this);

	exitMenu->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &BookTitle::OnExitMenu, this);
	Bind(wxEVT_TEXT_ENTER, &BookTitle::OnEnter, this);
	Bind(wxEVT_SHOW, &BookTitle::OnShow, this);
	//Set Color
	gridTitle->SetBackgroundColour(lightBlue);
	enterPanel->SetBackgroundColour(lightYellow);
	takeNotePanel->SetBackgroundColour(middleYellow);
	keyNotePanel->SetBackgroundColour(lightYellow);
	exitMenu->SetBackgroundColour(red);
	Centre();
}

void BookTitle::CreateEnterArea(wxPanel* enterPanel)
{
	wxColor lightRed, lightBlue;
	lightRed.Set(wxT("#FA8E8E"));
	lightBlue.Set(wxT("#9AD6E6"));
	wxStaticText* enterTitle = new wxStaticText(enterPanel, -1,
		wxT("CAP NHAT DAU SACH"), wxPoint(90, 20), wxSize(200, 30), wxALIGN_CENTER);
	checkInput->SetTextSize(enterTitle, 15);
	wxStaticText** nameEnterText = new wxStaticText * [6];
	enterText = new wxTextCtrl * [6];

	nameEnterText[0] = new wxStaticText(enterPanel, -1,
		wxT("ISBN:"), wxPoint(37, 70), wxSize(100, 15));
	nameEnterText[1] = new wxStaticText(enterPanel, -1,
		wxT("TEN SACH:"), wxPoint(37, 120), wxSize(100, 15));
	nameEnterText[2] = new wxStaticText(enterPanel, -1,
		wxT("SO TRANG:"), wxPoint(37, 170), wxSize(100, 15));
	nameEnterText[3] = new wxStaticText(enterPanel, -1,
		wxT("TAC GIA:"), wxPoint(37, 220), wxSize(100, 15));
	nameEnterText[4] = new wxStaticText(enterPanel, -1,
		wxT("NXB:"), wxPoint(37, 270), wxSize(100, 15));
	nameEnterText[5] = new wxStaticText(enterPanel, -1,
		wxT("THE LOAI:"), wxPoint(37, 320), wxSize(100, 15));
	wxStaticText* limitInput = new wxStaticText(enterPanel, -1,
		wxT("GIOI HAN NHAP: 100 DAU SACH"), wxPoint(100, 375), wxSize(200, 15));
	for (int i = 0; i < 6; i++)
	{
		enterText[i] = new wxTextCtrl(enterPanel, -1,
			wxT(""), wxPoint(37, 90 + i * 50), wxSize(300, 25), wxTE_CENTER
			| wxTE_PROCESS_ENTER | wxTE_CENTRE);
		enterText[i]->SetBackgroundColour(lightBlue);
		enterText[i]->Connect(wxID_ANY, wxEVT_COMMAND_TEXT_UPDATED,
			(wxObjectEventFunction)&BookTitle::OnKeyDownTextCltrToUpper);
	}
	enterText[0]->SetMaxLength(4);
	enterText[1]->SetMaxLength(24);
	enterText[2]->SetMaxLength(6);
	enterText[3]->SetMaxLength(17);
	enterText[4]->SetMaxLength(4);
	enterText[5]->SetMaxLength(11);
	enterTitle->SetBackgroundColour(lightRed);
}
void BookTitle::CreateTakeNoteArea(wxPanel* takeNotePanel)
{
	wxColor lightYellow, orange;
	lightYellow.Set("#E9F0C9");
	orange.Set(wxT("#FFAB03"));
	wxPanel* foreGroundPanel = new wxPanel(takeNotePanel, -1, wxPoint(10, 10), wxSize(355, 200));
	wxStaticText* titleTakeNoteText = new wxStaticText(foreGroundPanel, -1,
		wxT("GUIDES"), wxPoint(125, 5), wxSize(100, 15), wxALIGN_CENTER);

	wxStaticText* ISBNText = new wxStaticText(foreGroundPanel, -1,
		wxT("ISBN"), wxPoint(10, 30), wxSize(100, 30));
	wxStaticText* ISBNInfor = new wxStaticText(foreGroundPanel, -1,
		wxT(": TOI DA 4 KI TU, CHI LAY KI TU CHU"), wxPoint(80, 30), wxSize(300, 30));

	wxStaticText* bookNameText = new wxStaticText(foreGroundPanel, -1,
		wxT("TEN SACH"), wxPoint(10, 60), wxSize(100, 30));
	wxStaticText* bookNameInfor = new wxStaticText(foreGroundPanel, -1,
		wxT(": TOI DA 24 KI TU, GOM KI TU CHU VA SO"), wxPoint(80, 60), wxSize(300, 30));

	wxStaticText* pageNumberText = new wxStaticText(foreGroundPanel, -1,
		wxT("SO TRANG"), wxPoint(10, 90), wxSize(100, 30));
	wxStaticText* pageNumberInfor = new wxStaticText(foreGroundPanel, -1,
		wxT(": SO TRANG KHONG QUA 999999 TRANG"), wxPoint(80, 90), wxSize(300, 30));

	wxStaticText* authorText = new wxStaticText(foreGroundPanel, -1,
		wxT("TAC GIA"), wxPoint(10, 120), wxSize(100, 30));
	wxStaticText* authorInfor = new wxStaticText(foreGroundPanel, -1,
		wxT(": TOI DA 17 KI TU, CHI LAY KI TU CHU"), wxPoint(80, 120), wxSize(300, 30));

	wxStaticText* publicYearText = new wxStaticText(foreGroundPanel, -1,
		wxT("NXB"), wxPoint(10, 150), wxSize(100, 30));
	wxStaticText* publicYearInfor = new wxStaticText(foreGroundPanel, -1,
		wxT(": NXB KHONG LON HON NAM HIEN TAI"), wxPoint(80, 150), wxSize(300, 30));

	wxStaticText* typeText = new wxStaticText(foreGroundPanel, -1,
		wxT("THE LOAI"), wxPoint(10, 180), wxSize(100, 30));
	wxStaticText* typeInfor = new wxStaticText(foreGroundPanel, -1,
		wxT(": TOI DA 11 KI TU, CHI LAY KI TU CHU"), wxPoint(80, 180), wxSize(300, 30));

	//SetColor
	foreGroundPanel->SetBackgroundColour(lightYellow);
	titleTakeNoteText->SetBackgroundColour(orange);
}
void BookTitle::CreateKeyNoteArea(wxPanel* keyNotePanel)
{
	wxStaticText* keyNoteText = new wxStaticText(keyNotePanel, -1,
		wxT("F2-SAVE, F9-MO HOAC TAT CHE DO XOA (DELETE-XOA DAU SACH,ENTER-NHAP DAU SACH)"),
		wxPoint(10, 10), wxSize(550, 20), wxALIGN_CENTER_HORIZONTAL);
}
void BookTitle::MainKeyDown(int keyCode)
{
	if (keyCode == WXK_F4)
	{
		isTurnOnEnterPanel = !isTurnOnEnterPanel;
		SwitchPanel(isTurnOnEnterPanel);
		SwitchEnterText(isTurnOnEnterPanel);
	}
	if (keyCode == WXK_UP)
	{
		checkInput->MoveUpToAnotherTextCtrl(enterText, 6);
	}
	else if (keyCode == WXK_DOWN)
	{
		checkInput->MoveDownToAnotherTextCtrl(enterText, 6);
	}
	else if (keyCode == WXK_F2)
	{
		SaveFile();
	}
	else if (keyCode == WXK_DELETE)
	{
		ShowMessageClear();
	}
	else if (keyCode == WXK_F9)
	{
		isModeDelete = !isModeDelete;
		if (grid->IsSelection())
		{
			grid->ClearSelection();
		}
		SetModeDelete(isModeDelete);

	}
}
void BookTitle::OnKeyDown(wxKeyEvent& event)
{
	event.StopPropagation();
	int keyCode = event.GetKeyCode();
	MainKeyDown(keyCode);
	if (!isTurnOnEnterPanel)
	{
		event.Skip();

		return;
	}
	
	if (enterText[0]->HasFocus())
	{
		if (checkInput->HasAlpha(keyCode)||checkInput->HasRightEntering(keyCode,false))
		{
			event.Skip();
		}
	}
	else if (enterText[3]->HasFocus() || enterText[5]->HasFocus())
	{
		if (checkInput->HasAlpha(keyCode)||checkInput->HasRightEntering(keyCode,true))
		{
			event.Skip();
		}
	}
	else if (enterText[1]->HasFocus())
	{
		if (checkInput->HasAlphaAndNumber(keyCode)||checkInput->HasRightEntering(keyCode,true))
		{
			event.Skip();
		}
	}
	else if (enterText[2]->HasFocus() || enterText[4]->HasFocus())
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
void BookTitle::OnGridKeyDown(wxKeyEvent& event)
{
	event.StopPropagation();
	int keyCode = event.GetKeyCode();
	MainKeyDown(keyCode);
	int col = grid->GetGridCursorCol();
	if (!canEdit)
	{
		if (checkInput->HasRightEntering(keyCode, false))
		{
			event.Skip();
		}
		return;
	}
	if (col == 0)
	{
		if (checkInput->HasAlpha(keyCode) || checkInput->HasRightEntering(keyCode, true))
		{
			event.Skip();
		}
	}
	else if (col == 1)
	{
		if (checkInput->HasAlphaAndNumber(keyCode) || checkInput->HasRightEntering(keyCode, true))
		{
			event.Skip();
		}
	}
	else if (col == 2)
	{
		if (checkInput->HasNumber(keyCode)||checkInput->HasRightEntering(keyCode,false))
		{
			event.Skip();
		}
	}
	else if (col == 3)
	{
		if (checkInput->HasAlpha(keyCode) || checkInput->HasRightEntering(keyCode, true))
		{
			event.Skip();
		}
	}
	else if (col == 4)
	{
		if (checkInput->HasNumber(keyCode) || checkInput->HasRightEntering(keyCode, false))
		{
			event.Skip();
		}
	}
	else if (col == 5)
	{
		if (checkInput->HasAlpha(keyCode) || checkInput->HasRightEntering(keyCode, true))
		{
			event.Skip();
		}
	}
}
void BookTitle::SetModeDelete(bool state)
{
	for (int i = 0; i < maxItem; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			grid->SetReadOnly(i, j, state);
		}
	}
}
void BookTitle::OnEnter(wxCommandEvent& WXUNUSED(event))
{
	if (!isTurnOnEnterPanel) { return; }
	if(maxItem+1>titleList->GetList()->MaxLength())
	{
		wxMessageBox("GIOI HAN SACH LA 100 KHONG THE VUOT HON");
		return;
	}
	for (int i = 0; i < 6; i++)
	{
		if (checkInput->IsWhiteSpaceAllText(enterText[i]->GetValue()))
		{
			checkInput->ErrorMessageBox("KHONG DUOC BO TRONG O NHAP");
			enterText[i]->SetFocus();
			return;
		}
		wxString myWxStr = enterText[i]->GetValue();
		checkInput->ModifyTextInput(myWxStr);
		enterText[i]->SetValue(myWxStr);
	}
	wxString wxstr = enterText[0]->GetValue();
	if (!CheckISBN(wxstr))
	{
		checkInput->ErrorMessageBox("LOI ISBN");
		enterText[0]->SetFocus();
		return;
	}
	checkInput->ModifyTextInput(wxstr);
	//checkInput->UpperWxString(wxstr);
	if (!CheckDuplicateISBN(wxstr, -1))
	{
		checkInput->ErrorMessageBox("TRUNG ISBN CO TRONG DANH SACH");
		enterText[0]->SetFocus();
		return;
	}
	wxstr = enterText[1]->GetValue();
	if (!CheckBookName(wxstr))
	{
		checkInput->ErrorMessageBox("LOI TEN SACH");
		enterText[1]->SetFocus();
		return;
	}
	wxstr = enterText[2]->GetValue();
	if (!CheckPageNumber(wxstr))
	{
		checkInput->ErrorMessageBox("LOI SO TRANG");
		enterText[2]->SetFocus();
		return;
	}
	wxstr = enterText[3]->GetValue();
	if (!CheckAuthor(wxstr))
	{
		checkInput->ErrorMessageBox("LOI TEN TAC GIA");
		enterText[3]->SetFocus();
		return;
	}
	wxstr = enterText[4]->GetValue();
	if (!CheckYearPublic(wxstr))
	{
		checkInput->ErrorMessageBox("LOI NAM XUAT BAN");
		enterText[4]->SetFocus();
		return;
	}
	wxstr = enterText[5]->GetValue();
	if (!CheckType(wxstr))
	{
		checkInput->ErrorMessageBox("LOI THE LOAI");
		enterText[5]->SetFocus();
		return;
	}

	SaveToList();

}
void BookTitle::OnExitMenu(wxCommandEvent& WXUNUSED(event))
{
	this->Show(false);
	GetParent()->Show();
}
void BookTitle::OnShow(wxShowEvent& event)
{
	if (event.IsShown())
	{
		if (maxItem > 30)
		{
			grid->DeleteRows(30, maxItem - 30);
		}
		LoadData();
		isModeDelete = false;
		SetModeDelete(false);
	}
	event.Skip();
}
void BookTitle::EditCurrentCell(wxGridEvent& event)
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
	checkInput->ModifyTextInput(wxNewText);
	if (col == 0)
	{

		if (!CheckISBN(wxNewText))
		{
			checkInput->ErrorMessageBox("LOI ISBN");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}
		checkInput->UpperWxString(wxNewText);
		if (!CheckDuplicateISBN(wxNewText, row))
		{
			checkInput->ErrorMessageBox("TRUNG VOI ISBN CO TRONG DANH SACH");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}

	}
	if (col == 1)
	{
		if (!CheckBookName(wxNewText))
		{
			checkInput->ErrorMessageBox("LOI TEN SACH");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}
		checkInput->UpperWxString(wxNewText);
	}
	if (col == 2)
	{
		if (!CheckPageNumber(wxNewText))
		{
			checkInput->ErrorMessageBox("LOI SO TRANG");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}
	}
	if (col == 3)
	{
		if (!CheckAuthor(wxNewText))
		{
			checkInput->ErrorMessageBox("LOI TEN TAC GIA");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}
		checkInput->UpperWxString(wxNewText);
	}
	if (col == 4)
	{
		if (!CheckYearPublic(wxNewText))
		{
			checkInput->ErrorMessageBox("LOI NAM XUAT BAN");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}
	}
	if (col == 5)
	{
		if (!CheckType(wxNewText))
		{
			checkInput->ErrorMessageBox("LOI THE LOAI");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}
		checkInput->UpperWxString(wxNewText);
	}


	string ISBN = string(grid->GetCellValue(row, 0).mb_str());
	if (col == 0)
	{
		ISBN = string(wxOldText.mb_str());
	}
	BookList* tempList = titleList->GetData(ISBN)->GetListBook();
	uint countBorrow = titleList->GetData(ISBN)->GetCountBorrow();
	titleList->Delete(ISBN);
	grid->SetCellValue(row, col, wxNewText);
	ISBN = string(grid->GetCellValue(row, 0).mb_str());
	string bookName = string(grid->GetCellValue(row, 1).mb_str());
	uint numberPage = checkInput->CastWxStringToInt(grid->GetCellValue(row, 2));
	string author = string(grid->GetCellValue(row, 3).mb_str());
	uint nxb = checkInput->CastWxStringToInt(grid->GetCellValue(row, 4));
	string type = string(grid->GetCellValue(row, 5).mb_str());
	Title* title = new Title(ISBN, bookName, numberPage, author, nxb, type,countBorrow);
	if (col == 5 || col == 1)
	{
		EditTable(title, row);
		grid->DeleteRows(row, 1);
		//grid->Refresh();
	}
	title->SetListBook(tempList);
	titleList->GetList()->AddLast(title);

	//load grid again();
	QuickSort(0, maxItem);
	LoadListToTable();
	event.Skip();
}
void BookTitle::EditTable(Title* title, int row)
{
	int pos = -1;
	for (int i = 0; i < maxItem; i++)
	{
		Title* tempT = new Title();
		for (int j = 0; j < 6; j++)
		{
			int number = 0;
			wxString wxstr = grid->GetCellValue(i, j);
			if (!(j == 2 || j == 4))
			{

				if (j == 0)
				{
					tempT->SetISBN(string(wxstr.mbc_str()));
				}
				else if (j == 1)
				{
					tempT->SetBookName(string(wxstr.mbc_str()));
				}
				else if (j == 3)
				{
					tempT->SetAuthor(string(wxstr.mbc_str()));
				}
				else if (j == 5)
				{
					tempT->SetType(string(wxstr.mbc_str()));
				}

			}
			else
			{

				number = checkInput->CastWxStringToInt(wxstr);
				if (j == 2)
				{
					tempT->SetPageNumber(number);
				}
				else if (j == 4)
				{
					tempT->SetPublicYear(number);
				}
			}
		}
		//wxMessageBox(wxString::Format("Tempt: %s and cur: %s", tempT->GetType(), curTitle->GetType()));
		if (CompareTitle(title, tempT) < 1)
		{
			pos = i;
			tempT->GetListBook()->Clear();
			delete tempT;
			break;
		}
		tempT->GetListBook()->Clear();
		delete tempT;
		tempT = nullptr;
	}
	if (pos == -1)
	{
		pos = maxItem;
	}
	grid->InsertRows(pos, 1);
	if (row > pos)
	{
		row++;
	}
	for (int i = 0; i < 6; i++)
	{
		grid->SetCellValue(pos, i, grid->GetCellValue(row, i));
		grid->SetCellAlignment(pos, i, wxALIGN_CENTER, wxALIGN_CENTER);
	}
	
}
void BookTitle::OnKeyDownTextCltrToUpper(wxCommandEvent& _rCommandEvent)
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
void BookTitle::SaveToList()
{
	Title* curTitle = new Title();
	for (int i = 0; i < 6; i++)
	{
		int number = 0;
		if (!(i == 2 || i == 4))
		{
			wxString wxstr = enterText[i]->GetValue();
			//checkInput->UpperWxString(wxstr);
			enterText[i]->SetValue(wxstr);
			if (i == 0)
			{
				curTitle->SetISBN(string(wxstr.mbc_str()));
			}
			else if (i == 1)
			{
				curTitle->SetBookName(string(wxstr.mbc_str()));
			}
			else if (i == 3)
			{
				curTitle->SetAuthor(string(wxstr.mbc_str()));
			}
			else if (i == 5)
			{
				curTitle->SetType(string(wxstr.mbc_str()));
			}

		}
		else
		{
			number = checkInput->CastWxStringToInt(enterText[i]->GetValue());
			if (i == 2)
			{
				curTitle->SetPageNumber(number);
			}
			else if (i == 4)
			{
				curTitle->SetPublicYear(number);
			}
		}

	}


	int pos = -1;
	for (int i = 0; i < maxItem; i++)
	{
		Title* tempT = new Title();
		for (int j = 0; j < 6; j++)
		{
			int number = 0;
			wxString wxstr = grid->GetCellValue(i, j);
			if (!(j == 2 || j == 4))
			{

				if (j == 0)
				{
					tempT->SetISBN(string(wxstr.mbc_str()));
				}
				else if (j == 1)
				{
					tempT->SetBookName(string(wxstr.mbc_str()));
				}
				else if (j == 3)
				{
					tempT->SetAuthor(string(wxstr.mbc_str()));
				}
				else if (j == 5)
				{
					tempT->SetType(string(wxstr.mbc_str()));
				}

			}
			else
			{

				number = checkInput->CastWxStringToInt(wxstr);
				if (j == 2)
				{
					tempT->SetPageNumber(number);
				}
				else if (j == 4)
				{
					tempT->SetPublicYear(number);
				}
			}
		}
		//wxMessageBox(wxString::Format("Tempt: %s and cur: %s", tempT->GetType(), curTitle->GetType()));
		if (CompareTitle(curTitle, tempT) < 1)
		{
			pos = i;
			tempT->GetListBook()->Clear();
			delete tempT;
			tempT = nullptr;
			break;
		}
		tempT->GetListBook()->Clear();
		delete tempT;
		tempT = nullptr;
	}
	if (pos == -1)
	{
		pos = maxItem;
	}
	grid->InsertRows(pos, 1);

	for (int i = 0; i < 6; i++)
	{
		grid->SetCellValue(pos, i, enterText[i]->GetValue());
		grid->SetCellAlignment(pos, i, wxALIGN_CENTER, wxALIGN_CENTER);
	}
	ClearInforInEnterText();
	titleList->GetList()->AddLast(curTitle);
	maxItem++;
	if (maxItem + 1 > grid->GetNumberRows())
	{
		grid->AppendRows(maxItem - grid->GetNumberRows() + 1);
	}
}
void BookTitle::SaveFile()
{
	ISaveFile* isaveFile = dynamic_cast<ISaveFile*>(this->GetParent());
	isaveFile->SaveFile();
}
void BookTitle::LoadData()
{
	grid->Refresh();
	ClearOldDataInGrid();
	maxItem = titleList->GetList()->Length();
	//QuickSort(0, maxItem);
	LoadListToTable();

}
void BookTitle::LoadListToTable()
{
	if (maxItem > grid->GetNumberRows())
	{
		grid->AppendRows(maxItem - grid->GetNumberRows() + 1);
	}
	for (int i = 0; i < maxItem; i++)
	{
		Title* temp = titleList->GetList()->GetData(i);
		grid->SetCellValue(i, 0, temp->GetISBN());
		grid->SetCellValue(i, 1, temp->GetBookName());
		grid->SetCellValue(i, 2, wxString::Format("%i", temp->GetPageNumber()));
		grid->SetCellValue(i, 3, temp->GetAuthor());
		grid->SetCellValue(i, 4, wxString::Format("%i", temp->GetPublicYear()));
		grid->SetCellValue(i, 5, temp->GetType());
		for (int j = 0; j < 6; j++)
		{
			grid->SetCellAlignment(i, j, wxALIGN_CENTER, wxALIGN_CENTER);
		}
	}
}
void BookTitle::ClearOldDataInGrid()
{
	for (int i = 0; i < grid->GetNumberRows(); i++)
	{
		for (int j = 0; j < grid->GetNumberCols(); j++)
		{
			grid->SetCellValue(i,j,wxT(""));
		}
	}
}
void BookTitle::ShowMessageClear()
{
	wxMessageDialog* dialog = new wxMessageDialog(NULL,
		wxT("Are you sure to clear?"), wxT("Warning"),
		wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
	if (grid->IsSelection() && dialog->ShowModal() == wxID_YES)
	{
		DeleteSelectedRows();
	}
	delete dialog;

}
void BookTitle::DeleteSelectedRows()
{
	if (grid->IsSelection())
	{
		//wxMessageBox(wxString::Format("%i",cardCode));
		int row = grid->GetSelectedRows()[0];
		string ISBN = string(grid->GetCellValue(row, 0).mbc_str());
		if (ISBN != "")
		{
			BookList* tempList = titleList->GetData(ISBN)->GetListBook();
			if (tempList->Length() > 0)
			{
				SinglyNode<Book>* tempBook = tempList->First();
				while (tempBook != nullptr)
				{
					if (tempBook->data.GetState() == 1)
					{
						checkInput->ErrorMessageBox("DAU SACH CO SACH DANG MUON KHONG THE XOA");
						return;
					}
					tempBook = tempBook->next;
				}
			}
			titleList->Delete(ISBN);
			delete tempList;
			maxItem--;

		}
		grid->DeleteRows(row, 1);
		if (grid->GetNumberRows() < 30)
		{
			int numberRowsNeed = 30 - grid->GetNumberRows();

			grid->AppendRows(numberRowsNeed);
		}

	}
}
void BookTitle::SwitchPanel(bool state)
{
	enterPanel->Show(state);
	takeNotePanel->Show(state);
}
void BookTitle::SwitchEnterText(bool state)
{
	for (int i = 0; i < 6; i++)
	{
		enterText[i]->SetEditable(state);
	}
}
//
// if khong luu gia tri thi xoa mang di va luu gia tri cu cua file vao mang
//
void BookTitle::ClearInforInEnterText()
{
	for (int i = 0; i < 6; i++)
	{
		enterText[i]->Clear();
	}
	enterText[0]->SetFocus();
}
bool BookTitle::CheckISBN(wxString text)
{
	//ISBN CO 4 CHARS AND ALL IS CHAR NOT HAVE NUMBER;
	if (!checkInput->IsAlphabet(text)) { return false; }
	string textstr = string(text.mbc_str());
	return textstr.length() == 4;
}
bool BookTitle::CheckBookName(wxString text)
{
	return checkInput->HasNumberAndAlphabet(text);
}
bool BookTitle::CheckPageNumber(wxString text)
{
	//page number has 6 number;
	if (!checkInput->IsNumber(text)) { return false; }
	string textstr = string(text.mbc_str());
	return textstr.length() <= 6 && textstr.length() > 0;
}
bool BookTitle::CheckAuthor(wxString text)
{
	return checkInput->IsWord(text);
}
bool BookTitle::CheckYearPublic(wxString text)
{
	if (!checkInput->IsNumber(text)) { return false; }
	time_t current = time(0);
	tm* ltm = localtime(&current);
	int currentYear = ltm->tm_year + 1900;
	int yearInput = checkInput->CastWxStringToInt(text);
	//wxMessageBox(wxString::Format("current year: %i and year input: %i", currentYear, yearInput));
	return yearInput <= currentYear;
}
bool BookTitle::CheckType(wxString text)
{
	return checkInput->IsWord(text);
}
bool BookTitle::CheckDuplicateISBN(wxString text, int row)
{
	for (int i = 0; i < maxItem; i++)
	{
		if (row == i)
		{
			continue;
		}
		if (text == grid->GetCellValue(i, 0))
		{
			return false;
		}
	}
	return true;
}
int BookTitle::CompareTitle(Title* t1, Title* t2)
{
	if (t1->GetType() > t2->GetType()) { return 1; }
	else if (t1->GetType() < t2->GetType()) { return -1; }
	else
	{
		if (t1->GetBookName() > t2->GetBookName()) { return 1; }
		else if (t1->GetBookName() < t2->GetBookName()) { return -1; }
		else return 0;
	}
}

//quickSort
void BookTitle::Swap(Title* t1, Title* t2)
{
	Title temp = *t1;
	*t1 = *t2;
	*t2 = temp;
}
int BookTitle::partition(int l, int h)
{
	Title* pivot = titleList->GetList()->GetData(l);
	int i = l;
	int j = h;
	do
	{
		do { i++; if (i == j) { break; } } while (CompareTitle(titleList->GetList()->GetData(i), pivot) < 1);
		do { j--; } while (CompareTitle(titleList->GetList()->GetData(j), pivot) == 1);
		if (i < j) { Swap((titleList->GetList()->GetData(i)), (titleList->GetList()->GetData(j))); }
	} while (i < j);
	Swap(titleList->GetList()->GetData(l), titleList->GetList()->GetData(j));
	return j;
}
void BookTitle::QuickSort(int l, int h)
{
	int j = 0;
	if (l < h)
	{
		j = partition(l, h);
		QuickSort(l, j);
		QuickSort(j + 1, h);
	}
}
void BookTitle::OnSelectingGrid(wxGridRangeSelectEvent& WXUNUSED(event))
{
	if (grid->IsSelection())
	{
		grid->ClearSelection();
	}
}
void BookTitle::OnSelectedGrid(wxCommandEvent& WXUNUSED(event))
{
	if (isModeDelete) { return; }
	grid->ClearSelection();
}
void BookTitle::OnSelectedLabelGrid(wxCommandEvent& WXUNUSED(event))
{
	if (grid->IsSelection())
	{
		grid->ClearSelection();
	}
}
void BookTitle::OnSelectedCell(wxGridEvent& event)
{
	int row = event.GetRow();
	int col = event.GetCol();
	if (!isModeDelete)
	{
		grid->ClearSelection();
	}
	canEdit = true;
	event.Skip();
}
void BookTitle::OnGridTexting(wxCommandEvent& event)
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
int BookTitle::GetMaxLength(int col)
{
	if (col > 5) { return -1; }
	if (col == 0)
	{
		return 4;
	}
	else if (col == 1)
	{
		return 24;
	}
	else if(col==2)
	{
		return 6;
	}
	else if (col == 3)
	{
		return 17;
	}
	else if (col == 4)
	{
		return 4;
	}
	else if (col == 5)
	{
		return 11;
	}
	return -1;
}
BEGIN_EVENT_TABLE(BookTitle, wxFrame)
EVT_CHAR_HOOK(BookTitle::OnKeyDown)
END_EVENT_TABLE()
