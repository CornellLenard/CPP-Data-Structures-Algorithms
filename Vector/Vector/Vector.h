/*********************************************************************************
 *   @file        Vector.h
 *   @brief       The header file for C++ implemented Vector
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "Fibonacci.h"
#include "PriorityQueueArrayHeap.h"
#include "VectorIndexOutOfBoundsException.h"
#include <random>
using namespace std;

typedef int Rank;                                                              //定义秩，以体现向量"循秩访问"的特性
template<typename T> class Vector                                              //向量模板类
{
protected:
	const static int DEFAULT_CAPACITY = 11;                                    //默认初始容量，可视实际需求改变此值
	Rank size;                                                                 //向量规模
	int capacity;                                                              //向量容量
	T* element;                                                                //向量存储的数据所占的内存区域
	void copyFrom(const T* A, Rank lo, Rank hi);                               //复制数组区间[lo,hi)
	void expand();                                                             //空间不足时向量扩容
	void shrink();                                                             //装填因子过小时向量缩容
	Rank binSearch(const T& e, Rank lo, Rank hi) const;                        //二分查找算法
	Rank fibSearch(const T& e, Rank lo, Rank hi) const;                        //斐波那契查找算法
	void bubbleSort(Rank lo, Rank hi);                                         //冒泡排序算法
	void selectionSort(Rank lo, Rank hi);                                      //选择排序算法
	void merge(Rank lo, Rank mi, Rank hi);                                     //归并算法
	void mergeSort(Rank lo, Rank hi);                                          //归并排序算法
	Rank getPartition(Rank lo, Rank hi);                                       //轴点构造算法，返回轴点的秩
	void quickSort(Rank lo, Rank hi);                                          //快速排序算法
	void heapSort(Rank lo, Rank hi);                                           //堆排序算法
public:
	//构造函数
	Vector(int c = DEFAULT_CAPACITY, Rank s = 0, T v = static_cast<T>(0));     //容量为c，规模为s，所有元素初始为v，按此构造向量
	Vector(const T* A, Rank n);                                                //用数组整体构造向量
	Vector(const T* A, Rank lo, Rank hi);                                      //用数组区间[lo,hi)构造向量
	Vector(const Vector<T>& v);                                                //用向量整体构造向量
	Vector(const Vector<T>& v, Rank lo, Rank hi);                              //用向量区间[lo,hi)构造向量
	//析构函数
	~Vector();                                                                 //释放向量所占内存空间
	//只读访问接口
	const T& operator [] (Rank r) const;                                       //重载[]运算符，返回常引用，不可作为左值
	Rank getSize() const;                                                      //获取向量规模
	bool isEmpty() const;                                                      //判断向量是否为空
	int disordered() const;                                                    //判断向量是否已有序，返回相邻元素逆序对数
	Rank find(const T& e) const;                                               //无序向量整体查找算法
	Rank find(const T& e, Rank lo, Rank hi) const;                             //无序向量区间[lo,hi)查找算法，若未找到，则返回lo-1
	Rank search(const T& e) const;                                             //有序向量整体查找算法
	Rank search(const T& e, Rank lo, Rank hi) const;                           //有序向量区间[lo,hi)查找算法，若未找到，则返回第一个<=e的元素的秩
	//可写访问接口
	T& operator [] (Rank r);                                                   //重载[]运算符，返回普通引用，可作为左值
	Vector<T>& operator = (const Vector<T>& v);                                //重载赋值运算符，可以实现向量的赋值
	T remove(Rank r);                                                          //删除秩为r的元素，返回元素的值
	int remove(Rank lo, Rank hi);                                              //删除秩处于区间[lo,hi)的元素，返回删除元素的个数
	Rank insert(Rank r, const T& e);                                           //在秩为r处插入元素，返回插入后新元素的秩
	Rank insert(const T& e);                                                   //在向量末尾插入元素
	void sort(Rank lo, Rank hi);                                               //向量区间[lo,hi)排序算法
	void sort();                                                               //向量整体排序算法
	void unsort(Rank lo, Rank hi);                                             //向量区间[lo,hi)置乱算法
	void unsort();                                                             //向量整体置乱算法
	int deduplicate();                                                         //无序向量去重算法，返回去重所删除的元素个数
	int uniquify();                                                            //有序向量去重算法，返回去重所删除的元素个数
	//遍历
	template<typename VST> void traverse(VST& visit);                          //使用函数对象，对向量进行遍历访问
};

template<typename T> void Vector<T>::copyFrom(const T* A, Rank lo, Rank hi)    //拷贝数组区间[lo,hi)各元素值用以构造向量
{
	capacity = 2 * (hi - lo);
	size = hi - lo;
	element = new T[capacity];
	for (Rank i = 0; i < size; i++)
		element[i] = A[lo + i];
}

template<typename T> void Vector<T>::expand()                                  //向量扩容算法
{
	if (getSize() < capacity)                                                  //向量未满不必扩容
		return;
	if (capacity < DEFAULT_CAPACITY)                                           //向量容量小于默认容量，则此次扩容暂且扩为默认容量
		capacity = DEFAULT_CAPACITY;
	T* old_element = element;
	capacity *= 2;                                                             //向量扩容算法在正常情况下容量变为2倍，从而使均摊时间复杂度为O(1)
	element = new T[capacity];
	for (Rank i = 0; i < getSize(); i++)
		element[i] = old_element[i];
	delete[] old_element;
	old_element = nullptr;
}

template<typename T> void Vector<T>::shrink()                                  //向量缩容算法
{
	if (capacity / 2 < DEFAULT_CAPACITY)                                       //当前容量缩容一次后便低于默认容量的话就不缩容了
		return;
	if (getSize() * 4 > capacity)                                              //装填因子，即size/capacity大于25%的话不缩容
		return;
	T* old_element = element;
	capacity /= 2;                                                             //向量缩容算法在正常情况下容量变为一半，从而使均摊时间复杂度为O(1)
	element = new T[capacity];
	for (Rank i = 0; i < getSize(); i++)
		element[i] = old_element[i];
	delete[] old_element;
	old_element = nullptr;
}

template<typename T> Rank Vector<T>::binSearch(const T& e, Rank lo, Rank hi) const    //二分查找算法
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	Rank mi = 0;
	while (lo < hi)
	{
		mi = (lo + hi) / 2;
		(e < element[mi]) ? hi = mi : lo = mi + 1;
	}
	return lo - 1;
}

template<typename T> Rank Vector<T>::fibSearch(const T& e, Rank lo, Rank hi) const    //斐波那契查找算法，轴点的构造不同于二分查找的折半，而是根据斐波那契数列来定
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	Fibonacci fib(hi - lo);
	Rank mi = 0;
	while (lo < hi)
	{
		while (fib.get() > hi - lo)
			fib.prev();
		mi = lo + fib.get() - 1;
		if (e < element[mi])
			hi = mi;
		else if (e > element[mi])
			lo = mi + 1;
		else
			return mi;
	}
}

template<typename T> void Vector<T>::bubbleSort(Rank lo, Rank hi)              //改进的冒泡排序算法，虽然渐近时间复杂度仍为O(n^2)，但是实际对比次数明显下降
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	Rank upper_bound = hi - 1;                                                 //右边界，意味着存在逆序对的范围为[lo,upper_bound]
	Rank uncertain_upper_bound = 0;                                            //在每一轮比对中，不断更新此"不确定右边界"，结束本轮比对后赋值给upper_bound
	T temp;
	while (lo < upper_bound)
	{
		uncertain_upper_bound = 0;                                             //每轮比对前将"不确定右边界"赋值为0
		for (Rank i = lo; i < upper_bound; i++)
		{
			if (element[i] > element[i + 1])                                   //element[i]和element[i+1]构成逆序对，则交换彼此，并更新"不确定右边界"
			{
				temp = element[i];
				element[i] = element[i + 1];
				element[i + 1] = temp;
				uncertain_upper_bound = i;
			}
		}
		upper_bound = uncertain_upper_bound;                                   //用本轮最终确定的新"不确定右边界"更新右边界
	}
}

template<typename T> void Vector<T>::selectionSort(Rank lo, Rank hi)           //选择排序算法，原理还是比较简单的
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	Rank max = 0;
	T temp;
	for (Rank upper_bound = hi - 1; upper_bound > lo; upper_bound--)
	{
		max = lo;
		for (Rank i = lo + 1; i <= upper_bound; i++)
		{
			if (element[i] >= element[max])
				max = i;
		}
		if (max == upper_bound)
			continue;
		else
		{
			temp = element[upper_bound];
			element[upper_bound] = element[max];
			element[max] = temp;
		}
	}
}

template<typename T> void Vector<T>::merge(Rank lo, Rank mi, Rank hi)          //归并算法，向量区间[lo,mi)和[mi,hi)分别各自有序，归并结束后区间[lo,hi)整体有序
{
	int lb = mi - lo, lc = hi - mi;
	T* A = element + lo;
	T* B = new T[lb];
	for (Rank i = 0; i < lb; i++)
		B[i] = A[i];
	T* C = element + mi;
	for (Rank i = 0, j = 0, k = 0; j < lb;)                                    //如果B已处理完毕，则C未处理部分所处位置就是最终正确位置，循环结束
		A[i++] = (k >= lc || B[j] <= C[k]) ? B[j++] : C[k++];                  //如果{C已处理完毕}或{未处理完毕且B[j]<=C[k]}，则用B[j]给A[i]赋值，否则用C[k]
	delete[] B;
	B = nullptr;
}

template<typename T> void Vector<T>::mergeSort(Rank lo, Rank hi)               //归并排序算法
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	if (hi - lo <= 1)
		return;
	Rank mi = (lo + hi) / 2;
	mergeSort(lo, mi);                                                         //二路归并
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}

template<typename T> Rank Vector<T>::getPartition(Rank lo, Rank hi)            //轴点选取算法
{
	T temp;
	uniform_int_distribution<int> u(0, hi - lo - 1);                           //先随机生成一个偏移量，其值在[0,hi-lo-1]之间
	default_random_engine e;
	Rank rd = u(e);
	temp = element[lo];                                                        //交换element[lo]与element[lo+rd]，这是为保证随机选取候选轴点
	element[lo] = element[lo + rd];
	element[lo + rd] = temp;
	T pivot = element[lo];
	hi--;
	while (lo < hi)                                                            //lo<hi时进行此循环
	{
		while ((lo < hi) && (pivot <= element[hi]))                            //当lo<hi且pivot<=element[hi]时，右侧的边界hi可以向中间靠拢
			hi--;
		element[lo] = element[hi];                                             //条件不满足时，将此值element[hi]赋给element[lo]
		while ((lo < hi) && (pivot >= element[lo]))                            //当lo<hi且pivot>=element[hi]时，左侧的边界lo可以向中间靠拢
			lo++;
		element[hi] = element[lo];                                             //条件不满足时，将此值element[lo]赋给element[hi]
	}
	element[lo] = pivot;                                                       //循环结束后lo就是轴点位置
	return lo;                                                                 //返回轴点的秩
}

template<typename T> void Vector<T>::quickSort(Rank lo, Rank hi)
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	if (hi - lo <= 1)
		return;
	Rank mi = getPartition(lo, hi);
	quickSort(lo, mi);
	quickSort(mi + 1, hi);
}

template<typename T> void Vector<T>::heapSort(Rank lo, Rank hi)                //堆排序算法
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	PriorityQueueArrayHeap<T> heap(element + lo, hi - lo);                     //首先将向量区间[lo,hi)的元素构造成一个优先级队列
	while (heap.isEmpty() == false)                                            //优先级队列不空时进行此循环
		element[--hi] = heap.deleteMax();                                      //将优先级队列首元素，即最大元，弹出并赋值到向量当前最右侧位置
}

template<typename T> Vector<T>::Vector(int c, Rank s, T v)
{
	capacity = c;
	size = s;
	element = new T[capacity];
	for (Rank i = 0; i < size; i++)
		element[i] = v;
}

template<typename T> Vector<T>::Vector(const T* A, Rank n)
{
	copyFrom(A, 0, n);
}

template<typename T> Vector<T>::Vector(const T* A, Rank lo, Rank hi)
{
	copyFrom(A, lo, hi);
}

template<typename T> Vector<T>::Vector(const Vector<T>& v)
{
	copyFrom(v.element, 0, v.size);
}

template<typename T> Vector<T>::Vector(const Vector<T>& v, Rank lo, Rank hi)
{
	copyFrom(v.element, lo, hi);
}

template<typename T> Vector<T>::~Vector()
{
	delete[] element;
	element = nullptr;
}

template<typename T> const T& Vector<T>::operator [] (Rank r) const
{
	if (r < 0 || r >= getSize())
		throw VectorIndexOutOfBoundsException();
	return element[r];
}

template<typename T> Rank Vector<T>::getSize() const
{
	return size;
}

template<typename T> bool Vector<T>::isEmpty() const
{
	return !static_cast<bool>(getSize());
}

template<typename T> int Vector<T>::disordered() const                         //统计相邻元素逆序对数量
{
	int count = 0;
	for (Rank i = 0; i < getSize() - 1; i++)
	{
		if (element[i] > element[i + 1])
			count++;
	}
	return count;
}

template<typename T> Rank Vector<T>::find(const T& e) const
{
	return find(e, 0, getSize());
}

template<typename T> Rank Vector<T>::find(const T& e, Rank lo, Rank hi) const  //无序向量区间[lo,hi)查找算法，注意接口语义，若未找到，则返回lo-1
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	for (Rank i = hi - 1; i >= lo; i--)
	{
		if (element[i] == e)
			return i;
	}
	return lo - 1;
}

template<typename T> Rank Vector<T>::search(const T& e) const
{
	return (getSize() == 0) ? (-1) : search(e, 0, getSize());
}

template<typename T> Rank Vector<T>::search(const T& e, Rank lo, Rank hi) const//有序向量查找接口，随机调用二分查找算法和斐波那契查找算法
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	uniform_int_distribution<int> u(0, 1);
	default_random_engine e;
	return u(e) ? binSearch(e, lo, hi) : fibSearch(e, lo, hi);
}

template<typename T> T Vector<T>::remove(Rank r)
{
	if (r < 0 || r >= getSize())
		throw VectorIndexOutOfBoundsException();
	T e = element[r];
	remove(r, r + 1);
	return e;
}

template<typename T> int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	if (lo == hi)
		return 0;
	for (Rank i = hi; i < getSize(); i++)
		element[i - hi + lo] = element[i];
	size -= (hi - lo);
	shrink();
	return hi - lo;
}

template<typename T> Rank Vector<T>::insert(Rank r, const T& e)
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

template<typename T> Rank Vector<T>::insert(const T& e)
{
	return insert(getSize(), e);
}

template<typename T> void Vector<T>::sort(Rank lo, Rank hi)                    //随机选择一种排序算法
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	uniform_int_distribution<int> u(0, 4);
	default_random_engine e;
	switch (u(e))
	{
	case 0:bubbleSort(lo, hi); break;
	case 1:selectionSort(lo, hi); break;
	case 2:mergeSort(lo, hi); break;
	case 3:heapSort(lo, hi); break;
	case 4:quickSort(lo, hi); break;
	}
}

template<typename T> void Vector<T>::sort()
{
	sort(0, getSize());
}

template<typename T> void Vector<T>::unsort(Rank lo, Rank hi)
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	T* v = element + lo;
	T temp;
	default_random_engine e;
	Rank r = 0;
	for (Rank i = hi - 1; i >= lo + 1; i--)
	{
		uniform_int_distribution<int> u(0, i - 1);
		r = u(e);
		temp = element[i];
		element[i] = element[r];
		element[r] = temp;
	}
}

template<typename T> void Vector<T>::unsort()
{
	unsort(0, getSize());
}

template<typename T> T& Vector<T>::operator [] (Rank r)
{
	if (r < 0 || r >= getSize())
		throw VectorIndexOutOfBoundsException();
	return element[r];
}

template<typename T> Vector<T>& Vector<T>::operator = (const Vector<T>& v)
{
	if (element != nullptr)
		delete[] element;
	copyFrom(v.element, 0, v.size);
	return *this;
}

template<typename T> int Vector<T>::deduplicate()                              //无序向量去重算法，时间复杂度O(n^2)
{
	int old_size = getSize();
	Rank i = 1;
	while (i < getSize())
		(find(element[i], 0, i) < 0) ? i++ : remove(i);
	return old_size - getSize();
}

template<typename T> int Vector<T>::uniquify()                                 //有序向量去重算法，时间复杂度O(n)
{
	Rank i = 0, j = 1;
	while (j < getSize())
	{
		if (element[i] != element[j])
			element[++i] = element[j];
		j++;
	}
	size = ++i;
	shrink();
	return j - i;
}

template<typename T> template<typename VST> void Vector<T>::traverse(VST& visit)
{
	for (Rank i = 0; i < getSize(); i++)
		visit(element[i]);
}

