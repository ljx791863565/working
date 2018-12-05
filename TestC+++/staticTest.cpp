#include <stdio.h>
#include <iostream>
static int a;
static int b = 1;

class Base
{
public:
	static int g;
};

class Derivde1 : public Base
{

};

class Derivde2 : public Base
{

};
int main()
{	
	int c;
	int d = 2;
	static int e;
	static int f = 3;

	printf("a = %d, b = %d, c = %d, d = %d, e = %d, f = %d \n", a, b, c, d, e, f);

	Base b1;
	Derivde1 d1;
	Derivde2 d2;

	b1.g++;
	printf("g = %d\n", b1.g);
	
	d1.g++;
	printf("g = %d\n", d1.g);

	d2.g++;
	printf("g = %d\n", d2.g);
	return 0;
}
