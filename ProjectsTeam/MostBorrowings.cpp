#include"MostBorrowings.h"
MostBorrowings::MostBorrowings(const wxString& title) :wxFrame(NULL, -1, title,
	wxPoint(-1, -1), wxSize(1280, 680))
{
	wxColour lightYellow, red;
	lightYellow.Set(wxT("#E0EBB7"));
	red.Set(wxT("#F74A4A"));

	sort = new SortAlgorithm<Title>();
	sort->Compare = [](Title* t1, Title* t2)
	{
		if (t1->GetCountBorrow() > t2->GetCountBorrow()) { return -1; }
		else if (t1->GetCountBorrow() < t2->GetCountBorrow()) { return 1; }
		return 0;
	};
	checkInput = new CheckInput();
	wxPanel* mainPanel = new wxPanel(this, -1);
	wxButton* exitMainMenu = new wxButton(mainPanel, -1, wxT("EXIT MENU"), 
		wxPoint(20, 600), wxSize(-1, -1));
	wxStaticText* titlePanel = new wxStaticText(mainPanel, -1,
		wxT("TOP 10 CUON SACH DUOC MUON NHIEU NHAT"), 
		wxPoint(-1, -1), wxSize(500, 30),wxALIGN_CENTRE);
	checkInput->SetTextSize(titlePanel, 15);
	grid = new wxGrid(mainPanel, -1, wxPoint(-1, -1), wxSize(730, 225));
	grid->CreateGrid(10, 5);
	grid->SetColLabelValue(0, wxT("ISBN"));
	grid->SetColLabelValue(1, wxT("TEN SACH"));
	grid->SetColLabelValue(2, wxT("TAC GIA"));
	grid->SetColLabelValue(3, wxT("THE LOAI"));
	grid->SetColLabelValue(4, wxT("SL MUON"));
	for (int i = 0; i < 5; i++)
	{
		if (i == 0) { grid->SetColSize(i, 50); continue; }
		if (i == 1||i==2) { grid->SetColSize(i, 200); continue; }
		if (i == 4) { grid->SetColSize(i, 64); continue; }
		grid->SetColSize(i, 164);
	}
	grid->SetSelectionMode(wxGrid::wxGridSelectionModes::wxGridSelectRows);
	grid->SetRowLabelSize(50);
	grid->DisableDragColSize();
	grid->DisableDragRowSize();
	wxBoxSizer* mainVBox = new wxBoxSizer(wxVERTICAL);
	mainVBox->Add(titlePanel, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 100);
	mainVBox->Add(grid, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 30);
	mainPanel->SetSizer(mainVBox);
	this->Centre();

	//Register event
	this->Bind(wxEVT_SHOW, &MostBorrowings::OnShow, this);
	exitMainMenu->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MostBorrowings::OnExitMenu, this);

	//Set color
	exitMainMenu->SetBackgroundColour(red);
	titlePanel->SetBackgroundColour(lightYellow);
}
void MostBorrowings::OnShow(wxShowEvent& event)
{
	if (event.IsShown())
	{
		int length = titleList->GetList()->Length();
		Title** arr = new Title * [length];
		for (int i = 0; i < length; i++)
		{
			arr[i] = titleList->GetList()->GetData(i);
		}
		sort->QuickSortInList(arr, 0, titleList->GetList()->Length());
		LoadListToTable(arr);

		delete[] arr;
	}
}
void MostBorrowings::LoadListToTable(Title** arr)
{

	ClearOldData(arr);
	int maxLength = titleList->GetList()->Length() > 10 ? 10 : titleList->GetList()->Length();
	for (int i = 0; i < maxLength; i++)
	{
		if (arr[i]->GetCountBorrow() == 0)
		{
			break;
		}
		grid->SetCellValue(i, 0, arr[i]->GetISBN());
		grid->SetCellValue(i, 1, arr[i]->GetBookName());
		grid->SetCellValue(i, 2, arr[i]->GetAuthor());
		grid->SetCellValue(i, 3, arr[i]->GetType());
		string countStr = checkInput->CastIntToString(arr[i]->GetCountBorrow());
		grid->SetCellValue(i, 4,countStr);
		for (int j = 0; j < grid->GetNumberCols(); j++)
		{
			grid->SetCellAlignment(i, j, wxALIGN_CENTER, wxALIGN_CENTER);
		}
	}
}
void MostBorrowings::ClearOldData(Title** arr)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < grid->GetNumberCols(); j++)
		{
			grid->SetCellValue(i, j, wxT(""));
			grid->SetReadOnly(i, j, true);
		}
	}
}
void MostBorrowings::OnExitMenu(wxCommandEvent& WXUNUSED(event))
{
	this->GetParent()->Show();
	this->Hide();
}