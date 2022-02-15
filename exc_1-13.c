#include <stdio.h>

#define CHAR 1 /* inside a word */
#define BLANK 0 /* outside a word */
/* count lines, words, and characters in input */
int main()
{
        int c, lastc, words[100], i, j, count, k;
        lastc = i = count = BLANK;

        while ((c = getchar()) != EOF)
        {
                if (c == '\t' || c == '\\' || c == ' ' || c == '\n')
                {
                        if(lastc == CHAR)
                        {
                                words[i] = count;
                                count = 0;
                                i++;
                        }
                        lastc = BLANK;
                }
                else
                {
                        count++;
                        lastc = CHAR;
                }
        }
        for(j=0;j < i;j++)
        {
                printf("value of column %d is %d", j+1, words[j]);
                for(k=0; k < words[j]; k++)
                        printf("*");
                printf("\n");
        }
        return 0;
}