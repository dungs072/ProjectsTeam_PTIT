#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
class GiveBook:public wxFrame
{
private:
	wxPanel* searchPanel;
	wxGrid* grid;
public:
	GiveBook(const wxString&  title);
};

