#define CalculatorDll_API extern "C" __declspec(dllexport)

#include "Calculator_Library.h"
#include <iostream>
using namespace std;

bool Div_Zero(int number1, int number2)
{
		if (number1 == 0 || number2 == 0)
		return true;
	return false;
}

CalculatorDll_API int Sum(int number1, int* summ, int number2)
{
	*summ = number1 + number2;
	return *summ;
}

CalculatorDll_API int Min(int number1, int* summ, int number2)
{
	*summ = number1 - number2;
	return *summ;
}

CalculatorDll_API int Mult(int number1, int* summ, int number2)
{
	*summ = number1 * number2;
	return *summ;
}

CalculatorDll_API int Div(int number1, int* summ, int number2)
{
	if (Div_Zero(number1, number2) == true) {
		cout << "Division by zero is not possible" << endl;
	}
	else {
		*summ = number1 / number2;
		return *summ;
	}
}

