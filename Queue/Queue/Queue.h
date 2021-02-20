/*********************************************************************************
 *   @file        Queue.h
 *   @brief       The header file for C++ implemented Queue
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "QueueNode.h"
#include "QueueUnderflowException.h"
using namespace std;

template<typename T> class Queue                                               //����ģ����
{
protected:
	int size;                                                                  //���й�ģ
	QueueNode<T>* header;                                                      //ָ�����ͷ�ڱ��ڵ��ָ��
	QueueNode<T>* trailer;                                                     //ָ�����β�ڱ��ڵ��ָ��
	void init();                                                               //���д���ʱ��ʼ��
	int clear();                                                               //�ͷŶ������нڵ���ռ���ڴ�ռ�
	void copyNodes(QueueNode<T>* p, int n);                                    //���ƶ�������λ��p���n��
	QueueNode<T>* getFirst() const;                                            //��ȡָ���׽ڵ��ָ��
	QueueNode<T>* getLast() const;                                             //��ȡָ��ĩ�ڵ��ָ��
	QueueNode<T>* insertAsFirst(const T& e);                                   //��e�����׽ڵ���룬���ز����ָ���½ڵ��ָ��
	QueueNode<T>* insertAsLast(const T& e);                                    //��e����ĩ�ڵ���룬���ز����ָ���½ڵ��ָ��
	QueueNode<T>* insertAfter(QueueNode<T>* p, const T& e);                    //��e����p�ĺ�̲��룬���ز����ָ���½ڵ��ָ��
	QueueNode<T>* insertBefore(QueueNode<T>* p, const T& e);                   //��e����p��ǰ�����룬���ز����ָ���½ڵ��ָ��
	T remove(QueueNode<T>* p);                                                 //ɾ���Ϸ�λ��p���Ľڵ㣬���ر�ɾ���ڵ�洢������
public:
	//���캯��
	Queue();                                                                   //Ĭ�Ϲ��캯��
	Queue(const Queue<T>& q);                                                  //���帴�ƶ���q
	Queue(QueueNode<T>* p, int n);                                             //���ƶ�������λ��p���n��
	//��������
	~Queue();                                                                  //�ͷŶ�����ռ���ڴ�ռ䣬����ͷβ�ڱ��ڵ�
	//ֻ�����ʽӿ�
	int getSize() const;                                                       //��ȡ���й�ģ
	bool isEmpty() const;                                                      //�ж϶����Ƿ�Ϊ��
	//��д���ʽӿ�
	void enqueue(const T& e);                                                  //���
	T dequeue();                                                               //����
	T& getFront();                                                             //���ö���Ԫ��
};

template<typename T> void Queue<T>::init()
{
	header = new QueueNode<T>();
	trailer = new QueueNode<T>();
	header->succ = trailer;
	header->pred = nullptr;
	trailer->succ = nullptr;
	trailer->pred = header;
	size = 0;
}

template<typename T> int Queue<T>::clear()
{
	int old_size = getSize();
	while (getSize() > 0)
		remove(header->succ);
	return old_size;
}

template<typename T> void Queue<T>::copyNodes(QueueNode<T>* p, int n)
{
	init();
	while (n > 0)
	{
		insertAsLast(p->data);
		p = p->succ;
		n--;
	}
}

template<typename T> QueueNode<T>* Queue<T>::getFirst() const
{
	return header->succ;
}

template<typename T> QueueNode<T>* Queue<T>::getLast() const
{
	return trailer->pred;
}

template<typename T> QueueNode<T>* Queue<T>::insertAsFirst(const T& e)         //���ֲ��뺯�����ǵ��ö�Ӧ�ڵ�Ķ�Ӧ���뺯��
{
	size++;
	return header->insertAsSucc(e);
}

template<typename T> QueueNode<T>* Queue<T>::insertAsLast(const T& e)
{
	size++;
	return trailer->insertAsPred(e);
}

template<typename T> QueueNode<T>* Queue<T>::insertAfter(QueueNode<T>* p, const T& e)
{
	size++;
	return p->insertAsSucc(e);
}

template<typename T> QueueNode<T>* Queue<T>::insertBefore(QueueNode<T>* p, const T& e)
{
	size++;
	return p->insertAsPred(e);
}

template<typename T> T Queue<T>::remove(QueueNode<T>* p)
{
	T res = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	p = nullptr;
	size--;
	return res;
}

template<typename T> Queue<T>::Queue()
{
	init();
}

template<typename T> Queue<T>::Queue(QueueNode<T>* p, int n)
{
	copyNodes(p, n);
}

template<typename T> Queue<T>::Queue(const Queue<T>& q)
{
	copyNodes((q.header)->succ, q.size);
}

template<typename T> Queue<T>::~Queue()
{
	clear();
	delete header;
	header = nullptr;
	delete trailer;
	trailer = nullptr;
}

template<typename T> int Queue<T>::getSize() const
{
	return size;
}

template<typename T> bool Queue<T>::isEmpty() const
{
	return !static_cast<bool>(getSize());
}

template<typename T> void Queue<T>::enqueue(const T& e)                        //���ֱ�ӵ���insertAsLast()����
{
	insertAsLast(e);
}

template<typename T> T Queue<T>::dequeue()                                     //������Ҫ���жϴ�ʱ�����Ƿ�Ϊ�գ�Ϊ�����׳��쳣
{
	if (getSize() == 0)
		throw QueueUnderflowException();
	return remove(header->succ);
}

template<typename T> T& Queue<T>::getFront()                                   //getFront()��Ҫ���жϴ�ʱ�����Ƿ�Ϊ�գ�Ϊ�����׳��쳣
{
	if (getSize() == 0)
		throw QueueUnderflowException();
	return header->succ->data;
}
