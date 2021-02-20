/*********************************************************************************
 *   @file        SkipListDictionary.h
 *   @brief       The header file for C++ implemented SkipList Dictionary
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "Dictionary.h"
#include "List.h"
#include "QualList.h"
using namespace std;

template<typename K, typename V> class SkipListDictionary : public Dictionary<K, V>, public List<QuadList<K, V>*>   //��ת��ģ����
{
protected:
	//��ת�������㷨
	bool skipSearch(ListNode<QuadList<K, V>*>*& qlist, QuadListNode<K, V>*& p, const K& k);
public:
	int getSize() const;                                                       //��ȡ�ײ�QuadList�Ĺ�ģ
	int getLevel() const;                                                      //��ȡ���
	bool put(K k, V v);                                                        //�����������ת����������ظ�����˲���سɹ�
	V* get(K k);                                                               //��ȡ����
	bool remove(K k);                                                          //ɾ������������ɾ���Ƿ�ɹ�
};

//qlist�Ƕ����б�pָ��qlist���׽ڵ�
template<typename K, typename V> bool SkipListDictionary<K, V>::skipSearch(ListNode<QuadList<K, V>*>*& qlist, QuadListNode<K, V>*& p, const K& k)
{
	while (true)
	{
		while ((p->succ != nullptr) && ((p->entry).key <= k))                  //���׽ڵ���������̽�������������key�򵽴�β�ڱ��ڵ㴦��ֹͣ̽��
			p = p->succ;
		p = p->pred;                                                           //����һ��λ��
		if ((p->pred != nullptr) && ((p->entry).key == k))                     //���pָ��Ľڵ��ʱ����ͷ�ڱ��ڵ���������ؼ���Ϊk��������
			return true;                                                       //�򷵻�true
		qlist = qlist->succ;                                                   //����ת����һ��
		if (qlist->succ == nullptr)                                            //����ѵ���ײ㣬��β�ڱ��ڵ���һ�㣬��ʧ��
			return false;                                                      //�򷵻�false
		p = (p->pred != nullptr) ? p->below : qlist->data->getFirst();         //������pָ��Ľڵ㲢��ͷ�ڱ��ڵ㣬��p�����ƶ�һ����λ
	}                                                                          //������p�ƶ�����ʱqlist��Ӧ����һ���QuadList�ĵ�һ���ڵ㴦
}

template<typename K, typename V> int SkipListDictionary<K, V>::getSize() const //��ȡ�ײ�QuadList�Ĺ�ģ
{
	return (this->isEmpty() == true) ? 0 : this->getLast()->data->getSize();   //��ListΪ�գ���ײ��������ģΪ0�����򣬻�ȡĩ�ڵ�洢��ָ����ָ���������Ĺ�ģ
}

template<typename K, typename V> int SkipListDictionary<K, V>::getLevel() const//��ȡ���
{
	return List<QuadList<K, V>*>::getSize();                                   //ֱ�ӵ���List��getSize()����
}

template<typename K, typename V> bool SkipListDictionary<K, V>::put(K k, V v)  //�����������ת����������ظ�����˲���سɹ�
{
	if (this->isEmpty() == true)                                               //���Ϊ�գ�������׸�������
		this->insertAsFirst(new QuadList<K, V>());
	ListNode<QuadList<K, V>*>* qlist = this->getFirst();                       //�Ӷ���������
	QuadListNode<K, V>* p = qlist->data->getFirst();                           //���׽ڵ����
	if (skipSearch(qlist, p, k) == true)                                       //�����ʵ��Ĳ���λ��(�����ڹؼ���k�����һ���ڵ�p)
		while (p->below != nullptr)                                            //��������ͬ����������ǿ��ת������
			p = p->below;
	qlist = this->getLast();                                                   //���£�������p���Ҳ࣬һ���������Ե׶����������
	QuadListNode<K, V>* b = qlist->data->insertAfterAbove(k, v, p);            //�½ڵ�b����������
	uniform_int_distribution<int> u(0, 1);
	default_random_engine e;
	while (u(e))                                                               //��Ͷ��Ӳ�ң���ȷ��������Ҫ�ٳ���һ�㣬��
	{
		while ((qlist->data->isValid(p) == true) && (p->above == nullptr))     //�ҳ������ڴ˸߶ȵ����ǰ��
			p = p->pred;
		if (qlist->data->isValid(p) == false)                                  //����ǰ����ͷ�ڱ��ڵ�
		{
			if (qlist == this->getFirst())                                     //�ҵ�ǰ������㣬����ζ�ű���
				this->insertAsFirst(new QuadList<K, V>);                       //���ȴ����µ�һ�㣬Ȼ��
			p = qlist->pred->data->getFirst()->pred;                           //��pת����һ��Skiplist��ͷ�ڱ��ڵ�
		}
		else                                                                   //����
			p = p->above;                                                      //�ɽ�p�������ø߶�
		qlist = qlist->pred;                                                   //����һ�㣬���ڸò�
		b = qlist->data->insertAfterAbove(k, v, p, b);                         //���½ڵ����p֮��b֮��
	}
	return true;
}

template<typename K, typename V> V* SkipListDictionary<K, V>::get(K k)         //��ȡ����
{
	if (this->isEmpty() == true)
		return nullptr;
	ListNode<QuadList<K, V>*>* qlist = this->getFirst();                       //�Ӷ����������
	QuadListNode<K, V>* p = qlist->data->getFirst();                           //�׽ڵ㿪ʼ
	return (skipSearch(qlist, p, k) == true) ? &((p->entry).value) : nullptr;  //�ж������ʱ����������
}

template<typename K, typename V> bool SkipListDictionary<K, V>::remove(K k)    //ɾ������������ɾ���Ƿ�ɹ�
{
	if (this->isEmpty() == true)                                               //�ձ����
		return false;
	ListNode<QuadList<K, V>*>* qlist = this->getFirst();                       //�Ӷ����������
	QuadListNode<K, V>* p = qlist->data->getFirst();                           //�׽ڵ㿪ʼ
	if (skipSearch(qlist, p, k) == false)                                      //Ŀ����������ڣ�ֱ�ӷ���false
		return false;
	do                                                                         //��Ŀ��������ڣ����������֮��Ӧ����
	{
		QuadListNode<K, V>* lower = p->below;                                  //��ס��һ��ڵ㣬��
		qlist->data->remove(p);                                                //ɾ����ǰ��ڵ㣬��
		p = lower;                                                             //ת����һ��
		qlist = qlist->succ;
	} while (qlist->succ != nullptr);                                          //���ϲ����ظ���ֱ������
	while ((this->isEmpty() == false) && (this->getFirst()->data->isEmpty() == true)) //��һ��
		List<QuadList<K, V>*>::remove(this->getFirst());                       //����ѿ��ܲ��������Ķ���������
	return true;                                                               //ɾ���ɹ�������true
}



