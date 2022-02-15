#include <stdio.h>

int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
char *strchr(const char *s, int c);
/* int my_strlen(char s[]) */

int main(int argc, char *argv[])
{
	char s1[50], s2[50], c;
	int n, menu;

	printf("Please make a selection: ");
	printf("\n1. Compare two strings.");
	printf("\n2. Compare partialy two strings.");
	printf("\n3. Find a character location inside a string.");
	scanf("%d", menu);
	switch (menu)
	{
	case '1':
		printf("\nPlease enter the first string: ");
		scanf("%s", s1);
		printf("\nPlease enter the second string: ");
		scanf("%s", s2);
		printf("\nCompare result is: %d", my_strcmp(s1, s2));
		break;
	case '2':
		printf("\nPlease enter the first string: ");
		scanf("%s", s1);
		printf("\nPlease enter the second string: ");
		scanf("%s", s2);
		printf("\nNow enter the number of characters you wish to compare: ");
		scanf("%d", n);
		printf("\nCompare partialy result is: %d", my_strncmp(s1, s2, n));
		break;
	case '3':
		printf("\nPlease enter the string you wish to search: ");
		scanf("%s", s1);
		printf("\nPlease enter the character you are looking for: ");
		scanf("%c", c);
		printf("\nCharacter location is %d", my_strchr(s1, c));
		break;
	default:
		printf("\nYou must choose one of three choises.");
		break;	
	}
}

int my_strcmp(char s1[], char s2[])
{
	int i;
	for (i = 0; s[i] == t[i]; i++)
		if (s[i] == '\0')
			return 0;
	return s[i] - t[i];
}

int my_strncmp(char s1[], char s2[], size_t n)
{
	int i;
	for (i = 0; s[i] == t[i]; i++)
		if (s[i] == '\0' || i >= n)
			return 0;
	return s[i] - t[i];
}

int my_strchr(char s[], int c)
{
	int i;
	for (i=0;s[i] != '\0';i++)
		if (s[i] == c)
			return i;
	return -1;
}
