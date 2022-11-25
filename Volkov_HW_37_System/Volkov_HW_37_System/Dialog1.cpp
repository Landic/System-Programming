#include "Dialog1.h"
#include "Dialog2.h"
#include "Dialog3.h"

Dialog1* Dialog1::ptr = NULL;

Dialog1::Dialog1(void)
{
	ptr = this;
}

Dialog1::~Dialog1(void)
{

}

void Dialog1::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL Dialog1::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	return TRUE;
}


void Dialog1::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_BUTTON2)
	{
		Dialog2 dialog2;
		INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, Dialog2::DlgProc);
	}
	else if (id == IDC_BUTTON3)
	{
		Dialog3 dialog3;
		INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), hwnd, Dialog3::DlgProc);
	}
	else if (id == IDC_SUMMA) {
		TCHAR str[40];
		_stprintf_s(str, TEXT("%.2f"), summa);
		SetWindowText(hEdit1, str);
	}
	else if (id == IDCLOSE) {
		EndDialog(hwnd, IDCLOSE);
	}
}

BOOL CALLBACK Dialog1::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

float Dialog1::summa = 0;