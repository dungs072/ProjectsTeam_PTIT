#include "LendBook.h"
LendBook::LendBook(const wxString& title) :
	wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(1280, 680))
{
	//back end
	controlDateTime = new ControlDateTime();
	saveFile = new SaveTextFile<CardReader>("ListReaders.txt");
	readFile = new SaveTextFile<Title>("BookTitle.txt");
	checkInput = new CheckInput();
	maxCard = saveFile->GetSizeArray();
	maxTitle = readFile->GetSizeArray();
	treeCardReader = new BSTree<CardReader>();
	linearList = new LinearList<Title>();
	//color
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

	//Create panel
	wxPanel* mainPanel = new wxPanel(this, -1);
	searchPanel = new wxPanel(mainPanel, -1, wxPoint(-1, -1), wxSize(400, 600));
	displayInforPanel = new wxPanel(searchPanel, -1, wxPoint(10, 90), wxSize(380, 500));

	//Create Button

	selectedTitleButton = new wxButton(mainPanel, -1, wxT("CHON DAU SACH"),
		wxPoint(1100, 610), wxSize(150, 22));
	backTitleButton = new wxButton(mainPanel, -1, wxT("<--DAU SACH"),
		wxPoint(500, 610), wxSize(100, 22));
	selectedBookButton = new wxButton(mainPanel, -1, wxT("CHON MUC SACH"),
		wxPoint(1100, 610), wxSize(150, 22));

	//Create boxSizer
	wxBoxSizer* mainHBox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* vRightBox = new wxBoxSizer(wxVERTICAL);

	//Create Static Text

	titleGridText = new wxStaticText(mainPanel, -1,
		wxT("DANH SACH DAU SACH"), wxPoint(725, 10), wxSize(300, 30), wxALIGN_CENTRE_HORIZONTAL);
	checkInput->SetTextSize(titleGridText, 15);
	//create dialog
	dialog = new wxDialog(this, -1, wxT("NGAY MUON"),
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

	wxStaticText* dayText = new wxStaticText(dialog, -1, wxT("DAY"),
		wxPoint(25, 75), wxSize(50, 20));
	wxStaticText* monthText = new wxStaticText(dialog, -1, wxT("MONTH"),
		wxPoint(120, 75), wxSize(50, 20));
	wxStaticText* yearText = new wxStaticText(dialog, -1, wxT("YEAR"),
		wxPoint(225, 75), wxSize(50, 20));

	okButton = new wxButton(dialog, -1, wxT("OK"), wxPoint(125, 200), wxSize(50, 20));
	cancelButton = new wxButton(dialog, -1, wxT("CANCEL"), wxPoint(200, 200), wxSize(50, 20));


	//title grid
	titleGrid = new wxGrid(mainPanel, -1, wxPoint(500, 50), wxSize(745, 550));
	titleGrid->CreateGrid(30, 6);
	titleGrid->SetColLabelValue(0, wxT("ISBN"));
	titleGrid->SetColLabelValue(1, wxT("TEN SACH"));
	titleGrid->SetColLabelValue(2, wxT("SO TR"));
	titleGrid->SetColLabelValue(3, wxT("TAC GIA"));
	titleGrid->SetColLabelValue(4, wxT("NXB"));
	titleGrid->SetColLabelValue(5, wxT("THE LOAI"));
	titleGrid->SetSelectionMode(wxGrid::wxGridSelectionModes::wxGridSelectRows);
	for (int i = 0; i < 6; i++)
	{
		if (i == 0 || i == 2 || i == 4) { titleGrid->SetColSize(i, 50); continue; }
		if (i == 1) { titleGrid->SetColSize(i, 200); continue; }
		titleGrid->SetColSize(i, 164);
	}
	titleGrid->SetRowLabelSize(50);
	titleGrid->DisableDragColSize();
	titleGrid->DisableDragRowSize();
	titleGrid->FitInside();

	//book grid
	bookGrid = new wxGrid(mainPanel, -1, wxPoint(600, 50), wxSize(550, 550));
	bookGrid->CreateGrid(30, 3);
	bookGrid->SetColLabelValue(0, wxT("MA SACH"));
	bookGrid->SetColLabelValue(1, wxT("TRANG THAI"));
	bookGrid->SetColLabelValue(2, wxT("VI TRI"));
	for (int i = 0; i < 3; i++)
	{
		bookGrid->SetColSize(i, 150);
	}
	//bookGrid->SetRowLabelSize(50);
	bookGrid->DisableDragColSize();
	bookGrid->DisableDragRowSize();
	bookGrid->SetSelectionMode(wxGrid::wxGridSelectionModes::wxGridSelectRows);
	bookGrid->Hide();
	//Set BoxSizer
	vRightBox->Add(searchPanel, 0, wxTOP, 30);
	mainHBox->Add(vRightBox, 0, wxLEFT, 20);
	mainPanel->SetSizer(mainHBox);

	//Register event
	Bind(wxEVT_SHOW, &LendBook::OnShow, this);
	Bind(wxEVT_TEXT_ENTER, &LendBook::OnEnter, this);
	titleGrid->Bind(wxEVT_GRID_RANGE_SELECTING, &LendBook::OnSelectingTitleGrid, this);
	titleGrid->Bind(wxEVT_GRID_SELECT_CELL, &LendBook::OnSelectedTitleGrid, this);
	titleGrid->Bind(wxEVT_GRID_LABEL_LEFT_CLICK, &LendBook::OnSelectedLabelTitleGrid, this);
	selectedTitleButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		&LendBook::OnSelectedTitleButtonClicked, this);

	bookGrid->Bind(wxEVT_GRID_RANGE_SELECTING, &LendBook::OnSelectingBookGrid, this);
	bookGrid->Bind(wxEVT_GRID_SELECT_CELL, &LendBook::OnSelectedBookGrid, this);
	bookGrid->Bind(wxEVT_GRID_LABEL_LEFT_CLICK, &LendBook::OnSelectedLabelBookGrid, this);
	selectedBookButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		&LendBook::OnSelectedBookButtonClicked, this);

	backTitleButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		&LendBook::OnBackTitleButtonClicked, this);

	okButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		&LendBook::OnOkButton, this);
	cancelButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		&LendBook::OnCancelButton, this);

	//register for selection event of wxChoice
	monthChoice->Bind(wxEVT_CHOICE, &LendBook::OnMonthSelection, this);
	yearChoice->Bind(wxEVT_CHOICE, &LendBook::OnYearSelection, this);

	//Set color
	searchPanel->SetBackgroundColour(lightYellow);
	displayInforPanel->SetBackgroundColour(lightBlue);
	titleGridText->SetBackgroundColour(lightOrange);
	titleGrid->SetSelectionBackground(organColor);
	selectedTitleButton->SetBackgroundColour(greenColor);
	selectedBookButton->SetBackgroundColour(greenColor);
	backTitleButton->SetBackgroundColour(lightRed);
	CreateSearchPanel();
	Centre();
}
void LendBook::CreateSearchPanel()
{
	wxColor eggYellow;
	eggYellow.Set(wxT("#FDFF69"));
	wxStaticText* titleLendBook = new wxStaticText(searchPanel, -1,
		wxT("HAY NHAP VAO MA THE DOC GIA DE MUON SACH"),
		wxPoint(20, 10), wxSize(400, 30));
	checkInput->SetTextSize(titleLendBook, 12);
	enterSearchText = new wxTextCtrl(searchPanel, -1, wxT(""),
		wxPoint(50, 50), wxSize(300, 25), wxTE_PROCESS_ENTER | wxTE_CENTRE);
	enterSearchText->SetMaxLength(10);
	hideFocusText = new wxTextCtrl(searchPanel, -1, wxT(""),
		wxPoint(-1, -1), wxSize(10, 10));
	hideFocusText->Hide();

	//Create display infor for card reader
	wxStaticText* titleInforCard = new wxStaticText(displayInforPanel, -1,
		wxT("THONG TIN DOC GIA"), wxPoint(115, 10), wxSize(200, 30));
	checkInput->SetTextSize(titleInforCard, 11);

	wxStaticText* title0 = new wxStaticText(displayInforPanel, -1, wxT("Ho va ten: "),
		wxPoint(20, 50), wxSize(75, 20));
	checkInput->SetTextSize(title0, 10);
	wxStaticText* title1 = new wxStaticText(displayInforPanel, -1, wxT("Trang thai the: "),
		wxPoint(20, 100), wxSize(75, 20));
	checkInput->SetTextSize(title1, 10);
	wxStaticText* title2 = new wxStaticText(displayInforPanel, -1, wxT("Phai: "),
		wxPoint(20, 150), wxSize(50, 20));
	checkInput->SetTextSize(title2, 10);
	displayPersonText = new wxStaticText * [3];
	for (int i = 0; i < 3; i++)
	{
		displayPersonText[i] = new wxStaticText(displayInforPanel, -1, wxT("")
			, wxPoint(125, 50 + i * 50), wxSize(200, 20), wxALIGN_CENTER);
		checkInput->SetTextSize(displayPersonText[i], 10);
		displayPersonText[i]->SetBackgroundColour(eggYellow);
	}

	//create for display infor about book borrowed
	wxStaticText* bookBorrowedTitle = new wxStaticText(displayInforPanel, -1,
		wxT("CAC SACH DANG MUON"), wxPoint(115, 200), wxSize(300, 30));
	wxStaticText* bookTitle = new wxStaticText(displayInforPanel, -1,
		wxT("TEN SACH"), wxPoint(85, 230), wxSize(75, 30));
	wxStaticText* dateTitle = new wxStaticText(displayInforPanel, -1,
		wxT("NGAY MUON"), wxPoint(275, 230), wxSize(75, 30));
	displayNameBookText = new wxStaticText * [maxBookLend];
	for (int i = 0; i < maxBookLend; i++)
	{
		displayNameBookText[i] = new wxStaticText(displayInforPanel, -1, wxT(""),
			wxPoint(10, 275 + i * 50), wxSize(200, 20), wxALIGN_CENTER);
		displayNameBookText[i]->SetBackgroundColour(eggYellow);
	}
	displayDateBookText = new wxStaticText * [maxBookLend];
	for (int i = 0; i < maxBookLend; i++)
	{
		displayDateBookText[i] = new wxStaticText(displayInforPanel, -1, wxT(""),
			wxPoint(250, 275 + i * 50), wxSize(115, 20), wxALIGN_CENTER);
		displayDateBookText[i]->SetBackgroundColour(eggYellow);
	}
}
void LendBook::LoadFile()
{
	CardReader** arrCard = new CardReader * [maxCard];
	Title** arrTitle = new Title * [maxTitle];
	saveFile->ReadFile(arrCard);
	readFile->ReadFile(arrTitle);
	for (int i = 0; i < maxCard; i++)
	{
		treeCardReader->Add(arrCard[i]);
	}
	for (int i = 0; i < maxTitle; i++)
	{
		linearList->AddLast(arrTitle[i]);
	}
	delete[]arrCard;
	delete[]arrTitle;
}
void LendBook::OnShow(wxShowEvent& event)
{
	if (event.IsShown())
	{
		LoadFile();
		ClearOldDataInInforPanel();
		ClearOldDataInTitleGrid();
		LoadListTitleToTable();

		selectedTitleButton->Hide();
		selectedBookButton->Hide();
		backTitleButton->Hide();

		monthChoice->SetSelection(controlDateTime->GetCurrentMonth() - 1);
		yearChoice->SetSelection(20);
		ProccessYearSelection();
		ProccessMonthSelection();
		monthChoice->SetSelection(controlDateTime->GetCurrentMonth() - 1);
		dayChoice->SetSelection(controlDateTime->GetCurrenDay() - 1);

	}
	else
	{
		foundCardReader = nullptr;
		selectedTitle = nullptr;
		selectedBook = nullptr;
		borrowingBookCount = 0;
	}

	event.Skip();
}
void LendBook::OnEnter(wxCommandEvent& WXUNUSED(event))
{
	ulong hashCode = checkInput->ToNumber<ulong>(enterSearchText->GetValue());
	BSTNode<CardReader>* searchNode = treeCardReader->Search(hashCode);
	borrowingBookCount = 0;
	if (searchNode == nullptr)
	{
		checkInput->ErrorMessageBox("Khong the tim thay the doc can tim");
		SetDefaultGrid();
		ClearOldDataInInforPanel();
		foundCardReader = nullptr;
		selectedTitle = nullptr;
		selectedBook = nullptr;
		selectedTitleButton->Hide();
		titleGrid->ClearSelection();
		return;
	}
	foundCardReader = searchNode->data;
	ClearOldDataInInforPanel();
	SetDefaultGrid();
	DisplayCardOnPanel();
	hideFocusText->SetFocus();
	//enterSearchText->Clear();
}
void LendBook::SetDefaultGrid()
{
	bookGrid->Hide();
	titleGrid->Show();
	bookGrid->Refresh();
	//titleGrid->Refresh();
	backTitleButton->Hide();
	selectedBookButton->Hide();
	selectedTitleButton->Show();
	titleGridText->SetLabel("DANH SACH DAU SACH");
	this->Refresh();
}
void LendBook::OnSelectingTitleGrid(wxGridRangeSelectEvent& event)
{
	titleGrid->ClearSelection();
	event.Skip();
}
void LendBook::OnSelectedTitleGrid(wxCommandEvent& WXUNUSED(event))
{
	if (foundCardReader == nullptr)
	{
		titleGrid->ClearSelection();
		return;
	}

	int row = -1;
	if (titleGrid->GetSelectedRows().Count() > 0)
	{
		row = titleGrid->GetSelectedRows()[0];
	}
	if (row == -1)
	{
		selectedTitle = nullptr;
		selectedTitleButton->Hide();
		return;
	}
	string ISBN = string(titleGrid->GetCellValue(row, 0).mb_str());
	if (ISBN == "")
	{
		wxMessageBox(wxT("KHONG CO DAU SACH NAO DUOC CHON"));
		titleGrid->DeselectRow(row);
		selectedTitle = nullptr;
		selectedTitleButton->Hide();
		return;
	}

	selectedTitle = linearList->GetData(ISBN);
	selectedTitleButton->Show();


}
void LendBook::OnSelectedLabelTitleGrid(wxCommandEvent& event)
{
	titleGrid->ClearSelection();
	event.Skip();
}
void LendBook::OnSelectedTitleButtonClicked(wxCommandEvent& event)
{
	if (borrowingBookCount >= maxBookLend)
	{
		checkInput->ErrorMessageBox("MOT DOC GIA CHI DUOC MUON TOI DA 3 CUON SACH");
		return;
	}
	titleGrid->Hide();
	selectedTitleButton->Hide();
	this->Refresh();
	backTitleButton->Show();
	//bookGrid->Refresh();
	ClearOldDataInBookGrid();
	titleGridText->SetLabel("DANH SACH MUC SACH");
	bookGrid->Show();

	LoadListBookToTable();
}

