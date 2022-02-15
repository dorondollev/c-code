#include <stdio.h>
int sumOddRec(int A[], int p , int r)
{
	if((p == r) && (p%2 == 0))
		return 0;
	if((p == r) && (p%2 != 0))
		return A[p];
	return sumOddRec(A,p,((p+r)/2)) + sumOddRec(A,((p+r)/2)+1,r);
}

int sumEvenRec(int A[], int p , int r)
{
	if((p == r) && (p%2 == 0))
		return A[p];
	if((p == r) && (p%2 != 0))
		return 0;
	return sumEvenRec(A,p,((p+r)/2)) + sumEvenRec(A,((p+r)/2)+1,r);
}

int main(int argc, char *argv[])
{
	int p=0, r=4;
	int result;
	int A[] = { 2, 3, 4, 5, 6};
	printf("sumOddRec = %d\n",sumOddRec(A,p,r));
	printf("sumEvenRec = %d\n",sumEvenRec(A,p,r));
   return 0;
}

