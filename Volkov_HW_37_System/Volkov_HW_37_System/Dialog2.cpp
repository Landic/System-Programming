#include "Dialog2.h"
#include "Dialog1.h"

Dialog2* Dialog2::ptr = NULL;

Dialog2::Dialog2(void)
{
	ptr = this;
}

Dialog2::Dialog2(LPCTSTR lpStr)
{
	ptr = this;
	//_tcscpy(text, lpStr);
}

Dialog2::~Dialog2(void)
{

}

void Dialog2::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL Dialog2::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit = GetDlgItem(hwnd, IDC_EDIT2);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT3);
	hEdit3 = GetDlgItem(hwnd, IDC_EDIT4);
	hCombo = GetDlgItem(hwnd,IDC_COMBO3);
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("ÀÈ-92")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("ÀÈ-95")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("ÀÈ-98")));
	return TRUE;
}


void Dialog2::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	TCHAR buffer[20];
	TCHAR str[15];
	int i = 0;
	float litr = 0, price = 0;
	if (id == IDC_BUTTON6) {
		int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
		SendMessage(hStatic, LB_RESETCONTENT, 0, 0);
		switch (index)
		{
		case 0:
			SetWindowText(hEdit, TEXT("54.50"));
			petrol = 54.50;
			break;
		case 1:
			SetWindowText(hEdit, TEXT("56.25"));
			petrol = 56.25;
			break;
		case 2:
			SetWindowText(hEdit, TEXT("58.75"));
			petrol = 58.75;
			break;
		default:
			break;
		}
	}
	else if (id == IDC_BUTTON7) {
		LRESULT res = SendDlgItemMessage(hwnd, IDC_RADIO1, BM_GETCHECK, 0, 0);
		if (res == BST_CHECKED) {
			EnableWindow(hEdit3, FALSE);
			EnableWindow(hEdit2, TRUE);
		}
		res = SendDlgItemMessage(hwnd, IDC_RADIO2, BM_GETCHECK, 0, 0);
		if (res == BST_CHECKED) {
			EnableWindow(hEdit2, FALSE);
			EnableWindow(hEdit3, TRUE);
		}
	}
	else if (id == IDC_SUMMA2) {
		LRESULT res = SendDlgItemMessage(hwnd, IDC_RADIO1, BM_GETCHECK, 0, 0);
		if (res == BST_CHECKED) {
			GetWindowText(hEdit2, buffer, 15);
			litr = _wtof(buffer);
			petrol *= litr;
			_stprintf_s(buffer, TEXT("%.2f"), petrol);
			SetWindowText(hEdit3, buffer);
		}
		res = SendDlgItemMessage(hwnd, IDC_RADIO2, BM_GETCHECK, 0, 0);
		if (res == BST_CHECKED) {
				if (petrol == ai_92) {
					GetWindowText(hEdit3, buffer, 15);
					price = _wtof(buffer);
					litr = price / ai_92;
					_stprintf_s(buffer, TEXT("%.2f"), litr);
					SetWindowText(hEdit2, buffer);
				}
				else if (petrol == ai_95) {
					GetWindowText(hEdit3, buffer, 15);
					price = _wtof(buffer);
					litr = price / ai_95;
					_stprintf_s(buffer, TEXT("%.2f"), litr);
					SetWindowText(hEdit2, buffer);
				}
				else if (petrol == ai_98) {
					GetWindowText(hEdit3, buffer, 15);
					price = _wtof(buffer);
					litr = price / ai_98;
					_stprintf_s(buffer, TEXT("%.2f"), litr);
					SetWindowText(hEdit2, buffer);
				}
			}
	}
	else if (id == IDOK2) {
		GetWindowText(hEdit3, str, 15);
		petrol = _wtof(str);
		Dialog1::summa += petrol;
		EndDialog(hwnd, IDOK2);
	}
	else if (id == IDCANCEL2) {
		EndDialog(hwnd, IDCANCEL2);
	}
}

BOOL CALLBACK Dialog2::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}