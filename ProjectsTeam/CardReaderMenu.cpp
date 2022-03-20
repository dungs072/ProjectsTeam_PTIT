#include "CardReaderMenu.h"
CardReaderMenu::CardReaderMenu(const wxString& title) :
	wxFrame(NULL, -1, title, wxDefaultPosition, wxSize(1280, 680))
{
	//child app
	displayList = new DisplayListCardReader("IN DANH SACH THE DOC GIA");
	readerCard = new ReaderCard("NHAP THE DOC GIA");
	displayList->SetReaderCard(readerCard);
	this->AddChild(displayList);
	this->AddChild(readerCard);
	//create Color
	wxColour lightYellow, greenColor, organColor, lightBlue, eggYellow, lightRed,llRed,ldBlue;
	lightYellow.Set(wxT("#E0EBB7"));
	greenColor.Set(wxT("#03FF29"));
	organColor.Set(wxT("#FFAB03"));
	lightBlue.Set(wxT("#7FB1E3"));
	eggYellow.Set(wxT("#FDFF69"));
	lightRed.Set(wxT("#FA8E8E"));
	llRed.Set(wxT("#DEA0A0"));
	ldBlue.Set(wxT("#867DFF"));
	//Create Panel
	wxPanel* mainPanel = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(-1, -1));
	wxPanel* menuPanel = new wxPanel(mainPanel, -1, wxPoint(-1, -1), wxSize(450, 500));
	//Create StaticText
	wxStaticText* mainTitle = new wxStaticText(mainPanel, -1, wxT("QUAN LY THE DOC GIA")
		,wxDefaultPosition,wxSize(-1,-1));
	wxStaticText* menuTitle = new wxStaticText(menuPanel, -1, wxT("MENU"),
		wxPoint(-1,-1),wxSize(300,30),wxALIGN_CENTER);
	SetTextSize(mainTitle, 30);
	SetTextSize(menuTitle, 15);
	//Create BoxSizer
	wxBoxSizer* vBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vMainBox = new wxBoxSizer(wxVERTICAL);
	//Create Button
	wxButton* readerCardButton = new wxButton(menuPanel, READER_CARD, 
		wxT("NHAP THE DOC GIA"),wxPoint(-1,-1),wxSize(200,50));
	wxButton* displayListButton = new wxButton(menuPanel, DISPLAY_LIST,
		wxT("IN DANH SACH DOC GIA"), wxPoint(-1, -1), wxSize(200, 50));
	SetTextSize(readerCardButton, 11);
	SetTextSize(displayListButton, 11);
	//SetBoxSizer
	vBox->Add(menuTitle, 0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 20);
	vBox->Add(readerCardButton, 0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 50);
	vBox->Add(displayListButton, 0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 20);
	menuPanel->SetSizer(vBox);
	vMainBox->Add(mainTitle, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL,20);
	vMainBox->Add(menuPanel, 0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 50);
	mainPanel->SetSizer(vMainBox);

	//Register event
	Connect(READER_CARD, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(CardReaderMenu::OnReaderCard));
	Connect(DISPLAY_LIST, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(CardReaderMenu::OnDisplayList));
	//set color
	mainTitle->SetBackgroundColour(lightBlue);
	menuPanel->SetBackgroundColour(lightYellow);
	menuTitle->SetBackgroundColour(llRed);
	readerCardButton->SetBackgroundColour(ldBlue);
	displayListButton->SetBackgroundColour(ldBlue);
	Centre();
}
void CardReaderMenu::OnReaderCard(wxCommandEvent& WXUNUSED(event))
{
	if (readerCard == nullptr) { return; }
	readerCard->Show(true);
	this->Show(false);
}
void CardReaderMenu::OnDisplayList(wxCommandEvent& WXUNUSED(event))
{
	if (displayList == nullptr) { return; }
	displayList->Show(true);
	this->Show(false);
}
void CardReaderMenu::SetTextSize(wxStaticText* text, int size)
{
	wxFont tempFont = text->GetFont();
	tempFont.SetPointSize(size);
	text->SetFont(tempFont);
}
void CardReaderMenu::SetTextSize(wxButton* text, int size)
{
	wxFont tempFont = text->GetFont();
	tempFont.SetPointSize(size);
	text->SetFont(tempFont);
}
