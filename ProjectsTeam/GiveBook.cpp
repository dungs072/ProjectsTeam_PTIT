#include "GiveBook.h"
GiveBook::GiveBook(const wxString& title) :wxFrame(NULL, -1, title,
	wxPoint(-1, -1), wxSize(1280, 680))
{
	//backend
	controlDateTime = new ControlDateTime();
	checkInput = new CheckInput();
	titleList = new TitleList(100);
	saveFileCard = new SaveTextFile<CardReader>("ListReaders.txt");
	saveFileTitle = new SaveTextFile<Title>("BookTitle.txt");
	treeCardReader = new BSTree<CardReader>();
	listBorrowBook = new BorrowBook * [3];
	listBook = new Book * [3];

	//create color
	wxColor lightOrange;
	lightOrange.Set("#F5DBB8");
	wxColour lightYellow, greenColor, organColor, lightBlue, eggYellow, lightRed, red;
	lightYellow.Set(wxT("#E0EBB7"));
	greenColor.Set(wxT("#03FF29"));
	organColor.Set(wxT("#FFAB03"));
	lightBlue.Set(wxT("#7FB1E3"));
	eggYellow.Set(wxT("#FDFF69"));
	lightRed.Set(wxT("#FA8E8E"));
	red.Set(wxT("#F74A4A"));
	//create panel
	wxPanel* mainPanel = new wxPanel(this, -1);
	searchPanel = new wxPanel(mainPanel, -1, wxPoint(-1, -1), wxSize(300, 250));

	//Create wxStaticText
	wxStaticText* titleSearch = new wxStaticText(searchPanel, -1, wxT("NHAP MA THE DOC GIA"),
		wxPoint(-1, 10), wxSize(300, 20), wxALIGN_CENTER);
	//create Grid
	grid = new wxGrid(mainPanel, -1, wxPoint(-1, -1), wxSize(1200, 123));
	grid->CreateGrid(3, 7);
	grid->SetColLabelValue(0, wxT("TEN SACH"));
	grid->SetColLabelValue(1, wxT("MA SACH"));
	grid->SetColLabelValue(2, wxT("NGAY MUON"));
	grid->SetColLabelValue(3, wxT("NGAY TRA"));
	grid->SetColLabelValue(4, wxT("SO NGAY DA MUON"));
	grid->SetColLabelValue(5, wxT("VI TRI SACH"));
	grid->SetColLabelValue(6, wxT("TRANG THAI"));

	for (int i = 0; i < 7; i++)
	{
		if (i == 0 || i == 5 || i == 6) { grid->SetColSize(i, 200); continue; }
		if (i == 3||i==2||i==4) { grid->SetColSize(i, 130); continue; }
		grid->SetColSize(i, 126);
	}
	for (int i = 0; i < 3; i++)
	{
		grid->SetRowSize(i, 30);
	}
	grid->DisableDragColSize();
	grid->DisableDragRowSize();
	grid->SetSelectionMode(wxGrid::wxGridSelectionModes::wxGridSelectRows);
	for (int i = 0; i < grid->GetNumberRows(); i++)
	{
		for (int j = 0; j < grid->GetNumberCols(); j++)
		{
			grid->SetReadOnly(i, j);
		}
	}
	//Create wxCtrlText
	enterText = new wxTextCtrl(searchPanel,-1,wxT(""),
		wxPoint(50,30),wxSize(200,25), wxTE_CENTER | wxTE_PROCESS_ENTER);
	enterText->SetMaxLength(10);
	focusText = new wxTextCtrl(mainPanel, -1, wxT(""), wxPoint(-1, -1), wxSize(-1, -1));
	focusText->Hide();

	//date choice
	dialog = new wxDialog(this, -1, wxT("NGAY TRA"),
		wxPoint(-1, -1), wxSize(300, 300));
	for (int i = 0; i < 31; i++)
	{
		dayArray.Add(controlDateTime->GetDay()[i]);
		if (i < 12)
		{
			monthArray.Add(controlDateTime->GetMonth()[i]);
		}
		if (i <= 20)
		{
			yearArray.Add(controlDateTime->GetYear()[i]);
		}
	}
	dayChoice = new wxChoice(dialog, -1, wxPoint(15, 100), wxSize(50, 20), dayArray);
	monthChoice = new wxChoice(dialog, -1, wxPoint(115, 100), wxSize(50, 20), monthArray);
	yearChoice = new wxChoice(dialog, -1, wxPoint(200, 100), wxSize(75, 20), yearArray);
	//Create button
	okButton = new wxButton(dialog, -1, wxT("OK"), wxPoint(125, 200), wxSize(50, 20));
	cancelButton = new wxButton(dialog, -1, wxT("CANCEL"), wxPoint(200, 200), wxSize(50, 20));
	giveBookButton = new wxButton(mainPanel, -1, wxT("TRA SACH"), 
								wxPoint(-1, -1), wxSize(100, -1));
	lostBookButton = new wxButton(mainPanel, -1, wxT("BAO MAT SACH"), 
								wxPoint(-1, -1), wxSize(100, -1));
	wxButton* exitMenuButton = new wxButton(mainPanel, -1, wxT("EXIT MENU"),
		wxPoint(20, 600), wxSize(-1, -1));

	//create boxsizer
	wxBoxSizer* mainVBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* mainHBox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hButtonBox = new wxBoxSizer(wxHORIZONTAL);
	//Set box sizer
	hButtonBox->Add(giveBookButton, 0,wxRIGHT,20);
	hButtonBox->Add(lostBookButton, 0 );
	mainHBox->Add(searchPanel, 0, wxLEFT|wxRIGHT,475);
	mainVBox->Add(mainHBox,0,wxTOP,30);
	mainVBox->Add(grid, 0,wxALIGN_CENTRE_HORIZONTAL|wxTOP,75);
	mainVBox->Add(hButtonBox, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
	//Register event
	Bind(wxEVT_SHOW, &GiveBook::OnShow, this);
	Bind(wxEVT_TEXT_ENTER, &GiveBook::OnEnter, this);
	grid->Bind(wxEVT_GRID_RANGE_SELECTING, &GiveBook::OnSelectingGrid, this);
	grid->Bind(wxEVT_GRID_SELECT_CELL, &GiveBook::OnSelectedGrid, this);
	grid->Bind(wxEVT_GRID_LABEL_LEFT_CLICK, &GiveBook::OnSelectedLabelGrid, this);
	giveBookButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &GiveBook::OnGiveBook, this);
	lostBookButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &GiveBook::OnLostBook, this);
	okButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		&GiveBook::OnOkButton, this);
	cancelButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		&GiveBook::OnCancelButton, this);

	exitMenuButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		&GiveBook::OnExitMenuButton, this);

	dialog->Bind(wxEVT_SHOW, &GiveBook::OnShowDialog, this);
	//Set Color
	searchPanel->SetBackgroundColour(lightYellow);
	exitMenuButton->SetBackgroundColour(red);

	CreateDisplayInforCard();
	mainPanel->SetSizer(mainVBox);
	Centre();
}
void GiveBook::CreateDisplayInforCard()
{
	wxColor lightBlue;
	lightBlue.Set(wxT("#7FB1E3"));
	displayTitleText = new wxStaticText * [3];
	displayText = new wxStaticText * [3];
	displayTitleText[0] = new wxStaticText(searchPanel, -1, wxT("HO VA TEN:"),
		wxPoint(20, 75), wxSize(100, 15));
	displayTitleText[1] = new wxStaticText(searchPanel, -1, wxT("PHAI:"),
		wxPoint(20, 125), wxSize(100, 15));
	displayTitleText[2] = new wxStaticText(searchPanel, -1, wxT("TRANG THAI:"),
		wxPoint(20, 175), wxSize(100, 15));

	for (int i = 0; i < 3; i++)
	{
		displayText[i] = new wxStaticText(searchPanel, -1, wxT(""),
			wxPoint(20, 95 + i * 50), wxSize(260, 25),wxALIGN_CENTER);
		displayText[i]->SetBackgroundColour(lightBlue);
	}
}
void GiveBook::OnShow(wxShowEvent& event)
{
	if (event.IsShown())
	{
		LoadFile();
		ClearOldDataOnPanel();
		ClearOldDataOnGrid();
		ClearOldDataInBackEnd();
		enterText->Clear();
		foundCard = nullptr;
		hasRightSelection = false;
		bookCodeSelected = "";
		index = -1;
	}
	event.Skip();
}
void GiveBook::OnEnter(wxCommandEvent& WXUNUSED(event))
{
	if (grid->IsSelection())
	{
		grid->ClearSelection();
	}
	string keyCodeStr = string(enterText->GetValue().mb_str());
	ulong keyCode = checkInput->CastStringToNumber(keyCodeStr);
	BSTNode<CardReader>* tempNode = treeCardReader->Search(keyCode);
	ClearOldDataOnGrid();
	ClearOldDataInBackEnd();
	if (tempNode == nullptr)
	{
		checkInput->ErrorMessageBox("KHONG TIM THAY THE DOC");
		foundCard = nullptr;
		hasRightSelection = false;
		bookCodeSelected = "";
		ClearOldDataOnPanel();
		return;
	}
	hasRightSelection = false;
	bookCodeSelected = "";
	focusText->SetFocus();
	enterText->Clear();
	foundCard = tempNode->data;
	DisplayCardOnPanel();
	FindInforBorrowBook();
}
void GiveBook::OnKeyDown(wxKeyEvent& event)
{
	int keyCode = event.GetKeyCode();
	if (enterText->HasFocus())
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
	if (keyCode == WXK_F2)
	{
		SaveFile();
	}

}
void GiveBook::DisplayCardOnPanel()
{
	if (foundCard == nullptr) { return; }
	displayText[0]->SetLabel(foundCard->GetFirstName() + " " + foundCard->GetLastName());
	displayText[1]->SetLabel(foundCard->GetSex());
	displayText[2]->SetLabel(foundCard->GetState());
}
void GiveBook::FindInforBorrowBook()
{
	if (foundCard == nullptr) { return; }
	if (foundCard->GetListBorrowBook()->Length() == 0) { return; }
	DoublyNode<BorrowBook>* tempBorrowBookNode =  foundCard->GetListBorrowBook()->First();
	int i = 0;
	while (tempBorrowBookNode != nullptr)
	{
		BorrowBook borrowBook = tempBorrowBookNode->data;
		if (borrowBook.GetStateBorrow() == 0||borrowBook.GetStateBorrow()==2)
		{
			listBorrowBook[i] = &(tempBorrowBookNode->data);
			string ISBN = borrowBook.GetBookCode().substr(0, 4);
			Title title = *(titleList->GetData(ISBN));
			listBook[i] = &(title.GetListBook()->FindSinglyNode(borrowBook.GetBookCode())->data);
			DisplayBorrowingBook(borrowBook, *listBook[i], title, i);
			i++;
		}
		tempBorrowBookNode = tempBorrowBookNode->next;
	}
	
}
void GiveBook::DisplayBorrowingBook(BorrowBook borrowBook, Book book, Title title,int row)
{
	grid->SetCellValue(row, 0, title.GetBookName());
	grid->SetCellValue(row, 1, borrowBook.GetBookCode());
	grid->SetCellValue(row, 2, borrowBook.GetBorrowDate()->ToString());
	grid->SetCellValue(row, 3, "00/00/0000");
	DateTime* now = new DateTime();
	int numberDayBorrow = *now - *(borrowBook.GetBorrowDate());
	grid->SetCellValue(row, 4, to_string(numberDayBorrow));
	grid->SetCellValue(row, 5, book.GetPos());
	if (numberDayBorrow > 7)
	{
		grid->SetCellValue(row, 6, "QUA 7 NGAY");
	}
	else
	{
		grid->SetCellValue(row, 6, checkInput->GetBorrowBookState(borrowBook.GetStateBorrow()));
	}
	for (int i = 0; i < 7; i++)
	{
		grid->SetCellAlignment(row, i, wxALIGN_CENTER, wxALIGN_CENTER);
	}
	delete now;
}
void GiveBook::ClearOldDataOnPanel()
{
	for (int i = 0; i < 3; i++)
	{
		displayText[i]->SetLabel("");
	}
}
void GiveBook::ClearOldDataOnGrid()
{
	if (grid->IsSelection())
	{
		grid->ClearSelection();
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			grid->SetCellValue(i, j, "");
		}
	}
}
void GiveBook::ClearOldDataInBackEnd()
{
	for (int i = 0; i < 3; i++)
	{
		listBook[i] = nullptr;
		listBorrowBook[i] = nullptr;
	}
}
void GiveBook::LoadFile()
{
	titleList->GetList()->Clear();
	treeCardReader->Clear();
	lengthCard = saveFileCard->GetSizeArray();
	lengthTitle = saveFileTitle->GetSizeArray();
	CardReader** arrCard = new CardReader * [lengthCard];
	Title** arrTitle = new Title * [lengthTitle];
	saveFileCard->ReadFile(arrCard);
	saveFileTitle->ReadFile(arrTitle);
	for (int i = 0; i < lengthCard; i++)
	{
		treeCardReader->Add(arrCard[i]);
	}
	for (int i = 0; i < lengthTitle; i++)
	{
		titleList->GetList()->AddLast(arrTitle[i]);
	}
	delete []arrTitle;
	delete []arrCard;
}
void GiveBook::SaveFile()
{
	CardReader** arrCard = treeCardReader->ToSameTreeArray();
	Title** arrTitle = titleList->GetList()->ToArray();
	saveFileCard->WriteToFile(arrCard, treeCardReader->GetNumberNodes());
	saveFileTitle->WriteToFile(arrTitle, titleList->GetList()->Length());
	wxMessageBox("LUU FILE THANH CONG");
	// i have to notice to delete memory
}
void GiveBook::OnSelectingGrid(wxGridRangeSelectEvent& WXUNUSED(event))
{
	if (grid->IsSelection())
	{
		grid->ClearSelection();
	}
}
void GiveBook::OnSelectedGrid(wxCommandEvent& WXUNUSED(event))
{
	if (foundCard == nullptr)
	{
		grid->ClearSelection();
		return;
	}
	int row = grid->GetSelectedRows()[0];
	bookCodeSelected = string(grid->GetCellValue(row, 1).mb_str());
	hasRightSelection = bookCodeSelected.length() > 0;
}
void GiveBook::OnSelectedLabelGrid(wxCommandEvent& WXUNUSED(event))
{
	if (grid->IsSelection())
	{
		grid->ClearSelection();
	}
}

