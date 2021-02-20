/*********************************************************************************
 *   @file        VectorForHeap.h
 *   @brief       The header file for C++ implemented VectorForHeap
 *   @details     Works as Array Heap, so called Complete Binary Heap
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "VectorIndexOutOfBoundsException.h"

typedef int Rank;                                                              //定义秩，以体现向量"循秩访问"的特性
template<typename T> class VectorForHeap                                       //向量模板类
{
protected:
	const static int DEFAULT_CAPACITY = 11;                                    //默认初始容量，可视实际需求改变此值
	Rank size;                                                                 //向量规模
	int capacity;                                                              //向量容量
	T* element;                                                                //向量存储的数据所占的内存区域
	void copyFrom(const T* A, Rank lo, Rank hi);                               //复制数组区间[lo,hi)
	void expand();                                                             //空间不足时向量扩容
	void shrink();                                                             //装填因子过小时向量缩容
public:
	//构造函数
	VectorForHeap(int c = DEFAULT_CAPACITY, Rank s = 0, T v = static_cast<T>(0));     //容量为c，规模为s，所有元素初始为v
	VectorForHeap(const T* A, Rank n);                                         //用数组整体构造向量
	VectorForHeap(const T* A, Rank lo, Rank hi);                               //用数组区间[lo,hi)构造向量
	VectorForHeap(const VectorForHeap<T>& v);                                  //用向量整体构造向量
	VectorForHeap(const VectorForHeap<T>& v, Rank lo, Rank hi);                //用向量区间[lo,hi)构造向量
	//析构函数
	~VectorForHeap();                                                          //释放向量所占内存空间
	//只读访问接口
	const T& operator [] (Rank r) const;                                       //重载[]运算符，返回常引用，不可作为左值
	Rank getSize() const;                                                      //获取向量规模
	bool isEmpty() const;                                                      //判断向量是否为空
	//可写访问接口
	T& operator [] (Rank r);                                                   //重载[]运算符，可作为左值
	VectorForHeap<T>& operator = (const VectorForHeap<T>& v);                  //重载赋值运算符，可以实现向量的赋值
	Rank insert(Rank r, const T& e);                                           //在秩为r处插入元素
	Rank insert(const T& e);                                                   //在向量末尾插入元素
};

template<typename T> void VectorForHeap<T>::copyFrom(const T* A, Rank lo, Rank hi)
{
	capacity = 2 * (hi - lo);
	size = hi - lo;
	element = new T[capacity];
	for (Rank i = 0; i < size; i++)
		element[i] = A[lo + i];
}

template<typename T> void VectorForHeap<T>::expand()
{
	if (getSize() < capacity)
		return;
	if (capacity < DEFAULT_CAPACITY)
		capacity = DEFAULT_CAPACITY;
	T* old_element = element;
	capacity *= 2;
	element = new T[capacity];
	for (Rank i = 0; i < getSize(); i++)
		element[i] = old_element[i];
	delete[] old_element;
	old_element = nullptr;
}

template<typename T> void VectorForHeap<T>::shrink()
{
	if (capacity / 2 < DEFAULT_CAPACITY)
		return;
	if (getSize() * 4 > capacity)
		return;
	T* old_element = element;
	capacity /= 2;
	element = new T[capacity];
	for (Rank i = 0; i < getSize(); i++)
		element[i] = old_element[i];
	delete[] old_element;
	old_element = nullptr;
}

template<typename T> VectorForHeap<T>::VectorForHeap(int c, Rank s, T v)
{
	capacity = c;
	size = s;
	element = new T[capacity];
	for (Rank i = 0; i < size; i++)
		element[i] = v;
}

template<typename T> VectorForHeap<T>::VectorForHeap(const T* A, Rank n)
{
	copyFrom(A, 0, n);
}

template<typename T> VectorForHeap<T>::VectorForHeap(const T* A, Rank lo, Rank hi)
{
	copyFrom(A, lo, hi);
}

template<typename T> VectorForHeap<T>::VectorForHeap(const VectorForHeap<T>& v)
{
	copyFrom(v.element, 0, v.size);
}

template<typename T> VectorForHeap<T>::VectorForHeap(const VectorForHeap<T>& v, Rank lo, Rank hi)
{
	copyFrom(v.element, lo, hi);
}

template<typename T> VectorForHeap<T>::~VectorForHeap()
{
	delete[] element;
	element = nullptr;
}

template<typename T> const T& VectorForHeap<T>::operator [] (Rank r) const
{
	if (r < 0 || r >= getSize())
		throw VectorIndexOutOfBoundsException();
	return element[r];
}

template<typename T> Rank VectorForHeap<T>::getSize() const
{
	return size;
}

template<typename T> bool VectorForHeap<T>::isEmpty() const
{
	return !static_cast<bool>(getSize());
}

template<typename T> Rank VectorForHeap<T>::insert(Rank r, const T& e)
{
	if (r > getSize())
		throw VectorIndexOutOfBoundsException();
	expand();
	for (Rank i = getSize() - 1; i >= r; i--)
		element[i + 1] = element[i];
	element[r] = e;
	size++;
	return r;
}

template<typename T> Rank VectorForHeap<T>::insert(const T& e)
{
	return insert(getSize(), e);
}

template<typename T> T& VectorForHeap<T>::operator [] (Rank r)
{
	if (r < 0 || r >= getSize())
		throw VectorIndexOutOfBoundsException();
	return element[r];
}

template<typename T> VectorForHeap<T>& VectorForHeap<T>::operator = (const VectorForHeap<T>& v)
{
	if (element != nullptr)
		delete[] element;
	copyFrom(v.element, 0, v.size);
	return *this;
}

