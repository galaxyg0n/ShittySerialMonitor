#pragma once

#include "wx/wx.h"

// External panels
#include "controlPanel.h"
#include "connectionPanel.h"
#include "carPanel.h"
#include "dataPanel.h"
#include "COM_Communication.h"

// -------------------------

#define ICON "C:\\Users\\mathi\\OneDrive - Syddansk Universitet\\PROG\\CPP\\SerialMonitor\\Release\\Icon.ico"



class cMain : public wxFrame
{
public:
	cMain();
	~cMain();


	// ------- Sizers ------- //
	wxBoxSizer* s_sideSizer = nullptr;
	wxBoxSizer* s_dataSizer = nullptr;
	wxBoxSizer* s_fullSizer = nullptr;


private:
	controlPanel*    ctrlPanel;
	connectionPanel* connPanel;
	carPanel*		 carstatPanel;
	dataPanel*		 rawPanel;


	COM_Communication* comHandle = nullptr;


	wxStaticText* t_RawBytes = nullptr;



};

