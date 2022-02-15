#include <stdio.h>
#include "set.h"

void union_set(char *set1, char *set2, char *set3)
{
		int i;
	for (i=0; i<ARRAY; i++)
		set3[i] = set1[i] | set2[i];
}

void intersect_set(char *set1, char *set2, char *set3)
{
	int i;
	for (i=0; i<ARRAY; i++)
		set3[i] = set1[i] & set2[i];
}

void sub_set(char *set1, char *set2, char *set3)
{
	int i;
	for (i=0; i<ARRAY; i++)
		set3[i] = set1[i] & ~set2[i];
}

void print_set(char *mySet)
{
	int i,j,b;
	unsigned char temp;

	for (i=b=0;i<ARRAY ;i++ )
	{
		temp = mySet[i];
		for ( j=0;j<BYTE ;j++, b++, temp >>= 1)
			if (temp & 01)
				printf("%d ", b);
	}
	printf("\n");
	return;
}

int read_set(char *mySet, int num)
{
	unsigned char temp;
	char seg, dig, i;
	dig = num % BYTE;
	seg = num / BYTE;
	temp = 01;

	for (i=0; i<dig ;i++ )
		temp <<= 1;

	mySet[seg] |= temp;
	return 0;
}
