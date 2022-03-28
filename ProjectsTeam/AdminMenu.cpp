#include "AdminMenu.h"
AdminMenu::AdminMenu(const wxString& title) :wxFrame(NULL, -1, title,
	wxDefaultPosition, wxSize(1280, 680))
{
	// window control
	readerCard = new ReaderCard("THE DOC GIA");
	displayCardReader = new DisplayListCardReader("DANH SACH THE DOC GIA");
	bookTitle = new BookTitle("DAU SACH");
	displayTitle = new DisplayListTitle("DANH SACH DAU SACH");
	findInforBook = new FindInforBook("TIM KIEM THONG TIN DAU SACH");
	this->AddChild(readerCard);
	this->AddChild(displayCardReader);
	this->AddChild(bookTitle);
	this->AddChild(displayTitle);
	this->AddChild(findInforBook);

	checkInput = new CheckInput();
	//create color;
	wxColour lightYellow, greenColor, organColor, lightBlue,midBlue,
		eggYellow, lightRed, red, middleYellow;
	middleYellow.Set("#ECFF82");
	lightYellow.Set(wxT("#E0EBB7"));
	greenColor.Set(wxT("#03FF29"));
	organColor.Set(wxT("#FFAB03"));
	lightBlue.Set(wxT("#7FB1E3"));
	eggYellow.Set(wxT("#FDFF69"));
	lightRed.Set(wxT("#FA8E8E"));
	red.Set(wxT("#F74A4A"));
	midBlue.Set(wxT("#ACD0E0"));
	//create Panel
	wxPanel* mainPanel = new wxPanel(this, -1);
	wxPanel* buttonPanel = new wxPanel(mainPanel, -1, wxDefaultPosition, wxSize(1000, 100));
	wxPanel* backgroundPanel = new wxPanel(mainPanel, -1, wxDefaultPosition, wxSize(1000, 350));
	choicePanel = new wxPanel * [3];
	for (int i = 0; i < 3; i++)
	{
		choicePanel[i] = new wxPanel(backgroundPanel, -1,
			wxPoint(300, 20), wxSize(400, 300), wxALIGN_CENTER);
	}
	//create BoxSizer
	wxBoxSizer* mainVBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hBox = new wxBoxSizer(wxHORIZONTAL);
	//create button
	wxButton* mainMenuButton = new wxButton(mainPanel, -1,
		wxT("MENU CHINH"), wxPoint(30,580), wxSize(100, 30));
	wxButton* adminReaderCardButton = new wxButton(buttonPanel, -1,
		wxT("QUAN LY DOC GIA"), wxPoint(100,30), wxSize(200, 40));
	wxButton* adminTitleButton = new wxButton(buttonPanel, -1,
		wxT("QUAN LY DAU SACH"), wxPoint(400, 30), wxSize(200, 40));
	wxButton* adminBookButton = new wxButton(buttonPanel, -1,
		wxT("QUAN LY SACH"), wxPoint(700, 30), wxSize(200, 40));
	//Create static text
	wxStaticText* titleMenu = new wxStaticText(mainPanel, -1,
		wxT("QUAN LY THU VIEN"), wxPoint(485, 40), wxSize(300, 40),wxALIGN_CENTER);
	checkInput->SetTextSize(titleMenu, 20);
	//Set sizer
	//mainVBox->Add(titleMenu, 0,  wxTOP|wxBOTTOM, 20);
	mainVBox->Add(buttonPanel, 0, wxTOP | wxALIGN_CENTER, 100);
	mainVBox->Add(backgroundPanel, 0, wxTOP | wxALIGN_CENTER, 20);
	mainPanel->SetSizer(mainVBox);
	//Register event
	adminReaderCardButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnReaderCardPanel, this);
	adminTitleButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnTitlePanel, this);
	//Set color
	buttonPanel->SetBackgroundColour(lightYellow);
	titleMenu->SetBackgroundColour(lightBlue);
	backgroundPanel->SetBackgroundColour(lightYellow);
	for (int i = 0; i < 3; i++)
	{
		choicePanel[i]->SetBackgroundColour(midBlue);
		choicePanel[i]->Hide();
	}
	CreateReaderCardChoice();
	CreateTitleChoice();
	Centre();
}
void AdminMenu::CreateReaderCardChoice()
{
	wxButton* readerCardButton = new wxButton(choicePanel[0], -1, wxT("CAP NHAT DOC GIA"),
		wxPoint(50, 50), wxSize(300, 25));
	wxButton* displayCard = new wxButton(choicePanel[0], -1, wxT("HIEN THI DANH SACH TAT CA DOC GIA"),
		wxPoint(50, 100), wxSize(300, 25));

	//Register event
	readerCardButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnReaderCard, this);
	displayCard->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnDisplayCardReader, this);
}
void AdminMenu::CreateTitleChoice()
{
	wxButton* titleButton = new wxButton(choicePanel[1], -1, wxT("CAP NHAT DAU SACH"),
		wxPoint(50, 50), wxSize(300, 25));
	wxButton* displayTitle = new wxButton(choicePanel[1], -1, wxT("HIEN THI DANH SACH TAT CA DAU SACH"),
		wxPoint(50, 100), wxSize(300, 25));
	wxButton* findInforBook = new wxButton(choicePanel[1], -1, wxT("TIM THONG TIN DAU SACH"),
		wxPoint(50, 150), wxSize(300, 25));
	//Register event
	titleButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnTitle, this);
	displayTitle->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnDisplayTitle, this);
	findInforBook->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnFindInforBook, this);
}

void AdminMenu::OnReaderCard(wxCommandEvent& WXUNUSED(event))
{
	readerCard->Show();
	this->Hide();
}
void AdminMenu::OnDisplayCardReader(wxCommandEvent& WXUNUSED(event))
{
	displayCardReader->Show();
	this->Hide();
}
void AdminMenu::OnTitle(wxCommandEvent& WXUNUSED(event))
{
	bookTitle->Show();
	this->Hide();
}
void AdminMenu::OnDisplayTitle(wxCommandEvent& WXUNUSED(event))
{
	displayTitle->Show();
	this->Hide();
}
void AdminMenu::OnFindInforBook(wxCommandEvent& WXUNUSED(event))
{
	findInforBook->Show();
	this->Hide();
}
void AdminMenu::OnReaderCardPanel(wxCommandEvent& WXUNUSED(event))
{
	TurnOnPanel(0);
}
void AdminMenu::OnTitlePanel(wxCommandEvent& WXUNUSED(event))
{
	TurnOnPanel(1);
}

void AdminMenu::TurnOnPanel(int index)
{
	//enter index>3||index<0 to disable all pannel
	for (int i = 0; i < 3; i++)
	{
		if (i == index)
		{
			choicePanel[i]->Show();
		}
		else
		{
			choicePanel[i]->Hide();
		}
	}
}
