#include<iostream>
#include"SinglyLinkedList.h"
#include"CardReader.h"
#include"BSTree.h"
#include"SaveTextFile.h"
#include"CardReaderMenu.h"
#include"BookTitle.h"
#include"DisplayListTitle.h"
#include"DisplayListBook.h"
#include"AdminMenu.h"
#include"FindInforBook.h"
#include"LendBook.h"
#include"DateTime.h"
using std::cout;
using std::endl;
using namespace DataStructure;
typedef unsigned long long ulong;
class ReaderCardApp :public wxApp
{
public:
	virtual bool OnInit();
};
IMPLEMENT_APP(ReaderCardApp);
bool ReaderCardApp::OnInit()
{
	/*ReaderCard* readerCard = new ReaderCard("THE DOC GIA");
	readerCard->Show();*/
	/*CardReaderMenu* cardReaderMenu = new CardReaderMenu("Card Reader Menu");
	cardReaderMenu->Show(true);*/
	/*BookTitle* title = new BookTitle("DAU SACH");
	title->Show(true);*/
	/*DisplayListTitle* displayTitle = new DisplayListTitle("IN DANH SACH DAU SACH");
	displayTitle->Show(true);*/
	/*DisplayListBook* displayBook = new DisplayListBook("DANH SACH MUC SACH CUA DAU SACH");
	displayBook->Show(true);*/
	//AdminMenu* menu = new AdminMenu("ADMINISTRATOR MENU");
	//menu->Show(true);
	/*FindInforBook* search = new FindInforBook("TIM KIEM THONG TIN DAU SACH");
	search->Show();*/
	LendBook* lendBook = new LendBook("CHO MUON SACH");
	lendBook->Show();
	return true;
}
//class ReaderCardApp :public wxApp
//{
//public:
//	virtual bool OnInit();
//};
//IMPLEMENT_APP(ReaderCardApp);
//bool ReaderCardApp::OnInit()
//{
//	CardReaderMenu* cardReaderMenu = new CardReaderMenu("Card Reader Menu");
//	cardReaderMenu->Show(true);
//	/*BookTitle* title = new BookTitle("DAU SACH");
//	title->Show(true);*/
//	return true;
//}

//int main()
//{

	/*//=====BO TAT CA COMMENT O FILE DateTime.cpp LA SE HIEU RO.======
	DateTime* x = new DateTime();
	string temp = "30/03/2000";
	if (x->CheckDate(temp)) {
		cout << "nhap dung het roi kkk" << endl;
	}
	return 0;
  }*/


