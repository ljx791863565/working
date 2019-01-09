#include <stdio.h>
#include <stdlib.h>

void sort_double_bubble(int *a, int N)
{
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N - i -1; j++){
			if (a[j] > a[j+1]){
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

void show(int *a, int N)
{
	for (int i = 0; i < N; i++){
		printf("%4d", a[i]);
	}
	printf("\n");
}

int main()
{
	int array[7] = {5, 2, 7, 4, 6, 3, 1};

	printf("before sort...\n");
	show(array, 7);
	sort_double_bubble(array, 7);
	printf("after sort...\n");
	show(array, 7);

	return 0;
}
