#include "Write.h"

Write_File* Write_File::ptr = NULL;


Write_File::Write_File(void)
{
	ptr = this;
}

Write_File::~Write_File(void)
{
}

void Write_File::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

void MessageAboutError(DWORD dwError)
{
	LPVOID lpMsgBuf = NULL;
	TCHAR szBuf[300];

	BOOL fOK = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	if (lpMsgBuf != NULL)
	{
		wsprintf(szBuf, TEXT("Ошибка %d: %s"), dwError, lpMsgBuf);
		MessageBox(0, szBuf, TEXT("Сообщение об ошибке"), MB_OK | MB_ICONSTOP);
		LocalFree(lpMsgBuf);
	}
}


DWORD WINAPI Write(LPVOID lp)
{
	srand(time(0));
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("20F08E42-137C-4D5D-8336-B63C72809F49"));
	DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);
	if (dwAnswer == WAIT_OBJECT_0) {
		ofstream out(TEXT("array.txt"));
		if (!out.is_open())
		{
			MessageAboutError(GetLastError());
			return 1;
		}
		int A[100];
		for (int i = 0; i < 100; i++)
		{
			A[i] = rand() % 50;
			out << A[i] << ' ';
		}
		out.close();
		ReleaseMutex(hMutex);
		MessageBox(0, TEXT("Поток записал информацию в файл"), TEXT("Запись"), MB_OK);
	}
	return 0;
}

BOOL Write_File::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	CreateThread(NULL, 0, Write, this, 0, NULL);
	return TRUE;
}



BOOL CALLBACK Write_File::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}
	return FALSE;
}