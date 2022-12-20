#pragma once
#include "Header.h"
class Keyboard_Traines
{
public:
	Keyboard_Traines(void);
public:
	~Keyboard_Traines(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static Keyboard_Traines* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnCheck(WPARAM wParam, LPARAM lParam);
	void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy);
	void OnTrayIcon(WPARAM wp, LPARAM lp);
	HICON hIcon;
	PNOTIFYICONDATA pNID;
	HANDLE hMutex;
	HWND hDialog, hEdit1,hBut1, hEditTimer, hEditHit, hEditSpm, hBut[39], hProgress;
	HANDLE hThreadtime;
	TCHAR text[250];
	static int i;
	static int count;
	COLORREF color;
	LOGFONT lf;
	HFONT hFont;
};

//TCHAR Keyboard_Traines::text[250]{'\0'};

