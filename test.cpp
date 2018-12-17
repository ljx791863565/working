#include <stdio.h>
#include <iostream>
int main()
{
	int a = 12;
	int &b = a;
	printf("b = %d\n", b);

	int arr[12];
	for (int i = 0; i < a; i++){
		arr[i] = a--;
	}

	for (auto c : arr){
		printf("%d ", c);
	}
	printf("\n");
	printf("Hello World\n");
	return 0;
}
