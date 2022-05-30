
#include<iostream>
#include"MainMenu.h"
using namespace std;
using std::cout;
using std::endl;
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
