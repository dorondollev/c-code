#include <stdio.h>
#include <stdlib.h>

void printArr(int,int);

#define COL 5
#define ROW 6

int array[COL][ROW], i, j;

int main()
{
	for(i=0; i < COL; i++)
		for(j=0; j < ROW; j++)
			array[i][j] = rand() % 20 + 1;
	printArr(0,0);
	return 0;
}

void printArr(int i, int j)
{
	if(i == COL)
		return;
	else if(j == ROW)
	{
		printf("\n");
		i++;
		printArr(i, j++);
	}
	else
	{
		printf("%d\t", array[i][j]);
		printArr(i, j++);
		return;
	}
}