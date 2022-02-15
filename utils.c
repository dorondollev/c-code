#include "utils.h"

char * strncopy(char *dest, const char *src, size_t n)
{
	size_t i;
	for (i = n ; i > 0 && (src[i] != '\0' || src[i] != ' ' || src[i] != '\t'); i--)
		dest[i] = src[i];
	for (;i < n; i++)
		dest[i] = '\0';
	return dest;
}

char * getFirstCol(char *line)
{
	char *st;
	st = (char *)malloc(sizeof(line));
	//while(isspace(*line))
	//	line++;
	while(isalnum(*line) || *line == '-' || *line == '_')
	{
		*st++ = *line++;
		printf("%s",line);
	}
	//if (isspace(*st))
	//	*st-- = '\0';
	//while(*st != '\0')
	//	st--;
	return st;
}
