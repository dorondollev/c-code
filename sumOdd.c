#include <stdio.h>

int main(int argc, char *argv[])
{
	int p=0, r=5;
	int result;
	int A[] = {1, 2, 3, 4, 5};
	result = sumOdd(A, p, r);
	printf("normal result is %d\n", result);
	result = sumRec(A, p, r);
	printf("recursive result is %d\n", result);
	return 0;
}

int sumRec(int A[], int p , int r)
{
	if (p > r)
		return 0;
	if((p == r) && (A[p] % 2 > 0))
		return A[p];
	if((p == r) && (A[p] % 2 == 0))
		return 0;
	return sumRec(A, p, ((p+r)/2)) + sumRec(A, ((p+r)/2)+1, r);
}

int sumOdd(int A[], int p, int r)
{
	int result=0;
	for (p=0; p <= r; p++)
	{
		if (A[p] % 2 > 0)
		{
			result += A[p];
		}
	}
	return result;
}
