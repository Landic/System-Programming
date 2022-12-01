#include "Parent.h"

Parent* Parent::ptr = NULL;

Parent::Parent(void)
{
	ptr = this;
}

Parent::~Parent(void)
{

}

void Parent::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}



void Parent::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (IDC_BUTTON1) {
		CreateMutex(0, FALSE, TEXT("20F08E42-137C-4D5D-8336-B63C72809F49"));
		STARTUPINFO st = { sizeof(st) };
		PROCESS_INFORMATION pr;
		TCHAR filename[150];
		wsprintf(filename, TEXT("%s"), TEXT("Volkov_HW_Project_Write.exe"));
		if (!CreateProcess(NULL, filename, NULL, NULL, 0, 0, NULL, NULL, &st, &pr)){
			MessageBox(0, 0, 0, 0);
			return;
		}
		CloseHandle(pr.hThread);
		CloseHandle(pr.hProcess);
		ZeroMemory(&st, sizeof(st));
		st.cb = sizeof(st);
		wsprintf(filename, TEXT("%s"), TEXT("Volkov_HW_Project_Read.exe"));
		if (!CreateProcess(NULL, filename, NULL, NULL, 0, 0, NULL, NULL, &st, &pr)) {
			MessageBox(0, 0, 0, 0);
			return;
		}
		CloseHandle(pr.hThread);
		CloseHandle(pr.hProcess);
	}
}

BOOL CALLBACK Parent::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}