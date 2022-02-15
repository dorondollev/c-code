#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LENGTH 200

char delimiters[LENGTH] = " ,'\n''\t'";
int A[LENGTH];
int d=2;
int heapSize;

//int A[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
//30 10 20 40 60 50
void buildHeap(int *A);
void heapify(int *A, int i);
void swap(int *x, int *y);
void print(int *A);
void heapSort(int *A);
void heapInsert(int *A, int key);
void buildHeapPrepare(char *pstr);
void halt();
void stoi(char string[], int *A);
void readline(char *s);

int main(int argc, char *argv[])
{
	int menu, key, new_d;
	heapSize = 0;
	
	while (1)
	{
		printf("D-ARY HEAP MENU\n\n");
		printf("1.\tBuild a heap\n");
		printf("2.\tInsert a key to the heap\n");
		printf("3.\tExtract and print max key from heap\n");
		printf("4.\tPrint heap\n");
		printf("5.\tChange d-ary heap\n");
		printf("6.\tExit\n");
		printf("Please choose one: ");
		scanf("%d", &menu);
		switch (menu)
		{
			case 1:
			{
				while (1)
				{
					printf("Please enter integer 0(zero) to stop: ");
					scanf("%d", &key);
					if (key !=0)
						A[heapSize++] = key;
					else
						break;					
				}
				buildHeap(A);
				print(A);
				break;
			}
			case 2: 
			{
				printf("Please enter a key to insert: ");
				scanf("%d", &key);
				heapInsert(A,key);
				break;
			}
			case 3: 
			{
				if(A[0])
				{
					printf("Max heap %d extracted\n",heapExtractMax(A));
				}
				print(A);
				break;
			}
			case 4:
			{
				print(A);
				break;
			}
			case 5:
			{
				printf("Please enter d number: ");
				scanf("%d", &new_d);
				if(new_d < 2)
				{
					printf("D can't be <2\n");
					continue;
				}
				d = new_d;
				buildHeap(A);
				print(A);
				break;
			}
			case 6:
			{
				halt();
				break;
			}
			default: printf("Sorry does not correspond to that function please try again.\n");
		}
	}
	return 0;
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
        printf("start heap sort\n");
        int i;
        buildHeap(A);
        for (i=length(A)-1;i > 0;i--)
        {
                swap(&A[0], &A[i]);
                heapSize--;
                heapify(A,0);
        }
}

void print(int *A)
{
        int i;
        for(i=0;i<length(A);i++)
                printf("%d ",A[i]);
        printf("\n");
}

int heapExtractMax(int *A)
{
	int max;
	if(heapSize < 0)
	{
		printf("Heap underflow: %d\n", heapSize);
		return -1;
	}
	max = A[0];
	A[0] = A[heapSize-1];
	A[heapSize-1] = (int)NULL;
	heapSize--;
	heapify(A,0);
	return max;
}

void heapInsert(int *A, int key)
{
	heapSize++;
	int i = heapSize-1;
	while (i > 0 && A[parent(i)] < key)
	{
		A[i] = A[parent(i)];
		i = parent(i);
	}
	A[i] = key;
}

void buildHeapPrepare(char *pstr)
{
	int i=1;
	
	while ((pstr = strtok((char *)NULL, delimiters )) != NULL) 
	{
		if (i > LENGTH)
			break;
		A[i++] = atoi(pstr);
	}
}

void buildHeap(int *A)
{
	heapSize = length(A);
	int i;
	for(i=length(A)/2; i > 0; i--)
		heapify(A, i-1);
}

void heapify(int *A, int i)
{
	int largest=i, l, r;
	do
	{
		print(A);
		l = left(i);
		printf("l<%d>heapSize<%d>\n",l,heapSize);
		r = right(i);
		printf("r<%d>i<%d>\n",r,i);
		if (l < heapSize)
		{
			printf("in L: %d\n",l);
			if(A[l]>A[i])
			{
				printf("A[l]<%d>A[i]%d\n",A[l],A[i]);
				largest = l;
			}
			else
			{
				printf("A[l]<%d>A[i]%d\n",A[l],A[i]);
				largest = i;
			}
		}
		if (r < heapSize)
		{
			printf("in R: %d\n",r);
			if(A[r] > A[largest])
			{
				printf("A[r]<%d>A[largest]%d\n",A[r],A[largest]);
				largest = r;
			}
		}
		if(largest != i)
		{
			swap(&A[i], &A[largest]);
			i=largest;
		}
		else
			break;
	}
	while (i < heapSize);
}

int max(int x, int y)
{
	return (x > y) ? x : y;
}

int parent(int i)
{
	return (i / 2);
}

int left(int i)
{
	double a=heapSize, b=d, c;
	c=log(a) / log(b);
	long e = c;
	printf("log base-%lf of %lf c=%lf is: %d\n",a,b,c,d);
	return e;	
}
/*
int left(int i)
{
	return 2*i+1;
}
*/
int right(int i)
{
	return left(i)+1;
}

void swap(int *x, int *y)
{
	int tmp;
	printf("swap %d with %d\n",*x,*y);
	tmp = *x;
	*x = *y;
	*y = tmp;
}

/* quit program with greetings */
void halt()
{
	printf("bye bye\n");
	exit(0);
}
