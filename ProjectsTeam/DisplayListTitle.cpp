#include "DisplayListTitle.h"
DisplayListTitle::DisplayListTitle(const wxString& title) : wxFrame(NULL, -1, title, wxDefaultPosition, wxSize(1280, 680))
{
	//back end
	saveFile = new SaveTextFile<Title>("BookTitle.txt");
	maxItem = saveFile->GetLineCount();
	linearList = new LinearList<Title>(100);
	//catch error
	checkInput = new CheckInput();
	//create color;
	wxColour lightYellow, greenColor, organColor, lightBlue, eggYellow, lightRed, red, middleYellow;
	middleYellow.Set("#ECFF82");
	lightYellow.Set(wxT("#E0EBB7"));
	greenColor.Set(wxT("#03FF29"));
	organColor.Set(wxT("#FFAB03"));
	lightBlue.Set(wxT("#7FB1E3"));
	eggYellow.Set(wxT("#FDFF69"));
	lightRed.Set(wxT("#FA8E8E"));
	red.Set(wxT("#F74A4A"));
	//create panel
	wxPanel* mainPanel = new wxPanel(this, -1);
	wxPanel* keyNotePanel = new wxPanel(mainPanel, -1,
		wxDefaultPosition, wxSize(570, 30));
	//create wxStatic Text
	wxStaticText* gridTitle = new wxStaticText(mainPanel, -1,
		wxT("DANH SACH DAU SACH"), wxPoint(-1, -1), wxSize(400, 40), wxALIGN_CENTER);
	checkInput->SetTextSize(gridTitle, 20);

	//create BoxSizer
	wxBoxSizer* vGridBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vRightBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* mainHBox = new wxBoxSizer(wxHORIZONTAL);
	//create Grid
	grid = new wxGrid(mainPanel, -1, wxPoint(-1, -1), wxSize(745, 500));
	grid->CreateGrid(26, 6);
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
	vGridBox->Add(gridTitle, 0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 20);
	vGridBox->Add(grid, 0, wxLEFT | wxTOP, 20);
	vGridBox->Add(keyNotePanel, 0, wxTOP | wxALIGN_CENTER, 10);
	mainHBox->Add(vGridBox);
	mainHBox->Add(vRightBox);
	mainPanel->SetSizer(mainHBox);

	//Create areas;
	CreateKeyNoteArea(keyNotePanel);
	//Register event
	grid->Bind(wxEVT_GRID_CELL_CHANGED, &DisplayListTitle::EditCurrentCell, this);


	//Set Color
	gridTitle->SetBackgroundColour(lightBlue);
	keyNotePanel->SetBackgroundColour(lightYellow);
	LoadFile();
	Centre();
}

