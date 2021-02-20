/*********************************************************************************
 *   @file        BitMap.h
 *   @brief       The header file for C++ implemented BitMap
 *   @details     Utilizes each bit to represent each element
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#pragma once

class BitMap                                                                   //λͼ��
{
private:
	char* M;                                                                   //ָ��BitMap����ŵĿռ��ָ��
	int N;                                                                     //M��ָ���char�ĸ���
protected:
	void init(int n);                                                          //��ʼ��BitMap
public:
	BitMap(int n = 8);                                                         //���캯��
	~BitMap();                                                                 //��������
	void set(int k);                                                           //���õ�kλ
	void clear(int k);                                                         //�����kλ
	bool test(int k);                                                          //��֤��kλ�Ƿ�������
	void expand(int k);                                                        //�����㷨
};

