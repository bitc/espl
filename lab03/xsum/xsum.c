#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned int uint32_t;

void print_usage(void);
uint32_t calculate_checksum(char* filename);

/* xsum - print checksum of a file */
int main(int argc, char **argv) {
	int opt;
	char* optstring = "xh";
	int hexadecimal = 0;
	char* inputfile;
	uint32_t checksum;

	while((opt = getopt(argc, argv, optstring)) != -1) {
		switch(opt) {
			case 'x':
				hexadecimal = 1;
				break;
			case 'h':
			case '?':
				print_usage();
				exit(EXIT_FAILURE);
		}
	}

	if(optind != argc - 1) {
		print_usage();
		exit(EXIT_FAILURE);
	}

	inputfile = argv[optind];

	checksum = calculate_checksum(inputfile);
	if(hexadecimal) {
		printf("%08lX\n", (unsigned long)checksum);
	}
	else {
		printf("%lu\n", (unsigned long)checksum);
	}

	return 0;
}

void print_usage(void) {
	printf("usage: xsum [-x] [-h] FILE\n");
}

uint32_t calculate_checksum(char* filename) {
	/* Note: This function assumes a Little Endian architecture, and will
	 * ignore bytes at the end of a file that don't fill a full word */

	FILE* fp = fopen(filename, "rb");
	uint32_t checksum = 0;;
	uint32_t word;

	if(!fp) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	while(fread(&word, sizeof(word), 1, fp)) {
		checksum ^= word;
	}

	fclose(fp);

	return checksum;
}
