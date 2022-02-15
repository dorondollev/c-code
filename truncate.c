#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int chkFlag(char *);

int main(int argc, char *argv[])
{
	char *num_str;
	char *file_name;
	long int new_size;
	char *end_ptr;
	FILE *fp;
	int location;
	int flag;
	
	if (argc == 4)
	{
		if ((flag=chkFlag(argv[3])) != 1)
		{
			fprintf(stderr, "usage: %s file new-size-in-bytes [-r]\n", argv[0]);
			return 2;
		}
	}
	else if (argc != 3)
	{
		fprintf(stderr, "usage: %s file new-size-in-bytes [-r]\n", argv[0]);
		return 2;
	}
	
	new_size = strtol(argv[2], &end_ptr, 10);
	
	if (!argv[2] || *end_ptr)
	{
		fprintf(stderr, "'%s' is not a valid file size\n", argv[2]);
		return 2;
	}
	
	if((fp = fopen(argv[1], "r")) != NULL)
	{
		fseek(fp, 0L, SEEK_END);
		location = ftell (fp);
		fclose(fp);
	}
	else
	{
		fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
		return 2;
	}
	
	if(new_size <= location)
	{
		if (flag == 1)
		{
			if ((fp = fopen(argv[1], "r+")) != NULL)
			{
				if (fwrite('\0', 1, new_size, fp) < new_size)
				{
					fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
				}
				fclose(fp);
			}
		}
		else if (truncate(argv[1], new_size))
		{
			fprintf(stderr, "%s\n", strerror(errno));
			return 2;
		}
	}
	else
	{
		printf("New size must be less than file size\n");
		return 1;
	}
	return 0;
}

int chkFlag(char *s)
{
	if (*s == '\0')
		return 0;
	if (*s++ == '-' && *s == 'r')
		return 1;
	return -1;
}
