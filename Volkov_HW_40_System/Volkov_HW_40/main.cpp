#pragma once
#pragma comment (lib, "Volkov_HW_40_System")
#include <iostream>
#include <Windows.h>

using namespace std;

#include "../Volkov_HW_40_System/Calculator_Library.h"

int main()
{
	int menu = 0, number1 = 0,number2 = 0,summa = 0, choose = 0;
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
			Sum(number1, summa, number2);
			break;
		case 2:
			Min(number1, summa, number2);
			break;
		case 3:
			Mult(number1, summa, number2);
			break;
		case 4:
			Div(number1, summa, number2);
			break;
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