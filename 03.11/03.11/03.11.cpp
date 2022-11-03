#include "framework.h"
#include "03.11.h"

#define MAX_LOADSTRING 100


HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY0311, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0311));

    MSG msg;


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



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
    wcex.hCursor        = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = 0;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

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


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HCURSOR hcurb = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR2));
    HCURSOR hcurW = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1));
    RECT rect;
    TCHAR str[50];
    GetClientRect(hWnd, &rect);
    int x = rect.top + 10;
    int xs = rect.bottom - 10;
    int y = rect.left + 10;
    int ys = rect.right - 10;
    switch (message)
    {
    case WM_CREATE:
    {
        SetCursor(hcurW);
    }
    break;
    case WM_LBUTTONDOWN:
        if (LOWORD(lParam) > x && LOWORD(lParam) < xs && HIWORD(lParam) > y && HIWORD(lParam) < ys) {
            wsprintf(str, TEXT("Нажатие внутри прямоугольника x = %d  y = %d"), LOWORD(lParam), HIWORD(lParam));
            SetWindowText(hWnd, str);
        }
        else if (LOWORD(lParam) > x && LOWORD(lParam) < xs && HIWORD(lParam) == y || LOWORD(lParam) > x && LOWORD(lParam) < xs && HIWORD(lParam) == ys || HIWORD(lParam) > x && HIWORD(lParam) < xs && LOWORD(lParam) == y || HIWORD(lParam) > x && HIWORD(lParam) < xs && LOWORD(lParam) == ys) {
            wsprintf(str, TEXT("Нажатие на контур прямоугольника x = %d y = %d"), LOWORD(lParam), HIWORD(lParam));
            SetWindowText(hWnd, str);
        }
        else {
            wsprintf(str, TEXT("Нажатие вне прямоугольника x = %d y = %d"), LOWORD(lParam), HIWORD(lParam));
            SetWindowText(hWnd, str);
        }
    case WM_KEYDOWN:
        if (wParam == VK_RETURN) {
            SetCursor(hcurb);
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