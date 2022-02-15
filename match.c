#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int match(char *s, char *t);

int main()
{
        char pattern[sysconf(_SC_BC_STRING_MAX)], text[sysconf(_SC_BC_STRING_MAX)];
        int low, endLoop, current, t_size, p_size;
        endLoop = current = 0;
        printf("please enter a pattern and text to comapre: ");
        scanf("%s", pattern);
        low = p_size = strlen(pattern);
        for(;;) {
                printf("please enter a text to match, enter 1 when done: ");
                scanf("%s", text);
                t_size = strlen(text);
                if ((endLoop = atoi(text)) == 1)
                        break;
                if (p_size >= t_size)
                        current = mystrcmp(pattern, text);
                else
                        current = mystrcmp(text, pattern);
                low = (current < low) ? current : low;
        }
        printf("the lowest number of unmatched characters is: %d\n", low);
        return 0;
}

int match(char *s, char *t)
{
        int i, unmatched=0;
        for (i=0; s[i] != '\0'; i++)
                if(s[i] != t[i])
                        unmatched++;
        return unmatched;
}