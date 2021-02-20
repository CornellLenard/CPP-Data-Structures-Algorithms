/*********************************************************************************
 *   @file        List.h
 *   @brief       The header file for C++ implemented List
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "ListNode.h"
#include <random>
using namespace std;

template<typename T> class List                                                //列表模板类
{
protected:
	int size;                                                                  //列表规模
	ListNode<T>* header;                                                       //指向列表头哨兵节点的指针
	ListNode<T>* trailer;                                                      //指向列表尾哨兵节点的指针
	void init();                                                               //列表创建时初始化
	int clear();                                                               //释放列表所有节点所占的内存空间，返回节点数量
	void copyNodes(ListNode<T>* p, int n);                                     //复制列表中自位置p起的n项
	void merge(ListNode<T>*& p, int n, List<T>& lst, ListNode<T>* q, int m);   //归并算法
	void mergeSort(ListNode<T>*& p, int n);                                    //对从p开始连续的n个节点使用归并排序算法
	void selectionSort(ListNode<T>* p, int n);                                 //对从p开始连续的n个节点使用选择排序算法
	ListNode<T>* selectMax(ListNode<T>* p, int n);                             //在p及其n-1个后继中选出最大元素，返回指向最大元素节点的指针
	ListNode<T>* selectMax();                                                  //选取整个列表的最大元素，返回指向最大元素节点的指针
	void insertionSort(ListNode<T>* p, int n);                                 //对从p开始连续的n个节点使用插入排序算法
public:
	//构造函数
	List();                                                                    //默认构造函数
	List(const List<T>& lst);                                                  //整体复制列表lst
	List(ListNode<T>* p, int n);                                               //复制列表中自位置p起的n项
	//析构函数
	~List();                                                                   //释放列表所占的内存空间，包括头尾哨兵节点
	//只读访问接口
	int getSize() const;                                                       //获取列表规模
	bool isEmpty() const;                                                      //判断列表是否为空
	ListNode<T>* getFirst() const;                                             //获取指向首节点的指针，不可作为左值
	ListNode<T>* getLast() const;                                              //获取指向末节点的指针，不可作为左值
	bool isValid(ListNode<T>* p) const;                                        //判断给定指针p是否合法
	int disordered() const;                                                    //判断列表是否已有序，返回相邻元素逆序对数
	ListNode<T>* find(const T& e) const;                                       //无序列表查找算法
	ListNode<T>* find(const T& e, int n, ListNode<T>* p) const;                //无序列表查找算法，在p的n个真前驱中(不包括p)查找==e的最靠右者，未找到则返回nullptr
	ListNode<T>* search(const T& e) const;                                     //有序列表查找算法
	ListNode<T>* search(const T& e, int n, ListNode<T>* p) const;              /*有序列表查找算法，在p的n个真前驱中(不包括p)查找第一个<=e的元素
																			   若未找到，则返回的是指向p的n个真前驱最靠左者再向左一个位置的指针*/
																			   //可写访问接口
	ListNode<T>* insertAsFirst(const T& e);                                    //将e当作首节点插入，返回指向新节点的指针
	ListNode<T>* insertAsLast(const T& e);                                     //将e当作末节点插入，返回指向新节点的指针
	ListNode<T>* insertAfter(ListNode<T>* p, const T& e);                      //将e当作p的后继插入，返回指向新节点的指针
	ListNode<T>* insertBefore(ListNode<T>* p, const T& e);                     //将e当作p的前驱插入，返回指向新节点的指针
	T remove(ListNode<T>* p);                                                  //删除合法位置p处的节点，返回被删除节点存储的数据
	int remove(const T& e);                                                    //删除列表中全部数据==e的节点，返回所删除的节点个数
	void merge(List<T>& lst);                                                  //全列表归并算法
	void sort();                                                               //列表整体排序
	int deduplicate();                                                         //无序列表去重算法，返回去重所删除的节点数
	int uniquify();                                                            //有序列表去重算法，返回去重所删除的节点数
	void reverse();                                                            //反转列表算法
	//遍历
	template<typename VST> void traverse(VST& visit);                          //使用函数对象，对列表进行遍历访问
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

