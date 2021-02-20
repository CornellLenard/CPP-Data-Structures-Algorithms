#include "SkipListDictionary.h"
#include <iostream>
using namespace std;

int main()
{
	SkipListDictionary<int, int> dict;
	cout << dict.put(1, 11) << '\n';
	cout << dict.put(2, 11) << '\n';
	cout << dict.put(2, 11) << '\n';
	cout << dict.getSize() << '\n';
	cout << *(dict.get(1)) << '\n';
	cout << dict.remove(4) << '\n';
	cout << dict.getSize() << '\n';
	cout << dict.remove(3) << '\n';
	cout << dict.getSize() << '\n';
	for (int i = 3; i <= 11; i++)
		dict.put(i, 11);
	cout << dict.getSize() << '\n';
	return 0;
}