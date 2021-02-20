/*********************************************************************************
 *   @file        QueueNode.h
 *   @brief       The header file for C++ implemented QueueNode
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

template<typename T> class QueueNode                                           //���нڵ�ģ����
{
public:
	T data;                                                                    //�ڵ����洢������
	QueueNode<T>* pred;                                                        //ָ��ǰ���ڵ��ָ��
	QueueNode<T>* succ;                                                        //ָ���̽ڵ��ָ��
	//���캯��
	QueueNode(T e = static_cast<T>(0), QueueNode<T>* p = nullptr, QueueNode<T>* s = nullptr);
	//��������
	~QueueNode();
	//�����ӿ�
	QueueNode<T>* insertAsPred(const T& e);                                    //������ǰ�ڵ�֮ǰ�����½ڵ�
	QueueNode<T>* insertAsSucc(const T& e);                                    //������ǰ�ڵ�֮������½ڵ�
};

template<typename T> QueueNode<T>::QueueNode(T e, QueueNode<T>* p, QueueNode<T>* s) :data(e), pred(p), succ(s) {}

template<typename T> QueueNode<T>::~QueueNode()
{
	pred = nullptr;
	succ = nullptr;
}

template<typename T> QueueNode<T>* QueueNode<T>::insertAsPred(const T& e)
{
	QueueNode<T>* x = new QueueNode<T>(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}

template<typename T> QueueNode<T>* QueueNode<T>::insertAsSucc(const T& e)
{
	QueueNode<T>* x = new QueueNode<T>(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}
