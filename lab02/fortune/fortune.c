#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE_LENGTH 128
 
long get_lines(FILE* fp);
long random_number(long max);
void print_line(FILE* fp, long line);

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

	long random_line = random_number(num_lines);

	if(fseek(fp, 0, SEEK_SET)) {
		perror("Error seeking file");
	}

	print_line(fp, random_line);

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

/* Returns a random number between 0 and max (inclusive) */
long random_number(long max) {
	srandom(time(0));

	return random() % max;
}

void print_line(FILE* fp, long l) {
	long i;

	char line[MAX_LINE_LENGTH];
	for(i = 0; i < l+1; ++i) {
		if(!fgets(line, MAX_LINE_LENGTH, fp)) {
			perror("Error reading file");
			return;
		}
	}

	printf("%lu: %s", l+1, line);
}
