#pragma once
#pragma warning(disable : 4996)

#include <winsock2.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <shlobj.h> 

#include "wx/wx.h"


class dataPanel : public wxPanel
{
public:
	dataPanel(wxFrame* parent);
	~dataPanel();


	void AddTextToBox(wxString textToAdd);
	std::string get_desktop_path(int slash);
	void ClearTextBox();
	void SaveRawOutput();


	wxDECLARE_EVENT_TABLE();


private:
	// ------- Raw layout ------- //
	wxPanel* p_RawPanel    = nullptr;
	wxTextCtrl* t_DataText = nullptr;
	wxBoxSizer* dataSizer  = nullptr;


};

