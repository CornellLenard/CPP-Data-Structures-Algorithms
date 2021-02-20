/*********************************************************************************
 *   @file        List.h
 *   @brief       The header file for C++ implemented List
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "ListNode.h"
#include <random>
using namespace std;

template<typename T> class List                                                //�б�ģ����
{
protected:
	int size;                                                                  //�б��ģ
	ListNode<T>* header;                                                       //ָ���б�ͷ�ڱ��ڵ��ָ��
	ListNode<T>* trailer;                                                      //ָ���б�β�ڱ��ڵ��ָ��
	void init();                                                               //�б���ʱ��ʼ��
	int clear();                                                               //�ͷ��б����нڵ���ռ���ڴ�ռ䣬���ؽڵ�����
	void copyNodes(ListNode<T>* p, int n);                                     //�����б�����λ��p���n��
	void merge(ListNode<T>*& p, int n, List<T>& lst, ListNode<T>* q, int m);   //�鲢�㷨
	void mergeSort(ListNode<T>*& p, int n);                                    //�Դ�p��ʼ������n���ڵ�ʹ�ù鲢�����㷨
	void selectionSort(ListNode<T>* p, int n);                                 //�Դ�p��ʼ������n���ڵ�ʹ��ѡ�������㷨
	ListNode<T>* selectMax(ListNode<T>* p, int n);                             //��p����n-1�������ѡ�����Ԫ�أ�����ָ�����Ԫ�ؽڵ��ָ��
	ListNode<T>* selectMax();                                                  //ѡȡ�����б�����Ԫ�أ�����ָ�����Ԫ�ؽڵ��ָ��
	void insertionSort(ListNode<T>* p, int n);                                 //�Դ�p��ʼ������n���ڵ�ʹ�ò��������㷨
public:
	//���캯��
	List();                                                                    //Ĭ�Ϲ��캯��
	List(const List<T>& lst);                                                  //���帴���б�lst
	List(ListNode<T>* p, int n);                                               //�����б�����λ��p���n��
	//��������
	~List();                                                                   //�ͷ��б���ռ���ڴ�ռ䣬����ͷβ�ڱ��ڵ�
	//ֻ�����ʽӿ�
	int getSize() const;                                                       //��ȡ�б��ģ
	bool isEmpty() const;                                                      //�ж��б��Ƿ�Ϊ��
	ListNode<T>* getFirst() const;                                             //��ȡָ���׽ڵ��ָ�룬������Ϊ��ֵ
	ListNode<T>* getLast() const;                                              //��ȡָ��ĩ�ڵ��ָ�룬������Ϊ��ֵ
	bool isValid(ListNode<T>* p) const;                                        //�жϸ���ָ��p�Ƿ�Ϸ�
	int disordered() const;                                                    //�ж��б��Ƿ������򣬷�������Ԫ���������
	ListNode<T>* find(const T& e) const;                                       //�����б�����㷨
	ListNode<T>* find(const T& e, int n, ListNode<T>* p) const;                //�����б�����㷨����p��n����ǰ����(������p)����==e������ߣ�δ�ҵ��򷵻�nullptr
	ListNode<T>* search(const T& e) const;                                     //�����б�����㷨
	ListNode<T>* search(const T& e, int n, ListNode<T>* p) const;              /*�����б�����㷨����p��n����ǰ����(������p)���ҵ�һ��<=e��Ԫ��
																			   ��δ�ҵ����򷵻ص���ָ��p��n����ǰ�������������һ��λ�õ�ָ��*/
																			   //��д���ʽӿ�
	ListNode<T>* insertAsFirst(const T& e);                                    //��e�����׽ڵ���룬����ָ���½ڵ��ָ��
	ListNode<T>* insertAsLast(const T& e);                                     //��e����ĩ�ڵ���룬����ָ���½ڵ��ָ��
	ListNode<T>* insertAfter(ListNode<T>* p, const T& e);                      //��e����p�ĺ�̲��룬����ָ���½ڵ��ָ��
	ListNode<T>* insertBefore(ListNode<T>* p, const T& e);                     //��e����p��ǰ�����룬����ָ���½ڵ��ָ��
	T remove(ListNode<T>* p);                                                  //ɾ���Ϸ�λ��p���Ľڵ㣬���ر�ɾ���ڵ�洢������
	int remove(const T& e);                                                    //ɾ���б���ȫ������==e�Ľڵ㣬������ɾ���Ľڵ����
	void merge(List<T>& lst);                                                  //ȫ�б�鲢�㷨
	void sort();                                                               //�б���������
	int deduplicate();                                                         //�����б�ȥ���㷨������ȥ����ɾ���Ľڵ���
	int uniquify();                                                            //�����б�ȥ���㷨������ȥ����ɾ���Ľڵ���
	void reverse();                                                            //��ת�б��㷨
	//����
	template<typename VST> void traverse(VST& visit);                          //ʹ�ú������󣬶��б���б�������
};

