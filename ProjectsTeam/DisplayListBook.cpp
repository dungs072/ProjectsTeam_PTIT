#include "DisplayListBook.h"
DisplayListBook::DisplayListBook(const wxString& title) :wxFrame(NULL, -1,
	title, wxDefaultPosition, wxSize(1280, 680))
{
	//temp color
	wxColour lightYellow, lightBlue, red;
	lightYellow.Set(wxT("#E0EBB7"));
	lightBlue.Set(wxT("#7FB1E3"));
	red.Set(wxT("#F74A4A"));

	//backend
	stateBook = new string[3]{ "CHO MUON DUOC","DA CO DOC GIA MUON","DA THANH LY" };
	//Create panel
	wxPanel* mainPanel = new wxPanel(this, -1);
	enterPanel = new wxPanel(mainPanel, -1, wxDefaultPosition, wxSize(300, 250));
	takeNotePanel = new wxPanel(mainPanel, -1, wxDefaultPosition, wxSize(530, 30));
	guidePanel = new wxPanel(mainPanel, -1, wxDefaultPosition, wxSize(530, 200));
	//for hiding enter text
	hideEnterText = new wxTextCtrl(enterPanel, -1, wxT(""),
		wxDefaultPosition, wxSize(-1, -1), wxTE_PROCESS_ENTER);
	hideEnterText->SetEditable(false);
	hideEnterText->Hide();
	//Create static text
	titleGrid = new wxStaticText(mainPanel, -1, wxT("Danh muc sach cua dau sach: ")
		, wxDefaultPosition, wxSize(500, 30), wxALIGN_CENTER);
	checkInput->SetTextSize(titleGrid, 15);
	//Create Button

	backButton = new wxButton(enterPanel, -1, wxT("<<--BACK"), wxPoint(20, 220), wxSize(75, 20));
	//Create BoxSizer
	wxBoxSizer* mainHBox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* vGridBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vRightBox = new wxBoxSizer(wxVERTICAL);
	//Create Grid
	grid = new wxGrid(mainPanel, -1, wxDefaultPosition, wxSize(550, 550));
	grid->CreateGrid(30, 3);
	grid->SetColLabelValue(0, wxT("MA SACH"));
	grid->SetColLabelValue(1, wxT("TRANG THAI"));
	grid->SetColLabelValue(2, wxT("VI TRI"));
	for (int i = 0; i < 3; i++)
	{
		grid->SetColSize(i, 150);
	}
	//grid->SetRowLabelSize(50);
	grid->DisableDragColSize();
	grid->DisableDragRowSize();
	grid->SetSelectionMode(wxGrid::wxGridSelectionModes::wxGridSelectRows);
	//set sizer
	vGridBox->Add(titleGrid, 0, wxTOP | wxALIGN_CENTER, 10);
	vGridBox->Add(grid, 0, wxTOP, 10);
	vGridBox->Add(takeNotePanel, 0, wxTOP | wxALIGN_CENTER, 5);
	vRightBox->Add(enterPanel, 0, wxTOP, 70);
	vRightBox->Add(guidePanel, 0, wxTOP, 20);

	mainHBox->Add(vGridBox, 0, wxLEFT, 20);
	mainHBox->Add(vRightBox, 0, wxLEFT, 30);
	mainPanel->SetSizer(mainHBox);
	//Create area
	CreateEnterArea();
	CreateGuideArea();
	CreateKeyNoteArea();
	//Register event
	grid->Bind(wxEVT_GRID_CELL_CHANGED, &DisplayListBook::EditCurrentCell, this);
	Bind(wxEVT_TEXT_ENTER, &DisplayListBook::OnEnter, this);
	stateChoice->Bind(wxEVT_CHOICE, &DisplayListBook::OnChoice, this);
	backButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &DisplayListBook::OnButtonClicked, this);

	grid->Bind(wxEVT_GRID_RANGE_SELECTING, &DisplayListBook::OnSelectingGrid, this);
	grid->Bind(wxEVT_GRID_SELECT_CELL, &DisplayListBook::OnSelectedGrid, this);
	grid->Bind(wxEVT_GRID_LABEL_LEFT_CLICK, &DisplayListBook::OnSelectedLabelGrid, this);
	grid->Bind(wxEVT_CHAR_HOOK, &DisplayListBook::OnGridKeyDown, this);
	grid->Bind(wxEVT_GRID_SELECT_CELL, &DisplayListBook::OnSelectedCell, this);
	grid->Bind(wxEVT_TEXT, &DisplayListBook::OnGridTexting, this);

	//Set color
	titleGrid->SetBackgroundColour(lightBlue);
	enterPanel->SetBackgroundColour(lightYellow);
	guidePanel->SetBackgroundColour(lightYellow);
	takeNotePanel->SetBackgroundColour(lightYellow);
	backButton->SetBackgroundColour(red);
	Centre();
}
void DisplayListBook::CreateEnterArea()
{
	wxArrayString temp;
	temp.Add("NONE");
	for (int i = 0; i < 3; i++)
	{
		if (i == 1) continue;
		temp.Add(stateBook[i]);
	}
	wxColor orange, lightBlue;
	orange.Set(wxT("#FFAB03"));
	lightBlue.Set(wxT("#9AD6E6"));
	wxStaticText* titleText = new wxStaticText(enterPanel, -1,
		wxT("CAP NHAT MUC SACH"), wxPoint(50, 20), wxSize(200, 20), wxALIGN_CENTER);
	checkInput->SetTextSize(titleText, 15);
	wxStaticText* stateText = new wxStaticText(enterPanel, -1,
		wxT("TRANG THAI: "), wxPoint(10, 100), wxSize(100, 20));
	stateChoice = new wxChoice(enterPanel, -1, wxPoint(10, 120),
		wxSize(200, 25), temp);
	stateChoice->SetSelection(0);
	wxStaticText* posText = new wxStaticText(enterPanel, -1,
		wxT("VI TRI: "), wxPoint(10, 150), wxSize(100, 20));
	enterText = new wxTextCtrl(enterPanel, -1, wxT(""),
		wxPoint(10, 120 + 1 * 50), wxSize(200, 25), wxTE_PROCESS_ENTER | wxTE_CENTRE);
	enterText->SetMaxLength(17);
	enterText->SetBackgroundColour(lightBlue);
	enterText->Connect(wxID_ANY, wxEVT_COMMAND_TEXT_UPDATED,
		(wxObjectEventFunction)&DisplayListBook::OnKeyDownTextCltrToUpper);
	//Set color
	titleText->SetBackgroundColour(orange);

}
void DisplayListBook::CreateKeyNoteArea()
{
	wxStaticText* keyNoteText = new wxStaticText(takeNotePanel, -1,
		wxT("KEYHOT:  F2 - SAVE FILE, F9 - MO CHE DO XOA (DELETE - XOA MUC SACH ),ENTER - NHAP VAO BANG"),
		wxPoint(10, 10), wxSize(500, 15), wxALIGN_CENTER_HORIZONTAL);
}
void DisplayListBook::CreateGuideArea()
{
	wxColor orangeColor;
	orangeColor.Set(wxT("#FFAB03"));
	wxStaticText* titleGuide = new wxStaticText(guidePanel, -1,
		wxT("GUIDE"), wxPoint(210, 20), wxSize(100, 20), wxALIGN_CENTER);
	checkInput->SetTextSize(titleGuide, 15);
	wxStaticText* bookCodeText = new wxStaticText(guidePanel, -1,
		wxT("MA SACH"), wxPoint(20, 80), wxSize(75, 15));
	wxStaticText* stateText = new wxStaticText(guidePanel, -1,
		wxT("TRANG THAI"), wxPoint(20, 110), wxSize(75, 15));
	wxStaticText* posText = new wxStaticText(guidePanel, -1,
		wxT("VI TRI"), wxPoint(20, 140), wxSize(75, 15));
	wxStaticText* noteText1 = new wxStaticText(guidePanel, -1,
		wxT(":  MA SACH DUOC DANH TU DONG"), wxPoint(100, 80), wxSize(200, 15));
	wxStaticText* noteText2 = new wxStaticText(guidePanel, -1,
		wxT(": 0 = CHO MUON DUOC, 1 = DA CO DOC GIA MUON, 2 = SACH DA THANH LY"),
		wxPoint(100, 110), wxSize(550, 15));
	wxStaticText* noteText3 = new wxStaticText(guidePanel, -1,
		wxT(":  TOI DA 17 KI TU, CHI LAY KI TU CHU, SO VA DAU PHAY"),
		wxPoint(100, 140), wxSize(300, 15));
	//Set Color
	titleGuide->SetBackgroundColour(orangeColor);
}
void DisplayListBook::OnShow(wxShowEvent& event)
{
	if (event.IsShown())
	{
		string bookName = currentTitle->GetBookName();
		titleGrid->SetLabel("DANH MUC SACH CUA DAU SACH: " + bookName);
		for (int i = 0; i < maxItem; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				grid->SetCellValue(i, j, wxT(""));
			}
		}
		if (maxItem > 30)
		{
			grid->DeleteRows(30, maxItem - 30);
		}
		if (grid->IsSelection())
		{
			grid->ClearSelection();
		}
		maxItem = 0;
		LoadData();
		SetModeDelete(false);
	}
	else
	{
		backButton->SetFocus();
		stateChoice->SetSelection(0);
		enterText->Clear();
	}
}
void DisplayListBook::MainKeyDown(int keyDown)
{
	if (keyDown == WXK_F2)
	{
		SaveFile();
	}
	else if (keyDown == WXK_DELETE)
	{
		ShowMessageClear();
	}
	else if (keyDown == WXK_F9)
	{
		isModeDelete = !isModeDelete;
		grid->ClearSelection();
		SetModeDelete(isModeDelete);
	}

}
void DisplayListBook::OnKeyDown(wxKeyEvent& event)
{
	event.StopPropagation();
	MainKeyDown(event.GetKeyCode());
	event.Skip();
}
void DisplayListBook::OnGridKeyDown(wxKeyEvent& event)
{
	int keyCode = event.GetKeyCode();
	MainKeyDown(keyCode);
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
		if (checkInput->HasInRangeNumber(keyCode, 0, 2) || checkInput->HasRightEntering(keyCode, true))
		{
			if (keyCode != '1')// i dont have choice
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
	else if (col == 2)
	{
		if (checkInput->HasAlphaAndNumber(keyCode) ||
			checkInput->HasRightEntering(keyCode, true) ||
			keyCode == ',')
		{
			event.Skip();
		}
	}

}
void DisplayListBook::OnChoice(wxCommandEvent& event)
{
	hideEnterText->SetFocus();
}
void DisplayListBook::OnEnter(wxCommandEvent& event)
{
	if (checkInput->IsWhiteSpaceAllText(enterText->GetValue()))
	{
		checkInput->ErrorMessageBox("KHONG DUOC BO TRONG O NHAP");
		enterText->Clear();
		enterText->SetFocus();
		return;
	}

	if (stateChoice->GetSelection() == 0)
	{
		checkInput->ErrorMessageBox("CHUA CHON TRANG THAI SACH");
		stateChoice->SetFocus();
		return;
	}
	wxString wxstr = enterText->GetValue();
	checkInput->ModifyTextInput(wxstr);
	enterText->SetValue(wxstr);
	if (!CheckPos(wxstr))
	{
		checkInput->ErrorMessageBox("LOI VI TRI");
		enterText->SetFocus();
		return;
	}
	SaveToList();
}
void DisplayListBook::OnButtonClicked(wxCommandEvent& WXUNUSED(event))
{
	this->Show(false);
	GetParent()->Show(true);
}
void DisplayListBook::EditCurrentCell(wxGridEvent& event)
{
	int row = grid->GetGridCursorRow();
	int col = grid->GetGridCursorCol();
	wxString wxOldText = event.GetString();
	if (wxOldText == wxT(""))
	{
		checkInput->ErrorMessageBox("Khong the chinh sua o nay ");
		grid->SetCellValue(row, col, wxOldText);
		return;
	}
	wxString wxNewText = grid->GetCellValue(row, col);
	string bookCode = string(grid->GetCellValue(row, 0).mb_str());
	if (col == 1)
	{
		int num = checkInput->CastWxStringToInt(wxNewText);
		if (checkInput->IsWhiteSpaceAllText(wxNewText)||num==-1)
		{
			checkInput->ErrorMessageBox("Loi trang thai");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}
	}
	if (col == 2)
	{
		checkInput->ModifyTextInput(wxNewText);
		if (!CheckPos(wxNewText) || wxNewText == "")
		{
			checkInput->ErrorMessageBox("LOI VI TRI");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}
		else
		{
			wxNewText = wxNewText.Upper();
			grid->SetCellValue(row, col, wxNewText);
			string tempStr = string(wxNewText.mb_str());
			currentTitle->GetListBook()->FindSinglyNode(bookCode)->data.SetPos(tempStr);
		}
	}
}
void DisplayListBook::EditData(int row, int col,int index)
{
	string bookCode = string(grid->GetCellValue(row, 0).mb_str());
	if (bookCode == "")
	{
		checkInput->ErrorMessageBox("Khong the chinh sua o nay ");
		grid->SetCellValue(row, col, wxT(""));
		return;
	}
	Book *book = &(currentTitle->GetListBook()->FindSinglyNode(bookCode)->data);
	if (book->GetState()==1)
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
void DisplayListBook::ShowMessageClear()
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
void DisplayListBook::DeleteSelectedRows()
{
	if (grid->IsSelection())
	{
		int row = grid->GetSelectedRows()[0];
		string bookCode = string(grid->GetCellValue(row, 0).mbc_str());
		if (bookCode != "")
		{
			string stateBook = string(grid->GetCellValue(row, 1).mb_str());
			if (stateBook == "DA CO DOC GIA MUON")
			{
				checkInput->ErrorMessageBox("SACH DA DUOC MUON, KHONG THE XOA");
				return;
			}
			currentTitle->GetListBook()->Remove(bookCode);
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
void DisplayListBook::SaveToList()
{
	if (maxItem + 1 > grid->GetNumberRows())
	{
		grid->AppendRows(maxItem - grid->GetNumberRows() + 1);
	}
	string bookCode = currentTitle->GetISBN() + checkInput->CastIntToString(count);
	count++;
	int index = stateChoice->GetSelection();
	if (index < 0)
	{
		wxMessageBox("LOI TRANG THAI SACH");
		return;
	}
	index = index == 1 ? 0 : 2;
	string state = stateBook[index];
	grid->SetCellValue(maxItem, 0, bookCode);
	grid->SetCellValue(maxItem, 1, state);
	grid->SetCellValue(maxItem, 2, enterText->GetValue());
	for (int i = 0; i < 3; i++)
	{
		grid->SetCellAlignment(maxItem, i, wxALIGN_CENTER, wxALIGN_CENTER);
	}
	grid->SetReadOnly(maxItem, 0);

	Book tempBook(bookCode, index, string(enterText->GetValue().mb_str()));
	enterText->Clear();
	index = index == 0 ? 1 : 2;
	stateChoice->SetSelection(index);
	currentTitle->GetListBook()->Add(tempBook);
	maxItem++;


}
void DisplayListBook::SaveFile()
{
	ISaveFile* isaveFile = dynamic_cast<ISaveFile*>(grandPas);

	isaveFile->SaveFile();
}
void DisplayListBook::LoadData()
{
	SinglyNode<Book>* tempBook = currentTitle->GetListBook()->First();
	while (tempBook != nullptr)
	{
		string state = stateBook[tempBook->data.GetState()];
		grid->SetCellValue(maxItem, 0, tempBook->data.GetBookCode());
		grid->SetCellValue(maxItem, 1, state);
		grid->SetCellValue(maxItem, 2, tempBook->data.GetPos());
		for (int i = 0; i < 3; i++)
		{
			grid->SetCellAlignment(maxItem, i, wxALIGN_CENTER, wxALIGN_CENTER);
		}
		grid->SetReadOnly(maxItem, 0);
		maxItem++;

		if (maxItem + 1 > grid->GetNumberRows())
		{
			grid->AppendRows(1);
		}

		tempBook = tempBook->next;
	}
	if (maxItem == 0)
	{
		count = 1;
		return;
	}
	string bookCode = string(grid->GetCellValue(maxItem - 1, 0).mb_str());
	string numberText = "";
	for (int i = 4; i < bookCode.length(); i++)
	{
		numberText += bookCode[i];
	}

	count = checkInput->CastStringToNumber(numberText) + 1;
}
bool DisplayListBook::CheckPos(wxString text)
{
	return checkInput->HasNumberAlphabetAndComma(text);
}

void DisplayListBook::OnKeyDownTextCltrToUpper(wxCommandEvent& _rCommandEvent)
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

void DisplayListBook::OnSelectingGrid(wxGridRangeSelectEvent& WXUNUSED(event))
{
	if (grid->IsSelection())
	{
		grid->ClearSelection();
	}
}
void DisplayListBook::OnSelectedGrid(wxCommandEvent& WXUNUSED(event))
{
	if (isModeDelete)
	{
		return;
	}
	grid->ClearSelection();
}
void DisplayListBook::OnSelectedLabelGrid(wxCommandEvent& WXUNUSED(event))
{
	if (grid->IsSelection())
	{
		grid->ClearSelection();
	}
}
void DisplayListBook::OnSelectedCell(wxGridEvent& event)
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
void DisplayListBook::OnGridTexting(wxCommandEvent& event)
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
int DisplayListBook::GetMaxLength(int col)
{
	if (col == 1)
	{
		return 1;
	}
	else if (col == 2)
	{
		return 17;
	}
	return -1;

}

void DisplayListBook::SetModeDelete(bool state)
{
	for (int i = 0; i < maxItem; i++)
	{
		for (int j = 1; j < 3; j++)
		{
			grid->SetReadOnly(i, j, state);
		}
	}
}


BEGIN_EVENT_TABLE(DisplayListBook, wxFrame)
EVT_CHAR_HOOK(DisplayListBook::OnKeyDown)
EVT_SHOW(DisplayListBook::OnShow)
END_EVENT_TABLE()