void LendBook::OnSelectingBookGrid(wxGridRangeSelectEvent& event)
{
	bookGrid->ClearSelection();
	event.Skip();
}
void LendBook::OnSelectedBookGrid(wxCommandEvent& WXUNUSED(event))
{
	if (foundCardReader == nullptr)
	{
		bookGrid->ClearSelection();
		return;
	}
	int row = -1;
	if (bookGrid->GetSelectedRows().Count() > 0)
	{
		row = bookGrid->GetSelectedRows()[0];
	}
	if (row == -1)
	{
		selectedBook = nullptr;
		selectedBookButton->Hide();
		return;
	}
	string bookCode = string(bookGrid->GetCellValue(row, 0).mb_str());
	if (bookCode == "")
	{
		wxMessageBox(wxT("KHONG CO SACH NAO DUOC CHON"));
		selectedBookButton->Hide();
		bookGrid->DeselectRow(row);
		selectedBook = nullptr;
		return;
	}

	selectedBook = &selectedTitle->GetListBook()->FindSinglyNode(bookCode)->data;
	if (selectedBook->GetState() != 0)
	{
		checkInput->ErrorMessageBox("Sach khong co san de muon");
		selectedBookButton->Hide();
		bookGrid->DeselectRow(row);
		return;
	}
	bookRowChange = row;
	selectedBookButton->Show();
}
void LendBook::OnSelectedBookButtonClicked(wxCommandEvent& WXUNUSED(event))
{
	if (borrowingBookCount >= maxBookLend)
	{
		checkInput->ErrorMessageBox("MOT DOC GIA CHI DUOC MUON TOI DA 3 CUON SACH");
		return;
	}
	dialog->Centre();
	dialog->ShowModal();
}
void LendBook::OnSelectedLabelBookGrid(wxCommandEvent& event)
{
	bookGrid->ClearSelection();
	event.Skip();
}
void LendBook::OnBackTitleButtonClicked(wxCommandEvent& WXUNUSED(event))
{
	SetDefaultGrid();
}
void LendBook::OnOkButton(wxCommandEvent& WXUNUSED(event))
{
	selectedBook->SetState(1);
	bookGrid->SetCellValue(bookRowChange, 1, checkInput->GetBookState(1));
	bookGrid->Refresh();
	bookGrid->ClearSelection();
	string bookCode = string(bookGrid->GetCellValue(bookRowChange, 0).mb_str());
	string date = controlDateTime->GetDay()[dayChoice->GetSelection()] +
		"/" + controlDateTime->GetMonth()[monthChoice->GetSelection()] +
		"/" + controlDateTime->GetYear()[yearChoice->GetSelection()];
	DateTime* dateChosen = new DateTime();
	dateChosen->CastDate(date);
	BorrowBook borrowBook(bookCode, dateChosen, nullptr, 0);
	foundCardReader->GetListBorrowBook()->AddLast(borrowBook);
	borrowingBookCount++;
	DisplayBookJustBorrow();
	selectedBook = nullptr;
	selectedBookButton->Hide();
	dialog->Close();

}
void LendBook::DisplayBookJustBorrow()
{
	DoublyNode<BorrowBook>* tempCard = foundCardReader->GetListBorrowBook()->Last();
	if (tempCard->data.GetStateBorrow() != 0)
	{
		wxMessageBox("This is error->have to fix it");
		return;
	}
	string ISBN = "";
	for (int j = 0; j < 4; j++)
	{
		ISBN += tempCard->data.GetBookCode()[j];
	}
	Title* tempTitle = linearList->GetData(ISBN);
	displayNameBookText[borrowingBookCount-1]->SetLabel(tempTitle->GetBookName());
	displayDateBookText[borrowingBookCount-1]->SetLabel(tempCard->data.GetBorrowDate()->ToString());
	tempCard = tempCard->next;
}
void LendBook::OnCancelButton(wxCommandEvent& WXUNUSED(event))
{
	selectedBook = nullptr;
	dialog->Close();
}