//	CardReader* cardReader1 = new CardReader(1, "D", "Hoang", "Nam","KHOA");
//	CardReader* cardReader2 = new CardReader(2, "D", "Tien", "Nam", "KHOA");
//	CardReader* cardReader3 = new CardReader(3, "D", "Nguyen", "Nam", "KHOA");
//	CardReader* cardReader4 = new CardReader(4, "D", "Nhan", "Nam", "KHOA");
//	CardReader* cardReader5 = new CardReader(5, "D", "Duc", "Nam", "KHOA");
//	CardReader* cardReader6 = new CardReader(6, "D", "Chung", "Nam", "KHOA");
//	CardReader* cardReader0 = new CardReader(0, "D", "Khoi", "Nam", "KHOA");
//	CardReader* cardReader10 = new CardReader(10, "D", "Dung", "Nam", "KHOA");
//	BSTree<CardReader> *tree = new BSTree<CardReader>();
//	tree->Add(cardReader3);
//	tree->Add(cardReader2);
//	tree->Add(cardReader1);
//	tree->Add(cardReader4);
//	tree->Add(cardReader5);
//	tree->Add(cardReader6);
//	tree->Add(cardReader0);
//	tree->Add(cardReader10);
//	tree->InOrderTravelsal();
//	cout << endl;
//	tree->Clear();
//	cout << tree->GetNumberNodes() << endl;
//	//cout << tree->RootNode()->data->GetCardCode() << endl;
//	tree->InOrderTravelsal();
//	/*cardReader10->SetLastName("Ngo huu dung");
//	cardReader10->DisplayCardReader();*/
//	//string st;
//	//CardReader** arr = tree->ToArray();
//	//for (int i = 0; i < tree->GetNumberNodes(); i++)
//	//{
//	//	cout << arr[i]->GetCardCode() << endl;
//	//}
//	//SaveTextFile<CardReader>* file = new SaveTextFile<CardReader>("cardReader.txt");
//	//file->WriteToFile(arr, tree->GetNumberNodes());
//	//CardReader** arrRead = new CardReader * [tree->GetNumberNodes()];
//	//file->ReadFile(arrRead);
//	//for (int i = 0; i < tree->GetNumberNodes(); i++)
//	//{
//	//	arrRead[i]->DisplayCardReader();
//	//}
//	//tree->InOrderTravelsal();
//	///*tree->Delete(cardReader6->GetCardCode());
//	//tree->Delete(cardReader5->GetCardCode());
//	//tree->Delete(cardReader1->GetCardCode());
//	//tree->Delete(cardReader2->GetCardCode());
//	//tree->Delete(cardReader4->GetCardCode());*/
//	///*tree->Delete(cardReader3->GetCardCode());
//	//std::cout << tree->RootNode()->data.GetCardCode() << std::endl;
//	//std::cout << tree->Height() << std::endl;*/
//	//tree->InOrderTravelsal();
//	return 0;
//}
//void Swap(CardReader* x, CardReader* y)
//{
//	CardReader temp = *x;
//	*x = *y;
//	*y = temp;
//}
//int partition(CardReader **A, int l, int h)
//{
//	ulong pivot = A[l]->GetCardCode();
//	int i = l, j = h;
//	do
//	{
//		do { i++; if (i == j){ break; } } while (A[i]->GetCardCode() <= pivot);
//		do { j--; } while (A[j]->GetCardCode() > pivot);
//		if (i < j)Swap(A[i], A[j]);
//	} while (i < j);
//	Swap(A[l], A[j]);
//	return j;
//}
//void QuickSort(CardReader**arr, int l, int h)
//{
//	int j = 0;
//	if (l < h)
//	{
//		j = partition(arr, l, h);
//		QuickSort(arr, l, j);
//		QuickSort(arr, j + 1, h);
//	}
//}
//int main()
//{
//	/*CardReader* cardReader1 = new CardReader(1, "D", "Hoang", "Nam","KHOA");
//	CardReader* cardReader2 = new CardReader(2, "D", "Tien", "Nam", "KHOA");
//	CardReader* cardReader3 = new CardReader(3, "D", "Nguyen", "Nam", "KHOA");
//	CardReader* cardReader4 = new CardReader(4, "D", "Nhan", "Nam", "KHOA");
//	CardReader* cardReader5 = new CardReader(5, "D", "Duc", "Nam", "KHOA");
//	CardReader* cardReader6 = new CardReader(6, "D", "Chung", "Nam", "KHOA");
//	CardReader* cardReader0 = new CardReader(0, "D", "Khoi", "Nam", "KHOA");
//	CardReader* cardReader10 = new CardReader(10, "D", "Dung", "Nam", "KHOA");*/
//	CardReader** arr = new CardReader * [8];
//	int index = 0;
//	arr[index++] = new CardReader(5, "D", "Hoang", "Nam", "KHOA");
//	arr[index++] = new CardReader(1, "D", "Tien", "Nam", "KHOA");
//	arr[index++] = new CardReader(3, "D", "Nguyen", "Nam", "KHOA");
//	arr[index++] = new CardReader(4, "D", "Nhan", "Nam", "KHOA");
//	arr[index++] = new CardReader(7, "D", "Duc", "Nam", "KHOA");
//	arr[index++] = new CardReader(6, "D", "Chung", "Nam", "KHOA");
//	arr[index++] = new CardReader(0, "D", "Khoi", "Nam", "KHOA");
//	arr[index++] = new CardReader(2, "D", "Dung", "Nam", "KHOA");
//	//arr[index++] = new CardReader(99999, "D", "Dung", "Nam", "KHOA");
//	//int A[] = { 3,4,5,1,2,2,5,6,1,2,7,11,12,122,55,42 };
//	int length = index;
//	QuickSort(arr, 0, length);
//	for (int i = 0; i < length; i++)
//	{
//		arr[i]->DisplayCardReader();
//	}
//	return 0;
//}
//int random(int minN, int maxN) {
//    return minN + rand() % (maxN + 1 - minN);
//}
//
//int main()
//{
//    srand((int)time(0));
//    int r;
//    for (int i = 0; i < 1000; ++i) {
//        r = random(1, 100);
//    }
//	return 0;
//}
//LinearList<Title>* linearList = new LinearList<Title>(10);
//int CompareTitle(Title* t1, Title* t2)
//{
//	if (t1->GetType() > t2->GetType()) { return 1; }
//	else if (t1->GetType() < t2->GetType()) { return -1; }
//	else
//	{
//		if (t1->GetBookName() > t2->GetBookName()) { return 1; }
//		else if (t1->GetBookName() < t2->GetBookName()) { return -1; }
//		else return 0;
//	}
//}
//void Swap(Title* t1, Title* t2)
//{
//	Title temp = *t1;
//	*t1 = *t2;
//	*t2 = temp;
//}
//int partition(int l, int h)
//{
//	Title* pivot = linearList->GetData(l);
//	int i = l;
//	int j = h;
//	do
//	{
//		do { i++; if (i == j) { break; } } while (CompareTitle(linearList->GetData(i),pivot) < 1);
//		do { j--; } while (CompareTitle(linearList->GetData(j),pivot) == 1);
//		if (i < j) { Swap((linearList->GetData(i)), (linearList->GetData(j))); }
//	} while (i < j);
//	Swap(linearList->GetData(l), linearList->GetData(j));
//	return j;
//}
//void QuickSort(int l, int h)
//{
//	int j = 0;
//	if (l < h)
//	{
//		j = partition(l, h);
//		QuickSort(l, j);
//		QuickSort(j + 1, h);
//	}
//}
//int main()
//{
//	
//	Title* t1 = new Title("AAAA", "A", 123, "ASD", 1999, "bcd");
//	Title* t2 = new Title("AAAA", "x", 123, "ASD", 1999, "ucd");
//	Title* t3 = new Title("AAAA", "t", 123, "ASD", 1999, "acd");
//	Title* t4 = new Title("AAAA", "e", 123, "ASD", 1999, "dcd");
//	Title* t5 = new Title("AAAA", "b", 123, "ASD", 1999, "acd");
//	linearList->AddLast(t1);
//	linearList->AddLast(t2);
//	linearList->AddLast(t3);
//	linearList->AddLast(t4);
//	linearList->AddLast(t5);
//	QuickSort( 0, linearList->Length());
//	for (int i = 0; i < linearList->Length(); i++)
//	{
//		linearList->GetData(i)->Display();
//		cout << endl;
//	}
//	return 0;
//}
//int main()
//{
//	DateTime* date = new DateTime(12,2,2002);
//	date->CastDate("12/02/2002");
//	cout << date->CompareDate("12/03/1999") << endl;
//	string day = "12/06/2001";
//	date->ReverseDate(day);
//	cout << day << endl;
//	return 0;
//}