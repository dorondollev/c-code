#include <stdio.h>
#include <stdlib.h>
/*This is function Decleretion*/
char * get_name (void);
/*Main Program*/
int main(void)

{
	char *n;
	char c='f';
	n=&c;
	n = get_name();

	while(*n != '\0')
	printf("this is : %c \n",*n++);
	return 0;
}

/*This finction gets 2 vectors anfd there size and do scalar
multiple,by adding the result of multiple between two vectors
on the
,vetor1[i]*vector2[i] and sumerize the resault */
char * get_name(void)
{
	int i;
	char *ptr,*t;
	char names[3]={'a','b','c'};
	ptr = (char *)malloc(sizeof(names));
	for (i=0;i<3;i++,ptr++)
	{
		*ptr = names[i];
	}

	while (*--ptr != '\0')
	{
		printf("%c\n",*ptr);
	}
	return ++ptr;
	/*printf("this is a test - %c \n ",*ptr);*/
//	return (ptr+1);
	//t=(ptr+1);
	//return (t);
}
