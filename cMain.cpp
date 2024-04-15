#include "cMain.h"


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Shitty Serial Monitor", wxPoint(30, 30), wxSize(1000, 800))
{
	ctrlPanel = new controlPanel(this);

}

cMain::~cMain()
{

}