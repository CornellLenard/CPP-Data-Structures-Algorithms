/*********************************************************************************
 *   @file        BinarySearchTreeMap.h
 *   @brief       The header file for C++ implemented Binary Search Tree Map
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "BSTNode.h"

template<typename K, typename V> class BinarySearchTreeMap                     //����������ģ����
{
protected:
	int size;                                                                  //������������ģ
	BSTNode<K, V>* root;                                                       //ָ��������������ڵ��ָ��
	BSTNode<K, V>* hot;                                                        //�����㷨���нڵ��ĸ�׽ڵ�
	int updateHeight(BSTNode<K, V>* x);                                        //���½ڵ�x�ĸ߶ȣ�����xָ��Ľڵ���¸߶�
	void updateHeightAbove(BSTNode<K, V>* x);                                  //���½ڵ�x�������ȵĸ߶�
	//�����㷨�����岿�֣�vΪָ�������ʼ�ڵ��ָ�룬hotָ����ĸ�׽ڵ㣬�������ڴ˺���ִ�й����в���
	//ע��˺��������е�v��hot����*&�����ͣ����൱���βκ�ʵ����ͬһ������
	//��������һ��ָ������ã������д��ڹؼ���Ϊk�Ľڵ㣬���ָ��ָ��ýڵ㣻������û�������Ľڵ㣬���ָ��ָ������佫������ʱ��Ӧ�������λ��
	BSTNode<K, V>*& searchIn(BSTNode<K, V>*& v, const K& k, BSTNode<K, V>*& hot);
	BSTNode<K, V>* removeAt(BSTNode<K, V>*& x, BSTNode<K, V>*& hot);           //ɾ��xָ��Ľڵ㣬hotָ��xָ��Ľڵ��ĸ�׽ڵ�
	//������������������������
	int removeForDestructor(BSTNode<K, V>* x);                                 //ɾ����xΪ���ڵ�����������ظ�����ԭ�ȵĹ�ģ
	int removeAtForDestructor(BSTNode<K, V>* x);                               //ɾ��������������x���Ľڵ㼰���������ر�ɾ���ڵ������
	//3+4�ع��㷨
	//BSTNode<K, V>* connect34(BSTNode<K, V>* t0, BSTNode<K, V>* t1, BSTNode<K, V>* t2, BSTNode<K, V>* t3, BSTNode<K, V>* a, BSTNode<K, V>* b, BSTNode<K, V>* c);
	//��ת�����㷨
	//BSTNode<K, V>* rotateAt(BSTNode<K, V>* x);
	BSTNode<K, V>*& fromParentTo(const BSTNode<K, V>& bn);                     //��ȡbn�ڵ��ĸ�׽ڵ��ָ��bn�ڵ��ָ��
public:
	BinarySearchTreeMap();                                                     //���캯��
	~BinarySearchTreeMap();                                                    //��������
	int getSize() const;                                                       //��ȡ������������ģ
	bool isEmpty() const;                                                      //�ж϶����������Ƿ�Ϊ��
	BSTNode<K, V>* getRoot() const;                                            //��ȡָ��������������ڵ��ָ��
	BSTNode<K, V>*& search(const K& k);                                        //���������������㷨�����ҹؼ���Ϊk�Ľڵ㣬����ָ������ã����������searchIn()
	BSTNode<K, V>* insert(const K& k, const V& v);                             //���������������㷨�����ؼ���k������v�����һ���½ڵ����
	bool remove(const K& k);                                                   //����������ɾ���㷨��ɾ���ؼ���Ϊk�Ľڵ㣬����ɾ���Ƿ�ɹ�
	template<typename VST> void traverseLevel(VST& visit);                     //��α����㷨
	template<typename VST> void traverseIn(VST& visit);                        //��������㷨
};

template<typename K, typename V> int BinarySearchTreeMap<K, V>::updateHeight(BSTNode<K, V>* x)  //xָ��Ľڵ�ĸ߶ȵ���ȡ���Һ��ӵĸ߶ȵĴ����ټ�1
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

template<typename K, typename V> BSTNode<K, V>*& BinarySearchTreeMap<K, V>::searchIn(BSTNode<K, V>*& v, const K& k, BSTNode<K, V>*& hot)//�����㷨����
{
	if (v == nullptr || v->key == k)                                           //���vΪ�ջ���vָ��Ľڵ�Ĺؼ���Ϊk���򷵻�v
		return v;
	hot = v;                                                                   //����hot�ƶ���v����
	while (true)
	{
		BSTNode<K, V>*& c = (k < hot->key) ? hot->lc : hot->rc;                //����k��hot->key�Ĵ�С��ϵȷ���ƶ�����
		if (c == nullptr || c->key == k)                                       //ͬ�����cΪ�ջ���cָ��Ľڵ�Ĺؼ���Ϊk���򷵻�c
			return c;
		hot = c;                                                               //����hot�ƶ���c���Ȼ�������һ��ѭ��
	}
}

template<typename K, typename V> BSTNode<K, V>* BinarySearchTreeMap<K, V>::removeAt(BSTNode<K, V>*& x, BSTNode<K, V>*& hot)   //���������
{
	BSTNode<K, V>* w = x;                                                      //wҲָ��Ҫɾ���Ľڵ�
	BSTNode<K, V>* succ = nullptr;
	if (BSTNode<K, V>::hasLChild(*x) == false)                                 //���Ҫɾ���Ľڵ�û�����ӵĻ�
	{
		x = x->rc;                                                             //xΪhotָ��Ľڵ��lc��rc�������������ǽ�hot��lc��rc��Ҫɾ���Ľڵ���ӽڵ�����
		succ = x;                                                              //succָ��w���Һ��ӣ�Ҳ����xָ��Ľڵ�
	}
	else if (BSTNode<K, V>::hasRChild(*x) == false)                            //���Ҫɾ���Ľڵ������ӣ���û���Һ��ӵĻ�
	{
		x = x->lc;                                                             //xΪhotָ��Ľڵ��lc��rc�������������ǽ�hot��lc��rc��Ҫɾ���Ľڵ���ӽڵ�����
		succ = x;                                                              //succָ��w�����ӣ�Ҳ����xָ��Ľڵ�
	}
	else                                                                       //�������е�������ζ��Ҫɾ���Ľڵ��������Ҳ���Һ���
	{
		w = w->getSucc();                                                      //���ҵ�Ҫɾ���Ľڵ���������������µ�ֱ�Ӻ�̽ڵ�
		x->key = w->key;                                                       //��ֱ�Ӻ�̽ڵ��key��value���ǵ�Ҫɾ���Ľڵ��key��value
		x->value = w->value;
		BSTNode<K, V>* u = w->parent;                                          //Ȼ��ɾ����ֱ�Ӻ�̽ڵ��ok�ˣ��˽ڵ�Ҫôû�к���Ҫôֻ���Һ���
		succ = w->rc;
		(u == x ? u->rc : u->lc) = succ;
	}
	hot = w->parent;                                                           //ȷ��hotλ����ȷ
	if (succ != nullptr)                                                       //���succ�ǿ�
		succ->parent = hot;                                                    //Ҫɾ���Ľڵ㱻ɾ����succ��Ӧ����hot���ӽڵ㣬����������ϵ�����
	delete w;                                                                  //�ͷŵ�Ҫɾ���Ľڵ�
	w = nullptr;
	return succ;
}

template<typename K, typename V> int BinarySearchTreeMap<K, V>::removeForDestructor(BSTNode<K, V>* x)     //ɾ����xΪ���ڵ�����������ظ�����ԭ�ȵĹ�ģ
{
	fromParentTo(*x) = nullptr;                                                //���x��ĸ�׽ڵ��ָ��x��ָ��
	updateHeightAbove(x->parent);                                              //���¸߶�
	int count = removeAtForDestructor(x);                                      //ʵ����������removeAt()���
	size -= count;                                                             //����size
	return count;
}

template<typename K, typename V> int BinarySearchTreeMap<K, V>::removeAtForDestructor(BSTNode<K, V>* x)   //�ݹ�ʽʵ��
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

template<typename K, typename V> BSTNode<K, V>*& BinarySearchTreeMap<K, V>::search(const K& k)  //���������������㷨�����ҹؼ���Ϊk�Ľڵ�
{
	return searchIn(root, k, hot = nullptr);                                   //ֱ�ӵ���searchIn()�����Ӹ��ڵ㿪ʼ���ҹؼ���Ϊk�Ľڵ㣬hot��ʼֵ��ȻΪnullptr
}

template<typename K, typename V> BSTNode<K, V>* BinarySearchTreeMap<K, V>::insert(const K& k, const V& v) //���������������㷨
{
	BSTNode<K, V>*& x = search(k);                                             //����search()�����ҹؼ���Ϊk�Ľڵ�
	if (x == nullptr)                                                          //���xΪ��ָ�룬����ζ�Ų�û�йؼ���Ϊk�Ľڵ㣬���Կ��Բ���
	{
		x = new BSTNode<K, V>(k, v, hot);                                      //search()���ص���*&�����ֱ����x����һ���½ڵ㣬��ĸ�׽ڵ���Ǵ�ʱhot��ָ�Ľڵ�
		size++;                                                                //���¹�ģ
		updateHeightAbove(x);                                                  //���¸߶�
	}
	return x;
}

template<typename K, typename V> bool BinarySearchTreeMap<K, V>::remove(const K& k)   //����������ɾ���㷨������ɾ���Ƿ�ɹ�
{
	BSTNode<K, V>*& x = search(k);                                             //����search()�����ҹؼ���Ϊk�Ľڵ�
	if (x == nullptr)                                                          //���xΪ��ָ�룬����ζ��û�йؼ���Ϊk�Ľڵ㣬����ɾ��ʧ�ܣ�����false
		return false;
	removeAt(x, hot);                                                          //����removeAt()������ɾ������
	size--;                                                                    //���¹�ģ
	updateHeightAbove(hot);                                                    //���¸߶�
	return true;                                                               //ɾ���ɹ�������true
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


