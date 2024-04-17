#pragma once

#include "wx/wx.h"
#include "COM_Communication.h"


class controlPanel : public wxPanel
{
public:
	controlPanel(wxFrame* parent, COM_Communication* comHandle);
	~controlPanel();


	// ------ Buttons click functions ------ //
	void SendSpeedUp(wxCommandEvent& evt);
	void SendSpeedDown(wxCommandEvent& evt);
	void SendKill(wxCommandEvent& evt);


	wxDECLARE_EVENT_TABLE();


private:
	// --------- Sizer --------- //
	wxBoxSizer* s_controlSizer = nullptr;


	// --------- Buttons --------- //
	wxButton* b_BtnSpeed = nullptr;
	wxButton* b_BtnSlow  = nullptr;
	wxButton* b_BtnKill  = nullptr;

	COM_Communication* comHandle;


};

