
#include <iostream>
#include <Windows.h>
#include <tchar.h>

using namespace std;
typedef int (*FOO_IN_DLL)(int, int*, int);

int main()
{
	HINSTANCE hInstLib = LoadLibrary(TEXT("Volkov_HW_40_System.dll"));
	if (hInstLib == NULL) {
		cout << "Can`t load library MyFirstDll.dll" << endl;
		return 0;
	}
	int menu = 0, number1 = 0, number2 = 0, summa = 1, choose = 0;
	do {
		cout << "1. Summa" << endl;
		cout << "2. Minus" << endl;
		cout << "3. Multi" << endl;
		cout << "4. Divine" << endl;
		cout << "5. Exit" << endl;
		cin >> choose;
		system("cls");
		cout << "Enter number 1" << endl;
		cout << "Enter... ";
		cin >> number1;
		system("cls");
		cout << "Enter number 2" << endl;
		cout << "Enter... ";
		cin >> number2;
		system("cls");
		switch (choose) {
		case 1:
		{
			FOO_IN_DLL DllFoo1 = (FOO_IN_DLL)GetProcAddress(hInstLib, "Sum");
			if (DllFoo1 == NULL) {
				cout << "Error" << endl;
			}
			else {
				DllFoo1(number1, &summa, number2);
			}
			break;
		}
		case 2:
		{
			FOO_IN_DLL DllFoo2 = (FOO_IN_DLL)GetProcAddress(hInstLib, "Min");
			if (DllFoo2 == NULL) {
				cout << "Error" << endl;
			}
			else {
				DllFoo2(number1, &summa, number2);
			}
			break;
		}
		case 3:
		{
			FOO_IN_DLL DllFoo3 = (FOO_IN_DLL)GetProcAddress(hInstLib, "Mult");
			if (DllFoo3 == NULL) {
				cout << "Error" << endl;
			}
			else {
				DllFoo3(number1, &summa, number2);
			}
			break;
		}
		case 4:
		{
			FOO_IN_DLL DllFoo4 = (FOO_IN_DLL)GetProcAddress(hInstLib, "Div");
			if (DllFoo4 == NULL) {
				cout << "Error" << endl;
			}
			else {
				DllFoo4(number1, &summa, number2);
			}
			break;
		}
		case 5:
			cout << "Exit... " << endl;
			Sleep(1000);
			menu = 1;
			system("cls");
			break;
		default:
			cout << "Error!" << endl;
			continue;
			break;
		}
		cout << "Summa = " << summa << endl;
		cout << "Do you wont continue: \n0 - Yes\n1 - No" << endl;
		cin >> menu;
	} while (menu != 1);
}