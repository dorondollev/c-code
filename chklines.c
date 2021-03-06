#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 5
#define PN (N * N)
#define RESULT ((N)*((PN)+(1))/(2))

void chkdownangle(int t[N][N]);
void chklines(int t[N][N]);
void stot(char s[], int t[N][N]);
void print_t(int t[N][N]);
void init_t(int t[N][N], int n);
void chkupangle(int t[N][N]);
void chkcolumns(int t[N][N]);
void readline(char *s);
void flush(char *s);

int main(int argc, char *argv[])
{
//	char string[] = "15 8 1 24 17 16 14 7 5 23 22 20 13 6 4 3 21 19 12 10 9 2 25 18 11";
	char string[51];
	int target[N][N] = {0};
	printf("Enter an ordered line of %d that will match rows, lines and	angles of %d that will match a result of %d each\n",PN,N,RESULT);
	scanf("%[ 0-9]", string);
	int i;
	for (i=0;string[i] != '\0';i++)
	{
		printf("%c ", string[i]);
	}
	stot(string, target);
	chkupangle(target);
	chkdownangle(target);
	chklines(target);
	chkcolumns(target);
	print_t(target); 
	return 0;
}

void readline(char *s)
{
        char c;
        while((c=getchar()) != EOF && c != '\n') {
			if (c == ' ' || isdigit(c) || c == '\t')
				*s++ = c;
			else
                s++;
		}
		*s = '\0';
}

void chkcolumns(int t[N][N])
{
	int i, j, n;
	for (j = 0;j < N;j++) {
		n = 0;
		for (i = 0;i < N;i++)
			n += t[i][j];
		if (n == RESULT)
			printf("column %d is ok %d\n", j+1, n);
		else {
			printf("column %d is wrong %d\n", j+1, n);
			exit(1);
		}
	}
}

void chklines(int t[N][N])
{
	int i, j, n;
	for (i = 0;i < N;i++) {
		n = 0;
		for (j = 0;j < N;j++)
			n += t[i][j];
		if (n == RESULT)
			printf("line %d is ok %d\n", i+1, n);
		else {
			printf("line %d is wrong %d\n", i+1, n);
			exit(1);
		}
	}
}

void chkdownangle(int t[N][N])
{
	int i, j, n = 0;
	for (i = N-1, j = N-1;i >= 0;i--, j--)
		n += t[i][j];
	if (n == RESULT)
		printf("down angle is ok: %d\n", n);
	else {
		printf("down angle is wrong: %d\n", n);
		exit(1);
	}
}

void chkupangle(int t[N][N])
{
	int i, j, n = 0;
	for (i=0, j=0;i < N;i++, j++)
		n += t[i][j];
	if (n == RESULT)
		printf("up angle is ok: %d\n", n);
	else {
		printf("up angle is wrong: %d\n", n);
		exit(1);
	}
}

void stot(char s[], int t[N][N])
{
	int  n, i, j;
    int slength = strlen(s);
	for (i=0;i < slength;) {
		for (j=i;(!isdigit(s[j]));j++)
			;
		for (n=0;isdigit(s[j]);j++)
			n = 10 * n + (s[j] - '0');
		init_t(t, n);
		i = j;
	}
}

void init_t(int t[N][N], int n)
{
	int i, j;
	for (i = 0;i < N;i++)
		for (j = 0;j < N;j++)
			if (t[i][j] == 0) {
				t[i][j] = n;
				return;
			}
}

void print_t(int t[N][N])
{
	printf("\nIt is a magic square\n");
	int i, j;
	for (i=0;i < N;i++){
		printf("\n");
		for (j=0;j < N;j++)
			printf("\t%d ", t[i][j]);
	}
	printf("\n");
}
