#include "GiveBook.h"
GiveBook::GiveBook(const wxString& title) :wxFrame(NULL, -1, title,
	wxPoint(-1, -1), wxSize(1280, 680))
{
	//backend
	checkInput = new CheckInput();
	saveFile = new SaveTextFile<CardReader>("ListReaders.txt");
	treeCardReader = new BSTree<CardReader>();

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
	//Create wxCtrlText
	enterText = new wxTextCtrl(searchPanel,-1,wxT(""),
		wxPoint(50,30),wxSize(200,25), wxTE_CENTER | wxTE_PROCESS_ENTER);


	//create boxsizer
	wxBoxSizer* mainVBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* mainHBox = new wxBoxSizer(wxHORIZONTAL);

	//Set box sizer
	mainHBox->Add(searchPanel, 0, wxLEFT|wxRIGHT,475);
	mainVBox->Add(mainHBox,0,wxTOP,10);
	//Register event
	Bind(wxEVT_SHOW, &GiveBook::OnShow, this);
	Bind(wxEVT_TEXT_ENTER, &GiveBook::OnEnter, this);
	//Set Color
	searchPanel->SetBackgroundColour(lightYellow);

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
			wxPoint(20, 95 + i * 50), wxSize(260, 25));
		displayText[i]->SetBackgroundColour(lightBlue);
	}
}
void GiveBook::OnShow(wxShowEvent& event)
{
	if (event.IsShown())
	{
		LoadFile();
		ClearOldDataOnPanel();
		enterText->Clear();
		foundCard = nullptr;
	}
	event.Skip();
}
void GiveBook::OnEnter(wxCommandEvent& WXUNUSED(event))
{
	string keyCodeStr = string(enterText->GetValue().mb_str());
	ulong keyCode = checkInput->CastStringToNumber(keyCodeStr);
	BSTNode<CardReader>* tempNode = treeCardReader->Search(keyCode);
	if (tempNode == nullptr)
	{
		checkInput->ErrorMessageBox("KHONG TIM THAY THE DOC");
		ClearOldDataOnPanel();
		return;
	}
	enterText->Clear();
	foundCard = tempNode->data;
	DisplayCardOnPanel();
}
void GiveBook::OnKeyDown(wxKeyEvent& event)
{

	if (enterText->HasFocus())
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
void GiveBook::DisplayCardOnPanel()
{
	if (foundCard == nullptr) { return; }
	displayText[0]->SetLabel(foundCard->GetFirstName() + " " + foundCard->GetLastName());
	displayText[1]->SetLabel(foundCard->GetSex());
	displayText[2]->SetLabel(foundCard->GetState());
}
void GiveBook::ClearOldDataOnPanel()
{
	for (int i = 0; i < 3; i++)
	{
		displayText[i]->SetLabel("");
	}
}
void GiveBook::LoadFile()
{
	treeCardReader->Clear();
	length = saveFile->GetSizeArray();
	CardReader** arr = new CardReader * [length];
	saveFile->ReadFile(arr);
	for (int i = 0; i < length; i++)
	{
		treeCardReader->Add(arr[i]);
	}
	delete arr;
}
BEGIN_EVENT_TABLE(GiveBook, wxFrame)
EVT_CHAR_HOOK(GiveBook::OnKeyDown)
END_EVENT_TABLE()
