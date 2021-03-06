#include "ReaderCard.h"
ReaderCard::ReaderCard(const wxString& title) :wxFrame
(NULL, -1, title, wxPoint(-1, -1), wxSize(1280, 680))
{
	srand((ulong)time(0));//for random number
	//backend
	numberRowIsFilled = 0;
	//frontend
	//colors
	wxColour lightYellow, lightBlue, lightRed, red;
	lightYellow.Set(wxT("#E0EBB7"));
	lightBlue.Set(wxT("#7FB1E3"));
	lightRed.Set(wxT("#FA8E8E"));
	red.Set(wxT("#F74A4A"));

	wxPanel* mainPanel = new wxPanel(this, -1);
	//create NoteBook
	noteBook = new wxNotebook(mainPanel, -1, wxPoint(-1, -1), wxSize(300, 300), wxNB_TOP);
	//Draw label title 
	wxPanel* labelTitleBackGround = new wxPanel(mainPanel, -1, wxPoint(-1, -1), wxSize(500, 50));
	enterTextBackGround = new wxPanel(noteBook, -1, wxPoint(-1, -1), wxSize(300, 300));
	searchTextBackGround = new wxPanel(noteBook, -1, wxPoint(-1, -1), wxSize(300, 300));
	guidePanel = new wxPanel(mainPanel, -1, wxPoint(-1, -1), wxSize(450, 500));
	hotKeyPanel = new wxPanel(mainPanel, -1, wxPoint(130, 590), wxSize(550, 30));
	wxStaticText* labelText = new wxStaticText(labelTitleBackGround, -1,
		wxT("DANH SACH THE DOC"), wxPoint(50, -1), wxSize(350, 30));
	checkInput->SetTextSize(labelText, 30);
	//create label guide user
	wxStaticText* labelGuide = new wxStaticText(mainPanel, -1, "HUONG DAN",
		wxPoint(-1, -1), wxSize(100, 15), wxALIGN_CENTRE_HORIZONTAL);
	labelGuide->SetBackgroundColour(lightRed);
	//Box sizers
	mainHBox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* listBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vRightBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vGuideBox = new wxBoxSizer(wxVERTICAL);

	listBox->Add(labelTitleBackGround, 0, wxALIGN_CENTER);
	//Create choice

	//create grid;
	grid = new wxGrid(mainPanel, -1, wxDefaultPosition, wxSize(708, 500), wxEVT_GRID_CELL_CHANGED);
	grid->CreateGrid(DefaultRows, 5);
	//Create Button
	wxButton* exitMenuButton = new wxButton(mainPanel, CARD_MENU,
		wxT("EXIT MENU"), wxPoint(-1, -1), wxSize(100, 30));
	//Set BoxSizer
	//Set name for label
	grid->SetColLabelValue(0, wxT("MA THE"));
	grid->SetColLabelValue(1, wxT("HO"));
	grid->SetColLabelValue(2, wxT("TEN"));
	grid->SetColLabelValue(3, wxT("PHAI"));
	grid->SetColLabelValue(4, wxT("TRANG THAI THE"));
	for (int i = 0; i < 5; i++)
	{
		if (i == 4 || i == 2 || i == 1) { grid->SetColSize(i, 142); continue; }
		if (i == 3) { grid->SetColSize(i, 75); continue; }
		grid->SetColSize(i, 107);
	}

	grid->DisableDragColSize();
	grid->DisableDragRowSize();
	grid->SetSelectionMode(wxGrid::wxGridSelectionModes::wxGridSelectRows);
	for (int i = 0; i < grid->GetNumberRows(); i++)
	{
		grid->SetReadOnly(i, 0);
	}
	listBox->Add(grid, 0, wxTOP, 10);
	listBox->Add(exitMenuButton, 0, wxTOP | wxLEFT, 10);
	mainHBox->Add(listBox, 0, wxTOP, 20);
	CreateEnterArea();
	CreateSearchArea();
	CreateHotKeyArea();
	MakeEnCodeText();
	//LoadFile();
	guidePanel->SetBackgroundColour(lightYellow);

	vRightBox->Add(noteBook, 0, wxTOP, 80);
	vGuideBox->Add(labelGuide, 0, wxLEFT, 175);
	vGuideBox->Add(guidePanel, 0, wxBOTTOM, 5);

	vRightBox->Add(vGuideBox, 0, wxTOP, 10);
	mainHBox->Add(vRightBox, 0, wxLEFT | wxBOTTOM, 40);

	noteBook->AddPage(enterTextBackGround, wxT("NHAP"));
	noteBook->AddPage(searchTextBackGround, wxT("TIM KIEM"));
	//Register event
	Bind(wxEVT_SHOW, &ReaderCard::OnShow, this);
	Bind(wxEVT_TEXT_ENTER, &ReaderCard::OnEnter, this);
	grid->Bind(wxEVT_GRID_CELL_CHANGED, &ReaderCard::EditCurrentCell, this);
	noteBook->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &ReaderCard::OnChangedPageNoteBook, this);
	Connect(SAVE_FILE, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(ReaderCard::OnSave));
	Connect(CARD_MENU, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(ReaderCard::OnCardMenu));

	grid->Bind(wxEVT_GRID_RANGE_SELECTING, &ReaderCard::OnSelectingGrid, this);
	grid->Bind(wxEVT_GRID_SELECT_CELL, &ReaderCard::OnSelectedGrid, this);
	grid->Bind(wxEVT_GRID_LABEL_LEFT_CLICK, &ReaderCard::OnSelectedLabelGrid, this);
	grid->Bind(wxEVT_CHAR_HOOK, &ReaderCard::OnGridKeyDown, this);
	grid->Bind(wxEVT_GRID_SELECT_CELL, &ReaderCard::OnSelectedCell, this);
	grid->Bind(wxEVT_TEXT, &ReaderCard::OnGridTexting, this);
	//SetSizer for mainPanel runs on it
	mainPanel->SetSizer(mainHBox);
	//Create Menu bar
	file = new wxMenu;
	menuBar = new wxMenuBar;
	wxMenuItem* save = new wxMenuItem(file, SAVE_FILE, wxT("&SAVE"));
	file->Append(save);
	menuBar->Append(file, wxT("&FILE"));
	SetMenuBar(menuBar);
	Centre();
	//Set colors
	enterTextBackGround->SetBackgroundColour(lightYellow);
	searchTextBackGround->SetBackgroundColour(lightYellow);
	hotKeyPanel->SetBackgroundColour(lightYellow);
	labelTitleBackGround->SetBackgroundColour(lightBlue);
	exitMenuButton->SetBackgroundColour(red);

}

