#include <stdio.h>
#include <stdlib.h>
#include "namelist.h"

void read_file(char *fname, struct namelist *namelist);
int is_cname(char* name);
int compare_namestat(const void *lhs, const void *rhs);

int main(int argc, char **argv) {
	int i;
	struct namelist *namelist;

	namelist = make_namelist();

	for(i = 1; i < argc; ++i) {
		read_file(argv[i], namelist);
	}

	qsort(namelist->names, namelist->size, sizeof(struct namestat), compare_namestat);

	for(i = 0; i < namelist->size; ++i) {
		printf("%s %d\n", namelist->names[i].name, namelist->names[i].count);
	}

	free(namelist->names);
	free(namelist);

	return 0;
}

void read_file(char *fname, struct namelist *namelist) {
	FILE *fp;
	char name[NAMELEN];

	fp = fopen(fname, "r");
	if(!fp) {
		perror("Error opening file");
		return;
	}

	while(fgetname(name, NAMELEN, fp)) {
		if(!is_cname(name)) {
			add_name(namelist, name);
		}
	}

	fclose(fp);
}

int is_cname(char* name) {
	int i;
	static char* reserved_words[] = {
		"_Packed",
		"auto",
		"break",
		"case",
		"char",
		"const",
		"continue",
		"default",
		"do",
		"double",
		"else",
		"enum",
		"extern",
		"float",
		"for",
		"goto",
		"if",
		"int",
		"long",
		"register",
		"return",
		"short",
		"signed",
		"sizeof",
		"static",
		"struct",
		"switch",
		"typedef",
		"union",
		"unsigned",
		"void",
		"volatile",
		"while" };

	for(i=0; i<sizeof(reserved_words)/sizeof(char*); ++i) {
		if(strcmp(name, reserved_words[i]) == 0) {
			return 1;
		}
	}

	return 0;
}

int compare_namestat(const void *lhs, const void *rhs) {
	return strcmp(
			((struct namestat*)lhs)->name,
			((struct namestat*)rhs)->name);
}
