
#include <stdio.h>
#include <time.h>

clock_t start, end;

//递归
//O(2^n)
//求40项共用2.6s
int fibonacci(int n)
{
	if (n == 1 || n == 2){
		return 1;
	}
	return fibonacci(n-1) + fibonacci(n - 2);
}

//O(n)
//求40项几乎不耗时间
int fibonacci2(int n)
{
	int f0 = 1;
	int f1 = 1;
	int f2 = 0;

	int i;
	for (i = 2; i < n; i++){
		f2 = f0 + f1;
		f0 = f1;	//保存最新的第前二项
		f1 = f2;	//保存最新对第前一项
					//要求的第三项为前两项之和，不用递归再求前两项之前的所有项的值
	}
	return f2;
}
int main()
{
	int i;
	start = clock();
	for (i = 1; i < 40; i++){
		printf("fibonacci[%d] = %d\n", i, fibonacci2(i));
	}
	end = clock();

	double times = ((double)(end - start)) /CLOCKS_PER_SEC;
	printf("user %f secs\n", times);
	return 0;
}
