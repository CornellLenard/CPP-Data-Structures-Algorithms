/*********************************************************************************
 *   @file        AVLTreeMap.h
 *   @brief       The header file for C++ implemented AVL Tree Map
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "AVLNode.h"

template<typename K, typename V> class AVLTreeMap                              //AVL树模板类
{
protected:
	int size;                                                                  //AVL树规模
	AVLNode<K, V>* root;                                                       //指向AVL树根节点的指针
	AVLNode<K, V>* hot;                                                        //查找算法命中节点的母亲节点
	int updateHeight(AVLNode<K, V>* x);                                        //更新节点x的高度，返回x指向的节点的新高度
	void updateHeightAbove(AVLNode<K, V>* x);                                  //更新节点x及其祖先的高度
	//查找算法的主体部分，v为指向查找起始节点的指针，hot指向其母亲节点，其语义在此函数执行过程中不变
	//注意此函数参数中的v和hot都是*&的类型，这相当于形参和实参是同一个变量
	//函数返回一个指针的引用，若树中存在关键码为k的节点，则此指针指向该节点；若树中没有这样的节点，则此指针指向如果其将被插入时其应被插入的位置
	AVLNode<K, V>*& searchIn(AVLNode<K, V>*& v, const K& k, AVLNode<K, V>*& hot);
	AVLNode<K, V>* removeAt(AVLNode<K, V>*& x, AVLNode<K, V>*& hot);           //删除x指向的节点，hot指向x指向的节点的母亲节点
	//下面两个函数是用于析构的
	int removeForDestructor(AVLNode<K, V>* x);                                 //删除以x为根节点的子树，返回该子树原先的规模
	int removeAtForDestructor(AVLNode<K, V>* x);                               //删除AVL树中x处的节点及其后代，返回被删除节点的数量
	//3+4重构算法
	AVLNode<K, V>* connect34(AVLNode<K, V>* t0, AVLNode<K, V>* t1, AVLNode<K, V>* t2, AVLNode<K, V>* t3, AVLNode<K, V>* a, AVLNode<K, V>* b, AVLNode<K, V>* c);
	//旋转调整算法
	AVLNode<K, V>* rotateAt(AVLNode<K, V>* v);
	AVLNode<K, V>*& fromParentTo(const AVLNode<K, V>& avln);                   //获取avln节点的母亲节点的指向avln节点的指针
public:
	AVLTreeMap();                                                              //构造函数
	~AVLTreeMap();                                                             //析构函数
	int getSize() const;                                                       //获取AVL树规模
	bool isEmpty() const;                                                      //判断AVL树是否为空
	AVLNode<K, V>* getRoot() const;                                            //获取指向AVL树根节点的指针
	AVLNode<K, V>*& search(const K& k);                                        //AVL树查找算法，查找关键码为k的节点，返回指针的引用，具体语义见searchIn()
	AVLNode<K, V>* insert(const K& k, const V& v);                             //AVL树插入算法，将关键码k和数据v构造成一个新节点插入
	bool remove(const K& k);                                                   //AVL树删除算法，删除关键码为k的节点，返回删除是否成功
	template<typename VST> void traverseLevel(VST& visit);                     //层次遍历算法
	template<typename VST> void traverseIn(VST& visit);                        //中序遍历算法
};

template<typename K, typename V> int AVLTreeMap<K, V>::updateHeight(AVLNode<K, V>* x) //x指向的节点的高度等于取左右孩子的高度的大者再加1
{
	int max = (AVLNode<K, V>::getStature(x->lc) > AVLNode<K, V>::getStature(x->rc) ? AVLNode<K, V>::getStature(x->lc) : AVLNode<K, V>::getStature(x->rc));
	return x->height = 1 + max;
}

template<typename K, typename V> void AVLTreeMap<K, V>::updateHeightAbove(AVLNode<K, V>* x)
{
	while (x != nullptr)
	{
		updateHeight(x);
		x = x->parent;
	}
}

template<typename K, typename V> AVLNode<K, V>*& AVLTreeMap<K, V>::searchIn(AVLNode<K, V>*& v, const K& k, AVLNode<K, V>*& hot)         //查找算法主体
{
	if (v == nullptr || v->key == k)                                           //如果v为空或者v指向的节点的关键码为k，则返回v
		return v;
	hot = v;                                                                   //否则，hot移动到v这里
	while (true)
	{
		AVLNode<K, V>*& c = (k < hot->key) ? hot->lc : hot->rc;                //根据k与hot->key的大小关系确定移动方向
		if (c == nullptr || c->key == k)                                       //同理，如果c为空或者c指向的节点的关键码为k，则返回c
			return c;
		hot = c;                                                               //否则，hot移动到c这里，然后进行下一次循环
	}
}

template<typename K, typename V> AVLNode<K, V>* AVLTreeMap<K, V>::removeAt(AVLNode<K, V>*& x, AVLNode<K, V>*& hot)  //分情况讨论
{
	AVLNode<K, V>* w = x;                                                      //w也指向要删除的节点
	AVLNode<K, V>* succ = nullptr;
	if (AVLNode<K, V>::hasLChild(*x) == false)                                 //如果要删除的节点没有左孩子的话
	{
		x = x->rc;                                                             //x为hot指向的节点的lc或rc本身，因此这里就是将hot的lc或rc与要删除的节点的子节点连接
		succ = x;                                                              //succ指向w的右孩子，也就是x指向的节点
	}
	else if (AVLNode<K, V>::hasRChild(*x) == false)                            //如果要删除的节点有左孩子，但没有右孩子的话
	{
		x = x->lc;                                                             //x为hot指向的节点的lc或rc本身，因此这里就是将hot的lc或rc与要删除的节点的子节点连接
		succ = x;                                                              //succ指向w的左孩子，也就是x指向的节点
	}
	else                                                                       //程序运行到这里意味着要删除的节点既有左孩子也有右孩子
	{
		w = w->getSucc();                                                      //则找到要删除的节点在中序遍历意义下的直接后继节点
		x->key = w->key;                                                       //用直接后继节点的key和value覆盖掉要删除的节点的key和value
		x->value = w->value;
		AVLNode<K, V>* u = w->parent;                                          //然后删除掉直接后继节点就ok了，此节点要么没有孩子要么只有右孩子
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

template<typename K, typename V> int AVLTreeMap<K, V>::removeForDestructor(AVLNode<K, V>* x)    //删除以x为根节点的子树，返回该子树原先的规模
{
	fromParentTo(*x) = nullptr;                                                //清除x的母亲节点的指向x的指针
	updateHeightAbove(x->parent);                                              //更新高度
	int count = removeAtForDestructor(x);                                      //实际清理工作由removeAt()完成
	size -= count;                                                             //更新size
	return count;
}

template<typename K, typename V> int AVLTreeMap<K, V>::removeAtForDestructor(AVLNode<K, V>* x)  //递归式实现
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

template<typename K, typename V> AVLNode<K, V>* AVLTreeMap<K, V>::connect34(AVLNode<K, V>* a, AVLNode<K, V>* b, AVLNode<K, V>* c,
	AVLNode<K, V>* t0, AVLNode<K, V>* t1, AVLNode<K, V>* t2, AVLNode<K, V>* t3)
{
	a->lc = t0;                                                                //将3个节点与4棵子树之间的关系进行重构
	if (t0 != nullptr)                                                         //具体的操作步骤很简单，可配合ppt里的图片理解，语言表达不太直观，就不多赘述了
		t0->parent = a;
	a->rc = t1;
	if (t1 != nullptr)
		t1->parent = a;
	c->lc = t2;
	if (t2 != nullptr)
		t2->parent = c;
	c->rc = t3;
	if (t3 != nullptr)
		t3->parent = c;
	b->lc = a;
	a->parent = b;
	b->rc = c;
	c->parent = b;
	updateHeight(a);
	updateHeight(c);
	updateHeight(b);
	return b;
}

template<typename K, typename V> AVLNode<K, V>* AVLTreeMap<K, V>::rotateAt(AVLNode<K, V>* v)    //3+4重构算法的核心，根据四种情况来确定connect34()的参数顺序
{
	AVLNode<K, V>* p = v->parent;
	AVLNode<K, V>* g = p->parent;
	if (AVLNode<K, V>::isLChild(*p) == true)
	{
		if (AVLNode<K, V>::isLChild(*v) == true)
		{
			p->parent = g->parent;
			return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
		}
		else
		{
			v->parent = g->parent;
			return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
		}
	}
	else
	{
		if (AVLNode<K, V>::isRChild(*v) == true)
		{
			p->parent = g->parent;
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}
		else
		{
			v->parent = g->parent;
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
	}
}

template<typename K, typename V> AVLNode<K, V>*& AVLTreeMap<K, V>::fromParentTo(const AVLNode<K, V>& avln)
{
	return (AVLNode<K, V>::isRoot(avln) == true) ? root : ((AVLNode<K, V>::isLChild(avln) == true) ? (avln.parent)->lc : (avln.parent)->rc);
}

template<typename K, typename V> AVLTreeMap<K, V>::AVLTreeMap()
{
	size = 0;
	root = nullptr;
	hot = nullptr;
}

template<typename K, typename V> AVLTreeMap<K, V>::~AVLTreeMap()
{
	if (getSize() > 0)
		removeForDestructor(root);
}

template<typename K, typename V> int AVLTreeMap<K, V>::getSize() const
{
	return size;
}

template<typename K, typename V> bool AVLTreeMap<K, V>::isEmpty() const
{
	return !static_cast<bool>(getSize());
}

template<typename K, typename V> AVLNode<K, V>* AVLTreeMap<K, V>::getRoot() const
{
	return root;
}

template<typename K, typename V> AVLNode<K, V>*& AVLTreeMap<K, V>::search(const K& k)           //AVL树查找算法，查找关键码为k的节点
{
	return searchIn(root, k, hot = nullptr);                                   //直接调用searchIn()，即从根节点开始查找关键码为k的节点，hot初始值显然为nullptr
}

template<typename K, typename V> AVLNode<K, V>* AVLTreeMap<K, V>::insert(const K& k, const V& v)//AVL树插入算法
{
	AVLNode<K, V>*& x = search(k);                                             //调用search()，查找关键码为k的节点
	if (x != nullptr)                                                          //如果x不是空指针，说明已经有节点关键码为k，则不进行插入，直接返回x
		return x;
	x = new AVLNode<K, V>(k, v, hot);                                          //search()返回的是*&，因此直接用x开辟一个新节点，其母亲节点就是此时hot所指的节点
	AVLNode<K, V>* res = x;                                                    //创建结果指针，和x指向同一节点，即新插入的节点
	size++;                                                                    //更新规模
	for (AVLNode<K, V>* g = hot; g != nullptr; g = g->parent)                  //从x指向的节点的母亲节点开始，逐层向上检查各祖先节点
	{
		if (AVLNode<K, V>::isAVLBalanced(*g) == false)                         //如果祖先节点失衡，则进行调整
		{
			AVLNode<K, V>*& from_parent_to = fromParentTo(*g);                 //先获取当前状态下g指向的节点的母亲节点的指向g节点的指针
			from_parent_to = rotateAt(AVLNode<K, V>::getTallerChild(AVLNode<K, V>::getTallerChild(g))); //先进行调整，再向下连接调整完毕的子树
			break;                                                             //g指向的节点恢复平衡后，局部子树高度必然复原，其祖先亦必如此，故调整结束
		}
		else
			updateHeight(g);                                                   //对于平衡的祖先节点，要更新其高度
	}
	return res;
}

template<typename K, typename V> bool AVLTreeMap<K, V>::remove(const K& k)     //AVL树删除算法，返回删除是否成功
{
	AVLNode<K, V>*& x = search(k);                                             //调用search()，查找关键码为k的节点
	if (x == nullptr)                                                          //如果x为空指针，则意味着没有关键码为k的节点，所以删除失败，返回false
		return false;
	removeAt(x, hot);                                                          //否则，可以删除，调用removeAt()进行删除工作
	size--;                                                                    //更新规模
	for (AVLNode<K, V>* g = hot; g != nullptr; g = g->parent)                  //从x指向的节点的母亲节点开始，逐层向上检查各祖先节点
	{
		if (AVLNode<K, V>::isAVLBalanced(*g) == false)                         //如果祖先节点失衡，则进行调整
		{
			AVLNode<K, V>*& from_parent_to = fromParentTo(*g);                 //先获取当前状态下g指向的节点的母亲节点的指向g节点的指针
			from_parent_to = rotateAt(AVLNode<K, V>::getTallerChild(AVLNode<K, V>::getTallerChild(g))); //先进行调整，再向下连接调整完毕的子树
			g = from_parent_to;
		}
		updateHeight(g);                                                       //无论祖先节点平衡与否，都要进行高度更新
	}
	return true;                                                               //删除成功，返回true
}

template<typename K, typename V> template<typename VST> void AVLTreeMap<K, V>::traverseLevel(VST& visit)
{
	if (getRoot() != nullptr)
		root->traverseLevel(visit);
}

template<typename K, typename V> template<typename VST> void AVLTreeMap<K, V>::traverseIn(VST& visit)
{
	if (getRoot() != nullptr)
		root->traverseIn(visit);
}



