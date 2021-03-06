#include <stdio.h>

#define DATASIZE 128
#define CHAR 8
#define MAXCHARS ((CHAR) / (DATASIZE))

/*
        int array = 8;
        int bit = 119; the bit you wish to light up
        printf("mod<%d>divide<%d>\n",bit % array,bit / array); result is: 7 14
*/
unsigned numOfChars(unsigned num);
unsigned arrayCount(unsigned num);
void addbit(char x, unsigned num);
int bitcount(unsigned x);
void bitprint(unsigned x);
void print_set(char x);

main()
{
	unsigned bit = 6;
	char A[16];
	unsigned array_count = arrayCount(bit), num_of_chars = numOfChars(bit);
//	addbit(A[], bit);
	printf("A char is<%c>\n", A[arrayCount(bit)]);
	print_set(A[arrayCount(bit)]);
	bitprint(A[arrayCount(bit)]);
}
/*void addbit (char x, unsigned num)
{
	char y = 1;
	y <<= num;
	x |= y;
	printf("x<%d>\n", x);
}
*/
void bitprint(unsigned x)
{
	int b;
	for (b = 0; x != 0;b++, x >>= 1) {
		if (x & 01)
			printf("%d ", 1);
		else
			printf("%d ", 0);
	}
	printf("\n");
}

void print_set(char x)
{
        int b;
        for (b = 0; x != 0;b++, x >>= 1)
                if (x & 01)
                        printf("%d ", b);
        printf("\n");
}

unsigned arrayCount(unsigned num)
{
//	printf("array count: %d\n", num / CHAR);
	return num / CHAR;
}

unsigned numOfChars(unsigned num)
{
//	printf("num of chars: %d\n", num % CHAR);
	return num % CHAR;
}
