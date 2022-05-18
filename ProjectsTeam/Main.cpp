
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"MainMenu.h"
#include"SinglyLinkedList.h"
using namespace std;
using std::cout;
using std::endl;
using namespace DataStructure;
typedef unsigned long long ulong;
class MainApp :public wxApp
{
public:
	virtual bool OnInit();
};
IMPLEMENT_APP(MainApp);
bool MainApp::OnInit()
{
	MainMenu* mainMenu = new MainMenu("MAIN MENU");
	mainMenu->Show();
	return true;
}
