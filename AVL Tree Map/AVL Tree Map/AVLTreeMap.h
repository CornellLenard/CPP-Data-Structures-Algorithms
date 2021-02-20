/*********************************************************************************
 *   @file        AVLTreeMap.h
 *   @brief       The header file for C++ implemented AVL Tree Map
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "AVLNode.h"

template<typename K, typename V> class AVLTreeMap                              //AVL��ģ����
{
protected:
	int size;                                                                  //AVL����ģ
	AVLNode<K, V>* root;                                                       //ָ��AVL�����ڵ��ָ��
	AVLNode<K, V>* hot;                                                        //�����㷨���нڵ��ĸ�׽ڵ�
	int updateHeight(AVLNode<K, V>* x);                                        //���½ڵ�x�ĸ߶ȣ�����xָ��Ľڵ���¸߶�
	void updateHeightAbove(AVLNode<K, V>* x);                                  //���½ڵ�x�������ȵĸ߶�
	//�����㷨�����岿�֣�vΪָ�������ʼ�ڵ��ָ�룬hotָ����ĸ�׽ڵ㣬�������ڴ˺���ִ�й����в���
	//ע��˺��������е�v��hot����*&�����ͣ����൱���βκ�ʵ����ͬһ������
	//��������һ��ָ������ã������д��ڹؼ���Ϊk�Ľڵ㣬���ָ��ָ��ýڵ㣻������û�������Ľڵ㣬���ָ��ָ������佫������ʱ��Ӧ�������λ��
	AVLNode<K, V>*& searchIn(AVLNode<K, V>*& v, const K& k, AVLNode<K, V>*& hot);
	AVLNode<K, V>* removeAt(AVLNode<K, V>*& x, AVLNode<K, V>*& hot);           //ɾ��xָ��Ľڵ㣬hotָ��xָ��Ľڵ��ĸ�׽ڵ�
	//������������������������
	int removeForDestructor(AVLNode<K, V>* x);                                 //ɾ����xΪ���ڵ�����������ظ�����ԭ�ȵĹ�ģ
	int removeAtForDestructor(AVLNode<K, V>* x);                               //ɾ��AVL����x���Ľڵ㼰���������ر�ɾ���ڵ������
	//3+4�ع��㷨
	AVLNode<K, V>* connect34(AVLNode<K, V>* t0, AVLNode<K, V>* t1, AVLNode<K, V>* t2, AVLNode<K, V>* t3, AVLNode<K, V>* a, AVLNode<K, V>* b, AVLNode<K, V>* c);
	//��ת�����㷨
	AVLNode<K, V>* rotateAt(AVLNode<K, V>* v);
	AVLNode<K, V>*& fromParentTo(const AVLNode<K, V>& avln);                   //��ȡavln�ڵ��ĸ�׽ڵ��ָ��avln�ڵ��ָ��
public:
	AVLTreeMap();                                                              //���캯��
	~AVLTreeMap();                                                             //��������
	int getSize() const;                                                       //��ȡAVL����ģ
	bool isEmpty() const;                                                      //�ж�AVL���Ƿ�Ϊ��
	AVLNode<K, V>* getRoot() const;                                            //��ȡָ��AVL�����ڵ��ָ��
	AVLNode<K, V>*& search(const K& k);                                        //AVL�������㷨�����ҹؼ���Ϊk�Ľڵ㣬����ָ������ã����������searchIn()
	AVLNode<K, V>* insert(const K& k, const V& v);                             //AVL�������㷨�����ؼ���k������v�����һ���½ڵ����
	bool remove(const K& k);                                                   //AVL��ɾ���㷨��ɾ���ؼ���Ϊk�Ľڵ㣬����ɾ���Ƿ�ɹ�
	template<typename VST> void traverseLevel(VST& visit);                     //��α����㷨
	template<typename VST> void traverseIn(VST& visit);                        //��������㷨
};

template<typename K, typename V> int AVLTreeMap<K, V>::updateHeight(AVLNode<K, V>* x) //xָ��Ľڵ�ĸ߶ȵ���ȡ���Һ��ӵĸ߶ȵĴ����ټ�1
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

template<typename K, typename V> AVLNode<K, V>*& AVLTreeMap<K, V>::searchIn(AVLNode<K, V>*& v, const K& k, AVLNode<K, V>*& hot)         //�����㷨����
{
	if (v == nullptr || v->key == k)                                           //���vΪ�ջ���vָ��Ľڵ�Ĺؼ���Ϊk���򷵻�v
		return v;
	hot = v;                                                                   //����hot�ƶ���v����
	while (true)
	{
		AVLNode<K, V>*& c = (k < hot->key) ? hot->lc : hot->rc;                //����k��hot->key�Ĵ�С��ϵȷ���ƶ�����
		if (c == nullptr || c->key == k)                                       //ͬ�����cΪ�ջ���cָ��Ľڵ�Ĺؼ���Ϊk���򷵻�c
			return c;
		hot = c;                                                               //����hot�ƶ���c���Ȼ�������һ��ѭ��
	}
}

template<typename K, typename V> AVLNode<K, V>* AVLTreeMap<K, V>::removeAt(AVLNode<K, V>*& x, AVLNode<K, V>*& hot)  //���������
{
	AVLNode<K, V>* w = x;                                                      //wҲָ��Ҫɾ���Ľڵ�
	AVLNode<K, V>* succ = nullptr;
	if (AVLNode<K, V>::hasLChild(*x) == false)                                 //���Ҫɾ���Ľڵ�û�����ӵĻ�
	{
		x = x->rc;                                                             //xΪhotָ��Ľڵ��lc��rc�������������ǽ�hot��lc��rc��Ҫɾ���Ľڵ���ӽڵ�����
		succ = x;                                                              //succָ��w���Һ��ӣ�Ҳ����xָ��Ľڵ�
	}
	else if (AVLNode<K, V>::hasRChild(*x) == false)                            //���Ҫɾ���Ľڵ������ӣ���û���Һ��ӵĻ�
	{
		x = x->lc;                                                             //xΪhotָ��Ľڵ��lc��rc�������������ǽ�hot��lc��rc��Ҫɾ���Ľڵ���ӽڵ�����
		succ = x;                                                              //succָ��w�����ӣ�Ҳ����xָ��Ľڵ�
	}
	else                                                                       //�������е�������ζ��Ҫɾ���Ľڵ��������Ҳ���Һ���
	{
		w = w->getSucc();                                                      //���ҵ�Ҫɾ���Ľڵ���������������µ�ֱ�Ӻ�̽ڵ�
		x->key = w->key;                                                       //��ֱ�Ӻ�̽ڵ��key��value���ǵ�Ҫɾ���Ľڵ��key��value
		x->value = w->value;
		AVLNode<K, V>* u = w->parent;                                          //Ȼ��ɾ����ֱ�Ӻ�̽ڵ��ok�ˣ��˽ڵ�Ҫôû�к���Ҫôֻ���Һ���
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

template<typename K, typename V> int AVLTreeMap<K, V>::removeForDestructor(AVLNode<K, V>* x)    //ɾ����xΪ���ڵ�����������ظ�����ԭ�ȵĹ�ģ
{
	fromParentTo(*x) = nullptr;                                                //���x��ĸ�׽ڵ��ָ��x��ָ��
	updateHeightAbove(x->parent);                                              //���¸߶�
	int count = removeAtForDestructor(x);                                      //ʵ����������removeAt()���
	size -= count;                                                             //����size
	return count;
}

template<typename K, typename V> int AVLTreeMap<K, V>::removeAtForDestructor(AVLNode<K, V>* x)  //�ݹ�ʽʵ��
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
	a->lc = t0;                                                                //��3���ڵ���4������֮��Ĺ�ϵ�����ع�
	if (t0 != nullptr)                                                         //����Ĳ�������ܼ򵥣������ppt���ͼƬ��⣬���Ա�ﲻֱ̫�ۣ��Ͳ���׸����
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

template<typename K, typename V> AVLNode<K, V>* AVLTreeMap<K, V>::rotateAt(AVLNode<K, V>* v)    //3+4�ع��㷨�ĺ��ģ��������������ȷ��connect34()�Ĳ���˳��
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

template<typename K, typename V> AVLNode<K, V>*& AVLTreeMap<K, V>::search(const K& k)           //AVL�������㷨�����ҹؼ���Ϊk�Ľڵ�
{
	return searchIn(root, k, hot = nullptr);                                   //ֱ�ӵ���searchIn()�����Ӹ��ڵ㿪ʼ���ҹؼ���Ϊk�Ľڵ㣬hot��ʼֵ��ȻΪnullptr
}

template<typename K, typename V> AVLNode<K, V>* AVLTreeMap<K, V>::insert(const K& k, const V& v)//AVL�������㷨
{
	AVLNode<K, V>*& x = search(k);                                             //����search()�����ҹؼ���Ϊk�Ľڵ�
	if (x != nullptr)                                                          //���x���ǿ�ָ�룬˵���Ѿ��нڵ�ؼ���Ϊk���򲻽��в��룬ֱ�ӷ���x
		return x;
	x = new AVLNode<K, V>(k, v, hot);                                          //search()���ص���*&�����ֱ����x����һ���½ڵ㣬��ĸ�׽ڵ���Ǵ�ʱhot��ָ�Ľڵ�
	AVLNode<K, V>* res = x;                                                    //�������ָ�룬��xָ��ͬһ�ڵ㣬���²���Ľڵ�
	size++;                                                                    //���¹�ģ
	for (AVLNode<K, V>* g = hot; g != nullptr; g = g->parent)                  //��xָ��Ľڵ��ĸ�׽ڵ㿪ʼ��������ϼ������Ƚڵ�
	{
		if (AVLNode<K, V>::isAVLBalanced(*g) == false)                         //������Ƚڵ�ʧ�⣬����е���
		{
			AVLNode<K, V>*& from_parent_to = fromParentTo(*g);                 //�Ȼ�ȡ��ǰ״̬��gָ��Ľڵ��ĸ�׽ڵ��ָ��g�ڵ��ָ��
			from_parent_to = rotateAt(AVLNode<K, V>::getTallerChild(AVLNode<K, V>::getTallerChild(g))); //�Ƚ��е��������������ӵ�����ϵ�����
			break;                                                             //gָ��Ľڵ�ָ�ƽ��󣬾ֲ������߶ȱ�Ȼ��ԭ�������������ˣ��ʵ�������
		}
		else
			updateHeight(g);                                                   //����ƽ������Ƚڵ㣬Ҫ������߶�
	}
	return res;
}

template<typename K, typename V> bool AVLTreeMap<K, V>::remove(const K& k)     //AVL��ɾ���㷨������ɾ���Ƿ�ɹ�
{
	AVLNode<K, V>*& x = search(k);                                             //����search()�����ҹؼ���Ϊk�Ľڵ�
	if (x == nullptr)                                                          //���xΪ��ָ�룬����ζ��û�йؼ���Ϊk�Ľڵ㣬����ɾ��ʧ�ܣ�����false
		return false;
	removeAt(x, hot);                                                          //���򣬿���ɾ��������removeAt()����ɾ������
	size--;                                                                    //���¹�ģ
	for (AVLNode<K, V>* g = hot; g != nullptr; g = g->parent)                  //��xָ��Ľڵ��ĸ�׽ڵ㿪ʼ��������ϼ������Ƚڵ�
	{
		if (AVLNode<K, V>::isAVLBalanced(*g) == false)                         //������Ƚڵ�ʧ�⣬����е���
		{
			AVLNode<K, V>*& from_parent_to = fromParentTo(*g);                 //�Ȼ�ȡ��ǰ״̬��gָ��Ľڵ��ĸ�׽ڵ��ָ��g�ڵ��ָ��
			from_parent_to = rotateAt(AVLNode<K, V>::getTallerChild(AVLNode<K, V>::getTallerChild(g))); //�Ƚ��е��������������ӵ�����ϵ�����
			g = from_parent_to;
		}
		updateHeight(g);                                                       //�������Ƚڵ�ƽ����񣬶�Ҫ���и߶ȸ���
	}
	return true;                                                               //ɾ���ɹ�������true
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



