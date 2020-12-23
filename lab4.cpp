#include <iostream>
#include <Windows.h>
using namespace std;

HANDLE hTh01, hTh02, hTh03;
LONG arr[5] = {0,0,0,0,0};
bool cheсk=false;
CRITICAL_SECTION CrS;


void threadOne()
{
    srand(time_t(NULL));
    while (true)
    {
        Sleep(500);
        for (int count = 0; count < 5; count++) {
            LONG k = rand()%301 - 150;
            InterlockedExchange(&arr[count], k);
        }
    
    }

    return;
}

void threadTwo()
{
    while (true)
    {
        Sleep(500);
        if(cheсk)
        {
            for (int count = 0; count < 5; count++)
            {
                EnterCriticalSection(&CrS);
                if(arr[count]>0)
                {
                    InterlockedExchange(&arr[count], 0);
                }
                LeaveCriticalSection(&CrS);
            }
            for (int count = 0; count < 5; count++)
            {
                cout << arr[count] << " ";
            }
            cout << endl;
            cheсk = false;
        }
    }
    return;
}

void threadThree()
{
    while (true)
    {
        Sleep(1000);
        for (int count = 0; count < 5; count++)
        {
            cout << arr[count] << " ";
        }
        cout << endl;
    }
    return;
}

int main()
{
    InitializeCriticalSection(&CrS);
    DWORD IDTh01;
    hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadOne,
        NULL, 0, &IDTh01);
    if (hTh01 == NULL) return GetLastError();
    DWORD IDTh02;
    hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadTwo,
        NULL, 0, &IDTh02);
    if (hTh02 == NULL) return GetLastError();
    DWORD IDTh03;
    hTh03 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadThree,
        NULL, 0, &IDTh03);
    if (hTh03 == NULL) return GetLastError();
    int symbol;
    while(true)
    {
        cout << "If you like change positive numbers, enter 1." << endl
            << "If you like exit from the application, enter 2." << endl;
        cin >> symbol;
        switch(symbol)
        {
            case 1: cheсk = true; break;
            case 2:
            {
                DeleteCriticalSection(&CrS);
                CloseHandle(hTh01);
                CloseHandle(hTh02);
                CloseHandle(hTh03);
                return 0;
            }break;
            default: cout << "enter 1 or 2" << endl;
        }
    }
    
    return 0;
}