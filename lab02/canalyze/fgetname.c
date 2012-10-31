#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "fgetname.h"

int skip_string_literal(FILE* stream);
int skip_comment(FILE* stream);

char *fgetname(char *name, int size, FILE *stream) {
	int ich;
	int ch;

	assert(size>0); /* the buffer must have space in it */

	/** before a name */
	for(;;) {
		ch = fgetc(stream);
		if(ch=='/') {
			ch = fgetc(stream);
			if(ch == '*')
				ch = skip_comment(stream);
		}
		if(ch=='"')
			ch = skip_string_literal(stream);
		if(ch==EOF) /* end of stream or error before a name */
			return NULL;
		if(isalpha(ch) || ch=='_') /* a name begins */
			break; 
	}
		
	/** reading the name */
	ich = 0;
	for(;;) {
		/* a name character */
		if(ich!=size-1) /* add the character if space left */
			name[ich++] = ch;

		ch = fgetc(stream);
		if(ch==EOF) /* name ends at end of file */
			break;
		if(!(isalnum(ch) || ch=='_')) {
			ungetc(ch, stream); /* end of the name,
								   return the character to the stream */
			break;
		}
	}
	assert(ich<=size-1); /* truncated if too long */
	name[ich] = '\0';

	return name;
}

int skip_string_literal(FILE* stream) {
	/* This function does not correctly handle escape sequences */
	char ch;

	for(;;) {
		ch = fgetc(stream);
		if(ch==EOF)
			return EOF;
		if(ch=='"')
			return fgetc(stream);
	}
}

int skip_comment(FILE* stream) {
	char ch;
	for(;;) {
		ch = fgetc(stream);
		while(ch=='*') {
			ch = fgetc(stream);
			if(ch=='/')
				return fgetc(stream);
		}
		if(ch==EOF)
			return EOF;
	}
}
