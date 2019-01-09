#include <stdio.h>

int sum(int *a, int low, int high)
{
	if (high == low){
		return a[low];
	}else{
		int mid = (high + low) >> 1;
		return sum(a, low, mid) + sum(a, mid+1, high);
	}
}
int main()
{
	int array[10];
	int i;
	for (i = 0; i < 10; i++){
		array[i] = i + 1;
	}

	int num = sum(array, 0, 9);
	printf("num = %d\n", num);

	return 0;
}
