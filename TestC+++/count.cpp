#include <iostream>
#include <time.h>
#include <stdio.h>
clock_t start, end;

#define N 10000

using namespace std;

int main()
{
	start = clock();
	long long count = 0;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			for (int k = 0; k < N; k++){
				count++;
			}
		}
	}
	end = clock();
	
	double time = (double)(end - start)/CLOCKS_PER_SEC;
	printf("time = %f secands\n", time);
}