void GiveBook::OnGiveBook(wxCommandEvent& WXUNUSED(event))
{
	if (!hasRightSelection) { return; }
	for (int i = 0; i < 3; i++)
	{
		if (listBook[i] == nullptr && listBorrowBook[i] == nullptr) { continue; }
		if (bookCodeSelected == listBorrowBook[i]->GetBookCode())
		{
			index = i;
			dialog->Centre();
			dialog->ShowModal();
			
			break;
		}
	}
	
	hasRightSelection = false;
}
void GiveBook::OnLostBook(wxCommandEvent& WXUNUSED(event))
{
	if (!hasRightSelection) { return; }
	for (int i = 0; i < 3; i++)
	{
		if (listBook[i] == nullptr && listBorrowBook[i] == nullptr) { continue; }
		if (bookCodeSelected == listBorrowBook[i]->GetBookCode())
		{
			listBorrowBook[i]->SetStateBorrow(2);
			//listBook[i]->SetState(0);
			listBorrowBook[i] = nullptr;
			listBook[i] = nullptr;
			break;
		}
	}
	int row = grid->GetSelectedRows()[0];
	grid->SetCellValue(row, 6, checkInput->GetBorrowBookState(2));
	grid->Refresh();
	grid->ClearSelection();
	hasRightSelection = false;
}
void GiveBook::OnYearSelection(wxCommandEvent& WXUNUSED(event))
{
	ProccessYearSelection();
}
void GiveBook::OnMonthSelection(wxCommandEvent& WXUNUSED(event))
{
	ProccessMonthSelection();
}

