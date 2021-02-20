/*********************************************************************************
 *   @file        ListNode.h
 *   @brief       The header file for C++ implemented ListNode
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

template<typename T> class ListNode                                            //�б�ڵ�ģ����
{
public:
	T data;                                                                    //�ڵ����洢������
	ListNode<T>* pred;                                                         //ָ��ǰ���ڵ��ָ��
	ListNode<T>* succ;                                                         //ָ���̽ڵ��ָ��
	//���캯��
	ListNode(T e = static_cast<T>(0), ListNode<T>* p = nullptr, ListNode<T>* s = nullptr);
	//��������
	~ListNode();
	//�����ӿ�
	ListNode<T>* insertAsPred(const T& e);                                     //������ǰ�ڵ�֮ǰ�����½ڵ�
	ListNode<T>* insertAsSucc(const T& e);                                     //������ǰ�ڵ�֮������½ڵ�
};

template<typename T> ListNode<T>::ListNode(T e, ListNode<T>* p, ListNode<T>* s) :data(e), pred(p), succ(s) {}

template<typename T> ListNode<T>::~ListNode()
{
	pred = nullptr;
	succ = nullptr;
}

template<typename T> ListNode<T>* ListNode<T>::insertAsPred(const T& e)
{
	ListNode<T>* x = new ListNode<T>(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}

template<typename T> ListNode<T>* ListNode<T>::insertAsSucc(const T& e)
{
	ListNode<T>* x = new ListNode<T>(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}
