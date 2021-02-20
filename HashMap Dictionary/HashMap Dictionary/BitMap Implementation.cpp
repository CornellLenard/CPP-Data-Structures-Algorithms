/*********************************************************************************
 *   @file        BitMap Implementation.cpp
 *   @brief       The C++ implementation of BitMap class
 *   @details
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   �˿�����ʦ����Զ����
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#include "BitMap.h"
#include <memory>
using namespace std;

void BitMap::init(int n)                                                       //��ʼ��
{
	N = (n + 7) / 8;                                                           //һ��char��8��bitλ�����Ը���n�Ĵ�Сȷ����Ҫ���ٸ�char����NΪ����
	M = new char[N];                                                           //ȷ��N�󼴿ɿ��ٿռ�
	memset(M, 0, N);                                                           //��ʼ�����ٵĿռ�
}

BitMap::BitMap(int n)
{
	init(n);
}

BitMap::~BitMap()
{
	delete[] M;
	M = nullptr;
}

void BitMap::set(int k)                                                        //���õ�kλ��ע������ĵڼ�λ�Ǵ�0��ʼ�ģ���0λ��M[0]���char������λ
{
	expand(k);
	M[k >> 3] |= (0x80 >> (k & 0x07));
}

void BitMap::clear(int k)                                                      //�����kλ
{
	expand(k);
	M[k >> 3] &= ~(0x80 >> (k & 0x07));
}

bool BitMap::test(int k)                                                       //��֤��kλ�Ƿ�������
{
	expand(k);
	return M[k >> 3] & (0x80 >> (k & 0x07));
}

void BitMap::expand(int k)                                                     //�����㷨
{
	if (k < N * 8)                                                             //���k<N*8����Ŀǰbitλ�㹻��ʾk�����Բ�������
		return;
	int old_N = N;                                                             //������Ҫ���ݣ��ȱ��浱ǰ�ĸ�������
	char* old_M = M;
	init(2 * k);                                                               //��2*k�ٴν��г�ʼ��
	memcpy_s(M, N, old_M, old_N);                                              //��������
	delete[] old_M;                                                            //ԭ�ȵ����ݾͿ����ͷŵ���
	old_M = nullptr;
}




