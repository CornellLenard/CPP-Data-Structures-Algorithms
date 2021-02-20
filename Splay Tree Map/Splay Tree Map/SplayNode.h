/*********************************************************************************
 *   @file        SplayNode.h
 *   @brief       The header file for C++ implemented SplayNode
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include <random>
#include <stack>
#include <deque>
using namespace std;

typedef enum { RB_RED, RB_BLACK } RBColor;                                     //�ڵ���ɫ

template<typename K, typename V> class SplayNode                               //��չ���ڵ�ģ����
{
public:
	K key;                                                                     //��չ���ڵ����洢�Ĺؼ���
	V value;                                                                   //��չ���ڵ����洢������
	SplayNode<K, V>* parent;                                                   //ָ��ĸ�׽ڵ��ָ��
	SplayNode<K, V>* lc;                                                       //ָ�����ӽڵ��ָ��
	SplayNode<K, V>* rc;                                                       //ָ���Һ��ӽڵ��ָ��
	int height;                                                                //�߶�
	int npl;                                                                   //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height����
	RBColor color;                                                             //��ɫ�����ں����
	//�����жϽڵ����ʵĺ���
	static bool isRoot(const SplayNode<K, V>& sn);                             //�ж�sn�ڵ��Ƿ��Ǹ��ڵ�
	static bool isLChild(const SplayNode<K, V>& sn);                           //�ж�sn�ڵ��Ƿ������ӽڵ�
	static bool isRChild(const SplayNode<K, V>& sn);                           //�ж�sn�ڵ��Ƿ����Һ��ӽڵ�
	static bool hasParent(const SplayNode<K, V>& sn);                          //�ж�sn�ڵ��Ƿ���ĸ�׽ڵ�
	static bool hasLChild(const SplayNode<K, V>& sn);                          //�ж�sn�ڵ��Ƿ�������
	static bool hasRChild(const SplayNode<K, V>& sn);                          //�ж�sn�ڵ��Ƿ����Һ���
	static bool hasChild(const SplayNode<K, V>& sn);                           //�ж�sn�ڵ��Ƿ��к���
	static bool hasBothChild(const SplayNode<K, V>& sn);                       //�ж�sn�ڵ��Ƿ�������������Һ���
	static bool isLeaf(const SplayNode<K, V>& sn);                             //�ж�sn�ڵ��Ƿ���Ҷ�ӽڵ�
	static SplayNode<K, V>* sibling(SplayNode<K, V>* x);                       //��ȡxָ��Ľڵ���ֵܽڵ�
	static int getStature(SplayNode<K, V>* x);                                 //��ȡxָ��Ľڵ�ĸ߶ȣ���"�����߶�Ϊ-1"��Լ����ͳһ
	//���캯��
	SplayNode(K k, V v = static_cast<V>(0), SplayNode<K, V>* p = nullptr, SplayNode<K, V>* l = nullptr, SplayNode<K, V>* r = nullptr, int h = 0, int n = 1, RBColor c = RB_RED);
	//�����ӿ�
	int getSize();                                                             //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
	SplayNode<K, V>* getSucc();                                                //��ȡ��ǰ�ڵ���������������µ�ֱ�Ӻ��
	template<typename VST> void traverseLevel(VST& visit);                     //��α����㷨
	template<typename VST> void traverseIn(VST& visit);                        //��������㷨
	//�Ƚ������е�����������һ����������в���
	bool operator < (const SplayNode<K, V>& sn);
	bool operator == (const SplayNode<K, V>& sn);
protected:
	void goAlongLeftBranch(SplayNode<K, V>* x, stack<SplayNode<K, V>*>& s);    //�����汾��������㷨���踨������
	template<typename VST> void traverseInI1(SplayNode<K, V>* x, VST& visit);  //��xָ��Ľڵ�����е�һ�ֵ����汾��������㷨
	template<typename VST> void traverseInI2(SplayNode<K, V>* x, VST& visit);  //��xָ��Ľڵ�����еڶ��ֵ����汾��������㷨
	template<typename VST> void traverseInI3(SplayNode<K, V>* x, VST& visit);  //��xָ��Ľڵ�����е����ֵ����汾��������㷨
	template<typename VST> void traverseInR(SplayNode<K, V>* x, VST& visit);   //��xָ��Ľڵ�����еݹ�汾��������㷨
};

template<typename K, typename V> bool SplayNode<K, V>::isRoot(const SplayNode<K, V>& sn)
{
	return sn.parent == nullptr;
}

template<typename K, typename V> bool SplayNode<K, V>::isLChild(const SplayNode<K, V>& sn)
{
	return (isRoot(sn) == false) && ((sn.parent)->lc == &sn);
}

template<typename K, typename V> bool SplayNode<K, V>::isRChild(const SplayNode<K, V>& sn)
{
	return (isRoot(sn) == false) && ((sn.parent)->rc == &sn);
}

template<typename K, typename V> bool SplayNode<K, V>::hasParent(const SplayNode<K, V>& sn)
{
	return isRoot(sn) == false;
}

template<typename K, typename V> bool SplayNode<K, V>::hasLChild(const SplayNode<K, V>& sn)
{
	return sn.lc != nullptr;
}

template<typename K, typename V> bool SplayNode<K, V>::hasRChild(const SplayNode<K, V>& sn)
{
	return sn.rc != nullptr;
}

template<typename K, typename V> bool SplayNode<K, V>::hasChild(const SplayNode<K, V>& sn)
{
	return hasLChild(sn) == true || hasRChild(sn) == true;
}

template<typename K, typename V> bool SplayNode<K, V>::hasBothChild(const SplayNode<K, V>& sn)
{
	return hasLChild(sn) == true && hasRChild(sn) == true;
}

template<typename K, typename V> bool SplayNode<K, V>::isLeaf(const SplayNode<K, V>& sn)
{
	return hasChild(sn) == false;
}

template<typename K, typename V> SplayNode<K, V>* SplayNode<K, V>::sibling(SplayNode<K, V>* x)
{
	return (isLChild(*x) == true) ? x->parent->rc : x->parent->lc;
}

template<typename K, typename V> int SplayNode<K, V>::getStature(SplayNode<K, V>* x)  //��ȡxָ��Ľڵ�ĸ߶ȣ���"�����߶�Ϊ-1"��Լ����ͳһ
{
	return (x != nullptr) ? x->height : -1;
}

template<typename K, typename V> SplayNode<K, V>::SplayNode(K k, V v, SplayNode<K, V>* p, SplayNode<K, V>* l, SplayNode<K, V>* r, int h, int n, RBColor c) :
	key(k), value(v), parent(p), lc(l), rc(r), height(h), npl(n), color(c) {}


template<typename K, typename V> int SplayNode<K, V>::getSize()                //��ȡ�Ե�ǰ�ڵ�Ϊ���ڵ�������Ĺ�ģ�������˵ݹ�ʵ��
{
	int count = 1;
	if (lc != nullptr)
		count += lc->getSize();
	if (rc != nullptr)
		count += rc->getSize();
	return count;
}

template<typename K, typename V> SplayNode<K, V>* SplayNode<K, V>::getSucc()   //��ȡָ��ǰ�ڵ���������������µ�ֱ�Ӻ�̽ڵ��ָ��
{
	SplayNode<K, V>* s = this;
	if (rc != nullptr)                                                         //�����ǰ�ڵ����Һ��ӣ���ֱ�Ӻ��Ϊ���Һ���Ϊ���ڵ�������������ͨ·��ͷ�ڵ�
	{
		s = rc;                                                                //�������Һ���Ϊ���ڵ������
		while (SplayNode<K, V>::hasLChild(*s) == true)                         //ǰ�������ͨ·��ͷ
			s = s->lc;
	}
	else                                                                       //���򣬵�ǰ�ڵ��ֱ�Ӻ��Ϊ�����ϵ�һ�������Һ��ӵ����ȵ�ĸ�׽ڵ�
	{
		while (SplayNode<K, V>::isRChild(*s) == true)
			s = s->parent;
		s = s->parent;
	}
	return s;
}

template<typename K, typename V> template<typename VST> void SplayNode<K, V>::traverseLevel(VST& visit)   //��α����㷨�Ƚ�ֱ���׶����Ͳ���׸����
{
	deque<SplayNode<K, V>*> q;
	q.push_back(this);
	SplayNode<K, V>* x = nullptr;
	while (q.empty() == false)
	{
		x = q.pop_front();
		visit(x->value);
		if (SplayNode<K, V>::hasLChild(*x) == true)
			q.push_back(x->lc);
		if (SplayNode<K, V>::hasRChild(*x) == true)
			q.push_back(x->rc);
	}
}

template<typename K, typename V> template<typename VST> void SplayNode<K, V>::traverseIn(VST& visit)      //��������㷨���ѡ��һ��
{
	uniform_int_distribution<int> u(0, 3);
	default_random_engine e;
	switch (u(e))
	{
	case 0:traverseInI1(this, visit); break;
	case 1:traverseInI2(this, visit); break;
	case 2:traverseInI3(this, visit); break;
	case 3:traverseInR(this, visit); break;
	}
}

template<typename K, typename V> bool SplayNode<K, V>::operator < (const SplayNode<K, V>& sn)
{
	return key < sn.key;
}

template<typename K, typename V> bool SplayNode<K, V>::operator == (const SplayNode<K, V>& sn)
{
	return key == sn.key;
}

template<typename K, typename V> void SplayNode<K, V>::goAlongLeftBranch(SplayNode<K, V>* x, stack<SplayNode<K, V>*>& s)
{
	while (x != nullptr)
	{
		s.push(x);                                                             //�ڵ���ջ
		x = x->lc;                                                             //�����������ͨ·����
	}
}

template<typename K, typename V> template<typename VST> void SplayNode<K, V>::traverseInI1(SplayNode<K, V>* x, VST& visit)    //��һ�ֵ����汾��������㷨
{
	stack<SplayNode<K, V>*> s;
	while (true)
	{
		goAlongLeftBranch(x, s);                                               //���ø�������
		if (s.empty() == true)                                                 //ջΪ������ζ�ű������
			break;
		x = s.top();                                                           //ת����ջ��ָ����ָ��Ľڵ㣬ջ����ջ
		s.pop();
		visit(x->value);                                                       //���ʽڵ�
		x = x->rc;                                                             //���뵱ǰ�ڵ��������
	}
}

template<typename K, typename V> template<typename VST> void SplayNode<K, V>::traverseInI2(SplayNode<K, V>* x, VST& visit)    //���־��ǰѵ�һ�ֵ����������ϲ���
{
	stack<SplayNode<K, V>*> s;
	while (true)
	{
		if (x != nullptr)
		{
			s.push(x);
			x = x->lc;
		}
		else if (s.empty() == false)
		{
			x = s.top();
			s.pop();
			visit(x->value);
			x = x->rc;
		}
		else
			break;
	}
}

template<typename K, typename V> template<typename VST> void SplayNode<K, V>::traverseInI3(SplayNode<K, V>* x, VST& visit)
{                                                                              //ԭ������ͬ�ģ�������һ�����ݱ�־λ������ջ
	bool backtrack = false;
	while (true)
	{
		if ((backtrack == false) && (SplayNode<K, V>::hasLChild(*x) == true))  //������ݱ�־λΪfalse�ҵ�ǰ�ڵ�������
			x = x->lc;                                                         //������������ͨ·����
		else                                                                   //����
		{
			visit(x->value);                                                   //���ʵ�ǰ�ڵ�
			if (SplayNode<K, V>::hasRChild(*x) == true)                        //�����ǰ�ڵ����Һ���
			{
				x = x->rc;                                                     //���ƶ����Һ��Ӵ��������뵱ǰ�ڵ��������
				backtrack = false;                                             //���ݱ�־λ��Ϊfalse
			}
			else                                                               //�����ǰ�ڵ����Һ���
			{
				x = x->getSucc();                                              //����õ�ǰ�ڵ��getSucc()������ֱ��ת�Ƶ���ǰ�ڵ���������������µ�ֱ�Ӻ�̴�
				if (x == nullptr)                                              //���ֱ�Ӻ�̲����ڣ���������
					break;
				backtrack = true;                                              //ֱ�Ӻ�̴��ڣ�����ݱ�־λ��Ϊtrue
			}                                                                  //�������Ϊ��ǰ������ջ�ķ�����x = s.pop()�ǵȼ۵ģ�����ȷʵ����˵��һ��"����"
		}
	}
}

template<typename K, typename V> template<typename VST> void SplayNode<K, V>::traverseInR(SplayNode<K, V>* x, VST& visit)
{
	if (x == nullptr)
		return;
	traverseInR(x->lc, visit);
	visit(x->value);
	traverseInR(x->rc, visit);
}



