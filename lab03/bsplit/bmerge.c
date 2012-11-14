#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned int uint32_t;

void print_usage(void);

int main(int argc, char **argv) {
	char* optstring = "o:hx:";
	char* output = 0;
	char* prefix;
	uint32_t expected_checksum;
	long compare_checksum = 0;
	int opt;

	while((opt = getopt(argc, argv, optstring)) != -1) {
		switch(opt) {
			case 'o':
				output = optarg;
				break;
			case 'x':
				compare_checksum = strtol(optarg, 0, 10);
				if(compare_checksum < 0 || compare_checksum > (1L<<32)-1) {
					printf("Expected checksum is invalid\n");
					print_usage();
					exit(EXIT_FAILURE);
				}
				expected_checksum = compare_checksum;
				compare_checksum = 1;
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

	prefix = argv[optind];

	/* TODO */

	return 0;
}

void print_usage(void) {
	printf("usage: bmerge [-o OUTPUT] [-h] [-x CHECKSUM] PREFIX\n");
}
