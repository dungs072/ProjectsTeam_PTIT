#include "DisplayListCardReader.h"
DisplayListCardReader::DisplayListCardReader(const wxString& title)
	:wxFrame(NULL, -1, title, wxDefaultPosition, wxSize(1280, 680))
{
	
	// stateText
	sexText = new string[2]{ "NAM","NU" };
	wxColour lightYellow, organColor, lightBlue,red;
	lightYellow.Set(wxT("#E0EBB7"));
	organColor.Set(wxT("#FFAB03"));
	lightBlue.Set(wxT("#7FB1E3"));
	red.Set(wxT("#F74A4A"));
	//create panel
	wxPanel* mainPanel = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize);
	wxPanel* takeNotePanel = new wxPanel(mainPanel, -1, wxPoint(170,570), wxSize(400, 25));

	//create boxsizer
	wxBoxSizer* vGridBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vButtonBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* mainHBox = new wxBoxSizer(wxHORIZONTAL);
	//create static text
	gridLabel = new wxStaticText(mainPanel, -1,
		wxT("DANH SACH THE DOC"), wxPoint(-1, -1), wxSize(350, 40), wxALIGN_CENTRE_HORIZONTAL);
	wxStaticText* saveGuideText = new wxStaticText(takeNotePanel, -1,
		wxT("CO THE CHINH SUA DU LIEU, F2 LUU FILE"), wxPoint(50, 5), wxSize(300, 20), wxALIGN_CENTER);
	checkInput->SetTextSize(gridLabel, 20);
	//create Button
	wxButton* sortCodeButton = new wxButton(mainPanel, SORT_CODE,
		wxT("Sap xep danh sach theo ma the"), wxDefaultPosition, wxSize(200, 50));
	wxButton* sortNameButton = new wxButton(mainPanel, SORT_NAME,
		wxT("Sap xep danh sach theo ho ten "), wxDefaultPosition, wxSize(200, 50));
	wxButton* exitMenuButton = new wxButton(mainPanel, EXIT_MENU,
		wxT("EXIT MENU"), wxDefaultPosition, wxSize(100, 30));
	//create grid
	grid = new wxGrid(mainPanel, -1, wxDefaultPosition,
		wxSize(708, 500), wxEVT_GRID_CELL_CHANGED);
	grid->CreateGrid(DefaultRow, 5);
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
	for (int i = 0; i < grid->GetNumberRows(); i++)
	{
		grid->SetReadOnly(i, 0);
	}
	//Register event
	grid->Bind(wxEVT_GRID_CELL_CHANGED, &DisplayListCardReader::EditCurrentCell, this);
	Connect(SORT_CODE, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(DisplayListCardReader::OnSortCode));
	Connect(SORT_NAME, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(DisplayListCardReader::OnSortName));
	Connect(EXIT_MENU, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(DisplayListCardReader::OnExitMenu));
	Bind(wxEVT_SHOW, &DisplayListCardReader::OnShow, this);
	grid->Bind(wxEVT_GRID_RANGE_SELECTING, &DisplayListCardReader::OnSelectingGrid, this);
	grid->Bind(wxEVT_GRID_SELECT_CELL, &DisplayListCardReader::OnSelectedGrid, this);
	grid->Bind(wxEVT_GRID_LABEL_LEFT_CLICK, &DisplayListCardReader::OnSelectedLabelGrid, this);
	grid->Bind(wxEVT_CHAR_HOOK, &DisplayListCardReader::OnGridKeyDown, this);
	grid->Bind(wxEVT_GRID_SELECT_CELL, &DisplayListCardReader::OnSelectedCell, this);
	grid->Bind(wxEVT_TEXT, &DisplayListCardReader::OnGridTexting, this);
	//Set Color
	gridLabel->SetBackgroundColour(lightBlue);
	takeNotePanel->SetBackgroundColour(lightYellow);
	exitMenuButton->SetBackgroundColour(red);
	//do boxsizer
	vGridBox->Add(gridLabel, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 10);
	vGridBox->Add(grid, 0);
	vGridBox->Add(exitMenuButton, 0, wxTOP, 20);
	vButtonBox->Add(sortCodeButton, 0, wxTOP, 250);
	vButtonBox->Add(sortNameButton, 0);
	mainHBox->Add(vGridBox, 0, wxLEFT, 10);
	mainHBox->Add(vButtonBox, 0, wxLEFT, 40);
	mainPanel->SetSizer(mainHBox);
	Centre();
}
void DisplayListCardReader::OnShow(wxShowEvent& event)
{
	if (event.IsShown())
	{
		LoadData();
		ClearGridValue();
	}
}
void DisplayListCardReader::OnSortCode(wxCommandEvent& WXUNUSED(event))
{
	CardReader** arr = cardReaderTree->ToSortArray();
	DisplayCell(arr, length);
	delete[]arr;
}
void DisplayListCardReader::OnSortName(wxCommandEvent& WXUNUSED(event))
{
	CardReader** arr = cardReaderTree->ToSameTreeArray();
	QuickSort(arr, 0, length);
	DisplayCell(arr, length);

	delete[]arr;
}
void DisplayListCardReader::EditCurrentCell(wxGridEvent& event)
{
	LoadData();
	int row = grid->GetGridCursorRow();
	int col = grid->GetGridCursorCol();
	
	wxString wxOldText = event.GetString();
	if (wxOldText == wxT(""))
	{
		checkInput->ErrorMessageBox("Khong the chinh sua o nay ");
		grid->SetCellValue(row, col, wxOldText);
		return;
	}
	//find data
	string keyCodeStr = string(grid->GetCellValue(row, 0).mb_str());
	ulong keyCode = checkInput->CastWxStringToInt(keyCodeStr);
	CardReader* curEditCard = cardReaderTree->Search(keyCode)->data;

	wxString wxNewText = grid->GetCellValue(row, col);
	//main error
	if (checkInput->IsWhiteSpaceAllText(wxNewText))
	{
		checkInput->ErrorMessageBox("Loi Nhap Lieu ");
		grid->SetCellValue(row, col, wxOldText);
		return;
	}

	//col errors
	if (col == 1 || col == 2)
	{
		checkInput->ModifyTextInput(wxNewText);
		checkInput->UpperWxString(wxNewText);
		grid->SetCellValue(row, col, wxNewText);
		if (col == 1)
		{
			string str = string(wxNewText.mb_str());
			curEditCard->SetFirstName(str);
		}
		else if (col == 2)
		{
			string str = string(wxNewText.mb_str());
			curEditCard->SetLastName(str);
		}
	}
	if (col == 3)
	{
		int num = checkInput->CastWxStringToInt(wxNewText);
		grid->SetCellValue(row, col,sexText[num]);
		string str = sexText[num];
		curEditCard->SetSex(str);
	}
	if (col == 4)
	{
		checkInput->ModifyTextInput(wxNewText);
		int num =checkInput->CastWxStringToInt(wxNewText);
		grid->SetCellValue(row, col, checkInput->GetCardState(num));
		curEditCard->SetState(checkInput->GetCardState(num));
	}
	
	event.Skip();
}
void DisplayListCardReader::EditData(int row, int col)
{
	string keyCodeStr = string(grid->GetCellValue(row, 0).mb_str());
	if (keyCodeStr == "")
	{
		checkInput->ErrorMessageBox("Khong the chinh sua o nay");
		grid->SetCellValue(row, col, wxT(""));
		return;
	}
	ulong keyCode = checkInput->CastWxStringToInt(keyCodeStr);
	CardReader* curEditCard = cardReaderTree->Search(keyCode)->data;
	if (col == 3)
	{
		string str = string(grid->GetCellValue(row, col).mb_str());
		curEditCard->SetSex(str);
	}
	if (col == 4)
	{
		string str = string(grid->GetCellValue(row, col).mb_str());
		curEditCard->SetState(str);
	}
}
void DisplayListCardReader::OnKeyDown(wxKeyEvent& event)
{
	event.StopPropagation();
	if (event.GetKeyCode() == WXK_F2)
	{
		SaveFile();
	}
	event.Skip();
}
void DisplayListCardReader::OnGridKeyDown(wxKeyEvent& event)
{
	event.StopPropagation();
	if (event.GetKeyCode() == WXK_F2)
	{
		SaveFile();
	}
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
		if (checkInput->HasAlpha(keyCode)||checkInput->HasRightEntering(keyCode,true))
		{
			event.Skip();
		}
	}
	else if (col == 2)
	{
		if (checkInput->HasAlpha(keyCode)||checkInput->HasRightEntering(keyCode,true))
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
void DisplayListCardReader::OnExitMenu(wxCommandEvent& WXUNUSED(event))
{
	
	this->GetParent()->Show(true);
	this->Show(false);
}
void DisplayListCardReader::LoadData()
{
	length = cardReaderTree->GetNumberNodes();
}
void DisplayListCardReader::SaveFile()
{
	ISaveFile* isaveFile = dynamic_cast<ISaveFile*>(this->GetParent());
	isaveFile->SaveFile();
}
void DisplayListCardReader::DisplayCell(CardReader** arr, int length)
{
	if (length > grid->GetNumberRows())
	{
		grid->AppendRows(length-grid->GetNumberRows()+1);
	}
	ClearGridValue();
	for (int i = 0; i < length; i++)
	{
		string cardCodestr = EditCardCode(arr[i]->GetCardCode(), 10);
		grid->SetCellValue(i, 0, cardCodestr);
		grid->SetCellValue(i, 1, arr[i]->GetFirstName());
		grid->SetCellValue(i, 2, arr[i]->GetLastName());
		grid->SetCellValue(i, 3, arr[i]->GetSex());
		grid->SetCellValue(i, 4, arr[i]->GetState());
		for (int j = 0; j < 5; j++)
		{
			grid->SetCellAlignment(i, j, wxALIGN_CENTER, wxALIGN_CENTER);
		}
		
	}
	grid->Refresh();
}
wxString DisplayListCardReader::CastUlongToWxString(ulong number)
{
	string rawCodeReader = "";
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
	wxString myWxString(rawCodeReader.c_str(), wxConvUTF8);
	return myWxString;
}
void DisplayListCardReader::DisplayTabel(bool state)
{
	grid->Show(state);
	gridLabel->Show(state);
}
string DisplayListCardReader::EditCardCode(ulong number, int maxLengthCode)
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
void DisplayListCardReader::ClearGridValue()
{
	for (int i = 0; i < grid->GetNumberRows(); i++)
	{
		for (int j = 0; j < grid->GetNumberCols(); j++)
		{
			grid->SetCellValue(i, j, wxT(""));
		}
	}
}
void DisplayListCardReader::Swap(int i, int j, CardReader** A)
{
	CardReader* temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}
int DisplayListCardReader::Partition(CardReader** A, int l, int h)
{
	string pivot = A[l]->GetLastName()+A[l]->GetFirstName();

	int i = l, j = h;
	do
	{
		do { i++; if (i == j) { break; } } while (A[i]->GetLastName() + A[i]->GetFirstName() <= pivot);
		do { j--; } while (A[j]->GetLastName() + A[j]->GetFirstName() > pivot);
		if (i < j)Swap(i,j,A);
	} while (i < j);
	Swap(l,j,A);
	return j;
}
void DisplayListCardReader::QuickSort(CardReader** A, int l, int h)
{
	int j = 0;
	if (l < h)
	{
		j = Partition(A, l, h);
		QuickSort(A, l, j);
		QuickSort(A, j + 1, h);
	}
}
void DisplayListCardReader::SetData(BSTree<CardReader>* cardReaders,
	CheckInput* checkInput)
{
	cardReaderTree = cardReaders;
	this->length = cardReaders->GetNumberNodes();
	this->checkInput = checkInput;
}

void DisplayListCardReader::OnSelectingGrid(wxGridRangeSelectEvent& WXUNUSED(event))
{
	grid->ClearSelection();
}
void DisplayListCardReader::OnSelectedGrid(wxCommandEvent& WXUNUSED(event))
{
	grid->ClearSelection();
}
void DisplayListCardReader::OnSelectedLabelGrid(wxCommandEvent& WXUNUSED(event))
{
	grid->ClearSelection();
}
void DisplayListCardReader::OnSelectedCell(wxGridEvent& event)
{
	int row = event.GetRow();
	int col = event.GetCol();
	grid->ClearSelection();
	canEdit = true;
	event.Skip();
}
void DisplayListCardReader::OnGridTexting(wxCommandEvent& event)
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
int DisplayListCardReader::GetMaxLength(int col)
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
BEGIN_EVENT_TABLE(DisplayListCardReader, wxFrame)
EVT_CHAR_HOOK(DisplayListCardReader::OnKeyDown)
END_EVENT_TABLE()