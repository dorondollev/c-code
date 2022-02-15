#include <stdio.h>

#define CHAR 1 /* inside a word */
#define BLANK 0 /* outside a word */
/* count lines, words, and characters in input */
int main()
{
        int c, lastc;
        lastc = BLANK;
        while ((c = getchar()) != EOF)
        {
                if (c == '\n')
                {
                        if(lastc == CHAR)     /* end of a word */
                                putchar(c);
                        lastc = BLANK;
                }
                else if (c == '\t' || c == '\\' || c == ' ')
                {
                        if(lastc == CHAR)
                                putchar('\n');
                        lastc = BLANK;
                }
                else
                {
                        putchar(c);
                        lastc = CHAR;
                }
        }
        return 0;
}