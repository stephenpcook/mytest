/* Program for calculating the n-th fibonacci number */
#include <stdio.h>

long fib(int n){
	int i;
	long fn1, fn_old=0L, fn=1L;

	for(i = 1; i<n; i++){
		fn1 = fn+fn_old;
		fn_old = fn;
		fn = fn1;
	}
	return fn; 
}

int main(void){
	int n;

	printf("Give integer n: ");
	scanf("%d", &n);
	printf("%ld \n", fib(n));
}
