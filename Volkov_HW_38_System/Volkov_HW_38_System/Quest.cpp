#include "Quest.h"

Quest* Quest::ptr = NULL;

Quest::Quest(void)
{
	ptr = this;
}

Quest::~Quest(void)
{

}

void Quest::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI Thread1(LPVOID lp)
{
	DWORD Priority = GetPriorityClass(GetCurrentProcess());
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
	HWND Progress = (HWND)lp;
	while (true) {
		static time_t t;
		static TCHAR str[100];
		t = time(NULL);	// количество секунд, прошедших с 01.01.1970
		lstrcpy(str, _tctime(&t));	// формирование строки следующего формата:  день мес€ц число часы:минуты:секунды год
		str[lstrlen(str) - 1] = '\0';
		SetWindowText(Progress, str);
		Sleep(1000);
	}
	SetPriorityClass(GetCurrentProcess(), Priority);
	return 0;
}

BOOL Quest::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit = GetDlgItem(hwnd, IDC_EDIT2);
	hBut = GetDlgItem(hwnd, IDC_BUTTON1);
	hProgress = GetDlgItem(hwnd, IDC_PROGRESS1);
	SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 100)); // ”становка интервала дл€ индикатора 
	SendMessage(hProgress, PBM_SETSTEP, 0, 0); // ”становка шага приращени€  индикатора 
	SendMessage(hProgress, PBM_SETPOS, 0, 0); // ”становка текущей позиции индикатора
	SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(0, 214, 120))); // установил цвет
	CreateThread(NULL, 0, Thread1, hEdit, 0, NULL);
	return TRUE;
}

void Quest::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	float procent = 0;
	int question = 3;
	int score = 0;
	if (LOWORD(id) == IDC_BUTTON1) {
		LRESULT res = SendDlgItemMessage(hwnd, IDC_RADIO3, BM_GETCHECK, 0, 0);
		if (res == BST_CHECKED) {
			score++;
		}
		res = SendDlgItemMessage(hwnd, IDC_RADIO6, BM_GETCHECK, 0, 0);
		if (res == BST_CHECKED) {
			score++;
		}
		res = SendDlgItemMessage(hwnd, IDC_RADIO7, BM_GETCHECK, 0, 0);
		if (res == BST_CHECKED) {
			score++;
		}
		procent = (score * 100) / question;
		TCHAR str[20];
		SendMessage(hProgress, PBM_SETPOS, WPARAM(procent), 0);
	}
}

BOOL CALLBACK Quest::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}