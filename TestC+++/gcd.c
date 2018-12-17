#include <stdio.h>

/*
 *欧几里德算法
 *寻找两个非负数 p q 的最大公约数
 *当q为0时，最大公约数是p
 *当不为0时，最大公约数为两数相除的余数和q的最大公约数
 */

int gcd(int p, int q)
{
	if (q == 0){
		return p;
	}
	int r = p % q;
	return gcd(q, r);
}
int main()
{
	int a = 4, b = 8;
	int num = gcd(a, b);

	printf("gcd of %d, %d is %d\n",a, b, num);

	return 0;
}
