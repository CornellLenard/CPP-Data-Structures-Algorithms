/*********************************************************************************
 *   @file        BitMap Implementation.cpp
 *   @brief       The C++ implementation of BitMap class
 *   @details
 *
 *   @reference   Prof.Junhui Deng, Tsinghua University   邓俊辉老师，永远滴神！
 *   @author      Lenard Zhang
 *   @IDE         Visual Studio 2019
 *********************************************************************************/

#include "BitMap.h"
#include <memory>
using namespace std;

void BitMap::init(int n)                                                       //初始化
{
	N = (n + 7) / 8;                                                           //一个char有8个bit位，所以根据n的大小确定需要多少个char，即N为多少
	M = new char[N];                                                           //确认N后即可开辟空间
	memset(M, 0, N);                                                           //初始化开辟的空间
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

void BitMap::set(int k)                                                        //设置第k位，注意这里的第几位是从0开始的，第0位是M[0]这个char的最左位
{
	expand(k);
	M[k >> 3] |= (0x80 >> (k & 0x07));
}

void BitMap::clear(int k)                                                      //清除第k位
{
	expand(k);
	M[k >> 3] &= ~(0x80 >> (k & 0x07));
}

bool BitMap::test(int k)                                                       //验证第k位是否已设置
{
	expand(k);
	return M[k >> 3] & (0x80 >> (k & 0x07));
}

void BitMap::expand(int k)                                                     //扩容算法
{
	if (k < N * 8)                                                             //如果k<N*8，则目前bit位足够表示k，所以不用扩容
		return;
	int old_N = N;                                                             //否则需要扩容，先保存当前的各项数据
	char* old_M = M;
	init(2 * k);                                                               //用2*k再次进行初始化
	memcpy_s(M, N, old_M, old_N);                                              //拷贝数据
	delete[] old_M;                                                            //原先的数据就可以释放掉了
	old_M = nullptr;
}




