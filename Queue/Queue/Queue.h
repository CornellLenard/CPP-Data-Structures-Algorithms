/*********************************************************************************
 *   @file        Queue.h
 *   @brief       The header file for C++ implemented Queue
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "QueueNode.h"
#include "QueueUnderflowException.h"
using namespace std;

template<typename T> class Queue                                               //队列模板类
{
protected:
	int size;                                                                  //队列规模
	QueueNode<T>* header;                                                      //指向队列头哨兵节点的指针
	QueueNode<T>* trailer;                                                     //指向队列尾哨兵节点的指针
	void init();                                                               //队列创建时初始化
	int clear();                                                               //释放队列所有节点所占的内存空间
	void copyNodes(QueueNode<T>* p, int n);                                    //复制队列中自位置p起的n项
	QueueNode<T>* getFirst() const;                                            //获取指向首节点的指针
	QueueNode<T>* getLast() const;                                             //获取指向末节点的指针
	QueueNode<T>* insertAsFirst(const T& e);                                   //将e当作首节点插入，返回插入后指向新节点的指针
	QueueNode<T>* insertAsLast(const T& e);                                    //将e当作末节点插入，返回插入后指向新节点的指针
	QueueNode<T>* insertAfter(QueueNode<T>* p, const T& e);                    //将e当作p的后继插入，返回插入后指向新节点的指针
	QueueNode<T>* insertBefore(QueueNode<T>* p, const T& e);                   //将e当作p的前驱插入，返回插入后指向新节点的指针
	T remove(QueueNode<T>* p);                                                 //删除合法位置p处的节点，返回被删除节点存储的数据
public:
	//构造函数
	Queue();                                                                   //默认构造函数
	Queue(const Queue<T>& q);                                                  //整体复制队列q
	Queue(QueueNode<T>* p, int n);                                             //复制队列中自位置p起的n项
	//析构函数
	~Queue();                                                                  //释放队列所占的内存空间，包括头尾哨兵节点
	//只读访问接口
	int getSize() const;                                                       //获取队列规模
	bool isEmpty() const;                                                      //判断队列是否为空
	//可写访问接口
	void enqueue(const T& e);                                                  //入队
	T dequeue();                                                               //出队
	T& getFront();                                                             //引用队首元素
};

template<typename T> void Queue<T>::init()
{
	header = new QueueNode<T>();
	trailer = new QueueNode<T>();
	header->succ = trailer;
	header->pred = nullptr;
	trailer->succ = nullptr;
	trailer->pred = header;
	size = 0;
}

template<typename T> int Queue<T>::clear()
{
	int old_size = getSize();
	while (getSize() > 0)
		remove(header->succ);
	return old_size;
}

template<typename T> void Queue<T>::copyNodes(QueueNode<T>* p, int n)
{
	init();
	while (n > 0)
	{
		insertAsLast(p->data);
		p = p->succ;
		n--;
	}
}

template<typename T> QueueNode<T>* Queue<T>::getFirst() const
{
	return header->succ;
}

template<typename T> QueueNode<T>* Queue<T>::getLast() const
{
	return trailer->pred;
}

template<typename T> QueueNode<T>* Queue<T>::insertAsFirst(const T& e)         //各种插入函数都是调用对应节点的对应插入函数
{
	size++;
	return header->insertAsSucc(e);
}

template<typename T> QueueNode<T>* Queue<T>::insertAsLast(const T& e)
{
	size++;
	return trailer->insertAsPred(e);
}

template<typename T> QueueNode<T>* Queue<T>::insertAfter(QueueNode<T>* p, const T& e)
{
	size++;
	return p->insertAsSucc(e);
}

template<typename T> QueueNode<T>* Queue<T>::insertBefore(QueueNode<T>* p, const T& e)
{
	size++;
	return p->insertAsPred(e);
}

template<typename T> T Queue<T>::remove(QueueNode<T>* p)
{
	T res = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	p = nullptr;
	size--;
	return res;
}

template<typename T> Queue<T>::Queue()
{
	init();
}

template<typename T> Queue<T>::Queue(QueueNode<T>* p, int n)
{
	copyNodes(p, n);
}

template<typename T> Queue<T>::Queue(const Queue<T>& q)
{
	copyNodes((q.header)->succ, q.size);
}

template<typename T> Queue<T>::~Queue()
{
	clear();
	delete header;
	header = nullptr;
	delete trailer;
	trailer = nullptr;
}

template<typename T> int Queue<T>::getSize() const
{
	return size;
}

template<typename T> bool Queue<T>::isEmpty() const
{
	return !static_cast<bool>(getSize());
}

template<typename T> void Queue<T>::enqueue(const T& e)                        //入队直接调用insertAsLast()即可
{
	insertAsLast(e);
}

template<typename T> T Queue<T>::dequeue()                                     //出队需要先判断此时队列是否为空，为空则抛出异常
{
	if (getSize() == 0)
		throw QueueUnderflowException();
	return remove(header->succ);
}

template<typename T> T& Queue<T>::getFront()                                   //getFront()需要先判断此时队列是否为空，为空则抛出异常
{
	if (getSize() == 0)
		throw QueueUnderflowException();
	return header->succ->data;
}
