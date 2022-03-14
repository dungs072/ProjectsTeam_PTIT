#include"ReaderCard.h"
using namespace Library;
class ReaderCardApp :public wxApp
{
public:
	virtual bool OnInit();
};
IMPLEMENT_APP(ReaderCardApp);
bool ReaderCardApp::OnInit()
{
	ReaderCard* rl = new ReaderCard("Danh sach the doc gia");
	rl->Show(true);
	return true;
}
