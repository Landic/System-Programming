#include <windows.h>
#include <time.h>
#include <tchar.h>
#include "resource.h"
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HBITMAP hBmp[2];
HWND hBut[9];
HWND hPlayAgain, hExit, hStart;
HICON hIcon;
TCHAR szClassWindow[] = TEXT("Каркасное приложение");

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;
	srand(time(0));
	// создаём главное окно приложения на основе модального диалога
	return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("Крестики нолики"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	int hBmp2[9];
	// wp - клик
	// lp - отслеживает мышку
	int zero, min = 1, max =9;
	switch (message)
	{
	case WM_INITDIALOG:
	{
		//	hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		for (int i = 0; i < 9; i++)
		{
			hBut[i] = GetDlgItem(hWnd, IDC_BUTTON1 + i);
		}
		hStart = GetDlgItem(hWnd, IDC_START);
		hExit = GetDlgItem(hWnd, IDC_EXIT);
		hPlayAgain = GetDlgItem(hWnd, IDC_PLAYAGAIN);
		for (int i = 0; i < 2; i++)
		{
			hBmp[i] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1 + i));
		}
		return TRUE;
	}
	case WM_COMMAND:
	{
		if (wp == IDC_START) {
			EnableWindow(hStart, FALSE);
			for (int i = 0; i < 9; i++)
			{
				EnableWindow(hBut[i], TRUE);
			}
		}
		if (wp == IDC_BUTTON1) {
			SendMessage(hBut[0], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[0]));
			hBmp2[0] = 1;
			EnableWindow(hBut[0], FALSE);
			for (int i = 0; i < 9; i++)
			{
				zero = rand() % 9;
				if (IsWindowEnabled(hBut[zero]) == TRUE) {
					SendMessage(hBut[zero], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[1]));
					EnableWindow(hBut[zero], FALSE);
					break;
				}
			}
		}

		else if (wp == IDC_BUTTON2) {
			SendMessage(hBut[1], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[0]));
			EnableWindow(hBut[1], FALSE);
			for (int i = 0; i < 9; i++)
			{
				zero = rand() % 9;
				if (IsWindowEnabled(hBut[zero]) == TRUE) {
					SendMessage(hBut[zero], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[1]));
					EnableWindow(hBut[zero], FALSE);
					break;
				}
			}
		}
		else if (wp == IDC_BUTTON3) {
			SendMessage(hBut[2], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[0]));
			EnableWindow(hBut[2], FALSE);
			for (int i = 0; i < 9; i++)
			{
				zero = rand() % 9;
				if (IsWindowEnabled(hBut[zero]) == TRUE) {
					SendMessage(hBut[zero], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[1]));
					EnableWindow(hBut[zero], FALSE);
					break;
				}
			}
		}
		else if (wp == IDC_BUTTON4) {
			SendMessage(hBut[3], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[0]));
			EnableWindow(hBut[3], FALSE);
			for (int i = 0; i < 9; i++)
			{
				zero = rand() % 9;
				if (IsWindowEnabled(hBut[zero]) == TRUE) {
					SendMessage(hBut[zero], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[1]));
					EnableWindow(hBut[zero], FALSE);
					break;
				}
			}
		}
		else if (wp == IDC_BUTTON5) {
			SendMessage(hBut[4], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[0]));
			hBmp2[4] = 1;
			EnableWindow(hBut[4], FALSE);
			for (int i = 0; i < 9; i++)
			{
				zero = rand() % 9;
				if (IsWindowEnabled(hBut[zero]) == TRUE) {
					SendMessage(hBut[zero], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[1]));
					EnableWindow(hBut[zero], FALSE);
					break;
				}
			}
		}
		else if (wp == IDC_BUTTON6) {
			SendMessage(hBut[5], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[0]));
			EnableWindow(hBut[5], FALSE);
			for (int i = 0; i < 9; i++)
			{
				zero = rand() % 9;
				if (IsWindowEnabled(hBut[zero]) == TRUE) {
					SendMessage(hBut[zero], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[1]));
					EnableWindow(hBut[zero], FALSE);
					break;
				}
			}
		}
		else if (wp == IDC_BUTTON7) {
			SendMessage(hBut[6], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[0]));
			EnableWindow(hBut[6], FALSE);
			for (int i = 0; i < 9; i++)
			{
				zero = rand() % 9;
				if (IsWindowEnabled(hBut[zero]) == TRUE) {
					SendMessage(hBut[zero], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[1]));
					EnableWindow(hBut[zero], FALSE);
					break;
				}
			}
		}
		else if (wp == IDC_BUTTON8) {
			SendMessage(hBut[7], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[0]));
			EnableWindow(hBut[7], FALSE);
			for (int i = 0; i < 9; i++)
			{
				zero = rand() % 9;
				if (IsWindowEnabled(hBut[zero]) == TRUE) {
					SendMessage(hBut[zero], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[1]));
					EnableWindow(hBut[zero], FALSE);
					break;
				}
			}
		}
		else if (wp == IDC_BUTTON9) {
		    SendMessage(hBut[8], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[0]));
			hBmp2[8] = 1;
			EnableWindow(hBut[8], FALSE);
			for (int i = 0; i < 9; i++)
			{
				zero = rand() % 9;
				if (IsWindowEnabled(hBut[zero]) == TRUE) {
					SendMessage(hBut[zero], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[1]));
					EnableWindow(hBut[zero], FALSE);
					break;
				}
			}

		}
		else if (wp == IDC_EXIT) {
			EndDialog(hWnd, 0);
		}
		if (IsWindowEnabled(hBut[0]) == FALSE && IsWindowEnabled(hBut[1]) == FALSE && IsWindowEnabled(hBut[2]) == FALSE && IsWindowEnabled(hBut[3]) == FALSE &&
			IsWindowEnabled(hBut[4]) == FALSE && IsWindowEnabled(hBut[5]) == FALSE && IsWindowEnabled(hBut[6]) == FALSE && IsWindowEnabled(hBut[7]) == FALSE &&
			IsWindowEnabled(hBut[8]) == FALSE) 
		{
			EnableWindow(hPlayAgain, TRUE);
			SetFocus(hPlayAgain);
		}
		for (int i = 0; i < 9; i++)
		{
			if (wp == IDC_PLAYAGAIN) {
				SendMessage(hBut[i], BM_SETIMAGE, NULL, LPARAM(NULL));
				EnableWindow(hPlayAgain, FALSE);
				EnableWindow(hBut[i], TRUE);
			}
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hWnd, 0); // закрываем модальный диалог
		return TRUE;
	}
	return FALSE;
}