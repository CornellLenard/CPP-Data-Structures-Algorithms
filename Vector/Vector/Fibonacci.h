/*********************************************************************************
 *   @file        Fibonacci.h
 *   @brief       The header file for C++ implemented Fibonacci
 *   @details     Provides a sequence of Fibonacci Series
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

class Fibonacci                                                                //쳲����������࣬����һ��һ�����ȵ�쳲���������
{
private:
	int size;                                                                  //쳲��������е�Ԫ�ظ���
	int* fib;                                                                  //�洢���е��ڴ�ռ�
	int position;                                                              //������ָ�����е�ǰԪ��λ��
public:
	Fibonacci(int s = 2);                                                      //���캯�����������г��Ȳ����˹�������
	~Fibonacci();                                                              //�ͷ�������ռ�ڴ�ռ�
	int get() const;                                                           //��ȡ���е�ǰԪ��
	void prev();                                                               //����ǰ��
};
