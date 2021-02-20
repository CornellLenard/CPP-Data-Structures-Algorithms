/*********************************************************************************
 *   @file        AVLNode.h
 *   @brief       The header file for C++ implemented AVLNode
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

template<typename K, typename V> class AVLNode                                 //AVL树节点模板类
{
public:
	K key;                                                                     //AVL树节点所存储的关键码
	V value;                                                                   //AVL树节点所存储的数据
	AVLNode<K, V>* parent;                                                     //指向母亲节点的指针
	AVLNode<K, V>* lc;                                                         //指向左孩子节点的指针
	AVLNode<K, V>* rc;                                                         //指向右孩子节点的指针
	int height;                                                                //高度
	int npl;                                                                   //Null Path Length，左式堆，也可直接用height代替
	RBColor color;                                                             //颜色，用于红黑树
	//用于判断节点性质的函数
	static bool isRoot(const AVLNode<K, V>& avln);                             //判断avln节点是否是根节点
	static bool isLChild(const AVLNode<K, V>& avln);                           //判断avln节点是否是左孩子节点
	static bool isRChild(const AVLNode<K, V>& avln);                           //判断avln节点是否是右孩子节点
	static bool hasParent(const AVLNode<K, V>& avln);                          //判断avln节点是否有母亲节点
	static bool hasLChild(const AVLNode<K, V>& avln);                          //判断avln节点是否有左孩子
	static bool hasRChild(const AVLNode<K, V>& avln);                          //判断avln节点是否有右孩子
	static bool hasChild(const AVLNode<K, V>& avln);                           //判断avln节点是否有孩子
	static bool hasBothChild(const AVLNode<K, V>& avln);                       //判断avln节点是否既有左孩子又有右孩子
	static bool isLeaf(const AVLNode<K, V>& avln);                             //判断avln节点是否是叶子节点
	static AVLNode<K, V>* sibling(AVLNode<K, V>* x);                           //获取x指向的节点的兄弟节点
	static int getStature(AVLNode<K, V>* x);                                   //获取x指向的节点的高度，与"空树高度为-1"的约定相统一
	static bool isBalanced(const AVLNode<K, V>& avln);                         //判断avln节点是否理想平衡
	static int getBalanceFactor(const AVLNode<K, V>& avln);                    //获取avln节点的平衡因子
	static bool isAVLBalanced(const AVLNode<K, V>& avln);                      //判断avln节点是否AVL平衡
	static AVLNode<K, V>* getTallerChild(AVLNode<K, V>* x);                    //在左、右孩子中取更高者，若等高，则与母亲x同侧者(zig-zig或zag-zag)优先
	//构造函数
	AVLNode(K k, V v = static_cast<V>(0), AVLNode<K, V>* p = nullptr, AVLNode<K, V>* l = nullptr, AVLNode<K, V>* r = nullptr, int h = 0, int n = 1, RBColor c = RB_RED);
	//操作接口
	int getSize();                                                             //统计当前节点后代总数，亦即以其为根的子树的规模
	AVLNode<K, V>* getSucc();                                                  //获取当前节点在中序遍历意义下的直接后继
	template<typename VST> void traverseLevel(VST& visit);                     //层次遍历算法
	template<typename VST> void traverseIn(VST& visit);                        //中序遍历算法
	//比较器和判等器，各列其一，其余可自行补充
	bool operator < (const AVLNode<K, V>& avln);
	bool operator == (const AVLNode<K, V>& avln);
protected:
	void goAlongLeftBranch(AVLNode<K, V>* x, stack<AVLNode<K, V>*>& s);        //迭代版本中序遍历算法所需辅助函数
	template<typename VST> void traverseInI1(AVLNode<K, V>* x, VST& visit);    //自x指向的节点起进行第一种迭代版本中序遍历算法
	template<typename VST> void traverseInI2(AVLNode<K, V>* x, VST& visit);    //自x指向的节点起进行第二种迭代版本中序遍历算法
	template<typename VST> void traverseInI3(AVLNode<K, V>* x, VST& visit);    //自x指向的节点起进行第三种迭代版本中序遍历算法
	template<typename VST> void traverseInR(AVLNode<K, V>* x, VST& visit);     //自x指向的节点起进行递归版本中序遍历算法
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

template<typename K, typename V> int AVLNode<K, V>::getStature(AVLNode<K, V>* x)      //获取x指向的节点的高度，与"空树高度为-1"的约定相统一
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


template<typename K, typename V> int AVLNode<K, V>::getSize()                  //获取以当前节点为根节点的子树的规模，采用了递归实现
{
	int count = 1;
	if (lc != nullptr)
		count += lc->getSize();
	if (rc != nullptr)
		count += rc->getSize();
	return count;
}

template<typename K, typename V> AVLNode<K, V>* AVLNode<K, V>::getSucc()       //获取指向当前节点在中序遍历意义下的直接后继节点的指针
{
	AVLNode<K, V>* s = this;
	if (rc != nullptr)                                                         //如果当前节点有右孩子，则直接后继为以右孩子为根节点的子树的最左侧通路尽头节点
	{
		s = rc;                                                                //进入以右孩子为根节点的子树
		while (AVLNode<K, V>::hasLChild(*s) == true)                           //前往最左侧通路尽头
			s = s->lc;
	}
	else                                                                       //否则，当前节点的直接后继为其向上第一个不是右孩子的祖先的母亲节点
	{
		while (AVLNode<K, V>::isRChild(*s) == true)
			s = s->parent;
		s = s->parent;
	}
	return s;
}

template<typename K, typename V> template<typename VST> void AVLNode<K, V>::traverseLevel(VST& visit)     //层次遍历算法比较直观易懂，就不多赘述了
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

template<typename K, typename V> template<typename VST> void AVLNode<K, V>::traverseIn(VST& visit)        //中序遍历算法随机选择一种
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
		s.push(x);                                                             //节点入栈
		x = x->lc;                                                             //继续沿最左侧通路下行
	}
}

template<typename K, typename V> template<typename VST> void AVLNode<K, V>::traverseInI1(AVLNode<K, V>* x, VST& visit)        //第一种迭代版本中序遍历算法
{
	stack<AVLNode<K, V>*> s;
	while (true)
	{
		goAlongLeftBranch(x, s);                                               //调用辅助方法
		if (s.empty() == true)                                                 //栈为空则意味着遍历完成
			break;
		x = s.top();                                                           //转移至栈顶指针所指向的节点，栈顶出栈
		s.pop();
		visit(x->value);                                                       //访问节点
		x = x->rc;                                                             //进入当前节点的右子树
	}
}

template<typename K, typename V> template<typename VST> void AVLNode<K, V>::traverseInI2(AVLNode<K, V>* x, VST& visit)        //这种就是把第一种的两个函数合并了
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
{                                                                              //原理都是相同的，这种用一个回溯标志位代替了栈
	bool backtrack = false;
	while (true)
	{
		if ((backtrack == false) && (AVLNode<K, V>::hasLChild(*x) == true))    //如果回溯标志位为false且当前节点有左孩子
			x = x->lc;                                                         //则继续沿最左侧通路下行
		else                                                                   //否则
		{
			visit(x->value);                                                   //访问当前节点
			if (AVLNode<K, V>::hasRChild(*x) == true)                          //如果当前节点有右孩子
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

template<typename K, typename V> template<typename VST> void AVLNode<K, V>::traverseInR(AVLNode<K, V>* x, VST& visit)
{
	if (x == nullptr)
		return;
	traverseInR(x->lc, visit);
	visit(x->value);
	traverseInR(x->rc, visit);
}


