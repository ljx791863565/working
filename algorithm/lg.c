#include <stdio.h>

int lg(int n)
{
	int i;
	for (i = 0; n > 0; n /= 2){
		i++;
	}
	return i;
}
int main()
{
	int i, N;
	printf("%9s %2s %9s\n", "N", "lg(N)", "N*lg(N)");
	for (i = 0, N = 10; i <= 6; i++, N *= 10){
		printf("%9d %2d %9d\n", N, lg(N), N*lg(N));
	}

	return 0;
}
