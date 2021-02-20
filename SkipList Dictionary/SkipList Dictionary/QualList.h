/*********************************************************************************
 *   @file        QuadList.h
 *   @brief       The header file for C++ implemented QuadList
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "QuadListNode.h"

template<typename K, typename V> class QuadList                                //四联表模板类
{
private:
	int size;                                                                  //规模
	QuadListNode<K, V>* header;                                                //指向头哨兵节点的指针
	QuadListNode<K, V>* trailer;                                               //指向尾哨兵节点的指针
protected:
	void init();                                                               //构造时用于初始化的函数
	int clear();                                                               //析构时用于释放资源的函数
public:
	//构造函数
	QuadList();
	//析构函数
	~QuadList();
	//只读访问接口
	int getSize() const;                                                       //获取规模
	bool isEmpty() const;                                                      //判断表是否为空
	QuadListNode<K, V>* getFirst() const;                                      //获取指向第一个节点的指针
	QuadListNode<K, V>* getLast() const;                                       //获取指向最后一个节点的指针
	bool isValid(QuadListNode<K, V>* p) const;                                 //判断一个给定指针是否指向表的合法位置，header和trailer不是合法位置
	//可写访问接口
	V remove(QuadListNode<K, V>* p);                                           //删除指针p指向的节点，返回节点存储的词条的value值
	//将新节点作为p指向的节点的后继，b指向的节点的上邻插入
	QuadListNode<K, V>* insertAfterAbove(const K& k, const V& v, QuadListNode<K, V>* p, QuadListNode<K, V>* b = nullptr);
	//遍历
	template<typename VST> void traverse(VST& visit);
};

template<typename K, typename V> void QuadList<K, V>::init()                   //初始化
{
	header = new QuadListNode<K, V>(static_cast<K>(0));
	trailer = new QuadListNode<K, V>(static_cast<K>(0));
	header->succ = trailer;                                                    //设置各种指针
	header->pred = nullptr;
	trailer->succ = nullptr;
	trailer->pred = header;
	header->above = nullptr;
	header->below = nullptr;
	trailer->above = nullptr;
	trailer->below = nullptr;
	size = 0;
}

template<typename K, typename V> int QuadList<K, V>::clear()
{
	int old_size = getSize();
	while (getSize() > 0)
		remove(header->succ);
	return old_size;
}

template<typename K, typename V> QuadList<K, V>::QuadList()
{
	init();
}

template<typename K, typename V> QuadList<K, V>::~QuadList()
{
	clear();
	delete header;
	header = nullptr;
	delete trailer;
	trailer = nullptr;
}

template<typename K, typename V> int QuadList<K, V>::getSize() const
{
	return size;
}

template<typename K, typename V> bool QuadList<K, V>::isEmpty() const
{
	return !static_cast<bool>(getSize());
}

template<typename K, typename V> QuadListNode<K, V>* QuadList<K, V>::getFirst() const
{
	return header->succ;
}

template<typename K, typename V> QuadListNode<K, V>* QuadList<K, V>::getLast() const
{
	return trailer->pred;
}

template<typename K, typename V> bool QuadList<K, V>::isValid(QuadListNode<K, V>* p) const
{
	QuadListNode<K, V>* q = header->succ;
	while (q != trailer)
	{
		if (q == p)                                                            //只要p指向表中任意一个节点，则p合法
			return true;
		q = q->succ;
	}
	return false;
}

template<typename K, typename V> V QuadList<K, V>::remove(QuadListNode<K, V>* p)      //删除指针p所指向的节点，前提是p指向的位置是合法的
{
	if (isValid(p) == false)                                                   //先判断p是否合法
		return (p->entry).value;
	V res = (p->entry).value;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	p = nullptr;
	size--;
	return res;
}

template<typename K, typename V> QuadListNode<K, V>* QuadList<K, V>::insertAfterAbove(const K& k, const V& v, QuadListNode<K, V>* p, QuadListNode<K, V>* b)
{
	size++;
	return p->insertAsSuccAbove(k, v, b);
}


template<typename K, typename V> template<typename VST> void QuadList<K, V>::traverse(VST& visit)
{
	QuadListNode<K, V>* p = header->succ;
	while (p != trailer)
	{
		visit((p->entry).value);
		p = p->succ;
	}
}


