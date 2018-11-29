#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct test
{
	int a;
	char b[10];
	double c;
};

int main()
{
	struct test s;
	s.a = 1;
	strcpy(s.b, "lihua");
	s.c = 1.02;
	struct test s1;
//	memset(&s1, 0, sizeof(s1));
	memcpy(&s1, &s, sizeof(s));

	printf("a = %d b = %s c = %.f\n", s1.a, s1.b, s1.c);

	return 0;
}
