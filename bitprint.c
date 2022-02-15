#include <stdio.h>

int main(int argc, char *argv[])
{
	char *set;
	int number = 6;
	read_set(set, number);
	print_set(set);
	printf("Hello, world\n");
	
	return 0;
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
