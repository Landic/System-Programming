// Volkov_HW_31_System.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Volkov_HW_31_System.h"
#include <time.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_VOLKOVHW31SYSTEM, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VOLKOVHW31SYSTEM));
    srand(time(0));
    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VOLKOVHW31SYSTEM));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_VOLKOVHW31SYSTEM);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int rez;
    int random_number = 0;
    TCHAR str3[50];
    TCHAR str[50] = TEXT( "Волков Данил Андреевич" );
    TCHAR str2[50];
    int count = 0;
    int average = 0;
    int count_windows = 0;
    int rez2;
    short i = 1;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_RBUTTONDOWN:
        rez = MessageBox(hWnd, str, TEXT("Фамилия, имя, отчество"), MB_OKCANCEL | MB_ICONINFORMATION);
        count += wcslen(str);
        count_windows++;
        wcscpy_s(str, L"Учусь");
        if (rez == IDOK) {
            MessageBox(hWnd, str, TEXT("Чем занимается"), MB_OKCANCEL | MB_ICONINFORMATION);
            count += wcslen(str);
            count_windows++;
            wcscpy_s(str, L"Не работаю");
            if (rez == IDOK) {
                MessageBox(hWnd, str, TEXT("Работа"), MB_OKCANCEL | MB_ICONINFORMATION);
                count += wcslen(str);
                count_windows++;
                wcscpy_s(str, L"18 лет");
                if (rez == IDOK) {
                    MessageBox(hWnd, str, TEXT("Возраст"), MB_OKCANCEL | MB_ICONINFORMATION);
                    count += wcslen(str);
                    count_windows++;
                    wcscpy_s(str, L"Украина");
                    if (rez == IDOK) {
                        MessageBox(hWnd, str, TEXT("Страна"), MB_OKCANCEL | MB_ICONINFORMATION);
                        count += _tcslen(str);
                        count_windows++;
                        if (rez == IDOK) {
                            average = count / count_windows;
                            wsprintf(str2, TEXT("Symbols:%d \nAverage symbols%d"), count, average);
                            MessageBox(0, TEXT("Empty"), str2, MB_OKCANCEL | MB_ICONINFORMATION);
                        }
                    }
                }
            }
        }
        else {
            break;
        }
    case WM_LBUTTONDOWN:
        rez2 = MessageBox(hWnd, TEXT("Play?"), TEXT("Computer"), MB_YESNO | MB_ICONQUESTION);
        if (rez2 == IDYES) {
            while (true) {
                while(true){
                    wsprintf(str3, TEXT("Число: %d \nTry: %d"), random_number = rand() % 100, i);
                    rez2 = MessageBox(hWnd, str, TEXT("Computer"), MB_YESNO | MB_ICONQUESTION);
                    if (rez2 == IDNO ) {
                        if (i == 5) {
                            rez = MessageBox(hWnd, TEXT("You won! \nPlay again?"), TEXT("Computer"), MB_YESNO | MB_ICONQUESTION);
                            if (rez2 == IDYES) {
                                i = 1;
                                continue;
                            }
                            else {
                                break;
                            }
                        }
                        i++;
                        continue;
                    }
                    else {
                        rez2 = MessageBox(hWnd, TEXT("Computer won! \nPlay again?"), TEXT("Computer"), MB_YESNO | MB_ICONQUESTION);
                        if (rez2 == IDYES) {
                            i = 1;
                            continue;
                        }
                        else {
                            break;
                        }
                        break;
                    }
                }

                break;
            }
        }

        else {
            break;
        }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
