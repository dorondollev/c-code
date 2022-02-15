#include <stdio.h>

int heapSize;

void buildHeap(int *A);
void heapify(int *A, int i);
void swap(int *x, int *y);
void print(int *A);
void heapSort(int *A);

int main(int argc, char *argv[])
{
        int A[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
        print(A);
        heapSort(A);
        print(A);
        return 0;
}

void print(int *A)
{
        int i;
        for(i=0;i<length(A);i++)
                printf("%d ",A[i]);
        printf("\n");
}

int length(int *A)
{
        int i=0;
        while(A[i])
                i++;
        return i;
}

void heapSort(int *A)
{
        int i;
        buildHeap(A);
        for (i = length(A);i > 1;i--)
        {
                swap(&A[1], &A[i]);
                heapSize--;
                heapify(A,0);
        }
}

int heapExtractMax(int *A)
{
        int max;
        if(heapSize < 1)
        {
                printf("Heap underflow: %d\n", heapSize);
                return -1;
        }
        max = A[1];
        A[1] = A[heapSize];
        heapSize--;
        heapify(A,1);
        return max;
}

void heapInsert(int *A, int key)
{
        heapSize++;
        int i = heapSize;
        while (i > 0 && A[parent(i)] < key)
        {
                A[i] = A[parent(i)];
                i = parent(i);
        }
        A[i] = key;
}

void buildHeap(int *A)
{
        int i;
        heapSize = length(A);
        for(i=length(A)/2; i >= 0; i--)
                heapify(A, i);
}

void heapify(int *A, int i)
{
        int largest;
        int l = left(i);
        int r = right(i);
        if (l <= heapSize && A[l]>A[i])
                largest = l;
        else
                largest = i;
        if (r <= length(A)&& A[r] > A[largest])
                largest = r;
        if(largest != i)
        {
                swap(&A[i], &A[largest]);
                heapify(A, largest);
        }
}

int parent(int i)
{
        return (i / 2);
}

int left(int i)
{
        return 2*i;
}

int right(int i)
{
        return ((2*i) + 1);
}

void swap(int *x, int *y)
{
	int tmp;
    printf("before swap x is %d y is %d\n",*x,*y);
    tmp = *x;
    *x = *y;
    *y = tmp;
    printf("after swap x is %d y is %d\n",*x,*y);
}
