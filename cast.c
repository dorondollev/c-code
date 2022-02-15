#include <stdio.h>

char * getline(char *);
char * get_arg_name(char *);

int main(int argc, char *argv[])
{
	char *string;
	string = getline(argv[0]);
//	printf("getline-str<%s>\n", string);
	string = get_arg_name(string);
//	printf("arg<%s>\n",string);
	return 0;
}

char * get_arg_name(char *str)
{
	char *arg = "";
	printf("string<%s>\n", str);
	while(--*str != '.')
		;
	return arg;
}

char * getline(char *arg)
{
	char *str = "";
	printf("%s\n",arg);
	for (; *arg != '\n';str++, arg++) {
		printf("%c\n", *arg);
		*str = *arg;
	}
	printf("str<%c>arg<%c>\n",*str,*arg);
	printf("getline-arg<%s>\n", arg);
	printf("getline-str<%s>\n", str);
	return str;
}
