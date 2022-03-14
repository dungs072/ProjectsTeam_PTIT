#include "ReaderCard.h"
using namespace Library;
ReaderCard::ReaderCard(const wxString& title) :wxFrame
(NULL, -1, title, wxPoint(-1, -1), wxSize(1280, 680))
{
	//colors
	wxColour lightYellow, greenColor, organColor, lightBlue, eggYellow, lightRed;
	lightYellow.Set(wxT("#E0EBB7"));
	greenColor.Set(wxT("#03FF29"));
	organColor.Set(wxT("#FFAB03"));
	lightBlue.Set(wxT("#7FB1E3"));
	eggYellow.Set(wxT("#FDFF69"));
	lightRed.Set(wxT("#FA8E8E"));


	wxPanel* mainPanel = new wxPanel(this, -1);
	//create NoteBook
	noteBook = new wxNotebook(mainPanel, -1, wxPoint(-1, -1), wxSize(300, 300), wxNB_TOP);
	//Draw label title 
	wxPanel* labelTitleBackGround = new wxPanel(mainPanel, -1, wxPoint(-1, -1), wxSize(500, 50));
	enterTextBackGround = new wxPanel(noteBook, -1, wxPoint(-1, -1), wxSize(300, 300));
	insertTextBackGround = new wxPanel(noteBook, -1, wxPoint(-1, -1), wxSize(300, 300));
	guidePanel = new wxPanel(mainPanel, -1, wxPoint(-1, -1), wxSize(400, 75));
	noteTableBackGround = new wxPanel(mainPanel, -1, wxPoint(1050, 103), wxSize(200, 100));
	wxStaticText* labelText = new wxStaticText(labelTitleBackGround, -1,
		wxT("DANH SACH THE DOC"), wxPoint(50, -1), wxSize(350, 30));
	SetTextSize(*labelText, 30);
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
	//create grid;
	grid = new wxGrid(mainPanel, -1, wxDefaultPosition, wxSize(708, 500), wxEVT_GRID_CELL_CHANGED);
	grid->CreateGrid(DefaultRows, 5);
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
	for (int i = 0; i < grid->GetNumberRows(); i++)
	{
		grid->SetReadOnly(i, 0);
	}
	listBox->Add(grid, 0, wxTOP, 10);
	mainHBox->Add(listBox, 0, wxTOP, 20);
	CreateEnterArea();
	CreateInsertArea();
	CreateNoteArea();
	MakeStateCodeText();
	//Set BoxSizer
	vRightBox->Add(noteBook, 0, wxTOP, 80);
	vGuideBox->Add(labelGuide, 0, wxLEFT, 145);
	vGuideBox->Add(guidePanel, 0, wxTOP, 5);

	vRightBox->Add(vGuideBox, 0, wxTOP, 115);
	mainHBox->Add(vRightBox, 0, wxLEFT, 20);

	noteBook->AddPage(enterTextBackGround, wxT("NHAP"));
	noteBook->AddPage(insertTextBackGround, wxT("CHEN"));
	//Set colors
	enterTextBackGround->SetBackgroundColour(lightYellow);
	insertTextBackGround->SetBackgroundColour(lightYellow);
	noteTableBackGround->SetBackgroundColour(lightYellow);
	labelTitleBackGround->SetBackgroundColour(lightBlue);

	guidePanel->SetBackgroundColour(lightYellow);
	//Register event
	Bind(wxEVT_TEXT_ENTER, &ReaderCard::OnEnter, this);
	grid->Bind(wxEVT_GRID_CELL_CHANGED, &ReaderCard::EditCurrentCell, this);
	Connect(LOOKUP_ID, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(ReaderCard::OnSearch));
	//SetSizer for mainPanel runs on it
	mainPanel->SetSizer(mainHBox);
	//Create Menu bar
	menuBar = new wxMenuBar;
	file = new wxMenu;
	file->Append(LOOKUP_ID, wxT("&Search"));
	menuBar->Append(file, wxT("&File"));
	SetMenuBar(menuBar);
	Centre();
}

