#include <stdio.h>

typedef char set[16];
	
int main(int argc, unsigned char *argv[])
{
	set	A,B;
	int	res,ans=0,j;
	char mem;

	printf("\n init2 \n");
	res=init(A);
	res=init(B);
	res=printSet(A);
	while (ans == 0)
	{
		printf("\nPlease insert a number \n");
		scanf("%d",&j);
		mem = j;
		printf("\nmem = <%d>",mem);
		res = addMember(A , mem);
		res=printSet(A);
		printf("\nmem = <%d>",mem);
		scanf("%d",&j);
		mem = j;
		res = addMember(A , mem);
		res=printSet(A);
		printf("\ndismem = <%d>",mem);
		scanf("%d",&j);
		mem = j;
		res = addMember(B , mem);
		res=unionSet(A,B,A);
		res=printSet(A);
		printf("\nPlease update ans <0> go on, else quit\n");
		scanf("%d",ans);
	}
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
			temp >>= 1;
		}
		printf("\n");
	}
	return 0;
}

int addMember(set mySet,char num)
{
	unsigned char seg,dig,temp,i;

	dig = num % 8;
	seg = num / 8;

	printf("\ndig=<%d>,seg=<%d>\n",dig,seg);

	temp = 01;

	for (i=0; i<dig ;i++ )
	{
		temp <<= 1;
	}

	mySet[seg] |= temp;
	printf("\nTEMP\n");

	for ( i=0;i<8 ;i++ )
		{
			printf("%c",temp & 01?'1':'0');
			temp >>= 1;
		}
	printf("\n");
	return 0;
}

int subMember(set mySet,char num)
{
	unsigned char seg,dig,temp,i;

	dig = num % 8;
	seg = num / 8;

	printf("\ndig=<%d>,seg=<%d>\n",dig,seg);

	temp = 01;

	for (i=0; i<dig ;i++ )
	{
		temp <<= 1;
	}
	
	mySet[seg] &= ~temp;
	//temp |= 01;
	printf("\nTEMP\n");
	for ( i=0;i<8 ;i++ )
		{
			printf("%c",temp & 01?'1':'0');
			temp >>= 1;
		}
	printf("\n");
	return 0;
}

int unionSet(set A,set B,set C)
{
	int i;

	for (i=0;i<16 ;i++ )
	{
		C[i]=A[i] | B[i];
	}
	return 0;
}
