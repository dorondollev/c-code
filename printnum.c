#include <stdio.h>

#define printnum(N) { if (N > 0) { printnum(N-1); } printf("%d\n", N); }

int main(int argc, char *argv[])
{
	printnum(10);	
	return 0;
}
