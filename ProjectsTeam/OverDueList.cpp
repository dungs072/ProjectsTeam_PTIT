#include "OverDueList.h"
OverDueList::OverDueList(const wxString& title) :wxFrame(NULL, -1, title,
	wxDefaultPosition, wxSize(1280, 680))
{
	//backend
	overDueCardList = new DoublyLinkedList<OverDueCard>();
	sort = new SortAlgorithm<OverDueCard>();
	sort->Compare = [](OverDueCard* c1, OverDueCard* c2)
	{
		if (c1->GetNumberDayOverDue() < c2->GetNumberDayOverDue()) { return 1; }
		else if (c1->GetNumberDayOverDue() > c2->GetNumberDayOverDue()) { return -1; }
		return 0;
	};
	checkInput = new CheckInput();
	saveFile = new SaveTextFile<CardReader>("ListReaders.txt");
	wxColour lightYellow, red;
	lightYellow.Set(wxT("#E0EBB7"));
	red.Set(wxT("#F74A4A"));

	//create panel
	wxPanel* mainPanel = new wxPanel(this, -1);

	//create staticText
	wxStaticText* titleGrid = new wxStaticText(mainPanel, -1, wxT("DANH SACH DOC GIA QUA HAN"),
												wxPoint(-1,-1),wxSize(300,30),wxALIGN_CENTER);
	checkInput->SetTextSize(titleGrid, 15);
	
	//create button
	wxButton* exitMenuButton = new wxButton(mainPanel, -1, wxT("EXIT MENU"),
		wxPoint(10, 600), wxSize(100, 30));

	//create boxsizer
	wxBoxSizer* mainHBox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* mainVBox = new wxBoxSizer(wxVERTICAL);


	//create grid
	grid = new wxGrid(mainPanel, -1, wxDefaultPosition, wxSize(1025, 550));
	grid->CreateGrid(30, 6);
	grid->SetColLabelValue(0, wxT("MA DOC GIA"));
	grid->SetColLabelValue(1, wxT("HO DOC GIA"));
	grid->SetColLabelValue(2, wxT("TEN DOC GIA"));
	grid->SetColLabelValue(3, wxT("GIOI TINH"));
	grid->SetColLabelValue(4, wxT("TRANG THAI THE"));
	grid->SetColLabelValue(5, wxT("TONG SO NGAY QUA HAN"));
	for (int i = 0; i < 5; i++)
	{
		if (i == 3)
		{
			grid->SetColSize(i, 100);
			continue;
		}
		if (i == 1)
		{
			grid->SetColSize(i, 200);
			continue;
		}
		grid->SetColSize(i, 150);
	}
	grid->SetColSize(5, 175);
	//grid->SetRowLabelSize(50);
	grid->DisableDragColSize();
	grid->DisableDragRowSize();
	grid->SetSelectionMode(wxGrid::wxGridSelectionModes::wxGridSelectRows);
	
	mainHBox->Add(grid, 0, wxALIGN_CENTER_VERTICAL);
	mainVBox->Add(titleGrid,0, wxBOTTOM|wxTOP|wxALIGN_CENTER_HORIZONTAL,10);
	mainVBox->Add(mainHBox, 0, wxALIGN_CENTER_HORIZONTAL);
	mainPanel->SetSizer(mainVBox);


	//Register event
	grid->Bind(wxEVT_GRID_RANGE_SELECTING, &OverDueList::OnSelectingGrid, this);
	grid->Bind(wxEVT_GRID_SELECT_CELL, &OverDueList::OnSelectedGrid, this);
	grid->Bind(wxEVT_GRID_LABEL_LEFT_CLICK, &OverDueList::OnSelectedLabelGrid, this);
	this->Bind(wxEVT_SHOW, &OverDueList::OnShow, this);
	exitMenuButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &OverDueList::OnButtonClicked, this);
	//Set color
	exitMenuButton->SetBackgroundColour(red);
	titleGrid->SetBackgroundColour(lightYellow);

	Centre();

}
void OverDueList::OnButtonClicked(wxCommandEvent& event)
{
	this->Hide();
	this->GetParent()->Show();
}
void OverDueList::OnShow(wxShowEvent& event)
{
	if (event.IsShown())
	{
		ClearOldDataInTable();
		LoadFile();
		LoadFileToTable();
	}
}
void OverDueList::LoadFile()
{
	overDueCardList->Clear();

	if (arrOverDue != nullptr)
	{
		delete[] arrOverDue;
	}
	length = treeCardReader->GetNumberNodes();
	FindOverDueListCard();
	sort->QuickSort(arrOverDue, 0, lengthOverDue);
	//have to modify here
}
void OverDueList::LoadFileToTable()
{
	if (lengthOverDue == 0)
	{
		return;
	}
	//I just modify length into lengthOverDua here
	if (lengthOverDue > grid->GetNumberRows())
	{
		grid->AppendRows(lengthOverDue - grid->GetNumberRows() + 1);
	}
	for (int i = 0; i < lengthOverDue; i++)
	{
		string codeStr = checkInput->EditCardCode(arrOverDue[i]->GetCardReader()->GetCardCode(), 10);
		grid->SetCellValue(i,0,codeStr);
		grid->SetCellValue(i, 1, arrOverDue[i]->GetCardReader()->GetFirstName());
		grid->SetCellValue(i, 2, arrOverDue[i]->GetCardReader()->GetLastName());
		grid->SetCellValue(i, 3, arrOverDue[i]->GetCardReader()->GetSex());
		grid->SetCellValue(i, 4, arrOverDue[i]->GetCardReader()->GetState());
		grid->SetCellValue(i, 5, checkInput->CastIntToString(arrOverDue[i]->GetNumberDayOverDue()));
		for (int j = 0; j < 6; j++)
		{
			grid->SetCellAlignment(i, j, wxALIGN_CENTER, wxALIGN_CENTER);
			grid->SetReadOnly(i, j);
		}
	}
	for (int i = lengthOverDue; i < grid->GetNumberRows(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			grid->SetReadOnly(i, j);
		}
	}
}
void OverDueList::ClearOldDataInTable()
{
	if (grid->GetNumberRows() > 30)
	{
		for (int i = 30; i < grid->GetNumberRows(); i++)
		{
			grid->DeleteRows(i, 1);
		}
	}
	for (int i = 0; i < grid->GetNumberRows(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			grid->SetCellValue(i, j, wxT(""));
		}
	}
}
int OverDueList::FindLongestBorrowDay(CardReader* card)
{
	int longestDay = -1;
	if (card->GetListBorrowBook() == nullptr) {  return -1; }
	if (card->GetListBorrowBook()->Length() == 0)
	{
		return -1;
	}
	DoublyNode<BorrowBook>* tempBorrowBook = card->GetListBorrowBook()->First();
	DateTime* now = new DateTime();
	while (tempBorrowBook != nullptr)
	{
		if (tempBorrowBook->data.GetStateBorrow() != 1)
		{
			int day = *now - *(tempBorrowBook->data.GetBorrowDate());
			if (day>7&&day > longestDay)
			{
				longestDay = day;
			}
		}
		
		tempBorrowBook = tempBorrowBook->next;
	}
	return longestDay;
}
void OverDueList::FindOverDueListCard()
{
	
	for (int i = 0; i < length; i++)
	{
		int numberDay = FindLongestBorrowDay(arr[i]);
		
		if (numberDay != -1)
		{
			OverDueCard tempOverDueCard(arr[i], numberDay);
			overDueCardList->AddLast(tempOverDueCard);
		}
	}
	lengthOverDue = overDueCardList->Length();
	arrOverDue = overDueCardList->ToArray();
	
}
void OverDueList::OnSelectingGrid(wxGridRangeSelectEvent& WXUNUSED(event))
{
	if (grid->IsSelection())
	{
		grid->ClearSelection();
	}
}
void OverDueList::OnSelectedGrid(wxCommandEvent& WXUNUSED(event))
{
	if (grid->IsSelection())
	{
		grid->ClearSelection();
	}
}
void OverDueList::OnSelectedLabelGrid(wxCommandEvent& WXUNUSED(event))
{
	if (grid->IsSelection())
	{
		grid->ClearSelection();
	}
}