void ReaderCard::SetTextSize(wxStaticText& text, int size)
{
	wxFont tempFont = text.GetFont();
	tempFont.SetPointSize(size);
	text.SetFont(tempFont);
}
void ReaderCard::CreateEnterArea()
{
	wxColour lightBlue2, lightGreen, defaultColor;
	lightBlue2.Set(wxT("#9AD6E6"));
	lightGreen.Set(wxT("#ACE39D"));
	defaultColor.Set(wxT("#E0E0E0"));
	enterText = new wxTextCtrl * [4];
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
	}
	GuideToUser();
	//mainHBox->Add(enterTextBackGround, 0, wxLEFT|wxTOP, 60);
}
void ReaderCard::CreateInsertArea()
{
	wxColour lightBlue2, lightGreen;
	lightBlue2.Set(wxT("#9AD6E6"));
	lightGreen.Set(wxT("#ACE39D"));
	enterText2 = new wxTextCtrl * [5];
	wxStaticText** labelText2 = new wxStaticText * [5];
	labelText2[0] = new wxStaticText(insertTextBackGround, -1, wxT("HO: "), wxPoint(10, 10));
	labelText2[1] = new wxStaticText(insertTextBackGround, -1, wxT("TEN: "), wxPoint(10, 60));
	labelText2[2] = new wxStaticText(insertTextBackGround, -1, wxT("PHAI: "), wxPoint(10, 110));
	labelText2[3] = new wxStaticText(insertTextBackGround, -1, wxT("TRANG THAI THE: "), wxPoint(10, 160));
	labelText2[4] = new wxStaticText(insertTextBackGround, -1, wxT("HANG CHEN: "), wxPoint(10, 210));
	for (int i = 0; i < 5; i++)
	{
		enterText2[i] = new wxTextCtrl(insertTextBackGround, -1, wxT(""),
			wxPoint(10, 30 * (i + 1) + i * 20), wxSize(170, -1), wxTE_CENTER | wxTE_PROCESS_ENTER);
		enterText2[i]->SetBackgroundColour(lightBlue2);
	}
}
void ReaderCard::CreateNoteArea()
{
	wxColor lightRed, orange;
	lightRed.Set(wxT("#FA8E8E"));
	orange.Set(wxT("#FF9B70"));
	wxStaticText* noteLabel = new wxStaticText(noteTableBackGround, -1,
		wxT("GHI CHU"), wxPoint(50, 10), wxSize(100, -1), wxALIGN_CENTER_HORIZONTAL);
	wxStaticText* note1 = new wxStaticText(noteTableBackGround, -1,
		wxT("0: LA THE BI KHOA"), wxPoint(27, 40), wxSize(150, -1), wxALIGN_CENTER_HORIZONTAL);
	wxStaticText* note2 = new wxStaticText(noteTableBackGround, -1,
		wxT("1: LA THE HOAT DONG"), wxPoint(27, 70), wxSize(150, -1), wxALIGN_CENTER_HORIZONTAL);


	//Set Color
	noteLabel->SetBackgroundColour(lightRed);
	note1->SetBackgroundColour(orange);
	note2->SetBackgroundColour(orange);
}
void ReaderCard::GuideToUser()
{
	wxColour orange, lightOrange;
	orange.Set(wxT("#FF9B70"));
	lightOrange.Set(wxT("#FCD2C0"));

	//save area
	wxStaticText* saveLabel = new wxStaticText(guidePanel, -1, wxT("Nhap den danh sach"),
		wxPoint(20, 20), wxSize(100, 30), wxALIGN_CENTRE_HORIZONTAL | wxALIGN_CENTER_VERTICAL);

	wxStaticText* saveText = new wxStaticText(guidePanel, -1, wxT("Enter"), wxPoint(55, 55));

	//delete area
	wxStaticText* deleteLabel = new wxStaticText(guidePanel, -1, wxT("Xoa khoi danh sach"),
		wxPoint(150, 20), wxSize(100, 30), wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);

	wxStaticText* deleteText = new wxStaticText(guidePanel, -1, wxT("Delete"), wxPoint(183, 55));

	//set color for backgrounds
	saveLabel->SetBackgroundColour(orange);
	deleteLabel->SetBackgroundColour(orange);
	saveText->SetBackgroundColour(lightOrange);
	deleteText->SetBackgroundColour(lightOrange);
}
void ReaderCard::OnEnter(wxCommandEvent& WXUNUSED(event))
{
	if (noteBook->GetSelection() == 0)
	{
		SaveToList(enterText, 4, count);
	}
	else if (noteBook->GetSelection() == 1)
	{
		InsertToList();
	}

}
void ReaderCard::SaveToList(wxTextCtrl** textCtrlList, int length, int& pos)
{
	for (int j = 0; j < length; j++)
	{
		if (IsWhiteSpaceAllText(textCtrlList[j]))
		{
			ErrorMessageBox(pos, "Chua Nhap Thong Tin Du ");
			return;
		}
	}
	ModifyTextInput(textCtrlList[3]);
	int stateCard = CastWxStringToInt(textCtrlList[3]);
	if (stateCard == -1)
	{
		ErrorMessageBox(pos, "Loi Nhap Lieu ");
		return;
	}
	if (!IsRightCodeState(1, stateCard))
	{
		ErrorMessageBox(pos, "Loi Nhap Lieu ");
		return;
	}
	if (!IsRightSex(textCtrlList[2]))
	{
		ErrorMessageBox(pos, "Loi Nhap Lieu ");
		return;
	}
	for (int j = 0; j < 3; j++)
	{
		if (!IsWord(textCtrlList[j]))
		{
			ErrorMessageBox(pos, "Loi Nhap Lieu ");
			return;
		}
	}

	int i = 0;
	if (pos == grid->GetNumberRows())
	{
		grid->AppendRows(DefaultRows);
		for (int i = pos; i < grid->GetNumberRows(); i++)
		{
			grid->SetReadOnly(i, 0);
		}
	}
	textCtrlList[3]->SetLabelText(stateText[stateCard]);


	WriteHashCodeToCell(pos, textCtrlList);
	for (i = 1; i < 5; i++)
	{
		ModifyTextInput(textCtrlList[i - 1]);
		UpperWxString(textCtrlList[i - 1]);
		grid->SetCellValue(pos, i, textCtrlList[i - 1]->GetValue());
		grid->SetCellAlignment(pos, i, wxALIGN_CENTER, wxALIGN_CENTER);
		textCtrlList[i - 1]->Clear();

	}

	for (; i - 1 < length; i++)
	{
		textCtrlList[i - 1]->Clear();
	}
	textCtrlList[0]->SetFocus();
	count++;
	if (pos == grid->GetNumberRows())
	{
		grid->AppendRows(DefaultRows);
		for (int i = pos; i < grid->GetNumberRows(); i++)
		{
			grid->SetReadOnly(i, 0);
		}
	}
}
void ReaderCard::InsertToList()
{
	int row = CastWxStringToInt(enterText2[4]) - 1;
	if (row > count || row < 0)
	{
		wxMessageBox(wxString::Format("Loi vi tri chen"));
		return;
	}
	grid->InsertRows(row, 1);
	grid->SetReadOnly(row, 0);
	SaveToList(enterText2, 5, row);
}