template<typename T> void List<T>::init()
{
	header = new ListNode<T>();
	trailer = new ListNode<T>();
	header->succ = trailer;
	header->pred = nullptr;
	trailer->succ = nullptr;
	trailer->pred = header;
	size = 0;
}

template<typename T> int List<T>::clear()
{
	int old_size = getSize();
	while (getSize() > 0)
		remove(header->succ);
	return old_size;
}

template<typename T> void List<T>::copyNodes(ListNode<T>* p, int n)
{
	init();
	while (n > 0)
	{
		insertAsLast(p->data);
		p = p->succ;
		n--;
	}
}

template<typename T> void List<T>::merge(ListNode<T>*& p, int n, List<T>& lst, ListNode<T>* q, int m)     //�鲢�㷨��p���ֺ�q���־��������򣬴�����Ϻ���������
{
	ListNode<T>* pp = p->pred;
	while (m > 0)                                                              //q���ִ������ʱ��p���ֵ�δ������������λ�þ���������ȷλ��
	{
		if ((n > 0) && (p->data <= q->data))                                   //p��q�����־�δ���������p->data <= q->dataʱ
		{
			p = p->succ;                                                       //p����һ��λ��
			if (p == q)                                                        //���p��ʱ��q��һ��λ�ã�����ζ��p��q����������������������ֱ��break
				break;
			n--;                                                               //p���ֵ�δ�����ֹ�ģ-1
		}
		else
		{
			insertBefore(p, lst.remove((q = q->succ)->pred));                  //��qָ���Ԫ�ز���p���ֵ���ȷλ��
			m--;                                                               //q���ֵ�δ�����ֹ�ģ-1
		}
	}
	p = pp->succ;
}

template<typename T> void List<T>::mergeSort(ListNode<T>*& p, int n)           //�鲢�����㷨
{
	if (n <= 1)
		return;
	int m = n / 2;
	ListNode<T>* q = p;
	for (int i = 0; i < m; i++)                                                //qҪ�ƶ����б���м�λ��
		q = q->succ;
	mergeSort(p, m);                                                           //��·�鲢
	mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);
}

template<typename T> void List<T>::selectionSort(ListNode<T>* p, int n)        //ѡ�������㷨
{
	ListNode<T>* head = p->pred;
	ListNode<T>* tail = p;
	for (int i = 0; i < n; i++)
		tail = tail->succ;
	ListNode<T>* max = nullptr;
	while (n > 1)
	{
		max = selectMax(head->succ, n);                                        //�ҵ����Ԫ�ؽڵ�
		insertBefore(tail, remove(max));                                       //��tail��ǰһ��λ�ò����½ڵ㣬�½ڵ�����ݾ������Ԫ�ؽڵ������ֵ
		tail = tail->pred;                                                     //tailǰ��һ��λ��
		n--;
	}
}

template<typename T> ListNode<T>* List<T>::selectMax(ListNode<T>* p, int n)
{
	ListNode<T>* max = p;
	ListNode<T>* q = max->succ;
	while (n > 1)
	{
		if (q->data >= max->data)                                              //ע���ж�������>=���������Ԫ���ж��ʱ��ȡ��������ߣ�����Ϊ��֤�����ȶ���
			max = q;
		q = q->succ;
		n--;
	}
	return max;
}

template<typename T> ListNode<T>* List<T>::selectMax()
{
	return selectMax(header->succ, getSize());
}

