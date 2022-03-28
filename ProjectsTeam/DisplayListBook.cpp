#include "DisplayListBook.h"
DisplayListBook::DisplayListBook(const wxString& title) :wxFrame(NULL, -1,
	title, wxDefaultPosition, wxSize(1280, 680))
{	
	//temp color
	wxColour lightYellow, greenColor, organColor, lightBlue, eggYellow, lightRed, red, middleYellow;
	middleYellow.Set("#ECFF82");
	lightYellow.Set(wxT("#E0EBB7"));
	greenColor.Set(wxT("#03FF29"));
	organColor.Set(wxT("#FFAB03"));
	lightBlue.Set(wxT("#7FB1E3"));
	eggYellow.Set(wxT("#FDFF69"));
	lightRed.Set(wxT("#FA8E8E"));
	red.Set(wxT("#F74A4A"));

	//backend
	saveFile = new SaveTextFile<Title>("BookTitle.txt");
	stateBook = new string[3]{ "CHO MUON DUOC","DA CO DOC GIA MUON","DA THANH LY" };
	//Create panel
	wxPanel* mainPanel = new wxPanel(this, -1);
	enterPanel = new wxPanel(mainPanel, -1, wxDefaultPosition, wxSize(300, 250));
	takeNotePanel = new wxPanel(mainPanel, -1, wxDefaultPosition, wxSize(530, 30));
	guidePanel = new wxPanel(mainPanel, -1, wxDefaultPosition, wxSize(530, 200));
	//for hiding enter text
	hideEnterText = new wxTextCtrl(enterPanel,-1,wxT(""),
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
	enterText->SetBackgroundColour(lightBlue);
	//Set color
	titleText->SetBackgroundColour(orange);

}
void DisplayListBook::CreateKeyNoteArea()
{
	wxStaticText* keyNoteText = new wxStaticText(takeNotePanel, -1, 
		wxT("KEYHOT:  F2 - SAVE FILE, NHAP LIEU ( ENTER - LUU MUC SACH, DELETE - XOA MUC SACH ) "),
		wxPoint(10, 10), wxSize(500,15), wxALIGN_CENTER_HORIZONTAL);
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
			grid->DeleteRows(30,maxItem-30);
		}
		maxItem = 0;
		LoadFile();
	}
	else
	{
		backButton->SetFocus();
		stateChoice->SetSelection(0);
		enterText->Clear();
	}
}
void DisplayListBook::OnKeyDown(wxKeyEvent& event)
{
	event.StopPropagation();
	if (event.GetKeyCode() == WXK_F2)
	{
		SaveFile();
	}
	else if (event.GetKeyCode() == WXK_DELETE)
	{
		ShowMessageClear();
	}
	event.Skip();
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
		if (!CheckStateBook(wxNewText))
		{
			checkInput->ErrorMessageBox("LOI TRANG THAI MA SACH");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}
		else
		{
			int index = checkInput->CastWxStringToInt(wxNewText);
			grid->SetCellValue(row, col, stateBook[index]);
			currentTitle->GetListBook()->FindSinglyNode(bookCode)->data.SetState(index);
		}
	}
	else if (col == 2)
	{
		if (!CheckPos(wxNewText))
		{
			checkInput->ErrorMessageBox("LOI VI TRI");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}
		else
		{
			grid->SetCellValue(row, col, wxNewText);
			string tempStr = string(wxNewText.mb_str());
			currentTitle->GetListBook()->FindSinglyNode(bookCode)->data.SetPos(tempStr);
		}
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
		wxGridUpdateLocker locker(grid);
		for (int i = 0; i < grid->GetNumberRows();)
		{
			if (grid->IsInSelection(i, 0))
			{
				//wxMessageBox(wxString::Format("%i",cardCode));

				string bookCode = string(grid->GetCellValue(i, 0).mbc_str());
				if (bookCode != "")
				{

					currentTitle->GetListBook()->Remove(bookCode);
					maxItem--;

				}
				grid->DeleteRows(i, 1);
				if (grid->GetNumberRows() < 30)
				{
					int numberRowsNeed = 30 - grid->GetNumberRows();

					grid->AppendRows(numberRowsNeed);
				}
			}
			else
				i++;
		}
	}
}
void DisplayListBook::SaveToList()
{
	if (maxItem + 1 > grid->GetNumberRows())
	{
		grid->AppendRows(maxItem-grid->GetNumberRows()+1);
	}
	string bookCode = currentTitle->GetISBN() + checkInput->CastIntToString(count);
	count++;
	int index = stateChoice->GetSelection();
	if (index < 0)
	{
		wxMessageBox("LOI TRANG THAI SACH");
		return;
	}
	string state = stateBook[index - 1];
	grid->SetCellValue(maxItem, 0, bookCode);
	grid->SetCellValue(maxItem, 1, state);
	grid->SetCellValue(maxItem, 2, enterText->GetValue());
	for (int i = 0; i < 3; i++)
	{
		grid->SetCellAlignment(maxItem, i, wxALIGN_CENTER, wxALIGN_CENTER);
	}
	grid->SetReadOnly(maxItem, 0);
	
	Book tempBook(bookCode, index - 1, string(enterText->GetValue().mb_str()));
	enterText->Clear();
	stateChoice->SetSelection(0);
	currentTitle->GetListBook()->Add(tempBook);
	maxItem++;
	
	
}
void DisplayListBook::SaveFile()
{
	if (linearList == nullptr)
	{
		wxMessageBox("Danh sach dau sach rong");
		return;
	}
	Title** arr = linearList->ToArray();
	saveFile->WriteToFile(arr, linearList->Length());
	wxMessageBox(wxT("LIST IS SAVED SUCCESSFULLY"));
}
void DisplayListBook::LoadFile()
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

	count =checkInput->CastStringToNumber(numberText) + 1;
}
bool DisplayListBook::CheckStateBook(wxString text)
{
	checkInput->ModifyTextInput(text);
	if (!checkInput->IsNumber(text)) { return false; }
	int number = checkInput->CastWxStringToInt(text);
	return checkInput->IsInRangeNumber(0, 2, number);
}
bool DisplayListBook::CheckPos(wxString text)
{
	return checkInput->HasNumberAlphabetAndComma(text);
}
BEGIN_EVENT_TABLE(DisplayListBook, wxFrame)
EVT_CHAR_HOOK(DisplayListBook::OnKeyDown)
EVT_SHOW(DisplayListBook::OnShow)
END_EVENT_TABLE()
