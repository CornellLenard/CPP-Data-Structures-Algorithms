/*********************************************************************************
 *   @file        BinNode.h
 *   @brief       The header file for C++ implemented BinNode
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

template<typename T> class BinNode                                             //�������ڵ�ģ����
{
public:
	T data;                                                                    //�������ڵ����洢������
	BinNode<T>* parent;                                                        //ָ��ĸ�׽ڵ��ָ��
	BinNode<T>* lc;                                                            //ָ�����ӽڵ��ָ��
	BinNode<T>* rc;                                                            //ָ���Һ��ӽڵ��ָ��
	int height;                                                                //�߶�
	int npl;                                                                   //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height����
	RBColor color;                                                             //��ɫ�����ں����
	//�����жϽڵ����ʵĺ���
	static bool isRoot(const BinNode<T>& bn);                                  //�ж�bn�ڵ��Ƿ��Ǹ��ڵ�
	static bool isLChild(const BinNode<T>& bn);                                //�ж�bn�ڵ��Ƿ������ӽڵ�
	static bool isRChild(const BinNode<T>& bn);                                //�ж�bn�ڵ��Ƿ����Һ��ӽڵ�
	static bool hasParent(const BinNode<T>& bn);                               //�ж�bn�ڵ��Ƿ���ĸ�׽ڵ�
	static bool hasLChild(const BinNode<T>& bn);                               //�ж�bn�ڵ��Ƿ�������
	static bool hasRChild(const BinNode<T>& bn);                               //�ж�bn�ڵ��Ƿ����Һ���
	static bool hasChild(const BinNode<T>& bn);                                //�ж�bn�ڵ��Ƿ��к���
	static bool hasBothChild(const BinNode<T>& bn);                            //�ж�bn�ڵ��Ƿ�������������Һ���
	static bool isLeaf(const BinNode<T>& bn);                                  //�ж�bn�ڵ��Ƿ���Ҷ�ӽڵ�
	static BinNode<T>* sibling(BinNode<T>* x);                                 //��ȡxָ��Ľڵ���ֵܽڵ�
	static int getStature(BinNode<T>* x);                                      //��ȡxָ��Ľڵ�ĸ߶ȣ���"�����߶�Ϊ-1"��Լ����ͳһ
	//���캯��
	BinNode(T e = static_cast<T>(0), BinNode<T>* p = nullptr, BinNode<T>* l = nullptr, BinNode<T>* r = nullptr, int h = 0, int n = 1, RBColor c = RB_RED);
	//�����ӿ�
	int getSize();                                                             //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
	BinNode<T>* insertAsLC(const T& e);                                        //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
	BinNode<T>* insertAsRC(const T& e);                                        //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
	BinNode<T>* getSucc();                                                     //��ȡ��ǰ�ڵ���������������µ�ֱ�Ӻ��
	template<typename VST> void traverseLevel(VST& visit);                     //��α����㷨
	template<typename VST> void traversePre(VST& visit);                       //��������㷨
	template<typename VST> void traverseIn(VST& visit);                        //��������㷨
	template<typename VST> void traversePost(VST& visit);                      //��������㷨
	//�Ƚ������е�����������һ����������в���
	bool operator < (const BinNode<T>& bn);
	bool operator == (const BinNode<T>& bn);
protected:
	template<typename VST> void visitAlongLeftBranch(BinNode<T>* x, VST& visit, stack<BinNode<T>*>& s);   //�����汾��������㷨���踨������
	template<typename VST> void traversePreI(BinNode<T>* x, VST& visit);       //��xָ��Ľڵ�����е����汾��������㷨
	template<typename VST> void traversePreR(BinNode<T>* x, VST& visit);       //��xָ��Ľڵ�����еݹ�汾��������㷨
	void goAlongLeftBranch(BinNode<T>* x, stack<BinNode<T>*>& s);              //�����汾��������㷨���踨������
	template<typename VST> void traverseInI1(BinNode<T>* x, VST& visit);       //��xָ��Ľڵ�����е�һ�ֵ����汾��������㷨
	template<typename VST> void traverseInI2(BinNode<T>* x, VST& visit);       //��xָ��Ľڵ�����еڶ��ֵ����汾��������㷨
	template<typename VST> void traverseInI3(BinNode<T>* x, VST& visit);       //��xָ��Ľڵ�����е����ֵ����汾��������㷨
	template<typename VST> void traverseInR(BinNode<T>* x, VST& visit);        //��xָ��Ľڵ�����еݹ�汾��������㷨
	void gotoHLVFL(stack<BinNode<T>*>& s);                                     //�����汾��������㷨���踨������
	template<typename VST> void traversePostI(BinNode<T>* x, VST& visit);      //��xָ��Ľڵ�����е����汾��������㷨
	template<typename VST> void traversePostR(BinNode<T>* x, VST& visit);      //��xָ��Ľڵ�����еݹ�汾��������㷨
};

template<typename T> bool BinNode<T>::isRoot(const BinNode<T>& bn)
{
	return bn.parent == nullptr;
}

template<typename T> bool BinNode<T>::isLChild(const BinNode<T>& bn)
{
	return (isRoot(bn) == false) && ((bn.parent)->lc == &bn);
}

template<typename T> bool BinNode<T>::isRChild(const BinNode<T>& bn)
{
	return (isRoot(bn) == false) && ((bn.parent)->rc == &bn);
}

template<typename T> bool BinNode<T>::hasParent(const BinNode<T>& bn)
{
	return isRoot(bn) == false;
}

template<typename T> bool BinNode<T>::hasLChild(const BinNode<T>& bn)
{
	return bn.lc != nullptr;
}

template<typename T> bool BinNode<T>::hasRChild(const BinNode<T>& bn)
{
	return bn.rc != nullptr;
}

template<typename T> bool BinNode<T>::hasChild(const BinNode<T>& bn)
{
	return hasLChild(bn) == true || hasRChild(bn) == true;
}

template<typename T> bool BinNode<T>::hasBothChild(const BinNode<T>& bn)
{
	return hasLChild(bn) == true && hasRChild(bn) == true;
}

template<typename T> bool BinNode<T>::isLeaf(const BinNode<T>& bn)
{
	return hasChild(bn) == false;
}

template<typename T> BinNode<T>* BinNode<T>::sibling(BinNode<T>* x)
{
	return (isLChild(*x) == true) ? x->parent->rc : x->parent->lc;
}

template<typename T> int BinNode<T>::getStature(BinNode<T>* x)                 //��ȡxָ��Ľڵ�ĸ߶ȣ���"�����߶�Ϊ-1"��Լ����ͳһ
{
	return (x != nullptr) ? x->height : -1;
}

template<typename T> BinNode<T>::BinNode(T e, BinNode<T>* p, BinNode<T>* l, BinNode<T>* r, int h, int n, RBColor c) :
	data(e), parent(p), lc(l), rc(r), height(h), npl(n), color(c) {}

template<typename T> int BinNode<T>::getSize()                                 //��ȡ�Ե�ǰ�ڵ�Ϊ���ڵ�������Ĺ�ģ�������˵ݹ�ʵ��
{
	int count = 1;
	if (lc != nullptr)
		count += lc->getSize();
	if (rc != nullptr)
		count += rc->getSize();
	return count;
}

template<typename T> BinNode<T>* BinNode<T>::insertAsLC(const T& e)
{
	return lc = new BinNode<T>(e, this);
}

template<typename T> BinNode<T>* BinNode<T>::insertAsRC(const T& e)
{
	return rc = new BinNode<T>(e, this);
}

template<typename T> BinNode<T>* BinNode<T>::getSucc()                         //��ȡָ��ǰ�ڵ���������������µ�ֱ�Ӻ�̽ڵ��ָ��
{
	BinNode<T>* s = this;
	if (rc != nullptr)                                                         //�����ǰ�ڵ����Һ��ӣ���ֱ�Ӻ��Ϊ���Һ���Ϊ���ڵ�������������ͨ·��ͷ�ڵ�
	{
		s = rc;                                                                //�������Һ���Ϊ���ڵ������
		while (BinNode<T>::hasLChild(*s) == true)                              //ǰ�������ͨ·��ͷ
			s = s->lc;
	}
	else                                                                       //���򣬵�ǰ�ڵ��ֱ�Ӻ��Ϊ�����ϵ�һ�������Һ��ӵ����ȵ�ĸ�׽ڵ�
	{
		while (BinNode<T>::isRChild(*s) == true)
			s = s->parent;
		s = s->parent;
	}
	return s;
}

template<typename T> template<typename VST> void BinNode<T>::traverseLevel(VST& visit)//��α����㷨�Ƚ�ֱ���׶����Ͳ���׸����
{
	deque<BinNode<T>*> q;
	q.push_back(this);
	BinNode<T>* x = nullptr;
	while (q.empty() == false)
	{
		x = q.pop_front();
		visit(x->data);
		if (BinNode<T>::hasLChild(*x) == true)
			q.push_back(x->lc);
		if (BinNode<T>::hasRChild(*x) == true)
			q.push_back(x->rc);
	}
}

template<typename T> template<typename VST> void BinNode<T>::traversePre(VST& visit)  //��������㷨���ѡ������汾�͵ݹ�汾
{
	uniform_int_distribution<int> u(0, 1);
	default_random_engine e;
	switch (u(e))
	{
	case 0:traversePreI(this, visit); break;
	case 1:traversePreR(this, visit); break;
	}
}

template<typename T> template<typename VST> void BinNode<T>::traverseIn(VST& visit)   //��������㷨���ѡ��һ��
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

template<typename T> template<typename VST> void BinNode<T>::traversePost(VST& visit) //��������㷨���ѡ������汾�͵ݹ�汾
{
	uniform_int_distribution<int> u(0, 1);
	default_random_engine e;
	switch (u(e))
	{
	case 0:traversePostI(this, visit); break;
	case 1:traversePostR(this, visit); break;
	}
}

template<typename T> bool BinNode<T>::operator < (const BinNode<T>& bn)
{
	return data < bn.data;
}

template<typename T> bool BinNode<T>::operator == (const BinNode<T>& bn)
{
	return data == bn.data;
}

template<typename T> template<typename VST> void BinNode<T>::visitAlongLeftBranch(BinNode<T>* x, VST& visit, stack<BinNode<T>*>& s)
{
	while (x != nullptr)
	{
		visit(x->data);                                                        //���ʽڵ�
		s.push(x->rc);                                                         //�ڵ���Һ��ӣ�Ҳ���ǽڵ���������ĸ��ڵ㣬��ջ
		x = x->lc;                                                             //�����������ͨ·����
	}
}

template<typename T> template<typename VST> void BinNode<T>::traversePreI(BinNode<T>* x, VST& visit)      //�����汾��������㷨
{
	stack<BinNode<T>*> s;
	while (true)
	{
		visitAlongLeftBranch(x, visit, s);                                     //���ø�������
		if (s.empty() == true)                                                 //ջ������ζ�ű������
			break;
		x = s.pop();                                                           //ת����ջ��ָ����ָ��Ľڵ㣬ջ����ջ
	}
}

template<typename T> template<typename VST> void BinNode<T>::traversePreR(BinNode<T>* x, VST& visit)
{
	if (x == nullptr)
		return;
	visit(x->data);
	traversePreR(x->lc, visit);
	traversePreR(x->rc, visit);
}

template<typename T> void BinNode<T>::goAlongLeftBranch(BinNode<T>* x, stack<BinNode<T>*>& s)
{
	while (x != nullptr)
	{
		s.push(x);                                                             //�ڵ���ջ
		x = x->lc;                                                             //�����������ͨ·����
	}
}

template<typename T> template<typename VST> void BinNode<T>::traverseInI1(BinNode<T>* x, VST& visit)      //��һ�ֵ����汾��������㷨
{
	stack<BinNode<T>*> s;
	while (true)
	{
		goAlongLeftBranch(x, s);                                               //���ø�������
		if (s.empty() == true)                                                 //ջΪ������ζ�ű������
			break;
		x = s.top();                                                           //ת����ջ��ָ����ָ��Ľڵ㣬ջ����ջ
		s.pop();
		visit(x->data);                                                        //���ʽڵ�
		x = x->rc;                                                             //���뵱ǰ�ڵ��������
	}
}

template<typename T> template<typename VST> void BinNode<T>::traverseInI2(BinNode<T>* x, VST& visit)      //���־��ǰѵ�һ�ֵ����������ϲ���
{
	stack<BinNode<T>*> s;
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
			visit(x->data);
			x = x->rc;
		}
		else
			break;
	}
}

template<typename T> template<typename VST> void BinNode<T>::traverseInI3(BinNode<T>* x, VST& visit)      //ԭ������ͬ�ģ�������һ�����ݱ�־λ������ջ
{
	bool backtrack = false;
	while (true)
	{
		if ((backtrack == false) && (BinNode<T>::hasLChild(*x) == true))       //������ݱ�־λΪfalse�ҵ�ǰ�ڵ�������
			x = x->lc;                                                         //������������ͨ·����
		else                                                                   //����
		{
			visit(x->data);                                                    //���ʵ�ǰ�ڵ�
			if (BinNode<T>::hasRChild(*x) == true)                             //�����ǰ�ڵ����Һ���
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

template<typename T> template<typename VST> void BinNode<T>::traverseInR(BinNode<T>* x, VST& visit)
{
	if (x == nullptr)
		return;
	traverseInR(x->lc, visit);
	visit(x->data);
	traverseInR(x->rc, visit);
}

template<typename T> void BinNode<T>::gotoHLVFL(stack<BinNode<T>*>& s)         //����ջ���ڵ�Ϊ���������У��ҵ���������ɼ�Ҷ�ڵ�
{
	BinNode<T>* x = nullptr;
	while ((x = s.top()) != nullptr)                                           //ջ����Ϊ��ָ��ʱ���д�ѭ��
	{
		if (BinNode<T>::hasLChild(*x) == true)                                 //�����ǰ�ڵ�������
		{
			if (BinNode<T>::hasRChild(*x) == true)                             //�����ͬʱ���Һ���
				s.push(x->rc);                                                 //���Һ�������ջ
			s.push(x->lc);                                                     //������ջ
		}
		else                                                                   //�����ǰ�ڵ������ӣ����Һ�����ջ����Ȼ���Һ�����ȫ�п����ǿյ�
			s.push(x->rc);
	}
	s.pop();                                                                   //ѭ��������ջ����ȻΪ��ָ�룬�����ջ
}

template<typename T> template<typename VST> void BinNode<T>::traversePostI(BinNode<T>* x, VST& visit)     //�����汾��������㷨
{
	stack<BinNode<T>*> s;
	if (x != nullptr)                                                          //��ǰ�ڵ���ջ
		s.push(x);
	while (s.empty() == false)                                                 //ջΪ����������
	{
		if (s.top() != x->parent)                                              //���ջ���ڵ㲢�ǵ�ǰ�ڵ��ĸ�׽ڵ�
			gotoHLVFL(s);                                                      //���ø�������
		x = s.top();                                                           //ת����ջ��ָ����ָ��Ľڵ㣬ջ����ջ
		s.pop();
		visit(x->data);                                                        //���ʽڵ�
	}
}

template<typename T> template<typename VST> void BinNode<T>::traversePostR(BinNode<T>* x, VST& visit)
{
	if (x == nullptr)
		return;
	traversePostR(x->lc, visit);
	traversePostR(x->rc, visit);
	visit(x->data);
}

