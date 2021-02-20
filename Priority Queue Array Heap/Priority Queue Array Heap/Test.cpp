#include "PriorityQueueArrayHeap.h"
#include <iostream>
using namespace std;

int main()
{
	PriorityQueueArrayHeap<int> pq;
	pq.insert(1);
	pq.insert(2);
	pq.insert(3);
	cout << pq.getSize() << "   " << pq.isEmpty() << '\n';
	for (int i = 0; i < 3; i++)
		cout << pq.deleteMax() << "  ";
	return 0;
}