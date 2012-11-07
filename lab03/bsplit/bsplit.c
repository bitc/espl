#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_CHUNK_SIZE 32;
#define MIN_CHUNK_SIZE 5

void print_usage(void);

int main(int argc, char **argv) {
	char* optstring = "b:hx";
	long chunk_size = DEFAULT_CHUNK_SIZE;
	int print_checksum = 0;
	int opt;

	while((opt = getopt(argc, argv, optstring)) != -1) {
		switch(opt) {
			case 'b':
				chunk_size = strtol(optarg, 0, 10);
				if(chunk_size < MIN_CHUNK_SIZE) {
					printf("Chunk size must be at least %ld bytes\n", MIN_CHUNK_SIZE);
					print_usage();
					exit(EXIT_FAILURE);
				}
				break;
			case 'x':
				print_checksum = 1;
				break;
			case 'h':
			case '?':
				print_usage();
				exit(EXIT_FAILURE);
		}
	}

	/* TODO */

	return 0;
}

void print_usage(void) {
	printf("usage: bsplit [-b SIZE] [-h] [-x] FILE\n");
}
