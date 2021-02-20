/*********************************************************************************
 *   @file        BitMap.h
 *   @brief       The header file for C++ implemented BitMap
 *   @details     Utilizes each bit to represent each element
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

class BitMap                                                                   //位图类
{
private:
	char* M;                                                                   //指向BitMap所存放的空间的指针
	int N;                                                                     //M所指向的char的个数
protected:
	void init(int n);                                                          //初始化BitMap
public:
	BitMap(int n = 8);                                                         //构造函数
	~BitMap();                                                                 //析构函数
	void set(int k);                                                           //设置第k位
	void clear(int k);                                                         //清除第k位
	bool test(int k);                                                          //验证第k位是否已设置
	void expand(int k);                                                        //扩容算法
};

