/*********************************************************************************
 *   @file        SplayTreeMap.h
 *   @brief       The header file for C++ implemented Splay Tree Map
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "SplayNode.h"

template<typename K, typename V> class SplayTreeMap                            //伸展树模板类
{
protected:
	int size;                                                                  //伸展树规模
	SplayNode<K, V>* root;                                                     //指向伸展树根节点的指针
	SplayNode<K, V>* hot;                                                      //查找算法命中节点的母亲节点
	int updateHeight(SplayNode<K, V>* x);                                      //更新节点x的高度，返回x指向的节点的新高度
	void updateHeightAbove(SplayNode<K, V>* x);                                //更新节点x及其祖先的高度
	//查找算法的主体部分，v为指向查找起始节点的指针，hot指向其母亲节点，其语义在此函数执行过程中不变
	//注意此函数参数中的v和hot都是*&的类型，这相当于形参和实参是同一个变量
	//函数返回一个指针的引用，若树中存在关键码为k的节点，则此指针指向该节点；若树中没有这样的节点，则此指针指向如果其将被插入时其应被插入的位置
	SplayNode<K, V>*& searchIn(SplayNode<K, V>*& v, const K& k, SplayNode<K, V>*& hot);
	SplayNode<K, V>* removeAt(SplayNode<K, V>*& x, SplayNode<K, V>*& hot);     //删除x指向的节点，hot指向x指向的节点的母亲节点
	//下面两个函数是用于析构的
	int removeForDestructor(SplayNode<K, V>* x);                               //删除以x为根节点的子树，返回该子树原先的规模
	int removeAtForDestructor(SplayNode<K, V>* x);                             //删除伸展树中x处的节点及其后代，返回被删除节点的数量
	SplayNode<K, V>* splay(SplayNode<K, V>* v);                                //伸展算法，将v指向的节点伸展至根的位置
	void attachAsLChild(SplayNode<K, V>* x, SplayNode<K, V>* lc);              //在x指向的节点与lc指向的节点之间建立母-左孩子关系
	void attachAsRChild(SplayNode<K, V>* x, SplayNode<K, V>* rc);              //在x指向的节点与rc指向的节点之间建立母-右孩子关系
	SplayNode<K, V>*& fromParentTo(const SplayNode<K, V>& sn);                 //获取sn节点的母亲节点的指向sn节点的指针
public:
	SplayTreeMap();                                                            //构造函数
	~SplayTreeMap();                                                           //析构函数
	int getSize() const;                                                       //获取伸展树规模
	bool isEmpty() const;                                                      //判断伸展树是否为空
	SplayNode<K, V>* getRoot() const;                                          //获取指向伸展树根节点的指针
	SplayNode<K, V>*& search(const K& k);                                      //伸展树查找算法，查找关键码为k的节点，返回指针的引用，具体语义见searchIn()
	SplayNode<K, V>* insert(const K& k, const V& v);                           //伸展树插入算法，将关键码k和数据v构造成一个新节点插入
	bool remove(const K& k);                                                   //伸展树删除算法，删除关键码为k的节点，返回删除是否成功
	template<typename VST> void traverseLevel(VST& visit);                     //层次遍历算法
	template<typename VST> void traverseIn(VST& visit);                        //中序遍历算法
};

template<typename K, typename V> int SplayTreeMap<K, V>::updateHeight(SplayNode<K, V>* x)       //x指向的节点的高度等于取左右孩子的高度的大者再加1
{
	int max = (SplayNode<K, V>::getStature(x->lc) > SplayNode<K, V>::getStature(x->rc) ? SplayNode<K, V>::getStature(x->lc) : SplayNode<K, V>::getStature(x->rc));
	return x->height = 1 + max;
}

template<typename K, typename V> void SplayTreeMap<K, V>::updateHeightAbove(SplayNode<K, V>* x)
{
	while (x != nullptr)
	{
		updateHeight(x);
		x = x->parent;
	}
}

template<typename K, typename V> SplayNode<K, V>*& SplayTreeMap<K, V>::searchIn(SplayNode<K, V>*& v, const K& k, SplayNode<K, V>*& hot) //查找算法主体
{
	if (v == nullptr || v->key == k)                                           //如果v为空或者v指向的节点的关键码为k，则返回v
		return v;
	hot = v;                                                                   //否则，hot移动到v这里
	while (true)
	{
		SplayNode<K, V>*& c = (k < hot->key) ? hot->lc : hot->rc;              //根据k与hot->key的大小关系确定移动方向
		if (c == nullptr || c->key == k)                                       //同理，如果c为空或者c指向的节点的关键码为k，则返回c
			return c;
		hot = c;                                                               //否则，hot移动到c这里，然后进行下一次循环
	}
}

template<typename K, typename V> SplayNode<K, V>* SplayTreeMap<K, V>::removeAt(SplayNode<K, V>*& x, SplayNode<K, V>*& hot)    //分情况讨论
{
	SplayNode<K, V>* w = x;                                                    //w也指向要删除的节点
	SplayNode<K, V>* succ = nullptr;
	if (SplayNode<K, V>::hasLChild(*x) == false)                               //如果要删除的节点没有左孩子的话
	{
		x = x->rc;                                                             //x为hot指向的节点的lc或rc本身，因此这里就是将hot的lc或rc与要删除的节点的子节点连接
		succ = x;                                                              //succ指向w的右孩子，也就是x指向的节点
	}
	else if (SplayNode<K, V>::hasRChild(*x) == false)                          //如果要删除的节点有左孩子，但没有右孩子的话
	{
		x = x->lc;                                                             //x为hot指向的节点的lc或rc本身，因此这里就是将hot的lc或rc与要删除的节点的子节点连接
		succ = x;                                                              //succ指向w的左孩子，也就是x指向的节点
	}
	else                                                                       //程序运行到这里意味着要删除的节点既有左孩子也有右孩子
	{
		w = w->getSucc();                                                      //则找到要删除的节点在中序遍历意义下的直接后继节点
		x->key = w->key;                                                       //用直接后继节点的key和value覆盖掉要删除的节点的key和value
		x->value = w->value;
		SplayNode<K, V>* u = w->parent;                                        //然后删除掉直接后继节点就ok了，此节点要么没有孩子要么只有右孩子
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

template<typename K, typename V> int SplayTreeMap<K, V>::removeForDestructor(SplayNode<K, V>* x)//删除以x为根节点的子树，返回该子树原先的规模
{
	fromParentTo(*x) = nullptr;                                                //清除x的母亲节点的指向x的指针
	updateHeightAbove(x->parent);                                              //更新高度
	int count = removeAtForDestructor(x);                                      //实际清理工作由removeAt()完成
	size -= count;                                                             //更新size
	return count;
}

template<typename K, typename V> int SplayTreeMap<K, V>::removeAtForDestructor(SplayNode<K, V>* x)        //递归式实现
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

template<typename K, typename V> SplayNode<K, V>* SplayTreeMap<K, V>::splay(SplayNode<K, V>* v) //伸展算法，自己画画图就能弄明白了，语言说不太清楚，就不赘述了
{
	if (v == nullptr)
		return nullptr;
	SplayNode<K, V>* p = nullptr;
	SplayNode<K, V>* g = nullptr;
	SplayNode<K, V>* gg = nullptr;
	while (((p = v->parent) != nullptr) && ((g = p->parent) != nullptr))
	{
		gg = g->parent;
		if (SplayNode<K, V>::isLChild(*v) == true)
		{
			if (SplayNode<K, V>::isLChild(*p) == true)
			{
				attachAsLChild(g, p->rc);
				attachAsLChild(p, v->rc);
				attachAsRChild(p, g);
				attachAsRChild(v, p);
			}
			else
			{
				attachAsLChild(p, v->rc);
				attachAsRChild(g, v->lc);
				attachAsLChild(v, g);
				attachAsRChild(v, p);
			}
		}
		else if (SplayNode<K, V>::isRChild(*p) == true)
		{
			attachAsRChild(g, p->lc);
			attachAsRChild(p, v->lc);
			attachAsLChild(p, g);
			attachAsLChild(v, p);
		}
		else
		{
			attachAsRChild(p, v->lc);
			attachAsLChild(g, v->rc);
			attachAsRChild(v, g);
			attachAsLChild(v, p);
		}
		if (gg == nullptr)
			v->parent = nullptr;
		else
			(g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		updateHeight(g);
		updateHeight(p);
		updateHeight(v);
	}
	if ((p = v->parent) != nullptr)
	{
		if (SplayNode<K, V>::isLChild(*v) == true)
		{
			attachAsLChild(p, v->rc);
			attachAsRChild(v, p);
		}
		else
		{
			attachAsRChild(p, v->lc);
			attachAsLChild(v, p);
		}
		updateHeight(p);
		updateHeight(v);
	}
	v->parent = nullptr;
	return v;
}

template<typename K, typename V> void SplayTreeMap<K, V>::attachAsLChild(SplayNode<K, V>* x, SplayNode<K, V>* lc)
{                                                                              //在x指向的节点与lc指向的节点之间建立母-左孩子关系
	x->lc = lc;
	if (lc != nullptr)
		lc->parent = x;
}

template<typename K, typename V> void SplayTreeMap<K, V>::attachAsRChild(SplayNode<K, V>* x, SplayNode<K, V>* rc)
{                                                                              //在x指向的节点与lc指向的节点之间建立母-左孩子关系
	x->rc = rc;
	if (rc != nullptr)
		rc->parent = x;
}

template<typename K, typename V> SplayNode<K, V>*& SplayTreeMap<K, V>::fromParentTo(const SplayNode<K, V>& sn)
{
	return (SplayNode<K, V>::isRoot(sn) == true) ? root : ((SplayNode<K, V>::isLChild(sn) == true) ? (sn.parent)->lc : (sn.parent)->rc);
}

template<typename K, typename V> SplayTreeMap<K, V>::SplayTreeMap()
{
	size = 0;
	root = nullptr;
	hot = nullptr;
}

template<typename K, typename V> SplayTreeMap<K, V>::~SplayTreeMap()
{
	if (getSize() > 0)
		removeForDestructor(root);
}

template<typename K, typename V> int SplayTreeMap<K, V>::getSize() const
{
	return size;
}

template<typename K, typename V> bool SplayTreeMap<K, V>::isEmpty() const
{
	return !static_cast<bool>(getSize());
}

template<typename K, typename V> SplayNode<K, V>* SplayTreeMap<K, V>::getRoot() const
{
	return root;
}

template<typename K, typename V> SplayNode<K, V>*& SplayTreeMap<K, V>::search(const K& k)       //伸展树查找算法，查找关键码为k的节点
{
	SplayNode<K, V>*& x = searchIn(root, k, hot = nullptr);                    //直接调用searchIn()，即从根节点开始查找关键码为k的节点，hot初始值显然为nullptr
	root = splay((x != nullptr) ? x : hot);                                    //如果x不为空，则将此节点伸展至根位置，如果x为空，则只能将hot指向的节点伸展至根
	return root;
}

template<typename K, typename V> SplayNode<K, V>* SplayTreeMap<K, V>::insert(const K& k, const V& v)      //伸展树插入算法
{
	if (root == nullptr)                                                       //如果root为空，则直接在root处插入新节点即可
	{
		size++;
		return root = new SplayNode<K, V>(k, v);
	}
	if (search(k)->key == k)                                                   //调用search()查找关键码为k的节点，如果得到的指针(即root)指向的节点的关键码为k
		return root;                                                           //说明树中已存在关键码为k的节点，因此不需要插入，直接返回root即可
	SplayNode<K, V>* t = root;                                                 //t也指向根节点
	if (root->key < k)                                                         //如果根节点的key小于k
	{
		root = new SplayNode<K, V>(k, v, nullptr, t, t->rc);                   //则root创建一个新的根节点，左右孩子分别是t指向的节点和t指向的节点的右孩子
		t->parent = root;                                                      //向上连接t指向的节点和根节点
		if (SplayNode<K, V>::hasRChild(*t) == true)                            //如果t指向的节点的rc非空
		{
			t->rc->parent = root;                                              //向上连接t->rc指向的节点和根节点
			t->rc = nullptr;                                                   //切断t->rc
		}
	}
	else                                                                       //原理相同，就不多赘述了
	{
		root = new SplayNode<K, V>(k, v, nullptr, t->lc, t);
		t->parent = root;
		if (SplayNode<K, V>::hasLChild(*t) == true)
		{
			t->lc->parent = root;
			t->lc = nullptr;
		}
	}
	updateHeightAbove(t);                                                      //更新高度
	size++;                                                                    //更新规模
	return root;                                                               //返回root
}

template<typename K, typename V> bool SplayTreeMap<K, V>::remove(const K& k)   //伸展树删除算法，返回删除是否成功
{
	if (root == nullptr || search(k)->key != k)                                //如果root为空或者调用search()查找k得到的指针指向的节点的关键码不是k
		return false;                                                          //则删除压根就没法进行，因此删除失败，直接返回false
	SplayNode<K, V>* w = root;                                                 //因为之前调用了search()，因此要删除的节点成为了新的根节点
	                                                                           //w指向根节点，即w指向要删除的节点
	if (SplayNode<K, V>::hasLChild(*root) == false)                            //如果根节点没有左孩子
	{
		root = root->rc;                                                       //root指向根节点的右孩子
		if (root != nullptr)                                                   //如果root非空，则其指向的节点的parent指针置为nullptr
			root->parent = nullptr;
	}
	else if (SplayNode<K, V>::hasRChild(*root) == false)                       //对称情况，同理
	{
		root = root->lc;
		if (root != nullptr)
			root->parent = nullptr;
	}
	else                                                                       //根节点既有左孩子也有右孩子
	{
		SplayNode<K, V>* left_tree = root->lc;                                 //left_tree指向根节点的左孩子
		left_tree->parent = nullptr;                                           //分离根节点与其左子树
		root->lc = nullptr;
		root = root->rc;                                                       //root指向根节点的右孩子
		root->parent = nullptr;                                                //root指向的节点的parent指针置为nullptr
		search(w->key);                                                        //从新的根节点开始向下查找w->key，查找必然失败，但是"新树"的最小节点会伸展至树根
		root->lc = left_tree;                                                  //连接根节点与之前分离的左子树
		left_tree->parent = root;                                              //向上连接
	}
	delete w;                                                                  //释放掉w
	w = nullptr;
	size--;                                                                    //更新规模
	if (root != nullptr)                                                       //更新高度
		updateHeight(root);
	return true;                                                               //删除成功，返回true
}

template<typename K, typename V> template<typename VST> void SplayTreeMap<K, V>::traverseLevel(VST& visit)
{
	if (getRoot() != nullptr)
		root->traverseLevel(visit);
}

template<typename K, typename V> template<typename VST> void SplayTreeMap<K, V>::traverseIn(VST& visit)
{
	if (getRoot() != nullptr)
		root->traverseIn(visit);
}



