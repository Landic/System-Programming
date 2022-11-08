#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hEdit1, hEdit2;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	short score = 0;
	double procent = 0;
	int question = 14;
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case  WM_INITDIALOG:
		hEdit1 = GetDlgItem(hWnd, IDC_EDIT2);
		hEdit2 = GetDlgItem(hWnd, IDC_EDIT3);
		return TRUE;

	case WM_COMMAND:
		TCHAR Answer1[] = TEXT("Киев");
		TCHAR Answer2[] = TEXT("Берлин");
		TCHAR str1[10];
		TCHAR str2[10];
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
		    procent = (score * 100) / question;
			TCHAR str[20];
			_stprintf_s(str, TEXT("Результаты: %.2f"), procent);
			MessageBox(hWnd,str,TEXT("Результаты"),MB_OK);
		}
		return TRUE;
	}
	return FALSE;
}