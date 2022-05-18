#pragma once
#include<wx/wx.h>
#include<wx/grid.h>
#include"CheckInput.h"
#include"CardReader.h"
#include"BSTree.h"
#include"SortAlgorithm.h"
#include"OverDueCard.h"
#include"DoublyLinkedList.h"
class OverDueList:public wxFrame
{
private:
	CheckInput* checkInput;
	BSTree<CardReader>* treeCardReader;
	CardReader** arr;
	OverDueCard** arrOverDue;
	DoublyLinkedList<OverDueCard>* overDueCardList;
	SortAlgorithm<OverDueCard>* sort;

	void LoadData();
	void LoadDataToTable();
	//void GetDataOverDue();
	int FindLongestBorrowDay(CardReader* card);
	void FindOverDueListCard();

	void ClearOldDataInTable();

	void OnShow(wxShowEvent& event);
	void OnButtonClicked(wxCommandEvent& event);
	void OnSelectingGrid(wxGridRangeSelectEvent& event);
	void OnSelectedGrid(wxCommandEvent& event);
	void OnSelectedLabelGrid(wxCommandEvent& event);

	int length = 0;
	int lengthOverDue = 0;
	wxGrid* grid;
public:
	OverDueList(const wxString& title);
	~OverDueList()
	{
		delete checkInput;
	}
	void SetCardReader(BSTree<CardReader>* treeCard,CheckInput* checkInput)
	{
		this->treeCardReader = treeCard;
		this->checkInput = checkInput;
	
	}
	
};

