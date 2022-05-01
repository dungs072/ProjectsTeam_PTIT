#pragma once
#include<wx/wx.h>
#include"AdminMenu.h"
class MainMenu:public wxFrame
{
private:
	AdminMenu* adMenu;
	wxColour lightYellow, lightBlue, red, lightGrey;
	wxTimer timer;
	wxPanel* backGroundBarPanel;
	wxPanel* forGroundBarPanel;
	wxPanel* picturePanel;
	wxPanel* libraryPanel;
	wxStaticText* enterText;
	wxStaticText* titleText;
	wxStaticText* titleText2;
	wxStaticText* libraryText;
	wxStaticBitmap* logoImage;
	bool finishLoading = false;
	int distance = 0;
	void OnTimer(wxTimerEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	bool isStop = false;

public:
	MainMenu(const wxString& title);
	wxDECLARE_EVENT_TABLE();
};
const int TIME_ID = 8;