void ReaderCard::CreateEnterArea()
{
	wxColour lightBlue2, lightGreen, defaultColor;
	lightBlue2.Set(wxT("#9AD6E6"));
	lightGreen.Set(wxT("#ACE39D"));
	defaultColor.Set(wxT("#E0E0E0"));
	enterText = new wxTextCtrl * [4];
	/*sexCheckBox = new wxCheckBox * [2];
	stateCheckBox = new wxCheckBox * [2];*/
	wxStaticText** labelText = new wxStaticText * [4];
	labelText[0] = new wxStaticText(enterTextBackGround, -1, wxT("HO: "), wxPoint(10, 10));
	labelText[1] = new wxStaticText(enterTextBackGround, -1, wxT("TEN: "), wxPoint(10, 60));
	labelText[2] = new wxStaticText(enterTextBackGround, -1, wxT("PHAI: "), wxPoint(10, 110));
	labelText[3] = new wxStaticText(enterTextBackGround, -1, wxT("TRANG THAI THE: "), wxPoint(10, 160));
	for (int i = 0; i < 4; i++)
	{
		enterText[i] = new wxTextCtrl(enterTextBackGround, -1, wxT(""),
			wxPoint(10, 30 * (i + 1) + i * 20), wxSize(170, -1), wxTE_CENTER | wxTE_PROCESS_ENTER);
		enterText[i]->SetBackgroundColour(lightBlue2);
		enterText[i]->Connect(wxID_ANY, wxEVT_COMMAND_TEXT_UPDATED,
			(wxObjectEventFunction)&ReaderCard::OnKeyDownTextCltrToUpper);

	}
	enterText[0]->SetMaxLength(16);
	enterText[1]->SetMaxLength(7);
	enterText[2]->SetMaxLength(1);
	enterText[3]->SetMaxLength(1);

	GuideToUser();
}
void ReaderCard::CreateSearchArea()
{
	wxColour lightBlue2, lightGreen;
	lightBlue2.Set(wxT("#9AD6E6"));
	lightGreen.Set(wxT("#ACE39D"));
	displayText = new wxTextCtrl * [5];
	wxStaticText** labelText2 = new wxStaticText * [5];
	labelText2[0] = new wxStaticText(searchTextBackGround, -1, wxT("MA THE "), wxPoint(120, 10));
	labelText2[1] = new wxStaticText(searchTextBackGround, -1, wxT("HO: "), wxPoint(10, 60));
	labelText2[2] = new wxStaticText(searchTextBackGround, -1, wxT("TEN: "), wxPoint(10, 110));
	labelText2[3] = new wxStaticText(searchTextBackGround, -1, wxT("PHAI: "), wxPoint(10, 160));
	labelText2[4] = new wxStaticText(searchTextBackGround, -1, wxT("TRANG THAI THE: "), wxPoint(10, 210));

	displayText[0] = new wxTextCtrl(searchTextBackGround, -1, wxT(""),
		wxPoint(60, 30 * (0 + 1) + 0 * 20), wxSize(170, -1), wxTE_CENTER | wxTE_PROCESS_ENTER);
	displayText[0]->SetBackgroundColour(lightBlue2);
	for (int i = 1; i < 5; i++)
	{
		displayText[i] = new wxTextCtrl(searchTextBackGround, -1, wxT(""),
			wxPoint(10, 30 * (i + 1) + i * 20), wxSize(170, -1),
			wxTE_CENTER | wxTE_PROCESS_ENTER | wxTE_READONLY);
		displayText[i]->SetBackgroundColour(*wxWHITE);
	}
}
void ReaderCard::CreateHotKeyArea()
{
	wxStaticText* hotKeyText = new wxStaticText(hotKeyPanel, -1,
		wxT("F2-SAVE, F9-MO HOAC TAT CHE DO XOA (DELETE-XOA THE DOC GIA,ENTER-NHAP THE DOC GIA)"),
		wxPoint(10, 10), wxSize(-1, -1), wxALIGN_CENTRE);
}
void ReaderCard::GuideToUser()
{
	wxColour orange, lightOrange;
	orange.Set(wxT("#FF9B70"));
	lightOrange.Set(wxT("#FCD2C0"));

	wxStaticText* cardCodeText = new wxStaticText(guidePanel, -1, wxT("MA DOC GIA "),
		wxPoint(10, 20), wxSize(100, 20));
	wxStaticText* cardCodeGuide = new wxStaticText(guidePanel, -1,
		wxT(": DUOC CHUONG TRINH LAY TU DONG"),
		wxPoint(130, 20), wxSize(300, 20));
	wxStaticText* firstNameText = new wxStaticText(guidePanel, -1, wxT("HO DOC GIA "),
		wxPoint(10, 50), wxSize(100, 20));
	wxStaticText* firstNameGuide = new wxStaticText(guidePanel, -1,
		wxT(": TOI DA 16 KI TU, CHI LAY KI TU CHU"),
		wxPoint(130, 50), wxSize(300, 20));
	wxStaticText* lastNameText = new wxStaticText(guidePanel, -1, wxT("TEN DOC GIA "),
		wxPoint(10, 80), wxSize(100, 20));
	wxStaticText* lastNameGuide = new wxStaticText(guidePanel, -1,
		wxT(": TOI DA 7 KI TU, CHI LAY KI TU CHU"),
		wxPoint(130, 80), wxSize(300, 20));
	wxStaticText* sexText = new wxStaticText(guidePanel, -1, wxT("PHAI"),
		wxPoint(10, 110), wxSize(100, 20));
	wxStaticText* sexGuide = new wxStaticText(guidePanel, -1,
		wxT(": 0 = NAM, 1 = NU"),
		wxPoint(130, 110), wxSize(300, 20));
	wxStaticText* stateText = new wxStaticText(guidePanel, -1, wxT("TRANG THAI THE "),
		wxPoint(10, 140), wxSize(100, 20));
	wxStaticText* stateGuide = new wxStaticText(guidePanel, -1,
		wxT(": 0 = THE BI KHOA, 1 = THE HOAT DONG"),
		wxPoint(130, 140), wxSize(300, 20));

}
void ReaderCard::OnKeyDownTextCltrToUpper(wxCommandEvent& _rCommandEvent)
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
void ReaderCard::OnEnter(wxCommandEvent& WXUNUSED(event))
{
	if (noteBook->GetSelection() == 0)
	{
		SetDefaultColorForRow();
		SaveToList(enterText, 4, count);
	}
	else if (noteBook->GetSelection() == 1)
	{
		SearchOnList();
	}

}
void ReaderCard::SaveToList(wxTextCtrl** textCtrlList, int length, int& pos)
{
	for (int j = 0; j < length; j++)
	{
		if (IsWhiteSpaceAllText(textCtrlList[j]))
		{
			wxMessageBox(textCtrlList[j]->GetValue());
			ErrorMessageBox(pos, "Chua Nhap Thong Tin Du ");
			return;
		}
	}
	ModifyTextInput(textCtrlList[3]);
	int i = 0;
	if (pos == grid->GetNumberRows())
	{
		grid->AppendRows(1);
		for (int i = pos; i < grid->GetNumberRows(); i++)
		{
			grid->SetReadOnly(i, 0);
		}
	}
	ulong cardCode = 0;
	wxString wxStrCode;
	WriteHashCode(textCtrlList, cardCode, wxStrCode);
	numberRowIsFilled++;
	for (int i = 0; i < grid->GetNumberRows(); i++)
	{
		wxString cardCodeStr = grid->GetCellValue(i, 0);
		ulong tempCardCode = CastWxStringToUlong(cardCodeStr);
		if (tempCardCode > cardCode || tempCardCode == 0)
		{
			pos = i;
			grid->InsertRows(pos, 1);
			grid->SetReadOnly(pos, 0);
			grid->SetCellValue(pos, 0, wxStrCode);
			grid->SetCellAlignment(pos, 0, wxALIGN_CENTER, wxALIGN_CENTER);
			break;
		}
	}
	for (i = 1; i < 5; i++)
	{
		ModifyTextInput(textCtrlList[i - 1]);
		grid->SetCellValue(pos, i, textCtrlList[i - 1]->GetValue());
		grid->SetCellAlignment(pos, i, wxALIGN_CENTER, wxALIGN_CENTER);

	}
	CardReader* cardReader = CreateCardReader(textCtrlList, cardCode);
	cardReaderTree->Add(cardReader);
	for (int i = 0; i < 4; i++)
	{
		textCtrlList[i]->Clear();
	}
	textCtrlList[0]->SetFocus();
	count++;
	if (pos == grid->GetNumberRows())
	{
		grid->AppendRows(1);
		for (int i = pos; i < grid->GetNumberRows(); i++)
		{
			grid->SetReadOnly(i, 0);
		}
	}
}
void ReaderCard::SearchOnList()
{
	wxColor organColor;
	organColor.Set(wxT("#FFAB03"));
	wxString cardCodeStr = displayText[0]->GetValue();
	displayText[0]->Clear();
	ulong cardCode = CastWxStringToUlong(cardCodeStr);
	SetDefaultColorForRow();
	if (cardCode != 0)
	{
		for (int i = 0; i < grid->GetNumberRows(); i++)
		{
			ulong tempCardCode = CastWxStringToUlong(grid->GetCellValue(i, 0));
			if (tempCardCode == cardCode)
			{
				rowChangedColor = i;
				for (int j = 0; j < 5; j++)
				{
					grid->SetCellBackgroundColour(i, j, organColor);
					if (j == 4) { break; }
					displayText[j + 1]->SetValue(grid->GetCellValue(i, j + 1));
				}
				grid->Refresh();
				return;
			}
		}
	}
	wxMessageBox(wxString::Format("Khong the tim thay thong tin ma the yeu cau"));
}
void ReaderCard::OnChangedPageNoteBook(wxCommandEvent& WXUNUSED(event))
{
	if (noteBook->GetSelection() == 0)
	{
		SetDefaultColorForRow();
	}
}
void ReaderCard::MainKeyDown(int keyCode)
{
	if (keyCode == WXK_F2)
	{
		SaveFile();
	}
	if (keyCode == WXK_F9)
	{
		isModeDelete = !isModeDelete;
		grid->ClearSelection();
		SetModeDelete(isModeDelete);
	}

	if (keyCode == WXK_DELETE)
	{
		ShowMessageClear();
	}
	if (keyCode == WXK_DOWN)
	{
		checkInput->MoveDownToAnotherTextCtrl(enterText, 4);
	}
	if (keyCode == WXK_UP)
	{
		checkInput->MoveUpToAnotherTextCtrl(enterText, 4);
	}

}
void ReaderCard::OnKeyDown(wxKeyEvent& event)
{
	event.StopPropagation();
	int keyCode = event.GetKeyCode();
	MainKeyDown(keyCode);
	if (enterText[2]->HasFocus() || enterText[3]->HasFocus())
	{
		if (checkInput->HasInRangeNumber(keyCode, 0, 1) || checkInput->HasRightEntering(keyCode, false))
		{
			event.Skip();
			if (checkInput->HasInRangeNumber(keyCode, 0, 1))
			{
				int i = keyCode - '0';
				if (enterText[2]->HasFocus())
				{
					enterText[2]->SetValue(sexText[i]);
				}
				else if (enterText[3]->HasFocus())
				{
					enterText[3]->SetValue(checkInput->GetCardState(i));
				}
			}

		}
		else
		{
			return;
		}
	}
	if (enterText[0]->HasFocus() || enterText[1]->HasFocus())
	{
		if (checkInput->HasAlpha(keyCode) || checkInput->HasRightEntering(keyCode, true))
		{
			event.Skip();
		}
		else return;
	}

	event.Skip();
}
void ReaderCard::OnGridKeyDown(wxKeyEvent& event)
{
	event.StopPropagation();
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

		if (checkInput->HasAlpha(keyCode) || checkInput->HasRightEntering(keyCode, true))
		{
			event.Skip();
			
		}
	}
	else if (col == 2)
	{
		if (checkInput->HasAlpha(keyCode) || checkInput->HasRightEntering(keyCode, true))
		{
			event.Skip();
		}
	}
	else if (col == 3||col==4)
	{
		if (checkInput->HasInRangeNumber(keyCode, 0, 1) || checkInput->HasRightEntering(keyCode, false))
		{
			event.Skip();
			if (checkInput->HasInRangeNumber(keyCode, 0, 1))
			{
				int i = keyCode - '0';
				grid->SetCellValue(row, col, wxT(""));
				if (col == 3)
				{
					grid->SetCellValue(row, col, (sexText[i]));
					EditData(row,col);
				}
				else if (col == 4)
				{
					grid->SetCellValue(row, col, checkInput->GetCardState(i));
					EditData(row,col);
				}

			}
		}
	}
}
void ReaderCard::SetModeDelete(bool state)
{
	for (int i = 0; i < numberRowIsFilled; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			grid->SetReadOnly(i, j, state);
		}
	}
}
void ReaderCard::OnSave(wxCommandEvent& WXUNUSED(event))
{
	SaveFile();
}
void ReaderCard::OnCardMenu(wxCommandEvent& WXUNUSED(event))
{
	this->GetParent()->Show(true);
	this->Show(false);
}
void ReaderCard::OnShow(wxShowEvent& event)
{
	if (event.IsShown())
	{
		isModeDelete = false;

		grid->ClearSelection();
		if (numberRowIsFilled > 30)
		{
			grid->DeleteRows(30, numberRowIsFilled - 30);
		}
		numberRowIsFilled = cardReaderTree->GetNumberNodes();
		LoadData();
		SetModeDelete(false);
		noteBook->SetSelection(0);
	}
	event.Skip();
}
void ReaderCard::SetDefaultColorForRow()
{
	if (rowChangedColor == -1) { return; }
	for (int j = 0; j < 5; j++)
	{
		grid->SetCellBackgroundColour(rowChangedColor, j, *wxWHITE);
		if (j == 4) { break; }
		displayText[j + 1]->Clear();
	}
	grid->Refresh();
	rowChangedColor = -1;
}
void ReaderCard::SaveFile()
{
	ISaveFile* isaveFile = dynamic_cast<ISaveFile*>(this->GetParent());
	isaveFile->SaveFile();
}
void ReaderCard::LoadData()
{
	//cardReaderTree->Clear();
	CardReader** arr = cardReaderTree->ToSortArray();//new CardReader * [numberRowIsFilled];
	//saveFile->ReadFile(arr);
	if (numberRowIsFilled > grid->GetNumberRows())
	{
		grid->AppendRows(numberRowIsFilled - grid->GetNumberRows() + 1);
	}

	for (int i = 0; i < numberRowIsFilled; i++)
	{
		ulong cardCode = arr[i]->GetCardCode();
		wxString cardCodeStr = EditCardCode(cardCode, 10);
		grid->SetCellValue(i, 0, cardCodeStr);
		grid->SetCellValue(i, 1, arr[i]->GetFirstName());
		grid->SetCellValue(i, 2, arr[i]->GetLastName());
		grid->SetCellValue(i, 3, arr[i]->GetSex());
		grid->SetCellValue(i, 4, arr[i]->GetState());
		for (int j = 0; j < 5; j++)
		{
			if (j == 0)
			{
				grid->SetReadOnly(i, j);
			}
			grid->SetCellAlignment(i, j, wxALIGN_CENTER, wxALIGN_CENTER);
		}

	}
	delete[]arr;
}
void ReaderCard::DeleteSelectedRows()
{
	if (grid->IsSelection())
	{
		int row = grid->GetSelectedRows()[0];
		wxString cardCodewxstr = grid->GetCellValue(row, 0);
		if (cardCodewxstr == "") { return; }
		ulong cardCode = CastWxStringToUlong(cardCodewxstr);

		//wxMessageBox(wxString::Format("%i",cardCode));

		BorrowBookList* tempList = cardReaderTree->Search(cardCode)
			->data->GetListBorrowBook();
		if (tempList->Length() > 0)
		{
			DoublyNode<BorrowBook>* tempCard = tempList->First();
			while (tempCard != nullptr)
			{
				if (tempCard->data.GetStateBorrow() == 0)
				{
					wxMessageBox("THE DOC CO SACH DANG MUON -> KHONG THE XOA");
					return;
				}
				tempCard = tempCard->next;
			}
		}

		cardReaderTree->Delete(cardCode);
		delete tempList;
		numberRowIsFilled--;
		grid->DeleteRows(row, 1);

		if (row < count)
		{
			count--;
		}
		if (grid->GetNumberRows() < DefaultRows)
		{
			int numberRowsNeed = DefaultRows - grid->GetNumberRows();

			grid->AppendRows(numberRowsNeed);
		}

	}
	count = count < 0 ? 0 : count;
	//wxMessageBox(wxString::Format("Key pressed: %d", count));
}
void ReaderCard::ShowMessageClear()
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
void ReaderCard::ModifyTextInput(wxTextCtrl* textCtrl)
{
	wxString wxStr = textCtrl->GetLineText(0);
	ModifyTextInput(wxStr);
	textCtrl->SetLabelText(wxStr);
}
void ReaderCard::ModifyTextInput(wxString& wxStr)
{
	std::string strText = std::string(wxStr.mb_str());
	ModifyString(strText);
	wxString myWxString(strText.c_str(), wxConvUTF8);
	wxStr = myWxString;
}
void ReaderCard::ModifyString(std::string& strText)
{
	for (int i = 0; i < strText.length(); i++)
	{
		if (strText[i] == ' ' && strText[i + 1] == ' ')
		{
			strText.erase(strText.begin() + i);
			i--;
		}
	}
	if (strText[0] == ' ')
	{
		strText.erase(strText.begin());
	}
	int length = strText.length();
	if (strText[length - 1] == ' ')
	{
		strText.erase(strText.begin() + length - 1);
	}
}
void ReaderCard::ErrorMessageBox(int pos, std::string message)
{
	wxString myWxString(message.c_str(), wxConvUTF8);
	wxMessageBox(myWxString);
	if (pos < 0) { return; }
	if (noteBook->GetSelection() == 1) { grid->DeleteRows(pos, 1); }
}
void ReaderCard::MakeEnCodeText()
{
	stateText = new std::string[2]{ "KHOA","HOAT DONG" };
	sexText = new std::string[2]{ "NAM","NU" };
}
void ReaderCard::EditCurrentCell(wxGridEvent& event)
{
	int row = grid->GetGridCursorRow();
	int col = grid->GetGridCursorCol();
	wxString wxOldText = event.GetString();
	if (wxOldText == wxT(""))
	{
		ErrorMessageBox(-1, "Khong the chinh chua o nay ");
		grid->SetCellValue(row, col, wxOldText);
		return;
	}
	wxString wxNewText = grid->GetCellValue(row, col);
	//main error
	if (checkInput->IsWhiteSpaceAllText(wxNewText))
	{
		ErrorMessageBox(-1, "Loi Nhap Lieu ");
		grid->SetCellValue(row, col, wxOldText);
		return;
	}

	//col errors
	if (col == 1 || col == 2)
	{
		ModifyTextInput(wxNewText);

		checkInput->UpperWxString(wxNewText);
		grid->SetCellValue(row, col, wxNewText);
	}
	if (col == 3)
	{
		ModifyTextInput(wxNewText);
		int num = checkInput->CastWxStringToInt(wxNewText);
		grid->SetCellValue(row, col, sexText[num]);
	}
	if (col == 4)
	{
		ModifyTextInput(wxNewText);
		int num = checkInput->CastWxStringToInt(wxNewText);
		grid->SetCellValue(row, col, stateText[num]);
	}
	EditData(row,col);
	//wxMessageBox(event.GetString());
	event.Skip();
}
void ReaderCard::EditData(int row,int col)
{
	if (grid->GetCellValue(row, 0) == "")
	{
		checkInput->ErrorMessageBox("Khong the chinh sua o nay");
		grid->SetCellValue(row, col, wxT(""));
		return;
	}
	ulong key = CastWxStringToUlong(grid->GetCellValue(row, 0));
	
	string lastName = string(grid->GetCellValue(row, 1).mb_str());
	string firstName = string(grid->GetCellValue(row, 2).mb_str());
	string sex = string(grid->GetCellValue(row, 3).mb_str());
	string stateStr = string(grid->GetCellValue(row, 4).mb_str());

	//fix bug when edit and have to move list of old card to modified card
	BorrowBookList* tempList = cardReaderTree->Search(key)->data->GetListBorrowBook();
	cardReaderTree->Delete(key);

	CardReader* temp = new CardReader(key, lastName, firstName, sex, stateStr);
	temp->SetListBorrowBook(tempList);
	cardReaderTree->Add(temp);
}
void ReaderCard::WriteHashCode(wxTextCtrl** textCtrlList, ulong& hashCode, wxString& wxStrCode)
{
	hashCode = CreateHashCode();

	std::string strCode = EditCardCode(hashCode, 10);
	wxString wxStr(strCode.c_str(), wxConvUTF8);
	wxStrCode = wxStr;
}
void ReaderCard::CastWxStringIntoString(wxString text, string& str)
{
	str = std::string(text.mb_str());
}

