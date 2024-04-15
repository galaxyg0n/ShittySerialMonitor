#include "controlPanel.h"

wxBEGIN_EVENT_TABLE(controlPanel, wxPanel)
	EVT_BUTTON(30001, SendSpeedUp)
	EVT_BUTTON(30002, SendSpeedDown)
	EVT_BUTTON(30003, SendKill)
wxEND_EVENT_TABLE()



controlPanel::controlPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(250, 300))
{

	b_BtnSpeed = new wxButton(p_ControlPanel, 30001, "Speed up", wxDefaultPosition, wxSize(150, 30));
	b_BtnSlow  = new wxButton(p_ControlPanel, 30002, "Slow down", wxDefaultPosition, wxSize(150, 30));
	b_BtnKill  = new wxButton(p_ControlPanel, 30003, "KILL!", wxDefaultPosition, wxSize(150, 30));


}

controlPanel::~controlPanel()
{

}


void controlPanel::SendSpeedUp(wxCommandEvent& evt)
{

}


void controlPanel::SendSpeedDown(wxCommandEvent& evt)
{

}


void controlPanel::SendKill(wxCommandEvent& evt)
{

}