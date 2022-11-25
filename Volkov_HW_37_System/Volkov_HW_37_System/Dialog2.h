#pragma once
#include "header.h"

class Dialog2
{
public:
	Dialog2(void);
	Dialog2(LPCTSTR lpStr);
public:
	~Dialog2(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static Dialog2* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hEdit, hStatic, hCombo, hEdit2, hEdit3;
	float petrol;
	float ai_92 = 54.50, ai_95 = 56.25, ai_98 = 58.75;
};
