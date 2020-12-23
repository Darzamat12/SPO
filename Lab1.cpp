#include <iostream>
#include <Windows.h>

using namespace std;


struct worker
{
    char FIO[64];
    int hours;
    int rate;
};

void OpenFile(HANDLE&);
void OpenFile2(HANDLE&);
void WriteToFile(HANDLE, worker);
void SetWorker(worker&);
void ReadFromFile(HANDLE);
int menu();
void WorkerFilter(HANDLE, HANDLE);
void ReadAnswer(HANDLE);

int main()
{
    setlocale(LC_ALL, "Russian");
    HANDLE file;
    worker wr;
    OpenFile(file);
    HANDLE endFile;
    OpenFile2(endFile);
    while (true) {
        switch (menu())
        {
        case 1: {
            SetWorker(wr);
            WriteToFile(file, wr);
        } break;
        case 2: ReadFromFile(file); break;
        case 3: WorkerFilter(file, endFile); break;
        case 4: ReadAnswer(endFile); break;
        case 5:
        {
            CloseHandle(file);
            CloseHandle(endFile);
            return(0);
        } break;
        default:
            cout << "Введите от 1 до 4" << endl;
            break;
        }
    }
    
    cin.get();
    return 0;
}

void OpenFile(HANDLE &myFile)
{
    LPCTSTR fn = L"FirstFile.dat";
        myFile = CreateFile(
        fn, 
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
        if (myFile == INVALID_HANDLE_VALUE)
            cout << "Error" << endl;
    else
        cout << " File is created" << endl;
}
void OpenFile2(HANDLE& myFile)
{
    LPCTSTR fn = L"EndFile.dat";
    myFile = CreateFile(
        fn,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (myFile == INVALID_HANDLE_VALUE)
        cout << "Error" << endl;
    else
        cout << " File is created" << endl;
}


void WriteToFile(HANDLE file, worker wr)
{

    DWORD n;
    WriteFile(file, &wr, sizeof(wr), &n, NULL);

}

void SetWorker(worker &wr)
{
    cout << "Введите имя файла: ";
    cin.ignore();
    cin.getline(wr.FIO, 64);
    cout << "Введите кол-во отработаных часов: ";
    cin  >> wr.hours;
    cout << "Введите тариф:";
    cin >> wr.rate;
}

void ReadFromFile(HANDLE file)
{
    SetFilePointer(file, 0, 0, FILE_BEGIN);
    DWORD n;
    worker wr;
    
    while (ReadFile(file, &wr, sizeof(wr), &n, NULL) && n != 0){
        cout << "ФИО: " << wr.FIO << endl
            << "Кол-во отработаных часов: " << wr.hours << endl
            << "Тариф" << wr.rate << endl;
    }
}

int menu()
{
    int a;
    cout << "1.Добавить рабочего" << endl
        << "2.Прочитать файл" << endl
        << "3.Отобрать рабочих" << endl
        << "4.Вывести ответ" << endl
        << "5.Выход" << endl;
    cin >> a;
    return a;
}

void WorkerFilter(HANDLE file, HANDLE endFile)
{
    SetFilePointer(file, 0, 0, FILE_BEGIN);
    DWORD n, l;
    worker wr;
    double salary = 0;
    while (ReadFile(file, &wr, sizeof(wr), &n, NULL) && n != 0) 
    {
        if (wr.hours > 144) 
        {
            salary = (144 * wr.rate + (wr.hours - 144) * wr.rate * 2)*0.82;
            WriteFile(endFile, &salary, sizeof(salary), &l, NULL);
        } 
        else
        {
            salary = wr.hours * wr.rate * 0.82;
            WriteFile(endFile, &salary, sizeof(salary), &l, NULL);
        }
    }
}

void ReadAnswer(HANDLE file)
{
    SetFilePointer(file, 0, 0, FILE_BEGIN);
    DWORD n;
    double salary;

    while (ReadFile(file, &salary, sizeof(salary), &n, NULL) && n != 0) {
        cout << "Зарплата: " << salary << endl;
    }
}
