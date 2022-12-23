#define WM_ICON WM_APP
#define ID_TRAYICON WM_USER
#include "Keyboard_Traines.h"

// СТАТИК
Keyboard_Traines* Keyboard_Traines::ptr = NULL;
int Keyboard_Traines::i = 0;
int Keyboard_Traines::count = 0;
// ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
bool Timer = false;
short minute = 0, sec = 1;
float procent_minus = 0, wrong = 0, procent = 100;
float spm = 0;
int symbols = 0;
short x = 0;
float time1 = 0;
int progress = 0;
int score = 0;
short level = 0;
short start = 0;


Keyboard_Traines::Keyboard_Traines(void)
{
	ptr = this;
	pNID = new NOTIFYICONDATA;
}

Keyboard_Traines::~Keyboard_Traines(void)
{
	delete pNID;
	ReleaseMutex(hMutex);
}

void Keyboard_Traines::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI ThreadTime(LPVOID lp) { // поток для таймера
	HWND hTime = (HWND)lp;
	TCHAR strTime[100], strSec[100];
	while (TRUE) {
		if (Timer == false) { // если false таймер работает
			sec++;
			if (sec == 60) {
				minute++;
				sec = 0;
			}
			if (minute < 11) { // для красивого вывода
				_stprintf_s(strTime, TEXT("0%d:"), minute);
			}
			if (sec >= 10) {
				_stprintf_s(strSec, TEXT("%d"), sec);
			}
			else {
				_stprintf_s(strSec, TEXT("0%d"), sec);
			}
			wcscat_s(strTime, strSec);
			SetWindowText(hTime, strTime);
			Sleep(1000);
		}
	}
	return 0;
}



BOOL Keyboard_Traines::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	for (int j = 0; j < 39; j++) // запись всех кнопок в массив кнопок
	{
		hBut[j] = GetDlgItem(hwnd, IDC_1 + j);
	}
	color = RGB(0, 0, 0);//текущий цвет текста - черный
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfHeight = -15;
	hFont = CreateFontIndirect(&lf);
	for (int j = 0; j < 39; j++) // отправляем шрифт и размер в кнопки
	{
		SendMessage(hBut[j], WM_SETFONT, (WPARAM)hFont, TRUE);
	}
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	SendMessage(hEdit1, WM_SETFONT, (WPARAM)hFont, TRUE); // отправляет шрифт и размер в эдит контроль
	hEditTimer = GetDlgItem(hwnd, IDC_TIMER);
	hEditHit = GetDlgItem(hwnd, IDC_HIT);
	hEditSpm = GetDlgItem(hwnd, IDC_SPM);
	SetWindowText(hEdit1, TEXT("Press Shift to start"));
	hBut1 = GetDlgItem(hwnd, IDSTART);
	hDialog = hwnd;
	hProgress = GetDlgItem(hDialog, IDC_PROGRESS1);
	SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 100)); // Установка интервала для индикатора 
	SendMessage(hProgress, PBM_SETSTEP, 0, 0); // Установка шага приращения  индикатора 
	SendMessage(hProgress, PBM_SETPOS, 0, 0); // Установка текущей позиции индикатора
	SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(0, 191, 255)));
	HINSTANCE hInst = GetModuleHandle(NULL);
	hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	SetClassLong(hDialog, GCL_HICON, LONG(hIcon));
	memset(pNID, 0, sizeof(NOTIFYICONDATA));
	pNID->cbSize = sizeof(NOTIFYICONDATA);
	pNID->hIcon = hIcon;
	pNID->hWnd = hwnd;
	lstrcpy(pNID->szTip, TEXT("Клавиатурный тренажер"));
	pNID->uCallbackMessage = WM_ICON;
	pNID->uFlags = NIF_TIP | NIF_ICON | NIF_MESSAGE | NIF_INFO;
	lstrcpy(pNID->szInfo, TEXT("Приложение для тренировки быстрой печати и слепой печати"));
	lstrcpy(pNID->szInfoTitle, TEXT("Клавиатурный тренажер"));
	pNID->uID = ID_TRAYICON;

	TCHAR guid[] = TEXT("088E7639-EDDE-4B1D-8AEF-50BA5882F50B");
	hMutex = CreateMutex(NULL, FALSE, guid);
	DWORD dwAnswer = WaitForSingleObject(hMutex, 0);
	if (dwAnswer == WAIT_TIMEOUT) {
		MessageBox(hwnd, TEXT("Больше одного раза нельзя запускать!"), TEXT("Клавиатурный тренажер"), MB_OK | MB_ICONINFORMATION);
		EndDialog(hwnd, 0);
	}
	return TRUE;
}