void LendBook::OnYearSelection(wxCommandEvent& WXUNUSED(event))
{
	ProccessYearSelection();
}
void LendBook::OnMonthSelection(wxCommandEvent& WXUNUSED(event))
{
	ProccessMonthSelection();
}
void LendBook::ProccessYearSelection()
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
				dayChoice->Clear();
				dayChoice->Append(dayArray);
				return;
			}
			if (dayArray.GetCount() == 28)
			{
				dayArray.Add(controlDateTime->GetDay()[dayArray.GetCount()]);
				dayChoice->Clear();
				dayChoice->Append(dayArray);
				return;
			}
			for (int i = dayArray.GetCount(); i > 29; i--)
			{
				dayArray.pop_back();
			}
			dayChoice->Clear();
			dayChoice->Append(dayArray);
		}
	}
	else
	{
		for (int i = dayArray.GetCount(); i > 28; i--)
		{
			dayArray.pop_back();
		}
		dayChoice->Clear();
		dayChoice->Append(dayArray);
	}
}
void LendBook::ProccessMonthSelection()
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
		dayChoice->Clear();
		dayChoice->Append(dayArray);
	}
	else if (selection == 1)
	{
		ProccessYearSelection();
	}
	else
	{
		if (dayArray.GetCount() < 31)
		{
			for (int i = dayArray.GetCount(); i < 30; i++)
			{
				dayArray.Add(controlDateTime->GetDay()[i]);
			}
			dayChoice->Clear();
			dayChoice->Append(dayArray);
			return;
		}
		if (dayArray.GetCount() == 31)
		{
			dayArray.pop_back();
			dayChoice->Clear();
			dayChoice->Append(dayArray);
			return;
		}
		for (int i = dayArray.GetCount(); i < 30; i++)
		{
			dayArray.Add(controlDateTime->GetDay()[i]);
		}
		dayChoice->Clear();
		dayChoice->Append(dayArray);
	}
}
bool LendBook::ProccessCurrentDate()
{
	if (yearChoice->GetSelection() == 20)
	{
		if (monthChoice->GetSelection() != controlDateTime->GetCurrentMonth() - 1)
		{
			return false;
		}
		if (monthArray.GetCount() != controlDateTime->GetCurrentMonth())
		{
			for (int i = controlDateTime->GetCurrentMonth(); i < 12; i++)
			{
				monthArray.pop_back();
			}
			monthChoice->Clear();
			monthChoice->Append(monthArray);
		}
		if (dayArray.GetCount() != controlDateTime->GetCurrenDay())
		{
			int maxDay = dayArray.GetCount();
			for (int i = controlDateTime->GetCurrenDay(); i < maxDay; i++)
			{
				dayArray.pop_back();
			}
			dayChoice->Clear();

			dayChoice->Append(dayArray);

		}
		return true;
	}
	if (monthArray.GetCount() < 12)
	{
		SetDefaultValueDateTime();
	}
	return false;
}
void LendBook::SetDefaultValueDateTime()
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
	dayChoice->Clear();
	monthChoice->Clear();
	dayChoice->Append(dayArray);
	monthChoice->Append(monthArray);
}

