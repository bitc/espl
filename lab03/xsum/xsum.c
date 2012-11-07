#include <stdio.h>
#include <unistd.h>

void print_usage(void);

/* xsum - print checksum of a file */
int main(int argc, char **argv) {
	int opt;
	char* optstring = "xh";
	int hexadecimal = 0;
	char* inputfile;

	while((opt = getopt(argc, argv, optstring)) != -1) {
		switch(opt) {
			case 'x':
				hexadecimal = 1;
				break;
			case 'h':
			case '?':
				print_usage();
				return -1;
		}
	}

	if(optind != argc - 1) {
		print_usage();
		return -1;
	}

	inputfile = argv[optind];

	/* TODO Calculate and print checksum */
	printf("%s\n", inputfile);

	return 0;
}

void print_usage(void) {
	printf("usage: xsum [-x] [-h] FILE\n");
}
