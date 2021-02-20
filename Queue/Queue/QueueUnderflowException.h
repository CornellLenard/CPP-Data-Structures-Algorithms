/*********************************************************************************
 *   @file        QueueUnderflowException.h
 *   @brief       The header file for C++ implemented QueueUnderflowException
 *   @details
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   µÀø°ª‘¿œ ¶£¨”¿‘∂µŒ…Ò£°
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include <exception>
using namespace std;

class QueueUnderflowException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "dequeue() and getFront() cannot called by an empty Queue !";
	}
};
