/*********************************************************************************
 *   @file        Fibonacci Implementation.cpp
 *   @brief       The C++ implementation of Fibonacci class
 *   @details     
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   µÀø°ª‘¿œ ¶£¨”¿‘∂µŒ…Ò£°
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#include "Fibonacci.h"

Fibonacci::Fibonacci(int s)
{
	(s <= 2) ? size = 2 : size = s;
	fib = new int[size];
	fib[0] = 0;
	fib[1] = 1;
	for (int i = 2; i < size; i++)
		fib[i] = fib[i - 1] + fib[i - 2];
	position = size - 1;
}

Fibonacci::~Fibonacci()
{
	delete[] fib;
	fib = nullptr;
}

int Fibonacci::get() const
{
	return fib[position];
}

void Fibonacci::prev()
{
	if (position == 0)
		return;
	else
		position--;
}