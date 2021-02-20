/*********************************************************************************
 *   @file        Vector.h
 *   @brief       The header file for C++ implemented Vector
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "Fibonacci.h"
#include "PriorityQueueArrayHeap.h"
#include "VectorIndexOutOfBoundsException.h"
#include <random>
using namespace std;

typedef int Rank;                                                              //�����ȣ�����������"ѭ�ȷ���"������
template<typename T> class Vector                                              //����ģ����
{
protected:
	const static int DEFAULT_CAPACITY = 11;                                    //Ĭ�ϳ�ʼ����������ʵ������ı��ֵ
	Rank size;                                                                 //������ģ
	int capacity;                                                              //��������
	T* element;                                                                //�����洢��������ռ���ڴ�����
	void copyFrom(const T* A, Rank lo, Rank hi);                               //������������[lo,hi)
	void expand();                                                             //�ռ䲻��ʱ��������
	void shrink();                                                             //װ�����ӹ�Сʱ��������
	Rank binSearch(const T& e, Rank lo, Rank hi) const;                        //���ֲ����㷨
	Rank fibSearch(const T& e, Rank lo, Rank hi) const;                        //쳲����������㷨
	void bubbleSort(Rank lo, Rank hi);                                         //ð�������㷨
	void selectionSort(Rank lo, Rank hi);                                      //ѡ�������㷨
	void merge(Rank lo, Rank mi, Rank hi);                                     //�鲢�㷨
	void mergeSort(Rank lo, Rank hi);                                          //�鲢�����㷨
	Rank getPartition(Rank lo, Rank hi);                                       //��㹹���㷨������������
	void quickSort(Rank lo, Rank hi);                                          //���������㷨
	void heapSort(Rank lo, Rank hi);                                           //�������㷨
public:
	//���캯��
	Vector(int c = DEFAULT_CAPACITY, Rank s = 0, T v = static_cast<T>(0));     //����Ϊc����ģΪs������Ԫ�س�ʼΪv�����˹�������
	Vector(const T* A, Rank n);                                                //���������幹������
	Vector(const T* A, Rank lo, Rank hi);                                      //����������[lo,hi)��������
	Vector(const Vector<T>& v);                                                //���������幹������
	Vector(const Vector<T>& v, Rank lo, Rank hi);                              //����������[lo,hi)��������
	//��������
	~Vector();                                                                 //�ͷ�������ռ�ڴ�ռ�
	//ֻ�����ʽӿ�
	const T& operator [] (Rank r) const;                                       //����[]����������س����ã�������Ϊ��ֵ
	Rank getSize() const;                                                      //��ȡ������ģ
	bool isEmpty() const;                                                      //�ж������Ƿ�Ϊ��
	int disordered() const;                                                    //�ж������Ƿ������򣬷�������Ԫ���������
	Rank find(const T& e) const;                                               //����������������㷨
	Rank find(const T& e, Rank lo, Rank hi) const;                             //������������[lo,hi)�����㷨����δ�ҵ����򷵻�lo-1
	Rank search(const T& e) const;                                             //����������������㷨
	Rank search(const T& e, Rank lo, Rank hi) const;                           //������������[lo,hi)�����㷨����δ�ҵ����򷵻ص�һ��<=e��Ԫ�ص���
	//��д���ʽӿ�
	T& operator [] (Rank r);                                                   //����[]�������������ͨ���ã�����Ϊ��ֵ
	Vector<T>& operator = (const Vector<T>& v);                                //���ظ�ֵ�����������ʵ�������ĸ�ֵ
	T remove(Rank r);                                                          //ɾ����Ϊr��Ԫ�أ�����Ԫ�ص�ֵ
	int remove(Rank lo, Rank hi);                                              //ɾ���ȴ�������[lo,hi)��Ԫ�أ�����ɾ��Ԫ�صĸ���
	Rank insert(Rank r, const T& e);                                           //����Ϊr������Ԫ�أ����ز������Ԫ�ص���
	Rank insert(const T& e);                                                   //������ĩβ����Ԫ��
	void sort(Rank lo, Rank hi);                                               //��������[lo,hi)�����㷨
	void sort();                                                               //�������������㷨
	void unsort(Rank lo, Rank hi);                                             //��������[lo,hi)�����㷨
	void unsort();                                                             //�������������㷨
	int deduplicate();                                                         //��������ȥ���㷨������ȥ����ɾ����Ԫ�ظ���
	int uniquify();                                                            //��������ȥ���㷨������ȥ����ɾ����Ԫ�ظ���
	//����
	template<typename VST> void traverse(VST& visit);                          //ʹ�ú������󣬶��������б�������
};

template<typename T> void Vector<T>::copyFrom(const T* A, Rank lo, Rank hi)    //������������[lo,hi)��Ԫ��ֵ���Թ�������
{
	capacity = 2 * (hi - lo);
	size = hi - lo;
	element = new T[capacity];
	for (Rank i = 0; i < size; i++)
		element[i] = A[lo + i];
}

template<typename T> void Vector<T>::expand()                                  //���������㷨
{
	if (getSize() < capacity)                                                  //����δ����������
		return;
	if (capacity < DEFAULT_CAPACITY)                                           //��������С��Ĭ����������˴�����������ΪĬ������
		capacity = DEFAULT_CAPACITY;
	T* old_element = element;
	capacity *= 2;                                                             //���������㷨�����������������Ϊ2�����Ӷ�ʹ��̯ʱ�临�Ӷ�ΪO(1)
	element = new T[capacity];
	for (Rank i = 0; i < getSize(); i++)
		element[i] = old_element[i];
	delete[] old_element;
	old_element = nullptr;
}

template<typename T> void Vector<T>::shrink()                                  //���������㷨
{
	if (capacity / 2 < DEFAULT_CAPACITY)                                       //��ǰ��������һ�κ�����Ĭ�������Ļ��Ͳ�������
		return;
	if (getSize() * 4 > capacity)                                              //װ�����ӣ���size/capacity����25%�Ļ�������
		return;
	T* old_element = element;
	capacity /= 2;                                                             //���������㷨�����������������Ϊһ�룬�Ӷ�ʹ��̯ʱ�临�Ӷ�ΪO(1)
	element = new T[capacity];
	for (Rank i = 0; i < getSize(); i++)
		element[i] = old_element[i];
	delete[] old_element;
	old_element = nullptr;
}

template<typename T> Rank Vector<T>::binSearch(const T& e, Rank lo, Rank hi) const    //���ֲ����㷨
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

template<typename T> Rank Vector<T>::fibSearch(const T& e, Rank lo, Rank hi) const    //쳲����������㷨�����Ĺ��첻ͬ�ڶ��ֲ��ҵ��۰룬���Ǹ���쳲�������������
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

template<typename T> void Vector<T>::bubbleSort(Rank lo, Rank hi)              //�Ľ���ð�������㷨����Ȼ����ʱ�临�Ӷ���ΪO(n^2)������ʵ�ʶԱȴ��������½�
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	Rank upper_bound = hi - 1;                                                 //�ұ߽磬��ζ�Ŵ�������Եķ�ΧΪ[lo,upper_bound]
	Rank uncertain_upper_bound = 0;                                            //��ÿһ�ֱȶ��У����ϸ��´�"��ȷ���ұ߽�"���������ֱȶԺ�ֵ��upper_bound
	T temp;
	while (lo < upper_bound)
	{
		uncertain_upper_bound = 0;                                             //ÿ�ֱȶ�ǰ��"��ȷ���ұ߽�"��ֵΪ0
		for (Rank i = lo; i < upper_bound; i++)
		{
			if (element[i] > element[i + 1])                                   //element[i]��element[i+1]��������ԣ��򽻻��˴ˣ�������"��ȷ���ұ߽�"
			{
				temp = element[i];
				element[i] = element[i + 1];
				element[i + 1] = temp;
				uncertain_upper_bound = i;
			}
		}
		upper_bound = uncertain_upper_bound;                                   //�ñ�������ȷ������"��ȷ���ұ߽�"�����ұ߽�
	}
}

template<typename T> void Vector<T>::selectionSort(Rank lo, Rank hi)           //ѡ�������㷨��ԭ���ǱȽϼ򵥵�
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

template<typename T> void Vector<T>::merge(Rank lo, Rank mi, Rank hi)          //�鲢�㷨����������[lo,mi)��[mi,hi)�ֱ�������򣬹鲢����������[lo,hi)��������
{
	int lb = mi - lo, lc = hi - mi;
	T* A = element + lo;
	T* B = new T[lb];
	for (Rank i = 0; i < lb; i++)
		B[i] = A[i];
	T* C = element + mi;
	for (Rank i = 0, j = 0, k = 0; j < lb;)                                    //���B�Ѵ�����ϣ���Cδ����������λ�þ���������ȷλ�ã�ѭ������
		A[i++] = (k >= lc || B[j] <= C[k]) ? B[j++] : C[k++];                  //���{C�Ѵ������}��{δ���������B[j]<=C[k]}������B[j]��A[i]��ֵ��������C[k]
	delete[] B;
	B = nullptr;
}

template<typename T> void Vector<T>::mergeSort(Rank lo, Rank hi)               //�鲢�����㷨
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	if (hi - lo <= 1)
		return;
	Rank mi = (lo + hi) / 2;
	mergeSort(lo, mi);                                                         //��·�鲢
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}

template<typename T> Rank Vector<T>::getPartition(Rank lo, Rank hi)            //���ѡȡ�㷨
{
	T temp;
	uniform_int_distribution<int> u(0, hi - lo - 1);                           //���������һ��ƫ��������ֵ��[0,hi-lo-1]֮��
	default_random_engine e;
	Rank rd = u(e);
	temp = element[lo];                                                        //����element[lo]��element[lo+rd]������Ϊ��֤���ѡȡ��ѡ���
	element[lo] = element[lo + rd];
	element[lo + rd] = temp;
	T pivot = element[lo];
	hi--;
	while (lo < hi)                                                            //lo<hiʱ���д�ѭ��
	{
		while ((lo < hi) && (pivot <= element[hi]))                            //��lo<hi��pivot<=element[hi]ʱ���Ҳ�ı߽�hi�������м俿£
			hi--;
		element[lo] = element[hi];                                             //����������ʱ������ֵelement[hi]����element[lo]
		while ((lo < hi) && (pivot >= element[lo]))                            //��lo<hi��pivot>=element[hi]ʱ�����ı߽�lo�������м俿£
			lo++;
		element[hi] = element[lo];                                             //����������ʱ������ֵelement[lo]����element[hi]
	}
	element[lo] = pivot;                                                       //ѭ��������lo�������λ��
	return lo;                                                                 //����������
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

template<typename T> void Vector<T>::heapSort(Rank lo, Rank hi)                //�������㷨
{
	if (lo < 0 || lo > getSize() || hi < 0 || hi > getSize())
		throw VectorIndexOutOfBoundsException();
	PriorityQueueArrayHeap<T> heap(element + lo, hi - lo);                     //���Ƚ���������[lo,hi)��Ԫ�ع����һ�����ȼ�����
	while (heap.isEmpty() == false)                                            //���ȼ����в���ʱ���д�ѭ��
		element[--hi] = heap.deleteMax();                                      //�����ȼ�������Ԫ�أ������Ԫ����������ֵ��������ǰ���Ҳ�λ��
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

template<typename T> int Vector<T>::disordered() const                         //ͳ������Ԫ�����������
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

template<typename T> Rank Vector<T>::find(const T& e, Rank lo, Rank hi) const  //������������[lo,hi)�����㷨��ע��ӿ����壬��δ�ҵ����򷵻�lo-1
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

template<typename T> Rank Vector<T>::search(const T& e, Rank lo, Rank hi) const//�����������ҽӿڣ�������ö��ֲ����㷨��쳲����������㷨
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

template<typename T> void Vector<T>::sort(Rank lo, Rank hi)                    //���ѡ��һ�������㷨
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

template<typename T> int Vector<T>::deduplicate()                              //��������ȥ���㷨��ʱ�临�Ӷ�O(n^2)
{
	int old_size = getSize();
	Rank i = 1;
	while (i < getSize())
		(find(element[i], 0, i) < 0) ? i++ : remove(i);
	return old_size - getSize();
}

template<typename T> int Vector<T>::uniquify()                                 //��������ȥ���㷨��ʱ�临�Ӷ�O(n)
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

