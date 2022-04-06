#include "GiveBook.h"
GiveBook::GiveBook(const wxString& title) :wxFrame(NULL, -1, title,
	wxPoint(-1, -1), wxSize(1280, 680))
{
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
	searchPanel = new wxPanel(mainPanel, -1, wxPoint(-1, -1), wxSize(300, 300));

	//Create wxStaticText
	wxStaticText* titleSearch = new wxStaticText(searchPanel, -1, wxT("NHAP MA THE DOC GIA"),
		wxPoint(-1, 10), wxSize(300, 20), wxALIGN_CENTER);
	//Create wxCtrlText
	enterText = new wxTextCtrl();

	//create boxsizer
	wxBoxSizer* mainVBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* mainHBox = new wxBoxSizer(wxHORIZONTAL);

	//Set box sizer
	mainHBox->Add(searchPanel, 0, wxLEFT|wxRIGHT,450);
	mainVBox->Add(mainHBox);
	//Set Color
	searchPanel->SetBackgroundColour(lightYellow);

	mainPanel->SetSizer(mainVBox);
	Centre();
}
