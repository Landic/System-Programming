#pragma once

#ifndef CalculatorDll_API
#define CalculatorDll_API extern "C" __declspec(dllimport)
#endif

bool Div_Zero(int number1, int number2);
CalculatorDll_API int Sum(int number1, int* summ, int number2);
CalculatorDll_API int Min(int number1, int* summ, int number2);
CalculatorDll_API int Mult(int number1, int* summ, int number2);
CalculatorDll_API int Div(int number1, int* summ, int number2);