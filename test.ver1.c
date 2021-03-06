#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define LENGTH 40

char delimiters[LENGTH] = " ,'\n'";

void read_prepare(char *pstr)
{
	printf("pstr<%s>\n", pstr);
	pstr = strtok((char *)NULL, delimiters);
	if (!check_group_name(pstr)) 
	{
		printf("No such set: %s\n", pstr);
		return;
	}
}

void print_prepare(char *pstr)
{
	printf("pstr<%s>\n", pstr);
	return;
}

void union_prepare(char *pstr)
{
	printf("pstr<%s>\n", pstr);
	return;
}

void intersect_prepare(char *pstr)
{
	printf("pstr<%s>\n", pstr);
	return;
}

void sub_prepare(char *pstr)
{
	printf("pstr<%s>\n", pstr);
	return;
}

void halt(char *pstr)
{
	printf("pstr<%s>\n", pstr);
	exit(0);
}

typedef struct 
{
	char group;
	char set[16];
}Set;

typedef struct 
{
	char  *function_name;
	void (*pt2Func) (char *);
} prepare_t;

prepare_t function_array[] = { 
	"read_set", read_prepare,
	"print_set", print_prepare,
	"union_set", union_prepare,
	"intersect_set", intersect_prepare,
	"sub_set", sub_prepare,
	"halt", halt,
	0, 0 
};

//char *func[] = { "read_set", "print_set", "union_set", "intersect_set", "sub_set", "halt" };

//char * chkfunc(char *pstr);


main()
{
	char string1[LENGTH];
    char *pstr, *function;
	prepare_t *tmp;
	while (1)
	{
		printf("Enter the string to be searched: ");
		fgets(string1, LENGTH, stdin);
		pstr = strtok(string1, delimiters);
		for (tmp = function_array; tmp->function_name /*&& strcmp(pstr, tmp->function_name)*/; tmp++)
			if (strcmp(pstr, tmp->function_name) == 0)
				tmp->pt2Func(tmp->function_name);
	}
}

char * check_group_name(char *group)
{
	if (*group >= 'A' && *group <= 'F')
		return group;
	return '\0';
}
/*
char * chkfunc(char *pstr)
{
	int i;
	for (i=0;func[i] != '\0';i++)
		if(strcmp(pstr, func[i]) == 0)
			return pstr;
	return '\0';
}
*/
void bitprint(unsigned x)
{
	int b;
	for (b = 0; x != 0;b++, x >>= 1)
		if (x & 01)
			printf("%d ", b);
	printf("\n");
}
