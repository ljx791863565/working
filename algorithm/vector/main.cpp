#include "vector.h"
//#include <iostream>
using namespace std;
template <typename T>
void print(T &e)
{
	cout << e;
}

int main()
{
	Vector<int> v(8, 5, 0);
//	v.inster(9);
//	v.inster(10);
	v.traverse(print);	
}
