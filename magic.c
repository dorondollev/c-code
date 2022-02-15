#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 5
/* PN = for power N */
#define PowerN ((N)*(N))
/* SUM - for sum N's */
#define SUM ((N)*((PowerN)+(1))/(2))
/* LENGTH - for total chars */
#define LENGTH ((PowerN)*(2))

char delimiters[LENGTH] = " '\t'";

int main(int argc, char *argv[])
{
	//char s[] = "15 8 1 24 17 16 14 7 5 23 22 20 13 6 4 3 21 19 12 10 9 2 25 18 11";
	char string[LENGTH], *pstr;
	int target[LENGTH], counter;
	printf("Enter %d numbers each line space suppurated, row, angle of %d should produce a sum of %d: ",PowerN,N,SUM);
    if (fgets(string, LENGTH, stdin) != NULL) {
		if ((pstr = strtok(string, delimiters ))!= NULL) {
			/* pstr points to the first token */
			printf("Token 1 is %s\n", pstr);
			counter = 2;
			while ((pstr = strtok((char *)NULL, delimiters )) != NULL) {
				printf("Token %d is %s\n", counter, pstr);
				counter++;
			}
		}
	}
	return 0;
}
