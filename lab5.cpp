#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;

HANDLE hTh01, hTh02, hTh03;
LONG arr[10];


void threadOne()
{
    HANDLE hMutex01 = OpenMutex(SYNCHRONIZE, FALSE, L"MyMutex");
    if (hMutex01 == NULL)
        cout << "Open mutex01 failed" << GetLastError() << endl;
    srand(time(NULL));
    for(int i=0; i<3;i++)
    {
        WaitForSingleObject(hMutex01, INFINITE);
        for (int count = 0; count < 10; count++) {
            LONG k = rand() % 301 - 150;
            InterlockedExchange(&arr[count], k);
        }
        Sleep(500);
        cout << "First arr:";
        for (int count = 0; count < 10; count++)
        {
            cout << arr[count] << " ";
        }
        cout << endl;
        ReleaseMutex(hMutex01);
        Sleep(10);
    }
    CloseHandle(hMutex01);
    return;
}

void threadTwo()
{
    Sleep(500);
    HANDLE hMutex02 = OpenMutex(SYNCHRONIZE, FALSE, L"MyMutex");
    if (hMutex02 == NULL)
        cout << "Open mutex02 failed" << GetLastError() << endl;
    for(int i = 0; i<3; i++)
    {
        WaitForSingleObject(hMutex02, INFINITE);
        for (int count = 0; count < 10; count++)
        {
            if (arr[count] < 0)
            {
                InterlockedExchange(&arr[count], arr[count]* arr[count]);
            }
        }
        cout << "Second arr:";
        for (int count = 0; count < 10; count++)
        {
            cout << arr[count] << " ";
        }
        cout << endl;
        Sleep(10);
        ReleaseMutex(hMutex02);
        Sleep(10);
    }
    CloseHandle(hMutex02);
    return;
}


int main()
{
    HANDLE hMutex = CreateMutex(NULL, false, L"MyMutex");
    DWORD IDTh01;
    hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadOne,
        NULL, 0, &IDTh01);
    if (hTh01 == NULL) return GetLastError();
    DWORD IDTh02;
    hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadTwo,
        NULL, 0, &IDTh02);
    if (hTh02 == NULL) return GetLastError();
    cin.get();

    CloseHandle(hMutex);
    CloseHandle(hTh01);
    CloseHandle(hTh02);
    return 0;
}