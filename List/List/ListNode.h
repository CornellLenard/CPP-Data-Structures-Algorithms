/*********************************************************************************
 *   @file        ListNode.h
 *   @brief       The header file for C++ implemented ListNode
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

template<typename T> class ListNode                                            //列表节点模板类
{
public:
	T data;                                                                    //节点所存储的数据
	ListNode<T>* pred;                                                         //指向前驱节点的指针
	ListNode<T>* succ;                                                         //指向后继节点的指针
	//构造函数
	ListNode(T e = static_cast<T>(0), ListNode<T>* p = nullptr, ListNode<T>* s = nullptr);
	//析构函数
	~ListNode();
	//操作接口
	ListNode<T>* insertAsPred(const T& e);                                     //紧靠当前节点之前插入新节点
	ListNode<T>* insertAsSucc(const T& e);                                     //紧靠当前节点之后插入新节点
};

template<typename T> ListNode<T>::ListNode(T e, ListNode<T>* p, ListNode<T>* s) :data(e), pred(p), succ(s) {}

template<typename T> ListNode<T>::~ListNode()
{
	pred = nullptr;
	succ = nullptr;
}

template<typename T> ListNode<T>* ListNode<T>::insertAsPred(const T& e)
{
	ListNode<T>* x = new ListNode<T>(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}

template<typename T> ListNode<T>* ListNode<T>::insertAsSucc(const T& e)
{
	ListNode<T>* x = new ListNode<T>(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}
