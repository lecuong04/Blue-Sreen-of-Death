#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    system("SCHTASKS /Delete /TN BSoD /F");
    system("DEL /F /Q C:\\Windows\\System32\\BSoD.exe");
    return 0;
}
