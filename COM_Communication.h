#pragma once
#pragma warning(disable : 4996)

#include <winsock2.h>
#include <Windows.h>
#include <thread>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <condition_variable>

#include "wx/wx.h"
#include "dataPanel.h"

class COM_Communication
{
public:
	COM_Communication();
	~COM_Communication();




public:
	// ---------- COM communication ---------- //
	void ConfigureComPort(DWORD);
	void SetTimeouts();
	void WriteComPort(unsigned char& buff);
	void ConnectHandle(LPCWSTR COM_PORT);
	void DisconnectHandle();
	
	
	// ----------- Thread handling ----------- //
	void InitCOMReader(dataPanel* rawPanel);
	void ReadIncomingData(dataPanel* rawPanel);
	void pauseReadingData();
	void resumeReadingData();


	// Get status of COM_Recv
	wxString GetStatus();
	void     SetStatus(wxString);

	std::thread threadHandler;



private:
	HANDLE   hSerial;
	wxString status;

	std::mutex mutex_;
	std::condition_variable cv;

	std::atomic<bool> shouldPause = { false };
	std::atomic<bool> shouldRun   = { true };

};



/*
 void cMain::ConnButtonClicked(wxCommandEvent& evt)
 {
	 com_recv = new COM_Recv(c_ComSelector->GetStringSelection());
	 t_DataText->AppendText(com_recv->GetStatus());

	 com_recv->ConfigureComPort(wxAtoi(c_BaudSelector->GetStringSelection()));
	 t_DataText->AppendText(com_recv->GetStatus());

	 com_recv->SetTimeouts();
	 t_DataText->AppendText(com_recv->GetStatus());

	 unsigned char BytesArr = ' ';
	 while (disconnCheck)
	 {
		 if (!isSending)
		 {
			 if (com_recv->ReadComPort(BytesArr))
			 {
				 std::ostringstream oss;

				 // Format the byte as hexadecimal and save it into the stringstream
				 oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(BytesArr);

				 // Extract the string from the stringstream
				 std::string hexString = oss.str();
				 t_DataText->AppendText(hexString + " ");
			 }
		 }
		 wxYield();
	 }
	 t_DataText->AppendText("Handle killed\n");
	 disconnCheck = true;

	 evt.Skip();
 }

*/