/*********************************************************************************
 *   @file        Stack.h
 *   @brief       The header file for C++ implemented Stack
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "StackUnderflowException.h"
using namespace std;

template<typename T> class Stack                                               //ջģ����
{
protected:
	const static int DEFAULT_CAPACITY = 11;                                    //Ĭ�ϳ�ʼ����������ʵ������ı��ֵ
	int size;                                                                  //ջ��ģ
	int capacity;                                                              //ջ����
	T* element;                                                                //ջ�洢��������ռ���ڴ�����
	void copyFrom(const T* A, int lo, int hi);                                 //������������[lo,hi)
	void expand();                                                             //�ռ䲻��ʱջ����
	void shrink();                                                             //װ�����ӹ�Сʱջ����
public:
	//���캯��
	Stack(int c = DEFAULT_CAPACITY, int s = 0, T v = static_cast<T>(0));       //����Ϊc����ģΪs������Ԫ�س�ʼΪv
	Stack(const T* A, int n);                                                  //���������幹��ջ
	Stack(const T* A, int lo, int hi);                                         //����������[lo,hi)����ջ
	Stack(const Stack<T>& s);                                                  //��ջ���幹��ջ
	Stack(const Stack<T>& s, int lo, int hi);                                  //��ջ����[lo,hi)����ջ
	//��������
	~Stack();                                                                  //�ͷ�ջ��ռ�ڴ�ռ�
	//ֻ�����ʽӿ�
	int getSize() const;                                                       //��ȡջ��ģ
	bool isEmpty() const;                                                      //�ж�ջ�Ƿ�Ϊ��
	//��д���ʽӿ�
	Stack<T>& operator = (const Stack<T>& s);                                  //���ظ�ֵ�����������ʵ��ջ�ĸ�ֵ
	void push(const T& e);                                                     //��ջ
	T pop();                                                                   //��ջ
	T& top();                                                                  //ȡջ��Ԫ��
};

template<typename T> void Stack<T>::copyFrom(const T* A, int lo, int hi)
{
	capacity = 2 * (hi - lo);
	size = hi - lo;
	element = new T[capacity];
	for (int i = 0; i < size; i++)
		element[i] = A[lo + i];
}

template<typename T> void Stack<T>::expand()                                   //����ʱ������Ϊ2�����Ӷ�ʹ�þ�̯ʱ�临�Ӷ�ΪO(1)
{
	if (getSize() < capacity)                                                  //���ջδ������������
		return;
	if (capacity < DEFAULT_CAPACITY)                                           //���ջ����С��Ĭ����������˴����ݽ������������ݵ�Ĭ������
		capacity = DEFAULT_CAPACITY;
	T* old_element = element;
	capacity *= 2;
	element = new T[capacity];
	for (int i = 0; i < getSize(); i++)
		element[i] = old_element[i];
	delete[] old_element;
	old_element = nullptr;
}

template<typename T> void Stack<T>::shrink()                                   //����ʱ������Ϊһ�룬�Ӷ�ʹ�þ�̯ʱ�临�Ӷ�ΪO(1)
{
	if (capacity / 2 < DEFAULT_CAPACITY)                                       //����������ݺ�����С��Ĭ��������������
		return;
	if (getSize() * 4 > capacity)                                              //ֻ��װ������size/capacity <= 25%ʱ������
		return;
	T* old_element = element;
	capacity /= 2;
	element = new T[capacity];
	for (int i = 0; i < getSize(); i++)
		element[i] = old_element[i];
	delete[] old_element;
	old_element = nullptr;
}

template<typename T> Stack<T>::Stack(int c, int s, T v)
{
	capacity = c;
	size = s;
	element = new T[capacity];
	for (int i = 0; i < size; i++)
		element[i] = v;
}

template<typename T> Stack<T>::Stack(const T* A, int n)
{
	copyFrom(A, 0, n);
}

template<typename T> Stack<T>::Stack(const T* A, int lo, int hi)
{
	copyFrom(A, lo, hi);
}

template<typename T> Stack<T>::Stack(const Stack<T>& s)
{
	copyFrom(s.element, 0, s.size);
}

template<typename T> Stack<T>::Stack(const Stack<T>& s, int lo, int hi)
{
	copyFrom(s.element, lo, hi);
}

template<typename T> Stack<T>::~Stack()
{
	delete[] element;
	element = nullptr;
}

template<typename T> int Stack<T>::getSize() const
{
	return size;
}

template<typename T> bool Stack<T>::isEmpty() const
{
	return !static_cast<bool>(getSize());
}

template<typename T> Stack<T>& Stack<T>::operator = (const Stack<T>& s)
{
	if (element != nullptr)
		delete[] element;
	copyFrom(s.element, 0, s.size);
	return *this;
}

template<typename T> void Stack<T>::push(const T& e)
{
	expand();                                                                  //ѹջ֮ǰ���ȵ��������㷨���ж��Ƿ����ݵĹ����������㷨�н���
	element[getSize()] = e;
	size++;
}

template<typename T> T Stack<T>::pop()                                         //��ջ��Ӧ��ִ��pop()�������׳��쳣
{
	if (getSize() == 0)
		throw StackUnderflowException();
	T res = element[getSize() - 1];
	size--;
	shrink();                                                                  //��ջ�󣬵��������㷨���ж��Ƿ����ݵĹ����������㷨�н���
	return res;
}

template<typename T> T& Stack<T>::top()                                        //��ջ��Ӧ��ִ��top()�������׳��쳣
{
	if (getSize() == 0)
		throw StackUnderflowException();
	return element[getSize() - 1];
}
