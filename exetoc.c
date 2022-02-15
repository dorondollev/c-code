#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *exe = "exe";
	char *tmp = "";
	for (; *argv[0] != '\0';tmp++, argv[0]++) {
		*tmp = *argv[0];
		printf("tmp<%c>argv<%c>\n",*tmp,*argv);
	}
	tmp--;
	while (*tmp == *exe)
	{
		if (*tmp == 'x')
			*tmp = '\0';
		tmp--;
		exe--;
	}
	*tmp = 'c';
	
	printf("tmp<%c>\n",*tmp);
	while (*tmp != '\0') {
		tmp--;
	}
	tmp++;
	printf("tmp<%c>\n",*tmp);
	printf("\n");
/*
	for (; i = '\0';tmp++, argv[0]++)
		printf("%c\n", *argv[0]);
	printf("argv<%c>\n",*argv[0]);
	argv[0]--;
	while (*exe == *argv[0])
	{
		printf("exe<%c>argv<%c>\n",*exe,*argv[0]);
		exe++;
		argv[0]--;
	}
	*argv[0] = 'c';
	printf("argv<%c>\n",*argv[0]);
	argv[0]++;
	*argv[0] = '\0';
	printf("argv<%c>\n",*argv[0]); */
}