CardReader* ReaderCard::CreateCardReader(wxTextCtrl** textCtrlList, ulong cardCode)
{
	string firstName = "";
	string lastName = "";
	string sex = "";
	string state = "";
	CastWxStringIntoString(textCtrlList[0]->GetValue(), firstName);
	CastWxStringIntoString(textCtrlList[1]->GetValue(), lastName);
	CastWxStringIntoString(textCtrlList[2]->GetValue(), sex);
	CastWxStringIntoString(textCtrlList[3]->GetValue(), state);
	return new CardReader(cardCode, firstName, lastName, sex, state);
}
bool ReaderCard::IsWhiteSpaceAllText(wxTextCtrl* textCtrl)
{
	return checkInput->IsWhiteSpaceAllText(textCtrl->GetLineText(0));
}
string ReaderCard::EditCardCode(ulong number, int maxLengthCode)
{
	std::string codeReader = "";
	std::string rawCodeReader = "";
	int lengthNumber = 0;
	while (number != 0)
	{
		int tempNumber = number;
		for (int i = 0; i < 10; i++)
		{
			tempNumber -= i;
			if (tempNumber % 10 == 0)
			{
				lengthNumber++;
				number -= i;
				number /= 10;
				rawCodeReader += (i + '0');
			}
			tempNumber = number;
		}
	}
	//reverse string
	std::reverse(rawCodeReader.begin(), rawCodeReader.end());
	for (int i = 0; i < maxLengthCode - lengthNumber; i++)
	{
		codeReader += "0";
	}
	codeReader += rawCodeReader;
	return codeReader;
}
int ReaderCard::CastWxStringToInt(wxTextCtrl* textCtrl)
{
	wxString wxStr = textCtrl->GetLineText(0);
	return checkInput->CastWxStringToInt(wxStr);
}
ulong ReaderCard::CastWxStringToUlong(wxString wxStr)
{
	if (wxStr == "") { return 0; }
	int i, j;
	ulong number = 0;
	string strText = string(wxStr.mb_str());
	for (i = strText.length() - 1, j = 0; i >= 0; i--, j++)
	{
		if (strText[i] < '0' || strText[i]>'9')
		{
			return -1;
		}
		number += (strText[i] - '0') * pow(10, j);
	}
	return number;
}
ulong ReaderCard::CreateHashCode()
{

	ulong r;
	for (int i = 0; i < 1000; i++)
	{
		r = RandomNumber(1, 99999999);
		if (cardReaderTree->IsDifferentNode(r)) { break; }
	}
	return r;
}
ulong ReaderCard::RandomNumber(ulong minNumber, ulong maxNumber)
{

	return minNumber + rand() % (maxNumber + 1 - minNumber);
}

void ReaderCard::OnSelectingGrid(wxGridRangeSelectEvent& WXUNUSED(event))
{
	grid->ClearSelection();
}
void ReaderCard::OnSelectedGrid(wxCommandEvent& WXUNUSED(event))
{
	if (isModeDelete) { return; }
	grid->ClearSelection();
}
void ReaderCard::OnSelectedLabelGrid(wxCommandEvent& WXUNUSED(event))
{
	grid->ClearSelection();
}
void ReaderCard::OnSelectedCell(wxGridEvent& event)
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
void ReaderCard::OnGridTexting(wxCommandEvent& event)
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
int ReaderCard::GetMaxLength(int col)
{
	if (col < 1 || col>4) { return -1; }
	if (col == 1)
	{
		return 16;
	}
	else if (col == 2)
	{
		return 7;
	}
	else
	{
		return 1;
	}
}
void ReaderCard::SetData(BSTree<CardReader>* cardReaders,
	CheckInput* checkInput)
{
	this->cardReaderTree = cardReaders;
	this->checkInput = checkInput;
}

BEGIN_EVENT_TABLE(ReaderCard, wxFrame)
EVT_CHAR_HOOK(ReaderCard::OnKeyDown)
END_EVENT_TABLE()
