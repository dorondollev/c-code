#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define LENGTH 40
#define DATASIZE 128
#define BYTE 8
#define ARRAY ((DATASIZE) / (BYTE))

void print_prepare(char *pstr);
char delimiters[LENGTH] = " ,'\n'";

typedef struct 
{
	char *set_name;
	char data[ARRAY];
}Set;

Set group[] = {
	"A", {0},
	"B", {0},
	"C", {0},
	"D", {0},
	"E", {0},
	"F", {0},
	0, 0
};

void read_prepare(char *pstr)
{	
	Set *tmp;
	printf("pstr<%s>\n", pstr);
	pstr = strtok((char *)NULL, delimiters);
	tmp = check_group_name(pstr); 
	if (!tmp)
	{
		return;
	}
	if (tmp.data == NULL)
	{
		init(group.data);
	}
	printf("pstr is now <%s>\n",pstr);
	insert_data(tmp.data, pstr);
	printSet(tmp.data);
}

void insert_data(char *data, char *pstr)
{
	while ((pstr = strtok((char *)NULL, delimiters )) != NULL) 
	{
		int num = atoi(pstr);
		if (num	< 0)
		{
			return;
		}
		printf("pstring is now <%s>\n",pstr);
		if (num >= 0 && num <= 127)
		{
			addMember(data, num);
		}
		else 
		{
			printf("%s is out of range\n", pstr);
			return;
		}
	}
//	printSet(data);
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
		for (tmp = function_array; tmp->function_name; tmp++)
			if (strcmp(pstr, tmp->function_name) == 0)
				tmp->pt2Func(tmp->function_name);
	}
}

Set check_group_name(char *pstr)
{
	Set *tmp;
	for (tmp = group; tmp->set_name; tmp++)
			if (strcmp(pstr, tmp->set_name) == 0)
				return tmp;
	/*if (*group >= 'A' && *group <= 'F')
		return group;*/
	printf("No such set: %c\n", *group);
	return NULL;
}

void bitprint(unsigned x)
{
	int b;
	for (b = 0; x != 0;b++, x >>= 1)
		if (x & 01)
			printf("%d ", b);
	printf("\n");
}

int addMember(char *mySet, int num)
{
	unsigned char temp;
	char seg, dig, i;
	dig = num % BYTE;
	seg = num / BYTE;

	printf("\ndig=<%d>,seg=<%d>\n",dig,seg);

	temp = 01;

	for (i=0; i<dig ;i++ )
	{
		temp <<= 1;
	}
	mySet[seg] |= temp;
	return 0;
}

int init(char *mySet)
{
	int i;
	for (i=0;i<16 ;i++ )
	{
		mySet[i] = 0;
	}
	return 0;
}

int printSet(char *mySet)
{
	int i,j;
	unsigned char temp;

	for (i=0;i<ARRAY ;i++ )
	{
		printf("ROW# <%d> \t: ",i);
		temp = mySet[i];
		for ( j=0;j<BYTE ;j++ )
		{
			printf("%c",temp & 01?'1':'0');
			temp >>= 1;
		}
		printf("\n");
	}
	return 0;
}

int print_prepare(char *pstr)
{
	Set tmp;
	pstr = strtok((char *)NULL, delimiters);
	tmp = check_group_name(pstr);
	if (!tmp)
	{
		return;
	}
	printf("group<%c>\n",tmp.set_name);
	if (tmp.data == NULL)
	{
		init(tmp.data);
	}
	printSet(tmp.data);
	return 0;
}
