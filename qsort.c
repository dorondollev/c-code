#include <stdio.h>

void quickSort(int A[], int p, int r);
int partition(int A[], int p, int r);
void printA(int A[],int,int);
void swap(int *y, int *x);

#define MAX 10
#define K 1

int main(int argc, char *argv[])
{
    int A[] = {5, 2, 6, 9, 7, 4, 8, 4, 3, 10};
	printA(A, 0, MAX);
	quickSort(A, 0, MAX-1);
	printA(A, 0, MAX);
    return 0;
}

void quickSort(int A[], int p, int r)
{
	if (K+p < r)//use the K only for question 5
    {
		int q = partition(A, p, r);
		quickSort(A, p, q);
        quickSort(A, q+1, r);
	}       
}

int partition(int A[], int p, int r)
{
	int x = A[p];
    int i = p - 1;
    int j = r + 1;

    while (TRUE)
    {
		do
        {
			j--;
		}
		while (A[j] > x);
        do
        {
			i++;
        }
        while (A[i] < x);
		if (i < j)
        {
			swap(&A[i], &A[j]);
		}
		else
			return j;
	}
}

void swap(int *y, int *x)
{
	int temp;
	temp = *y;
	*y = *x;
	*x = temp;
}

void printA(int A[], int j, int max)
{
        int i;
        for (i = j;i < max;i++ )
        {
                printf("%d ",A[i]);
        }
        printf("\n");
}
