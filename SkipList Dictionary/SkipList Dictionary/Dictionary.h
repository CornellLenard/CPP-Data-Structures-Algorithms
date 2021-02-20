/*********************************************************************************
 *   @file        Dictionary.h
 *   @brief       The header file for C++ implemented Dictionary Abstract Class
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

template<typename K, typename V> class Dictionary                              //�ʵ����ģ����
{
public:
	virtual int getSize() const = 0;                                           //��ǰ��������
	virtual bool put(K k, V v) = 0;                                            //�������(��ֹ��ͬ����ʱ����ʧ��)�����ز����Ƿ�ɹ�
	virtual V* get(K k) = 0;                                                   //��ȡ����
	virtual bool remove(K k) = 0;                                              //ɾ������������ɾ���Ƿ�ɹ�
};


