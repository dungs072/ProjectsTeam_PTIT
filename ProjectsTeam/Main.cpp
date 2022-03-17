#include"ReaderCard.h"
#include"SinglyLinkedList.h"
#include"CardReader.h"
#include"BSTree.h"
#include<iostream>
using std::cout;
using std::endl;
using namespace DataStructure;
using namespace Library;
//class ReaderCardApp :public wxApp
//{
//public:
//	virtual bool OnInit();
//};
//IMPLEMENT_APP(ReaderCardApp);
//bool ReaderCardApp::OnInit()
//{
//	ReaderCard* rl = new ReaderCard("Danh sach the doc gia");
//	rl->Show(true);
//	return true;
//}
int main()
{
	CardReader* cardReader1 = new CardReader(1, "D", "N", "Nam","KHOA");
	CardReader* cardReader2 = new CardReader(2, "D", "N", "Nam", "KHOA");
	CardReader* cardReader3 = new CardReader(3, "D", "N", "Nam", "KHOA");
	CardReader* cardReader4 = new CardReader(4, "D", "N", "Nam", "KHOA");
	CardReader* cardReader5 = new CardReader(5, "D", "N", "Nam", "KHOA");
	CardReader* cardReader6 = new CardReader(6, "D", "N", "Nam", "KHOA");
	CardReader* cardReader0 = new CardReader(0, "D", "N", "Nam", "KHOA");
	CardReader* cardReader10 = new CardReader(10, "D", "N", "Nam", "KHOA");
	BSTree<CardReader> *tree = new BSTree<CardReader>();
	tree->Add(cardReader3);
	tree->Add(cardReader2);
	tree->Add(cardReader1);
	tree->Add(cardReader4);
	tree->Add(cardReader5);
	tree->Add(cardReader6);
	tree->Add(cardReader0);
	tree->Add(cardReader10);
	CardReader** arr = tree->ToArray();
	for (int i = 0; i < tree->GetNumberNodes(); i++)
	{
		cout << arr[i]->GetCardCode() << endl;
	}
	//tree->InOrderTravelsal();
	///*tree->Delete(cardReader6->GetCardCode());
	//tree->Delete(cardReader5->GetCardCode());
	//tree->Delete(cardReader1->GetCardCode());
	//tree->Delete(cardReader2->GetCardCode());
	//tree->Delete(cardReader4->GetCardCode());*/
	///*tree->Delete(cardReader3->GetCardCode());
	//std::cout << tree->RootNode()->data.GetCardCode() << std::endl;
	//std::cout << tree->Height() << std::endl;*/
	//tree->InOrderTravelsal();
	return 0;
}