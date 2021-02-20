/*********************************************************************************
 *   @file        QueueNode.h
 *   @brief       The header file for C++ implemented QueueNode
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

template<typename T> class QueueNode                                           //队列节点模板类
{
public:
	T data;                                                                    //节点所存储的数据
	QueueNode<T>* pred;                                                        //指向前驱节点的指针
	QueueNode<T>* succ;                                                        //指向后继节点的指针
	//构造函数
	QueueNode(T e = static_cast<T>(0), QueueNode<T>* p = nullptr, QueueNode<T>* s = nullptr);
	//析构函数
	~QueueNode();
	//操作接口
	QueueNode<T>* insertAsPred(const T& e);                                    //紧靠当前节点之前插入新节点
	QueueNode<T>* insertAsSucc(const T& e);                                    //紧靠当前节点之后插入新节点
};

template<typename T> QueueNode<T>::QueueNode(T e, QueueNode<T>* p, QueueNode<T>* s) :data(e), pred(p), succ(s) {}

template<typename T> QueueNode<T>::~QueueNode()
{
	pred = nullptr;
	succ = nullptr;
}

template<typename T> QueueNode<T>* QueueNode<T>::insertAsPred(const T& e)
{
	QueueNode<T>* x = new QueueNode<T>(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}

template<typename T> QueueNode<T>* QueueNode<T>::insertAsSucc(const T& e)
{
	QueueNode<T>* x = new QueueNode<T>(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}
