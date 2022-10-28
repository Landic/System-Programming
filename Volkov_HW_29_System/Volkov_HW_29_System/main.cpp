#include <iostream>
#include <tchar.h>

#define _UNICODE

using namespace std;

void Task1();

void Task2();

void Task3();

void Task5();

void Task6();

void Task7();

void Task8();

void Task9();

int main() {
	//Task1();
	//Task2();
	//Task3();
	//Task5();
	//Task6();
	//Task7();
	//Task8();
	Task9();
}

void Task1()
{
	_TCHAR str[15];
	wcin.getline(str, 15);
	wcout << "wstr - " << str << endl;
	for (int i = 0; i < 15; i++)
	{
		if (str[i] == ' ')
			str[i] = '\t';
	}
	wcout << "wstr tab - " << str << endl;
}

void Task2()
{
	_TCHAR str[15];
	short letter = 0, number=0, symbol=0;
	cout << "Enter... ";
	wcin >> str;
	system("cls");
	wcout << "wstr - " << str << endl;
	for (int i = 0; i < 15; i++)
	{
		if (str[i] >= 48 && str[i] <= 57)
			number++;
		else if (str[i] >= 65 && str[i] <= 90 || str[i] >= 97 && str[i] <= 122)
			letter++;
		else {
			symbol++;
		}
	}
	wcout << "Count number - " << number << endl;
	wcout << "Count letter - " << letter << endl;
	wcout << "Count symbol - " << symbol << endl;
}

void Task3()
{
	_TCHAR str[15];
	cout << "Enter... ";
	wcin.getline(str,15);
	short word = 0;
	system("cls");
	wcout << "wstr - " << str << endl;
	for (int i = 0; i < 15; i++)
	{
		if (str[i - 1] != ' ' && (str[i] == ' ' || str[i + 1] == '\0')) {
			word++;
		}
	}
	cout << "Count word - " << word << endl;
}

void Task5()
{
	setlocale(NULL, "ru");
	_TCHAR str[15];
	cout << "Enter... ";
	wcin.getline(str, 15);
	short vowels = 0;
	system("cls");
	wcout << "wstr - " << str << endl;
	for (short i = 0; i < 15; i++)
	{
		if (str[i] == 192 || str[i] == 211 || str[i] == 206 || str[i] == 221 || str[i] == 223 || str[i] == 222 || str[i] == 200 || str[i] == 197 || str[i] == 224 || str[i] == 243 || str[i] == 238 || str[i] == 251 || str[i] == 253 || str[i] == 255 || str[i] == 254 || str[i] == 232 || str[i] == 229) {
			vowels++;
		}
	}
	cout << "Count vowels - " << vowels << endl;
}

void Task6()
{
	_TCHAR str[15];
	cout << "Enter... ";
	wcin.getline(str, 15);
	short vowels = 0;
	system("cls");
	wcout << "wstr - " << str << endl;
	for (int i = 0; i < 15; i++)
	{
		if (str[i] != str[15 - i - 1])
		{
			cout << str << " not a palindrome" << endl;
		}
		else
		{
			cout << str << " palindrome" << endl;
		}
	}
}

void Task7()
{
	_TCHAR str[15];
	short index = 0;
	cout << "Enter... ";
	wcin.getline(str, 15);
	cout << "Enter index" << endl;
	cout << "Enter... ";
	cin >> index;
	system("cls");
	wcout << "wstr - " << str << endl;
	for (int count = index - 1; count < 15; count++) {
		str[count] = str[count + 1];
	}
	wcout << "wstr - " << str << endl;
}

void Task8()
{
	_TCHAR str[15];
	_TCHAR letter[1];
	cout << "Enter... ";
	wcin >> str;
	cout << "Enter letter" << endl;
	cout << "Enter... ";
	wcin >> letter;
	system("cls");
	_TCHAR old = str;
	while (old)
	{
		if (old != letter) {
		str = old;
		++str[0];
		}
	}
	wcout << "wstr - " << str << endl;
}

void Task9()
{
	_TCHAR str[15];
	_TCHAR letter[2];
	short index = 0;
	int len = 0;
	cout << "Enter... ";
	wcin.getline(str, 15);
	cout << "Enter index" << endl;
	cout << "Enter... ";
	cin >> index;
	cout << "Enter letter" << endl;
	cout << "Enter... ";
	wcin.getline(letter, 15);
	system("cls");
	while (str[len]) {
		len++;
	}
	for (int i = len; i > index - 2; i--)
        str[i + 1] = str[i];
    letter[index - 1] = letter[0];
	wcout << "wstr - " << str << endl;
}
