/*********************************************************************************
 *   @file        QuadListNode.h
 *   @brief       The header file for C++ implemented QuadListNode
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "Entry.h"

template<typename K, typename V> class QuadListNode                            //��ת��ڵ�ģ����
{
public:
	Entry<K, V> entry;                                                         //�ڵ�洢�Ĵ���
	QuadListNode<K, V>* pred;                                                  //ָ��ǰ���ڵ��ָ��
	QuadListNode<K, V>* succ;                                                  //ָ���̽ڵ��ָ��
	QuadListNode<K, V>* above;                                                 //ָ�����ڽڵ��ָ��
	QuadListNode<K, V>* below;                                                 //ָ�����ڽڵ��ָ��
	//���캯��
	QuadListNode(K k, V v = static_cast<V>(0), QuadListNode<K, V>* p = nullptr, QuadListNode<K, V>* s = nullptr, QuadListNode<K, V>* a = nullptr, QuadListNode<K, V>* b = nullptr);
	//�����½ڵ㣬�Ե�ǰ�ڵ�Ϊǰ������bָ��Ľڵ�Ϊ����
	QuadListNode<K, V>* insertAsSuccAbove(const K& k, const V& v, QuadListNode<K, V>* b = nullptr);
};

template<typename K, typename V> QuadListNode<K, V>::QuadListNode(K k, V v, QuadListNode<K, V>* p, QuadListNode<K, V>* s, QuadListNode<K, V>* a, QuadListNode<K, V>* b) :
	entry(k, v), pred(p), succ(s), above(a), below(b) {}

template<typename K, typename V> QuadListNode<K, V>* QuadListNode<K, V>::insertAsSuccAbove(const K& k, const V& v, QuadListNode<K, V>* b)
{
	QuadListNode<K, V>* x = new QuadListNode<K, V>(k, v, this, succ, nullptr, b);     //�����½ڵ㣬�����ĸ������ָ��
	succ->pred = x;                                                            //ǰ�����ϵ�����
	succ = x;
	if (b != nullptr)                                                          //���·����ϵ�����
		b->above = x;
	return x;                                                                  //����ָ���½ڵ��ָ��
}



