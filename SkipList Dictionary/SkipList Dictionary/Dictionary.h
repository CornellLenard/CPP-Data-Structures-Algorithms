/*********************************************************************************
 *   @file        Dictionary.h
 *   @brief       The header file for C++ implemented Dictionary Abstract Class
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

template<typename K, typename V> class Dictionary                              //词典抽象模板类
{
public:
	virtual int getSize() const = 0;                                           //当前词条总数
	virtual bool put(K k, V v) = 0;                                            //插入词条(禁止雷同词条时可能失败)，返回插入是否成功
	virtual V* get(K k) = 0;                                                   //读取词条
	virtual bool remove(K k) = 0;                                              //删除词条，返回删除是否成功
};


