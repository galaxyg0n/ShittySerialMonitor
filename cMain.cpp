#include "cMain.h"


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Shitty Serial Monitor", wxPoint(30, 30), wxSize(1000, 800))
{
	SetBackgroundColour(wxColor(30, 30, 30));
	SetIcon(wxIcon(ICON, wxBITMAP_TYPE_ICO));

	// Create object for COM_Communication
	comHandle = new COM_Communication();

	// ---------- Constructing the panel objects ---------- //
	carstatPanel = new carPanel(this, comHandle);
	ctrlPanel    = new controlPanel(this, comHandle);
	rawPanel     = new dataPanel(this);
	connPanel    = new connectionPanel(this, rawPanel, comHandle);



	t_RawBytes = new wxStaticText(this, wxID_ANY, "Raw output ");
	t_RawBytes->SetForegroundColour(wxColor(245, 247, 250));



	// Side panels sizer
	s_sideSizer = new wxBoxSizer(wxVERTICAL);
	s_sideSizer->Add(connPanel, 1, wxEXPAND | wxBOTTOM, 5);
	s_sideSizer->Add(carstatPanel, 1, wxEXPAND);


	// Data menu sizer
	s_dataSizer = new wxBoxSizer(wxVERTICAL);
	s_dataSizer->Add(ctrlPanel, 1, wxEXPAND | wxBOTTOM, 5);
	s_dataSizer->Add(t_RawBytes, 0, wxEXPAND);
	s_dataSizer->Add(rawPanel, 0, wxEXPAND);


	// Full layout sizer
	s_fullSizer = new wxBoxSizer(wxHORIZONTAL);
	s_fullSizer->Add(s_sideSizer, 0, wxEXPAND | wxTOP | wxLEFT | wxBOTTOM, 5);
	s_fullSizer->Add(s_dataSizer, 0, wxEXPAND | wxTOP | wxLEFT | wxBOTTOM, 5);
	this->SetSizerAndFit(s_fullSizer);
}

cMain::~cMain()
{

}