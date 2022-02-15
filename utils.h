#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define HASHSIZE 101

struct nlist *install(char *, char *);
char* strncopy(char *, const char *, size_t );
int isptr(char *);
char * getFirstCol(char *);
unsigned hash(char *);
unsigned hash(char *);
struct nlist *lookup(char *);
int isin(char *);
