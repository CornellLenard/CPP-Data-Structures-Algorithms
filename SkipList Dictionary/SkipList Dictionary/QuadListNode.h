/*********************************************************************************
 *   @file        QuadListNode.h
 *   @brief       The header file for C++ implemented QuadListNode
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "Entry.h"

template<typename K, typename V> class QuadListNode                            //跳转表节点模板类
{
public:
	Entry<K, V> entry;                                                         //节点存储的词条
	QuadListNode<K, V>* pred;                                                  //指向前驱节点的指针
	QuadListNode<K, V>* succ;                                                  //指向后继节点的指针
	QuadListNode<K, V>* above;                                                 //指向上邻节点的指针
	QuadListNode<K, V>* below;                                                 //指向下邻节点的指针
	//构造函数
	QuadListNode(K k, V v = static_cast<V>(0), QuadListNode<K, V>* p = nullptr, QuadListNode<K, V>* s = nullptr, QuadListNode<K, V>* a = nullptr, QuadListNode<K, V>* b = nullptr);
	//插入新节点，以当前节点为前驱，以b指向的节点为下邻
	QuadListNode<K, V>* insertAsSuccAbove(const K& k, const V& v, QuadListNode<K, V>* b = nullptr);
};

template<typename K, typename V> QuadListNode<K, V>::QuadListNode(K k, V v, QuadListNode<K, V>* p, QuadListNode<K, V>* s, QuadListNode<K, V>* a, QuadListNode<K, V>* b) :
	entry(k, v), pred(p), succ(s), above(a), below(b) {}

template<typename K, typename V> QuadListNode<K, V>* QuadListNode<K, V>::insertAsSuccAbove(const K& k, const V& v, QuadListNode<K, V>* b)
{
	QuadListNode<K, V>* x = new QuadListNode<K, V>(k, v, this, succ, nullptr, b);     //创建新节点，设置四个方向的指针
	succ->pred = x;                                                            //前后方向上的连接
	succ = x;
	if (b != nullptr)                                                          //上下方向上的连接
		b->above = x;
	return x;                                                                  //返回指向新节点的指针
}



