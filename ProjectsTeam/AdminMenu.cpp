#include "AdminMenu.h"
AdminMenu::AdminMenu(const wxString& title) :wxFrame(NULL, -1, title,
	wxDefaultPosition, wxSize(1280, 680)),timer(this,TIMER_ID)
{
	checkInput = new CheckInput();
	timer.Start();
	LoadDataIntoTempMemory();
	// window control
	readerCard = new ReaderCard("THE DOC GIA");
	readerCard->SetData(treeCardReader,checkInput);
	displayCardReader = new DisplayListCardReader("DANH SACH THE DOC GIA");
	displayCardReader->SetData(treeCardReader,checkInput);
	bookTitle = new BookTitle("DAU SACH");
	bookTitle->SetData(titleList,checkInput);
	displayTitle = new DisplayListTitle("DANH SACH DAU SACH");
	displayTitle->SetData(titleList,checkInput);
	findInforBook = new FindInforBook("TIM KIEM THONG TIN DAU SACH");
	findInforBook->SetData(titleList,checkInput);
	lendBook = new LendBook("MUON SACH");
	lendBook->SetData(treeCardReader, titleList,checkInput);
	giveBook = new GiveBook("TRA SACH");
	giveBook->SetData(treeCardReader, titleList, checkInput);
	overDueList = new OverDueList("THE DOC GIA QUA HAN");
	overDueList->SetCardReader(treeCardReader,checkInput);
	mostBorrowings = new MostBorrowings("TOP 10 SACH MUON NHIEU NHAT");
	mostBorrowings->SetTitleList(titleList,checkInput);
	this->AddChild(readerCard);
	this->AddChild(displayCardReader);
	this->AddChild(bookTitle);
	this->AddChild(displayTitle);
	this->AddChild(findInforBook);
	this->AddChild(lendBook);
	this->AddChild(giveBook);
	this->AddChild(overDueList);
	this->AddChild(mostBorrowings);

	
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
	wxPanel* runningTextPanel = new wxPanel(mainPanel, -1, wxDefaultPosition, wxSize(500, 40));
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
	wxButton* exitButton = new wxButton(mainPanel,-1,
		wxT("THOAT"),wxPoint(1130,580),wxSize(100,30));
	wxButton* adminReaderCardButton = new wxButton(buttonPanel, -1,
		wxT("QUAN LY DOC GIA"), wxPoint(100,30), wxSize(200, 40));
	wxButton* adminTitleButton = new wxButton(buttonPanel, -1,
		wxT("QUAN LY DAU SACH"), wxPoint(400, 30), wxSize(200, 40));
	wxButton* adminFunctionBookButton = new wxButton(buttonPanel, -1,
		wxT("QUAN LY SACH"), wxPoint(700, 30), wxSize(200, 40));
	//Create static text
	wxStaticText* titleMenu = new wxStaticText(mainPanel, -1,
		wxT("QUAN LY THU VIEN"), wxPoint(485, 40), wxSize(300, 40),wxALIGN_CENTER);
	runningText = new wxStaticText(runningTextPanel, -1,
		wxT("HOC VIEN CONG NGHE BUU CHINH VIEN THONG - CO SO THANH PHO HO CHI MINH - THU VIEN PTIT"),
		wxPoint(-1, 13), wxSize(800, 20));
	checkInput->SetTextSize(titleMenu, 20);
	//Set sizer
	//mainVBox->Add(titleMenu, 0,  wxTOP|wxBOTTOM, 20);
	mainVBox->Add(buttonPanel, 0, wxTOP | wxALIGN_CENTER, 100);
	mainVBox->Add(backgroundPanel, 0, wxTOP | wxALIGN_CENTER, 20);
	mainVBox->Add(runningTextPanel, 0, wxTOP | wxALIGN_CENTER, 10);
	mainPanel->SetSizer(mainVBox);
	//Register event
	mainMenuButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnMainMenu, this);
	exitButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnExit, this);
	adminReaderCardButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnReaderCardPanel, this);
	adminTitleButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnTitlePanel, this);
	adminFunctionBookButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnFunctionBookPanel, this);
	
	//Set color
	buttonPanel->SetBackgroundColour(lightYellow);
	titleMenu->SetBackgroundColour(lightBlue);
	backgroundPanel->SetBackgroundColour(lightYellow);
	runningTextPanel->SetBackgroundColour(lightYellow);
	for (int i = 0; i < 3; i++)
	{
		choicePanel[i]->SetBackgroundColour(midBlue);
		choicePanel[i]->Hide();
	}
	CreateReaderCardChoice();
	CreateTitleChoice();
	CreateBookFunctionChoice();
	Centre();
}
void AdminMenu::CreateReaderCardChoice()
{
	wxButton* readerCardButton = new wxButton(choicePanel[0], -1, wxT("CAP NHAT DOC GIA"),
		wxPoint(50, 75), wxSize(300, 30));
	wxButton* displayCard = new wxButton(choicePanel[0], -1, wxT("HIEN THI DANH SACH TAT CA DOC GIA"),
		wxPoint(50, 130), wxSize(300, 30));
	wxButton* displayOverDueList = new wxButton(choicePanel[0], -1, wxT("HIEN THI DANH SACH THE QUA HAN"),
		wxPoint(50, 180), wxSize(300, 30));

	//Register event
	readerCardButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnReaderCard, this);
	displayCard->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnDisplayCardReader, this);
	displayOverDueList->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnOverDueList, this);
}
void AdminMenu::CreateTitleChoice()
{
	wxButton* titleButton = new wxButton(choicePanel[1], -1, wxT("CAP NHAT DAU SACH"),
		wxPoint(50, 75), wxSize(300, 30));
	wxButton* displayTitle = new wxButton(choicePanel[1], -1, wxT("HIEN THI DANH SACH TAT CA DAU SACH"),
		wxPoint(50, 130), wxSize(300, 30));
	wxButton* findInforBook = new wxButton(choicePanel[1], -1, wxT("TIM THONG TIN DAU SACH"),
		wxPoint(50, 180), wxSize(300, 30));
	//Register event
	titleButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnTitle, this);
	displayTitle->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnDisplayTitle, this);
	findInforBook->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnFindInforBook, this);
}
void AdminMenu::CreateBookFunctionChoice()
{
	wxButton* borrowBook = new wxButton(choicePanel[2], -1, wxT("MUON SACH"),
		wxPoint(50, 75), wxSize(300, 30));
	wxButton* giveBook = new wxButton(choicePanel[2], -1, wxT("TRA SACH"),
		wxPoint(50, 130), wxSize(300, 30));
	wxButton* mostBorrow = new wxButton(choicePanel[2], -1, wxT("TOP 10 SACH MUON NHIEU NHAT"),
		wxPoint(50, 180), wxSize(300, 30));
	//Register event
	borrowBook->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnBorrowBook, this);
	giveBook->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnGiveBook, this);
	mostBorrow->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AdminMenu::OnMostBorrowings, this);
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
void AdminMenu::OnBorrowBook(wxCommandEvent& WXUNUSED(event))
{
	lendBook->Show();
	this->Hide();
}
void AdminMenu::OnGiveBook(wxCommandEvent& WXUNUSED(event))
{
	giveBook->Show();
	this->Hide();
}
void AdminMenu::OnOverDueList(wxCommandEvent& WXUNUSED(event))
{
	overDueList->Show();
	this->Hide();
}
void AdminMenu::OnMostBorrowings(wxCommandEvent& WXUNUSED(event))
{
	mostBorrowings->Show();
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
void AdminMenu::OnFunctionBookPanel(wxCommandEvent& WXUNUSED(event))
{
	TurnOnPanel(2);
}

void AdminMenu::OnExit(wxCommandEvent& WXUNUSED(event))
{
	this->Close();
}
void AdminMenu::OnMainMenu(wxCommandEvent& WXUNUSED(event))
{
	this->Hide();
	this->GetParent()->Show();
}

void AdminMenu::OnTimer(wxTimerEvent& event)
{
	if (distance == -550)
	{
		distance =550;

	}
	else
	{
		distance -= 1;
		
		runningText->SetPosition(wxPoint(distance,13));
	} 
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

void AdminMenu::LoadDataIntoTempMemory()
{
	//heap memory
	cardReaderFile = new SaveTextFile<CardReader>("ListReaders.txt");
	titleFile = new SaveTextFile<Title>("BookTitle.txt");

	//card
	treeCardReader = new BSTree<CardReader>();
	int lengthCardReader = cardReaderFile->GetSizeArray();
	CardReader** arr = new CardReader*[lengthCardReader];
	cardReaderFile->ReadFile(arr);
	for (int i = 0; i < lengthCardReader; i++)
	{
		treeCardReader->Add(arr[i]);
	}
	//title
	titleList = new TitleList(100);
	int lengthTitleList = titleFile->GetSizeArray();
	Title** titles = new Title * [lengthTitleList];
	titleFile->ReadFile(titles);
	for (int i = 0; i < lengthTitleList; i++)
	{
		titleList->GetList()->AddLast(titles[i]);
	}

	delete[]titles;
	delete[]arr;

}
void AdminMenu::SaveFile()
{
	//check here if list is null
	int lengthCard = treeCardReader->GetNumberNodes();
	int lengthTitle = titleList->GetList()->Length();

	CardReader** arrCard = treeCardReader->ToSameTreeArray();
	Title** arrTitle = titleList->GetList()->ToArray();
	cardReaderFile->WriteToFile(arrCard, lengthCard);
	titleFile->WriteToFile(arrTitle, lengthTitle);
	wxMessageBox(wxString::Format("LUU THANH CONG"));
	delete[]arrCard;
}
wxBEGIN_EVENT_TABLE(AdminMenu, wxFrame)
EVT_TIMER(TIMER_ID, AdminMenu::OnTimer)
wxEND_EVENT_TABLE()

