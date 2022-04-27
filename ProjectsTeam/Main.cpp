#include<iostream>
#include"AdminMenu.h"
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
	
	AdminMenu* menu = new AdminMenu("ADMINISTRATOR MENU");
	menu->Show(true);
	return true;
}
