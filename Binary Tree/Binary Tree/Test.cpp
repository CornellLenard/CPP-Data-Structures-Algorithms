#include "BinaryTree.h"
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
	BinaryTree<int> bt;
	Visit<int> visit;
	bt.insertAsRoot(2);
	bt.insertAsLC(bt.getRoot(), 1);
	bt.insertAsRC(bt.getRoot(), 3);
	cout << bt.getSize() << "  " << bt.isEmpty() << '\n';
	bt.traverseIn(visit);
	cout << '\n';
	bt.remove(bt.getRoot()->lc);
	bt.remove(bt.getRoot()->rc);
	cout << bt.getSize() << '\n';
	bt.traverseIn(visit);
	cout << '\n';
	bt.remove(bt.getRoot());
	cout << bt.isEmpty();
	return 0;
}