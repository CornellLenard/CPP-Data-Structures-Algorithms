#include "Queue.h"
#include <iostream>
using namespace std;

int main()
{
	Queue<int> q;
	for (int i = 1; i <= 11; i++)
		q.enqueue(i);
	cout << q.getSize() << "  " << q.isEmpty() << '\n';
	for (int i = 0; i < 11; i++)
		cout << q.dequeue() << " ";
	return 0;
}