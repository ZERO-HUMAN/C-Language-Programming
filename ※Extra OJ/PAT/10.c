#include<stdio.h> 

int main(void)
{
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d + %d = %d\n", a, b, a + b);
	printf("%d - %d = %d\n", a, b, a - b);
	printf("%d * %d = %d\n", a, b, a * b);
	a / b == (double) a / b ?
	printf( "%d / %d = %d\n" , a, b, a / b)
	:
	printf( "%d / %d = %.2lf\n" , a, b, (double)a / b);
	return 0;
}
