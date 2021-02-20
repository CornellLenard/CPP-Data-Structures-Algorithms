/*********************************************************************************
 *   @file        PriorityQueueArrayHeap.h
 *   @brief       The header file for C++ implemented Priority Queue
 *                based on Array Heap - so called Complete Binary Heap
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "PriorityQueue.h"
#include "VectorForHeap.h"
#include <iostream>
using namespace std;

template<typename T> class PriorityQueueArrayHeap : public PriorityQueue<T>, public VectorForHeap<T>      //������ȫ����ѵ����ȼ�����ģ����
{
protected:
	bool inHeap(Rank i);                                                       //�ж�λ��i�Ƿ�Ϸ�
	Rank parent(Rank i);                                                       //����i�ڵ��ĸ�׽ڵ��λ������
	Rank lastInternal();                                                       //�������һ���ڲ��ڵ㣬Ҳ����ĩ�ڵ��ĸ�׽ڵ��λ������
	Rank lChild(Rank i);                                                       //����i�ڵ�����ӵ�λ������
	Rank rChild(Rank i);                                                       //����i�ڵ���Һ��ӵ�λ������
	bool hasParent(Rank i);                                                    //�ж�i�ڵ��Ƿ���ĸ�׽ڵ�
	bool hasLChild(Rank i);                                                    //�ж�i�ڵ��Ƿ�������
	bool hasRChild(Rank i);                                                    //�ж�i�ڵ��Ƿ����Һ���
	Rank bigger(Rank i, Rank j);                                               //����i�ڵ��j�ڵ����д��ߵ�λ������
	Rank getMaxOfThree(Rank i);                                                //����i�ڵ�����������ӽڵ��������е�����ߵ�λ������
	Rank percolateDown(Rank i);                                                //�����㷨������������ɺ�i������λ������
	Rank percolateUp(Rank i);                                                  //�����㷨������������ɺ�i������λ������
	void heapify();                                                            //Floyd�����㷨
public:
	PriorityQueueArrayHeap();                                                  //Ĭ�Ϲ��캯��
	PriorityQueueArrayHeap(T* A, Rank n);                                      //���캯��
	void insert(T e);                                                          //���ձȽ���ȷ�������ȼ����򣬲������
	T getMax();                                                                //�������ȼ���ߵĴ���
	T deleteMax();                                                             //ɾ�����ȼ���ߵĴ��������������ݷ���
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

template<typename T> Rank PriorityQueueArrayHeap<T>::percolateDown(Rank i)     //�����㷨
{
	T temp;
	Rank j = getMaxOfThree(i);                                                 //������jΪi�ڵ㼰���������������е�����߽ڵ��λ������
	while (i != j)                                                             //ֻҪj����i���ͽ���ѭ��
	{
		temp = this->element[i];                                               //����i��j
		this->element[i] = this->element[j];
		this->element[j] = temp;
		i = j;                                                                 //i�ƶ���j��
		j = getMaxOfThree(i);                                                  //j�ٴ�Ϊi�ڵ㼰���������������е�����߽ڵ��λ������
	}
	return i;
}

template<typename T> Rank PriorityQueueArrayHeap<T>::percolateUp(Rank i)       //�����㷨
{
	Rank j = 0;
	T temp;
	while (hasParent(i) == true)                                               //ֻҪi��ĸ�׽ڵ㣬�ͽ���ѭ��
	{
		j = parent(i);                                                         //j����Ϊi��ĸ�׽ڵ��λ������
		if (this->element[i] < this->element[j])                               //���element[i] < element[j]�����������
			break;
		temp = this->element[i];                                               //���򣬽���i��j
		this->element[i] = this->element[j];
		this->element[j] = temp;
		i = j;                                                                 //i�ƶ���j��
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

template<typename T> void PriorityQueueArrayHeap<T>::insert(T e)               //�������
{
	VectorForHeap<T>::insert(e);                                               //����VectorForHeap���insert()����elementβ�������´���
	percolateUp(this->getSize() - 1);                                          //��������´���
}

template<typename T> T PriorityQueueArrayHeap<T>::getMax()                     //�������ȼ���ߵĴ�����ֱ�ӷ���element[0]����
{
	return this->element[0];
}

template<typename T> T PriorityQueueArrayHeap<T>::deleteMax()                  //ɾ�����ȼ���ߵĴ��������������ݷ���
{
	if (this->getSize() == 0)
	{
		cout << "Warning ! You cannot call deleteMax() from an empty priority queue !\n";
		return this->element[0];
	}
	T max = this->element[0];                                                  //�������ȼ���ߵĴ���������
	this->element[0] = this->element[--(this->size)];                          //��β���Ĵ����ƶ���ͷ��
	percolateDown(0);                                                          //����ͷ������
	return max;                                                                //����֮ǰ���ȼ���ߵĴ���������
}

