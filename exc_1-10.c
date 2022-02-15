#include <stdio.h>

/* count lines in input */
int main()
{
        int c;

        while ((c = getchar()) != EOF)
        {
                if(c == '\t')
                        printf("%s", "\\t");
                else if(c == ' ')
                        printf("%s", "\\s");
                else if(c == '\b')
                        printf("%s", "\\b");
                else if(c == '\\')
                        printf("%s", "\\\\");
                else
                        putchar(c);
        }
        return 0;
}