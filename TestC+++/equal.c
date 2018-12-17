#include <stdio.h>

int main()
{
	float a = 1.00000001;
	float b = 1.00000002;

	if (a == b){
		printf("a equal b\n");
	}else {
		printf("a not equal b\n");
	}

	return 0;
}
