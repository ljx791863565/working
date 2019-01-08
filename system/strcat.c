#include <stdio.h>
#include <assert.h>

char *strcat(char *dest, const char *src)
{
	assert(dest != NULL && src != NULL);

	char *s1 = dest;

	while (*s1 != '\0'){
		s1++;
	}

	while (*s1++ = *src++)
		;
	return s1;
}
int main()
{	
	char p[20] = "hello";
	printf("%s\n", strcat(p, "world"));

	return 0;
}
