#include <windows.h>
#include <windowsX.h>
#include <ctime>
#include <tchar.h>
#include <commctrl.h>
#include "resource.h"

#pragma comment(lib,"comctl32")

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hEdit1, hEdit2, hProgress, hDialog, hSpin1, hEdit3,hEdit4, hSpin2, hStatus;
BOOL bShowStatusBar;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	short score = 0;
	double procent = 0;
	int question = 16;
	bShowStatusBar = TRUE;
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case  WM_INITDIALOG:
	{
		hEdit3 = GetDlgItem(hWnd, IDC_EDIT1);
		hEdit1 = GetDlgItem(hWnd, IDC_EDIT2);
		hEdit2 = GetDlgItem(hWnd, IDC_EDIT3);
		hEdit4 = GetDlgItem(hWnd, IDC_EDIT4);
		hDialog = hWnd;
		hProgress = GetDlgItem(hDialog, IDC_PROGRESS2);
		SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 100)); // Установка интервала для индикатора 
		SendMessage(hProgress, PBM_SETSTEP, 0, 0); // Установка шага приращения  индикатора 
		SendMessage(hProgress, PBM_SETPOS, 0, 0); // Установка текущей позиции индикатора
		SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(0, 214, 120))); // установил цвет
		hSpin1 = GetDlgItem(hDialog, IDC_SPIN1);
		SendMessage(hSpin1, UDM_SETRANGE32, 0, 2022);
		UDACCEL pAcceleration[3] = { {1,1}, {2,10}, {3,50} };
		SendMessage(hSpin1, UDM_SETACCEL, 3, LPARAM(pAcceleration));
		SendMessage(hSpin1, UDM_SETBUDDY, WPARAM(hEdit3), 0);
		hSpin2 = GetDlgItem(hDialog, IDC_SPIN2);
		SendMessage(hSpin2, UDM_SETRANGE32, 0, 2022);
		UDACCEL pAcceleration2[3] = { {1,1}, {3,10}, {3,50} };
		SendMessage(hSpin2, UDM_SETACCEL, 3, LPARAM(pAcceleration2));
		SendMessage(hSpin2, UDM_SETBUDDY, WPARAM(hEdit4), 0);
		hStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE | CCS_BOTTOM | SBARS_TOOLTIPS | SBARS_SIZEGRIP, 0, hDialog, WM_USER);
		HMENU hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
		SetMenu(hDialog, hMenu);
		return TRUE;
	}
	case WM_COMMAND:
		TCHAR Answer1[] = TEXT("Киев");
		TCHAR Answer2[] = TEXT("Берлин");
		TCHAR Answer3[] = TEXT("1 939");
		TCHAR Answer4[] = TEXT("1 991");
		TCHAR str1[10];
		TCHAR str2[10];
		TCHAR str3[10];
		TCHAR str4[10];
		if (LOWORD(wp) == ID_MENU_EXIT) {
			EndDialog(hWnd, 0);
		}
		if (wp == IDOK) {
			LRESULT res = SendDlgItemMessage(hWnd, IDC_RADIO1, BM_GETCHECK, 0, 0);;
			if (res == BST_CHECKED) {
				score++;
			}
			res = SendDlgItemMessage(hWnd, IDC_RADIO5, BM_GETCHECK, 0, 0);
			if (res == BST_CHECKED) {
				score++;
			}
			res = SendDlgItemMessage(hWnd, IDC_RADIO7, BM_GETCHECK, 0, 0);
			if (res == BST_CHECKED) {
				score++;
			}
			res = SendDlgItemMessage(hWnd, IDC_RADIO10, BM_GETCHECK, 0, 0);
			if (res == BST_CHECKED) {
				score++;
			}
			res = SendDlgItemMessage(hWnd, IDC_RADIO13, BM_GETCHECK, 0, 0);
			if (res == BST_CHECKED) {
				score++;
			}
			res = SendDlgItemMessage(hWnd, IDC_RADIO17, BM_GETCHECK, 0, 0);
			if (res == BST_CHECKED) {
				score++;
			}
			res = SendDlgItemMessage(hWnd, IDC_RADIO20, BM_GETCHECK, 0, 0);
			if (res == BST_CHECKED) {
				score++;
			}
			res = SendDlgItemMessage(hWnd, IDC_RADIO22, BM_GETCHECK, 0, 0);
			if (res == BST_CHECKED) {
				score++;
			}
			res = SendDlgItemMessage(hWnd, IDC_CHECK1, BM_GETCHECK, 0, 0);
			if (res == BST_CHECKED) {
				score++;
			}
			res = SendDlgItemMessage(hWnd, IDC_CHECK3, BM_GETCHECK, 0, 0);
			if (res == BST_CHECKED) {
				score++;
			}
			res = SendDlgItemMessage(hWnd, IDC_CHECK5, BM_GETCHECK, 0, 0);
			if (res == BST_CHECKED) {
				score++;
			}
			res = SendDlgItemMessage(hWnd, IDC_CHECK6, BM_GETCHECK, 0, 0);
			if (res == BST_CHECKED) {
				score++;
			}
			GetWindowText(hEdit1, str1, 10);
			GetWindowText(hEdit2, str2, 10);
			if (!lstrcmpi(Answer1, str1)) {
				score++;
			}
			if (!lstrcmpi(Answer2, str2)) {
				score++;
			}
			GetWindowText(hEdit3, str3, 6);
			GetWindowText(hEdit4, str4, 6);		
			if (!lstrcmpi(Answer3, str3)) {
				score++;
			}
			if (!lstrcmp(Answer4, str4)) {
				score++;
			}
		    procent = (score * 100) / question;
			TCHAR str[20];
			SendMessage(hProgress, PBM_SETPOS, WPARAM(procent), 0);
			_stprintf_s(str, TEXT("Результаты: %.2f"), procent);
			MessageBox(hWnd,str,TEXT("Результаты"),MB_OK);
		}
		return TRUE;
	}
	return FALSE;
}