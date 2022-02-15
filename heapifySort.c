#include <stdio.h>

#define MAXITEM 1000001
#define MAXLINE 256

char line[MAXLINE];
int count, a[MAXITEM];

main(){
	int i;
	count = 1;
	int a[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	/*while(fgets(line, MAXLINE, stdin)!='\0'){
		sscanf(line,"%d\n",&a[count]);
		count++;
	}*/
/*	printarray(); */
	count=11;
	for(i=count-1;i>0;i--){
		heapify(i,count-1);
	}
/*	printarray(); */
	for(i=count-1;i>1;i--){
		int temp;
		temp = a[1];
		a[1] = a[i];
		a[i] = temp;
		heapify(1,i-1);
/*		printarray(); */
	}
	for(i=1;i<count;i++){
		printf("%d ",a[i]);
	}

}
/*
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
*/
heapify(p,q)
int p,q;
{
	if(p<=q/2){ /* a[i] is not a leaf */
		int temp,c;
		if(2*p+1>q){
			c = 2*p;
		}else if(a[2*p] > a[2*p+1]){
			c = 2*p;
		}else{
			c = 2*p+1;
		}
		if(a[p] < a[c]){
			temp = a[c];
			a[c] = a[p];
			a[p] = temp;
		}
		heapify(c,q);
	}
}

printarray()
{
	int i;
	for(i=1;i<count;i++){
		printf("%3d ",a[i]);
	}
	printf("\n");
}
