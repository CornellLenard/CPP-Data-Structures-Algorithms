/*********************************************************************************
 *   @file        Entry.h
 *   @brief       The header file for C++ implemented Entry
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

template<typename K, typename V> class Entry                                   //词条模板类
{
public:
	K key;                                                                     //关键码
	V value;                                                                   //数值
	//构造函数
	Entry(K k = static_cast<K>(0), V v = static_cast<V>(0)) :key(k), value(v) {}
	Entry(const Entry<K, V>& e) :key(e.key), value(e.value) {}
	//比较器与判等器
	bool operator < (const Entry<K, V>& e) { return key < e.key; }
	bool operator > (const Entry<K, V>& e) { return key > e.key; }
	bool operator == (const Entry<K, V>& e) { return key == e.key; }
	bool operator != (const Entry<K, V>& e) { return key != e.key; }
};

