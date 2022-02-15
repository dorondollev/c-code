#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	//char *exe = "exe";
	char *tmp = "";
	strcpy(tmp, argv[0]);
	int num = my_strlen(argv[0]);
	printf("%d\n",num);
	int i;
	for (i=0; i < num; i++)
	{
		printf("tmp<%c>",tmp[i]);
	}
	printf("\n");
}

int my_strlen(char s[])
{
	int i=0;
	while(s[i] != '\0')
		++i;
	return i;
}
