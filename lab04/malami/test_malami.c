#include <stdlib.h>
#include <stdio.h>

/* malami is a like the atoi function from the standard library */
int malami(char* str);

int main(int argc, char **argv) {
	char* test_string = "5123";

	if(argc != 2) {
		printf("Usage: %s [NUMBER]\n", argv[0]);
		return -1;
	}

	printf("Testing malami with string %s, result is: %d\n", test_string, malami(test_string));
	printf("Number from command line argument is: %d\n", malami(argv[1]));

	return 0;
}
