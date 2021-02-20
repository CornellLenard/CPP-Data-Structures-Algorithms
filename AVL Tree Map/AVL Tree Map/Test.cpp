#include "AVLTreeMap.h"
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
	AVLTreeMap<int, int> am;
	Visit<int> visit;
	am.insert(1, 1);
	am.insert(2, 2);
	am.insert(3, 3);
	cout << am.getSize() << "   " << am.isEmpty() << '\n';
	am.traverseIn(visit);
	cout << '\n';
	am.remove(3);
	cout << am.getSize() << '\n';
	am.traverseIn(visit);
	cout << '\n';
	am.remove(1);
	am.remove(2);
	cout << am.getSize();
	return 0;
}