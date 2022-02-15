#include "utils.h"

#define HOST 1
#define CNAME 2
#define MX 3

int isnumber(char *line);

static struct nlist *hashtab[HASHSIZE];

struct nlist {
	char *firstColumn;
	char *secondColumn;
	struct nlist *next;
};

int main()
{
	char * db = "db.10.10.150";//"db.dbs.co.il";/**/
	FILE *fp;
	char str[sysconf(_SC_LINE_MAX)];
	char *tmp;
	int size;

	if ((fp=fopen(db, "r")) == NULL)
	{
		printf("file not found\n");
		return(1);
	}
	while(fgets(str, sysconf(_SC_LINE_MAX), fp) != NULL)
	{
		if(isin(str) == 1)
		{
			size = strlen(str);			
			int i=0;
				//printf("%c",str[i]);				
		}
	}
	fclose(fp);
	return 0;
}

int isnumber(char *line)
{
	char *str;
	int count=0;
	int alpha = -1;
	int word=0;

	str = (char *)malloc(sizeof(line));
	for (*str = line[0];*str!='\0';str++, count++)
	{
		if(isspace(*str))
			continue;
		if(!isdigit(*str)
		{
			word = 1;
			break;
		}
	}
}

struct nlist *install(char *firstColumn, char *secondColumn)
{
	struct nlist *np;
	unsigned hashval;
	if ((np = lookup(firstColumn)) == NULL)  /* not found */
	{
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->firstColumn = strdup(firstColumn)) == NULL)
			return NULL;
		hashval = hash(firstColumn);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else /* already there */
		free((void *) np->secondColumn); /*free previous secondColumn */
	if ((np->secondColumn = strdup(secondColumn)) == NULL)
		return NULL;
	return np;
}

struct nlist *lookup(char *s)
{
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->firstColumn) == 0)
			return np; /* found */
	return NULL; /* not found */
}

unsigned hash(char *s)
{
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

int isin(char *line)
{
	char *cur;
	cur = strdup(line);
	while(*cur != '\0')
	{
		if (*cur == '@')
			return 0;
		if (*cur == ';')
			return 0;
		if (*cur == 'I')
		{
			cur++;
			if (*cur++ == 'N')
			{
				while(isspace(*cur))
					cur++;
				if (*cur == 'N')
				{
					cur++;
					if (*cur == 'S')
						return 0;
				}
				else if (*cur == 'C')
				{
					cur++;
					if (*cur == 'N')
					{
						cur++;
						if (*cur == 'A')
						{
							cur++;
							if (*cur == 'M')
							{
								cur++;
								if (*cur == 'E')
									return 2;
							}
						}
					}
				}
				else if (*cur == 'M')
				{
					cur++;
					if (*cur == 'X')
						return 3;
				}
				return 1;
			}
		}
		cur++;
	}
	return 0;
}