void Keyboard_Traines::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
}

void Keyboard_Traines::Cls_OnCheck(WPARAM wParam, LPARAM lParam)
{
	if (wParam == VK_SHIFT) { // если нажимается Shift то игра начинается
		if (start == 0) {
			hThreadtime = CreateThread(NULL, 1, ThreadTime, hEditTimer, 0, NULL); // создаем поток с таймером
			start++;
		}
		if (level == 0) { // первый уровень
			SetWindowText(hEdit1, TEXT("Hello world"));
		}
		else if (level == 1) { // второй уровень
			SetWindowText(hEdit1, TEXT("Do you agree with this statement"));
		}
		else if (level == 2) { // третий уровень
			SetWindowText(hEdit1, TEXT("The store sells everything from shoelaces to computers"));
		}
		GetWindowText(hEdit1, text, 100); // забираем текст текущий в эдит контроль
		count = 0; // обнуляем размер строки
		procent = 100; // возвращаем процент
		progress = 0; // обнуляем прогресс
		symbols = 0;
		score = 0; // обнуляем очки
		count += wcslen(text); // прибавляем размер строки в глобальную перменную
		SetWindowText(hEditHit, TEXT("100%")); // устанавливаем по дефолту 100 процентов попадание по клавишам если не попадает уменьшается
		SetWindowText(hEditSpm, TEXT("0")); // счетчик по умолчанию ноль
		Timer = false; // таймер фолс 
		x++;
		i = 0; // обнуляем счетчик для строки
		wrong = 0; // обнуляем ошибки
		procent_minus = 0; // обнуляем процент для отнимания
	} 
	// считывание нажатие клавишь
	else if (wParam == 'A') {
		if (text[i] == 'a' || text[i] == 'A') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str1[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str1, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str1); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'B') {
		if (text[i] == 'b' || text[i] == 'B') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'C') {
		if (text[i] == 'c' || text[i] == 'C') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'D') {
		if (text[i] == 'd' || text[i] == 'D') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'E') {
		if (text[i] == 'e' || text[i] == 'E') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'F') {
		if (text[i] == 'f' || text[i] == 'F') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'G') {
		if (text[i] == 'g' || text[i] == 'G') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'H') {
		if (text[i] == 'h' || text[i] == 'H') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'I') {
		if (text[i] == 'i' || text[i] == 'I') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'J') {
		if (text[i] == 'j' || text[i] == 'J') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'K') {
		if (text[i] == 'k' || text[i] == 'K') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'L') {
		if (text[i] == 'l' || text[i] == 'L') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'M') {
		if (text[i] == 'm' || text[i] == 'M') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'N') {
		if (text[i] == 'n' || text[i] == 'N') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'O') {
		if (text[i] == 'o' || text[i] == 'O') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'P') {
		if (text[i] == 'p' || text[i] == 'P') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'Q') {
		if (text[i] == 'q' || text[i] == 'Q') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'R') {
		if (text[i] == 'r' || text[i] == 'R') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'S') {
		if (text[i] == 's' || text[i] == 'S') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'T') {
		if (text[i] == 't' || text[i] == 'T') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'U') {
		if (text[i] == 'u' || text[i] == 'U') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'V') {
		if (text[i] == 'v' || text[i] == 'V') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'W') {
		if (text[i] == 'w' || text[i] == 'W') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'X') {
		if (text[i] == 'x' || text[i] == 'X') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'Y') {
		if (text[i] == 'y' || text[i] == 'Y') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == 'Z') {
		if (text[i] == 'z' || text[i] == 'Z') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam == VK_SPACE) {
		if (text[i] == ' ') {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	else if (wParam >= '0' || wParam <= '9') {
		if (wParam == text[i]) {
			text[i] = ' '; // перезаписывается на пробел
			SetWindowText(hEdit1, text); // отправляется перезаписанная строка в эдит контроль
			i++; // счетчик строки увеличивается
			score++; // очки увеличиваются
			progress = (score * 100) / count; // прогрес увеличивается
			SendMessage(hProgress, PBM_SETPOS, WPARAM(progress), 0); // прогресс передается progress control
			TCHAR str[20]; // создается строка
			symbols++; // увеличивается счетчик
			spm = (symbols * 60) / sec; // умножается на секунды
			_stprintf_s(str, TEXT("%.2f"), spm); // передается в строку
			SetWindowText(hEditSpm, str); // передается в эдит контроль
		}
		else { // если не верно
			wrong++; // увеличивается ошибка на один
			procent_minus = (wrong / 100) * count; // высчитываем процент
			procent -= procent_minus; // от основного процента отнимаем процент полученный выше
			TCHAR str[20]; // создаем строку
			_stprintf_s(str, TEXT("%.2f%%"), procent); // записываем в строку процент
			SetWindowText(hEditHit, str); // передаем в эдит контроль
		}
	}
	if (text[i] == '\0') { // если доходит до нулл терминатора то спрашивает следующий уровень или нет
		TCHAR str[250];
		Timer = true; // таймер останавливает если тру
		sec = 0;
		minute = 0;
		_stprintf_s(str, TEXT("Procent to hit: %.2f%%, SPM: %.2f"), procent, spm);
		MessageBox(0, str, TEXT("Level complete"), MB_OK | MB_ICONINFORMATION);
		SetWindowText(hEdit1, TEXT("Start new level? Press Shift"));
		level++;
		if (level == 3) { // если лвл 3 то тренировка выполнена
			MessageBox(0, TEXT("You completed the traines"), TEXT("End"), MB_OK);
			SetWindowText(hEdit1, TEXT("Again? Press Shift"));
			x = 0;
			level = 0;
		}
	}
	TCHAR buffer[40];
	for (int j = 0; j < 40; j++) // цикл для увеличение кнопки которую надо нажать
	{
		GetWindowText(hBut[j], buffer, 40);
		TCHAR key[37] = { L"1234567890QWERTYUIOPASDFGHJKLZXCVBNM" }; // хранит клавиши
		if (wParam == key[j]) {
			lf.lfHeight = -20;
			hFont = CreateFontIndirect(&lf);//создаём новый шрифт с характеристиками, установленными в диалоге Шрифт
			SendMessage(hBut[j], WM_SETFONT, (WPARAM)hFont, TRUE);//устанавливаем для текстового поля новый шрифт 
		}
		else {
			lf.lfHeight = 12;
			hFont = CreateFontIndirect(&lf);//создаём новый шрифт с характеристиками, установленными в диалоге Шрифт
			SendMessage(hBut[j], WM_SETFONT, (WPARAM)hFont, TRUE);
		}
	}
}

void Keyboard_Traines::Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	if (state == SIZE_MINIMIZED) {
		ShowWindow(hwnd, SW_HIDE);
		Shell_NotifyIcon(NIM_ADD, pNID);
	}
}

void Keyboard_Traines::OnTrayIcon(WPARAM wp, LPARAM lp)
{
	if (lp == WM_LBUTTONDBLCLK) {
		Shell_NotifyIcon(NIM_DELETE, pNID);
		ShowWindow(hDialog, SW_NORMAL);
		SetForegroundWindow(hDialog);
	}
}

BOOL CALLBACK Keyboard_Traines::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_SIZE, ptr->Cls_OnSize);
	}
	if (message == WM_KEYDOWN) {
		ptr->Cls_OnCheck(wParam, lParam);
		return TRUE;
	}
	if (message == WM_ICON) {
		ptr->OnTrayIcon(wParam, lParam);
		return TRUE;
	}
	return FALSE;
}
