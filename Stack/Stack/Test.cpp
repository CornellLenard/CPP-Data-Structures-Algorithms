#include "Stack.h"
#include <iostream>
using namespace std;

int main()
{
	Stack<int> st;
	for (int i = 1; i <= 11; i++)
		st.push(i);
	cout << st.getSize() << "  " << st.isEmpty() << '\n';
	for (int i = 0; i < 11; i++)
		cout << st.pop() << "  ";
	return 0;
}