template<typename T> void List<T>::insertionSort(ListNode<T>* p, int n)
{
	for (int i = 0; i < n; i++)
	{
		insertAfter(search(p->data, i, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}

template<typename T> List<T>::List()
{
	init();
}

template<typename T> List<T>::List(ListNode<T>* p, int n)
{
	copyNodes(p, n);
}

template<typename T> List<T>::List(const List<T>& lst)
{
	copyNodes((lst.header)->succ, lst.size);
}

template<typename T> List<T>::~List()
{
	clear();
	delete header;
	header = nullptr;
	delete trailer;
	trailer = nullptr;
}

template<typename T> int List<T>::getSize() const
{
	return size;
}

template<typename T> bool List<T>::isEmpty() const
{
	return !static_cast<bool>(getSize());
}

template<typename T> ListNode<T>* List<T>::getFirst() const
{
	return header->succ;
}

template<typename T> ListNode<T>* List<T>::getLast() const
{
	return trailer->pred;
}

template<typename T> bool List<T>::isValid(ListNode<T>* p) const               //�ж�һ������ָ���Ƿ�ָ���б�ĺϷ�λ�ã�header��trailer���ǺϷ�λ��
{
	ListNode<T>* q = header->succ;
	while (q != trailer)
	{
		if (q == p)                                                            //ֻҪpָ���б�������һ���ڵ㣬��p�Ϸ�
			return true;
		q = q->succ;
	}
	return false;
}

template<typename T> int List<T>::disordered() const
{
	ListNode<T>* p = getFirst()->succ;
	int count = 0;
	while (p != trailer)
	{
		if (p->pred->data > p->data)
			count++;
		p = p->succ;
	}
	return count;
}

template<typename T> ListNode<T>* List<T>::find(const T& e) const
{
	return find(e, getSize(), trailer);
}

template<typename T> ListNode<T>* List<T>::find(const T& e, int n, ListNode<T>* p) const        //�����б�����㷨��ע��ӿ����壬��δ�ҵ��򷵻�nullptr
{
	while (n > 0)
	{
		p = p->pred;
		if (p->data == e)
			return p;
		n--;
	}
	return nullptr;
}

template<typename T> ListNode<T>* List<T>::search(const T& e) const
{
	return search(e, getSize(), trailer);
}

template<typename T> ListNode<T>* List<T>::search(const T& e, int n, ListNode<T>* p) const      //�����б�����㷨������p����һ��<=e��Ԫ��
{
	while (n >= 0)                                                             //ע��ӿ����壬��δ�ҵ����򷵻ص���ָ��p��n����ǰ�������������һ��λ�õ�ָ��
	{
		p = p->pred;
		if ((p->data) <= e)
			break;
		n--;
	}
	return p;
}

template<typename T> ListNode<T>* List<T>::insertAsFirst(const T& e)           //�����㷨ֱ�ӵ��ö�Ӧ�ڵ�Ķ�Ӧ�����㷨����
{
	size++;
	return header->insertAsSucc(e);
}

template<typename T> ListNode<T>* List<T>::insertAsLast(const T& e)
{
	size++;
	return trailer->insertAsPred(e);
}

template<typename T> ListNode<T>* List<T>::insertAfter(ListNode<T>* p, const T& e)
{
	size++;
	return p->insertAsSucc(e);
}

template<typename T> ListNode<T>* List<T>::insertBefore(ListNode<T>* p, const T& e)
{
	size++;
	return p->insertAsPred(e);
}

template<typename T> T List<T>::remove(ListNode<T>* p)                         //ɾ��ָ��p��ָ��Ľڵ㣬ǰ����pָ���λ���ǺϷ���
{
	if (isValid(p) == false)                                                   //���ж�p�Ƿ�Ϸ�
		return p->data;
	T res = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	p = nullptr;
	size--;
	return res;
}

template<typename T> int List<T>::remove(const T& e)
{
	ListNode<T>* p = header->succ;
	int count = 0;
	while (p != trailer)
	{
		p = p->succ;
		if (p->pred->data == e)
		{
			remove(p->pred);
			count++;
		}
	}
	return count;
}

template<typename T> void List<T>::merge(List<T>& lst)                         //�б�����鲢�㷨
{
	merge(header->succ, getSize(), lst, (lst.header)->succ, lst.getSize());
}

template<typename T> void List<T>::sort()                                      //���ѡ��һ�������㷨
{
	uniform_int_distribution<int> u(0, 2);
	default_random_engine e;
	ListNode<T>* p = header->succ;
	switch (u(e))
	{
	case 0:insertionSort(p, getSize()); break;
	case 1:selectionSort(p, getSize()); break;
	case 2:mergeSort(p, getSize()); break;
	}
}

template<typename T> int List<T>::deduplicate()                                //�����б�ȥ���㷨��ʱ�临�Ӷ�O(n^2)
{
	if (getSize() <= 1)
		return 0;
	int old_size = getSize();
	ListNode<T>* p = header->succ;
	int r = 0;
	ListNode<T>* q = nullptr;
	while (p != trailer)                                                       //ÿ��ѭ����Ҫ����find()����p֮ǰ��Ԫ�������޺�p����һ����
	{
		q = find(p->data, r, p);
		(q != nullptr) ? remove(q) : r++;
		p = p->succ;
	}
	return old_size - getSize();
}

template<typename T> int List<T>::uniquify()                                   //�����б�ȥ���㷨��ʱ�临�Ӷ�O(n)
{
	if (getSize() <= 1)
		return 0;
	int old_size = getSize();
	ListNode<T>* p = header->succ;
	ListNode<T>* q = p->succ;
	while (q != trailer)
	{
		if (p->data == q->data)
			remove(q);
		else
			p = q;
		q = p->succ;
	}
	return old_size - getSize();
}

template<typename T> void List<T>::reverse()                                   //��ת�б��㷨����ʵ������ķ�ת���ڵ㣬��ÿһ����ֵ����������
{
	ListNode<T>* p = header->succ;
	ListNode<T>* q = trailer->pred;
	T temp;
	int n = getSize() / 2;
	while (n > 0)
	{
		temp = p->data;
		p->data = q->data;
		q->data = temp;
		p = p->succ;
		q = q->pred;
		n--;
	}
}

template<typename T> template<typename VST> void List<T>::traverse(VST& visit)
{
	ListNode<T>* p = header->succ;
	while (p != trailer)
	{
		visit(p->data);
		p = p->succ;
	}
}
