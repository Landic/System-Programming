#include "Dialog3.h"
#include "Dialog1.h"

Dialog3* Dialog3::ptr = NULL;

Dialog3::Dialog3(void)
{
	ptr = this;
}

Dialog3::Dialog3(LPCTSTR lpStr)
{
	ptr = this;
	//_tcscpy(text, lpStr);
}

Dialog3::~Dialog3(void)
{

}

void Dialog3::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL Dialog3::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT5);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT6);
	hEdit3 = GetDlgItem(hwnd, IDC_EDIT7);
	hEdit4 = GetDlgItem(hwnd, IDC_EDIT8);
	hEdit5 = GetDlgItem(hwnd, IDC_EDIT9);
	hEdit6 = GetDlgItem(hwnd, IDC_EDIT10);
	hEdit7 = GetDlgItem(hwnd, IDC_EDIT11);
	hEdit8 = GetDlgItem(hwnd, IDC_EDIT12);
	SetWindowText(hEdit1, TEXT("23.50"));
	SetWindowText(hEdit2, TEXT("32.25"));
	SetWindowText(hEdit3, TEXT("19.75"));
	SetWindowText(hEdit4, TEXT("14.25"));
	return TRUE;
}


void Dialog3::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	double arr[4] = {0,0,0,0};
	double arr_price[4] = {0,0,0,0};
	TCHAR buffer1[20], buffer2[20], buffer3[20], buffer4[20];
	LRESULT res = SendDlgItemMessage(hwnd, IDC_CHECK1, BM_GETCHECK, 0, 0);
	if (res == BST_CHECKED) {
		EnableWindow(hEdit5, TRUE);
		GetWindowText(hEdit5, buffer1, 20);
		arr[0] = _wtof(buffer1);
		GetWindowText(hEdit1, buffer1, 20);
		arr_price[0] = _wtof(buffer1);
		arr[0] *= arr_price[0];
	}
	res = SendDlgItemMessage(hwnd, IDC_CHECK2, BM_GETCHECK, 0, 0);
	if (res == BST_CHECKED) {
		EnableWindow(hEdit6, TRUE);
		GetWindowText(hEdit6, buffer2, 20);
		arr[1] = _wtof(buffer2);
		GetWindowText(hEdit2, buffer2, 20);
		arr_price[1] = _wtof(buffer2);
		arr[1] *= arr_price[1];
	}
	res = SendDlgItemMessage(hwnd, IDC_CHECK3, BM_GETCHECK, 0, 0);
	if (res == BST_CHECKED) {
		EnableWindow(hEdit7, TRUE);
		GetWindowText(hEdit7, buffer3, 20);
		arr[2] = _wtof(buffer3);
		GetWindowText(hEdit3, buffer3, 20);
		arr_price[2] = _wtof(buffer3);
		arr[2] *= arr_price[2];
	}
	res = SendDlgItemMessage(hwnd, IDC_CHECK4, BM_GETCHECK, 0, 0);
	if (res == BST_CHECKED) {
		EnableWindow(hEdit8, TRUE);
		GetWindowText(hEdit8, buffer4, 20);
		arr[3] = _wtof(buffer4);
		GetWindowText(hEdit4, buffer4, 20);
		arr_price[3] = _wtof(buffer4);
		arr[3] *= arr_price[3];
	}
	if (id == IDOK1) {
		for (int i = 0; i < 4; i++)
		{
			Dialog1::summa += arr[i];
		}
		EndDialog(hwnd, IDCANCEL1);
	}
	else if (id == IDCANCEL1) {
		EndDialog(hwnd, IDCANCEL1);
	}
}

BOOL CALLBACK Dialog3::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}