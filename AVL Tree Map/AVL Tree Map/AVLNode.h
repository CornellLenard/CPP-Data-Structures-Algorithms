/*********************************************************************************
 *   @file        AVLNode.h
 *   @brief       The header file for C++ implemented AVLNode
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

template<typename K, typename V> class AVLNode                                 //AVL���ڵ�ģ����
{
public:
	K key;                                                                     //AVL���ڵ����洢�Ĺؼ���
	V value;                                                                   //AVL���ڵ����洢������
	AVLNode<K, V>* parent;                                                     //ָ��ĸ�׽ڵ��ָ��
	AVLNode<K, V>* lc;                                                         //ָ�����ӽڵ��ָ��
	AVLNode<K, V>* rc;                                                         //ָ���Һ��ӽڵ��ָ��
	int height;                                                                //�߶�
	int npl;                                                                   //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height����
	RBColor color;                                                             //��ɫ�����ں����
	//�����жϽڵ����ʵĺ���
	static bool isRoot(const AVLNode<K, V>& avln);                             //�ж�avln�ڵ��Ƿ��Ǹ��ڵ�
	static bool isLChild(const AVLNode<K, V>& avln);                           //�ж�avln�ڵ��Ƿ������ӽڵ�
	static bool isRChild(const AVLNode<K, V>& avln);                           //�ж�avln�ڵ��Ƿ����Һ��ӽڵ�
	static bool hasParent(const AVLNode<K, V>& avln);                          //�ж�avln�ڵ��Ƿ���ĸ�׽ڵ�
	static bool hasLChild(const AVLNode<K, V>& avln);                          //�ж�avln�ڵ��Ƿ�������
	static bool hasRChild(const AVLNode<K, V>& avln);                          //�ж�avln�ڵ��Ƿ����Һ���
	static bool hasChild(const AVLNode<K, V>& avln);                           //�ж�avln�ڵ��Ƿ��к���
	static bool hasBothChild(const AVLNode<K, V>& avln);                       //�ж�avln�ڵ��Ƿ�������������Һ���
	static bool isLeaf(const AVLNode<K, V>& avln);                             //�ж�avln�ڵ��Ƿ���Ҷ�ӽڵ�
	static AVLNode<K, V>* sibling(AVLNode<K, V>* x);                           //��ȡxָ��Ľڵ���ֵܽڵ�
	static int getStature(AVLNode<K, V>* x);                                   //��ȡxָ��Ľڵ�ĸ߶ȣ���"�����߶�Ϊ-1"��Լ����ͳһ
	static bool isBalanced(const AVLNode<K, V>& avln);                         //�ж�avln�ڵ��Ƿ�����ƽ��
	static int getBalanceFactor(const AVLNode<K, V>& avln);                    //��ȡavln�ڵ��ƽ������
	static bool isAVLBalanced(const AVLNode<K, V>& avln);                      //�ж�avln�ڵ��Ƿ�AVLƽ��
	static AVLNode<K, V>* getTallerChild(AVLNode<K, V>* x);                    //�����Һ�����ȡ�����ߣ����ȸߣ�����ĸ��xͬ����(zig-zig��zag-zag)����
	//���캯��
	AVLNode(K k, V v = static_cast<V>(0), AVLNode<K, V>* p = nullptr, AVLNode<K, V>* l = nullptr, AVLNode<K, V>* r = nullptr, int h = 0, int n = 1, RBColor c = RB_RED);
	//�����ӿ�
	int getSize();                                                             //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
	AVLNode<K, V>* getSucc();                                                  //��ȡ��ǰ�ڵ���������������µ�ֱ�Ӻ��
	template<typename VST> void traverseLevel(VST& visit);                     //��α����㷨
	template<typename VST> void traverseIn(VST& visit);                        //��������㷨
	//�Ƚ������е�����������һ����������в���
	bool operator < (const AVLNode<K, V>& avln);
	bool operator == (const AVLNode<K, V>& avln);
protected:
	void goAlongLeftBranch(AVLNode<K, V>* x, stack<AVLNode<K, V>*>& s);        //�����汾��������㷨���踨������
	template<typename VST> void traverseInI1(AVLNode<K, V>* x, VST& visit);    //��xָ��Ľڵ�����е�һ�ֵ����汾��������㷨
	template<typename VST> void traverseInI2(AVLNode<K, V>* x, VST& visit);    //��xָ��Ľڵ�����еڶ��ֵ����汾��������㷨
	template<typename VST> void traverseInI3(AVLNode<K, V>* x, VST& visit);    //��xָ��Ľڵ�����е����ֵ����汾��������㷨
	template<typename VST> void traverseInR(AVLNode<K, V>* x, VST& visit);     //��xָ��Ľڵ�����еݹ�汾��������㷨
};

template<typename K, typename V> bool AVLNode<K, V>::isRoot(const AVLNode<K, V>& avln)
{
	return avln.parent == nullptr;
}

template<typename K, typename V> bool AVLNode<K, V>::isLChild(const AVLNode<K, V>& avln)
{
	return (isRoot(avln) == false) && ((avln.parent)->lc == &avln);
}

template<typename K, typename V> bool AVLNode<K, V>::isRChild(const AVLNode<K, V>& avln)
{
	return (isRoot(avln) == false) && ((avln.parent)->rc == &avln);
}

template<typename K, typename V> bool AVLNode<K, V>::hasParent(const AVLNode<K, V>& avln)
{
	return isRoot(avln) == false;
}

template<typename K, typename V> bool AVLNode<K, V>::hasLChild(const AVLNode<K, V>& avln)
{
	return avln.lc != nullptr;
}

template<typename K, typename V> bool AVLNode<K, V>::hasRChild(const AVLNode<K, V>& avln)
{
	return avln.rc != nullptr;
}

template<typename K, typename V> bool AVLNode<K, V>::hasChild(const AVLNode<K, V>& avln)
{
	return hasLChild(avln) == true || hasRChild(avln) == true;
}

template<typename K, typename V> bool AVLNode<K, V>::hasBothChild(const AVLNode<K, V>& avln)
{
	return hasLChild(avln) == true && hasRChild(avln) == true;
}

template<typename K, typename V> bool AVLNode<K, V>::isLeaf(const AVLNode<K, V>& avln)
{
	return hasChild(avln) == false;
}

template<typename K, typename V> AVLNode<K, V>* AVLNode<K, V>::sibling(AVLNode<K, V>* x)
{
	return (isLChild(*x) == true) ? x->parent->rc : x->parent->lc;
}

template<typename K, typename V> int AVLNode<K, V>::getStature(AVLNode<K, V>* x)      //��ȡxָ��Ľڵ�ĸ߶ȣ���"�����߶�Ϊ-1"��Լ����ͳһ
{
	return (x != nullptr) ? x->height : -1;
}

template<typename K, typename V> bool AVLNode<K, V>::isBalanced(const AVLNode<K, V>& avln)
{
	return getStature(avln.lc) == getStature(avln.rc);
}

template<typename K, typename V> int AVLNode<K, V>::getBalanceFactor(const AVLNode<K, V>& avln)
{
	return getStature(avln.lc) - getStature(avln.rc);
}

template<typename K, typename V> bool AVLNode<K, V>::isAVLBalanced(const AVLNode<K, V>& avln)
{
	return (getBalanceFactor(avln) >= -1) && (getBalanceFactor(avln) <= 1);
}

template<typename K, typename V> AVLNode<K, V>* AVLNode<K, V>::getTallerChild(AVLNode<K, V>* x)
{
	if (getStature(x->lc) > getStature(x->rc))
		return x->lc;
	else if (getStature(x->rc) > getStature(x->lc))
		return x->rc;
	else
		return (isLChild(*x) == true) ? x->lc : x->rc;
}

template<typename K, typename V> AVLNode<K, V>::AVLNode(K k, V v, AVLNode<K, V>* p, AVLNode<K, V>* l, AVLNode<K, V>* r, int h, int n, RBColor c) :
	key(k), value(v), parent(p), lc(l), rc(r), height(h), npl(n), color(c) {}


template<typename K, typename V> int AVLNode<K, V>::getSize()                  //��ȡ�Ե�ǰ�ڵ�Ϊ���ڵ�������Ĺ�ģ�������˵ݹ�ʵ��
{
	int count = 1;
	if (lc != nullptr)
		count += lc->getSize();
	if (rc != nullptr)
		count += rc->getSize();
	return count;
}

template<typename K, typename V> AVLNode<K, V>* AVLNode<K, V>::getSucc()       //��ȡָ��ǰ�ڵ���������������µ�ֱ�Ӻ�̽ڵ��ָ��
{
	AVLNode<K, V>* s = this;
	if (rc != nullptr)                                                         //�����ǰ�ڵ����Һ��ӣ���ֱ�Ӻ��Ϊ���Һ���Ϊ���ڵ�������������ͨ·��ͷ�ڵ�
	{
		s = rc;                                                                //�������Һ���Ϊ���ڵ������
		while (AVLNode<K, V>::hasLChild(*s) == true)                           //ǰ�������ͨ·��ͷ
			s = s->lc;
	}
	else                                                                       //���򣬵�ǰ�ڵ��ֱ�Ӻ��Ϊ�����ϵ�һ�������Һ��ӵ����ȵ�ĸ�׽ڵ�
	{
		while (AVLNode<K, V>::isRChild(*s) == true)
			s = s->parent;
		s = s->parent;
	}
	return s;
}

template<typename K, typename V> template<typename VST> void AVLNode<K, V>::traverseLevel(VST& visit)     //��α����㷨�Ƚ�ֱ���׶����Ͳ���׸����
{
	deque<AVLNode<K, V>*> q;
	q.push_back(this);
	AVLNode<K, V>* x = nullptr;
	while (q.empty() == false)
	{
		x = q.pop_front();
		visit(x->value);
		if (AVLNode<K, V>::hasLChild(*x) == true)
			q.push_back(x->lc);
		if (AVLNode<K, V>::hasRChild(*x) == true)
			q.push_back(x->rc);
	}
}

template<typename K, typename V> template<typename VST> void AVLNode<K, V>::traverseIn(VST& visit)        //��������㷨���ѡ��һ��
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

template<typename K, typename V> bool AVLNode<K, V>::operator < (const AVLNode<K, V>& avln)
{
	return key < avln.key;
}

template<typename K, typename V> bool AVLNode<K, V>::operator == (const AVLNode<K, V>& avln)
{
	return key == avln.key;
}

template<typename K, typename V> void AVLNode<K, V>::goAlongLeftBranch(AVLNode<K, V>* x, stack<AVLNode<K, V>*>& s)
{
	while (x != nullptr)
	{
		s.push(x);                                                             //�ڵ���ջ
		x = x->lc;                                                             //�����������ͨ·����
	}
}

template<typename K, typename V> template<typename VST> void AVLNode<K, V>::traverseInI1(AVLNode<K, V>* x, VST& visit)        //��һ�ֵ����汾��������㷨
{
	stack<AVLNode<K, V>*> s;
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

template<typename K, typename V> template<typename VST> void AVLNode<K, V>::traverseInI2(AVLNode<K, V>* x, VST& visit)        //���־��ǰѵ�һ�ֵ����������ϲ���
{
	stack<AVLNode<K, V>*> s;
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

template<typename K, typename V> template<typename VST> void AVLNode<K, V>::traverseInI3(AVLNode<K, V>* x, VST& visit)
{                                                                              //ԭ������ͬ�ģ�������һ�����ݱ�־λ������ջ
	bool backtrack = false;
	while (true)
	{
		if ((backtrack == false) && (AVLNode<K, V>::hasLChild(*x) == true))    //������ݱ�־λΪfalse�ҵ�ǰ�ڵ�������
			x = x->lc;                                                         //������������ͨ·����
		else                                                                   //����
		{
			visit(x->value);                                                   //���ʵ�ǰ�ڵ�
			if (AVLNode<K, V>::hasRChild(*x) == true)                          //�����ǰ�ڵ����Һ���
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

template<typename K, typename V> template<typename VST> void AVLNode<K, V>::traverseInR(AVLNode<K, V>* x, VST& visit)
{
	if (x == nullptr)
		return;
	traverseInR(x->lc, visit);
	visit(x->value);
	traverseInR(x->rc, visit);
}


