#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>

using namespace std;
struct worker
{
    char FIO[64];
    int hours;
    int rate;
};

void OpenFile(HANDLE& );
void ReadFromFile(HANDLE );
int NumberOfWorkers(HANDLE);

int main()
{
    HANDLE file;
    worker wr;
    OpenFile(file);
    ReadFromFile(file);
    char number[2];
    cout << "We have " << NumberOfWorkers(file) << " workers" << endl
        << "enter number of the worker you want to change: ";
    cin >> number;
    STARTUPINFO StartupInfo;
    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
    StartupInfo.cb = sizeof(StartupInfo);
    PROCESS_INFORMATION ProcInfo;
    ZeroMemory(&ProcInfo, sizeof(ProcInfo));
    char AppName[64] = "Lab2.exe ";
    strcat(AppName, number);
    wchar_t app[64];
    mbstowcs(app, AppName, strlen(AppName) + 1);
    LPWSTR appname = app;
    if (!CreateProcess(NULL, appname, NULL, NULL, FALSE, 0,
        NULL, NULL, &StartupInfo, &ProcInfo)) return 1;
    WaitForSingleObject(ProcInfo.hProcess, INFINITE);
    CloseHandle(ProcInfo.hProcess);
    CloseHandle(ProcInfo.hThread);
    CloseHandle(file);
    return 0;
}

void OpenFile(HANDLE& myFile)
{
    LPCTSTR fn = L"FirstFile.dat";
    myFile = CreateFile(
        fn,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (myFile == INVALID_HANDLE_VALUE)
        cout << "Error" << endl;
    else
        cout << " File is opened" << endl;
}

void ReadFromFile(HANDLE file)
{
    SetFilePointer(file, 0, 0, FILE_BEGIN);
    DWORD n;
    worker wr;

    while (ReadFile(file, &wr, sizeof(wr), &n, NULL) && n != 0) {
        cout << "FIO: " << wr.FIO << endl
            << "Amount of hours: " << wr.hours << endl
            << "Rate: " << wr.rate << endl;
    }
}

int NumberOfWorkers(HANDLE file)
{
    return GetFileSize(file,NULL)/sizeof(worker);
}
