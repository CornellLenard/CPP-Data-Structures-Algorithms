/*********************************************************************************
 *   @file        BinaryTree.h
 *   @brief       The header file for C++ implemented Binary Tree
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "BinNode.h"

template<typename T> class BinaryTree                                          //������ģ����
{
protected:
	int size;                                                                  //��������ģ
	BinNode<T>* root;                                                          //ָ����������ڵ��ָ��
	int updateHeight(BinNode<T>* x);                                           //���½ڵ�x�ĸ߶ȣ�����xָ��Ľڵ���¸߶�
	void updateHeightAbove(BinNode<T>* x);                                     //���½ڵ�x�������ȵĸ߶�
	int removeAt(BinNode<T>* x);                                               //ɾ����������x���Ľڵ㼰���������ر�ɾ���ڵ������
	BinNode<T>*& fromParentTo(const BinNode<T>& bn);                           //��ȡbn�ڵ��ĸ�׽ڵ��ָ��bn�ڵ��ָ��
public:
	BinaryTree();                                                              //���캯��
	~BinaryTree();                                                             //��������
	int getSize() const;                                                       //��ȡ��������ģ
	bool isEmpty() const;                                                      //�ж϶������Ƿ�Ϊ��
	BinNode<T>* getRoot() const;                                               //��ȡָ����������ڵ��ָ��
	BinNode<T>* insertAsRoot(const T& e);                                      //������ڵ�
	BinNode<T>* insertAsLC(BinNode<T>* x, const T& e);                         //e��Ϊxָ��Ľڵ�����Ӳ���
	BinNode<T>* insertAsRC(BinNode<T>* x, const T& e);                         //e��Ϊxָ��Ľڵ���Һ��Ӳ���
	BinNode<T>* attachAsLC(BinNode<T>* x, BinaryTree<T>*& bt);                 //bt��Ϊxָ��Ľڵ������������
	BinNode<T>* attachAsRC(BinNode<T>* x, BinaryTree<T>*& bt);                 //bt��Ϊxָ��Ľڵ������������
	int remove(BinNode<T>* x);                                                 //ɾ����xָ��Ľڵ�Ϊ���ڵ�����������ظ�����ԭ�ȵĹ�ģ
	BinaryTree<T>* secede(BinNode<T>* x);                                      //������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������
	template<typename VST> void traverseLevel(VST& visit);                     //��α����㷨
	template<typename VST> void traversePre(VST& visit);                       //��������㷨
	template<typename VST> void traverseIn(VST& visit);                        //��������㷨
	template<typename VST> void traversePost(VST& visit);                      //��������㷨
};

template<typename T> int BinaryTree<T>::updateHeight(BinNode<T>* x)            //xָ��Ľڵ�ĸ߶ȵ���ȡ���Һ��ӵĸ߶ȵĴ����ټ�1
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

template<typename T> int BinaryTree<T>::removeAt(BinNode<T>* x)                //�ݹ�ʽʵ��
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

template<typename T> BinNode<T>* BinaryTree<T>::insertAsLC(BinNode<T>* x, const T& e) //�����㷨ֱ�ӵ��ö�Ӧ�ڵ�Ķ�Ӧ�����㷨
{
	size++;
	x->insertAsLC(e);
	updateHeightAbove(x);                                                      //���¸߶�
	return x->lc;
}

template<typename T> BinNode<T>* BinaryTree<T>::insertAsRC(BinNode<T>* x, const T& e)
{
	size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rc;
}

template<typename T> BinNode<T>* BinaryTree<T>::attachAsLC(BinNode<T>* x, BinaryTree<T>*& bt)   //bt��Ϊxָ��Ľڵ������������
{
	x->lc = bt->getRoot();                                                     //����x��btָ������ĸ��ڵ������
	if (x->lc != nullptr)
		x->lc->parent = x;                                                     //����btָ������ĸ��ڵ㵽x������
	size += bt->getSize();                                                     //size����
	updateHeightAbove(x);                                                      //�߶ȸ���
	bt->root = nullptr;                                                        //btָ��������ڲ�������������
	bt->size = 0;
	//release(bt);
	bt = nullptr;
	return x;
}

template<typename T> BinNode<T>* BinaryTree<T>::attachAsRC(BinNode<T>* x, BinaryTree<T>*& bt)   //bt��Ϊxָ��Ľڵ������������
{
	x->rc = bt->getRoot();                                                     //����x��btָ������ĸ��ڵ������
	if (x->rc != nullptr)
		x->rc->parent = x;                                                     //����btָ������ĸ��ڵ㵽x������
	size += bt->getSize();                                                     //size����
	updateHeightAbove(x);                                                      //�߶ȸ���
	bt->root = nullptr;                                                        //btָ��������ڲ�������������
	bt->size = 0;
	//release(bt);
	bt = nullptr;
	return x;
}

template<typename T> int BinaryTree<T>::remove(BinNode<T>* x)                  //ɾ����xΪ���ڵ�����������ظ�����ԭ�ȵĹ�ģ
{
	fromParentTo(*x) = nullptr;                                                //���x��ĸ�׽ڵ��ָ��x��ָ��
	updateHeightAbove(x->parent);                                              //���¸߶�
	int count = removeAt(x);                                                   //ʵ����������removeAt()���
	size -= count;                                                             //����size
	return count;
}

template<typename T> BinaryTree<T>* BinaryTree<T>::secede(BinNode<T>* x)       //������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������
{
	fromParentTo(*x) = nullptr;                                                //���x��ĸ�׽ڵ��ָ��x��ָ��
	updateHeightAbove(x->parent);                                              //���¸߶�
	BinaryTree<T>* bt = new BinaryTree<T>();                                   //�½�һ�ö�����
	bt->root = x;                                                              //�¶������ĸ��ڵ㼴Ϊxָ��Ľڵ�
	x->parent = nullptr;                                                       //xָ��Ľڵ��parentָ����Ϊnullptr
	bt->size = x->getSize();                                                   //�����¶�����size
	size -= bt->getSize();                                                     //����ԭ������size
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

