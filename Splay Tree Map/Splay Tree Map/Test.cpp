#include "SplayTreeMap.h"
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
	SplayTreeMap<int, int> stm;
	Visit<int> visit;
	stm.insert(1, 1);
	stm.insert(2, 2);
	stm.insert(3, 3);
	cout << stm.getSize() << "   " << stm.isEmpty() << '\n';
	stm.traverseIn(visit);
	cout << '\n';
	stm.remove(3);
	cout << stm.getSize() << '\n';
	stm.traverseIn(visit);
	cout << '\n';
	stm.remove(1);
	stm.remove(2);
	cout << stm.getSize();
	return 0;
}