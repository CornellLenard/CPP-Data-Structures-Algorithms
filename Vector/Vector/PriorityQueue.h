/*********************************************************************************
 *   @file        PriorityQueue.h
 *   @brief       The header file for C++ implemented Priority Queue Abstract Class
 *   @details     Utilizes Generic Programming
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

template<typename T> class PriorityQueue                                       //���ȼ����г���ģ����
{
public:
	virtual void insert(T e) = 0;                                              //���ձȽ���ȷ�������ȼ�����������
	virtual T getMax() = 0;                                                    //ȡ�����ȼ���ߵĴ���
	virtual T deleteMax() = 0;                                                 //ɾ�����ȼ���ߵĴ��������������ݷ���
};
