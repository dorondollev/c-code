#include <stdio.h>

typedef char set[16];
	
int main(int argc, unsigned char *argv[])
{
	set	A,B;
	int	res;

	res=init(A);
	A[0] = 6;
	res=printSet(A);

	
	return 0;
}

int init(set mySet)
{
	int i;
	for (i=0;i<16 ;i++ )
	{
		mySet[i] = 0;
	}
	return 0;
}

int printSet(set mySet)
{
	int i,j;
	unsigned char temp;

	for (i=0;i<16 ;i++ )
	{
		printf("ROW# <%d> \t: ",i);
		temp = mySet[i];
		for ( j=0;j<8 ;j++ )
		{
			printf("%c",temp & 01?'1':'0');
		}
		temp >>= 1;
		printf("\n");
	}
	return 0;

}

