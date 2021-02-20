/*********************************************************************************
 *   @file        Stack.h
 *   @brief       The header file for C++ implemented Stack
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "StackUnderflowException.h"
using namespace std;

template<typename T> class Stack                                               //栈模板类
{
protected:
	const static int DEFAULT_CAPACITY = 11;                                    //默认初始容量，可视实际需求改变此值
	int size;                                                                  //栈规模
	int capacity;                                                              //栈容量
	T* element;                                                                //栈存储的数据所占的内存区域
	void copyFrom(const T* A, int lo, int hi);                                 //复制数组区间[lo,hi)
	void expand();                                                             //空间不足时栈扩容
	void shrink();                                                             //装填因子过小时栈缩容
public:
	//构造函数
	Stack(int c = DEFAULT_CAPACITY, int s = 0, T v = static_cast<T>(0));       //容量为c，规模为s，所有元素初始为v
	Stack(const T* A, int n);                                                  //用数组整体构造栈
	Stack(const T* A, int lo, int hi);                                         //用数组区间[lo,hi)构造栈
	Stack(const Stack<T>& s);                                                  //用栈整体构造栈
	Stack(const Stack<T>& s, int lo, int hi);                                  //用栈区间[lo,hi)构造栈
	//析构函数
	~Stack();                                                                  //释放栈所占内存空间
	//只读访问接口
	int getSize() const;                                                       //获取栈规模
	bool isEmpty() const;                                                      //判断栈是否为空
	//可写访问接口
	Stack<T>& operator = (const Stack<T>& s);                                  //重载赋值运算符，可以实现栈的赋值
	void push(const T& e);                                                     //入栈
	T pop();                                                                   //出栈
	T& top();                                                                  //取栈顶元素
};

template<typename T> void Stack<T>::copyFrom(const T* A, int lo, int hi)
{
	capacity = 2 * (hi - lo);
	size = hi - lo;
	element = new T[capacity];
	for (int i = 0; i < size; i++)
		element[i] = A[lo + i];
}

template<typename T> void Stack<T>::expand()                                   //扩容时容量变为2倍，从而使得均摊时间复杂度为O(1)
{
	if (getSize() < capacity)                                                  //如果栈未满，则不用扩容
		return;
	if (capacity < DEFAULT_CAPACITY)                                           //如果栈容量小于默认容量，则此次扩容将容量暂且扩容到默认容量
		capacity = DEFAULT_CAPACITY;
	T* old_element = element;
	capacity *= 2;
	element = new T[capacity];
	for (int i = 0; i < getSize(); i++)
		element[i] = old_element[i];
	delete[] old_element;
	old_element = nullptr;
}

template<typename T> void Stack<T>::shrink()                                   //缩容时容量变为一半，从而使得均摊时间复杂度为O(1)
{
	if (capacity / 2 < DEFAULT_CAPACITY)                                       //如果本次缩容后容量小于默认容量，则不缩容
		return;
	if (getSize() * 4 > capacity)                                              //只有装填因子size/capacity <= 25%时才缩容
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
	expand();                                                                  //压栈之前，先调用扩容算法，判断是否扩容的工作在扩容算法中进行
	element[getSize()] = e;
	size++;
}

template<typename T> T Stack<T>::pop()                                         //空栈不应该执行pop()，所以抛出异常
{
	if (getSize() == 0)
		throw StackUnderflowException();
	T res = element[getSize() - 1];
	size--;
	shrink();                                                                  //出栈后，调用缩容算法，判断是否缩容的工作在缩容算法中进行
	return res;
}

template<typename T> T& Stack<T>::top()                                        //空栈不应该执行top()，所以抛出异常
{
	if (getSize() == 0)
		throw StackUnderflowException();
	return element[getSize() - 1];
}
