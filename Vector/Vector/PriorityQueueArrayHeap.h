/*********************************************************************************
 *   @file        PriorityQueueArrayHeap.h
 *   @brief       The header file for C++ implemented Priority Queue
 *                based on Array Heap - so called Complete Binary Heap
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "PriorityQueue.h"
#include "VectorForHeap.h"
#include <iostream>
using namespace std;

template<typename T> class PriorityQueueArrayHeap : public PriorityQueue<T>, public VectorForHeap<T>      //基于完全二叉堆的优先级队列模板类
{
protected:
	bool inHeap(Rank i);                                                       //判断位置i是否合法
	Rank parent(Rank i);                                                       //返回i节点的母亲节点的位置索引
	Rank lastInternal();                                                       //返回最后一个内部节点，也就是末节点的母亲节点的位置索引
	Rank lChild(Rank i);                                                       //返回i节点的左孩子的位置索引
	Rank rChild(Rank i);                                                       //返回i节点的右孩子的位置索引
	bool hasParent(Rank i);                                                    //判断i节点是否有母亲节点
	bool hasLChild(Rank i);                                                    //判断i节点是否有左孩子
	bool hasRChild(Rank i);                                                    //判断i节点是否有右孩子
	Rank bigger(Rank i, Rank j);                                               //返回i节点和j节点其中大者的位置索引
	Rank getMaxOfThree(Rank i);                                                //返回i节点和其两个孩子节点这三者中的最大者的位置索引
	Rank percolateDown(Rank i);                                                //下滤算法，返回下滤完成后i的最终位置索引
	Rank percolateUp(Rank i);                                                  //上滤算法，返回上滤完成后i的最终位置索引
	void heapify();                                                            //Floyd建堆算法
public:
	PriorityQueueArrayHeap();                                                  //默认构造函数
	PriorityQueueArrayHeap(T* A, Rank n);                                      //构造函数
	void insert(T e);                                                          //按照比较器确定的优先级次序，插入词条
	T getMax();                                                                //返回优先级最高的词条
	T deleteMax();                                                             //删除优先级最高的词条，并将其内容返回
};

template<typename T> bool PriorityQueueArrayHeap<T>::inHeap(Rank i)
{
	return (i >= 0) && (i < this->getSize());
}

template<typename T> Rank PriorityQueueArrayHeap<T>::parent(Rank i)
{
	return (i - 1) / 2;
}

template<typename T> Rank PriorityQueueArrayHeap<T>::lastInternal()
{
	return parent(this->getSize() - 1);
}

template<typename T> Rank PriorityQueueArrayHeap<T>::lChild(Rank i)
{
	return 2 * i + 1;
}

template<typename T> Rank PriorityQueueArrayHeap<T>::rChild(Rank i)
{
	return 2 * i + 2;
}

template<typename T> bool PriorityQueueArrayHeap<T>::hasParent(Rank i)
{
	return i > 0;
}

template<typename T> bool PriorityQueueArrayHeap<T>::hasLChild(Rank i)
{
	return inHeap(lChild(i)) == true;
}

template<typename T> bool PriorityQueueArrayHeap<T>::hasRChild(Rank i)
{
	return inHeap(rChild(i)) == true;
}

template<typename T> Rank PriorityQueueArrayHeap<T>::bigger(Rank i, Rank j)
{
	return (this->element[i] < this->element[j]) ? j : i;
}

template<typename T> Rank PriorityQueueArrayHeap<T>::getMaxOfThree(Rank i)
{
	Rank lc = lChild(i), rc = rChild(i), max = 0;
	if (inHeap(rc) == true)
	{
		max = bigger(i, lc);
		max = bigger(max, rc);
	}
	else if (inHeap(lc) == true)
		max = bigger(i, lc);
	else
		max = i;
	return max;
}

template<typename T> Rank PriorityQueueArrayHeap<T>::percolateDown(Rank i)     //下滤算法
{
	T temp;
	Rank j = getMaxOfThree(i);                                                 //首先令j为i节点及其两个孩子三者中的最大者节点的位置索引
	while (i != j)                                                             //只要j不是i，就进行循环
	{
		temp = this->element[i];                                               //交换i和j
		this->element[i] = this->element[j];
		this->element[j] = temp;
		i = j;                                                                 //i移动到j处
		j = getMaxOfThree(i);                                                  //j再次为i节点及其两个孩子三者中的最大者节点的位置索引
	}
	return i;
}

template<typename T> Rank PriorityQueueArrayHeap<T>::percolateUp(Rank i)       //上滤算法
{
	Rank j = 0;
	T temp;
	while (hasParent(i) == true)                                               //只要i有母亲节点，就进行循环
	{
		j = parent(i);                                                         //j更新为i的母亲节点的位置索引
		if (this->element[i] < this->element[j])                               //如果element[i] < element[j]，则上滤完成
			break;
		temp = this->element[i];                                               //否则，交换i和j
		this->element[i] = this->element[j];
		this->element[j] = temp;
		i = j;                                                                 //i移动到j处
	}
	return i;
}

template<typename T> void PriorityQueueArrayHeap<T>::heapify()
{
	for (Rank i = lastInternal(); inHeap(i) == true; i--)
		percolateDown(i);
}

template<typename T> PriorityQueueArrayHeap<T>::PriorityQueueArrayHeap() {}

template<typename T> PriorityQueueArrayHeap<T>::PriorityQueueArrayHeap(T* A, Rank n) :VectorForHeap<T>(A, n)
{
	heapify();
}

template<typename T> void PriorityQueueArrayHeap<T>::insert(T e)               //插入词条
{
	VectorForHeap<T>::insert(e);                                               //调用VectorForHeap类的insert()，在element尾部插入新词条
	percolateUp(this->getSize() - 1);                                          //上滤这个新词条
}

template<typename T> T PriorityQueueArrayHeap<T>::getMax()                     //返回优先级最高的词条，直接返回element[0]即可
{
	return this->element[0];
}

template<typename T> T PriorityQueueArrayHeap<T>::deleteMax()                  //删除优先级最高的词条，并将其内容返回
{
	if (this->getSize() == 0)
	{
		cout << "Warning ! You cannot call deleteMax() from an empty priority queue !\n";
		return this->element[0];
	}
	T max = this->element[0];                                                  //保存优先级最高的词条的内容
	this->element[0] = this->element[--(this->size)];                          //将尾部的词条移动到头部
	percolateDown(0);                                                          //下滤头部词条
	return max;                                                                //返回之前优先级最高的词条的内容
}

