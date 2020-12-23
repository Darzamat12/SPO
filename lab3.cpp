#include <iostream>
#include <windows.h>

using namespace std;

int n = 0, m = 0, k = 0, exitNumber;
HANDLE hTh01, hTh02, hTh03;

void threadOne()
{
    while (true) { 
        n++; 
        Sleep(50);
        if (exitNumber == 1) {
            ExitThread(0);
        }
    }
    
    return;
}

void threadTwo()
{
    while (true) { 
        m++; 
        Sleep(200); 
        if (exitNumber == 2) {
        ExitThread(0);
        }
    }
    
    return;
}

void threadThree()
{
    while (true) { 
        k++;
        Sleep(4);
        if (exitNumber == 3) {
            ExitThread(0);
        }
    }
    
    return;
}

int main()
{
    setlocale(LC_ALL, "Russian");
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
    char symbol;
    int check = 0;
    while (true)
    {
        cout << "d для удаления потока имеющего самое малое значение счетчика." << endl
            << "q для закрытия потока и завершения программы." << endl;
        cin >> symbol;
        switch (symbol) {
        case 'd': {
            cout << "Первый поток досчитал до: " << n << " второй до: " << m << " третий до: " << k << endl;
            
            if(check == 0){
            if (n <= m and n <= k)
            {
                exitNumber = 1;
                cout << "Удален поток 1." << endl;
                check = 1;
            }
            else if (m <= n and m <= k)
            {
                exitNumber = 2;
                cout << "Удален поток 2." << endl;
                check = 2;
            }
            else if (k <= n and k <= m)
            {
                exitNumber = 3;
                cout << "Удален поток 3." << endl;
                check = 3;
            }
            }else
            {
                cout << "Минимальный поток уже не изменить, и это " << check << " поток." << endl;
            }

        } break;
        case 'q': 
        {
            return 0; break;
        }
        default: cout << "Введите d или q" << endl;
        }
    }

    return 0;
}