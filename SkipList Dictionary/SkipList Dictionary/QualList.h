/*********************************************************************************
 *   @file        QuadList.h
 *   @brief       The header file for C++ implemented QuadList
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "QuadListNode.h"

template<typename K, typename V> class QuadList                                //������ģ����
{
private:
	int size;                                                                  //��ģ
	QuadListNode<K, V>* header;                                                //ָ��ͷ�ڱ��ڵ��ָ��
	QuadListNode<K, V>* trailer;                                               //ָ��β�ڱ��ڵ��ָ��
protected:
	void init();                                                               //����ʱ���ڳ�ʼ���ĺ���
	int clear();                                                               //����ʱ�����ͷ���Դ�ĺ���
public:
	//���캯��
	QuadList();
	//��������
	~QuadList();
	//ֻ�����ʽӿ�
	int getSize() const;                                                       //��ȡ��ģ
	bool isEmpty() const;                                                      //�жϱ��Ƿ�Ϊ��
	QuadListNode<K, V>* getFirst() const;                                      //��ȡָ���һ���ڵ��ָ��
	QuadListNode<K, V>* getLast() const;                                       //��ȡָ�����һ���ڵ��ָ��
	bool isValid(QuadListNode<K, V>* p) const;                                 //�ж�һ������ָ���Ƿ�ָ���ĺϷ�λ�ã�header��trailer���ǺϷ�λ��
	//��д���ʽӿ�
	V remove(QuadListNode<K, V>* p);                                           //ɾ��ָ��pָ��Ľڵ㣬���ؽڵ�洢�Ĵ�����valueֵ
	//���½ڵ���Ϊpָ��Ľڵ�ĺ�̣�bָ��Ľڵ�����ڲ���
	QuadListNode<K, V>* insertAfterAbove(const K& k, const V& v, QuadListNode<K, V>* p, QuadListNode<K, V>* b = nullptr);
	//����
	template<typename VST> void traverse(VST& visit);
};

template<typename K, typename V> void QuadList<K, V>::init()                   //��ʼ��
{
	header = new QuadListNode<K, V>(static_cast<K>(0));
	trailer = new QuadListNode<K, V>(static_cast<K>(0));
	header->succ = trailer;                                                    //���ø���ָ��
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
		if (q == p)                                                            //ֻҪpָ���������һ���ڵ㣬��p�Ϸ�
			return true;
		q = q->succ;
	}
	return false;
}

template<typename K, typename V> V QuadList<K, V>::remove(QuadListNode<K, V>* p)      //ɾ��ָ��p��ָ��Ľڵ㣬ǰ����pָ���λ���ǺϷ���
{
	if (isValid(p) == false)                                                   //���ж�p�Ƿ�Ϸ�
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


