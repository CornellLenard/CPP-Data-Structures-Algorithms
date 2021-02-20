/*********************************************************************************
 *   @file        VectorIndexOutOfBoundsException.h
 *   @brief       The header file for C++ implemented VectorIndexOutOfBoundsException
 *   @details     An exception class used for Vector
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   µÀø°ª‘¿œ ¶£¨”¿‘∂µŒ…Ò£°
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include <exception>
using namespace std;

class VectorIndexOutOfBoundsException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "The given index is out of bounds !";
	}
};

