#include <stdio.h>

void quickSort(int A[], int p, int r);
int partition(int A[], int p, int r);
void swap(int *y, int *x);
void printA(int A[],int,int);

#define MAX 10
#define K 1

int main(int argc, char *argv[])
{
        //{5, 2, 6, 9, 7, 4, 8, 4, 3, 10}=51
        //{5, 3, 6, 9, 7, 4, 8, 4, 2, 10}=50
        //{9, 3, 6, 5, 7, 4, 8, 4, 2, 10}=58
        //{2, 3, 4, 4, 5, 6, 7, 8, 9, 10}=64
        //{6, 9, 4, 2, 5, 8, 3, 7, 4, 10}=46
        int A[] = {5, 3, 2, 4, 4, 8, 6, 7, 9, 10};
        printA(A, 0, MAX);
        quickSort(A, 0, MAX-1);
        printA(A, 0, MAX);
        return 0;
}

void quickSort(int A[], int p, int r)
{
        if (K+p < r)
        {
                int q = partition(A, p, r);
                printf("q is: %d \n", q+1);
                printA(A, p, q+1);
                printA(A, q+1, r+1);
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
                        printf("checking %d pivot %d\n",A[j],x);
                }
                while (A[j] > x);
                do
                {
                        i++;
                        printf("checking %d pivot %d\n",A[i],x);
                }
                while (A[i] < x);
                if (i < j)
                {
					swap(&A[i], &A[j]);
                        //swap = A[i];
                        //A[i] = A[j];
                        //A[j] = swap;
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