#include "MainMenu.h"
MainMenu::MainMenu(const wxString& title) :wxFrame(NULL, -1, title,
	wxPoint(-1, -1), wxSize(1280, 680)),timer(this,TIME_ID)
{
	timer.Start(1, wxTIMER_CONTINUOUS);
	adMenu = new AdminMenu("ADMINISTRATOR MENU");
	this->AddChild(adMenu);

	//Colors;
	//wxColour lightYellow, lightBlue, red, lightGrey;
	lightYellow.Set(wxT("#E0EBB7"));
	lightBlue.Set(wxT("#54A3F2"));
	red.Set(wxT("#F74A4A"));
	lightGrey.Set(wxT("#C9CDD1"));

	
	wxPanel* mainPanel = new wxPanel(this, -1);
	wxPanel* textPanel = new wxPanel(mainPanel, -1, wxDefaultPosition, wxSize(500, 70));
	picturePanel = new wxPanel(mainPanel, -1, wxDefaultPosition, wxSize(300, 300));
	backGroundBarPanel = new wxPanel(mainPanel, -1, wxDefaultPosition, wxSize(750, 20));
	forGroundBarPanel = new wxPanel(backGroundBarPanel, -1, wxDefaultPosition, wxSize(750, 20));
	libraryPanel = new wxPanel(mainPanel, -1, wxDefaultPosition, wxSize(600, 150));
	enterText = new wxStaticText(backGroundBarPanel, -1, wxT("PRESS SPACE KEY TO CONTINUE :))"),
		wxPoint(273, 2), wxSize(200, 15), wxALIGN_CENTER);
	enterText->Hide();
	titleText = new wxStaticText(textPanel, -1,wxT("POSTS AND TELECOMMUNICATIONS INSTITUTE OF TECHNOLOGY"),
								wxPoint(0,10), wxSize(500, 20), wxALIGN_CENTER);
	titleText2 = new wxStaticText(textPanel, -1, wxT("HO CHI MINH CITY CAMPUS"),
		wxPoint(0,30), wxSize(500, 20), wxALIGN_CENTER);
	libraryText = new wxStaticText(libraryPanel, -1, wxT("LIBRARY"), 
		wxPoint(-1,20), wxSize(600, 150), wxALIGN_CENTER);
	wxFont myFont(50, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	myFont.SetPixelSize(wxSize(75, 50));
	libraryText->SetFont(myFont);
	
	// image
	wxImage::AddHandler(new wxJPEGHandler);
	wxBitmap bmp(wxT("LOGO_PTIT2.jpg"), wxBITMAP_TYPE_JPEG);
	logoImage = new wxStaticBitmap(picturePanel, -1, bmp);
	

	wxBoxSizer* mainVBox = new wxBoxSizer(wxVERTICAL);
	mainVBox->Add(libraryPanel, 0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 50);
	mainVBox->Add(picturePanel, 0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 10);
	mainVBox->Add(textPanel, 0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 20);
	mainVBox->Add(backGroundBarPanel, 0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 10);
	mainPanel->SetSizer(mainVBox);
	Centre();

	titleText->Hide();
	titleText2->Hide();
	
	//Set Color
	backGroundBarPanel->SetBackgroundColour(lightBlue);
	forGroundBarPanel->SetBackgroundColour(lightGrey);
	enterText->SetForegroundColour(lightYellow);
	picturePanel->SetBackgroundColour(lightBlue);
	//libraryPanel->SetBackgroundColour(lightBlue);

}
void MainMenu::OnTimer(wxTimerEvent& event)
{
	if (isStop)
	{
		timer.Stop();
	}
	if (distance == 752)
	{
		finishLoading = true;
		enterText->Show();
		titleText->Show();
		titleText2->Show();
		if (timer.IsRunning())
		{
			enterText->SetForegroundColour(red);
			enterText->Refresh();
			isStop = true;
		}
		else
		{
			timer.Start(470);
			isStop = false;
			enterText->SetForegroundColour(lightYellow);
			enterText->Refresh();
		}
	}
	else
	{
		forGroundBarPanel->SetPosition(wxPoint(distance, 0));
		if (distance < 600)
		{
			picturePanel->SetSize(wxSize(300, distance/2));
			libraryPanel->SetSize(wxSize(distance, 150));
		}
		distance += 2;
	}
	
	event.Skip();
}
void MainMenu::OnKeyDown(wxKeyEvent& event)
{
	event.StopPropagation();
	if (finishLoading)
	{
		if (event.GetKeyCode() == WXK_SPACE)
		{
			this->Hide();
			adMenu->Show();
			
			event.Skip();
		}
	}
	
}
BEGIN_EVENT_TABLE(MainMenu, wxFrame)
EVT_CHAR_HOOK(MainMenu::OnKeyDown)
EVT_TIMER(TIME_ID, MainMenu::OnTimer)
END_EVENT_TABLE()