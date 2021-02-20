#include "Vector.h"
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
	Vector<int> vec;
	Visit<int> visit;
	for (int i = 1; i <= 6; i++)
		vec.insert(i);
	for (int i = 0; i < 6; i++)
		vec.insert(7);
	for (int i = 11; i > 7; i--)
		vec.insert(i);
	cout << vec.getSize() << "  " << vec.isEmpty() << "  " << vec.disordered() << '\n';
	vec.traverse(visit);
	cout << '\n';
	vec.uniquify();
	vec.traverse(visit);
	cout << '\n';
	vec.insert(12);
	vec.remove(vec.getSize() - 1);
	vec.traverse(visit);
	cout << '\n';
	vec.sort();
	vec.traverse(visit);
	return 0;
}