#include <iostream>
#include <windows.h>

using namespace std;

struct worker
{
    char FIO[64];
    int hours;
    int rate;
};

void OpenFile(HANDLE&);
worker ReadFromFile(HANDLE&, int);
void changeFIO(worker&);
void changeHours(worker&);
void changeRate(worker&);
void saveWorker(HANDLE&, int, worker );
void showWorker(worker& wr);
int menu();

int main(int n, char** arg)
{
    int pos;
    if(n>0){
        pos = atoi(arg[1]);
    }
    else { return 1; }
    STARTUPINFO StartupInfo;
    HANDLE myFile;
    worker wr;
    OpenFile(myFile);
    wr = ReadFromFile(myFile, pos);
    while (true) {
        switch (menu())
        {
        case 1: {
            changeFIO(wr);
        } break;
        case 2: changeHours(wr); break;
        case 3: changeRate(wr); break;
        case 4: saveWorker(myFile, pos, wr); break;
        case 5:
        {
            CloseHandle(myFile);
            return 0;
        } break;
        default:
            cout << "Введите от 1 до 4" << endl;
            break;
        }
    }


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
        cout << " File is created" << endl;
}
worker ReadFromFile(HANDLE& file, int pos)
{
    DWORD n;
    worker wr;
    SetFilePointer(file, (pos-1)*sizeof(wr), 0, FILE_BEGIN);
    ReadFile(file, &wr, sizeof(wr), &n, NULL);
    showWorker(wr);
    return wr;
}

void changeFIO(worker& wr)
{
    cout << "Enter new name: ";
    cin.ignore();
    cin.getline(wr.FIO, 64);
}

void changeHours(worker& wr)
{
    cout << "Enter new amount of hours: ";
    cin >> wr.hours;
}

void changeRate(worker& wr) 
{
    cout << "Enter new rate: ";
    cin >> wr.rate;
}

void saveWorker(HANDLE& file, int pos, worker wr)
{
    DWORD l;
    SetFilePointer(file, (pos - 1) * sizeof(wr), 0, FILE_BEGIN);
    WriteFile(file, &wr, sizeof(wr), &l, NULL);
    showWorker(wr);
}

void showWorker(worker& wr)
{
    cout << "FIO: " << wr.FIO << endl
        << "Amount of hours: " << wr.hours << endl
        << "Rate: " << wr.rate << endl;
}

int menu()
{
    int a;
    cout << "1.Change Name" << endl
        << "2.Change amount of hours" << endl
        << "3.Change rate" << endl
        << "4.Save" << endl
        << "5.Exit" << endl;
    cin >> a;
    return a;
}