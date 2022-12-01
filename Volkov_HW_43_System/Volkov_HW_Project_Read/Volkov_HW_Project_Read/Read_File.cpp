#include "Read_File.h"

Read_File* Read_File::ptr = NULL;


Read_File::Read_File(void)
{
	ptr = this;
}

Read_File::~Read_File(void)
{
}

void Read_File::Cls_OnClose(HWND hwnd)
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


DWORD WINAPI Read(LPVOID lp)
{
	ifstream in(TEXT("array.txt"));
	if (!in.is_open())
	{
		MessageAboutError(GetLastError());
		return 1;
	}
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("20F08E42-137C-4D5D-8336-B63C72809F49"));
	DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITY);
	int B[100];
	int sum = 0;
	if (dwAnswer == WAIT_OBJECT_0) {
		for (int i = 0; i < 100; i++)
		{
			in >> B[i];
			sum += B[i];
		}
		in.close();
		ReleaseMutex(hMutex);
		MessageBox(0, TEXT("Поток прочитал информацию из файла"), TEXT("Критическая секция"), MB_OK);
		TCHAR str[30];
		wsprintf(str, TEXT("Сумма чисел равна %d"), sum);
		MessageBox(0, str, TEXT("Критическая секция"), MB_OK);
	}
	return 0;
}

BOOL Read_File::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	CreateThread(NULL, 0, Read, this, 0, NULL);
	return TRUE;
}


BOOL CALLBACK Read_File::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}
	return FALSE;
}