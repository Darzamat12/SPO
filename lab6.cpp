#include <iostream>
#include <Windows.h>
#include <time.h>
#include <iomanip>
using namespace std;

HANDLE hSemaphore;
int arr[90],n;


int thread01() 
{
    for (int i = 0; i < n; i++) {
        srand(time(NULL));
        arr[i] = rand() % 501;
        cout << "Befor change: " << arr[i] << endl;
        ReleaseSemaphore(hSemaphore, 1, NULL);
        WaitForSingleObject(hSemaphore, INFINITE);
    }
    return 0;
}

int thread02()
{
    for (int i = 0; i < n; i++) {
        WaitForSingleObject(hSemaphore, INFINITE);
        if (arr[i] % 2 == 0)
        {
            arr[i] = 0;
        }
        cout << "After change: " << arr[i] << endl;
        ReleaseSemaphore(hSemaphore, 1, NULL);
        
    }
    return 0;
}

int main()
{
    cout << "Enter the quantity of numbers in the array" << endl;
    cin >> n;
    hSemaphore = CreateSemaphore(NULL, 0, 1, L"MySemaphore");
    if (hSemaphore == NULL) cout << "Create semaphore failed"
        << GetLastError() << endl;
    HANDLE hTh01 = CreateThread(NULL, 0,
        (LPTHREAD_START_ROUTINE)thread01, NULL, 0, NULL);
    if (hTh01 == NULL) return GetLastError();
    HANDLE hTh02 = CreateThread(NULL, 0,
        (LPTHREAD_START_ROUTINE)thread02, NULL, 0, NULL);
    if (hTh02 == NULL) return GetLastError();

    cin.ignore();
    cin.get();
    CloseHandle(hSemaphore);
    CloseHandle(hTh01);
    CloseHandle(hTh02);
    return 0;
}

