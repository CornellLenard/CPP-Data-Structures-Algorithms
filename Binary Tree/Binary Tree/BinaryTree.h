/*********************************************************************************
 *   @file        BinaryTree.h
 *   @brief       The header file for C++ implemented Binary Tree
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "BinNode.h"

template<typename T> class BinaryTree                                          //二叉树模板类
{
protected:
	int size;                                                                  //二叉树规模
	BinNode<T>* root;                                                          //指向二叉树根节点的指针
	int updateHeight(BinNode<T>* x);                                           //更新节点x的高度，返回x指向的节点的新高度
	void updateHeightAbove(BinNode<T>* x);                                     //更新节点x及其祖先的高度
	int removeAt(BinNode<T>* x);                                               //删除二叉树中x处的节点及其后代，返回被删除节点的数量
	BinNode<T>*& fromParentTo(const BinNode<T>& bn);                           //获取bn节点的母亲节点的指向bn节点的指针
public:
	BinaryTree();                                                              //构造函数
	~BinaryTree();                                                             //析构函数
	int getSize() const;                                                       //获取二叉树规模
	bool isEmpty() const;                                                      //判断二叉树是否为空
	BinNode<T>* getRoot() const;                                               //获取指向二叉树根节点的指针
	BinNode<T>* insertAsRoot(const T& e);                                      //插入根节点
	BinNode<T>* insertAsLC(BinNode<T>* x, const T& e);                         //e作为x指向的节点的左孩子插入
	BinNode<T>* insertAsRC(BinNode<T>* x, const T& e);                         //e作为x指向的节点的右孩子插入
	BinNode<T>* attachAsLC(BinNode<T>* x, BinaryTree<T>*& bt);                 //bt作为x指向的节点的左子树接入
	BinNode<T>* attachAsRC(BinNode<T>* x, BinaryTree<T>*& bt);                 //bt作为x指向的节点的右子树接入
	int remove(BinNode<T>* x);                                                 //删除以x指向的节点为根节点的子树，返回该子树原先的规模
	BinaryTree<T>* secede(BinNode<T>* x);                                      //将子树x从当前树中摘除，并将其转换为一棵独立子树
	template<typename VST> void traverseLevel(VST& visit);                     //层次遍历算法
	template<typename VST> void traversePre(VST& visit);                       //先序遍历算法
	template<typename VST> void traverseIn(VST& visit);                        //中序遍历算法
	template<typename VST> void traversePost(VST& visit);                      //后序遍历算法
};

template<typename T> int BinaryTree<T>::updateHeight(BinNode<T>* x)            //x指向的节点的高度等于取左右孩子的高度的大者再加1
{
	int max = (BinNode<T>::getStature(x->lc) > BinNode<T>::getStature(x->rc) ? BinNode<T>::getStature(x->lc) : BinNode<T>::getStature(x->rc));
	return x->height = 1 + max;
}

template<typename T> void BinaryTree<T>::updateHeightAbove(BinNode<T>* x)
{
	while (x != nullptr)
	{
		updateHeight(x);
		x = x->parent;
	}
}

template<typename T> int BinaryTree<T>::removeAt(BinNode<T>* x)                //递归式实现
{
	if (x == nullptr)
		return 0;
	int count = 1 + removeAt(x->lc) + removeAt(x->rc);
	//release(x->data);
	//release(x);
	delete x;
	x = nullptr;
	return count;
}

template<typename T> BinNode<T>*& BinaryTree<T>::fromParentTo(const BinNode<T>& bn)
{
	return (BinNode<T>::isRoot(bn) == true) ? root : ((BinNode<T>::isLChild(bn) == true) ? (bn.parent)->lc : (bn.parent)->rc);
}

template<typename T> BinaryTree<T>::BinaryTree() :size(0), root(nullptr) {}

template<typename T> BinaryTree<T>::~BinaryTree()
{
	if (getSize() > 0)
		remove(root);
}

template<typename T> int BinaryTree<T>::getSize() const
{
	return size;
}

template<typename T> bool BinaryTree<T>::isEmpty() const
{
	return !static_cast<bool>(getSize());
}

template<typename T> BinNode<T>* BinaryTree<T>::getRoot() const
{
	return root;
}

template<typename T> BinNode<T>* BinaryTree<T>::insertAsRoot(const T& e)
{
	size = 1;
	return root = new BinNode<T>(e);
}

template<typename T> BinNode<T>* BinaryTree<T>::insertAsLC(BinNode<T>* x, const T& e) //插入算法直接调用对应节点的对应插入算法
{
	size++;
	x->insertAsLC(e);
	updateHeightAbove(x);                                                      //更新高度
	return x->lc;
}

template<typename T> BinNode<T>* BinaryTree<T>::insertAsRC(BinNode<T>* x, const T& e)
{
	size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rc;
}

template<typename T> BinNode<T>* BinaryTree<T>::attachAsLC(BinNode<T>* x, BinaryTree<T>*& bt)   //bt作为x指向的节点的左子树接入
{
	x->lc = bt->getRoot();                                                     //构造x到bt指向的树的根节点的连接
	if (x->lc != nullptr)
		x->lc->parent = x;                                                     //构造bt指向的树的根节点到x的连接
	size += bt->getSize();                                                     //size更新
	updateHeightAbove(x);                                                      //高度更新
	bt->root = nullptr;                                                        //bt指向的树的内部变量进行清理
	bt->size = 0;
	//release(bt);
	bt = nullptr;
	return x;
}

template<typename T> BinNode<T>* BinaryTree<T>::attachAsRC(BinNode<T>* x, BinaryTree<T>*& bt)   //bt作为x指向的节点的右子树接入
{
	x->rc = bt->getRoot();                                                     //构造x到bt指向的树的根节点的连接
	if (x->rc != nullptr)
		x->rc->parent = x;                                                     //构造bt指向的树的根节点到x的连接
	size += bt->getSize();                                                     //size更新
	updateHeightAbove(x);                                                      //高度更新
	bt->root = nullptr;                                                        //bt指向的树的内部变量进行清理
	bt->size = 0;
	//release(bt);
	bt = nullptr;
	return x;
}

template<typename T> int BinaryTree<T>::remove(BinNode<T>* x)                  //删除以x为根节点的子树，返回该子树原先的规模
{
	fromParentTo(*x) = nullptr;                                                //清除x的母亲节点的指向x的指针
	updateHeightAbove(x->parent);                                              //更新高度
	int count = removeAt(x);                                                   //实际清理工作由removeAt()完成
	size -= count;                                                             //更新size
	return count;
}

template<typename T> BinaryTree<T>* BinaryTree<T>::secede(BinNode<T>* x)       //将子树x从当前树中摘除，并将其转换为一棵独立子树
{
	fromParentTo(*x) = nullptr;                                                //清除x的母亲节点的指向x的指针
	updateHeightAbove(x->parent);                                              //更新高度
	BinaryTree<T>* bt = new BinaryTree<T>();                                   //新建一棵二叉树
	bt->root = x;                                                              //新二叉树的根节点即为x指向的节点
	x->parent = nullptr;                                                       //x指向的节点的parent指针置为nullptr
	bt->size = x->getSize();                                                   //更新新二叉树size
	size -= bt->getSize();                                                     //更新原二叉树size
	return bt;
}

template<typename T> template<typename VST> void BinaryTree<T>::traverseLevel(VST& visit)
{
	if (getRoot() != nullptr)
		root->traverseLevel(visit);
}

template<typename T> template<typename VST> void BinaryTree<T>::traversePre(VST& visit)
{
	if (getRoot() != nullptr)
		root->traversePre(visit);
}

template<typename T> template<typename VST> void BinaryTree<T>::traverseIn(VST& visit)
{
	if (getRoot() != nullptr)
		root->traverseIn(visit);
}

template<typename T> template<typename VST> void BinaryTree<T>::traversePost(VST& visit)
{
	if (getRoot() != nullptr)
		root->traversePost(visit);
}

