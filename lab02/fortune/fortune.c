#include <stdio.h>

#define MAX_LINE_LENGTH 128
 
long get_lines(FILE* fp);

/* print random line */
int main(int argc, char **argv) {
	if(argc != 2) {
		fprintf(stderr, "You must supply a single command line argument\n");
		return 1;
	}

	FILE* fp = fopen(argv[1], "r");
	if(!fp) {
		perror("Error opening file");
		return 2;
	}

	long num_lines = get_lines(fp);

	/* TODO This print is only temporary for testing */
	printf("num lines in file: %lu\n", num_lines);

	/* TODO Finish */

	fclose(fp);
 
	return 0;
}

/* Get the number of lines in a file */
long get_lines(FILE* fp) {
	long numlines;

	numlines = 0;
	char line[MAX_LINE_LENGTH];
	while(fgets(line, MAX_LINE_LENGTH, fp) != 0) {
		++numlines;
	}

	return numlines;
}