void DisplayListTitle::CreateTakeNoteArea(wxPanel* takeNotePanel)
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
void DisplayListTitle::CreateKeyNoteArea(wxPanel* keyNotePanel)
{
	wxStaticText* keyNoteText = new wxStaticText(keyNotePanel, -1,
		wxT("KEYHOT :   F2 - SAVE FILE, F4 - NHAP LIEU ( ENTER - LUU DAU SACH, DELETE - XOA DAU SACH )"),
		wxPoint(10, 10), wxSize(550, 20), wxALIGN_CENTER_HORIZONTAL);
}
void DisplayListTitle::OnKeyDown(wxKeyEvent& event)
{
	
	if (event.GetKeyCode() == WXK_F2)
	{
		SaveFile();
	}

	event.Skip();
}
void DisplayListTitle::EditCurrentCell(wxGridEvent& event)
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
		if (!CheckDuplicateISBN(wxNewText,row))
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
	grid->SetCellValue(row, col, wxNewText);
	ISBN = string(grid->GetCellValue(row, 0).mb_str());
	string bookName = string(grid->GetCellValue(row, 1).mb_str());
	uint numberPage = checkInput->CastWxStringToInt(grid->GetCellValue(row, 2));
	string author = string(grid->GetCellValue(row, 3).mb_str());
	uint nxb = checkInput->CastWxStringToInt(grid->GetCellValue(row, 4));
	string type = string(grid->GetCellValue(row, 5).mb_str());
	Title* title = new Title(ISBN, bookName, numberPage, author, nxb, type);
	if (col == 5 || col == 1)
	{
		EditTable(title, row);
	}
	event.Skip();
}
void DisplayListTitle::EditTable(Title* title, int row)
{
	int pos = -1;
	for (int i = 0; i < maxItem; i++)
	{
		if (i == row)
		{
			continue;
		}
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

			delete tempT;
			break;
		}
		delete tempT;
		tempT = nullptr;
	}
	if (pos == -1)
	{
		pos = maxItem;
	}
	grid->InsertRows(pos, 1);
	/*wxMessageBox(wxString::Format("%i", pos));
	wxMessageBox(wxString::Format("%i", row));*/
	if (row > pos)
	{
		row++;
	}
	for (int i = 0; i < 6; i++)
	{
		grid->SetCellValue(pos, i, grid->GetCellValue(row, i));
		grid->SetCellAlignment(pos, i, wxALIGN_CENTER, wxALIGN_CENTER);
	}
	grid->DeleteRows(row, 1);
}
void DisplayListTitle::SaveFile()
{
	Title** arr = linearList->ToArray();
	saveFile->WriteToFile(arr, maxItem);
	wxMessageBox(wxT("LIST IS SAVED SUCCESSFULLY"));
}
void DisplayListTitle::LoadFile()
{
	linearList->Clear();
	int length = maxItem;

	if (length > linearList->MaxLength())
	{
		wxMessageBox("Danh sach trong file qua lon, khong the load duoc");
		return;
	}
	Title** arr = new Title * [length];

	saveFile->ReadFile(arr);

	for (int i = 0; i < length; i++)
	{
		linearList->AddLast(arr[i]);
		//wxMessageBox(wxString::Format("%i",i));
	}
	LoadListToTable();
}
void DisplayListTitle::LoadListToTable()
{
	if (maxItem > grid->GetNumberRows())
	{
		grid->AppendRows(maxItem - grid->GetNumberRows());
	}
	for (int i = 0; i < maxItem; i++)
	{
		grid->SetCellValue(i, 0, linearList->GetData(i)->GetISBN());
		grid->SetCellValue(i, 1, linearList->GetData(i)->GetBookName());
		grid->SetCellValue(i, 2, wxString::Format("%i", linearList->GetData(i)->GetPageNumber()));
		grid->SetCellValue(i, 3, linearList->GetData(i)->GetAuthor());
		grid->SetCellValue(i, 4, wxString::Format("%i", linearList->GetData(i)->GetPublicYear()));
		grid->SetCellValue(i, 5, linearList->GetData(i)->GetType());
		for (int j = 0; j < 6; j++)
		{
			grid->SetCellAlignment(i, j, wxALIGN_CENTER, wxALIGN_CENTER);
		}
	}
}

bool DisplayListTitle::CheckISBN(wxString text)
{
	//ISBN CO 4 CHARS AND ALL IS CHAR NOT HAVE NUMBER;
	if (!checkInput->IsAlphabet(text)) { return false; }
	string textstr = string(text.mbc_str());
	return textstr.length() == 4;
}
bool DisplayListTitle::CheckBookName(wxString text)
{
	return checkInput->HasNumberAndAlphabet(text);
}
bool DisplayListTitle::CheckPageNumber(wxString text)
{
	//page number has 6 number;
	if (!checkInput->IsNumber(text)) { return false; }
	string textstr = string(text.mbc_str());
	return textstr.length() <= 6 && textstr.length() > 0;
}
bool DisplayListTitle::CheckAuthor(wxString text)
{
	return checkInput->IsWord(text);
}
bool DisplayListTitle::CheckYearPublic(wxString text)
{
	if (!checkInput->IsNumber(text)) { return false; }
	time_t current = time(0);
	tm* ltm = localtime(&current);
	int currentYear = ltm->tm_year + 1900;
	int yearInput = checkInput->CastWxStringToInt(text);
	//wxMessageBox(wxString::Format("current year: %i and year input: %i", currentYear, yearInput));
	return yearInput <= currentYear;
}
bool DisplayListTitle::CheckType(wxString text)
{
	return checkInput->IsWord(text);
}
bool DisplayListTitle::CheckDuplicateISBN(wxString text,int row)
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
int DisplayListTitle::CompareTitle(Title* t1, Title* t2)
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


BEGIN_EVENT_TABLE(DisplayListTitle, wxFrame)
EVT_CHAR_HOOK(DisplayListTitle::OnKeyDown)
END_EVENT_TABLE()
