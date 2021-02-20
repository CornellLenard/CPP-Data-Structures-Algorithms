/*********************************************************************************
 *   @file        StackUnderflowException.h
 *   @brief       The header file for C++ implemented StackUnderflowException
 *   @details
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   µÀø°ª‘¿œ ¶£¨”¿‘∂µŒ…Ò£°
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include <exception>
using namespace std;

class StackUnderflowException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "pop() and top() cannot called by an empty Stack !";
	}
};
