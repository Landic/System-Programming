#pragma once

#ifndef CalculatorDll_API
#define CalculatorDll_API extern "C" __declspec(dllimport)
#endif

bool Div_Zero(int number1, int number2);
CalculatorDll_API void Sum(int number1, int& summ, int number2);
CalculatorDll_API void Min(int number1, int& summ, int number2);
CalculatorDll_API void Mult(int number1, int& summ, int number2);
CalculatorDll_API void Div(int number1, int& summ, int number2);