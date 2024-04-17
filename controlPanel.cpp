#include "controlPanel.h"

wxBEGIN_EVENT_TABLE(controlPanel, wxPanel)
	EVT_BUTTON(30001, SendSpeedUp)
	EVT_BUTTON(30002, SendSpeedDown)
	EVT_BUTTON(30003, SendKill)
wxEND_EVENT_TABLE()



controlPanel::controlPanel(wxFrame* parent, COM_Communication* new_comHandle) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(750, 300))
{
	comHandle = new_comHandle;

	b_BtnSpeed = new wxButton(this, 30001, "Speed up", wxDefaultPosition, wxSize(150, 30));
	b_BtnSlow  = new wxButton(this, 30002, "Slow down", wxDefaultPosition, wxSize(150, 30));
	b_BtnKill  = new wxButton(this, 30003, "KILL!", wxDefaultPosition, wxSize(150, 30));

	s_controlSizer = new wxBoxSizer(wxHORIZONTAL);
	s_controlSizer->Add(b_BtnSpeed, 1, wxALL, 5);
	s_controlSizer->Add(b_BtnSlow, 1, wxALL, 5);
	s_controlSizer->Add(b_BtnKill, 1, wxALL, 5);
	this->SetSizer(s_controlSizer);


}

controlPanel::~controlPanel()
{

}


// -------------------------- Button handlers -------------------------- //


void controlPanel::SendSpeedUp(wxCommandEvent& evt)
{

}


void controlPanel::SendSpeedDown(wxCommandEvent& evt)
{

}


void controlPanel::SendKill(wxCommandEvent& evt)
{

}