template<typename T> void List<T>::merge(ListNode<T>*& p, int n, List<T>& lst, ListNode<T>* q, int m)     //归并算法，p部分和q部分均各自有序，处理完毕后整体有序
{
	ListNode<T>* pp = p->pred;
	while (m > 0)                                                              //q部分处理完毕时，p部分的未处理部分所处的位置就是最终正确位置
	{
		if ((n > 0) && (p->data <= q->data))                                   //p和q两部分均未处理完毕且p->data <= q->data时
		{
			p = p->succ;                                                       //p后移一个位置
			if (p == q)                                                        //如果p此时和q是一个位置，则意味着p和q连接上了且已整体有序，则直接break
				break;
			n--;                                                               //p部分的未处理部分规模-1
		}
		else
		{
			insertBefore(p, lst.remove((q = q->succ)->pred));                  //将q指向的元素插入p部分的正确位置
			m--;                                                               //q部分的未处理部分规模-1
		}
	}
	p = pp->succ;
}

template<typename T> void List<T>::mergeSort(ListNode<T>*& p, int n)           //归并排序算法
{
	if (n <= 1)
		return;
	int m = n / 2;
	ListNode<T>* q = p;
	for (int i = 0; i < m; i++)                                                //q要移动到列表的中间位置
		q = q->succ;
	mergeSort(p, m);                                                           //二路归并
	mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);
}

template<typename T> void List<T>::selectionSort(ListNode<T>* p, int n)        //选择排序算法
{
	ListNode<T>* head = p->pred;
	ListNode<T>* tail = p;
	for (int i = 0; i < n; i++)
		tail = tail->succ;
	ListNode<T>* max = nullptr;
	while (n > 1)
	{
		max = selectMax(head->succ, n);                                        //找到最大元素节点
		insertBefore(tail, remove(max));                                       //在tail的前一个位置插入新节点，新节点的数据就是最大元素节点的数据值
		tail = tail->pred;                                                     //tail前移一个位置
		n--;
	}
}

template<typename T> ListNode<T>* List<T>::selectMax(ListNode<T>* p, int n)
{
	ListNode<T>* max = p;
	ListNode<T>* q = max->succ;
	while (n > 1)
	{
		if (q->data >= max->data)                                              //注意判断条件是>=，即当最大元素有多个时，取其中最靠右者，这是为保证排序稳定性
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

template<typename T> bool List<T>::isValid(ListNode<T>* p) const               //判断一个给定指针是否指向列表的合法位置，header和trailer不是合法位置
{
	ListNode<T>* q = header->succ;
	while (q != trailer)
	{
		if (q == p)                                                            //只要p指向列表中任意一个节点，则p合法
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

template<typename T> ListNode<T>* List<T>::find(const T& e, int n, ListNode<T>* p) const        //无序列表查找算法，注意接口语义，若未找到则返回nullptr
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

template<typename T> ListNode<T>* List<T>::search(const T& e, int n, ListNode<T>* p) const      //有序列表查找算法，返回p左侧第一个<=e的元素
{
	while (n >= 0)                                                             //注意接口语义，若未找到，则返回的是指向p的n个真前驱最靠左者再向左一个位置的指针
	{
		p = p->pred;
		if ((p->data) <= e)
			break;
		n--;
	}
	return p;
}

template<typename T> ListNode<T>* List<T>::insertAsFirst(const T& e)           //插入算法直接调用对应节点的对应插入算法即可
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

template<typename T> T List<T>::remove(ListNode<T>* p)                         //删除指针p所指向的节点，前提是p指向的位置是合法的
{
	if (isValid(p) == false)                                                   //先判断p是否合法
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

template<typename T> void List<T>::merge(List<T>& lst)                         //列表整体归并算法
{
	merge(header->succ, getSize(), lst, (lst.header)->succ, lst.getSize());
}

template<typename T> void List<T>::sort()                                      //随机选择一种排序算法
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

template<typename T> int List<T>::deduplicate()                                //无序列表去重算法，时间复杂度O(n^2)
{
	if (getSize() <= 1)
		return 0;
	int old_size = getSize();
	ListNode<T>* p = header->succ;
	int r = 0;
	ListNode<T>* q = nullptr;
	while (p != trailer)                                                       //每次循环都要调用find()来找p之前的元素中有无和p数据一样的
	{
		q = find(p->data, r, p);
		(q != nullptr) ? remove(q) : r++;
		p = p->succ;
	}
	return old_size - getSize();
}

template<typename T> int List<T>::uniquify()                                   //有序列表去重算法，时间复杂度O(n)
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

template<typename T> void List<T>::reverse()                                   //反转列表算法，其实不用真的反转各节点，把每一对数值交换就行了
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
