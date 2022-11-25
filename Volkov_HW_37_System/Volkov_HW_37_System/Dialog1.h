#pragma once
#include "header.h"

class Dialog1
{
public:
	Dialog1(void);
public:
	~Dialog1(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static Dialog1* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hEdit1, hStatic1, hEdit2, hStatic2;
	static float summa;
};
