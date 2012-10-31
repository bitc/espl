#include <stdio.h>
#include <stdlib.h>
#include "namelist.h"

void read_file(char *fname, struct namelist *namelist);

int main(int argc, char **argv) {
	int i;

	struct namelist *namelist;

	namelist = make_namelist();

	for(i = 1; i < argc; ++i) {
		read_file(argv[i], namelist);
	}
	/* TODO */

	free(namelist->names);
	free(namelist);

	return 0;
}

void read_file(char *fname, struct namelist *namelist) {
	FILE *fp;
	char name[NAMELEN];

	printf("%s\n", fname);

	fp = fopen(fname, "r");
	if(!fp) {
		perror("Error opening file");
		return;
	}

	while(fgetname(name, NAMELEN, fp)) {
		printf("%s ", name);
	}
	printf("\n");

	fclose(fp);
}
