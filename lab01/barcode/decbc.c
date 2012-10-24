#include <assert.h>
#include <stdio.h>
#include "bclib.h"

int main(int argc, char **argv) {
	char line[BC_WIDTH+1]; /* buffer for reading and writing */
	int barcode[BC_WIDTH][BC_NBITS] = {0};
	int i, j;

	/* read */
	j = 0;
	while(fgets(line, BC_WIDTH+1, stdin)) {
		for(i = 0; line[i]; ++i) 
			barcode[i][j] = line[i]=='#';
		++j;
	}
			
	/* decode */	
	for(i=0; i!=BC_WIDTH; ++i) 
		line[i] = bc_bits2char(barcode[i]);

    /* print */
	printf("%s\n", line);

    return 0;
}
