#define A_EQUALS_B 0
#define A_GREATER_B 1
#define A_LESS_B 2

int cmpstr(char* a, char* b) {
	for(;;) {
		if(*a == '\0')
			break;
		if(*a != *b)
			break;
		++a;
		++b;
	}
	if(*a == *b)
		return A_EQUALS_B;
	if(*a < *b)
		return A_LESS_B;
	if(*a > *b)
		return A_GREATER_B;
}
