/*********************************************************************************
 *   @file        HashMapDictionary.h
 *   @brief       The header file for C++ implemented HashMap Dictionary
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

#include "Dictionary.h"
#include "Entry.h"
#include "BitMap.h"
#include <cmath>
#include <cstring>
using namespace std;

template<typename K, typename V> class HashMapDictionary : public Dictionary<K, V>    //散列表模板类
{
protected:
	Entry<K, V>** ht;                                                          //指向桶数组的指针，桶数组中的每一个元素都是一个指向一个词条的指针
	int capacity;                                                              //桶数组容量
	int size;                                                                  //词条数量
	BitMap* lazy_removal;                                                      //懒惰删除标记
	bool isLazilyRemoved(int x);                                               //判断x是否为懒惰删除
	void markAsRemoved(int x);                                                 //标记x为懒惰删除
	int probeForHit(const K& k);                                               //沿关键码k对应的查找链，找到词条匹配的桶，返回索引
	int probeForFree(const K& k);                                              //沿关键码k对应的查找链，找到首个可用的空桶，返回索引
	void rehash();                                                             //重散列算法，扩充桶数组，保证装填因子在警戒线以下
	int getPrime(int c);                                                       //获取不小于c的第一个素数
	//计算散列码的函数
	size_t hashCode(char c);                                                   //字符
	size_t hashCode(int k);                                                    //整数
	size_t hashCode(long long i);                                              //长长整数
	size_t hashCode(char s[]);                                                 //生成字符串的循环移位散列码（Cyclic Shift Hash Code）
public:
	HashMapDictionary(int c = 11);                                             //构造函数，创建一个容量不小于c的散列表，c可视实际需求设置
	~HashMapDictionary();                                                      //析构函数，释放桶数组及其中各非空元素所指向的词条
	int getSize() const;                                                       //返回当前的词条数目
	bool put(K k, V v);                                                        //插入词条(禁止雷同词条，故可能失败)，返回插入是否成功
	V* get(K k);                                                               //读取词条
	bool remove(K k);                                                          //删除词条，返回删除是否成功
};

template<typename K, typename V> bool HashMapDictionary<K, V>::isLazilyRemoved(int x) //判断是否为懒惰删除
{
	return lazy_removal->test(x);                                              //直接调用BitMap的test()即可
}

template<typename K, typename V> void HashMapDictionary<K, V>::markAsRemoved(int x)   //标记x为懒惰删除
{
	lazy_removal->set(x);                                                      //直接调用BitMap的set()即可
}

template<typename K, typename V> int HashMapDictionary<K, V>::probeForHit(const K& k) //沿关键码k对应的查找链，找到词条匹配的桶，返回索引
{
	int r = hashCode(k) % capacity;                                            //计算得到关键码k对应的初始索引
	while (((ht[r] != nullptr) && (ht[r]->key != k)) || ((ht[r] == nullptr) && (isLazilyRemoved(r) == true))) //两种情况下继续向后搜索
		r = (r + 1) % capacity;                                                //1.ht[r]非空但指向的词条不对 2.ht[r]为空但是此位置为懒惰删除
	return r;
}

template<typename K, typename V> int HashMapDictionary<K, V>::probeForFree(const K& k)//沿关键码k对应的查找链，找到首个可用的空桶，返回索引
{
	int r = hashCode(k) % capacity;                                            //计算得到关键码k对应的初始索引
	while (ht[r] != nullptr)                                                   //只要ht[r]不是空的，就一直向后搜索
		r = (r + 1) % capacity;
	return r;
}

template<typename K, typename V> void HashMapDictionary<K, V>::rehash()        //重散列算法
{
	int old_capacity = capacity;
	Entry<K, V>** old_ht = ht;
	capacity = getPrime(2 * capacity);                                         //通过getPrime()选取合适的容量
	ht = new Entry<K, V> * [capacity];                                         //开辟新的桶数组空间
	memset(ht, 0, capacity * sizeof(Entry<K, V>*));                            //初始化新桶数组
	delete lazy_removal;                                                       //重新设置BitMap
	lazy_removal = new BitMap(capacity);
	size = 0;
	for (int i = 0; i < old_capacity; i++)                                     //遍历原桶数组
	{
		if (old_ht[i] != nullptr)                                              //若指针ht[i]不是nullptr
		{
			put(old_ht[i]->key, old_ht[i]->value);                             //则将其所指向的词条的关键码和数值构造为新词条插入新桶数组中
			delete old_ht[i];
			old_ht[i] = nullptr;
		}
	}
	delete[] old_ht;
	old_ht = nullptr;
}

template<typename K, typename V> int HashMapDictionary<K, V>::getPrime(int c)
{
	int i = c, temp = 0;
	bool found = true;
	for (;; i++)
	{
		found = true;
		temp = sqrt(i);
		for (int j = 2; j <= temp; j++)
		{
			if (i % j == 0)
			{
				found = false;
				break;
			}
		}
		if (found == true)
			break;
	}
	return i;
}

template<typename K, typename V> size_t HashMapDictionary<K, V>::hashCode(char c)
{
	return static_cast<size_t>(c);
}

template<typename K, typename V> size_t HashMapDictionary<K, V>::hashCode(int k)
{
	return static_cast<size_t>(k);
}

template<typename K, typename V> size_t HashMapDictionary<K, V>::hashCode(long long i)
{
	return static_cast<size_t>((i >> 32) + static_cast<int>(i));
}

template<typename K, typename V> size_t HashMapDictionary<K, V>::hashCode(char s[])
{
	unsigned int h = 0;                                                        //散列码
	size_t n = strlen(s);
	for (size_t i = 0; i < n; i++)                                             //自左向右，逐个处理每一字符
	{
		h = (h << 5) | (h >> 27);
		h += static_cast<int>(s[i]);
	}                                                                          //散列码循环左移5位，再累加当前字符
	return static_cast<size_t>(h);                                             //如此所得的散列码，实际上可理解为近似的“多项式散列码”
}

template<typename K, typename V> HashMapDictionary<K, V>::HashMapDictionary(int c)
{
	capacity = getPrime(c);
	size = 0;
	ht = new Entry<K, V> * [capacity];
	memset(ht, 0, capacity * sizeof(Entry<K, V>*));
	lazy_removal = new BitMap(capacity);
}

template<typename K, typename V> HashMapDictionary<K, V>::~HashMapDictionary()
{
	for (int i = 0; i < capacity; i++)
	{
		if (ht[i] != nullptr)
		{
			delete ht[i];
			ht[i] = nullptr;
		}
	}
	delete[] ht;
	ht = nullptr;
	delete lazy_removal;
	lazy_removal = nullptr;
}

template<typename K, typename V> int HashMapDictionary<K, V>::getSize() const
{
	return size;
}

template<typename K, typename V> bool HashMapDictionary<K, V>::put(K k, V v)   //插入词条(禁止雷同词条，故可能失败)，返回插入是否成功
{
	if (ht[probeForHit(k)] != nullptr)                                         //先调用probeForHit()，得到关键码k对应的索引，如果此索引对应的桶非空
		return false;                                                          //则意味着已经有词条具有相同的关键码了，则返回插入失败
	int r = probeForFree(k);                                                   //否则，可以插入，调用probeForFree()得到关键码k对应的空桶的索引
	ht[r] = new Entry<K, V>(k, v);                                             //创建词条
	size++;
	if (getSize() * 2 > capacity)                                              //装填因子大于50%则重散列
		rehash();
	return true;                                                               //返回插入成功
}

template<typename K, typename V> V* HashMapDictionary<K, V>::get(K k)          //读取词条
{
	int r = probeForHit(k);                                                    //调用probeForHit()，得到关键码k对应的索引
	return (ht[r] != nullptr) ? &(ht[r]->value) : nullptr;                     //如果ht[r]非空，则返回对应词条的数值的地址，否则返回空指针
}

template<typename K, typename V> bool HashMapDictionary<K, V>::remove(K k)     //删除词条，返回删除是否成功
{
	int r = probeForHit(k);                                                    //调用probeForHit()，得到关键码k对应的索引
	if (ht[r] == nullptr)                                                      //如果ht[r]为空，则意味着桶数组中暂无指向关键码为k的词条的指针
		return false;                                                          //返回删除失败
	delete ht[r];                                                              //否则，则可以删除
	ht[r] = nullptr;
	markAsRemoved(r);                                                          //标记为懒惰删除
	size--;
	return true;                                                               //返回删除成功
}

