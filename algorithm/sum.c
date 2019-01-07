#include <stdio.h>
#include <stdlib.h>

int main()
{
	int sum = 0;

	int i;
	for (i = 0; i< 5; i++){
		sum += i;
	}

	printf("%d\n", sum);

	return 0;
}
