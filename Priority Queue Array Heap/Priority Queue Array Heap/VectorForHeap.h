/*********************************************************************************
 *   @file        VectorForHeap.h
 *   @brief       The header file for C++ implemented VectorForHeap
 *   @details     Works as Array Heap, so called Complete Binary Heap
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "VectorIndexOutOfBoundsException.h"

typedef int Rank;                                                              //�����ȣ�����������"ѭ�ȷ���"������
template<typename T> class VectorForHeap                                       //����ģ����
{
protected:
	const static int DEFAULT_CAPACITY = 11;                                    //Ĭ�ϳ�ʼ����������ʵ������ı��ֵ
	Rank size;                                                                 //������ģ
	int capacity;                                                              //��������
	T* element;                                                                //�����洢��������ռ���ڴ�����
	void copyFrom(const T* A, Rank lo, Rank hi);                               //������������[lo,hi)
	void expand();                                                             //�ռ䲻��ʱ��������
	void shrink();                                                             //װ�����ӹ�Сʱ��������
public:
	//���캯��
	VectorForHeap(int c = DEFAULT_CAPACITY, Rank s = 0, T v = static_cast<T>(0));     //����Ϊc����ģΪs������Ԫ�س�ʼΪv
	VectorForHeap(const T* A, Rank n);                                         //���������幹������
	VectorForHeap(const T* A, Rank lo, Rank hi);                               //����������[lo,hi)��������
	VectorForHeap(const VectorForHeap<T>& v);                                  //���������幹������
	VectorForHeap(const VectorForHeap<T>& v, Rank lo, Rank hi);                //����������[lo,hi)��������
	//��������
	~VectorForHeap();                                                          //�ͷ�������ռ�ڴ�ռ�
	//ֻ�����ʽӿ�
	const T& operator [] (Rank r) const;                                       //����[]����������س����ã�������Ϊ��ֵ
	Rank getSize() const;                                                      //��ȡ������ģ
	bool isEmpty() const;                                                      //�ж������Ƿ�Ϊ��
	//��д���ʽӿ�
	T& operator [] (Rank r);                                                   //����[]�����������Ϊ��ֵ
	VectorForHeap<T>& operator = (const VectorForHeap<T>& v);                  //���ظ�ֵ�����������ʵ�������ĸ�ֵ
	Rank insert(Rank r, const T& e);                                           //����Ϊr������Ԫ��
	Rank insert(const T& e);                                                   //������ĩβ����Ԫ��
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

