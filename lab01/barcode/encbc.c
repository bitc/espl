#include <assert.h>
#include <stdio.h>
#include "bclib.h"

int main(int argc, char **argv) {
	int barcode[BC_WIDTH][BC_NBITS];
	int i, j;
	int n;
	char* c;

	n = 0;
	for(i=1; i<argc; ++i) {
		c = argv[i];
		while(*c != '\0') {
			bc_char2bits(*c, barcode[n]);
			++n;
			++c;
		}
		/* Add space character between words */
		if(i!=argc-1) {
			bc_char2bits(' ', barcode[n]);
			++n;
		}
		if(n == BC_WIDTH) {
			/* Don't overflow */
			break;
		}
	}

	for(j=0; j<BC_NBITS; ++j) {
		for(i=0; i<n; ++i) {
			if(barcode[i][j]) {
				printf("#");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}

	return 0;
}
