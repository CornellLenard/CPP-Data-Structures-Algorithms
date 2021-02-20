/*********************************************************************************
 *   @file        HashMapDictionary.h
 *   @brief       The header file for C++ implemented HashMap Dictionary
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
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

template<typename K, typename V> class HashMapDictionary : public Dictionary<K, V>    //ɢ�б�ģ����
{
protected:
	Entry<K, V>** ht;                                                          //ָ��Ͱ�����ָ�룬Ͱ�����е�ÿһ��Ԫ�ض���һ��ָ��һ��������ָ��
	int capacity;                                                              //Ͱ��������
	int size;                                                                  //��������
	BitMap* lazy_removal;                                                      //����ɾ�����
	bool isLazilyRemoved(int x);                                               //�ж�x�Ƿ�Ϊ����ɾ��
	void markAsRemoved(int x);                                                 //���xΪ����ɾ��
	int probeForHit(const K& k);                                               //�عؼ���k��Ӧ�Ĳ��������ҵ�����ƥ���Ͱ����������
	int probeForFree(const K& k);                                              //�عؼ���k��Ӧ�Ĳ��������ҵ��׸����õĿ�Ͱ����������
	void rehash();                                                             //��ɢ���㷨������Ͱ���飬��֤װ�������ھ���������
	int getPrime(int c);                                                       //��ȡ��С��c�ĵ�һ������
	//����ɢ����ĺ���
	size_t hashCode(char c);                                                   //�ַ�
	size_t hashCode(int k);                                                    //����
	size_t hashCode(long long i);                                              //��������
	size_t hashCode(char s[]);                                                 //�����ַ�����ѭ����λɢ���루Cyclic Shift Hash Code��
public:
	HashMapDictionary(int c = 11);                                             //���캯��������һ��������С��c��ɢ�б�c����ʵ����������
	~HashMapDictionary();                                                      //�����������ͷ�Ͱ���鼰���и��ǿ�Ԫ����ָ��Ĵ���
	int getSize() const;                                                       //���ص�ǰ�Ĵ�����Ŀ
	bool put(K k, V v);                                                        //�������(��ֹ��ͬ�������ʿ���ʧ��)�����ز����Ƿ�ɹ�
	V* get(K k);                                                               //��ȡ����
	bool remove(K k);                                                          //ɾ������������ɾ���Ƿ�ɹ�
};

template<typename K, typename V> bool HashMapDictionary<K, V>::isLazilyRemoved(int x) //�ж��Ƿ�Ϊ����ɾ��
{
	return lazy_removal->test(x);                                              //ֱ�ӵ���BitMap��test()����
}

template<typename K, typename V> void HashMapDictionary<K, V>::markAsRemoved(int x)   //���xΪ����ɾ��
{
	lazy_removal->set(x);                                                      //ֱ�ӵ���BitMap��set()����
}

template<typename K, typename V> int HashMapDictionary<K, V>::probeForHit(const K& k) //�عؼ���k��Ӧ�Ĳ��������ҵ�����ƥ���Ͱ����������
{
	int r = hashCode(k) % capacity;                                            //����õ��ؼ���k��Ӧ�ĳ�ʼ����
	while (((ht[r] != nullptr) && (ht[r]->key != k)) || ((ht[r] == nullptr) && (isLazilyRemoved(r) == true))) //��������¼����������
		r = (r + 1) % capacity;                                                //1.ht[r]�ǿյ�ָ��Ĵ������� 2.ht[r]Ϊ�յ��Ǵ�λ��Ϊ����ɾ��
	return r;
}

template<typename K, typename V> int HashMapDictionary<K, V>::probeForFree(const K& k)//�عؼ���k��Ӧ�Ĳ��������ҵ��׸����õĿ�Ͱ����������
{
	int r = hashCode(k) % capacity;                                            //����õ��ؼ���k��Ӧ�ĳ�ʼ����
	while (ht[r] != nullptr)                                                   //ֻҪht[r]���ǿյģ���һֱ�������
		r = (r + 1) % capacity;
	return r;
}

template<typename K, typename V> void HashMapDictionary<K, V>::rehash()        //��ɢ���㷨
{
	int old_capacity = capacity;
	Entry<K, V>** old_ht = ht;
	capacity = getPrime(2 * capacity);                                         //ͨ��getPrime()ѡȡ���ʵ�����
	ht = new Entry<K, V> * [capacity];                                         //�����µ�Ͱ����ռ�
	memset(ht, 0, capacity * sizeof(Entry<K, V>*));                            //��ʼ����Ͱ����
	delete lazy_removal;                                                       //��������BitMap
	lazy_removal = new BitMap(capacity);
	size = 0;
	for (int i = 0; i < old_capacity; i++)                                     //����ԭͰ����
	{
		if (old_ht[i] != nullptr)                                              //��ָ��ht[i]����nullptr
		{
			put(old_ht[i]->key, old_ht[i]->value);                             //������ָ��Ĵ����Ĺؼ������ֵ����Ϊ�´���������Ͱ������
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
	unsigned int h = 0;                                                        //ɢ����
	size_t n = strlen(s);
	for (size_t i = 0; i < n; i++)                                             //�������ң��������ÿһ�ַ�
	{
		h = (h << 5) | (h >> 27);
		h += static_cast<int>(s[i]);
	}                                                                          //ɢ����ѭ������5λ�����ۼӵ�ǰ�ַ�
	return static_cast<size_t>(h);                                             //������õ�ɢ���룬ʵ���Ͽ����Ϊ���Ƶġ�����ʽɢ���롱
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

template<typename K, typename V> bool HashMapDictionary<K, V>::put(K k, V v)   //�������(��ֹ��ͬ�������ʿ���ʧ��)�����ز����Ƿ�ɹ�
{
	if (ht[probeForHit(k)] != nullptr)                                         //�ȵ���probeForHit()���õ��ؼ���k��Ӧ�������������������Ӧ��Ͱ�ǿ�
		return false;                                                          //����ζ���Ѿ��д���������ͬ�Ĺؼ����ˣ��򷵻ز���ʧ��
	int r = probeForFree(k);                                                   //���򣬿��Բ��룬����probeForFree()�õ��ؼ���k��Ӧ�Ŀ�Ͱ������
	ht[r] = new Entry<K, V>(k, v);                                             //��������
	size++;
	if (getSize() * 2 > capacity)                                              //װ�����Ӵ���50%����ɢ��
		rehash();
	return true;                                                               //���ز���ɹ�
}

template<typename K, typename V> V* HashMapDictionary<K, V>::get(K k)          //��ȡ����
{
	int r = probeForHit(k);                                                    //����probeForHit()���õ��ؼ���k��Ӧ������
	return (ht[r] != nullptr) ? &(ht[r]->value) : nullptr;                     //���ht[r]�ǿգ��򷵻ض�Ӧ��������ֵ�ĵ�ַ�����򷵻ؿ�ָ��
}

template<typename K, typename V> bool HashMapDictionary<K, V>::remove(K k)     //ɾ������������ɾ���Ƿ�ɹ�
{
	int r = probeForHit(k);                                                    //����probeForHit()���õ��ؼ���k��Ӧ������
	if (ht[r] == nullptr)                                                      //���ht[r]Ϊ�գ�����ζ��Ͱ����������ָ��ؼ���Ϊk�Ĵ�����ָ��
		return false;                                                          //����ɾ��ʧ��
	delete ht[r];                                                              //���������ɾ��
	ht[r] = nullptr;
	markAsRemoved(r);                                                          //���Ϊ����ɾ��
	size--;
	return true;                                                               //����ɾ���ɹ�
}

