/*********************************************************************************
 *   @file        BSTNode.h
 *   @brief       The header file for C++ implemented BSTNode
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

template<typename K, typename V> class BSTNode                                 //�����������ڵ�ģ����
{
public:
	K key;                                                                     //�����������ڵ����洢�Ĺؼ���
	V value;                                                                   //�����������ڵ����洢������
	BSTNode<K, V>* parent;                                                     //ָ��ĸ�׽ڵ��ָ��
	BSTNode<K, V>* lc;                                                         //ָ�����ӽڵ��ָ��
	BSTNode<K, V>* rc;                                                         //ָ���Һ��ӽڵ��ָ��
	int height;                                                                //�߶�
	int npl;                                                                   //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height����
	RBColor color;                                                             //��ɫ�����ں����
	//�����жϽڵ����ʵĺ���
	static bool isRoot(const BSTNode<K, V>& bn);                               //�ж�bn�ڵ��Ƿ��Ǹ��ڵ�
	static bool isLChild(const BSTNode<K, V>& bn);                             //�ж�bn�ڵ��Ƿ������ӽڵ�
	static bool isRChild(const BSTNode<K, V>& bn);                             //�ж�bn�ڵ��Ƿ����Һ��ӽڵ�
	static bool hasParent(const BSTNode<K, V>& bn);                            //�ж�bn�ڵ��Ƿ���ĸ�׽ڵ�
	static bool hasLChild(const BSTNode<K, V>& bn);                            //�ж�bn�ڵ��Ƿ�������
	static bool hasRChild(const BSTNode<K, V>& bn);                            //�ж�bn�ڵ��Ƿ����Һ���
	static bool hasChild(const BSTNode<K, V>& bn);                             //�ж�bn�ڵ��Ƿ��к���
	static bool hasBothChild(const BSTNode<K, V>& bn);                         //�ж�bn�ڵ��Ƿ�������������Һ���
	static bool isLeaf(const BSTNode<K, V>& bn);                               //�ж�bn�ڵ��Ƿ���Ҷ�ӽڵ�
	static BSTNode<K, V>* sibling(BSTNode<K, V>* x);                           //��ȡxָ��Ľڵ���ֵܽڵ�
	static int getStature(BSTNode<K, V>* x);                                   //��ȡxָ��Ľڵ�ĸ߶ȣ���"�����߶�Ϊ-1"��Լ����ͳһ
	//���캯��
	BSTNode(K k, V v = static_cast<V>(0), BSTNode<K, V>* p = nullptr, BSTNode<K, V>* l = nullptr, BSTNode<K, V>* r = nullptr, int h = 0, int n = 1, RBColor c = RB_RED);
	//�����ӿ�
	int getSize();                                                             //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
	BSTNode<K, V>* getSucc();                                                  //��ȡ��ǰ�ڵ���������������µ�ֱ�Ӻ��
	template<typename VST> void traverseLevel(VST& visit);                     //��α����㷨
	template<typename VST> void traverseIn(VST& visit);                        //��������㷨
	//�Ƚ������е�����������һ����������в���
	bool operator < (const BSTNode<K, V>& bn);
	bool operator == (const BSTNode<K, V>& bn);
protected:
	void goAlongLeftBranch(BSTNode<K, V>* x, stack<BSTNode<K, V>*>& s);        //�����汾��������㷨���踨������
	template<typename VST> void traverseInI1(BSTNode<K, V>* x, VST& visit);    //��xָ��Ľڵ�����е�һ�ֵ����汾��������㷨
	template<typename VST> void traverseInI2(BSTNode<K, V>* x, VST& visit);    //��xָ��Ľڵ�����еڶ��ֵ����汾��������㷨
	template<typename VST> void traverseInI3(BSTNode<K, V>* x, VST& visit);    //��xָ��Ľڵ�����е����ֵ����汾��������㷨
	template<typename VST> void traverseInR(BSTNode<K, V>* x, VST& visit);     //��xָ��Ľڵ�����еݹ�汾��������㷨
};

template<typename K, typename V> bool BSTNode<K, V>::isRoot(const BSTNode<K, V>& bn)
{
	return bn.parent == nullptr;
}

template<typename K, typename V> bool BSTNode<K, V>::isLChild(const BSTNode<K, V>& bn)
{
	return (isRoot(bn) == false) && ((bn.parent)->lc == &bn);
}

template<typename K, typename V> bool BSTNode<K, V>::isRChild(const BSTNode<K, V>& bn)
{
	return (isRoot(bn) == false) && ((bn.parent)->rc == &bn);
}

template<typename K, typename V> bool BSTNode<K, V>::hasParent(const BSTNode<K, V>& bn)
{
	return isRoot(bn) == false;
}

template<typename K, typename V> bool BSTNode<K, V>::hasLChild(const BSTNode<K, V>& bn)
{
	return bn.lc != nullptr;
}

template<typename K, typename V> bool BSTNode<K, V>::hasRChild(const BSTNode<K, V>& bn)
{
	return bn.rc != nullptr;
}

template<typename K, typename V> bool BSTNode<K, V>::hasChild(const BSTNode<K, V>& bn)
{
	return hasLChild(bn) == true || hasRChild(bn) == true;
}

template<typename K, typename V> bool BSTNode<K, V>::hasBothChild(const BSTNode<K, V>& bn)
{
	return hasLChild(bn) == true && hasRChild(bn) == true;
}

template<typename K, typename V> bool BSTNode<K, V>::isLeaf(const BSTNode<K, V>& bn)
{
	return hasChild(bn) == false;
}

template<typename K, typename V> BSTNode<K, V>* BSTNode<K, V>::sibling(BSTNode<K, V>* x)
{
	return (isLChild(*x) == true) ? x->parent->rc : x->parent->lc;
}

template<typename K, typename V> int BSTNode<K, V>::getStature(BSTNode<K, V>* x)      //��ȡxָ��Ľڵ�ĸ߶ȣ���"�����߶�Ϊ-1"��Լ����ͳһ
{
	return (x != nullptr) ? x->height : -1;
}

template<typename K, typename V> BSTNode<K, V>::BSTNode(K k, V v, BSTNode<K, V>* p, BSTNode<K, V>* l, BSTNode<K, V>* r, int h, int n, RBColor c) :
	key(k), value(v), parent(p), lc(l), rc(r), height(h), npl(n), color(c) {}


template<typename K, typename V> int BSTNode<K, V>::getSize()                  //��ȡ�Ե�ǰ�ڵ�Ϊ���ڵ�������Ĺ�ģ�������˵ݹ�ʵ��
{
	int count = 1;
	if (lc != nullptr)
		count += lc->getSize();
	if (rc != nullptr)
		count += rc->getSize();
	return count;
}

template<typename K, typename V> BSTNode<K, V>* BSTNode<K, V>::getSucc()       //��ȡָ��ǰ�ڵ���������������µ�ֱ�Ӻ�̽ڵ��ָ��
{
	BSTNode<K, V>* s = this;
	if (rc != nullptr)                                                         //�����ǰ�ڵ����Һ��ӣ���ֱ�Ӻ��Ϊ���Һ���Ϊ���ڵ�������������ͨ·��ͷ�ڵ�
	{
		s = rc;                                                                //�������Һ���Ϊ���ڵ������
		while (BSTNode<K, V>::hasLChild(*s) == true)                           //ǰ�������ͨ·��ͷ
			s = s->lc;
	}
	else                                                                       //���򣬵�ǰ�ڵ��ֱ�Ӻ��Ϊ�����ϵ�һ�������Һ��ӵ����ȵ�ĸ�׽ڵ�
	{
		while (BSTNode<K, V>::isRChild(*s) == true)
			s = s->parent;
		s = s->parent;
	}
	return s;
}

template<typename K, typename V> template<typename VST> void BSTNode<K, V>::traverseLevel(VST& visit)     //��α����㷨�Ƚ�ֱ���׶����Ͳ���׸����
{
	deque<BSTNode<K, V>*> q;
	q.push_back(this);
	BSTNode<K, V>* x = nullptr;
	while (q.empty() == false)
	{
		x = q.pop_front();
		visit(x->value);
		if (BSTNode<K, V>::hasLChild(*x) == true)
			q.push_back(x->lc);
		if (BSTNode<K, V>::hasRChild(*x) == true)
			q.push_back(x->rc);
	}
}

template<typename K, typename V> template<typename VST> void BSTNode<K, V>::traverseIn(VST& visit)        //��������㷨���ѡ��һ��
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

template<typename K, typename V> bool BSTNode<K, V>::operator < (const BSTNode<K, V>& bn)
{
	return key < bn.key;
}

template<typename K, typename V> bool BSTNode<K, V>::operator == (const BSTNode<K, V>& bn)
{
	return key == bn.key;
}

template<typename K, typename V> void BSTNode<K, V>::goAlongLeftBranch(BSTNode<K, V>* x, stack<BSTNode<K, V>*>& s)
{
	while (x != nullptr)
	{
		s.push(x);                                                             //�ڵ���ջ
		x = x->lc;                                                             //�����������ͨ·����
	}
}

template<typename K, typename V> template<typename VST> void BSTNode<K, V>::traverseInI1(BSTNode<K, V>* x, VST& visit)        //��һ�ֵ����汾��������㷨
{
	stack<BSTNode<K, V>*> s;
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

template<typename K, typename V> template<typename VST> void BSTNode<K, V>::traverseInI2(BSTNode<K, V>* x, VST& visit)        //���־��ǰѵ�һ�ֵ����������ϲ���
{
	stack<BSTNode<K, V>*> s;
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

template<typename K, typename V> template<typename VST> void BSTNode<K, V>::traverseInI3(BSTNode<K, V>* x, VST& visit)
{                                                                              //ԭ������ͬ�ģ�������һ�����ݱ�־λ������ջ
	bool backtrack = false;
	while (true)
	{
		if ((backtrack == false) && (BSTNode<K, V>::hasLChild(*x) == true))    //������ݱ�־λΪfalse�ҵ�ǰ�ڵ�������
			x = x->lc;                                                         //������������ͨ·����
		else                                                                   //����
		{
			visit(x->value);                                                   //���ʵ�ǰ�ڵ�
			if (BSTNode<K, V>::hasRChild(*x) == true)                          //�����ǰ�ڵ����Һ���
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

template<typename K, typename V> template<typename VST> void BSTNode<K, V>::traverseInR(BSTNode<K, V>* x, VST& visit)
{
	if (x == nullptr)
		return;
	traverseInR(x->lc, visit);
	visit(x->value);
	traverseInR(x->rc, visit);
}


