/*********************************************************************************
 *   @file        Fibonacci.h
 *   @brief       The header file for C++ implemented Fibonacci
 *   @details     Provides a sequence of Fibonacci Series
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

class Fibonacci                                                                //斐波那契数列类，生成一个一定长度的斐波那契数列
{
private:
	int size;                                                                  //斐波那契数列的元素个数
	int* fib;                                                                  //存储数列的内存空间
	int position;                                                              //索引，指向数列当前元素位置
public:
	Fibonacci(int s = 2);                                                      //构造函数，接收数列长度并按此构造数列
	~Fibonacci();                                                              //释放数列所占内存空间
	int get() const;                                                           //获取数列当前元素
	void prev();                                                               //索引前移
};
