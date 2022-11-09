#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <vector>
#include <time.h>

using namespace std;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hCombo, hList, hEdit;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    srand(time(0));
   	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}


BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
    vector<int> arr;
    int min = 10, max = 20, min2 = -10, max2 = 10;
    TCHAR str[60];
    TCHAR str2[20];
    switch (message)
    {
    case WM_INITDIALOG:
    {
        hCombo = GetDlgItem(hWnd, IDC_COMBO1);
        hList = GetDlgItem(hWnd, IDC_LIST1);
        hEdit = GetDlgItem(hWnd, IDC_EDIT2);
        SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("Сумма чисел")));
        SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("Произведение чисел")));
        SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("Среднее арифметическое")));

    }
    return TRUE;
    case WM_COMMAND:
    {
        if (wp == IDC_BUTTON1) {
            float summ = 0;
            int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
            int number = min + rand() % (max - min + 1);
            SendMessage(hList, LB_RESETCONTENT, 0, 0);
            while (arr.size() <= number)
            {
                arr.push_back(min2 + rand() % (max2 - min2 + 1));
                if (arr.back() == 0) {
                    arr.pop_back();
                }
            }
            for (vector<int>::iterator it = arr.begin(); it != arr.end(); it++)
            {
                _stprintf_s(str, TEXT("%i"), *it);
                SendMessage(hList, LB_ADDSTRING, 0, LPARAM(str));
            }
            switch (index) {
            case 0:
                summ = 1;
                for (vector<int>::iterator it = arr.begin(); it != arr.end(); it++)
                {
                    summ *= *it;
                }
                break;
            case 1:
                for (vector<int>::iterator it = arr.begin(); it != arr.end(); it++)
                {
                    summ += *it;
                }
                summ /= number;
            case 2:
                for (vector<int>::iterator it = arr.begin(); it != arr.end(); it++)
                {
                    summ += *it;
                }
                break;
            }
            _stprintf_s(str2, TEXT("%.2f"), summ);
            SetWindowText(hEdit, str2);
        }
        else if (wp == IDC_BUTTON2) {
            EndDialog(hWnd, 0);
        }
    }
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}