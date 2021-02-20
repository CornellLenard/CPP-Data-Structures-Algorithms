#include "List.h"
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
	List<int> lst;
	Visit<int> visit;
	for (int i = 1; i <= 6; i++)
		lst.insertAsFirst(i);
	for (int i = 0; i < 7; i++)
		lst.insertAsLast(7);
	for (int i = 11; i >= 8; i--)
		lst.insertAsLast(i);
	lst.traverse(visit);
	cout << '\n';
	lst.deduplicate();
	lst.traverse(visit);
	cout << '\n';
	cout << lst.getSize() << "  " << lst.isEmpty() << '\n';
	cout << (lst.find(7))->data << '\n';
	lst.sort();
	lst.traverse(visit);
	cout << '\n';
	lst.reverse();
	lst.traverse(visit);
	return 0;
}