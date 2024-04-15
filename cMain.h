#pragma once

#include "wx/wx.h"
#include "controlPanel.h"


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

private:
	controlPanel* ctrlPanel;

};