void ReaderCard::OnKeyDown(wxKeyEvent& event)
{

	if (event.GetKeyCode() == WXK_DELETE)
	{
		//wxMessageBox(wxString::Format("Key pressed: %c", event.GetUnicodeKey()));
		ShowMessageClear();

	}
	if (event.GetKeyCode() == WXK_DOWN)
	{
		if (noteBook->GetSelection() == 0)
		{
			MoveDownToAnotherTextCtrl(enterText, 4);
		}
		else if (noteBook->GetSelection() == 1)
		{
			MoveDownToAnotherTextCtrl(enterText2, 5);
		}
	}
	if (event.GetKeyCode() == WXK_UP)
	{
		if (noteBook->GetSelection() == 0)
		{
			MoveUpToAnotherTextCtrl(enterText, 4);
		}
		else if (noteBook->GetSelection() == 1)
		{
			MoveUpToAnotherTextCtrl(enterText2, 5);
		}
	}
	event.Skip();
}
void ReaderCard::OnSearch(wxCommandEvent& WXUNUSED(event))
{

}
void ReaderCard::DeleteSelectedRows()
{

	if (grid->IsSelection())
	{
		wxGridUpdateLocker locker(grid);
		for (int i = 0; i < grid->GetNumberRows();)
		{
			if (grid->IsInSelection(i, 0))
			{

				grid->DeleteRows(i, 1);
				if (i < count)
				{
					count--;
				}
				if (grid->GetNumberRows() < DefaultRows)
				{
					int numberRowsNeed = DefaultRows - grid->GetNumberRows();

					grid->AppendRows(numberRowsNeed);
				}
			}
			else
				i++;
		}
		count = count < 0 ? 0 : count;
		//wxMessageBox(wxString::Format("Key pressed: %d", count));
	}
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
}
void ReaderCard::MoveDownToAnotherTextCtrl(wxTextCtrl** textCtrl, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (textCtrl[i]->HasFocus())
		{
			if (i < length - 1)
			{
				textCtrl[i + 1]->SetFocus();
				return;
			}
			else if (i == length - 1)
			{
				textCtrl[0]->SetFocus();
				return;
			}

		}
	}
}
void ReaderCard::MoveUpToAnotherTextCtrl(wxTextCtrl** textCtrl, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (textCtrl[i]->HasFocus())
		{
			if (i > 0)
			{
				textCtrl[i - 1]->SetFocus();
				return;
			}
			else if (i == 0)
			{
				textCtrl[length - 1]->SetFocus();
				return;
			}
		}
	}
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
void ReaderCard::MakeStateCodeText()
{
	stateText = new std::string[2]{ "KHOA","HOAT DONG" };
}
void ReaderCard::UpperWxString(wxTextCtrl* textCtrl)
{
	wxString wxStr = textCtrl->GetLineText(0);
	UpperWxString(wxStr);
	textCtrl->SetValue(wxStr);
}
void ReaderCard::UpperWxString(wxString& wxStr)
{
	std::string strText = std::string(wxStr.mb_str());
	strText = UpperText(strText);
	wxString myWxString(strText.c_str(), wxConvUTF8);
	wxStr = myWxString;
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
	if (IsWhiteSpaceAllText(wxNewText))
	{
		ErrorMessageBox(-1, "Loi Nhap Lieu ");
		grid->SetCellValue(row, col, wxOldText);
		return;
	}

	//col errors
	if (col == 1 || col == 2)
	{
		ModifyTextInput(wxNewText);
		if (!IsWord(wxNewText))
		{
			ErrorMessageBox(-1, "Loi Nhap Lieu ");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}

		UpperWxString(wxNewText);
		grid->SetCellValue(row, col, wxNewText);
		WriteHashCodeToCell(row);
	}
	if (col == 3)
	{
		if (!IsRightSex(wxNewText))
		{
			ErrorMessageBox(-1, "Loi Nhap Lieu ");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}
		UpperWxString(wxNewText);
		grid->SetCellValue(row, col, wxNewText);
		WriteHashCodeToCell(row);
	}
	if (col == 4)
	{
		ModifyTextInput(wxNewText);
		int num = CastWxStringToInt(wxNewText);
		if (!IsRightCodeState(1, num))
		{
			ErrorMessageBox(-1, "Loi Nhap Lieu ");
			grid->SetCellValue(row, col, wxOldText);
			return;
		}
		grid->SetCellValue(row, col, stateText[num]);
	}
	//wxMessageBox(event.GetString());
	event.Skip();
}
void ReaderCard::WriteHashCodeToCell(int pos, wxTextCtrl** textCtrlList)
{
	long long hashCode = CreateHashCode(textCtrlList);
	std::string strCode = EditCardCode(hashCode, 10);
	wxString wxStrCode(strCode.c_str(), wxConvUTF8);
	grid->SetCellValue(pos, 0, wxStrCode);
	grid->SetCellAlignment(pos, 0, wxALIGN_CENTER, wxALIGN_CENTER);
}
void ReaderCard::WriteHashCodeToCell(int row)
{
	long long hashCode = CreateHashCode(row);
	std::string strCode = EditCardCode(hashCode, 10);
	wxString wxStrCode(strCode.c_str(), wxConvUTF8);
	grid->SetCellValue(row, 0, wxStrCode);
	grid->SetCellAlignment(row, 0, wxALIGN_CENTER, wxALIGN_CENTER);
}
bool ReaderCard::IsWhiteSpaceAllText(wxTextCtrl* textCtrl)
{
	return IsWhiteSpaceAllText(textCtrl->GetLineText(0));
}
bool ReaderCard::IsWhiteSpaceAllText(wxString wxStr)
{
	std::string strText = std::string(wxStr.mb_str());
	for (char str : strText)
	{
		if (str != ' ')
		{
			return false;
		}
	}
	return true;
}
bool ReaderCard::IsWord(wxTextCtrl* textCtrl)
{
	wxString wxStr = textCtrl->GetLineText(0);
	return IsWord(wxStr);
}
bool ReaderCard::IsWord(wxString wxStr)
{
	std::string strText = std::string(wxStr.mb_str());
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
bool ReaderCard::IsRightSex(wxTextCtrl* textCtrl)
{
	std::string strText = std::string(textCtrl->GetLineText(0).mb_str());
	wxString wxStr = textCtrl->GetLineText(0);
	if (IsRightSex(wxStr))
	{
		textCtrl->SetLabelText(wxStr);
		return true;
	}
	return false;
}
bool ReaderCard::IsRightSex(wxString& wxStr)
{
	std::string strText = std::string(wxStr.mb_str());
	strText = UpperText(strText);
	if (strText == "") { return false; }
	ModifyString(strText);
	wxString myWxString(strText.c_str(), wxConvUTF8);
	if (strText == "NAM" || strText == "NU")
	{
		wxStr = myWxString;
		return true;
	}
	return false;
}
bool ReaderCard::IsRightCodeState(int maxNumber, int number)
{
	return number >= 0 && number <= maxNumber;
}
std::string ReaderCard::UpperText(std::string text)
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
std::string ReaderCard::EditCardCode(long long number, int maxLengthCode)
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
	return CastWxStringToInt(wxStr);
}
int ReaderCard::CastWxStringToInt(wxString wxStr)
{
	int i, j;
	int number = 0;
	std::string strText = std::string(wxStr.mb_str());
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
long long ReaderCard::CreateHashCode(wxTextCtrl** textCtrlList)
{

	std::string strText = "";
	wxString wxStrText = wxT("");
	for (int i = 0; i < 3; i++)
	{
		if (i == 1) { continue; }
		wxStrText += textCtrlList[i]->GetLineText(0);
	}
	wxStrText += textCtrlList[1]->GetLineText(0);
	UpperWxString(wxStrText);
	strText = std::string(wxStrText.mb_str());
	return HashCode(strText);

}
long long ReaderCard::CreateHashCode(int row)
{
	wxString wxStrText = wxT("");
	std::string strText = "";
	for (int i = 1; i < 4; i++)
	{
		if (i == 2) { continue; }
		wxStrText += grid->GetCellValue(row, i);
	}
	wxStrText += grid->GetCellValue(row, 2);
	strText = std::string(wxStrText.mb_str());
	return HashCode(strText);
}
long long ReaderCard::HashCode(std::string strText)
{
	long long hashCode = 0;
	for (int i = 0; i < strText.length(); i++)
	{
		if (strText[i] == ' ')
		{
			strText.erase(strText.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < strText.length(); i++)
	{
		hashCode += strText[i] * i;
	}
	return hashCode;
}
BEGIN_EVENT_TABLE(ReaderCard, wxFrame)
EVT_CHAR_HOOK(ReaderCard::OnKeyDown)
END_EVENT_TABLE()
