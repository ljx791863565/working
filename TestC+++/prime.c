#include <stdio.h>

#define N 10000
int main()
{
	int arr[N];
	int i, j;

	for (i = 2; i < N; i++){
		arr[i] = 1;
	}
	for (i = 2; i < N; i++){
		if (arr[i]){
			for (j = i; j < N / i; j++){
				arr[i * j] = 0;
			}
		}
	}

	int count = 0;
	for (i = 2; i < N; i++){
		if (arr[i]){
			printf("%d ", i);
			count++;
		}
	}
	printf("\ncount = %d\n", count);
	return 0;
}
