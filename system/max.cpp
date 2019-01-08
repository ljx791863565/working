#include <iostream>

template <typename T>
inline const T& Max(const T& a, const T& b)
{
	return a > b ? a : b;
}
using namespace std;

int main()
{
	cout << Max(3, 4) << endl;
	cout << Max(3.7, 2.1) << endl;
	return 0;
}