//5 methods for selecting date 
void GiveBook::ProccessYearSelection()
{
	ProccessMonthSelection();
}
void GiveBook::ProccessMonthSelection()
{
	if (ProccessCurrentDate()) { return; }
	int selection = monthChoice->GetSelection();
	if (selection == 0 || selection == 2 ||
		selection == 4 || selection == 6 ||
		selection == 7 || selection == 9 || selection == 11)
	{
		for (int i = dayArray.GetCount(); i < 31; i++)
		{
			dayArray.Add(controlDateTime->GetDay()[i]);
		}
		int daySelect = min((int)(dayArray.GetCount() - 1), dayChoice->GetSelection());
		dayChoice->Clear();
		dayChoice->Append(dayArray);
		dayChoice->SetSelection(daySelect);
	}
	else if (selection == 1)
	{
		ProccessLeapYear();
	}
	else
	{
		if (dayArray.GetCount() < 31)
		{
			for (int i = dayArray.GetCount(); i < 30; i++)
			{
				dayArray.Add(controlDateTime->GetDay()[i]);
			}
		}
		else if (dayArray.GetCount() == 31)
		{
			dayArray.pop_back();
		}
		else
		{
			for (int i = dayArray.GetCount(); i < 30; i++)
			{
				dayArray.Add(controlDateTime->GetDay()[i]);
			}
		}
		int daySelect = min((int)(dayArray.GetCount() - 1), dayChoice->GetSelection());
		dayChoice->Clear();
		dayChoice->Append(dayArray);
		dayChoice->SetSelection(daySelect);
	}
}
void GiveBook::ProccessLeapYear()
{
	if (ProccessCurrentDate()) { return; }
	string strYear = controlDateTime->GetYear()[yearChoice->GetSelection()];
	int numYear = checkInput->CastWxStringToInt(strYear);
	if (controlDateTime->IsLeapYear(numYear))
	{
		int monthSelection = monthChoice->GetSelection();
		if (monthSelection == 1)
		{
			if (dayArray.GetCount() < 28)
			{
				for (int i = dayArray.GetCount(); i < 28; i++)
				{
					dayArray.Add(controlDateTime->GetDay()[i]);
				}
			}
			else if (dayArray.GetCount() == 28)
			{
				dayArray.Add(controlDateTime->GetDay()[dayArray.GetCount()]);
			}
			else
			{
				for (int i = dayArray.GetCount(); i > 29; i--)
				{
					dayArray.pop_back();
				}
			}

		}
		int daySelect = min((int)(dayArray.GetCount() - 1), dayChoice->GetSelection());
		dayChoice->Clear();
		dayChoice->Append(dayArray);
		dayChoice->SetSelection(daySelect);
	}
	else
	{
		if (dayArray.GetCount() < 28)
		{
			for (int i = dayArray.GetCount(); i < 28; i++)
			{
				dayArray.push_back(controlDateTime->GetDay()[i]);
			}
		}
		else
		{
			for (int i = dayArray.GetCount(); i > 28; i--)
			{
				dayArray.pop_back();
			}
		}
		int daySelect = min((int)(dayArray.GetCount() - 1), dayChoice->GetSelection());
		dayChoice->Clear();
		dayChoice->Append(dayArray);
		dayChoice->SetSelection(daySelect);
	}
}
bool GiveBook::ProccessCurrentDate()
{
	if (yearChoice->GetSelection() == 20)
	{
		if (monthArray.GetCount() > controlDateTime->GetCurrentMonth())
		{
			for (int i = controlDateTime->GetCurrentMonth(); i < 12; i++)
			{
				monthArray.pop_back();
			}
			int monthSelect = min((int)(monthArray.GetCount() - 1), monthChoice->GetSelection());
			monthChoice->Clear();
			monthChoice->Append(monthArray);
			monthChoice->SetSelection(monthSelect);
		}
		if (monthChoice->GetSelection() != controlDateTime->GetCurrentMonth() - 1)
		{
			return false;
		}
		if (dayArray.GetCount() > controlDateTime->GetCurrenDay())
		{
			int maxDay = dayArray.GetCount();
			for (int i = controlDateTime->GetCurrenDay(); i < maxDay; i++)
			{
				dayArray.pop_back();
			}
			int daySelect = min((int)(dayArray.GetCount() - 1), dayChoice->GetSelection());
			dayChoice->Clear();

			dayChoice->Append(dayArray);
			dayChoice->SetSelection(daySelect);
		}
		return true;
	}
	if (monthArray.GetCount() < 12)
	{
		SetDefaultRangeDateTime();
	}
	return false;
}
void GiveBook::SetDefaultRangeDateTime()
{
	dayArray.Clear();
	monthArray.Clear();

	for (int i = 0; i < 31; i++)
	{
		dayArray.Add(controlDateTime->GetDay()[i]);
	}
	for (int i = 0; i < 12; i++)
	{
		monthArray.Add(controlDateTime->GetMonth()[i]);
	}
	int monthSelect = min((int)(monthArray.GetCount() - 1), monthChoice->GetSelection());
	int daySelect = min((int)(dayArray.GetCount() - 1), dayChoice->GetSelection());
	dayChoice->Clear();
	monthChoice->Clear();
	dayChoice->Append(dayArray);
	dayChoice->SetSelection(daySelect);
	monthChoice->Append(monthArray);
	monthChoice->SetSelection(monthSelect);
}
void GiveBook::OnShowDialog(wxShowEvent& event)
{
	if (event.IsShown())
	{
		monthChoice->SetSelection(controlDateTime->GetCurrentMonth() - 1);
		yearChoice->SetSelection(20);
		ProccessYearSelection();
		ProccessMonthSelection();
		monthChoice->SetSelection(controlDateTime->GetCurrentMonth() - 1);
		dayChoice->SetSelection(controlDateTime->GetCurrenDay() - 1);
	}
	event.Skip();
}
void GiveBook::OnOkButton(wxCommandEvent& WXUNUSED(event))
{
	listBorrowBook[index]->SetStateBorrow(1);
	listBook[index]->SetState(0);
	listBorrowBook[index] = nullptr;
	listBook[index] = nullptr;
	string date = controlDateTime->GetDay()[dayChoice->GetSelection()] +
		"/" + controlDateTime->GetMonth()[monthChoice->GetSelection()] +
		"/" + controlDateTime->GetYear()[yearChoice->GetSelection()];
	DateTime* dateChosen = new DateTime();
	dateChosen->CastDate(date);
	listBorrowBook[index]->SetReturnDate(dateChosen);

	int row = grid->GetSelectedRows()[0];
	grid->DeleteRows(row, 1);
	grid->AppendRows(1);
	grid->SetRowSize(2, 30);
	grid->ClearSelection();
	dialog->Close();

}
void GiveBook::OnCancelButton(wxCommandEvent& WXUNUSED(event))
{
	grid->ClearSelection();
	dialog->Close();
}
void GiveBook::OnExitMenuButton(wxCommandEvent& WXUNUSED(event))
{
	this->Hide();
	this->GetParent()->Show();
}
BEGIN_EVENT_TABLE(GiveBook, wxFrame)
EVT_CHAR_HOOK(GiveBook::OnKeyDown)
END_EVENT_TABLE()
