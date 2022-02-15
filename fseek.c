#include <stdio.h>
#include <string.h>
#include <ctype.h>


int chkint (char *arg);

main(int argc, char *argv[])
{
	int input_char, position;
	FILE *fp;
	char *prog = argv[0]; /* program name for errors */
	int num;
	num = chkint(argv[1]);
	printf("%d\n", num);
	while (--argc > 1) {
		printf("argc<%d>\n",argc);
		if ((fp = fopen(argv[argc], "r")) == NULL) {
			fprintf(stderr, "%s: can't open %s\n", prog, argv[argc]);
			exit(1);
		} else {
			fseek(fp, num, SEEK_SET);
			position = ftell (fp);
			printf("position: %d\n", position);
			input_char = getc (fp);
			printf ("Character at position %d = '%c'.\n\n", position, input_char);
			fclose(fp);
		}
	}
	if (ferror(stdout)) {
		fprintf(stderr, "%s: error writing stdout\n", prog);
		exit(2);
	}
	exit(0);
}

int chkint (char *arg)
{
	int num, i, length;
	length = strlen(arg);
	for (num=0, i=0; i < length; i++) {
		if (! isdigit(arg[i]))
			return -1;
		num = 10 * num + (arg[i] - '0');
	}
	return num;
}
