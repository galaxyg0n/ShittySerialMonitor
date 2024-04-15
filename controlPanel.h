#pragma once

#include "wx/wx.h"
#include "cMain.h"

class controlPanel : public wxPanel
{
public:
	controlPanel(wxFrame* parent);
	~controlPanel();


	void SendSpeedUp(wxCommandEvent& evt);
	void SendSpeedDown(wxCommandEvent& evt);
	void SendKill(wxCommandEvent& evt);


	wxDECLARE_EVENT_TABLE();


private:
	wxPanel* p_ControlPanel = nullptr;

	wxButton* b_BtnSpeed = nullptr;
	wxButton* b_BtnSlow  = nullptr;
	wxButton* b_BtnKill  = nullptr;




};

