/*********************************************************************************
 *   @file        SplayTreeMap.h
 *   @brief       The header file for C++ implemented Splay Tree Map
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "SplayNode.h"

template<typename K, typename V> class SplayTreeMap                            //��չ��ģ����
{
protected:
	int size;                                                                  //��չ����ģ
	SplayNode<K, V>* root;                                                     //ָ����չ�����ڵ��ָ��
	SplayNode<K, V>* hot;                                                      //�����㷨���нڵ��ĸ�׽ڵ�
	int updateHeight(SplayNode<K, V>* x);                                      //���½ڵ�x�ĸ߶ȣ�����xָ��Ľڵ���¸߶�
	void updateHeightAbove(SplayNode<K, V>* x);                                //���½ڵ�x�������ȵĸ߶�
	//�����㷨�����岿�֣�vΪָ�������ʼ�ڵ��ָ�룬hotָ����ĸ�׽ڵ㣬�������ڴ˺���ִ�й����в���
	//ע��˺��������е�v��hot����*&�����ͣ����൱���βκ�ʵ����ͬһ������
	//��������һ��ָ������ã������д��ڹؼ���Ϊk�Ľڵ㣬���ָ��ָ��ýڵ㣻������û�������Ľڵ㣬���ָ��ָ������佫������ʱ��Ӧ�������λ��
	SplayNode<K, V>*& searchIn(SplayNode<K, V>*& v, const K& k, SplayNode<K, V>*& hot);
	SplayNode<K, V>* removeAt(SplayNode<K, V>*& x, SplayNode<K, V>*& hot);     //ɾ��xָ��Ľڵ㣬hotָ��xָ��Ľڵ��ĸ�׽ڵ�
	//������������������������
	int removeForDestructor(SplayNode<K, V>* x);                               //ɾ����xΪ���ڵ�����������ظ�����ԭ�ȵĹ�ģ
	int removeAtForDestructor(SplayNode<K, V>* x);                             //ɾ����չ����x���Ľڵ㼰���������ر�ɾ���ڵ������
	SplayNode<K, V>* splay(SplayNode<K, V>* v);                                //��չ�㷨����vָ��Ľڵ���չ������λ��
	void attachAsLChild(SplayNode<K, V>* x, SplayNode<K, V>* lc);              //��xָ��Ľڵ���lcָ��Ľڵ�֮�佨��ĸ-���ӹ�ϵ
	void attachAsRChild(SplayNode<K, V>* x, SplayNode<K, V>* rc);              //��xָ��Ľڵ���rcָ��Ľڵ�֮�佨��ĸ-�Һ��ӹ�ϵ
	SplayNode<K, V>*& fromParentTo(const SplayNode<K, V>& sn);                 //��ȡsn�ڵ��ĸ�׽ڵ��ָ��sn�ڵ��ָ��
public:
	SplayTreeMap();                                                            //���캯��
	~SplayTreeMap();                                                           //��������
	int getSize() const;                                                       //��ȡ��չ����ģ
	bool isEmpty() const;                                                      //�ж���չ���Ƿ�Ϊ��
	SplayNode<K, V>* getRoot() const;                                          //��ȡָ����չ�����ڵ��ָ��
	SplayNode<K, V>*& search(const K& k);                                      //��չ�������㷨�����ҹؼ���Ϊk�Ľڵ㣬����ָ������ã����������searchIn()
	SplayNode<K, V>* insert(const K& k, const V& v);                           //��չ�������㷨�����ؼ���k������v�����һ���½ڵ����
	bool remove(const K& k);                                                   //��չ��ɾ���㷨��ɾ���ؼ���Ϊk�Ľڵ㣬����ɾ���Ƿ�ɹ�
	template<typename VST> void traverseLevel(VST& visit);                     //��α����㷨
	template<typename VST> void traverseIn(VST& visit);                        //��������㷨
};

template<typename K, typename V> int SplayTreeMap<K, V>::updateHeight(SplayNode<K, V>* x)       //xָ��Ľڵ�ĸ߶ȵ���ȡ���Һ��ӵĸ߶ȵĴ����ټ�1
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

template<typename K, typename V> SplayNode<K, V>*& SplayTreeMap<K, V>::searchIn(SplayNode<K, V>*& v, const K& k, SplayNode<K, V>*& hot) //�����㷨����
{
	if (v == nullptr || v->key == k)                                           //���vΪ�ջ���vָ��Ľڵ�Ĺؼ���Ϊk���򷵻�v
		return v;
	hot = v;                                                                   //����hot�ƶ���v����
	while (true)
	{
		SplayNode<K, V>*& c = (k < hot->key) ? hot->lc : hot->rc;              //����k��hot->key�Ĵ�С��ϵȷ���ƶ�����
		if (c == nullptr || c->key == k)                                       //ͬ�����cΪ�ջ���cָ��Ľڵ�Ĺؼ���Ϊk���򷵻�c
			return c;
		hot = c;                                                               //����hot�ƶ���c���Ȼ�������һ��ѭ��
	}
}

template<typename K, typename V> SplayNode<K, V>* SplayTreeMap<K, V>::removeAt(SplayNode<K, V>*& x, SplayNode<K, V>*& hot)    //���������
{
	SplayNode<K, V>* w = x;                                                    //wҲָ��Ҫɾ���Ľڵ�
	SplayNode<K, V>* succ = nullptr;
	if (SplayNode<K, V>::hasLChild(*x) == false)                               //���Ҫɾ���Ľڵ�û�����ӵĻ�
	{
		x = x->rc;                                                             //xΪhotָ��Ľڵ��lc��rc�������������ǽ�hot��lc��rc��Ҫɾ���Ľڵ���ӽڵ�����
		succ = x;                                                              //succָ��w���Һ��ӣ�Ҳ����xָ��Ľڵ�
	}
	else if (SplayNode<K, V>::hasRChild(*x) == false)                          //���Ҫɾ���Ľڵ������ӣ���û���Һ��ӵĻ�
	{
		x = x->lc;                                                             //xΪhotָ��Ľڵ��lc��rc�������������ǽ�hot��lc��rc��Ҫɾ���Ľڵ���ӽڵ�����
		succ = x;                                                              //succָ��w�����ӣ�Ҳ����xָ��Ľڵ�
	}
	else                                                                       //�������е�������ζ��Ҫɾ���Ľڵ��������Ҳ���Һ���
	{
		w = w->getSucc();                                                      //���ҵ�Ҫɾ���Ľڵ���������������µ�ֱ�Ӻ�̽ڵ�
		x->key = w->key;                                                       //��ֱ�Ӻ�̽ڵ��key��value���ǵ�Ҫɾ���Ľڵ��key��value
		x->value = w->value;
		SplayNode<K, V>* u = w->parent;                                        //Ȼ��ɾ����ֱ�Ӻ�̽ڵ��ok�ˣ��˽ڵ�Ҫôû�к���Ҫôֻ���Һ���
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

template<typename K, typename V> int SplayTreeMap<K, V>::removeForDestructor(SplayNode<K, V>* x)//ɾ����xΪ���ڵ�����������ظ�����ԭ�ȵĹ�ģ
{
	fromParentTo(*x) = nullptr;                                                //���x��ĸ�׽ڵ��ָ��x��ָ��
	updateHeightAbove(x->parent);                                              //���¸߶�
	int count = removeAtForDestructor(x);                                      //ʵ����������removeAt()���
	size -= count;                                                             //����size
	return count;
}

template<typename K, typename V> int SplayTreeMap<K, V>::removeAtForDestructor(SplayNode<K, V>* x)        //�ݹ�ʽʵ��
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

template<typename K, typename V> SplayNode<K, V>* SplayTreeMap<K, V>::splay(SplayNode<K, V>* v) //��չ�㷨���Լ�����ͼ����Ū�����ˣ�����˵��̫������Ͳ�׸����
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
{                                                                              //��xָ��Ľڵ���lcָ��Ľڵ�֮�佨��ĸ-���ӹ�ϵ
	x->lc = lc;
	if (lc != nullptr)
		lc->parent = x;
}

template<typename K, typename V> void SplayTreeMap<K, V>::attachAsRChild(SplayNode<K, V>* x, SplayNode<K, V>* rc)
{                                                                              //��xָ��Ľڵ���lcָ��Ľڵ�֮�佨��ĸ-���ӹ�ϵ
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

template<typename K, typename V> SplayNode<K, V>*& SplayTreeMap<K, V>::search(const K& k)       //��չ�������㷨�����ҹؼ���Ϊk�Ľڵ�
{
	SplayNode<K, V>*& x = searchIn(root, k, hot = nullptr);                    //ֱ�ӵ���searchIn()�����Ӹ��ڵ㿪ʼ���ҹؼ���Ϊk�Ľڵ㣬hot��ʼֵ��ȻΪnullptr
	root = splay((x != nullptr) ? x : hot);                                    //���x��Ϊ�գ��򽫴˽ڵ���չ����λ�ã����xΪ�գ���ֻ�ܽ�hotָ��Ľڵ���չ����
	return root;
}

template<typename K, typename V> SplayNode<K, V>* SplayTreeMap<K, V>::insert(const K& k, const V& v)      //��չ�������㷨
{
	if (root == nullptr)                                                       //���rootΪ�գ���ֱ����root�������½ڵ㼴��
	{
		size++;
		return root = new SplayNode<K, V>(k, v);
	}
	if (search(k)->key == k)                                                   //����search()���ҹؼ���Ϊk�Ľڵ㣬����õ���ָ��(��root)ָ��Ľڵ�Ĺؼ���Ϊk
		return root;                                                           //˵�������Ѵ��ڹؼ���Ϊk�Ľڵ㣬��˲���Ҫ���룬ֱ�ӷ���root����
	SplayNode<K, V>* t = root;                                                 //tҲָ����ڵ�
	if (root->key < k)                                                         //������ڵ��keyС��k
	{
		root = new SplayNode<K, V>(k, v, nullptr, t, t->rc);                   //��root����һ���µĸ��ڵ㣬���Һ��ӷֱ���tָ��Ľڵ��tָ��Ľڵ���Һ���
		t->parent = root;                                                      //��������tָ��Ľڵ�͸��ڵ�
		if (SplayNode<K, V>::hasRChild(*t) == true)                            //���tָ��Ľڵ��rc�ǿ�
		{
			t->rc->parent = root;                                              //��������t->rcָ��Ľڵ�͸��ڵ�
			t->rc = nullptr;                                                   //�ж�t->rc
		}
	}
	else                                                                       //ԭ����ͬ���Ͳ���׸����
	{
		root = new SplayNode<K, V>(k, v, nullptr, t->lc, t);
		t->parent = root;
		if (SplayNode<K, V>::hasLChild(*t) == true)
		{
			t->lc->parent = root;
			t->lc = nullptr;
		}
	}
	updateHeightAbove(t);                                                      //���¸߶�
	size++;                                                                    //���¹�ģ
	return root;                                                               //����root
}

template<typename K, typename V> bool SplayTreeMap<K, V>::remove(const K& k)   //��չ��ɾ���㷨������ɾ���Ƿ�ɹ�
{
	if (root == nullptr || search(k)->key != k)                                //���rootΪ�ջ��ߵ���search()����k�õ���ָ��ָ��Ľڵ�Ĺؼ��벻��k
		return false;                                                          //��ɾ��ѹ����û�����У����ɾ��ʧ�ܣ�ֱ�ӷ���false
	SplayNode<K, V>* w = root;                                                 //��Ϊ֮ǰ������search()�����Ҫɾ���Ľڵ��Ϊ���µĸ��ڵ�
	                                                                           //wָ����ڵ㣬��wָ��Ҫɾ���Ľڵ�
	if (SplayNode<K, V>::hasLChild(*root) == false)                            //������ڵ�û������
	{
		root = root->rc;                                                       //rootָ����ڵ���Һ���
		if (root != nullptr)                                                   //���root�ǿգ�����ָ��Ľڵ��parentָ����Ϊnullptr
			root->parent = nullptr;
	}
	else if (SplayNode<K, V>::hasRChild(*root) == false)                       //�Գ������ͬ��
	{
		root = root->lc;
		if (root != nullptr)
			root->parent = nullptr;
	}
	else                                                                       //���ڵ��������Ҳ���Һ���
	{
		SplayNode<K, V>* left_tree = root->lc;                                 //left_treeָ����ڵ������
		left_tree->parent = nullptr;                                           //������ڵ�����������
		root->lc = nullptr;
		root = root->rc;                                                       //rootָ����ڵ���Һ���
		root->parent = nullptr;                                                //rootָ��Ľڵ��parentָ����Ϊnullptr
		search(w->key);                                                        //���µĸ��ڵ㿪ʼ���²���w->key�����ұ�Ȼʧ�ܣ�����"����"����С�ڵ����չ������
		root->lc = left_tree;                                                  //���Ӹ��ڵ���֮ǰ�����������
		left_tree->parent = root;                                              //��������
	}
	delete w;                                                                  //�ͷŵ�w
	w = nullptr;
	size--;                                                                    //���¹�ģ
	if (root != nullptr)                                                       //���¸߶�
		updateHeight(root);
	return true;                                                               //ɾ���ɹ�������true
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



