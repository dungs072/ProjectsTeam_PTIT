#include "DisplayListCardReader.h"
DisplayListCardReader::DisplayListCardReader(const wxString& title)
	:wxFrame(NULL, -1, title, wxDefaultPosition, wxSize(1280, 680))
{
	
	// stateText
	stateText = new string[2]{ "KHOA","HOAT DONG" };
	wxColour lightYellow, greenColor, organColor, lightBlue, eggYellow, lightRed,red;
	lightYellow.Set(wxT("#E0EBB7"));
	greenColor.Set(wxT("#03FF29"));
	organColor.Set(wxT("#FFAB03"));
	lightBlue.Set(wxT("#7FB1E3"));
	eggYellow.Set(wxT("#FDFF69"));
	lightRed.Set(wxT("#FA8E8E"));
	red.Set(wxT("#F74A4A"));
	//Create SaveFile
	saveFile = new SaveTextFile<CardReader>("ListReaders.txt");
	length = saveFile->GetSizeArray();
	//create panel
	wxPanel* mainPanel = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize);
	wxPanel* takeNotePanel = new wxPanel(mainPanel, -1, wxDefaultPosition, wxSize(300, 100));

	//create boxsizer
	wxBoxSizer* vGridBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vButtonBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* mainHBox = new wxBoxSizer(wxHORIZONTAL);
	//create static text
	gridLabel = new wxStaticText(mainPanel, -1,
		wxT("DANH SACH THE DOC"), wxPoint(-1, -1), wxSize(350, 40), wxALIGN_CENTRE_HORIZONTAL);
	wxStaticText* guideText = new wxStaticText(takeNotePanel, -1,
		wxT("HUONG DAN"), wxPoint(100, 5), wxSize(100, 20), wxALIGN_CENTER_HORIZONTAL);
	wxStaticText* saveGuideText = new wxStaticText(takeNotePanel, -1,
		wxT("F2 - LUU FILE"), wxPoint(20, 30), wxSize(100, 20));
	SetTextSize(gridLabel, 20);
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
	//Set Color
	gridLabel->SetBackgroundColour(lightBlue);
	takeNotePanel->SetBackgroundColour(lightYellow);
	guideText->SetBackgroundColour(organColor);
	exitMenuButton->SetBackgroundColour(red);
	//do boxsizer
	vGridBox->Add(gridLabel, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 10);
	vGridBox->Add(grid, 0);
	vGridBox->Add(exitMenuButton, 0, wxTOP, 20);
	vButtonBox->Add(sortCodeButton, 0, wxTOP, 250);
	vButtonBox->Add(sortNameButton, 0);
	vButtonBox->Add(takeNotePanel, 0, wxTOP, 100);
	mainHBox->Add(vGridBox, 0, wxLEFT, 10);
	mainHBox->Add(vButtonBox, 0, wxLEFT, 40);
	mainPanel->SetSizer(mainHBox);
	Centre();
}
void DisplayListCardReader::OnSortCode(wxCommandEvent& WXUNUSED(event))
{
	
	if (arr != nullptr)
	{
		for (int i = 0; i < length; i++)
		{
			delete arr[i];
		}
		delete []arr;
		arr = nullptr;
	}
	length = saveFile->GetSizeArray();
	arr = new CardReader* [length];

	saveFile->ReadFile(arr);
	DisplayCell(arr, length);
}
void DisplayListCardReader::OnSortName(wxCommandEvent& WXUNUSED(event))
{
	if (arr != nullptr)
	{
		for (int i = 0; i < length; i++)
		{
			delete arr[i];
		}
		delete []arr;
		arr = nullptr;
	}
	length = saveFile->GetSizeArray();
	arr = new CardReader* [length];
	saveFile->ReadFile(arr);
	QuickSort(arr, 0, length);
	DisplayCell(arr, length);
	grid->Refresh();
}
void DisplayListCardReader::EditCurrentCell(wxGridEvent& event)
{
	int row = grid->GetGridCursorRow();
	int col = grid->GetGridCursorCol();
	wxString wxOldText = event.GetString();
	if (wxOldText == wxT(""))
	{
		ErrorMessageBox("Khong the chinh chua o nay ");
		grid->SetCellValue(row, col, wxOldText);
		return;
	}
	wxString wxNewText = grid->GetCellValue(row, col);
	//main error
	if (IsWhiteSpaceAllText(wxNewText))
	{
		ErrorMessageBox("Loi Nhap Lieu ");
		grid->SetCellValue(row, col, wxOldText);
		return;
	}

	//col errors
	if (col == 1 || col == 2)
	{
		ModifyTextInput(wxNewText);
		if (!IsWord(wxNewText))
		{
			ErrorMessageBox("Loi Nhap Lieu ");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}

		UpperWxString(wxNewText);
		grid->SetCellValue(row, col, wxNewText);
		if (col == 1)
		{
			string str = string(wxNewText.mb_str());
			arr[row]->SetFirstName(str);
		}
		else if (col == 2)
		{
			string str = string(wxNewText.mb_str());
			arr[row]->SetLastName(str);
		}
	}
	if (col == 3)
	{
		if (!IsRightSex(wxNewText))
		{
			ErrorMessageBox("Loi Nhap Lieu ");
			grid->SetCellValue(row, col, wxOldText);
			
			return;
		}
		UpperWxString(wxNewText);
		grid->SetCellValue(row, col, wxNewText);
		string str = string(wxNewText.mb_str());
		arr[row]->SetSex(str);
	}
	if (col == 4)
	{
		ModifyTextInput(wxNewText);
		int num = CastWxStringToInt(wxNewText);
		if (!IsRightCodeState(1, num))
		{
			ErrorMessageBox("Loi Nhap Lieu ");
			grid->SetCellValue(row, col, wxOldText);
			
			return;
		}
		grid->SetCellValue(row, col, stateText[num]);
		string str = stateText[num];
		arr[row]->SetState(str);
	}
	
	event.Skip();
}
void DisplayListCardReader::OnKeyDown(wxKeyEvent& event)
{
	if (event.GetKeyCode() == WXK_F2)
	{
		SaveFile();
	}
	event.Skip();
}
void DisplayListCardReader::OnExitMenu(wxCommandEvent& WXUNUSED(event))
{
	this->GetParent()->Show(true);
	this->Show(false);
}
void DisplayListCardReader::SaveFile()
{
	if (arr == nullptr) { return; }

	BSTree<CardReader>* tempTree = new BSTree<CardReader>();
	for (int i = 0; i < length; i++)
	{
		tempTree->Add(arr[i]);

	}
	//to sort with code reader//dont missunderstand:))
	arr = tempTree->ToArray();
	saveFile->WriteToFile(arr, length);
	tempTree->Clear();
	delete tempTree;
	tempTree = nullptr;
	wxMessageBox(wxString::Format("LIST IS SAVED SUCCESSFULLY"));
	//if (readerCard == nullptr) { return; }
	//readerCard->LoadFile();
}
bool DisplayListCardReader::IsWhiteSpaceAllText(wxString text)
{
	std::string strText = std::string(text.mb_str());
	for (char str : strText)
	{
		if (str != ' ')
		{
			return false;
		}
	}
	return true;
}
bool DisplayListCardReader::IsWord(wxString text)
{
	std::string strText = std::string(text.mb_str());
	for (int i = 0; i < strText.length(); i++)
	{
		if (!(strText[i] >= 'a' && strText[i] <= 'z'))
		{
			if (!(strText[i] >= 'A' && strText[i] <= 'Z'))
			{
				if (strText[i] != ' ')
					return false;
			}
		}
	}
	return true;
}
bool DisplayListCardReader::IsRightSex(wxString text)
{
	std::string strText = std::string(text.mb_str());
	strText = UpperText(strText);
	if (strText == "") { return false; }
	ModifyString(strText);
	wxString myWxString(strText.c_str(), wxConvUTF8);
	if (strText == "NAM" || strText == "NU")
	{
		text = myWxString;
		return true;
	}
	return false;
}
bool DisplayListCardReader::IsRightCodeState(int maxNumber, int currentNumber)
{
	return currentNumber >= 0 && currentNumber <= maxNumber;
}
void DisplayListCardReader::ModifyTextInput(wxString& text)
{
	std::string strText = std::string(text.mb_str());
	ModifyString(strText);
	wxString myWxString(strText.c_str(), wxConvUTF8);
	text = myWxString;
}
void DisplayListCardReader::ModifyString(string& strText)
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
void DisplayListCardReader::UpperWxString(wxString& text)
{
	std::string strText = std::string(text.mb_str());
	strText = UpperText(strText);
	wxString myWxString(strText.c_str(), wxConvUTF8);
	text = myWxString;
}
string DisplayListCardReader::UpperText(string text)
{
	for (int i = 0; i < text.length(); i++)
	{
		if ((text[i] >= 'Z' && text[i] <= 'A'))
		{
			return "";
		}
		if (text[i] <= 'z' && text[i] >= 'a')
		{
			text[i] -= 32;
		}
	}
	return text;
}
int DisplayListCardReader::CastWxStringToInt(wxString text)
{
	int i, j;
	int number = 0;
	string strText = string(text.mb_str());
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
void DisplayListCardReader::ErrorMessageBox(string message)
{
	wxString myWxString(message.c_str(), wxConvUTF8);
	wxMessageBox(myWxString);
}
void DisplayListCardReader::DisplayCell(CardReader** arr, int length)
{
	
	if (length > grid->GetNumberRows())
	{
		grid->AppendRows(length - grid->GetNumberRows() + 1);
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
void DisplayListCardReader::SetTextSize(wxStaticText* text, int size)
{
	wxFont tempFont = text->GetFont();
	tempFont.SetPointSize(size);
	text->SetFont(tempFont);
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
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < grid->GetNumberCols(); j++)
		{
			grid->SetCellValue(i, j, wxT(""));
		}
	}
}
//QuickSort
void DisplayListCardReader:: Swap(CardReader** card1, CardReader** card2)
{
	CardReader temp = **card1;
	**card1 = **card2;
	**card2 = temp;	
}
int DisplayListCardReader::Partition(CardReader** A, int l, int h)
{
	string pivot = A[l]->GetLastName()+A[l]->GetFirstName();

	int i = l, j = h;
	do
	{
		do { i++; if (i == j) { break; } } while (A[i]->GetLastName() + A[i]->GetFirstName() <= pivot);
		do { j--; } while (A[j]->GetLastName() + A[j]->GetFirstName() > pivot);
		if (i < j)Swap(&A[i], &A[j]);
	} while (i < j);
	Swap(&A[l], &A[j]);
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

BEGIN_EVENT_TABLE(DisplayListCardReader, wxFrame)
EVT_CHAR_HOOK(DisplayListCardReader::OnKeyDown)
END_EVENT_TABLE()