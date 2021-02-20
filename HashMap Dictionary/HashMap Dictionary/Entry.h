/*********************************************************************************
 *   @file        Entry.h
 *   @brief       The header file for C++ implemented Entry
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

template<typename K, typename V> class Entry                                   //����ģ����
{
public:
	K key;                                                                     //�ؼ���
	V value;                                                                   //��ֵ
	//���캯��
	Entry(K k = static_cast<K>(0), V v = static_cast<V>(0)) :key(k), value(v) {}
	Entry(const Entry<K, V>& e) :key(e.key), value(e.value) {}
	//�Ƚ������е���
	bool operator < (const Entry<K, V>& e) { return key < e.key; }
	bool operator > (const Entry<K, V>& e) { return key > e.key; }
	bool operator == (const Entry<K, V>& e) { return key == e.key; }
	bool operator != (const Entry<K, V>& e) { return key != e.key; }
};

