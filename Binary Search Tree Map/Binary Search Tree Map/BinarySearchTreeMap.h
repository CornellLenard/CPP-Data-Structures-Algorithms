/*********************************************************************************
 *   @file        BinarySearchTreeMap.h
 *   @brief       The header file for C++ implemented Binary Search Tree Map
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "BSTNode.h"

template<typename K, typename V> class BinarySearchTreeMap                     //二叉搜索树模板类
{
protected:
	int size;                                                                  //二叉搜索树规模
	BSTNode<K, V>* root;                                                       //指向二叉搜索树根节点的指针
	BSTNode<K, V>* hot;                                                        //查找算法命中节点的母亲节点
	int updateHeight(BSTNode<K, V>* x);                                        //更新节点x的高度，返回x指向的节点的新高度
	void updateHeightAbove(BSTNode<K, V>* x);                                  //更新节点x及其祖先的高度
	//查找算法的主体部分，v为指向查找起始节点的指针，hot指向其母亲节点，其语义在此函数执行过程中不变
	//注意此函数参数中的v和hot都是*&的类型，这相当于形参和实参是同一个变量
	//函数返回一个指针的引用，若树中存在关键码为k的节点，则此指针指向该节点；若树中没有这样的节点，则此指针指向如果其将被插入时其应被插入的位置
	BSTNode<K, V>*& searchIn(BSTNode<K, V>*& v, const K& k, BSTNode<K, V>*& hot);
	BSTNode<K, V>* removeAt(BSTNode<K, V>*& x, BSTNode<K, V>*& hot);           //删除x指向的节点，hot指向x指向的节点的母亲节点
	//下面两个函数是用于析构的
	int removeForDestructor(BSTNode<K, V>* x);                                 //删除以x为根节点的子树，返回该子树原先的规模
	int removeAtForDestructor(BSTNode<K, V>* x);                               //删除二叉搜索树中x处的节点及其后代，返回被删除节点的数量
	//3+4重构算法
	//BSTNode<K, V>* connect34(BSTNode<K, V>* t0, BSTNode<K, V>* t1, BSTNode<K, V>* t2, BSTNode<K, V>* t3, BSTNode<K, V>* a, BSTNode<K, V>* b, BSTNode<K, V>* c);
	//旋转调整算法
	//BSTNode<K, V>* rotateAt(BSTNode<K, V>* x);
	BSTNode<K, V>*& fromParentTo(const BSTNode<K, V>& bn);                     //获取bn节点的母亲节点的指向bn节点的指针
public:
	BinarySearchTreeMap();                                                     //构造函数
	~BinarySearchTreeMap();                                                    //析构函数
	int getSize() const;                                                       //获取二叉搜索树规模
	bool isEmpty() const;                                                      //判断二叉搜索树是否为空
	BSTNode<K, V>* getRoot() const;                                            //获取指向二叉搜索树根节点的指针
	BSTNode<K, V>*& search(const K& k);                                        //二叉搜索树查找算法，查找关键码为k的节点，返回指针的引用，具体语义见searchIn()
	BSTNode<K, V>* insert(const K& k, const V& v);                             //二叉搜索树插入算法，将关键码k和数据v构造成一个新节点插入
	bool remove(const K& k);                                                   //二叉搜索树删除算法，删除关键码为k的节点，返回删除是否成功
	template<typename VST> void traverseLevel(VST& visit);                     //层次遍历算法
	template<typename VST> void traverseIn(VST& visit);                        //中序遍历算法
};

template<typename K, typename V> int BinarySearchTreeMap<K, V>::updateHeight(BSTNode<K, V>* x)  //x指向的节点的高度等于取左右孩子的高度的大者再加1
{
	int max = (BSTNode<K, V>::getStature(x->lc) > BSTNode<K, V>::getStature(x->rc) ? BSTNode<K, V>::getStature(x->lc) : BSTNode<K, V>::getStature(x->rc));
	return x->height = 1 + max;
}

template<typename K, typename V> void BinarySearchTreeMap<K, V>::updateHeightAbove(BSTNode<K, V>* x)
{
	while (x != nullptr)
	{
		updateHeight(x);
		x = x->parent;
	}
}

template<typename K, typename V> BSTNode<K, V>*& BinarySearchTreeMap<K, V>::searchIn(BSTNode<K, V>*& v, const K& k, BSTNode<K, V>*& hot)//查找算法主体
{
	if (v == nullptr || v->key == k)                                           //如果v为空或者v指向的节点的关键码为k，则返回v
		return v;
	hot = v;                                                                   //否则，hot移动到v这里
	while (true)
	{
		BSTNode<K, V>*& c = (k < hot->key) ? hot->lc : hot->rc;                //根据k与hot->key的大小关系确定移动方向
		if (c == nullptr || c->key == k)                                       //同理，如果c为空或者c指向的节点的关键码为k，则返回c
			return c;
		hot = c;                                                               //否则，hot移动到c这里，然后进行下一次循环
	}
}

template<typename K, typename V> BSTNode<K, V>* BinarySearchTreeMap<K, V>::removeAt(BSTNode<K, V>*& x, BSTNode<K, V>*& hot)   //分情况讨论
{
	BSTNode<K, V>* w = x;                                                      //w也指向要删除的节点
	BSTNode<K, V>* succ = nullptr;
	if (BSTNode<K, V>::hasLChild(*x) == false)                                 //如果要删除的节点没有左孩子的话
	{
		x = x->rc;                                                             //x为hot指向的节点的lc或rc本身，因此这里就是将hot的lc或rc与要删除的节点的子节点连接
		succ = x;                                                              //succ指向w的右孩子，也就是x指向的节点
	}
	else if (BSTNode<K, V>::hasRChild(*x) == false)                            //如果要删除的节点有左孩子，但没有右孩子的话
	{
		x = x->lc;                                                             //x为hot指向的节点的lc或rc本身，因此这里就是将hot的lc或rc与要删除的节点的子节点连接
		succ = x;                                                              //succ指向w的左孩子，也就是x指向的节点
	}
	else                                                                       //程序运行到这里意味着要删除的节点既有左孩子也有右孩子
	{
		w = w->getSucc();                                                      //则找到要删除的节点在中序遍历意义下的直接后继节点
		x->key = w->key;                                                       //用直接后继节点的key和value覆盖掉要删除的节点的key和value
		x->value = w->value;
		BSTNode<K, V>* u = w->parent;                                          //然后删除掉直接后继节点就ok了，此节点要么没有孩子要么只有右孩子
		succ = w->rc;
		(u == x ? u->rc : u->lc) = succ;
	}
	hot = w->parent;                                                           //确保hot位置正确
	if (succ != nullptr)                                                       //如果succ非空
		succ->parent = hot;                                                    //要删除的节点被删除后，succ就应该是hot的子节点，这里进行向上的连接
	delete w;                                                                  //释放掉要删除的节点
	w = nullptr;
	return succ;
}

template<typename K, typename V> int BinarySearchTreeMap<K, V>::removeForDestructor(BSTNode<K, V>* x)     //删除以x为根节点的子树，返回该子树原先的规模
{
	fromParentTo(*x) = nullptr;                                                //清除x的母亲节点的指向x的指针
	updateHeightAbove(x->parent);                                              //更新高度
	int count = removeAtForDestructor(x);                                      //实际清理工作由removeAt()完成
	size -= count;                                                             //更新size
	return count;
}

template<typename K, typename V> int BinarySearchTreeMap<K, V>::removeAtForDestructor(BSTNode<K, V>* x)   //递归式实现
{
	if (x == nullptr)
		return 0;
	int count = 1 + removeAtForDestructor(x->lc) + removeAtForDestructor(x->rc);
	//release(x->data);
	//release(x);
	delete x;
	x = nullptr;
	return count;
}

template<typename K, typename V> BSTNode<K, V>*& BinarySearchTreeMap<K, V>::fromParentTo(const BSTNode<K, V>& bn)
{
	return (BSTNode<K, V>::isRoot(bn) == true) ? root : ((BSTNode<K, V>::isLChild(bn) == true) ? (bn.parent)->lc : (bn.parent)->rc);
}

template<typename K, typename V> BinarySearchTreeMap<K, V>::BinarySearchTreeMap()
{
	size = 0;
	root = nullptr;
	hot = nullptr;
}

template<typename K, typename V> BinarySearchTreeMap<K, V>::~BinarySearchTreeMap()
{
	if (getSize() > 0)
		removeForDestructor(root);
}

template<typename K, typename V> int BinarySearchTreeMap<K, V>::getSize() const
{
	return size;
}

template<typename K, typename V> bool BinarySearchTreeMap<K, V>::isEmpty() const
{
	return !static_cast<bool>(getSize());
}

template<typename K, typename V> BSTNode<K, V>* BinarySearchTreeMap<K, V>::getRoot() const
{
	return root;
}

template<typename K, typename V> BSTNode<K, V>*& BinarySearchTreeMap<K, V>::search(const K& k)  //二叉搜索树查找算法，查找关键码为k的节点
{
	return searchIn(root, k, hot = nullptr);                                   //直接调用searchIn()，即从根节点开始查找关键码为k的节点，hot初始值显然为nullptr
}

template<typename K, typename V> BSTNode<K, V>* BinarySearchTreeMap<K, V>::insert(const K& k, const V& v) //二叉搜索树插入算法
{
	BSTNode<K, V>*& x = search(k);                                             //调用search()，查找关键码为k的节点
	if (x == nullptr)                                                          //如果x为空指针，则意味着并没有关键码为k的节点，所以可以插入
	{
		x = new BSTNode<K, V>(k, v, hot);                                      //search()返回的是*&，因此直接用x开辟一个新节点，其母亲节点就是此时hot所指的节点
		size++;                                                                //更新规模
		updateHeightAbove(x);                                                  //更新高度
	}
	return x;
}

template<typename K, typename V> bool BinarySearchTreeMap<K, V>::remove(const K& k)   //二叉搜索树删除算法，返回删除是否成功
{
	BSTNode<K, V>*& x = search(k);                                             //调用search()，查找关键码为k的节点
	if (x == nullptr)                                                          //如果x为空指针，则意味着没有关键码为k的节点，所以删除失败，返回false
		return false;
	removeAt(x, hot);                                                          //调用removeAt()，进行删除工作
	size--;                                                                    //更新规模
	updateHeightAbove(hot);                                                    //更新高度
	return true;                                                               //删除成功，返回true
}

template<typename K, typename V> template<typename VST> void BinarySearchTreeMap<K, V>::traverseLevel(VST& visit)
{
	if (getRoot() != nullptr)
		root->traverseLevel(visit);
}

template<typename K, typename V> template<typename VST> void BinarySearchTreeMap<K, V>::traverseIn(VST& visit)
{
	if (getRoot() != nullptr)
		root->traverseIn(visit);
}