void LendBook::DisplayCardOnPanel()
{

	displayPersonText[0]->SetLabel(foundCardReader->GetFirstName() + " " +
		foundCardReader->GetLastName());
	displayPersonText[1]->SetLabel(foundCardReader->GetState());
	displayPersonText[2]->SetLabel(foundCardReader->GetSex());

	if (foundCardReader->GetListBorrowBook()->Length() > 0)
	{
		DisplayBookBorrow();
	}
}
void LendBook::DisplayBookBorrow()
{
	int i = 0;
	DoublyNode<BorrowBook>* tempCard = foundCardReader->GetListBorrowBook()->First();
	while (tempCard != nullptr)
	{
		if (tempCard->data.GetStateBorrow() != 0)
		{
			continue;
		}
		string ISBN = "";
		for (int j = 0; j < 4; j++)
		{
			ISBN += tempCard->data.GetBookCode()[j];
		}
		Title* tempTitle = linearList->GetData(ISBN);
		displayNameBookText[i]->SetLabel(tempTitle->GetBookName());
		displayDateBookText[i]->SetLabel(tempCard->data.GetBorrowDate()->ToString());
		i++;
		borrowingBookCount++;
		tempCard = tempCard->next;
	}
}
void LendBook::LoadListTitleToTable()
{
	if (maxTitle > titleGrid->GetNumberRows())
	{
		titleGrid->AppendRows(maxTitle - titleGrid->GetNumberRows() + 1);
	}
	else if (maxTitle < titleGrid->GetNumberRows())
	{
		for (int i = maxTitle; i < titleGrid->GetNumberRows(); i++)
		{
			for (int j = 0; j < 6; j++)
			{
				titleGrid->SetReadOnly(i, j);
			}
		}
	}
	for (int i = 0; i < maxTitle; i++)
	{

		titleGrid->SetCellValue(i, 0, linearList->GetData(i)->GetISBN());
		titleGrid->SetCellValue(i, 1, linearList->GetData(i)->GetBookName());
		string pageNumber = checkInput->CastIntToString(linearList->GetData(i)->GetPageNumber());
		titleGrid->SetCellValue(i, 2, pageNumber);
		titleGrid->SetCellValue(i, 3, linearList->GetData(i)->GetAuthor());
		string nxb = checkInput->CastIntToString(linearList->GetData(i)->GetPublicYear());
		titleGrid->SetCellValue(i, 4, nxb);
		titleGrid->SetCellValue(i, 5, linearList->GetData(i)->GetType());
		for (int j = 0; j < 6; j++)
		{
			titleGrid->SetCellAlignment(i, j, wxALIGN_CENTER, wxALIGN_CENTER);
			titleGrid->SetReadOnly(i, j);
		}
	}
}
void LendBook::LoadListBookToTable()
{
	if (selectedTitle == nullptr) { return; }
	maxBook = selectedTitle->GetListBook()->Length();
	if (maxBook > bookGrid->GetNumberRows())
	{
		bookGrid->AppendRows(maxBook - bookGrid->GetNumberRows() + 1);
	}
	SinglyNode<Book>* tempBook = selectedTitle->GetListBook()->First();
	int i = 0;
	while (tempBook != nullptr)
	{
		bookGrid->SetCellValue(i, 0, tempBook->data.GetBookCode());
		bookGrid->SetCellValue(i, 1, checkInput->GetBookState(tempBook->data.GetState()));
		bookGrid->SetCellValue(i, 2, tempBook->data.GetPos());
		for (int j = 0; j < 3; j++)
		{
			bookGrid->SetCellAlignment(i, j, wxALIGN_CENTER, wxALIGN_CENTER);
		}
		i++;
		tempBook = tempBook->next;
	}
	for (i = 0; i < bookGrid->GetNumberRows(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			bookGrid->SetReadOnly(i, j);
		}
	}
}
void LendBook::ClearOldDataInInforPanel()
{
	for (int i = 0; i < 3; i++)
	{
		displayPersonText[i]->SetLabel("");
		displayNameBookText[i]->SetLabel("");
		displayDateBookText[i]->SetLabel("");
	}
}
void LendBook::ClearOldDataInTitleGrid()
{
	if (titleGrid->GetNumberRows() > 30)
	{
		titleGrid->DeleteRows(30, titleGrid->GetNumberRows() - 30 + 1);
	}
	for (int i = 0; i < titleGrid->GetNumberRows(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			titleGrid->SetCellValue(i, j, wxT(""));
		}
	}
}
void LendBook::ClearOldDataInBookGrid()
{
	if (bookGrid->GetNumberRows() > 30)
	{
		bookGrid->DeleteRows(30, bookGrid->GetNumberRows() - 30 + 1);
	}
	for (int i = 0; i < bookGrid->GetNumberRows(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			bookGrid->SetCellValue(i, j, wxT(""));
		}
	}
}
void LendBook::OnKeyDown(wxKeyEvent& event)
{
	if (enterSearchText->HasFocus())
	{
		int keyCode = event.GetKeyCode();
		if ((keyCode >= '0' && keyCode <= '9') || keyCode == WXK_BACK || keyCode == WXK_RETURN)
		{
			event.Skip();
		}
	}
	else
	{
		event.Skip();
	}

}
BEGIN_EVENT_TABLE(LendBook, wxFrame)
EVT_CHAR_HOOK(LendBook::OnKeyDown)
END_EVENT_TABLE()
