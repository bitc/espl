#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>

#define DEFAULT_CHUNK_SIZE 32
#define MIN_CHUNK_SIZE 8
#define MAX_FILENAME_LENGTH 1024
#define MAX_ALLOWED_CHILDREN 128

typedef unsigned int uint32_t;

void print_usage(void);
long get_file_size(char* filename);
uint32_t split_file(char* filename, long chunk_size, int max_child_processes);
uint32_t process_chunk(FILE* input_fp, long chunk_size, char* chunk_filename);

int main(int argc, char **argv) {
	char* optstring = "b:hxp:";
	long chunk_size = DEFAULT_CHUNK_SIZE;
	int print_checksum = 0;
	int max_child_processes = INT_MAX;
	char* inputfile;
	int opt;
	size_t checksum;

	while((opt = getopt(argc, argv, optstring)) != -1) {
		switch(opt) {
			case 'b':
				chunk_size = strtol(optarg, 0, 10);
				if(chunk_size < MIN_CHUNK_SIZE) {
					printf("Chunk size must be at least %d bytes\n", MIN_CHUNK_SIZE);
					print_usage();
					exit(EXIT_FAILURE);
				}
				if(chunk_size % 4 != 0) {
					printf("Chunk size must be a multiple of 4\n");
					print_usage();
					exit(EXIT_FAILURE);
				}
				break;
			case 'x':
				print_checksum = 1;
				break;
			case 'p':
				max_child_processes = strtol(optarg, 0, 10);
				if(max_child_processes < 1) {
					printf("maximum number of child processes must be at least 1\n");
					print_usage();
					exit(EXIT_FAILURE);
				}
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

	checksum = split_file(inputfile, chunk_size, max_child_processes);

	if(print_checksum) {
		printf("%lu\n", (unsigned long)checksum);
	}

	return 0;
}

void print_usage(void) {
	printf("usage: pbsplit [-b SIZE] [-h] [-x] [-p NUM] FILE\n");
}

long get_file_size(char* filename) {
	struct stat buf;
	stat(filename, &buf);
	return buf.st_size;
}

/* Returns the checksum of the file */
uint32_t split_file(char* filename, long chunk_size, int max_child_processes) {
	FILE* fp;
	uint32_t global_checksum = 0;
	char chunk_fname[MAX_FILENAME_LENGTH];

	long filesize = get_file_size(filename);
	long num_chunks = (filesize + (chunk_size-4) - 1) / (chunk_size-4);

	int my_chunk = 0;
	int num_active_children = 0;

	while(my_chunk < num_chunks)
	{
		while(num_active_children >= max_child_processes) {
			if(wait(0) == -1) {
				perror("Error waiting for child to finish");
			}
			num_active_children--;
		}
		pid_t child;
		child = fork();
		if(child == -1)
		{
			perror("Error forking child");
			exit(EXIT_FAILURE);
		}
		else if(child == 0)
		{
			/* Child */
			int e = snprintf(chunk_fname, MAX_FILENAME_LENGTH, "%s.%02d", filename, my_chunk+1);

			if(e < 0 || e >= MAX_FILENAME_LENGTH) {
				printf("Filename is too long\n");
				exit(EXIT_FAILURE);
			}

			fp = fopen(filename, "rb");
			if(!fp) {
				perror("Error opening file");
				exit(EXIT_FAILURE);
			}

			if(fseek(fp, my_chunk * chunk_size, SEEK_SET) == -1) {
				perror("Error seeking");
				exit(EXIT_FAILURE);
			}
			process_chunk(fp, chunk_size, chunk_fname);
			fclose(fp);
			exit(0);
		}
		/* Parent */
		num_active_children++;
		my_chunk++;
	}

	for(my_chunk = 0; my_chunk < num_active_children; ++my_chunk) {
		if(wait(0) == -1) {
			perror("Error waiting for child");
		}
	}

	return global_checksum;
}

static size_t min(size_t a, size_t b) {
	return a < b ? a : b;
}

uint32_t process_chunk(FILE* input_fp, long chunk_size, char* chunk_filename) {
	FILE* chunk_fp;
	uint32_t checksum = 0;
	uint32_t word;
	long num_bytes = 4;

	chunk_fp = fopen(chunk_filename, "wb");
	if(!chunk_fp) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	/* Write a placeholder at the beginning of the file to make room for
	 * the checksum */
	fwrite(&checksum, sizeof(checksum), 1, chunk_fp);

	for(;;) {
		size_t n;
		word = 0;
		n = fread(&word, 1, min(sizeof(word), chunk_size - num_bytes), input_fp);
		fwrite(&word, 1, n, chunk_fp);
		num_bytes += n;

		checksum ^= word;

		/* End of input file */
		if(n < sizeof(checksum)) {
			break;
		}

		/* Output file reached destination size */
		if(num_bytes == chunk_size) {
			break;
		}
	}

	/* Write the real checksum at the beginning of the file */
	rewind(chunk_fp);
	fwrite(&checksum, sizeof(checksum), 1, chunk_fp);

	fclose(chunk_fp);

	return checksum;
}
