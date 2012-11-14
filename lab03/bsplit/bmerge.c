#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned int uint32_t;
#define MAX_FILENAME_LENGTH 1024

void print_usage(void);
uint32_t merge_file(char* prefix, char* outfile);
uint32_t process_chunk(FILE* out_fp, FILE* chunk_fp, char* chunk_fname);

int main(int argc, char **argv) {
	char* optstring = "o:hx:";
	char* output = 0;
	char* prefix;
	uint32_t expected_checksum;
	uint32_t calculated_checksum;
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

	if(!output) {
		output = prefix;
	}

	calculated_checksum = merge_file(prefix, output);

	if(compare_checksum) {
		if(calculated_checksum == expected_checksum) {
			printf("Checksum matches\n");
		}
		else {
			printf("Checksum mismatch, calculated value is: %lu\n", (unsigned long)calculated_checksum);
		}
	}

	return 0;
}

void print_usage(void) {
	printf("usage: bmerge [-o OUTPUT] [-h] [-x CHECKSUM] PREFIX\n");
}

uint32_t merge_file(char* prefix, char* outfile) {
	FILE* fp;
	FILE* chunk_fp;
	char chunk_fname[MAX_FILENAME_LENGTH];
	int chunk_num = 1;
	uint32_t global_checksum = 0;

	fp = fopen(outfile, "wb");
	if(!fp) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	for(;;) {
		int e = snprintf(chunk_fname, MAX_FILENAME_LENGTH, "%s.%02d", prefix, chunk_num);
		if(e < 0 || e >= MAX_FILENAME_LENGTH) {
			printf("Filename is too long\n");
			exit(EXIT_FAILURE);
		}
		chunk_fp = fopen(chunk_fname, "rb");
		if(!chunk_fp) {
			/* Finish when a chunk file cannot be opened */
			break;
		}

		global_checksum ^= process_chunk(fp, chunk_fp, chunk_fname);
		++chunk_num;

		fclose(chunk_fp);
	}

	fclose(fp);

	return global_checksum;
}

uint32_t process_chunk(FILE* out_fp, FILE* chunk_fp, char* chunk_fname) {
	uint32_t checksum_header;
	uint32_t checksum = 0;
	uint32_t word = 0;
	size_t n;

	/* TODO Error checking, Verify that the file contains a checksum */
	fread(&checksum_header, sizeof(checksum), 1, chunk_fp);

	while((n = fread(&word, 1, sizeof(word), chunk_fp)) > 0) {
		/* TODO Error checking */
		fwrite(&word, 1, n, out_fp);
		checksum ^= word;
		word = 0;
	}

	if(checksum != checksum_header) {
		printf("Checksum mismatch in file %s\n", chunk_fname);
	}

	return checksum;
}
