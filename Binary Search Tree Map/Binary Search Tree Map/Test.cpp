#include "BinarySearchTreeMap.h"
#include <iostream>
using namespace std;

template<typename T> class Visit
{
public:
	void operator () (const T& e)
	{
		cout << e << "  ";
	}
};

int main()
{
	BinarySearchTreeMap<int, int> bm;
	Visit<int> visit;
	bm.insert(1, 1);
	bm.insert(2, 2);
	bm.insert(3, 3);
	cout << bm.getSize() << "   " << bm.isEmpty() << '\n';
	bm.traverseIn(visit);
	cout << '\n';
	bm.remove(3);
	cout << bm.getSize() << '\n';
	bm.traverseIn(visit);
	cout << '\n';
	bm.remove(1);
	bm.remove(2);
	cout << bm.getSize();
	return 0;
}