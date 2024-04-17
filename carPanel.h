#pragma once

#include "wx/wx.h"
#include "COM_Communication.h"

class carPanel : public wxPanel
{
public:
	carPanel(wxFrame* parent, COM_Communication* comHandle);
	~carPanel();





	wxDECLARE_EVENT_TABLE();


private:
	// --------- Car stats --------- //
	wxStaticText* t_Speed     = nullptr;
	wxStaticText* t_Lap       = nullptr;
	wxStaticText* t_DutyCycle = nullptr;
	wxStaticText* t_IsTurning = nullptr;


	wxBoxSizer* carBoxSizer = nullptr;

	COM_Communication* comHandle;
};
