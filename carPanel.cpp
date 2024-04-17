#include "carPanel.h"

wxBEGIN_EVENT_TABLE(carPanel, wxPanel)
	// EVT_BUTTON(30001, SendSpeedUp)

wxEND_EVENT_TABLE()



carPanel::carPanel(wxFrame* parent, COM_Communication* new_comHandle) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(250, 300))
{
	this->SetBackgroundColour(wxColor(39, 39, 39));

	comHandle = new_comHandle;

	// ----------------- Text  ----------------- //
	t_Speed = new wxStaticText(this, wxID_ANY, "Current speed: ");
	t_Speed->SetForegroundColour(wxColor(245, 247, 250));

	t_Lap = new wxStaticText(this, wxID_ANY, "Current lap: ");
	t_Lap->SetForegroundColour(wxColor(245, 247, 250));

	t_DutyCycle = new wxStaticText(this, wxID_ANY, "Duty cycle: ");
	t_DutyCycle->SetForegroundColour(wxColor(245, 247, 250));

	t_IsTurning = new wxStaticText(this, wxID_ANY, "Turning: ");
	t_IsTurning->SetForegroundColour(wxColor(245, 247, 250));


	// ----------------- Font ----------------- //
	wxFont speedFont = t_Speed->GetFont();
	speedFont.SetPointSize(speedFont.GetPointSize() + 2);
	t_Speed->SetFont(speedFont);
	t_Lap->SetFont(speedFont);
	t_DutyCycle->SetFont(speedFont);
	t_IsTurning->SetFont(speedFont);


	// -------- Sizer for car stats panel -------- //
	carBoxSizer = new wxBoxSizer(wxVERTICAL);
	carBoxSizer->Add(t_Speed, 0, wxEXPAND | wxALL, 5);
	carBoxSizer->Add(t_Lap, 0, wxEXPAND | wxALL, 5);
	carBoxSizer->Add(t_DutyCycle, 0, wxEXPAND | wxALL, 5);
	carBoxSizer->Add(t_IsTurning, 0, wxEXPAND | wxALL, 5);
	this->SetSizer(carBoxSizer);


}

carPanel::~carPanel()
{

}