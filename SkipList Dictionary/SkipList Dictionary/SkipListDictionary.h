/*********************************************************************************
 *   @file        SkipListDictionary.h
 *   @brief       The header file for C++ implemented SkipList Dictionary
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "Dictionary.h"
#include "List.h"
#include "QualList.h"
using namespace std;

template<typename K, typename V> class SkipListDictionary : public Dictionary<K, V>, public List<QuadList<K, V>*>   //跳转表模板类
{
protected:
	//跳转表搜索算法
	bool skipSearch(ListNode<QuadList<K, V>*>*& qlist, QuadListNode<K, V>*& p, const K& k);
public:
	int getSize() const;                                                       //获取底层QuadList的规模
	int getLevel() const;                                                      //获取层高
	bool put(K k, V v);                                                        //插入词条，跳转表允许词条重复，因此插入必成功
	V* get(K k);                                                               //读取词条
	bool remove(K k);                                                          //删除词条，返回删除是否成功
};

//qlist是顶层列表，p指向qlist的首节点
template<typename K, typename V> bool SkipListDictionary<K, V>::skipSearch(ListNode<QuadList<K, V>*>*& qlist, QuadListNode<K, V>*& p, const K& k)
{
	while (true)
	{
		while ((p->succ != nullptr) && ((p->entry).key <= k))                  //从首节点出发，向后探索，遇到更大的key或到达尾哨兵节点处则停止探索
			p = p->succ;
		p = p->pred;                                                           //回溯一个位置
		if ((p->pred != nullptr) && ((p->entry).key == k))                     //如果p指向的节点此时并非头哨兵节点且其词条关键码为k，则命中
			return true;                                                       //则返回true
		qlist = qlist->succ;                                                   //否则，转入下一层
		if (qlist->succ == nullptr)                                            //如果已到达底层，即尾哨兵节点那一层，则失败
			return false;                                                      //则返回false
		p = (p->pred != nullptr) ? p->below : qlist->data->getFirst();         //否则，若p指向的节点并非头哨兵节点，则p向下移动一个单位
	}                                                                          //否则，则p移动到此时qlist对应的这一层的QuadList的第一个节点处
}

template<typename K, typename V> int SkipListDictionary<K, V>::getSize() const //获取底层QuadList的规模
{
	return (this->isEmpty() == true) ? 0 : this->getLast()->data->getSize();   //若List为空，则底层四联表规模为0，否则，获取末节点存储的指针所指向的四联表的规模
}

template<typename K, typename V> int SkipListDictionary<K, V>::getLevel() const//获取层高
{
	return List<QuadList<K, V>*>::getSize();                                   //直接调用List的getSize()即可
}

template<typename K, typename V> bool SkipListDictionary<K, V>::put(K k, V v)  //插入词条，跳转表允许词条重复，因此插入必成功
{
	if (this->isEmpty() == true)                                               //如果为空，则插入首个四联表
		this->insertAsFirst(new QuadList<K, V>());
	ListNode<QuadList<K, V>*>* qlist = this->getFirst();                       //从顶层四联表
	QuadListNode<K, V>* p = qlist->data->getFirst();                           //的首节点出发
	if (skipSearch(qlist, p, k) == true)                                       //查找适当的插入位置(不大于关键码k的最后一个节点p)
		while (p->below != nullptr)                                            //若已有雷同词条，则需强制转到塔底
			p = p->below;
	qlist = this->getLast();                                                   //以下，紧邻于p的右侧，一座新塔将自底而上逐层生长
	QuadListNode<K, V>* b = qlist->data->insertAfterAbove(k, v, p);            //新节点b即新塔基座
	uniform_int_distribution<int> u(0, 1);
	default_random_engine e;
	while (u(e))                                                               //经投掷硬币，若确定新塔需要再长高一层，则
	{
		while ((qlist->data->isValid(p) == true) && (p->above == nullptr))     //找出不低于此高度的最近前驱
			p = p->pred;
		if (qlist->data->isValid(p) == false)                                  //若该前驱是头哨兵节点
		{
			if (qlist == this->getFirst())                                     //且当前已是最顶层，则意味着必须
				this->insertAsFirst(new QuadList<K, V>);                       //首先创建新的一层，然后
			p = qlist->pred->data->getFirst()->pred;                           //将p转至上一层Skiplist的头哨兵节点
		}
		else                                                                   //否则
			p = p->above;                                                      //可将p提升至该高度
		qlist = qlist->pred;                                                   //上升一层，并在该层
		b = qlist->data->insertAfterAbove(k, v, p, b);                         //将新节点插入p之后、b之上
	}
	return true;
}

template<typename K, typename V> V* SkipListDictionary<K, V>::get(K k)         //读取词条
{
	if (this->isEmpty() == true)
		return nullptr;
	ListNode<QuadList<K, V>*>* qlist = this->getFirst();                       //从顶层四联表的
	QuadListNode<K, V>* p = qlist->data->getFirst();                           //首节点开始
	return (skipSearch(qlist, p, k) == true) ? &((p->entry).value) : nullptr;  //有多个命中时靠后者优先
}

template<typename K, typename V> bool SkipListDictionary<K, V>::remove(K k)    //删除词条，返回删除是否成功
{
	if (this->isEmpty() == true)                                               //空表情况
		return false;
	ListNode<QuadList<K, V>*>* qlist = this->getFirst();                       //从顶层四联表的
	QuadListNode<K, V>* p = qlist->data->getFirst();                           //首节点开始
	if (skipSearch(qlist, p, k) == false)                                      //目标词条不存在，直接返回false
		return false;
	do                                                                         //若目标词条存在，则逐层拆除与之对应的塔
	{
		QuadListNode<K, V>* lower = p->below;                                  //记住下一层节点，并
		qlist->data->remove(p);                                                //删除当前层节点，再
		p = lower;                                                             //转入下一层
		qlist = qlist->succ;
	} while (qlist->succ != nullptr);                                          //如上不断重复，直到塔基
	while ((this->isEmpty() == false) && (this->getFirst()->data->isEmpty() == true)) //逐一地
		List<QuadList<K, V>*>::remove(this->getFirst());                       //清除已可能不含词条的顶层四联表
	return true;                                                               //删除成功，返回true
}



