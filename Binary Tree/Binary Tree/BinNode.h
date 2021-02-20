/*********************************************************************************
 *   @file        BinNode.h
 *   @brief       The header file for C++ implemented BinNode
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include <random>
#include <stack>
#include <deque>
using namespace std;

typedef enum { RB_RED, RB_BLACK } RBColor;                                     //节点颜色

template<typename T> class BinNode                                             //二叉树节点模板类
{
public:
	T data;                                                                    //二叉树节点所存储的数据
	BinNode<T>* parent;                                                        //指向母亲节点的指针
	BinNode<T>* lc;                                                            //指向左孩子节点的指针
	BinNode<T>* rc;                                                            //指向右孩子节点的指针
	int height;                                                                //高度
	int npl;                                                                   //Null Path Length，左式堆，也可直接用height代替
	RBColor color;                                                             //颜色，用于红黑树
	//用于判断节点性质的函数
	static bool isRoot(const BinNode<T>& bn);                                  //判断bn节点是否是根节点
	static bool isLChild(const BinNode<T>& bn);                                //判断bn节点是否是左孩子节点
	static bool isRChild(const BinNode<T>& bn);                                //判断bn节点是否是右孩子节点
	static bool hasParent(const BinNode<T>& bn);                               //判断bn节点是否有母亲节点
	static bool hasLChild(const BinNode<T>& bn);                               //判断bn节点是否有左孩子
	static bool hasRChild(const BinNode<T>& bn);                               //判断bn节点是否有右孩子
	static bool hasChild(const BinNode<T>& bn);                                //判断bn节点是否有孩子
	static bool hasBothChild(const BinNode<T>& bn);                            //判断bn节点是否既有左孩子又有右孩子
	static bool isLeaf(const BinNode<T>& bn);                                  //判断bn节点是否是叶子节点
	static BinNode<T>* sibling(BinNode<T>* x);                                 //获取x指向的节点的兄弟节点
	static int getStature(BinNode<T>* x);                                      //获取x指向的节点的高度，与"空树高度为-1"的约定相统一
	//构造函数
	BinNode(T e = static_cast<T>(0), BinNode<T>* p = nullptr, BinNode<T>* l = nullptr, BinNode<T>* r = nullptr, int h = 0, int n = 1, RBColor c = RB_RED);
	//操作接口
	int getSize();                                                             //统计当前节点后代总数，亦即以其为根的子树的规模
	BinNode<T>* insertAsLC(const T& e);                                        //作为当前节点的左孩子插入新节点
	BinNode<T>* insertAsRC(const T& e);                                        //作为当前节点的右孩子插入新节点
	BinNode<T>* getSucc();                                                     //获取当前节点在中序遍历意义下的直接后继
	template<typename VST> void traverseLevel(VST& visit);                     //层次遍历算法
	template<typename VST> void traversePre(VST& visit);                       //先序遍历算法
	template<typename VST> void traverseIn(VST& visit);                        //中序遍历算法
	template<typename VST> void traversePost(VST& visit);                      //后序遍历算法
	//比较器和判等器，各列其一，其余可自行补充
	bool operator < (const BinNode<T>& bn);
	bool operator == (const BinNode<T>& bn);
protected:
	template<typename VST> void visitAlongLeftBranch(BinNode<T>* x, VST& visit, stack<BinNode<T>*>& s);   //迭代版本先序遍历算法所需辅助函数
	template<typename VST> void traversePreI(BinNode<T>* x, VST& visit);       //自x指向的节点起进行迭代版本先序遍历算法
	template<typename VST> void traversePreR(BinNode<T>* x, VST& visit);       //自x指向的节点起进行递归版本先序遍历算法
	void goAlongLeftBranch(BinNode<T>* x, stack<BinNode<T>*>& s);              //迭代版本中序遍历算法所需辅助函数
	template<typename VST> void traverseInI1(BinNode<T>* x, VST& visit);       //自x指向的节点起进行第一种迭代版本中序遍历算法
	template<typename VST> void traverseInI2(BinNode<T>* x, VST& visit);       //自x指向的节点起进行第二种迭代版本中序遍历算法
	template<typename VST> void traverseInI3(BinNode<T>* x, VST& visit);       //自x指向的节点起进行第三种迭代版本中序遍历算法
	template<typename VST> void traverseInR(BinNode<T>* x, VST& visit);        //自x指向的节点起进行递归版本中序遍历算法
	void gotoHLVFL(stack<BinNode<T>*>& s);                                     //迭代版本后序遍历算法所需辅助函数
	template<typename VST> void traversePostI(BinNode<T>* x, VST& visit);      //自x指向的节点起进行迭代版本后序遍历算法
	template<typename VST> void traversePostR(BinNode<T>* x, VST& visit);      //自x指向的节点起进行递归版本后序遍历算法
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

template<typename T> int BinNode<T>::getStature(BinNode<T>* x)                 //获取x指向的节点的高度，与"空树高度为-1"的约定相统一
{
	return (x != nullptr) ? x->height : -1;
}

template<typename T> BinNode<T>::BinNode(T e, BinNode<T>* p, BinNode<T>* l, BinNode<T>* r, int h, int n, RBColor c) :
	data(e), parent(p), lc(l), rc(r), height(h), npl(n), color(c) {}

template<typename T> int BinNode<T>::getSize()                                 //获取以当前节点为根节点的子树的规模，采用了递归实现
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

template<typename T> BinNode<T>* BinNode<T>::getSucc()                         //获取指向当前节点在中序遍历意义下的直接后继节点的指针
{
	BinNode<T>* s = this;
	if (rc != nullptr)                                                         //如果当前节点有右孩子，则直接后继为以右孩子为根节点的子树的最左侧通路尽头节点
	{
		s = rc;                                                                //进入以右孩子为根节点的子树
		while (BinNode<T>::hasLChild(*s) == true)                              //前往最左侧通路尽头
			s = s->lc;
	}
	else                                                                       //否则，当前节点的直接后继为其向上第一个不是右孩子的祖先的母亲节点
	{
		while (BinNode<T>::isRChild(*s) == true)
			s = s->parent;
		s = s->parent;
	}
	return s;
}

template<typename T> template<typename VST> void BinNode<T>::traverseLevel(VST& visit)//层次遍历算法比较直观易懂，就不多赘述了
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

template<typename T> template<typename VST> void BinNode<T>::traversePre(VST& visit)  //先序遍历算法随机选择迭代版本和递归版本
{
	uniform_int_distribution<int> u(0, 1);
	default_random_engine e;
	switch (u(e))
	{
	case 0:traversePreI(this, visit); break;
	case 1:traversePreR(this, visit); break;
	}
}

template<typename T> template<typename VST> void BinNode<T>::traverseIn(VST& visit)   //中序遍历算法随机选择一种
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

template<typename T> template<typename VST> void BinNode<T>::traversePost(VST& visit) //后序遍历算法随机选择迭代版本和递归版本
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
		visit(x->data);                                                        //访问节点
		s.push(x->rc);                                                         //节点的右孩子，也就是节点的右子树的根节点，入栈
		x = x->lc;                                                             //继续沿最左侧通路下行
	}
}

template<typename T> template<typename VST> void BinNode<T>::traversePreI(BinNode<T>* x, VST& visit)      //迭代版本先序遍历算法
{
	stack<BinNode<T>*> s;
	while (true)
	{
		visitAlongLeftBranch(x, visit, s);                                     //调用辅助方法
		if (s.empty() == true)                                                 //栈空则意味着遍历完成
			break;
		x = s.pop();                                                           //转移至栈顶指针所指向的节点，栈顶出栈
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
		s.push(x);                                                             //节点入栈
		x = x->lc;                                                             //继续沿最左侧通路下行
	}
}

template<typename T> template<typename VST> void BinNode<T>::traverseInI1(BinNode<T>* x, VST& visit)      //第一种迭代版本中序遍历算法
{
	stack<BinNode<T>*> s;
	while (true)
	{
		goAlongLeftBranch(x, s);                                               //调用辅助方法
		if (s.empty() == true)                                                 //栈为空则意味着遍历完成
			break;
		x = s.top();                                                           //转移至栈顶指针所指向的节点，栈顶出栈
		s.pop();
		visit(x->data);                                                        //访问节点
		x = x->rc;                                                             //进入当前节点的右子树
	}
}

template<typename T> template<typename VST> void BinNode<T>::traverseInI2(BinNode<T>* x, VST& visit)      //这种就是把第一种的两个函数合并了
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

template<typename T> template<typename VST> void BinNode<T>::traverseInI3(BinNode<T>* x, VST& visit)      //原理都是相同的，这种用一个回溯标志位代替了栈
{
	bool backtrack = false;
	while (true)
	{
		if ((backtrack == false) && (BinNode<T>::hasLChild(*x) == true))       //如果回溯标志位为false且当前节点有左孩子
			x = x->lc;                                                         //则继续沿最左侧通路下行
		else                                                                   //否则
		{
			visit(x->data);                                                    //访问当前节点
			if (BinNode<T>::hasRChild(*x) == true)                             //如果当前节点有右孩子
			{
				x = x->rc;                                                     //则移动到右孩子处，即进入当前节点的右子树
				backtrack = false;                                             //回溯标志位置为false
			}
			else                                                               //如果当前节点无右孩子
			{
				x = x->getSucc();                                              //则调用当前节点的getSucc()函数，直接转移到当前节点在中序遍历意义下的直接后继处
				if (x == nullptr)                                              //如果直接后继不存在，则遍历完成
					break;
				backtrack = true;                                              //直接后继存在，则回溯标志位置为true
			}                                                                  //这里的行为和前两种用栈的方法里x = s.pop()是等价的，所以确实可以说是一种"回溯"
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

template<typename T> void BinNode<T>::gotoHLVFL(stack<BinNode<T>*>& s)         //在以栈顶节点为根的子树中，找到最深的左侧可见叶节点
{
	BinNode<T>* x = nullptr;
	while ((x = s.top()) != nullptr)                                           //栈顶不为空指针时进行此循环
	{
		if (BinNode<T>::hasLChild(*x) == true)                                 //如果当前节点有左孩子
		{
			if (BinNode<T>::hasRChild(*x) == true)                             //如果还同时有右孩子
				s.push(x->rc);                                                 //则右孩子先入栈
			s.push(x->lc);                                                     //左孩子入栈
		}
		else                                                                   //如果当前节点无左孩子，则右孩子入栈，当然，右孩子完全有可能是空的
			s.push(x->rc);
	}
	s.pop();                                                                   //循环结束后栈顶必然为空指针，则将其出栈
}

template<typename T> template<typename VST> void BinNode<T>::traversePostI(BinNode<T>* x, VST& visit)     //迭代版本后序遍历算法
{
	stack<BinNode<T>*> s;
	if (x != nullptr)                                                          //当前节点入栈
		s.push(x);
	while (s.empty() == false)                                                 //栈为空则遍历完成
	{
		if (s.top() != x->parent)                                              //如果栈顶节点并非当前节点的母亲节点
			gotoHLVFL(s);                                                      //调用辅助函数
		x = s.top();                                                           //转移至栈顶指针所指向的节点，栈顶出栈
		s.pop();
		visit(x->data);                                                        //访问节点
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

