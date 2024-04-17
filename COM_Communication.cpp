#include "COM_Communication.h"



COM_Communication::COM_Communication()
{
    status = "Initialized";
}



COM_Communication::~COM_Communication()
{
    /*
    if (!CloseHandle((HANDLE)hSerial))
    {
        throw std::runtime_error("Failed to close COM handle");
    }
    */
}




void COM_Communication::ConnectHandle(LPCWSTR COM_PORT)
{
    hSerial = CreateFileW(
        COM_PORT,
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0
    );

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            SetStatus("Could not connect");
        }
    }
    else
    {
        std::wstring result(COM_PORT);
        SetStatus("Connected to " + result);
    }
}



void COM_Communication::DisconnectHandle()
{
    shouldRun.store(false);
    threadHandler.join();

    if(!CloseHandle((HANDLE)hSerial))
    {
        throw std::runtime_error("Failed to close COM handle");
    }
}


wxString COM_Communication::GetStatus()
{
    return status;
}




void COM_Communication::SetStatus(wxString newStatus)
{
    status = newStatus + "\n";
}





void COM_Communication::ConfigureComPort(DWORD BaudRate)
{
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (hSerial != INVALID_HANDLE_VALUE)
    {
        if (!GetCommState(hSerial, &dcbSerialParams))
        {
            SetStatus("Error getting state");
        }

        dcbSerialParams.BaudRate = BaudRate;
        dcbSerialParams.ByteSize = 8;
        dcbSerialParams.StopBits = ONE5STOPBITS;
        dcbSerialParams.Parity = NOPARITY;

        if (!SetCommState(hSerial, &dcbSerialParams))
        {
            SetStatus("Error setting serial port state");
        }

        SetStatus("Handle worked!");
    }
    else
    {
        SetStatus("Error in handle");
    }
}




void COM_Communication::SetTimeouts()
{
    COMMTIMEOUTS timeouts = { 0 };

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts))
    {
        SetStatus("Error in timeout settings");
    }
    else
    {
        SetStatus("Timeout settings set!");
    }
}







void COM_Communication::WriteComPort(unsigned char& buff)
{
    DWORD dwBytesRead = NULL;
    if (!WriteFile(hSerial, &buff, sizeof(char), &dwBytesRead, NULL))
    {
        SetStatus("Error has occured in WriteComPort");
    }
    else
    {
        SetStatus("Data sent!");
    }
}


void COM_Communication::InitCOMReader(dataPanel* rawPanel)
{
    threadHandler = std::thread(&COM_Communication::ReadIncomingData, this, rawPanel);
}



void COM_Communication::ReadIncomingData(dataPanel* rawPanel)
{
    unsigned char buff = ' ';
    while (shouldRun.load())
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cv.wait(lock, [&] { return !shouldPause; });

        DWORD dwBytesRead = NULL;
        if (!ReadFile(hSerial, &buff, sizeof(char), &dwBytesRead, NULL))
        {
            SetStatus("Error has occured in ReadIncomingData");
        }
        else
        {
            std::ostringstream oss;

            // Format the byte as hexadecimal and save it into the stringstream
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buff);

            // Extract the string from the stringstream
            std::string hexString = oss.str();
            rawPanel->AddTextToBox(hexString + " ");
        }
    }
}


void COM_Communication::pauseReadingData()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        shouldPause.store(true);
        SetStatus("Thread paused");
    }
    cv.notify_all();
}


void COM_Communication::resumeReadingData()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        shouldPause.store(false);
        SetStatus("Thread resumed");
    }
    cv.notify_all();
}