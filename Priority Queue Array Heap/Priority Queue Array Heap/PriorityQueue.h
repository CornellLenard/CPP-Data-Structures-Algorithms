/*********************************************************************************
 *   @file        PriorityQueue.h
 *   @brief       The header file for C++ implemented Priority Queue Abstract Class
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

template<typename T> class PriorityQueue                                       //优先级队列抽象模板类
{
public:
	virtual void insert(T e) = 0;                                              //按照比较器确定的优先级次序插入词条
	virtual T getMax() = 0;                                                    //取出优先级最高的词条
	virtual T deleteMax() = 0;                                                 //删除优先级最高的词条，并将其内容返回
};
