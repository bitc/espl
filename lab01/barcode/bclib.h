#ifndef BCLIB_H
#define BCLIB_H

/* maximum width of the bar code */
#define BC_WIDTH 80
/* number of bits per character */
#define BC_NBITS 8

/* character for representing bit 1 */
#define BC_ONE '#'
/* character for representing bit 0 */
#define BC_ZERO ' '

/* encode a character into a bit vector
 * write the bit vector to the array pointed to
 * by `bits', return the pointer to the bit vector 
 */
int *bc_char2bits(int ch, int *bits);


/* decode the character from a bit vector,
 * return the character
 */
int bc_bits2char(int *bits);


/* testing hook */
void bc_test();


#endif
