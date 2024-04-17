#include "dataPanel.h"

wxBEGIN_EVENT_TABLE(dataPanel, wxPanel)
// EVT_BUTTON(30001, SendSpeedUp)

wxEND_EVENT_TABLE()



dataPanel::dataPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(550, 200))
{
	this->SetBackgroundColour(wxColor(39, 39, 39));



	// ------------------------ Raw panel layout ------------------------ //


	t_DataText = new wxTextCtrl(this, wxID_ANY, "", wxPoint(0, 0), wxSize(550, 200), wxTE_READONLY | wxTE_MULTILINE);
	t_DataText->SetBackgroundColour(wxColor(59, 59, 59));
	t_DataText->SetForegroundColour(wxColor(245, 247, 250));


	wxFont dataFont = t_DataText->GetFont();
	dataFont.SetPointSize(dataFont.GetPointSize() + 2);
	t_DataText->SetFont(dataFont);

	dataSizer = new wxBoxSizer(wxVERTICAL);
	dataSizer->Add(t_DataText, 1, wxEXPAND | wxALIGN_TOP);
	this->SetSizer(dataSizer);

}

dataPanel::~dataPanel()
{

}


void dataPanel::AddTextToBox(wxString textToAdd)
{
	t_DataText->AppendText(textToAdd);
}


void dataPanel::ClearTextBox()
{
	t_DataText->Clear();
}


void dataPanel::SaveRawOutput()
{
	std::ofstream stream;
	stream.open(get_desktop_path(1) + "\\output.txt");

	if (!stream)
	{
		t_DataText->AppendText("Error saving the file!");
	}
	else
	{
		t_DataText->AppendText("File saved to: " + get_desktop_path(2) + "\\output.txt");
		stream << static_cast<std::string>(t_DataText->GetValue());
	}

	stream.close();
}


std::string dataPanel::get_desktop_path(int slash)
{
	TCHAR desktopPath[MAX_PATH];

	if (SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, 0, desktopPath) != S_OK) {
		t_DataText->AppendText("Error in getting desktop path");
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
	if (slash == 1)
	{
		return cleanDesktop;
	}
	else
	{
		return desktopPathA;
	}
}