#pragma once

#include "wx/wx.h"
#include "dataPanel.h"
#include "COM_Communication.h"

#include <list>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <shlobj.h> 


class connectionPanel : public wxPanel
{
public:
	connectionPanel(wxFrame* parent, dataPanel* new_rawPanel, COM_Communication* comHandle);
	~connectionPanel();

	void FillComboBoxes();
	std::list<int> GetAvailableComPorts();
	std::string get_desktop_path();

	// ------ Buttons click functions ------ //

	void ConnButtonClicked(wxCommandEvent& evt);
	void RefreshButtonClicked(wxCommandEvent& evt);
	void DisconnButtonClicked(wxCommandEvent& evt);
	void ClearRawBox(wxCommandEvent& evt);
	void SaveRawOutput(wxCommandEvent& evt);




	wxDECLARE_EVENT_TABLE();

private:
	// --------- Sizer --------- //
	wxBoxSizer* s_connectlSizer = nullptr;

	// -------- Buttons -------- //
	wxButton* b_BtnConn		  = nullptr;
	wxButton* b_BtnRefresh    = nullptr;
	wxButton* b_BtnDisconn    = nullptr;
	wxButton* b_BtnClearRaw   = nullptr;
	wxButton* b_BtnSaveOutput = nullptr;

	// -------- Selectors -------- //
	wxChoice* c_ComSelector   = nullptr;
	wxChoice* c_BaudSelector  = nullptr;

	// --------- Titles --------- //
	wxStaticText* t_COMTitle  = nullptr;
	wxStaticText* t_BaudTitle = nullptr;


	dataPanel* rawPanel;



	int BaudRates[20] = { 300, 600, 750, 1200, 2400, 4800, 9600, 19200, 31250, 38400, 57600, 74880, 115200, 230400, 250000, 460800, 500000, 921600, 1000000, 2000000 };
	
	
	bool disconnCheck = true;
	COM_Communication* comHandle;
};

