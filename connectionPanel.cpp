#include "connectionPanel.h"

wxBEGIN_EVENT_TABLE(connectionPanel, wxPanel)
	EVT_BUTTON(10001, ConnButtonClicked)
	EVT_BUTTON(10002, RefreshButtonClicked)
	EVT_BUTTON(10003, DisconnButtonClicked)
	EVT_BUTTON(10004, ClearRawBox)
	EVT_BUTTON(10005, SaveRawOutput)
wxEND_EVENT_TABLE()



connectionPanel::connectionPanel(wxFrame* parent, dataPanel* new_rawPanel, COM_Communication* new_comHandle) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(250, 350))
{
	this->SetBackgroundColour(wxColor(39, 39, 39));
	rawPanel = new_rawPanel;
	comHandle = new_comHandle;

	t_COMTitle = new wxStaticText(this, wxID_ANY, "Select COM port ");
	t_COMTitle->SetForegroundColour(wxColor(245, 247, 250));
	c_ComSelector = new wxChoice(this, 20001, wxDefaultPosition, wxSize(250, 30));


	t_BaudTitle = new wxStaticText(this, wxID_ANY, "Select Baudrate ");
	t_BaudTitle->SetForegroundColour(wxColor(245, 247, 250));
	c_BaudSelector = new wxChoice(this, 20001, wxDefaultPosition, wxSize(250, 30));


	wxFont connFont = t_COMTitle->GetFont();
	connFont.SetPointSize(connFont.GetPointSize() + 1);
	t_COMTitle->SetFont(connFont);
	t_BaudTitle->SetFont(connFont);


	FillComboBoxes(); // Fill selectors with stuff


	// -------------------------- Buttons  -------------------------- //

	b_BtnConn       = new wxButton(this, 10001, "Connect", wxDefaultPosition, wxSize(250, 30));
	b_BtnRefresh	= new wxButton(this, 10002, "Refresh COM ports", wxDefaultPosition, wxSize(250, 30));
	b_BtnDisconn    = new wxButton(this, 10003, "Disconnect", wxDefaultPosition, wxSize(250, 30));
	b_BtnClearRaw   = new wxButton(this, 10004, "Clear Raw Box", wxDefaultPosition, wxSize(250, 30));
	b_BtnSaveOutput = new wxButton(this, 10005, "Save Raw Output", wxDefaultPosition, wxSize(250, 30));



	// --------------------------- Sizer  --------------------------- //

	s_connectlSizer = new wxBoxSizer(wxVERTICAL);
	s_connectlSizer->Add(t_COMTitle, 0, wxEXPAND | wxALL, 5);
	s_connectlSizer->Add(c_ComSelector, 0, wxEXPAND | wxALL, 5);
	s_connectlSizer->Add(t_BaudTitle, 0, wxEXPAND | wxALL, 5);
	s_connectlSizer->Add(c_BaudSelector, 0, wxEXPAND | wxALL, 5);
	s_connectlSizer->Add(b_BtnConn, 0, wxEXPAND | wxALL, 5);
	s_connectlSizer->Add(b_BtnRefresh, 0, wxEXPAND | wxALL, 5);
	s_connectlSizer->Add(b_BtnDisconn, 0, wxEXPAND | wxALL, 5);
	s_connectlSizer->Add(b_BtnClearRaw, 0, wxEXPAND | wxALL, 5);
	s_connectlSizer->Add(b_BtnSaveOutput, 0, wxEXPAND | wxALL, 5);
	this->SetSizer(s_connectlSizer);


}

connectionPanel::~connectionPanel()
{

}




// -------------------------- Button handlers -------------------------- //

void connectionPanel::ConnButtonClicked(wxCommandEvent& evt)
{
	comHandle->ConnectHandle(c_ComSelector->GetStringSelection());
	rawPanel->AddTextToBox(comHandle->GetStatus());

	comHandle->ConfigureComPort(wxAtoi(c_BaudSelector->GetStringSelection()));
	rawPanel->AddTextToBox(comHandle->GetStatus());

	comHandle->SetTimeouts();
	rawPanel->AddTextToBox(comHandle->GetStatus());

	comHandle->InitCOMReader(rawPanel);

}


void connectionPanel::DisconnButtonClicked(wxCommandEvent& evt)
{
	comHandle->DisconnectHandle();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	rawPanel->AddTextToBox("\nDisconnected!\n");
	evt.Skip();
}



void connectionPanel::ClearRawBox(wxCommandEvent& evt)
{
	rawPanel->ClearTextBox();
}



void connectionPanel::SaveRawOutput(wxCommandEvent& evt)
{
	rawPanel->SaveRawOutput();
}


void connectionPanel::RefreshButtonClicked(wxCommandEvent& evt)
{
	c_ComSelector->Clear();
	c_BaudSelector->Clear();
	FillComboBoxes();
	rawPanel->AddTextToBox("COM ports refreshed!");
}



// ------------------------ Non button functions ------------------------ //

void connectionPanel::FillComboBoxes()
{
	std::list<int> portsList = GetAvailableComPorts();
	for (int item : portsList)
	{
		c_ComSelector->AppendString("COM" + std::to_string(item));
	}
	c_ComSelector->SetSelection(0);

	for (int item : BaudRates)
	{
		c_BaudSelector->AppendString(std::to_string(item));
	}
	c_BaudSelector->SetSelection(6);

}



std::list<int> connectionPanel::GetAvailableComPorts()
{
	wchar_t szDevices[1024];
	std::list<int> portList;

	for (int i = 0; i < 255; i++)
	{
		std::wstring str = L"COM" + std::to_wstring(i);

		DWORD dwRet = QueryDosDeviceW(
			str.c_str(),
			szDevices,
			1024
		);

		if (dwRet != 0)
		{
			portList.push_back(i);
		}
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			std::cout << "ERROR_INSUFFICIENT_BUFFER";
		}
	}
	return portList;
}




std::string connectionPanel::get_desktop_path()
{
	TCHAR desktopPath[MAX_PATH];

	if (SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, 0, desktopPath) != S_OK) {
		//t_DataText->AppendText("Error in getting desktop path");
	}

	std::wstring desktopPathW(desktopPath);
	std::string desktopPathA(desktopPathW.begin(), desktopPathW.end());
	std::string cleanDesktop;
	for (char c : desktopPathA) {
		if (c == '\\') {
			cleanDesktop += "\\\\";
		}
		else {
			cleanDesktop += c;
		}
	}

	return cleanDesktop;
}