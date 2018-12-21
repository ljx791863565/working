
#include <iostream>
#include <stdio.h>

class A
{
private:
	static int a;
public:
	static void setA(int num)
	{
		a = num;
	}
};
int main()
{
	A a1;
	a1.setA(6);
	printf("%d\n", a1.a);

	return 0;
}
