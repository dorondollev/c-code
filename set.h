#define LENGTH 40
#define DATASIZE 128
#define BYTE 8
#define MAXGROUP 6
#define ARRAY ((DATASIZE) / (BYTE))

void union_set(char *set1, char *set2, char *set3);
void intersect_set(char *set1, char *set2, char *set3);
void sub_set(char *set1, char *set2, char *set3);
void print_set(char *mySet);
int read_set(char *mySet, int num);