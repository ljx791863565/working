#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Test
{
public:
	void *operator new(size_t size);
	void operator delete(void *p);
	void *operator new[](size_t size);
	void operator delete[](void *p);
private:
	int m_data;
};

void* Test::operator new(size_t size)
{
	void *p = malloc(size);
	return p;
}

void Test::operator delete(void *p)
{
	free(p);
}

void* Test::operator new[](size_t size)
{
	void *p = malloc(size);
	return p;
}

void Test::operator delete[](void *p)
{
	free(p);
}

int main()
{
	Test *p = new Test[10];
	delete[] p;

	return 0;
}
