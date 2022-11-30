#include "CriticalSectionDlg.h"

CriticalSectionDlg* CriticalSectionDlg::ptr = NULL;


CriticalSectionDlg::CriticalSectionDlg(void)
{
	ptr = this;
}

CriticalSectionDlg::~CriticalSectionDlg(void)
{
}

void CriticalSectionDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CriticalSectionDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	return TRUE;
}

DWORD WINAPI Write(LPVOID lp)
{
	srand(time(0));
	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, 0, TEXT("5DE129FD-55A5-4873-BF5A-1C9AC0EF2EC0"));
	if (WaitForSingleObject(hEvent, INFINITY) == WAIT_OBJECT_0) { // ожидает сигнальное состояние
		ofstream out(TEXT("array.txt"));
		if (!out.is_open())
		{
			MessageBox(0, TEXT("Error"), TEXT("Критическая секция"), MB_OK);
			return 1;
		}
		int A[100];
		for (int i = 0; i < 100; i++)
		{
			A[i] = rand() % 50;
			out << A[i] << ' ';
		}
		out.close();
		MessageBox(0, TEXT("Поток записал информацию в файл"), TEXT("Критическая секция"), MB_OK);
	}
	ResetEvent(hEvent);
	return 0;
}

DWORD WINAPI Read(LPVOID lp)
{
	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, 0, TEXT("5DE129FD-55A5-4873-BF5A-1C9AC0EF2EC0"));
	if (WaitForSingleObject(hEvent, INFINITY) == WAIT_OBJECT_0) { // ожидает сигнальное состояние
	ifstream in(TEXT("array.txt"));
	int B[100];
	int sum = 0;
		if (!in.is_open())
		{
			MessageBox(0, TEXT("Error"), TEXT("Error"), MB_OK);
			return 1;
		}
		for (int i = 0; i < 100; i++)
		{
			in >> B[i];
			sum += B[i];
		}
		in.close();
		MessageBox(0, TEXT("Поток прочитал информацию из файла"), TEXT("Критическая секция"), MB_OK);
		TCHAR str[30];
		wsprintf(str, TEXT("Сумма чисел равна %d"), sum);
		MessageBox(0, str, TEXT("Критическая секция"), MB_OK);
	}
	ResetEvent(hEvent);
	return 0;
}


void CriticalSectionDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON1)
	{
		CreateEvent(NULL, TRUE, FALSE, TEXT("5DE129FD-55A5-4873-BF5A-1C9AC0EF2EC0")); // ручной сброс события
		HANDLE hThread = CreateThread(NULL, 0, Write, 0, 0, NULL); 
		CloseHandle(hThread);
		hThread = CreateThread(NULL, 0, Read, 0, 0, NULL);  
		CloseHandle(hThread);
		HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, 0, TEXT("5DE129FD-55A5-4873-BF5A-1C9AC0EF2EC0"));
		SetEvent(hEvent); // переводим событие в сигнальное состояние
	}
}

BOOL CALLBACK CriticalSectionDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}